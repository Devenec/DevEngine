/**
 * @file platform/windows/WindowsWindowManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Memory.h>
#include <core/String.h>
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>
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


// Implementation

//
#include <core/Log.h>
#include <core/LogManager.h>
//

class WindowManager::Impl
{
public:

	Impl()
	{
		//

		Log& log = LogManager::instance().log();

		Int32 res = 1;
		DISPLAY_DEVICEW displayDeviceInfo;
		displayDeviceInfo.cb = sizeof(displayDeviceInfo);
		String16 primaryDeviceName;

		for(Uint32 i = 0u; res != 0; ++i)
		{
			res = EnumDisplayDevicesW(nullptr, i, &displayDeviceInfo, 0u);

			if((displayDeviceInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0u)
				primaryDeviceName = displayDeviceInfo.DeviceName;

			Int32 res2;
			DEVMODEW displayMode;
			displayMode.dmDriverExtra = 0u;
			displayMode.dmSize = sizeof(displayMode);

			res2 = EnumDisplaySettingsW(displayDeviceInfo.DeviceName, ENUM_CURRENT_SETTINGS, &displayMode);

			if(res2 != 0 && (displayDeviceInfo.StateFlags & DISPLAY_DEVICE_ACTIVE) != 0u)
			{
				log << LogLevel::Debug << "Current display mode (" << displayDeviceInfo.DeviceName << "): " <<
					displayMode.dmPelsWidth << " x " << displayMode.dmPelsHeight << ", " << displayMode.dmBitsPerPel <<
					", " << displayMode.dmDisplayFrequency << Log::flush;
			}
			
			if(res != 0 && (displayDeviceInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0u)
			{
				Uint32 displayModeCount = 0u;
				res2 = 1;

				for(Uint32 j = 0u; res2 != 0; ++j)
				{
					res2 = EnumDisplaySettingsW(displayDeviceInfo.DeviceName, j, &displayMode);

					if(res2 != 0 && displayMode.dmBitsPerPel == 32u)
					{
						log << LogLevel::Debug << displayMode.dmPelsWidth << " x " << displayMode.dmPelsHeight <<
							", " << displayMode.dmBitsPerPel << ", " << displayMode.dmDisplayFrequency << Log::flush;

						++displayModeCount;
					}
				}

				log << "Total " << displayModeCount << " display modes" << Log::flush;
			}
		}

		res = 1;

		if(!primaryDeviceName.empty())
		{
			for(Uint32 i = 0u; res != 0; ++i)
			{
				res = EnumDisplayDevicesW(primaryDeviceName.c_str(), i, &displayDeviceInfo, 0u);
			}
		}

		//

		HANDLE cursorHandle = LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
		DE_ASSERT(cursorHandle != nullptr);

		WNDCLASSEXW windowClass;
		windowClass.cbClsExtra = 0;
		windowClass.cbSize = sizeof(windowClass);
		windowClass.cbWndExtra = 0;
		windowClass.hbrBackground = nullptr;
		windowClass.hCursor = static_cast<HCURSOR>(cursorHandle);
		windowClass.hIcon = nullptr; // TODO: set icon?
		windowClass.hIconSm = nullptr; // TODO: set icon?
		windowClass.hInstance = GetModuleHandleW(nullptr);
		windowClass.lpfnWndProc = processMessage;
		windowClass.lpszClassName = WINDOW_CLASS_NAME;
		windowClass.lpszMenuName = nullptr;
		windowClass.style = CS_OWNDC;

		const Uint32 result = RegisterClassExW(&windowClass);
		DE_ASSERT(result != 0u);
	}

	~Impl()
	{
		const Int32 result = UnregisterClassW(WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));
		DE_ASSERT(result != 0);
	}

	HWND createWindow() const
	{
		const RECT windowRectangle = createWindowRectangle();
		
		HWND windowHandle = CreateWindowExW(0u, WINDOW_CLASS_NAME, WINDOW_DEFAULT_TITLE, WINDOW_STYLE,
			windowRectangle.left, windowRectangle.top, windowRectangle.right, windowRectangle.bottom, nullptr, nullptr,
			GetModuleHandleW(nullptr), nullptr);

		DE_ASSERT(windowHandle != nullptr);
		return windowHandle;
	}

	void destroyWindow(HWND windowHandle) const
	{
		const Int32 result = DestroyWindow(windowHandle);
		DE_ASSERT(result != 0);
	}

private:

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	RECT createWindowRectangle() const
	{
		RECT windowRectangle;
		windowRectangle.left = 100; // TODO: adjust
		windowRectangle.top = 100; // TODO: adjust
		windowRectangle.right = WINDOW_DEFAULT_WIDTH;
		windowRectangle.bottom = WINDOW_DEFAULT_HEIGHT;

		const Int32 result = AdjustWindowRectEx(&windowRectangle, WINDOW_STYLE, 0, 0u);
		DE_ASSERT(result != 0);

		return windowRectangle;
	}

	Impl& operator =(const Impl& impl) = delete;

	static LRESULT CALLBACK processMessage(HWND windowHandle, Uint32 message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)
		{
			case WM_CLOSE:
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProcW(windowHandle, message, wParam, lParam);
		}
		
		return 0;
	}
};


// Public

WindowManager::WindowManager()
	: _impl(DE_NEW Impl()),
	  _window(nullptr) { }

WindowManager::~WindowManager()
{
	if(_window != nullptr)
		destroyWindow();
	
	DE_DELETE _impl;
}

Window* WindowManager::createWindow()
{
	if(_window == nullptr)
	{
		HWND windowHandle = _impl->createWindow();
		_window = DE_NEW Window(windowHandle);
	}

	return _window;
}

// Private

void WindowManager::destroyWindow()
{
	_impl->destroyWindow(static_cast<HWND>(_window->handle()));
	DE_DELETE _window;
	_window = nullptr;
}
