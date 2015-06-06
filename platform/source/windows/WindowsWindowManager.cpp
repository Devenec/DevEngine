/**
 * @file platform/windows/WindowsWindowManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/WindowManager.h>

#define OEMRESOURCE
#include <platform/windows/Windows.h>
#undef OEMRESOURCE

using namespace Core;
using namespace Graphics;

// External

static const Char16* WINDOW_CLASS_NAME	  = DE_CHAR16("devengine");
static const Char16* WINDOW_DEFAULT_TITLE = DE_CHAR16("DevEngine");
static const Uint32 WINDOW_DEFAULT_WIDTH  = 800u;
static const Uint32 WINDOW_DEFAULT_HEIGHT = 600u;
static const Uint32 WINDOW_STYLE		  = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

static const Char8* WINDOW_MANAGER_CONTEXT = "[Platform::WindowsWindowManager]";


// Implementation

class WindowManager::Impl
{
public:

	Impl()
		: _isCursorVisible(true)
	{
		WNDCLASSEXW windowClass;
		windowClass.cbClsExtra = 0;
		windowClass.cbSize = sizeof(windowClass);
		windowClass.cbWndExtra = 0;
		windowClass.hbrBackground = nullptr;
		windowClass.hCursor = loadCursor();
		windowClass.hIcon = nullptr; // TODO: set icon
		windowClass.hIconSm = nullptr; // TODO: set icon
		windowClass.hInstance = GetModuleHandleW(nullptr);
		windowClass.lpfnWndProc = processMessage;
		windowClass.lpszClassName = WINDOW_CLASS_NAME;
		windowClass.lpszMenuName = nullptr;
		windowClass.style = CS_OWNDC;

		registerWindowClass(windowClass);

		//SetCursor(nullptr);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		const Int32 result = UnregisterClassW(WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));
		
		if(result == 0u)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT << "Failed to deregister the window class." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}

	HWND createWindow() const
	{
		const RECT windowRectangle = createWindowRectangle();
		const Int32 windowWidth = windowRectangle.right - windowRectangle.left;
		const Int32 windowHeight = windowRectangle.bottom - windowRectangle.top;
		
		HWND windowHandle = CreateWindowExW(0u, WINDOW_CLASS_NAME, WINDOW_DEFAULT_TITLE, WINDOW_STYLE,
			windowRectangle.left, windowRectangle.top, windowWidth, windowHeight, nullptr, nullptr,
			GetModuleHandleW(nullptr), nullptr);

		if(windowHandle == nullptr)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT << "Failed to create a window." << Log::Flush();
			DE_ERROR(0); // TODO: set errorCode
		}

		setUserDataPointer(windowHandle);
		return windowHandle;
	}

	void destroyWindow(HWND windowHandle) const
	{
		const Int32 result = DestroyWindow(windowHandle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT << "Failed to destroy a window." << Log::Flush();
			DE_ERROR(0); // TODO: set errorCode
		}
	}

	void setCursorVisibility(const Bool value)
	{
		_isCursorVisible = value;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	Bool _isCursorVisible;

	HCURSOR loadCursor() const
	{
		HANDLE cursorHandle = LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);

		if(cursorHandle == nullptr)
			return nullptr;
		else
			return static_cast<HCURSOR>(cursorHandle);
	}

	void registerWindowClass(const WNDCLASSEX& windowClassInfo) const
	{
		const Uint32 result = RegisterClassExW(&windowClassInfo);

		if(result == 0u)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT << "Failed to register the window class." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}

	RECT createWindowRectangle() const
	{
		DE_ASSERT(GraphicsAdapterManager::hasInstance());
		const GraphicsAdapterManager& graphicsAdapterManager = GraphicsAdapterManager::instance();
		const DisplayMode& currentDisplayMode = graphicsAdapterManager.graphicsAdapters()[0]->currentDisplayMode();

		RECT rectangle;
		rectangle.left = currentDisplayMode.width() / 2 - WINDOW_DEFAULT_WIDTH / 2;
		rectangle.top = currentDisplayMode.height() / 2 - WINDOW_DEFAULT_HEIGHT / 2;
		rectangle.right = rectangle.left + WINDOW_DEFAULT_WIDTH;
		rectangle.bottom = rectangle.top + WINDOW_DEFAULT_HEIGHT;

		const Int32 result = AdjustWindowRectEx(&rectangle, WINDOW_STYLE, 0, 0u);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT << "Failed to create a rectangle for a window." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}

		return rectangle;
	}

	void setUserDataPointer(HWND windowHandle) const
	{
		SetLastError(0u);
		const Int32 result = SetWindowLongPtrW(windowHandle, GWLP_USERDATA, reinterpret_cast<long>(this));

		if(result == 0 && GetLastError() != 0u)
		{
			defaultLog << LogLevel::Error << WINDOW_MANAGER_CONTEXT <<
				"Failed to set the user data pointer of a window." << Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}

	Bool hideCursor(const Bool isCursorInClientArea) const
	{
		if(!_isCursorVisible && isCursorInClientArea)
		{
			SetCursor(nullptr);
			return true;
		}

		return false;
	}

	static LRESULT CALLBACK processMessage(HWND windowHandle, Uint32 message, WPARAM wParam, LPARAM lParam)
	{
		Impl* impl = reinterpret_cast<Impl*>(GetWindowLongPtrW(windowHandle, GWLP_USERDATA));

		switch(message)
		{
			case WM_CLOSE:
				PostQuitMessage(0);
				break;

			case WM_SETCURSOR:
				if(impl->hideCursor(LOWORD(lParam) == HTCLIENT))
					return 1;

			default:
				return DefWindowProcW(windowHandle, message, wParam, lParam);
		}
		
		return 0;
	}
};


// Public

WindowManager::WindowManager()
	: _impl(nullptr),
	  _window(nullptr) { }

Window* WindowManager::createWindow()
{
	if(_window == nullptr)
	{
		HWND windowHandle = _impl->createWindow();
		_window = DE_NEW Window(windowHandle);
	}

	return _window;
}

void WindowManager::deinitialise()
{
	if(_window != nullptr)
		destroyWindow();
	
	DE_DELETE _impl;
}

void WindowManager::initialise()
{
	_impl = DE_NEW Impl();
}

void WindowManager::setCursorVisibility(const Bool value)
{
	_impl->setCursorVisibility(value);
}

// Private

void WindowManager::destroyWindow()
{
	_impl->destroyWindow(static_cast<HWND>(_window->handle()));
	DE_DELETE _window;
	_window = nullptr;
}
