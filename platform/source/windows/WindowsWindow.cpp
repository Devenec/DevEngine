/**
 * @file platform/windows/WindowsWindow.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/Window.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// External

static const Char8* WINDOW_CONTEXT = "[Platform::WindowsWindow]";


// Implementation

class Window::Impl
{
public:

	Impl(HWND handle)
		: _handle(handle),
		  _height(0u),
		  _width(0u),
		  _isFullscreen(false)
	{
		getSize(_width, _height);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	HWND handle() const
	{
		return _handle;
	}

	Bool processMessages() const
	{
		MSG message;

		while(PeekMessageW(&message, nullptr, 0u, 0u, PM_REMOVE) != FALSE)
		{
			if(message.message == WM_QUIT)
				return false;

			DispatchMessageW(&message);
		}

		return true;
	}

	// TODO: clean
	void setFullscreen(const Bool value)
	{
		if(value != _isFullscreen)
		{
			HMONITOR monitorHandle = MonitorFromWindow(_handle, MONITOR_DEFAULTTONEAREST);
			MONITORINFO monitorInfo;
			monitorInfo.cbSize = sizeof(monitorInfo);
			const Int32 result = GetMonitorInfoW(monitorHandle, &monitorInfo);

			if(result == 0)
			{
				defaultLog << LogLevel::Error << WINDOW_CONTEXT << "Failed to get the info of the window's monitor." <<
					Log::Flush();

				DE_ERROR(0); // TODO: set errorCode
			}

			setFullscreenStyle(value);

			if(value)
			{
				const Int32 windowWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
				const Int32 windowHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
				setRectangle(monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top, windowWidth, windowHeight);
			}
			else
			{
				const Int32 windowX = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left) / 2 - _width / 2;
				const Int32 windowY = (monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top) / 2 - _height / 2;
				setRectangle(windowX, windowY, _width, _height);
			}

			_isFullscreen = value;
		}
	}

	void setTitle(const String8& value) const
	{
		const String16 title = toString16(value);
		const Int32 result = SetWindowTextW(_handle, title.c_str());

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << "Failed to set the title of the window." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}

	void show() const
	{
		ShowWindow(_handle, SW_SHOWNORMAL);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	HWND _handle;
	Uint32 _height;
	Uint32 _width;
	Bool _isFullscreen;

	void getSize(Uint32& width, Uint32& height)
	{
		RECT rectangle;
		const Int32 result = GetWindowRect(_handle, &rectangle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << "Failed to get the rectangle of the window." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}

		width = rectangle.right - rectangle.left;
		height = rectangle.bottom - rectangle.top;
	}

	void setFullscreenStyle(const Bool isFullscreen)
	{
		const Int32 style = GetWindowLongPtrW(_handle, GWL_STYLE);
		Int32 newStyle = style;

		if(isFullscreen)
			newStyle &= ~WS_CAPTION;
		else
			newStyle |= WS_CAPTION;

		const Int32 result = SetWindowLongPtrW(_handle, GWL_STYLE, newStyle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << "Failed to set the style of the window." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}

	void setRectangle(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height)
	{
		const Int32 result = SetWindowPos(_handle, HWND_TOP, x, y, width, height,
			SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOZORDER);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << "Failed to set the rectangle of the window." <<
				Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
		}
	}
};


// Public

WindowHandle Window::handle() const
{
	return _impl->handle();
}

Bool Window::processMessages() const
{
	return _impl->processMessages();
}

void Window::setFullscreen(const Bool value) const
{
	_impl->setFullscreen(value);
}

void Window::setTitle(const String8& value) const
{
	_impl->setTitle(value);
}

void Window::show() const
{
	_impl->show();
}

// Private

Window::Window(WindowHandle windowHandle)
	: _impl(DE_NEW Impl(static_cast<HWND>(windowHandle))) { }

Window::~Window()
{
	DE_DELETE _impl;
}
