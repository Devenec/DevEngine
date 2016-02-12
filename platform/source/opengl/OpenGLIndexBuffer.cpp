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
#include <platform/opengl/OpenGLGraphicsEnumerations.h>
#include <platform/opengl/OpenGLIndexBuffer.h>

using namespace Graphics;

// Implementation

// Public

IndexBuffer::Implementation::Implementation(const Uint size, const AccessMode& accessMode,
	const BufferUsage& usage)
	: Base(BufferBinding::Index, size, accessMode, usage) { }


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
	static_cast<Void>(graphicsInterfaceHandle);
	_implementation = DE_NEW(Implementation)(size, accessMode, usage);
}

IndexBuffer::~IndexBuffer()
{
	DE_DELETE(_implementation, Implementation);
}
