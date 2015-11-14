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

static Uint32 getVertexElementComponentCount(const VertexElement& element, Bool& normalise);
static Uint32 getVertexElementSize(const VertexElement& element);


// Implementation

class VertexBufferState::Impl final
{
public:

	Impl(OpenGL* openGL)
		: _indexBuffer(nullptr),
		_openGL(openGL),
		_vertexArrayHandle(0u)
	{
		_openGL->genVertexArrays(1, &_vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		_openGL->deleteVertexArrays(1, &_vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void bind() const
	{
		bind(_vertexArrayHandle);
	}

	void debind() const
	{
		bind(0u);
	}

	IndexBuffer* indexBuffer() const
	{
		return _indexBuffer;
	}

	void setIndexBuffer(IndexBuffer* buffer)
	{
		// TODO: assert that buffer has BufferBinding::Index
		bind();

		if(buffer == nullptr)
			_indexBuffer->_impl->debind(); // TODO: restore old binding?
		else
			buffer->_impl->bind();

		debind();
		// TODO: restore old binding?
		_indexBuffer = buffer;
	}

	// TODO: rename and rename bufferIndex
	void setVertexBuffer(const GraphicsBuffer* buffer, const InitialiserList<VertexElement>& vertexElements,
		const Uint32 stride, const Uint32 offset) const
	{
		Uint32 bufferHandle = 0u;

		if(buffer != nullptr)
			bufferHandle = buffer->_impl->handle();

		bind();
		buffer->bind();
		setVertexLayout(vertexElements, stride, offset);
		buffer->debind();
		debind();
		// TODO: restore old bindings?
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	IndexBuffer* _indexBuffer;
	Platform::OpenGL* _openGL;
	Uint32 _vertexArrayHandle;

	void bind(const Uint32 vertexArrayHandle) const
	{
		_openGL->bindVertexArray(vertexArrayHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void setVertexLayout(const InitialiserList<VertexElement>& vertexElements, const Uint32 stride,
		const Uint32 bufferOffset) const
	{
		Uint32 elementOffset = bufferOffset;

		for(InitialiserList<VertexElement>::const_iterator i = vertexElements.begin(), end = vertexElements.end();
			i != end; ++i)
		{
			if(i->offset != VertexElement::AFTER_PREVIOUS)
				elementOffset += i->offset;

			setVertexElementFormat(*i, elementOffset, stride);
			elementOffset += ::getVertexElementSize(*i);
		}
	}

	void setVertexElementFormat(const VertexElement& element, const Uint32 elementOffset, const Uint32 stride) const
	{
		Bool normalise;
		const Uint32 componentCount = ::getVertexElementComponentCount(element, normalise);
		const Uint32 elementType = static_cast<Uint32>(element.type) >> 3;
		_openGL->enableVertexAttribArray(element.index);
		DE_CHECK_ERROR_OPENGL(_openGL);
		const Void* bufferOffset = reinterpret_cast<Void*>(elementOffset);
		_openGL->vertexAttribPointer(element.index, componentCount, elementType, normalise, stride, bufferOffset);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}
};


// Graphics::VertexBufferState

// Public

void VertexBufferState::bind() const
{
	_impl->bind();
}

void VertexBufferState::debind() const
{
	_impl->debind();
}

IndexBuffer* VertexBufferState::indexBuffer() const
{
	return _impl->indexBuffer();
}

void VertexBufferState::setIndexBuffer(IndexBuffer* indexBuffer) const
{
	return _impl->setIndexBuffer(indexBuffer);
}

void VertexBufferState::setVertexBuffer(const GraphicsBuffer* buffer,
	const InitialiserList<VertexElement>& vertexElements, const Uint32 stride, const Uint32 offset) const
{
	_impl->setVertexBuffer(buffer, vertexElements, stride, offset);
}

// Private

VertexBufferState::VertexBufferState(GraphicsInterface graphicsInterface)
	: _impl(DE_NEW(Impl)(static_cast<OpenGL*>(graphicsInterface))) { }

VertexBufferState::~VertexBufferState()
{
	DE_DELETE(_impl, Impl);
}


// External

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
