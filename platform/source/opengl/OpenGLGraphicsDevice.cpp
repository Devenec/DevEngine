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
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsResource.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Shader.h>
#include <graphics/VertexBufferState.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>
#include <platform/opengl/OpenGLGraphicsDevice.h>
#include <platform/opengl/OpenGLShader.h>
#include <platform/wgl/WGLGraphicsContext.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

// Public

GraphicsDevice::Impl::Impl(GraphicsContext* graphicsContext)
	: _activeEffect(nullptr),
	  _graphicsContext(graphicsContext),
	  _activeVertexBufferState(nullptr),
	  _openGL(nullptr)
{
	initialiseOpenGL();
	initialiseViewport();
}

GraphicsDevice::Impl::~Impl()
{
	DE_DELETE(_openGL, OpenGL);
	_graphicsContext->makeNonCurrent();
	DE_DELETE(_graphicsContext, GraphicsContext);
}

void GraphicsDevice::Impl::clear(const Colour& colour) const
{
	_openGL->clearColor(colour.red, colour.green, colour.blue, colour.alpha);
	_openGL->clear(OpenGL::COLOR_BUFFER_BIT);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

GraphicsBuffer* GraphicsDevice::Impl::createBuffer(const Uint32 binding, const Uint32 size,
	const AccessMode& accessMode) const
{
	return DE_NEW(GraphicsBuffer)(_openGL, binding, size, accessMode);
}

Effect* GraphicsDevice::Impl::createEffect() const
{
	return DE_NEW(Effect)(_openGL);
}

IndexBuffer* GraphicsDevice::Impl::createIndexBuffer(const Uint32 size, const IndexType& indexType,
	const AccessMode& accessMode) const
{
	return DE_NEW(IndexBuffer)(_openGL, size, indexType, accessMode);
}

Shader* GraphicsDevice::Impl::createShader(const ShaderType& type, const String8& source) const
{
	return DE_NEW(Shader)(_openGL, type, source);
}

VertexBufferState* GraphicsDevice::Impl::createVertexBufferState() const
{
	return DE_NEW(VertexBufferState)(_openGL);
}

void GraphicsDevice::Impl::draw(const PrimitiveType& primitiveType, const Uint32 vertexCount,
	const Uint32 vertexOffset) const
{
	initialiseDrawing();
	_openGL->drawArrays(static_cast<Uint32>(primitiveType), vertexOffset, vertexCount);
	DE_CHECK_ERROR_OPENGL(_openGL);
	deinitialiseDrawing();
}

void GraphicsDevice::Impl::drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount,
	const Uint32 indexOffset) const
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

void GraphicsDevice::Impl::setViewport(const Viewport& viewport)
{
	_viewport = viewport;
	const Rectangle& bounds = viewport.bounds();
	_openGL->viewport(bounds.x, bounds.y, bounds.width, bounds.height);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsDevice::Impl::swapBuffers() const
{
	_graphicsContext->swapBuffers();
}

// Private

void GraphicsDevice::Impl::initialiseOpenGL()
{
	_graphicsContext->makeCurrent();
	_openGL = DE_NEW(OpenGL)();
}

void GraphicsDevice::Impl::initialiseViewport()
{
	// TODO: use future wrapper in _openGL?
	_openGL->getIntegerv(OpenGL::VIEWPORT, reinterpret_cast<Int32*>(&_viewport));
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsDevice::Impl::initialiseDrawing() const
{
	DE_ASSERT(_activeEffect != nullptr);
	DE_ASSERT(_activeVertexBufferState != nullptr);
	_activeEffect->use();
	_activeVertexBufferState->bind();
}

void GraphicsDevice::Impl::deinitialiseDrawing() const
{
	_activeVertexBufferState->debind();
	_activeEffect->disuse();
}


// Graphics::GraphicsDevice

// Public

GraphicsDevice::GraphicsDevice(Impl* impl, Window* window)
	: _impl(impl),
	  _window(window) { }

GraphicsDevice::~GraphicsDevice()
{
	destroyResources();
	DE_DELETE(_impl, Impl);
}

void GraphicsDevice::clear(const Colour& colour) const
{
	_impl->clear(colour);
}

GraphicsBuffer* GraphicsDevice::createBuffer(const BufferBinding& binding, const Uint32 size,
	const AccessMode& accessMode)
{
	GraphicsBuffer* buffer = _impl->createBuffer(static_cast<Uint32>(binding), size, accessMode);
	_resources.push_back(buffer);

	return buffer;
}

Effect* GraphicsDevice::createEffect()
{
	Effect* effect = _impl->createEffect();
	_resources.push_back(effect);

	return effect;
}

IndexBuffer* GraphicsDevice::createIndexBuffer(const Uint32 size, const IndexType& indexType,
	const AccessMode& accessMode)
{
	IndexBuffer* indexBuffer = _impl->createIndexBuffer(size, indexType, accessMode);
	_resources.push_back(indexBuffer);

	return indexBuffer;
}

Shader* GraphicsDevice::createShader(const ShaderType& type, const String8& source)
{
	Shader* shader = _impl->createShader(type, source);
	_resources.push_back(shader);

	return shader;
}

VertexBufferState* GraphicsDevice::createVertexBufferState()
{
	VertexBufferState* vertexBufferState = _impl->createVertexBufferState();
	_resources.push_back(vertexBufferState);

	return vertexBufferState;
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

void GraphicsDevice::swapBuffers() const
{
	_impl->swapBuffers();
}
