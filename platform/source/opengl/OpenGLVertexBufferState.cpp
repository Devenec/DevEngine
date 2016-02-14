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

// Static

void VertexBufferState::Implementation::setVertexLayout(const VertexElementList& vertexElements,
	const Uint32 stride, const Uint bufferOffset)
{
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

void VertexBufferState::Implementation::setVertexElementFormat(const VertexElement& element,
	const Uint elementOffset, const Uint32 stride)
{
	Bool normalise = element.normalise;
	const Uint32 componentCount = ::getVertexElementComponentCount(element.type, normalise);
	const Uint32 elementType = static_cast<Uint32>(element.type) >> 3;
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

	if((elementTypeId & 0x04) == 0x04)
	{
		normalise = true;
		return OpenGL::BGRA;
	}

	return (elementTypeId & 0x03) + 1u;
}

static Uint32 getVertexElementSize(const VertexElement& element)
{
	switch(element.type)
	{
		case VertexElementType::Float16:
		case VertexElementType::Int8Vector2:
		case VertexElementType::Int16:
		case VertexElementType::Uint8Vector2:
		case VertexElementType::Uint16:
			return 2u;

		case VertexElementType::Float16Vector2:
		case VertexElementType::Float32:
		case VertexElementType::Int8Vector4:
		case VertexElementType::Int16Vector2:
		case VertexElementType::Int32:
		case VertexElementType::Int32_A2B10G10R10:
		case VertexElementType::Int32_A2R10G10B10:
		case VertexElementType::Uint8Vector4:
		case VertexElementType::Uint16Vector2:
		case VertexElementType::Uint32:
		case VertexElementType::Uint32_A2B10G10R10:
		case VertexElementType::Uint32_A2R10G10B10:
			return 4u;

		case VertexElementType::Float16Vector3:
		case VertexElementType::Int16Vector3:
		case VertexElementType::Uint16Vector3:
			return 6u;

		case VertexElementType::Float16Vector4:
		case VertexElementType::Float32Vector2:
		case VertexElementType::Float64:
		case VertexElementType::Int16Vector4:
		case VertexElementType::Int32Vector2:
		case VertexElementType::Uint16Vector4:
		case VertexElementType::Uint32Vector2:
			return 8u;

		case VertexElementType::Float32Vector3:
		case VertexElementType::Int32Vector3:
		case VertexElementType::Uint32Vector3:
			return 12u;

		case VertexElementType::Float32Vector4:
		case VertexElementType::Float64Vector2:
		case VertexElementType::Int32Vector4:
		case VertexElementType::Uint32Vector4:
			return 16u;

		case VertexElementType::Float64Vector3:
			return 24u;

		case VertexElementType::Float64Vector4:
			return 32u;

		case VertexElementType::Int8:
		case VertexElementType::Uint8:
			return 1u;

		case VertexElementType::Int8Vector3:
		case VertexElementType::Uint8Vector3:
			return 3u;

		default:
			return 0u;
	}
}
