/**
 * @file platform/windows/WindowsWindow.cpp
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
#include <graphics/Image.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::Window - Windows] ";


// Implementation

// Public

Window::Implementation::Implementation(WindowHandle windowHandle)
	: _windowHandle(static_cast<HWND>(windowHandle)),
	  _inFullscreen(false),
	  _isOpen(true),
	  _isPointerVisible(true) { }

Core::Rectangle Window::Implementation::clientRectangle() const
{
	RECT clientRectangle;
	Int32 result = GetClientRect(_windowHandle, &clientRectangle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			"Failed to get the client rectangle of the window." << Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	POINT clientPosition = POINT();
	result = MapWindowPoints(_windowHandle, HWND_DESKTOP, &clientPosition, 1u);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the position of the window." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return Core::Rectangle(clientPosition.x, clientPosition.y, clientRectangle.right, clientRectangle.bottom);
}

void Window::Implementation::hide() const
{
	ShowWindow(_windowHandle, SW_HIDE);
}

void Window::Implementation::setClientRectangle(const Core::Rectangle& rectangle) const
{
	const Core::Rectangle windowRectangle = calculateWindowRectangle(rectangle);

	const Int32 result =
		MoveWindow(_windowHandle, windowRectangle.x, windowRectangle.y, windowRectangle.width,
			windowRectangle.height, FALSE);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the window rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

void Window::Implementation::setFullscreen(const Bool inFullscreen)
{
	if(inFullscreen != _inFullscreen)
	{
		setStyle(inFullscreen);
		setFullscreenClientRectangle(inFullscreen);
		_inFullscreen = inFullscreen;
	}
}

void Window::Implementation::setIcon(const Image* image)
{
	if(image == nullptr)
		_icon = Icon();
	else
		_icon = Icon(image);

	SendMessageW(_windowHandle, WM_SETICON, ICON_BIG, reinterpret_cast<long>(_icon.handle()));
}

void Window::Implementation::setTitle(const String8& title) const
{
	const String16 title16 = toString16(title);
	const Int32 result = SetWindowTextW(_windowHandle, title16.c_str());

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the window title." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

Bool Window::Implementation::shouldHidePointer(const Bool isPointerInClientArea) const
{
	if(!_isPointerVisible && isPointerInClientArea)
	{
		SetCursor(nullptr);
		return true;
	}

	return false;
}

void Window::Implementation::show() const
{
	ShowWindow(_windowHandle, SW_SHOW);
}

// Private

Core::Rectangle Window::Implementation::calculateWindowRectangle(const Core::Rectangle& clientRectangle) const
{
	RECT windowRectangle;
	windowRectangle.left = clientRectangle.x;
	windowRectangle.top = clientRectangle.y;
	windowRectangle.right = windowRectangle.left + clientRectangle.width;
	windowRectangle.bottom = windowRectangle.top + clientRectangle.height;
	const Int32 style = GetWindowLongPtrW(_windowHandle, GWL_STYLE);
	const Int32 result = AdjustWindowRectEx(&windowRectangle, style, FALSE, 0u);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to calculate the window rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return createRectangle(windowRectangle);
}

void Window::Implementation::setFullscreenClientRectangle(const Bool inFullscreen)
{
	Core::Rectangle windowRectangle;

	if(inFullscreen)
	{
		_windowedClientRectangle = clientRectangle();
		windowRectangle = getFullscreenRectangle();
	}
	else
	{
		windowRectangle = _windowedClientRectangle;
	}

	const Int32 result =
		SetWindowPos(_windowHandle, HWND_TOP, windowRectangle.x, windowRectangle.y, windowRectangle.width,
			windowRectangle.height, SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOZORDER);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the window rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

void Window::Implementation::setStyle(const Bool inFullscreen) const
{
	Int32 style = GetWindowLongPtrW(_windowHandle, GWL_STYLE);

	if(inFullscreen)
		style &= ~WS_CAPTION;
	else
		style |= WS_CAPTION;

	const Int32 result = SetWindowLongPtrW(_windowHandle, GWL_STYLE, style);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the window style." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

Core::Rectangle Window::Implementation::getFullscreenRectangle() const
{
	HMONITOR monitorHandle = MonitorFromWindow(_windowHandle, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFO);
	const Int32 result = GetMonitorInfoW(monitorHandle, &monitorInfo);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get a fullscreen rectangle." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return createRectangle(monitorInfo.rcMonitor);
}


// Graphics::Window

// Public

Core::Rectangle Window::clientRectangle() const
{
	return _implementation->clientRectangle();
}

WindowHandle Window::handle() const
{
	return _implementation->handle();
}

void Window::hide() const
{
	_implementation->hide();
}

Bool Window::isOpen() const
{
	return _implementation->isOpen();
}

void Window::setClientRectangle(const Core::Rectangle& rectangle) const
{
	if(!_implementation->inFullscreen())
		_implementation->setClientRectangle(rectangle);
}

void Window::setFullscreen(const Bool inFullscreen) const
{
	_implementation->setFullscreen(inFullscreen);
}

void Window::setIcon(const Image* image) const
{
	_implementation->setIcon(image);
}

void Window::setPointerVisibility(const Bool isPointerVisible) const
{
	_implementation->setPointerVisibility(isPointerVisible);
}

void Window::setTitle(const String8& title) const
{
	_implementation->setTitle(title);
}

void Window::show() const
{
	_implementation->show();
}

// Private

Window::Window(WindowHandle windowHandle)
	: _implementation(DE_NEW(Implementation)(windowHandle)) { }

Window::~Window()
{
	DE_DELETE(_implementation, Implementation);
}
