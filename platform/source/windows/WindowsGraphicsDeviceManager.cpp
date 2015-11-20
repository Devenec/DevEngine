/**
 * @file platform/windows/WindowsGraphicsDeviceManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
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

static const Char8* COMPONENT_TAG		  = "[Graphics::GraphicsManager - Windows]";
static const Char16* WINDOW_CLASS_NAME	  = DE_CHAR16("devengine");
static const Char16* WINDOW_DEFAULT_TITLE = DE_CHAR16("DevEngine Application");
static const Uint32 WINDOW_STYLE		  = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

static HWND createWindow(const Uint32 width = 640u, const Uint32 height = 480u);
static RECT createWindowRectangle(const Uint32 width, const Uint32 height);
static void deregisterWindowClass();
static void destroyWindow(HWND windowHandle);
static void initialiseWGL();
static HCURSOR loadCursor();
static void processMessages();
static void registerWindowClass(const WNDCLASSEX& windowClassInfo);


// Implementation

class GraphicsDeviceManager::Impl final
{
public:

	Impl()
	{
		initialiseWindowClass();
		::initialiseWGL();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		::deregisterWindowClass();
	}

	Window* createWindowObject(const Uint32 width, const Uint32 height)
	{
		HWND windowHandle = ::createWindow(width, height);
		Window* window = DE_NEW(Window)(windowHandle);
		setWindowUserDataPointer(windowHandle, window->_impl);

		return window;
	}

	void destroyWindowAndDevice(GraphicsDevice* device)
	{
		Window* window = device->window();
		DE_DELETE(device, GraphicsDevice);
		::destroyWindow(static_cast<HWND>(window->handle()));
		DE_DELETE(window, Window);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	void initialiseWindowClass()
	{
		const WNDCLASSEX windowClassInfo = createWindowClassInfo();
		::registerWindowClass(windowClassInfo);
	}

	void setWindowUserDataPointer(HWND windowHandle, Window::Impl* windowImpl)
	{
		SetLastError(0u);
		const Int32 result = SetWindowLongPtrW(windowHandle, GWLP_USERDATA, reinterpret_cast<long>(windowImpl));
	
		if(result == 0 && getWindowsErrorCode() != 0u)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to set the user data pointer of a window." <<
				Log::Flush();
	
			DE_ERROR_WINDOWS(0x0);
		}
	}

	static WNDCLASSEX createWindowClassInfo()
	{
		WNDCLASSEXW windowClassInfo = WNDCLASSEXW();
		windowClassInfo.cbSize = sizeof(WNDCLASSEXW);
		windowClassInfo.hCursor = ::loadCursor();
		windowClassInfo.hInstance = GetModuleHandleW(nullptr);
		windowClassInfo.lpfnWndProc = processMessage;
		windowClassInfo.lpszClassName = ::WINDOW_CLASS_NAME;
		windowClassInfo.style = CS_OWNDC;

		return windowClassInfo;
	}

	static LRESULT CALLBACK processMessage(HWND windowHandle, const Uint32 message, const WPARAM wParam,
		const LPARAM lParam)
	{
		Window::Impl* windowImpl = reinterpret_cast<Window::Impl*>(GetWindowLongPtrW(windowHandle, GWLP_USERDATA));

		switch(message)
		{
			case WM_CLOSE:
				windowImpl->close();
				break;

			case WM_SETCURSOR:
				if(windowImpl->shouldHideCursor(LOWORD(lParam) == HTCLIENT))
					return 1;

			default:
				return DefWindowProcW(windowHandle, message, wParam, lParam);
		}

		return 0;
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager()
	: _impl(DE_NEW(Impl)()) { }

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	for(GraphicsDeviceList::const_iterator i = _devices.begin(), end = _devices.end(); i != end; ++i)
		_impl->destroyWindowAndDevice(*i);

	DE_DELETE(_impl, Impl);
}

GraphicsDevice* GraphicsDeviceManager::createWindowAndDevice(const Uint32 windowWidth, const Uint32 windowHeight)
{
	Window* window = _impl->createWindowObject(windowWidth, windowHeight);
	GraphicsDeviceFactory graphicsDeviceFactory;
	GraphicsConfig graphicsConfig;
	GraphicsDevice* device = graphicsDeviceFactory.createDevice(window, graphicsConfig);
	logGraphicsDeviceConfiguration(graphicsConfig); // TODO: rename
	_devices.push_back(device);

	return device;
}

void GraphicsDeviceManager::destroyWindowAndDevice(GraphicsDevice* device)
{
	DE_ASSERT(device != nullptr);
	GraphicsDeviceList::const_iterator iterator = std::find(_devices.begin(), _devices.end(), device);
	DE_ASSERT(iterator != _devices.end());
	_devices.erase(iterator);
	_impl->destroyWindowAndDevice(device);
}

void GraphicsDeviceManager::processWindowMessages() const
{
	return ::processMessages();
}


// External

static HWND createWindow(const Uint32 width, const Uint32 height)
{
	const RECT windowRectangle = ::createWindowRectangle(width, height);
	const Int32 windowWidth = windowRectangle.right - windowRectangle.left;
	const Int32 windowHeight = windowRectangle.bottom - windowRectangle.top;

	HWND windowHandle = CreateWindowExW(0u, ::WINDOW_CLASS_NAME, ::WINDOW_DEFAULT_TITLE, ::WINDOW_STYLE,
		windowRectangle.left, windowRectangle.top, windowWidth, windowHeight, nullptr, nullptr,
		GetModuleHandleW(nullptr), nullptr);

	if(windowHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to create a window." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return windowHandle;
}

static RECT createWindowRectangle(const Uint32 width, const Uint32 height)
{
	const GraphicsAdapterManager& graphicsAdapterManager = GraphicsAdapterManager::instance();
	const DisplayMode& currentDisplayMode = graphicsAdapterManager.graphicsAdapters()[0]->currentDisplayMode();

	RECT rectangle;
	rectangle.left = currentDisplayMode.width() / 2 - width / 2;
	rectangle.top = currentDisplayMode.height() / 2 - height / 2;
	rectangle.right = rectangle.left + width;
	rectangle.bottom = rectangle.top + height;

	const Int32 result = AdjustWindowRectEx(&rectangle, ::WINDOW_STYLE, 0, 0u);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to create a window rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return rectangle;
}

static void deregisterWindowClass()
{
	const Int32 result = UnregisterClassW(::WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to deregister the window class." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

static void destroyWindow(HWND windowHandle)
{
	const Int32 result = DestroyWindow(windowHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to destroy a window." << Log::Flush();
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

static HCURSOR loadCursor()
{
	HANDLE cursorHandle = LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);

	if(cursorHandle == nullptr)
		return nullptr;
	else
		return static_cast<HCURSOR>(cursorHandle);
}

static void processMessages()
{
	MSG message;

	while(PeekMessageW(&message, nullptr, 0u, 0u, PM_REMOVE) != FALSE)
		DispatchMessageW(&message);
}

static void registerWindowClass(const WNDCLASSEX& windowClassInfo)
{
	const Uint32 result = RegisterClassExW(&windowClassInfo);

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to register the window class." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}
