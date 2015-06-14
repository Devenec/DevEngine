/**
 * @file platform/windows/WindowsWindow.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Log.h>
#include <core/Memory.h>
#include <core/Rectangle.h>
#include <graphics/Image.h>
#include <graphics/Window.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsIcon.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

static const Char8* WINDOW_CONTEXT = "[Platform::WindowsWindow]";

// Implementation

class Window::Impl final
{
public:

	Impl(HWND handle)
		: _handle(handle),
		  _isFullscreen(false)
	{
		_rectangle = getRectangle();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() { }

	HWND handle() const
	{
		return _handle;
	}

	Bool isFullscreen() const
	{
		return _isFullscreen;
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

	Core::Rectangle rectangle() const
	{
		if(_isFullscreen)
			return getRectangle();
		else
			return _rectangle;
	}

	void setFullscreen(const Bool value)
	{
		if(value != _isFullscreen)
		{
			setFullscreenStyle(value);

			if(value)
				setRectangle(getFullscreenRectangle(), value);
			else
				setRectangle(_rectangle);

			_isFullscreen = value;
		}
	}

	void setIcon(const Image* value)
	{
		_icon.deinitialise();
		
		if(value != nullptr)
		{
			_icon.initialise(value);
			SendMessageW(_handle, WM_SETICON, ICON_BIG, reinterpret_cast<long>(_icon.handle()));
		}
	}
	
	void setRectangle(const Core::Rectangle& value, const Bool isFullscreenRectangle = false)
	{
		const Int32 result = SetWindowPos(_handle, HWND_TOP, value.x, value.y, value.width, value.height,
			SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOZORDER);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << " Failed to set the rectangle of the window." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x000300);
		}
			
		if(!isFullscreenRectangle)
			_rectangle = value;
	}

	void setTitle(const String8& value) const
	{
		const String16 title = toString16(value);
		const Int32 result = SetWindowTextW(_handle, title.c_str());

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << " Failed to set the title of the window." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x000301);
		}
	}

	void show() const
	{
		ShowWindow(_handle, SW_SHOWNORMAL);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:
	
	Core::Rectangle _rectangle;
	HWND _handle;
	Icon _icon;
	Bool _isFullscreen;

	Core::Rectangle getRectangle() const
	{
		RECT rectangle;
		const Int32 result = GetWindowRect(_handle, &rectangle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << " Failed to get the rectangle of the window." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x000302);
		}

		return Core::Rectangle(rectangle.left, rectangle.top, rectangle.right - rectangle.left,
			rectangle.bottom - rectangle.top);
	}

	void setFullscreenStyle(const Bool isFullscreen) const
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
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << " Failed to set the style of the window." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x000303);
		}
	}

	Core::Rectangle getFullscreenRectangle() const
	{
		HMONITOR monitorHandle = MonitorFromWindow(_handle, MONITOR_DEFAULTTONEAREST);
		MONITORINFO monitorInfo;
		monitorInfo.cbSize = sizeof(monitorInfo);
		const Int32 result = GetMonitorInfoW(monitorHandle, &monitorInfo);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << WINDOW_CONTEXT << " Failed to get the info of the window's monitor." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x000304);
		}
		
		return Core::Rectangle(monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
			monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
			monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
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

Core::Rectangle Window::rectangle() const
{
	return _impl->rectangle();
}

void Window::setFullscreen(const Bool value) const
{
	_impl->setFullscreen(value);
}

void Window::setIcon(const Image* value) const
{
	_impl->setIcon(value);
}

void Window::setRectangle(const Core::Rectangle& value) const
{
	if(!_impl->isFullscreen())
		_impl->setRectangle(value);
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
	: _impl(DE_NEW(Impl)(static_cast<HWND>(windowHandle))) { }

Window::~Window()
{
	DE_DELETE(_impl, Impl);
}
