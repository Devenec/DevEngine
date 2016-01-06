/**
 * @file platform/opengl/OpenGLGraphicsDevice.cpp
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
#include <core/Rectangle.h>
#include <core/debug/Assert.h>
#include <graphics/Colour.h>
#include <graphics/Effect.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Shader.h>
#include <graphics/VertexBufferState.h>
#include <graphics/Viewport.h>
#include <platform/GraphicsContext.h>
#include <platform/opengl/OpenGL.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsDevice::Implementation final
{
public:

	Implementation(GraphicsContext* graphicsContext)
		: _activeEffect(nullptr),
		  _activeVertexBufferState(nullptr),
		  _graphicsContext(graphicsContext),
		  _openGL(nullptr)
	{
		initialiseOpenGL();
		initialiseViewport();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		DE_DELETE(_openGL, OpenGL);
		DE_DELETE(_graphicsContext, GraphicsContext);
	}

	void clear(const Colour& colour) const
	{
		_openGL->clearColor(colour.red, colour.green, colour.blue, colour.alpha);
		_openGL->clear(OpenGL::COLOR_BUFFER_BIT);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	GraphicsBuffer* createBuffer(const BufferBinding& binding, const Uint32 size,
		const AccessMode& accessMode) const
	{
		return DE_NEW(GraphicsBuffer)(_openGL, binding, size, accessMode);
	}

	Effect* createEffect() const
	{
		return DE_NEW(Effect)(_openGL);
	}

	IndexBuffer* createIndexBuffer(const Uint32 size, const IndexType& indexType,
		const AccessMode& accessMode) const
	{
		return DE_NEW(IndexBuffer)(_openGL, size, indexType, accessMode);
	}

	Shader* createShader(const ShaderType& type, const String8& source) const
	{
		return DE_NEW(Shader)(_openGL, type, source);
	}

	VertexBufferState* createVertexBufferState() const
	{
		return DE_NEW(VertexBufferState)(_openGL);
	}

	void draw(const PrimitiveType& primitiveType, const Uint32 vertexCount, const Uint32 vertexOffset) const
	{
		initialiseDrawing();
		_openGL->drawArrays(static_cast<Uint32>(primitiveType), vertexOffset, vertexCount);
		DE_CHECK_ERROR_OPENGL(_openGL);
		deinitialiseDrawing();
	}

	void drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount, const Uint32 indexOffset)
		const
	{
		initialiseDrawing();
		IndexBuffer* indexBuffer = _activeVertexBufferState->indexBuffer();
		DE_ASSERT(indexBuffer != nullptr);
		const Uint32 indexTypeId = static_cast<Uint32>(indexBuffer->indexType());
		const Uint32 byteOffset = indexOffset * ((indexTypeId & 0x03) + 1u);

		_openGL->drawElements(static_cast<Uint32>(primitiveType), indexCount, indexTypeId >> 2,
			reinterpret_cast<Void*>(byteOffset));

		DE_CHECK_ERROR_OPENGL(_openGL);
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
		_openGL->viewport(bounds.x, bounds.y, bounds.width, bounds.height);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void swapBuffers() const
	{
		_graphicsContext->swapBuffers();
	}

	const Viewport& viewport() const
	{
		return _viewport;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	Viewport _viewport;
	Effect* _activeEffect;
	VertexBufferState* _activeVertexBufferState;
	GraphicsContext* _graphicsContext;
	OpenGL* _openGL;

	void initialiseOpenGL()
	{
		_graphicsContext->makeCurrent();
		_openGL = DE_NEW(OpenGL)();
	}

	void initialiseViewport()
	{
		Int32 viewportValues[4];
		_openGL->getIntegerv(OpenGL::VIEWPORT, viewportValues);
		DE_CHECK_ERROR_OPENGL(_openGL);

		_viewport.setBounds(Rectangle(viewportValues[0], viewportValues[1], viewportValues[2],
			viewportValues[3]));
	}

	void initialiseDrawing() const
	{
		DE_ASSERT(_activeEffect != nullptr);
		DE_ASSERT(_activeVertexBufferState != nullptr);
		_activeEffect->use();
		_activeVertexBufferState->bind();
	}

	void deinitialiseDrawing() const
	{
		_activeVertexBufferState->debind();
		_activeEffect->disuse();
	}
};


// Graphics::GraphicsDevice

// Public

void GraphicsDevice::clear(const Colour& colour) const
{
	_implementation->clear(colour);
}

GraphicsBuffer* GraphicsDevice::createBuffer(const BufferBinding& binding, const Uint32 size,
	const AccessMode& accessMode)
{
	GraphicsBuffer* buffer = _implementation->createBuffer(binding, size, accessMode);
	_resources.push_back(buffer);

	return buffer;
}

Effect* GraphicsDevice::createEffect()
{
	Effect* effect = _implementation->createEffect();
	_resources.push_back(effect);

	return effect;
}

IndexBuffer* GraphicsDevice::createIndexBuffer(const Uint32 size, const IndexType& indexType,
	const AccessMode& accessMode)
{
	IndexBuffer* indexBuffer = _implementation->createIndexBuffer(size, indexType, accessMode);
	_resources.push_back(indexBuffer);

	return indexBuffer;
}

Shader* GraphicsDevice::createShader(const ShaderType& type, const String8& source)
{
	Shader* shader = _implementation->createShader(type, source);
	_resources.push_back(shader);

	return shader;
}

VertexBufferState* GraphicsDevice::createVertexBufferState()
{
	VertexBufferState* vertexBufferState = _implementation->createVertexBufferState();
	_resources.push_back(vertexBufferState);

	return vertexBufferState;
}

void GraphicsDevice::draw(const PrimitiveType& primitiveType, const Uint32 vertexCount,
	const Uint32 vertexOffset) const
{
	_implementation->draw(primitiveType, vertexCount, vertexOffset);
}

void GraphicsDevice::drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount,
	const Uint32 indexOffset) const
{
	_implementation->drawIndexed(primitiveType, indexCount, indexOffset);
}

void GraphicsDevice::setEffect(Effect* effect) const
{
	_implementation->setEffect(effect);
}

void GraphicsDevice::setVertexBufferState(VertexBufferState* vertexBufferState) const
{
	_implementation->setVertexBufferState(vertexBufferState);
}

void GraphicsDevice::setViewport(const Viewport& viewport) const
{
	_implementation->setViewport(viewport);
}

const Viewport& GraphicsDevice::viewport() const
{
	return _implementation->viewport();
}

void GraphicsDevice::swapBuffers() const
{
	_implementation->swapBuffers();
}

// Private

GraphicsDevice::GraphicsDevice(GraphicsContext* graphicsContext)
	: _implementation(DE_NEW(Implementation)(graphicsContext)) { }

GraphicsDevice::~GraphicsDevice()
{
	destroyResources();
	DE_DELETE(_implementation, Implementation);
}
