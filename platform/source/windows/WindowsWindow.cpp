/**
 * @file platform/windows/WindowsWindow.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/Image.h>
#include <platform/windows/WindowsWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

// Public

Window::Impl::Impl(HWND handle)
	: _windowHandle(handle),
	  _isCursorVisible(true),
	  _isFullscreen(false),
	  _isOpen(true)
{
	_rectangle = getRectangle();
}

void Window::Impl::setFullscreen(const Bool value)
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

void Window::Impl::setIcon(const Image* value)
{
	if(value == nullptr)
		_icon = Icon();
	else
		_icon = Icon(value);

	SendMessageW(_windowHandle, WM_SETICON, ICON_BIG, reinterpret_cast<long>(_icon.handle()));
}
	
void Window::Impl::setRectangle(const Core::Rectangle& value, const Bool isFullscreenRectangle)
{
	const Int32 result = SetWindowPos(_windowHandle, HWND_TOP, value.x, value.y, value.width, value.height,
		SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOZORDER);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to set the rectangle of the window." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x000300);
	}
			
	if(!isFullscreenRectangle)
		_rectangle = value;
}

void Window::Impl::setTitle(const String8& value) const
{
	const String16 title = toString16(value);
	const Int32 result = SetWindowTextW(_windowHandle, title.c_str());

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to set the title of the window." << Log::Flush();
		DE_ERROR_WINDOWS(0x000301);
	}
}

Bool Window::Impl::shouldHideCursor(const Bool isCursorInClientArea) const
{
	if(!_isCursorVisible && isCursorInClientArea)
	{
		SetCursor(nullptr);
		return true;
	}

	return false;
}

// Private

const Char8* Window::Impl::COMPONENT_TAG = "[Platform::Window - Windows]";

Core::Rectangle Window::Impl::getRectangle() const
{
	RECT rectangle;
	const Int32 result = GetWindowRect(_windowHandle, &rectangle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the rectangle of the window." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x000302);
	}

	return Core::Rectangle(rectangle.left, rectangle.top, rectangle.right - rectangle.left,
		rectangle.bottom - rectangle.top);
}

void Window::Impl::setFullscreenStyle(const Bool isFullscreen) const
{
	const Int32 style = GetWindowLongPtrW(_windowHandle, GWL_STYLE);
	Int32 newStyle = style;

	if(isFullscreen)
		newStyle &= ~WS_CAPTION;
	else
		newStyle |= WS_CAPTION;

	const Int32 result = SetWindowLongPtrW(_windowHandle, GWL_STYLE, newStyle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to set the style of the window." << Log::Flush();
		DE_ERROR_WINDOWS(0x000303);
	}
}

Core::Rectangle Window::Impl::getFullscreenRectangle() const
{
	HMONITOR monitorHandle = MonitorFromWindow(_windowHandle, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	const Int32 result = GetMonitorInfoW(monitorHandle, &monitorInfo);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the info of the window's monitor." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x000304);
	}
		
	return Core::Rectangle(monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top,
		monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
		monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
}


// Graphics::Window

// Public

WindowHandle Window::handle() const
{
	return _impl->handle();
}

void Window::hide() const
{
	_impl->hide();
}

Core::Rectangle Window::rectangle() const
{
	return _impl->rectangle();
}

void Window::setCursorVisibility(const Bool value) const
{
	_impl->setCursorVisibility(value);
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

Bool Window::shouldClose() const
{
	return _impl->shouldClose();
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
