/**
 * @file platform/opengl/OpenGLGraphicsBuffer.cpp
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

#include <algorithm>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/AccessMode.h>
#include <graphics/GraphicsBuffer.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsBuffer - OpenGL]";


// Implementation

// Public

GraphicsBuffer::Impl::Impl(const Uint32 size, const AccessMode& accessMode)
	: _bufferHandle(0u),
	  _flags(0u)
{
	createBuffer();
	initialiseFlags(accessMode);
	initialiseStorage(size);
}

GraphicsBuffer::Impl::~Impl()
{
	OpenGL::deleteBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

void GraphicsBuffer::Impl::demapData() const
{
	const Uint32 result = OpenGL::unmapNamedBuffer(_bufferHandle);
	DE_CHECK_ERROR_OPENGL();

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to demap the buffer data" << Log::Flush();
		DE_ERROR(0x0);
	}
}

Uint32 GraphicsBuffer::Impl::handle() const
{
	return _bufferHandle;
}

Byte* GraphicsBuffer::Impl::mapData(const Uint32 size, const Uint32 bufferOffset) const
{
	Void* pointer = OpenGL::mapNamedBufferRange(_bufferHandle, bufferOffset, size, _flags);
	DE_CHECK_ERROR_OPENGL();

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to map the buffer data" << Log::Flush();
		DE_ERROR(0x0);
	}

	return static_cast<Byte*>(pointer);
}

void GraphicsBuffer::Impl::setData(const Byte* data, const Uint32 size, const Uint32 bufferOffset) const
{
	DE_ASSERT(data != nullptr);
	Byte* mappedData = mapData(size, bufferOffset);
	std::copy(data, data + size, mappedData);
	demapData();
}

// Private

void GraphicsBuffer::Impl::createBuffer()
{
	OpenGL::createBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

void GraphicsBuffer::Impl::initialiseFlags(const AccessMode& accessMode)
{
	if((accessMode & AccessMode::Read) == AccessMode::Read)
		_flags |= OpenGL::MAP_READ_BIT;
		
	if((accessMode & AccessMode::Write) == AccessMode::Write)
		_flags |= OpenGL::MAP_WRITE_BIT;
}

void GraphicsBuffer::Impl::initialiseStorage(const Uint32 size) const
{
	OpenGL::namedBufferStorage(_bufferHandle, size, nullptr, _flags);
	DE_CHECK_ERROR_OPENGL();
}


// Graphics::GraphicsBuffer

// Public

void GraphicsBuffer::demapData() const
{
	_impl->demapData();
}

Byte* GraphicsBuffer::mapData(const Uint32 size, const Uint32 bufferOffset) const
{
	return _impl->mapData(size, bufferOffset);
}

void GraphicsBuffer::setData(const Byte* data, const Uint32 dataSize, const Uint32 bufferOffset) const
{
	_impl->setData(data, dataSize, bufferOffset);
}

// Protected

GraphicsBuffer::GraphicsBuffer(const Uint32 size, const AccessMode& accessMode)
	: _impl(DE_NEW(Impl)(size, accessMode)) { }

GraphicsBuffer::~GraphicsBuffer()
{
	DE_DELETE(_impl, Impl);
}
