/**
 * @file platform/opengl/OpenGLGraphicsBufferBase.cpp
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
#include <graphics/AccessMode.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBufferBase.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsBufferBase - OpenGL] ";


// Public

GraphicsBufferBase::GraphicsBufferBase(GraphicsInterfaceHandle graphicsInterfaceHandle,
	const BufferBinding& binding, const Uint size, const AccessMode& accessMode)
	: _openGl(static_cast<OpenGL*>(graphicsInterfaceHandle)),
	  _size(size),
	  _binding(static_cast<Uint32>(binding)),
	  _bufferHandle(0u),
	  _flags(0u)
{
	initialiseAccessMode(accessMode);
	createBuffer();
}

GraphicsBufferBase::~GraphicsBufferBase()
{
	OpenGL::deleteBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

void GraphicsBufferBase::demapData() const
{
	const Uint32 result = OpenGL::unmapBuffer(_binding >> 4);
	DE_CHECK_ERROR_OPENGL();

	if(result == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to demap the buffer data." <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}

Uint8* GraphicsBufferBase::mapData(const Uint size, const Uint bufferOffset) const
{
	Void* data = OpenGL::mapBufferRange(_binding >> 4, bufferOffset, size, _flags);
	DE_CHECK_ERROR_OPENGL();

	if(data == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to map the buffer data." << Log::Flush();
		DE_ERROR(0x0);
	}

	return static_cast<Uint8*>(data);
}

// Protected

void GraphicsBufferBase::initialiseStorage(const AccessMode& accessMode, const BufferUsage& usage) const
{
	const Uint32 usageId = getUsageId(accessMode, usage);
	OpenGL::bufferData(_binding >> 4, _size, nullptr, usageId);
	DE_CHECK_ERROR_OPENGL();
}

// Private

void GraphicsBufferBase::initialiseAccessMode(const AccessMode& accessMode)
{
	if((accessMode & AccessMode::Read) == AccessMode::Read)
		_flags |= OpenGL::MAP_READ_BIT;

	if((accessMode & AccessMode::Write) == AccessMode::Write)
		_flags |= OpenGL::MAP_WRITE_BIT;
}

void GraphicsBufferBase::createBuffer()
{
	OpenGL::genBuffers(1, &_bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}

// Static

Uint32 GraphicsBufferBase::getUsageId(const AccessMode& accessMode, const BufferUsage& usage)
{
	Uint32 id = static_cast<Uint32>(usage);

	if((accessMode & AccessMode::Read) == AccessMode::Read &&
		(accessMode & AccessMode::Write) != AccessMode::Write)
	{
		++id;
	}

	return id;
}
