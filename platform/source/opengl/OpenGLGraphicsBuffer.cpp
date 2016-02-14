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

#include <core/Memory.h>
#include <core/Platform.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>

using namespace Graphics;

// Implementation

// Public

GraphicsBuffer::Implementation::Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle,
	const BufferBinding& binding, const Uint size, const AccessMode& accessMode, const BufferUsage& usage)
	: Base(graphicsInterfaceHandle, binding, size, accessMode)
{
	bind();
	initialiseStorage(accessMode, usage);

#if DE_BUILD == DE_BUILD_DEBUG
	debind();
#endif
}

void GraphicsBuffer::Implementation::demapData() const
{
	bind();
	Base::demapData();

#if DE_BUILD == DE_BUILD_DEBUG
	debind();
#endif
}

Uint8* GraphicsBuffer::Implementation::mapData(const Uint size, const Uint offset) const
{
	bind();
	Uint8* data = Base::mapData(size, offset);

#if DE_BUILD == DE_BUILD_DEBUG
	debind();
#endif

	return data;
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

// Private

GraphicsBuffer::GraphicsBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const BufferBinding& binding,
	const Uint size, const AccessMode& accessMode, const BufferUsage& usage)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(graphicsInterfaceHandle, binding, size, accessMode, usage);
}

GraphicsBuffer::~GraphicsBuffer()
{
	DE_DELETE(_implementation, Implementation);
}
