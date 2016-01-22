/**
 * @file platform/x/XWindow.cpp
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

#include <core/Memory.h>
#include <core/Vector.h>
#include <graphics/Image.h>
#include <platform/x/XWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static Vector<Uint> createIconData(const Image* image);


// Implementation

// Public

Graphics::Window::Implementation::Implementation(WindowHandle windowHandle)
	: _hiddenPointerHandle(0u),
	  _windowHandle(reinterpret_cast<::Window>(windowHandle)),
	  _inFullscreen(false),
	  _isOpen(true)
{
	_hiddenPointerHandle = X::instance().createHiddenPointer(_windowHandle);
}

Graphics::Window::Implementation::~Implementation()
{
	setPointerVisibility(true);
	X::instance().destroyPointer(_hiddenPointerHandle);
}

void Graphics::Window::Implementation::setFullscreen(const Bool inFullscreen)
{
	if(inFullscreen != _inFullscreen)
	{
		X::instance().setWindowFullscreen(_windowHandle, inFullscreen);
		_inFullscreen = inFullscreen;
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
		const Vector<Uint> iconData = ::createIconData(image);

		X::instance().setWindowProperty(_windowHandle, iconPropertyName, "CARDINAL",
			reinterpret_cast<const Uint8*>(iconData.data()), 32u, static_cast<Uint32>(iconData.size()));
	}
}

void Graphics::Window::Implementation::setTitle(const String8& title) const
{
	X::instance().setWindowTitle(_windowHandle, title.c_str());
}


// Graphics::Window

// Public

Rectangle Graphics::Window::clientRectangle() const
{
	return _implementation->clientRectangle();
}

WindowHandle Graphics::Window::handle() const
{
	return _implementation->handle();
}

void Graphics::Window::hide() const
{
	_implementation->hide();
}

Bool Graphics::Window::isOpen() const
{
	return _implementation->isOpen();
}

void Graphics::Window::setClientRectangle(const Rectangle& rectangle) const
{
	if(!_implementation->inFullscreen())
		_implementation->setClientRectangle(rectangle);
}

void Graphics::Window::setFullscreen(const Bool inFullscreen) const
{
	_implementation->setFullscreen(inFullscreen);
}

void Graphics::Window::setIcon(const Image* image) const
{
	_implementation->setIcon(image);
}

void Graphics::Window::setPointerVisibility(const Bool isPointerVisible) const
{
	_implementation->setPointerVisibility(isPointerVisible);
}

void Graphics::Window::setTitle(const String8& title) const
{
	_implementation->setTitle(title);
}

void Graphics::Window::show() const
{
	_implementation->show();
}

// Private

Graphics::Window::Window(WindowHandle windowHandle)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(windowHandle);
}

Graphics::Window::~Window()
{
	DE_DELETE(_implementation, Implementation);
}


// External

static Vector<Uint> createIconData(const Image* image)
{
	const Uint32 elementCount = image->width() * image->height();
	const ByteData& imageData = image->data();
	Vector<Uint> iconData(elementCount + 2u);
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
