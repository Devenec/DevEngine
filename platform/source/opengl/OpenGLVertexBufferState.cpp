/**
 * @file platform/opengl/OpenGLVertexBufferState.cpp
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
#include <core/debug/Assert.h>
#include <graphics/IndexBuffer.h>
#include <graphics/VertexElement.h>
#include <platform/PlatformInternal.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>
#include <platform/opengl/OpenGLIndexBuffer.h>
#include <platform/opengl/OpenGLGraphicsEnumerations.h>
#include <platform/opengl/OpenGLVertexBufferState.h>

using namespace Graphics;
using namespace Platform;

// External

static Uint32 getVertexElementComponentCount(const VertexElementType& elementType, Bool& normalise);
static Uint32 getVertexElementSize(const VertexElement& element);


// Implementation

// Public

VertexBufferState::Implementation::Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle)
	: _indexBuffer(nullptr),
	  _openGl(static_cast<OpenGL*>(graphicsInterfaceHandle)),
	  _vertexArrayHandle(0u)
{
	OpenGL::genVertexArrays(1, &_vertexArrayHandle);
	DE_CHECK_ERROR_OPENGL();
}

VertexBufferState::Implementation::~Implementation()
{
	OpenGL::deleteVertexArrays(1, &_vertexArrayHandle);
	DE_CHECK_ERROR_OPENGL();
}

void VertexBufferState::Implementation::setIndexBuffer(IndexBuffer* buffer)
{
	const Uint32 previousVertexArrayHandle = bind();

	if(buffer == nullptr)
		_indexBuffer->_implementation->debind();
	else
		buffer->_implementation->bind();

	debind(previousVertexArrayHandle);
	_indexBuffer = buffer;
}

void VertexBufferState::Implementation::setVertexBuffer(const GraphicsBuffer* buffer,
	const VertexElementList& vertexElements, const Uint32 stride, const Uint offset) const
{
	DE_ASSERT(buffer != nullptr);
	DE_ASSERT(buffer->_implementation->binding() == BufferBinding::Vertex);

	const Uint32 previousVertexArrayHandle = bind();
	buffer->_implementation->bind();
	setVertexLayout(vertexElements, stride, offset);

#if DE_BUILD == DE_BUILD_DEBUG
	buffer->_implementation->debind();
#endif

	debind(previousVertexArrayHandle);
}

// Private

void VertexBufferState::Implementation::setVertexLayout(const VertexElementList& vertexElements,
	const Uint32 stride, const Uint bufferOffset) const
{
	resetVertexAttributes();
	Uint elementOffset = bufferOffset;

	for(VertexElementList::const_iterator i = vertexElements.begin(), end = vertexElements.end();
		i != end; ++i)
	{
		if(i->offset != VertexElement::AFTER_PREVIOUS)
			elementOffset += i->offset;

		setVertexElementFormat(*i, elementOffset, stride);
		elementOffset += ::getVertexElementSize(*i);
	}
}

void VertexBufferState::Implementation::resetVertexAttributes() const
{
	for(Uint32 i = 0u, count = _openGl->vertexAttributeCount(); i < count; ++i)
		OpenGL::disableVertexAttribArray(i);
}

// Static

void VertexBufferState::Implementation::setVertexElementFormat(const VertexElement& element,
	const Uint elementOffset, const Uint32 stride)
{
	Bool normalise = false;
	const Uint32 componentCount = ::getVertexElementComponentCount(element.type, normalise);
	const Uint32 elementType = static_cast<Uint32>(element.type) >> 4;
	OpenGL::enableVertexAttribArray(element.index);
	DE_CHECK_ERROR_OPENGL();

	OpenGL::vertexAttribPointer(element.index, componentCount, elementType, normalise, stride,
		reinterpret_cast<Void*>(elementOffset));

	DE_CHECK_ERROR_OPENGL();
}


// Graphics::VertexBufferState

// Public

void VertexBufferState::setIndexBuffer(IndexBuffer* indexBuffer) const
{
	return _implementation->setIndexBuffer(indexBuffer);
}

void VertexBufferState::setVertexBuffer(const GraphicsBuffer* buffer, const VertexElementList& vertexElements,
	const Uint32 stride, const Uint offset) const
{
	_implementation->setVertexBuffer(buffer, vertexElements, stride, offset);
}

// Private

VertexBufferState::VertexBufferState(GraphicsInterfaceHandle graphicsInterfaceHandle)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(graphicsInterfaceHandle);
}

VertexBufferState::~VertexBufferState()
{
	DE_DELETE(_implementation, Implementation);
}


// External

static Uint32 getVertexElementComponentCount(const VertexElementType& elementType, Bool& normalise)
{
	const Int32 elementTypeId = static_cast<Int32>(elementType);
	normalise = (elementTypeId & 0x04) == 0x04;

	if((elementTypeId & 0x08) == 0x08)
		return OpenGL::BGRA;

	return (elementTypeId & 0x03) + 1u;
}

static Uint32 getVertexElementSize(const VertexElement& element)
{
	switch(element.type)
	{
		case VertexElementType::A2B10G10R10Int:
		case VertexElementType::A2B10G10R10IntNormalised:
		case VertexElementType::A2B10G10R10Uint:
		case VertexElementType::A2B10G10R10UintNormalised:
		case VertexElementType::A2R10G10B10IntNormalised:
		case VertexElementType::A2R10G10B10UintNormalised:
		case VertexElementType::B8G8R8A8UintNormalised:
		case VertexElementType::R16G16Float:
		case VertexElementType::R32Float:
		case VertexElementType::R8G8B8A8Int:
		case VertexElementType::R8G8B8A8IntNormalised:
		case VertexElementType::R16G16Int:
		case VertexElementType::R16G16IntNormalised:
		case VertexElementType::R32Int:
		case VertexElementType::R32IntNormalised:
		case VertexElementType::R8G8B8A8Uint:
		case VertexElementType::R8G8B8A8UintNormalised:
		case VertexElementType::R16G16Uint:
		case VertexElementType::R16G16UintNormalised:
		case VertexElementType::R32Uint:
		case VertexElementType::R32UintNormalised:
			return 4u;

		case VertexElementType::R16Float:
		case VertexElementType::R8G8Int:
		case VertexElementType::R8G8IntNormalised:
		case VertexElementType::R16Int:
		case VertexElementType::R16IntNormalised:
		case VertexElementType::R8G8Uint:
		case VertexElementType::R8G8UintNormalised:
		case VertexElementType::R16Uint:
		case VertexElementType::R16UintNormalised:
			return 2u;

		case VertexElementType::R16G16B16Float:
		case VertexElementType::R16G16B16Int:
		case VertexElementType::R16G16B16IntNormalised:
		case VertexElementType::R16G16B16Uint:
		case VertexElementType::R16G16B16UintNormalised:
			return 6u;

		case VertexElementType::R16G16B16A16Float:
		case VertexElementType::R32G32Float:
		case VertexElementType::R16G16B16A16Int:
		case VertexElementType::R16G16B16A16IntNormalised:
		case VertexElementType::R32G32Int:
		case VertexElementType::R32G32IntNormalised:
		case VertexElementType::R16G16B16A16Uint:
		case VertexElementType::R16G16B16A16UintNormalised:
		case VertexElementType::R32G32Uint:
		case VertexElementType::R32G32UintNormalised:
			return 8u;

		case VertexElementType::R32G32B32Float:
		case VertexElementType::R32G32B32Int:
		case VertexElementType::R32G32B32IntNormalised:
		case VertexElementType::R32G32B32Uint:
		case VertexElementType::R32G32B32UintNormalised:
			return 12u;

		case VertexElementType::R32G32B32A32Float:
		case VertexElementType::R32G32B32A32Int:
		case VertexElementType::R32G32B32A32IntNormalised:
		case VertexElementType::R32G32B32A32Uint:
		case VertexElementType::R32G32B32A32UintNormalised:
			return 16u;

		case VertexElementType::R8Int:
		case VertexElementType::R8IntNormalised:
		case VertexElementType::R8Uint:
		case VertexElementType::R8UintNormalised:
			return 1u;

		case VertexElementType::R8G8B8Int:
		case VertexElementType::R8G8B8IntNormalised:
		case VertexElementType::R8G8B8Uint:
		case VertexElementType::R8G8B8UintNormalised:
			return 3u;

		default:
			return 0u;
	}
}
