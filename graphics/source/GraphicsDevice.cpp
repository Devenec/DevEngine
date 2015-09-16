/**
 * @file graphics/GraphicsDevice.cpp
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
#include <graphics/Effect.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsResource.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Shader.h>
#include <graphics/VertexBufferState.h>

using namespace Core;
using namespace Graphics;

// Some members are defined in platform/*/*GraphicsDevice.cpp

// Public

GraphicsBuffer* GraphicsDevice::createBuffer(const BufferBinding& binding, const Uint32 size,
	const AccessMode& accessMode)
{
	GraphicsBuffer* buffer = DE_NEW(GraphicsBuffer)(binding, size, accessMode);
	_resources.push_back(buffer);

	return buffer;
}

Effect* GraphicsDevice::createEffect()
{
	Effect* effect = DE_NEW(Effect)();
	_resources.push_back(effect);

	return effect;
}

IndexBuffer* GraphicsDevice::createIndexBuffer(const Uint32 size, const IndexType& indexType,
	const AccessMode& accessMode)
{
	IndexBuffer* indexBuffer = DE_NEW(IndexBuffer)(size, indexType, accessMode);
	_resources.push_back(indexBuffer);

	return indexBuffer;
}

Shader* GraphicsDevice::createShader(const ShaderType& type, const String8& source)
{
	Shader* shader = DE_NEW(Shader)(type, source);
	_resources.push_back(shader);

	return shader;
}

VertexBufferState* GraphicsDevice::createVertexBufferState()
{
	VertexBufferState* vertexBufferState = DE_NEW(VertexBufferState)();
	_resources.push_back(vertexBufferState);

	return vertexBufferState;
}

void GraphicsDevice::destroyResource(GraphicsResource* resource)
{
	_resources.remove(resource);
	DE_DELETE(resource, GraphicsResource);
}

// Private

void GraphicsDevice::destroyResources() const
{
	for(GraphicsResourceList::const_reverse_iterator i = _resources.rbegin(), end = _resources.rend(); i != end; ++i)
		DE_DELETE(*i, GraphicsResource);
}
