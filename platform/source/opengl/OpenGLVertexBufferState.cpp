/**
 * @file platform/opengl/OpenGLVertexBufferState.cpp
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
#include <core/Types.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/VertexBufferState.h>
#include <graphics/VertexElement.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>
#include <platform/opengl/OpenGLInterface.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class VertexBufferState::Impl final
{
public:

	Impl()
		: _vertexArrayHandle(0u)
	{
		OpenGL::createVertexArrays(1, &_vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		OpenGL::deleteVertexArrays(1, &_vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	// TODO: should store the previously applied program and restore it at deapply?
	void apply() const
	{
		applyVertexArray(_vertexArrayHandle);
	}

	void deapply() const
	{
		applyVertexArray(0u);
	}

	void setVertexBuffer(const GraphicsBuffer* buffer, const Uint32 slot, const Uint32 stride,
		const Uint32 bufferOffset) const
	{
		OpenGL::vertexArrayVertexBuffer(_vertexArrayHandle, slot, buffer->_impl->handle(), bufferOffset, stride);
		DE_CHECK_ERROR_OPENGL();
	}

	void setVertexLayout(const InitialiserList<VertexElement>& vertexElements, const Bool calculateOffsets) const
	{
		Uint32 offset = 0u;

		for(InitialiserList<VertexElement>::const_iterator i = vertexElements.begin(), end = vertexElements.end();
			i != end; ++i)
		{
			if(!calculateOffsets)
				offset = i->offset;

			OpenGL::vertexArrayAttribFormat(_vertexArrayHandle, i->index, i->componentCount, getVertexElementType(*i),
				i->normalise, offset);

			DE_CHECK_ERROR_OPENGL();
			OpenGL::enableVertexArrayAttrib(_vertexArrayHandle, i->index);
			DE_CHECK_ERROR_OPENGL();
			OpenGL::vertexArrayAttribBinding(_vertexArrayHandle, i->index, i->slot);
			DE_CHECK_ERROR_OPENGL();

			if(calculateOffsets)
				offset += getVertexElementSize(*i);
		}
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	Uint32 _vertexArrayHandle;

	static void applyVertexArray(const Uint32 vertexArrayHandle)
	{
		OpenGL::bindVertexArray(vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	static Uint32 getVertexElementSize(const VertexElement& element)
	{
		switch(element.type)
		{
			case VertexElementType::Float16:
			case VertexElementType::Int16:
			case VertexElementType::Uint16:
				return 2u;

			case VertexElementType::Float32:
			case VertexElementType::Int32:
			case VertexElementType::Uint32:
				return 4u;

			case VertexElementType::Float64:
				return 8u;

			case VertexElementType::Int8:
			case VertexElementType::Uint8:
				return 1u;

			default:
				DE_ASSERT(false);
				return 0u;
		}
	}

	static Uint32 getVertexElementType(const VertexElement& element)
	{
		switch(element.type)
		{
			case VertexElementType::Float16:
				return GL_HALF_FLOAT;

			case VertexElementType::Float32:
				return GL_FLOAT;

			case VertexElementType::Float64:
				return GL_DOUBLE;

			case VertexElementType::Int8:
				return GL_BYTE;

			case VertexElementType::Int16:
				return GL_SHORT;

			case VertexElementType::Int32:
				return GL_INT;

			case VertexElementType::Uint8:
				return GL_UNSIGNED_BYTE;

			case VertexElementType::Uint16:
				return GL_UNSIGNED_SHORT;

			case VertexElementType::Uint32:
				return GL_UNSIGNED_INT;

			default:
				DE_ASSERT(false);
				return 0u;
		}
	}
};


// Public

VertexBufferState::VertexBufferState()
	: _impl(DE_NEW(Impl)()) { }

VertexBufferState::~VertexBufferState()
{
	DE_DELETE(_impl, Impl);
}

void VertexBufferState::apply() const
{
	_impl->apply();
}

void VertexBufferState::deapply() const
{
	_impl->deapply();
}

void VertexBufferState::setVertexBuffer(const GraphicsBuffer* buffer, const Uint32 slot, const Uint32 stride,
	const Uint32 bufferOffset) const
{
	_impl->setVertexBuffer(buffer, slot, stride, bufferOffset);
}

void VertexBufferState::setVertexLayout(const InitialiserList<VertexElement>& vertexElements,
	const Bool calculateOffsets) const
{
	_impl->setVertexLayout(vertexElements, calculateOffsets);
}
