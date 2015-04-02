/**
 * @file platform/windows/WindowsWindowManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Memory.h>
#include <core/String.h>
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsAdapter.h>
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

class WindowManager::Impl
{
public:

	Impl()
	{
		initialiseGraphicsAdapters();
		registerWindowClass();
	}

	~Impl()
	{
		unregisterWindowClass();
		deinitialiseGraphicsAdapters();
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

	using GraphicsAdapters = Core::Vector<GraphicsAdapter*>;

	GraphicsAdapters _graphicsAdapters;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	void initialiseGraphicsAdapters()
	{
		Int32 result = 1;
		DISPLAY_DEVICEW graphicsAdapterInfo;
		graphicsAdapterInfo.cb = sizeof(graphicsAdapterInfo);

		for(Uint32 i = 0u; result != 0; ++i)
		{
			result = EnumDisplayDevicesW(nullptr, i, &graphicsAdapterInfo, 0u);

			if(result != 0 && (graphicsAdapterInfo.StateFlags & DISPLAY_DEVICE_ACTIVE) != 0u)
			{
				Uint32 currentDisplayModeIndex;

				const DisplayModes displayModes = getGraphicsAdapterDisplayModes(graphicsAdapterInfo.DeviceName,
					currentDisplayModeIndex);

				GraphicsAdapter* graphicsAdapter = DE_NEW GraphicsAdapter(toString8(graphicsAdapterInfo.DeviceName),
					displayModes, currentDisplayModeIndex);

				if((graphicsAdapterInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0u)
					_graphicsAdapters.insert(_graphicsAdapters.begin(), graphicsAdapter);
				else
					_graphicsAdapters.push_back(graphicsAdapter);
			}
		}
	}

	void registerWindowClass() const
	{
		HANDLE cursorHandle = LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
		DE_ASSERT(cursorHandle != nullptr);

		WNDCLASSEXW windowClass;
		windowClass.cbClsExtra = 0;
		windowClass.cbSize = sizeof(windowClass);
		windowClass.cbWndExtra = 0;
		windowClass.hbrBackground = nullptr;
		windowClass.hCursor = static_cast<HCURSOR>(cursorHandle);
		windowClass.hIcon = nullptr; // TODO: set icon
		windowClass.hIconSm = nullptr; // TODO: set icon
		windowClass.hInstance = GetModuleHandleW(nullptr);
		windowClass.lpfnWndProc = processMessage;
		windowClass.lpszClassName = WINDOW_CLASS_NAME;
		windowClass.lpszMenuName = nullptr;
		windowClass.style = CS_OWNDC;

		const Uint32 result = RegisterClassExW(&windowClass);
		DE_ASSERT(result != 0u);
	}

	void unregisterWindowClass() const
	{
		const Int32 result = UnregisterClassW(WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));
		DE_ASSERT(result != 0);
	}

	void deinitialiseGraphicsAdapters() const
	{
		for(GraphicsAdapters::const_iterator i = _graphicsAdapters.begin(), end = _graphicsAdapters.end(); i != end; ++i)
			delete *i;
	}

	RECT createWindowRectangle() const
	{
		const DisplayMode& currentDisplayMode = _graphicsAdapters[0]->currentDisplayMode();
		RECT windowRectangle;
		windowRectangle.left = currentDisplayMode.width() / 2 - WINDOW_DEFAULT_WIDTH / 2;
		windowRectangle.top = currentDisplayMode.height() / 2 - WINDOW_DEFAULT_HEIGHT / 2;
		windowRectangle.right = WINDOW_DEFAULT_WIDTH;
		windowRectangle.bottom = WINDOW_DEFAULT_HEIGHT;

		const Int32 result = AdjustWindowRectEx(&windowRectangle, WINDOW_STYLE, 0, 0u);
		DE_ASSERT(result != 0);

		return windowRectangle;
	}

	DisplayModes getGraphicsAdapterDisplayModes(const Char16* adapterName, Uint32& currentModeIndex) const
	{
		DisplayMode displayMode(1u, 0u, 0u, 0u);
		DEVMODEW displayModeInfo;
		displayModeInfo.dmDriverExtra = 0u;
		displayModeInfo.dmSize = sizeof(displayModeInfo);
		DisplayModes displayModes;

		for(Uint32 i = 0; displayMode.width() != 0; ++i)
		{
			displayMode = getGraphicsAdapterDisplayMode(adapterName, i, displayModeInfo);

			if(displayMode.width() != 0u &&
				std::find(displayModes.begin(), displayModes.end(), displayMode) == displayModes.end())
			{
					displayModes.push_back(displayMode);
			}
		}

		displayModes.shrink_to_fit();
		std::sort(displayModes.begin(), displayModes.end());
		displayMode = getGraphicsAdapterDisplayMode(adapterName, ENUM_CURRENT_SETTINGS, displayModeInfo);
		DE_ASSERT(displayMode.width() != 0u);
		DisplayModes::const_iterator position = std::find(displayModes.begin(), displayModes.end(), displayMode);
		DE_ASSERT(position != displayModes.end());
		currentModeIndex = position - displayModes.begin();

		return displayModes;
	}

	DisplayMode getGraphicsAdapterDisplayMode(const Char16* adapterName, const Uint32 modeIndex, DEVMODEW& modeInfo)
		const
	{
		const Int32 result = EnumDisplaySettingsW(adapterName, modeIndex, &modeInfo);

		if(result == 0)
		{
			return DisplayMode();
		}
		else
		{
			return DisplayMode(modeInfo.dmPelsWidth, modeInfo.dmPelsHeight, modeInfo.dmBitsPerPel,
				modeInfo.dmDisplayFrequency);
		}
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

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
