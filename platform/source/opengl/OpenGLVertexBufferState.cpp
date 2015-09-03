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
#include <core/debug/Assert.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/IndexBuffer.h>
#include <graphics/VertexBufferState.h>
#include <graphics/VertexElement.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static void applyVertexArray(const Uint32 vertexArrayHandle);
static Uint32 getVertexElementComponentCount(const VertexElement& element, Bool& normalise);
static Uint32 getVertexElementSize(const VertexElement& element);


// Implementation

class VertexBufferState::Impl final
{
public:

	Impl()
		: _indexBuffer(nullptr),
		  _vertexArrayHandle(0u)
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

	void apply() const
	{
		applyVertexArray(_vertexArrayHandle);
	}

	void deapply() const
	{
		applyVertexArray(0u);
	}

	IndexBuffer* indexBuffer() const
	{
		return _indexBuffer;
	}

	void setIndexBuffer(IndexBuffer* buffer)
	{
		_indexBuffer = buffer;
		Uint32 bufferHandle = 0u;

		if(buffer != nullptr)
			bufferHandle = buffer->_impl->handle();

		OpenGL::vertexArrayElementBuffer(_vertexArrayHandle, bufferHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	void setVertexBuffer(const GraphicsBuffer* buffer, const Uint32 bufferIndex, const Uint32 stride,
		const Uint32 offset) const
	{
		Uint32 bufferHandle = 0u;

		if(buffer != nullptr)
			bufferHandle = buffer->_impl->handle();

		OpenGL::vertexArrayVertexBuffer(_vertexArrayHandle, bufferIndex, bufferHandle, offset, stride);
		DE_CHECK_ERROR_OPENGL();
	}

	void setVertexLayout(const InitialiserList<VertexElement>& vertexElements) const
	{
		Uint32 offset = 0u;

		for(InitialiserList<VertexElement>::const_iterator i = vertexElements.begin(), end = vertexElements.end();
			i != end; ++i)
		{
			if(i->offset != VertexElement::AFTER_PREVIOUS)
				offset = i->offset;

			setVertexElementFormat(*i, offset);
			setVertexElementBinding(*i);
			offset += getVertexElementSize(*i);
		}
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	IndexBuffer* _indexBuffer;
	Uint32 _vertexArrayHandle;

	void setVertexElementFormat(const VertexElement& element, const Uint32 offset) const
	{
		Bool normalise;
		const Uint32 componentCount = getVertexElementComponentCount(element, normalise);
		const Uint32 vertexElementType = static_cast<Uint32>(element.type) >> 3;

		OpenGL::vertexArrayAttribFormat(_vertexArrayHandle, element.vertexIndex, componentCount, vertexElementType,
			normalise, offset);

		DE_CHECK_ERROR_OPENGL();
		OpenGL::enableVertexArrayAttrib(_vertexArrayHandle, element.vertexIndex);
		DE_CHECK_ERROR_OPENGL();
	}

	void setVertexElementBinding(const VertexElement& element) const
	{
		OpenGL::vertexArrayAttribBinding(_vertexArrayHandle, element.vertexIndex, element.bufferIndex);
		DE_CHECK_ERROR_OPENGL();
	}
};


// Public

void VertexBufferState::apply() const
{
	_impl->apply();
}

void VertexBufferState::deapply() const
{
	_impl->deapply();
}

IndexBuffer* VertexBufferState::indexBuffer() const
{
	return _impl->indexBuffer();
}

void VertexBufferState::setIndexBuffer(IndexBuffer* indexBuffer) const
{
	return _impl->setIndexBuffer(indexBuffer);
}

void VertexBufferState::setVertexBuffer(const GraphicsBuffer* buffer, const Uint32 bufferIndex, const Uint32 stride,
	const Uint32 offset) const
{
	_impl->setVertexBuffer(buffer, bufferIndex, stride, offset);
}

void VertexBufferState::setVertexLayout(const InitialiserList<VertexElement>& vertexElements) const
{
	_impl->setVertexLayout(vertexElements);
}

// Private

VertexBufferState::VertexBufferState()
	: _impl(DE_NEW(Impl)()) { }

VertexBufferState::~VertexBufferState()
{
	DE_DELETE(_impl, Impl);
}


// External

static void applyVertexArray(const Uint32 vertexArrayHandle)
{
	OpenGL::bindVertexArray(vertexArrayHandle);
	DE_CHECK_ERROR_OPENGL();
}

static Uint32 getVertexElementComponentCount(const VertexElement& element, Bool& normalise)
{
	normalise = element.normalise;
	Uint32 componentCount = static_cast<Int32>(element.type) & 0x07;

	if(componentCount > 4u)
	{
		--componentCount;
		normalise = true;
	}

	if(componentCount == 5u)
		componentCount = OpenGL::BGRA;

	return componentCount;
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
		case VertexElementType::Int32_B10G10R10A2:
		case VertexElementType::Int32_R10G10B10A2:
		case VertexElementType::Uint8Vector4:
		case VertexElementType::Uint16Vector2:
		case VertexElementType::Uint32:
		case VertexElementType::Uint32_B10G10R10A2:
		case VertexElementType::Uint32_R10G10B10A2:
		case VertexElementType::Uint32_R11G11B10_Float:
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
			DE_ASSERT(false);
			return 0u;
	}
}
