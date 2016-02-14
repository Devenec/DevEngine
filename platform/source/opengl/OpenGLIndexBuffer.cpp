/**
 * @file platform/opengl/OpenGLIndexBuffer.cpp
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
#include <core/Platform.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsEnumerations.h>
#include <platform/opengl/OpenGLIndexBuffer.h>

using namespace Graphics;
using namespace Platform;

// Implementation

// Public

IndexBuffer::Implementation::Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle, const Uint size,
	const AccessMode& accessMode, const BufferUsage& usage)
	: Base(graphicsInterfaceHandle, BufferBinding::Index, size, accessMode)
{
	const Uint32 previousVertexArrayHandle = bindToDefaultVertexArray();
	initialiseStorage(accessMode, usage);
	debindFromDefaultVertexArray(previousVertexArrayHandle);
}

void IndexBuffer::Implementation::demapData() const
{
	const Uint32 previousVertexArrayHandle = bindToDefaultVertexArray();
	Base::demapData();
	debindFromDefaultVertexArray(previousVertexArrayHandle);
}

Uint8* IndexBuffer::Implementation::mapData(const Uint size, const Uint offset) const
{
	const Uint32 previousVertexArrayHandle = bindToDefaultVertexArray();
	Uint8* data = Base::mapData(size, offset);
	debindFromDefaultVertexArray(previousVertexArrayHandle);

	return data;
}

// Private

Uint32 IndexBuffer::Implementation::bindToDefaultVertexArray() const
{
	const Uint32 previousVertexArrayHandle = _openGl->bindDefaultVertexArray();
	bind();

	return previousVertexArrayHandle;
}

void IndexBuffer::Implementation::debindFromDefaultVertexArray(const Uint32 previousVertexArrayHandle) const
{
#if DE_BUILD == DE_BUILD_DEBUG
	debind();
#endif

	_openGl->bindVertexArrayCustom(previousVertexArrayHandle);
}

void IndexBuffer::Implementation::bind(const Uint32 bufferHandle) const
{
	OpenGL::bindBuffer(_binding >> 4, bufferHandle);
	DE_CHECK_ERROR_OPENGL();
}


// Graphics::IndexBuffer

// Public

void IndexBuffer::demapData() const
{
	_implementation->demapData();
}

Uint8* IndexBuffer::mapData() const
{
	return _implementation->mapData();
}

Uint8* IndexBuffer::mapData(const Uint size, const Uint bufferOffset) const
{
	return _implementation->mapData(size, bufferOffset);
}

// Private

IndexBuffer::IndexBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const Uint size,
	const IndexType& indexType, const AccessMode& accessMode, const BufferUsage& usage)
	: _implementation(nullptr),
	  _indexType(indexType)
{
	_implementation = DE_NEW(Implementation)(graphicsInterfaceHandle, size, accessMode, usage);
}

IndexBuffer::~IndexBuffer()
{
	DE_DELETE(_implementation, Implementation);
}
