/**
 * @file platform/x/XWindow.cpp
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

#include <core/Memory.h>
#include <core/Vector.h>
#include <graphics/Image.h>
#include <platform/x/XWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static Vector<Uint32> createIconData(const Image* image);


// Implementation

// Public

Graphics::Window::Implementation::Implementation(const ::Window windowHandle)
	: _rectangle(X::instance().getWindowRectangle(windowHandle)),
	  _hiddenPointerHandle(X::instance().createHiddenPointer(windowHandle)),
	  _windowHandle(windowHandle),
	  _isFullscreen(false),
	  _isOpen(true) { }

Graphics::Window::Implementation::~Implementation()
{
	setPointerVisibility(true);
	X::instance().destroyPointer(_hiddenPointerHandle);
}

Rectangle Graphics::Window::Implementation::rectangle() const
{
	if(_isFullscreen)
		return X::instance().getWindowRectangle(_windowHandle);
	else
		return _rectangle;
}

void Graphics::Window::Implementation::setFullscreen(const Bool isFullscreen)
{
	if(isFullscreen != _isFullscreen)
	{
		X::instance().setFullscreen(_windowHandle, isFullscreen);
		_isFullscreen = isFullscreen;
	}
}

void Graphics::Window::Implementation::setIcon(const Image* image)
{
	const Char8* iconPropertyName = "_NET_WM_ICON";

	if(image == nullptr)
	{
		X::instance().destroyWindowProperty(_windowHandle, iconPropertyName);
	}
	else
	{
		const Vector<Uint32> iconData = ::createIconData(image);

		X::instance().setWindowProperty(_windowHandle, iconPropertyName, "CARDINAL",
			reinterpret_cast<const Uint8*>(iconData.data()), 32u, iconData.size());
	}
}

void Graphics::Window::Implementation::setRectangle(const Rectangle& rectangle)
{
	X::instance().setWindowRectangle(_windowHandle, rectangle);

	if(!_isFullscreen)
		_rectangle = rectangle;
}

void Graphics::Window::Implementation::setTitle(const String8& title) const
{
	X::instance().setWindowTitle(_windowHandle, title.c_str());
}


// Graphics::Window

// Public

WindowHandle Graphics::Window::handle() const
{
	return reinterpret_cast<WindowHandle>(_implementation->handle());
}

void Graphics::Window::hide() const
{
	_implementation->hide();
}

Rectangle Graphics::Window::rectangle() const
{
	return _implementation->rectangle();
}

void Graphics::Window::setPointerVisibility(const Bool isPointerVisible) const
{
	_implementation->setPointerVisibility(isPointerVisible);
}

void Graphics::Window::setFullscreen(const Bool isFullscreen) const
{
	_implementation->setFullscreen(isFullscreen);
}

void Graphics::Window::setIcon(const Image* image) const
{
	_implementation->setIcon(image);
}

void Graphics::Window::setRectangle(const Rectangle& rectangle) const
{
	_implementation->setRectangle(rectangle);
}

void Graphics::Window::setTitle(const String8& title) const
{
	_implementation->setTitle(title);
}

Bool Graphics::Window::shouldClose() const
{
	return _implementation->shouldClose();
}

void Graphics::Window::show() const
{
	_implementation->show();
}

// Private

Graphics::Window::Window(WindowHandle windowHandle)
	: _implementation(DE_NEW(Implementation)(reinterpret_cast<::Window>(windowHandle))) { }

Graphics::Window::~Window()
{
	DE_DELETE(_implementation, Implementation);
}


// External

static Vector<Uint32> createIconData(const Image* image)
{
	const Uint32 elementCount = image->width() * image->height();
	const ByteData& imageData = image->data();
	Vector<Uint32> iconData(elementCount + 2u, 0u);
	iconData[0] = image->width();
	iconData[1] = image->height();

	for(Uint32 i = 0u; i < elementCount; ++i)
	{
		const Uint32 pixelIndex = 4u * i;

		iconData[i + 2] =
			static_cast<Uint32>(imageData[pixelIndex + 3]) << 24 |
			static_cast<Uint32>(imageData[pixelIndex])	   << 16 |
			static_cast<Uint32>(imageData[pixelIndex + 1]) << 8	 |
			static_cast<Uint32>(imageData[pixelIndex + 2]);
	}

	return iconData;
}
