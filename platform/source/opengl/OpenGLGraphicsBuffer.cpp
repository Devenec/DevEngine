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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/AccessMode.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>
#include <platform/opengl/OpenGLGraphicsEnumerations.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::GraphicsBuffer - OpenGL] ";


// Implementation

// Public

GraphicsBuffer::Implementation::Implementation(const BufferBinding& binding, const Uint size,
	const AccessMode& accessMode, const BufferUsage& usage)
	: _size(size),
	  _binding(static_cast<Uint32>(binding)),
	  _bufferHandle(0u),
	  _flags(0u)
{
	initialiseAccessMode(accessMode);
	createBuffer();
	initialiseStorage(accessMode, usage);
}

GraphicsBuffer::Implementation::~Implementation()
{
	OpenGL::deleteBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

void GraphicsBuffer::Implementation::demapData() const
{
	bind();
	const Uint32 result = OpenGL::unmapBuffer(_binding);
	DE_CHECK_ERROR_OPENGL();

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to demap the buffer data." <<
			Log::Flush();

		DE_ERROR(0x0);
	}

	debind();
}

Uint8* GraphicsBuffer::Implementation::mapData(const Uint size, const Uint bufferOffset) const
{
	bind();
	Void* data = OpenGL::mapBufferRange(_binding, bufferOffset, size, _flags);
	DE_CHECK_ERROR_OPENGL();

	if(data == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to map the buffer data." << Log::Flush();
		DE_ERROR(0x0);
	}

	debind();
	return static_cast<Uint8*>(data);
}

// Private

void GraphicsBuffer::Implementation::initialiseAccessMode(const AccessMode& accessMode)
{
	if((accessMode & AccessMode::Read) == AccessMode::Read)
		_flags |= OpenGL::MAP_READ_BIT;

	if((accessMode & AccessMode::Write) == AccessMode::Write)
		_flags |= OpenGL::MAP_WRITE_BIT;
}

void GraphicsBuffer::Implementation::createBuffer()
{
	OpenGL::genBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

void GraphicsBuffer::Implementation::initialiseStorage(const AccessMode& accessMode, const BufferUsage& usage)
	const
{
	bind();
	OpenGL::bufferData(_binding, _size, nullptr, getUsageValue(accessMode, usage));
	DE_CHECK_ERROR_OPENGL();
	debind();
}

void GraphicsBuffer::Implementation::bind(const Uint32 bufferHandle) const
{
	OpenGL::bindBuffer(_binding, bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

Uint32 GraphicsBuffer::Implementation::getUsageValue(const AccessMode& accessMode, const BufferUsage& usage)
	const
{
	Uint32 value = static_cast<Uint32>(usage);

	if((accessMode & AccessMode::Read) == AccessMode::Read &&
		(accessMode & AccessMode::Write) != AccessMode::Write)
	{
		++value;
	}

	return value;
}


// Graphics::GraphicsBuffer

// Public

void GraphicsBuffer::demapData() const
{
	_implementation->demapData();
}

Uint8* GraphicsBuffer::mapData() const
{
	return _implementation->mapData();
}

Uint8* GraphicsBuffer::mapData(const Uint size, const Uint bufferOffset) const
{
	return _implementation->mapData(size, bufferOffset);
}

// Protected

GraphicsBuffer::GraphicsBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const BufferBinding& binding,
	const Uint size, const AccessMode& accessMode, const BufferUsage& usage)
	: _implementation(nullptr)
{
	static_cast<Void>(graphicsInterfaceHandle);
	_implementation = DE_NEW(Implementation)(binding, size, accessMode, usage);
}

GraphicsBuffer::~GraphicsBuffer()
{
	DE_DELETE(_implementation, Implementation);
}
