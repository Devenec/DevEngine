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
#include <core/debug/Assert.h>
#include <graphics/Colour.h>
#include <graphics/Effect.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsResource.h>
#include <graphics/IndexBuffer.h>
#include <graphics/VertexBufferState.h>
#include <graphics/Viewport.h>
#include <platform/opengl/OpenGL.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsDevice::Impl final
{
public:

	Impl()
		: _activeEffect(nullptr),
		  _activeVertexBufferState(nullptr)
	{
		OpenGL::getIntegerv(OpenGL::VIEWPORT, reinterpret_cast<Int32*>(&_viewport));
		DE_CHECK_ERROR_OPENGL();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	void clear(const Colour& colour) const
	{
		OpenGL::clearColor(colour.red, colour.green, colour.blue, colour.alpha);
		OpenGL::clear(OpenGL::COLOR_BUFFER_BIT);
		DE_CHECK_ERROR_OPENGL();
	}

	void draw(const PrimitiveType& primitiveType, const Uint32 vertexCount, const Uint32 vertexOffset) const
	{
		initialiseDrawing();
		OpenGL::drawArrays(static_cast<Uint32>(primitiveType), vertexOffset, vertexCount);
		DE_CHECK_ERROR_OPENGL();
		deinitialiseDrawing();
	}

	void drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount, const Uint32 indexOffset) const
	{
		initialiseDrawing();
		IndexBuffer* indexBuffer = _activeVertexBufferState->indexBuffer();
		DE_ASSERT(indexBuffer != nullptr);
		const Uint32 indexTypeId = static_cast<Uint32>(indexBuffer->indexType());
		const Uint32 byteOffset = indexOffset * ((indexTypeId & 0x03) + 1u);

		OpenGL::drawElements(static_cast<Uint32>(primitiveType), indexCount, indexTypeId >> 2,
			reinterpret_cast<Void*>(byteOffset));

		DE_CHECK_ERROR_OPENGL();
		deinitialiseDrawing();
	}

	void setEffect(Effect* effect)
	{
		_activeEffect = effect;
	}

	void setVertexBufferState(VertexBufferState* vertexBufferState)
	{
		_activeVertexBufferState = vertexBufferState;
	}

	void setViewport(const Viewport& viewport)
	{
		_viewport = viewport;
		const Rectangle& bounds = viewport.bounds();
		OpenGL::viewport(bounds.x, bounds.y, bounds.width, bounds.height);
		DE_CHECK_ERROR_OPENGL();
	}

	const Viewport& viewport() const
	{
		return _viewport;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	Viewport _viewport;
	Effect* _activeEffect;
	VertexBufferState* _activeVertexBufferState;

	void initialiseDrawing() const
	{
		DE_ASSERT(_activeEffect != nullptr);
		DE_ASSERT(_activeVertexBufferState != nullptr);
		_activeEffect->apply();
		_activeVertexBufferState->apply();
	}

	void deinitialiseDrawing() const
	{
		_activeVertexBufferState->deapply();
		_activeEffect->deapply();
	}
};


// Graphics::GraphicsDevice

// Public

GraphicsDevice::GraphicsDevice()
	: _impl(DE_NEW(Impl)()) { }

GraphicsDevice::~GraphicsDevice()
{
	destroyResources();
	DE_DELETE(_impl, Impl);
}

void GraphicsDevice::clear(const Colour& colour) const
{
	_impl->clear(colour);
}

void GraphicsDevice::draw(const PrimitiveType& primitiveType, const Uint32 vertexCount,
	const Uint32 vertexOffset) const
{
	_impl->draw(primitiveType, vertexCount, vertexOffset);
}

void GraphicsDevice::drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount,
	const Uint32 indexOffset) const
{
	_impl->drawIndexed(primitiveType, indexCount, indexOffset);
}

void GraphicsDevice::setEffect(Effect* effect) const
{
	_impl->setEffect(effect);
}

void GraphicsDevice::setVertexBufferState(VertexBufferState* vertexBufferState) const
{
	_impl->setVertexBufferState(vertexBufferState);
}

void GraphicsDevice::setViewport(const Viewport& viewport) const
{
	_impl->setViewport(viewport);
}

const Viewport& GraphicsDevice::viewport() const
{
	return _impl->viewport();
}
