/**
 * @file platform/opengl/OpenGLGraphicsBuffer.cpp
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

#include <algorithm>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/AccessMode.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::GraphicsBuffer - OpenGL] ";


// Implementation

// Public

GraphicsBuffer::Implementation::Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle,
	const BufferBinding& binding, const Uint32 size, const AccessMode& accessMode)
	: _openGL(static_cast<OpenGL*>(graphicsInterfaceHandle)),
	  _binding(static_cast<Uint32>(binding)),
	  _bufferHandle(0u),
	  _flags(0u),
	  _size(size)
{
	initialiseAccessMode(accessMode);
	createBuffer();
	initialiseStorage();
}

GraphicsBuffer::Implementation::~Implementation()
{
	_openGL->deleteBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsBuffer::Implementation::bindIndexed(const Uint32 bindingIndex) const
{
	_openGL->bindBufferBase(_binding, bindingIndex, _bufferHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsBuffer::Implementation::debindIndexed(const Uint32 bindingIndex) const
{
	_openGL->bindBufferBase(_binding, bindingIndex, 0u);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsBuffer::Implementation::demapData() const
{
	bind();
	const Uint32 result = _openGL->unmapBuffer(_binding);
	DE_CHECK_ERROR_OPENGL(_openGL);

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to demap the buffer data." << Log::Flush();
		DE_ERROR(0x0);
	}

	debind();
	// TODO: restore old binding?
}

Uint8* GraphicsBuffer::Implementation::mapData(const Uint32 size, const Uint32 bufferOffset) const
{
	bind();
	Void* data = _openGL->mapBufferRange(_binding, bufferOffset, size, _flags);
	DE_CHECK_ERROR_OPENGL(_openGL);

	if(data == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to map the buffer data." << Log::Flush();
		DE_ERROR(0x0);
	}

	debind(); // TODO: restore old binding?
	return static_cast<Uint8*>(data);
}

void GraphicsBuffer::Implementation::setData(const Uint8* data, const Uint32 size, const Uint32 bufferOffset) const
{
	DE_ASSERT(data != nullptr);
	Uint8* mappedData = mapData(size, bufferOffset);
	std::copy(data, data + size, mappedData);
	demapData(); // TODO: restore old binding?
}

// Private

void GraphicsBuffer::Implementation::bind(const Uint32 bufferHandle) const
{
	_openGL->bindBuffer(_binding, bufferHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsBuffer::Implementation::initialiseAccessMode(const AccessMode& accessMode)
{
	if((accessMode & AccessMode::Read) == AccessMode::Read)
		_flags |= OpenGL::MAP_READ_BIT;

	if((accessMode & AccessMode::Write) == AccessMode::Write)
		_flags |= OpenGL::MAP_WRITE_BIT;
}

void GraphicsBuffer::Implementation::createBuffer()
{
	_openGL->genBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void GraphicsBuffer::Implementation::initialiseStorage() const
{
	bind();
	_openGL->bufferData(_binding, _size, nullptr, OpenGL::STATIC_DRAW);
	DE_CHECK_ERROR_OPENGL(_openGL);
	debind(); // TODO: restore old binding?
}


// Graphics::GraphicsBuffer

// Public

void GraphicsBuffer::bind() const
{
	_implementation->bind();
}

void GraphicsBuffer::bindIndexed(const Uint32 bindingIndex) const
{
	_implementation->bindIndexed(bindingIndex);
}

void GraphicsBuffer::debind() const
{
	_implementation->debind();
}

void GraphicsBuffer::debindIndexed(const Uint32 bindingIndex) const
{
	_implementation->debindIndexed(bindingIndex);
}

void GraphicsBuffer::demapData() const
{
	_implementation->demapData();
}

Uint8* GraphicsBuffer::mapData(const Uint32 size, const Uint32 bufferOffset) const
{
	return _implementation->mapData(size, bufferOffset);
}

void GraphicsBuffer::setData(const Uint8* data, const Uint32 dataSize, const Uint32 bufferOffset) const
{
	_implementation->setData(data, dataSize, bufferOffset);
}

// Protected

GraphicsBuffer::GraphicsBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const BufferBinding& binding,
	const Uint32 size, const AccessMode& accessMode)
	: _implementation(DE_NEW(Implementation)(graphicsInterfaceHandle, binding, size, accessMode)) { }

GraphicsBuffer::~GraphicsBuffer()
{
	DE_DELETE(_implementation, Implementation);
}
