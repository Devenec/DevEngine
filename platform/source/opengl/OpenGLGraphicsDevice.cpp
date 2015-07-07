/**
 * @file platform/opengl/OpenGLGraphicsDevice.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Memory.h>
#include <core/Rectangle.h>
#include <graphics/Colour.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/Viewport.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLInterface.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsDevice::Impl final
{
public:

	Impl()
	{
		OpenGL::initialise();
		OpenGL::getIntegerv(GL_VIEWPORT, reinterpret_cast<Int32*>(&_viewport));
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	void clear(const Colour& colour) const
	{
		OpenGL::clearColor(colour.red, colour.green, colour.blue, colour.alpha);
		OpenGL::clear(GL_COLOR_BUFFER_BIT);
		DE_CHECK_ERROR_OPENGL();
	}

	void setViewport(const Viewport& viewport)
	{
		_viewport = viewport;
		const Rectangle& bounds = viewport.bounds();
		OpenGL::viewport(bounds.x, bounds.y, bounds.width, bounds.height);
	}

	const Viewport& viewport() const
	{
		return _viewport;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	Viewport _viewport;
};


// Public

GraphicsDevice::GraphicsDevice()
	: _impl(DE_NEW(Impl)()) { }

GraphicsDevice::~GraphicsDevice()
{
	DE_DELETE(_impl, Impl);
}

void GraphicsDevice::clear(const Colour& colour) const
{
	_impl->clear(colour);
}

void GraphicsDevice::setViewport(const Viewport& viewport)
{
	_impl->setViewport(viewport);
}

const Viewport& GraphicsDevice::viewport() const
{
	return _impl->viewport();
}
