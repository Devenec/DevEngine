/**
 * @file platform/windows/WindowsGraphicsDeviceManager.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Log.h>
#include <core/Memory.h>
#include <core/Rectangle.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsDeviceFactory.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>

#define OEMRESOURCE
#include <platform/windows/Windows.h> // Needs to be the first header to include Windows.h
#undef OEMRESOURCE

#include <platform/windows/WindowsWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG		  = "[Graphics::GraphicsDeviceManager - Windows] ";
static const Char16* WINDOW_CLASS_NAME	  = DE_CHAR16("devengine");
static const Char16* WINDOW_DEFAULT_TITLE = DE_CHAR16("DevEngine Application");
static const Uint32 WINDOW_STYLE		  = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

static HWND createWindow(const Uint32 width = 640u, const Uint32 height = 480u);
static Core::Rectangle createWindowRectangle(const Uint32 width, const Uint32 height);
static void deregisterWindowClass();
static void destroyWindow(HWND windowHandle);
static void initialiseWGL();
static HCURSOR loadPointer();
static void processWindowMessages();
static void registerWindowClass(const WNDCLASSEX& windowClassInfo);


// Implementation

class GraphicsDeviceManager::Implementation final
{
public:

	Implementation()
	{
		initialiseWindowClass();
		::initialiseWGL();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		::deregisterWindowClass();
	}

	GraphicsDevice* createDeviceObject(Window* window) const
	{
		GraphicsDeviceFactory graphicsDeviceFactory;
		GraphicsConfig graphicsConfig;
		GraphicsDevice* device = graphicsDeviceFactory.createDevice(window, graphicsConfig);
		// TODO: move loggingS to GraphicsDeviceFactory?
		logChosenGraphicsConfig(graphicsConfig);
		logGraphicsDeviceCreation(device);
		GraphicsDeviceFactory::logDeviceInfo(device);

		return device;
	}

	Window* createWindowObject(const Uint32 width, const Uint32 height) const
	{
		HWND windowHandle = ::createWindow(width, height);
		Window* window = DE_NEW(Window)(windowHandle);
		setWindowUserData(windowHandle, window->_implementation);

		return window;
	}

	void destroyWindow(Window* window) const
	{
		HWND windowHandle = static_cast<HWND>(window->handle());
		DE_DELETE(window, Window);
		::destroyWindow(windowHandle);
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	static void initialiseWindowClass()
	{
		const WNDCLASSEX windowClassInfo = createWindowClassInfo();
		::registerWindowClass(windowClassInfo);
	}

	static void setWindowUserData(HWND windowHandle, Window::Implementation* windowImplementation)
	{
		SetLastError(0u);

		const Int32 result =
			SetWindowLongPtrW(windowHandle, GWLP_USERDATA, reinterpret_cast<long>(windowImplementation));

		if(result == 0 && getWindowsErrorCode() != 0u)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the user data of a window." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}
	}

	static WNDCLASSEX createWindowClassInfo()
	{
		WNDCLASSEXW windowClassInfo = WNDCLASSEXW();
		windowClassInfo.cbSize = sizeof(WNDCLASSEXW);
		windowClassInfo.hCursor = ::loadPointer();
		windowClassInfo.hInstance = GetModuleHandleW(nullptr);
		windowClassInfo.lpfnWndProc = windowMessageHandler;
		windowClassInfo.lpszClassName = ::WINDOW_CLASS_NAME;
		windowClassInfo.style = CS_OWNDC;

		return windowClassInfo;
	}

	static Window::Implementation* getWindow(HWND windowHandle)
	{
		return reinterpret_cast<Window::Implementation*>(GetWindowLongPtrW(windowHandle, GWLP_USERDATA));
	}

	static LRESULT CALLBACK windowMessageHandler(HWND windowHandle, const Uint32 message, const WPARAM wParam,
		const LPARAM lParam)
	{
		switch(message)
		{
			case WM_CLOSE:
				getWindow(windowHandle)->close();
				break;

			case WM_SETCURSOR:
				if(getWindow(windowHandle)->shouldHidePointer(LOWORD(lParam) == HTCLIENT))
					return 1;

			default:
				return DefWindowProcW(windowHandle, message, wParam, lParam);
		}

		return 0;
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager(WindowCreatedHandler windowCreatedHandler)
	: _implementation(DE_NEW(Implementation)()),
	  _windowCreatedHandler(windowCreatedHandler) { }

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	destroyDevices();
	destroyWindows();
	DE_DELETE(_implementation, Implementation);
}

GraphicsDevice* GraphicsDeviceManager::createDevice(Window* window)
{
	GraphicsDevice* device = _implementation->createDeviceObject(window);
	_devices.push_back(device);

	return device;
}

void GraphicsDeviceManager::createWindow(const Uint32 windowWidth, const Uint32 windowHeight)
{
	Window* window = _implementation->createWindowObject(windowWidth, windowHeight);
	logWindowCreation();
	_windows.push_back(window);
	_windowCreatedHandler(window);
}

void GraphicsDeviceManager::destroyDevice(GraphicsDevice* device)
{
	DE_ASSERT(device != nullptr);
	GraphicsDeviceList::const_iterator iterator = std::find(_devices.begin(), _devices.end(), device);
	DE_ASSERT(iterator != _devices.end());
	_devices.erase(iterator);
	DE_DELETE(device, GraphicsDevice);
}

void GraphicsDeviceManager::destroyWindow(Window* window)
{
	DE_ASSERT(window != nullptr);
	WindowList::const_iterator iterator = std::find(_windows.begin(), _windows.end(), window);
	DE_ASSERT(iterator != _windows.end());
	_windows.erase(iterator);
	_implementation->destroyWindow(window);
}

void GraphicsDeviceManager::processWindowMessages() const
{
	::processWindowMessages();
}

// Private

void GraphicsDeviceManager::destroyWindows()
{
	for(WindowList::const_iterator i = _windows.begin(), end = _windows.end(); i != end; ++i)
		_implementation->destroyWindow(*i);
}


// External

static HWND createWindow(const Uint32 width, const Uint32 height)
{
	const Core::Rectangle rectangle = ::createWindowRectangle(width, height);

	HWND windowHandle =
		CreateWindowExW(0u, ::WINDOW_CLASS_NAME, ::WINDOW_DEFAULT_TITLE, ::WINDOW_STYLE, rectangle.x,
			rectangle.y, rectangle.width, rectangle.height, nullptr, nullptr, GetModuleHandleW(nullptr),
			nullptr);

	if(windowHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create a window." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return windowHandle;
}

static Core::Rectangle createWindowRectangle(const Uint32 width, const Uint32 height)
{
	const GraphicsAdapterManager& graphicsAdapterManager = GraphicsAdapterManager::instance();
	const DisplayMode& currentDisplayMode = graphicsAdapterManager.adapters()[0]->currentDisplayMode();

	RECT rectangle;
	rectangle.left = (currentDisplayMode.width() - width) / 2;
	rectangle.top = (currentDisplayMode.height() - height) / 2;
	rectangle.right = rectangle.left + width;
	rectangle.bottom = rectangle.top + height;

	const Int32 result = AdjustWindowRectEx(&rectangle, ::WINDOW_STYLE, FALSE, 0u);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create a window rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return createRectangle(rectangle);
}

static void deregisterWindowClass()
{
	const Int32 result = UnregisterClassW(::WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to deregister the window class." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

static void destroyWindow(HWND windowHandle)
{
	const Int32 result = DestroyWindow(windowHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to destroy a window." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

static void initialiseWGL()
{
	HWND temporaryWindowHandle = ::createWindow();

	{
		TemporaryGraphicsContext temporaryGraphicsContext(temporaryWindowHandle);
		WGL::initialise(temporaryGraphicsContext);
	}

	::destroyWindow(temporaryWindowHandle);
}

static HCURSOR loadPointer()
{
	HANDLE pointerHandle = LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);

	if(pointerHandle == nullptr)
		return nullptr;
	else
		return static_cast<HCURSOR>(pointerHandle);
}

static void processWindowMessages()
{
	MSG message;

	while(PeekMessageW(&message, nullptr, 0u, 0u, PM_REMOVE) != 0)
		DispatchMessageW(&message);
}

static void registerWindowClass(const WNDCLASSEX& windowClassInfo)
{
	const Uint32 result = RegisterClassExW(&windowClassInfo);

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to register the window class." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}
