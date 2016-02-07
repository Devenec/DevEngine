/**
 * @file platform/opengl/OpenGLGraphicsDevice.cpp
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

#include <core/Bitset.h>
#include <core/Memory.h>
#include <core/Platform.h>
#include <core/Rectangle.h>
#include <core/Utility.h>
#include <core/debug/Assert.h>
#include <graphics/Colour.h>
#include <graphics/Effect.h>
#include <graphics/EffectCode.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/IndexBuffer.h>
#include <graphics/Shader.h>
#include <graphics/VertexBufferState.h>
#include <graphics/Viewport.h>
#include <platform/GraphicsContext.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLEffect.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>
#include <platform/opengl/OpenGLVertexBufferState.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsDevice::Implementation final
{
public:

	explicit Implementation(GraphicsContext* graphicsContext)
		: _activeEffect(nullptr),
		  _activeVertexBufferState(nullptr),
		  _graphicsContext(graphicsContext),
		  _openGl(nullptr)
	{
		initialiseOpenGL();
		initialiseViewport();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		DE_DELETE(_openGl, OpenGL);
		DE_DELETE(_graphicsContext, GraphicsContext);
	}

	void bindBufferIndexed(GraphicsBuffer* buffer, const Uint32 bindingIndex) const
	{
		GraphicsBuffer::Implementation* bufferImplementation = buffer->_implementation;
		OpenGL::bindBufferBase(bufferImplementation->binding(), bindingIndex, bufferImplementation->handle());
		DE_CHECK_ERROR_OPENGL();
	}

	void clear(const Colour& colour) const
	{
		OpenGL::clearColor(colour.red, colour.green, colour.blue, colour.alpha);
		OpenGL::clear(OpenGL::COLOR_BUFFER_BIT);
		DE_CHECK_ERROR_OPENGL();
	}

	GraphicsBuffer* createBuffer(const BufferBinding& binding, const Uint size, const AccessMode& accessMode,
		const BufferUsage& usage) const
	{
		return DE_NEW(GraphicsBuffer)(nullptr, binding, size, accessMode, usage);
	}

	Effect* createEffect() const
	{
		return DE_NEW(Effect)(nullptr);
	}

	IndexBuffer* createIndexBuffer(const Uint size, const IndexType& indexType, const AccessMode& accessMode,
		const BufferUsage& usage) const
	{
		return DE_NEW(IndexBuffer)(nullptr, size, indexType, accessMode, usage);
	}

	Shader* createShader(const ShaderType& type, const ByteList& shaderCode) const
	{
		return DE_NEW(Shader)(nullptr, type, shaderCode);
	}

	VertexBufferState* createVertexBufferState() const
	{
		return DE_NEW(VertexBufferState)(nullptr);
	}

	void debindBufferIndexed(GraphicsBuffer* buffer, const Uint32 bindingIndex) const
	{
		OpenGL::bindBufferBase(buffer->_implementation->binding(), bindingIndex, 0u);
		DE_CHECK_ERROR_OPENGL();
	}

	void draw(const PrimitiveType& primitiveType, const Uint32 vertexCount, const Uint32 vertexOffset)
	{
		initialiseDrawing();
		OpenGL::drawArrays(static_cast<Uint32>(primitiveType), vertexOffset, vertexCount);
		DE_CHECK_ERROR_OPENGL();

#if DE_BUILD == DE_BUILD_DEBUG
		deinitialiseDrawing();
#endif
	}

	void drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount, const Uint32 indexOffset)
	{
		initialiseDrawing();
		IndexBuffer* indexBuffer = _activeVertexBufferState->_implementation->indexBuffer();
		DE_ASSERT(indexBuffer != nullptr);
		const Uint32 indexTypeId = static_cast<Uint32>(indexBuffer->indexType());
		const Uint byteOffset = indexOffset * ((indexTypeId & 0x03) + 1u);

		OpenGL::drawElements(static_cast<Uint32>(primitiveType), indexCount, indexTypeId >> 2,
			reinterpret_cast<Void*>(byteOffset));

		DE_CHECK_ERROR_OPENGL();

#if DE_BUILD == DE_BUILD_DEBUG
		deinitialiseDrawing();
#endif
	}

	void setEffect(Effect* effect)
	{
		_activeEffect = effect;
		setComponentState(ComponentID::Effect, false);
	}

	void setVertexBufferState(VertexBufferState* vertexBufferState)
	{
		_activeVertexBufferState = vertexBufferState;
		setComponentState(ComponentID::VertexBufferState, false);
	}

	void setViewport(const Viewport& viewport)
	{
		_viewport = viewport;
		setComponentState(ComponentID::Viewport, false);
	}

	void swapBuffers() const
	{
		_graphicsContext->swapBuffers();
	}

	const Viewport& viewport() const
	{
		return _viewport;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	enum class ComponentID
	{
		Effect,
		VertexBufferState,
		Viewport
	};

	Viewport _viewport;
	Effect* _activeEffect;
	VertexBufferState* _activeVertexBufferState;
	GraphicsContext* _graphicsContext;
	OpenGL* _openGl;
	Core::Bitset _componentStates;

	void initialiseOpenGL()
	{
		_graphicsContext->makeCurrent();
		_openGl = DE_NEW(OpenGL)();
	}

	void initialiseViewport()
	{
		Int32 viewport[4];
		OpenGL::getIntegerv(OpenGL::VIEWPORT, viewport);
		DE_CHECK_ERROR_OPENGL();
		_viewport.setBounds(Rectangle(viewport[0], viewport[1], viewport[2], viewport[3]));
		setComponentState(ComponentID::Viewport, true);
	}

	void initialiseDrawing()
	{
		DE_ASSERT(_activeEffect != nullptr);
		DE_ASSERT(_activeVertexBufferState != nullptr);

		if(shouldUpdateComponent(ComponentID::Effect))
			initialiseEffectForDrawing();

		if(shouldUpdateComponent(ComponentID::VertexBufferState))
			initialiseVertexBufferStateForDrawing();

		if(shouldUpdateComponent(ComponentID::Viewport))
			initialiseViewportForDrawing();
	}

	void deinitialiseDrawing()
	{
		_activeVertexBufferState->_implementation->debind();
		setComponentState(ComponentID::VertexBufferState, false);
		Effect::Implementation::debind();
		setComponentState(ComponentID::Effect, false);
	}

	void setComponentState(const ComponentID& componentId, const Bool isUpToDate)
	{
		_componentStates.set(static_cast<Uint32>(componentId), isUpToDate);
	}

	Bool shouldUpdateComponent(const ComponentID& componentId) const
	{
		return !_componentStates.isSet(static_cast<Uint32>(componentId));
	}

	void initialiseEffectForDrawing()
	{
		_activeEffect->_implementation->bind();
		setComponentState(ComponentID::Effect, true);
	}

	void initialiseVertexBufferStateForDrawing()
	{
		_activeVertexBufferState->_implementation->bind();
		setComponentState(ComponentID::VertexBufferState, true);
	}

	void initialiseViewportForDrawing()
	{
		const Rectangle& bounds = _viewport.bounds();
		OpenGL::viewport(bounds.x, bounds.y, bounds.width, bounds.height);
		DE_CHECK_ERROR_OPENGL();
		setComponentState(ComponentID::Viewport, true);
	}
};


// Graphics::GraphicsDevice

// Public

void GraphicsDevice::bindBufferIndexed(GraphicsBuffer* buffer, const Uint32 bindingIndex) const
{
	_implementation->bindBufferIndexed(buffer, bindingIndex);
}

void GraphicsDevice::clear(const Colour& colour) const
{
	_implementation->clear(colour);
}

GraphicsBuffer* GraphicsDevice::createBuffer(const BufferBinding& binding, const Uint size,
	const AccessMode& accessMode, const BufferUsage& usage)
{
	GraphicsBuffer* buffer = _implementation->createBuffer(binding, size, accessMode, usage);
	_resources.push_back(buffer);

	return buffer;
}

Effect* GraphicsDevice::createEffect(EffectCode* effectCode)
{
	Shader* vertexShader = _implementation->createShader(ShaderType::Vertex, effectCode->vertexShaderCode());

	Shader* fragmentShader =
		_implementation->createShader(ShaderType::Fragment, effectCode->fragmentShaderCode());

	Effect* effect = _implementation->createEffect();
	effect->_implementation->attachShader(vertexShader);
	effect->_implementation->attachShader(fragmentShader);
	effect->_implementation->link();
	DE_DELETE(fragmentShader, Shader);
	DE_DELETE(vertexShader, Shader);
	_resources.push_back(effect);

	return effect;
}

IndexBuffer* GraphicsDevice::createIndexBuffer(const Uint size, const IndexType& indexType,
	const AccessMode& accessMode, const BufferUsage& usage)
{
	IndexBuffer* indexBuffer = _implementation->createIndexBuffer(size, indexType, accessMode, usage);
	_resources.push_back(indexBuffer);

	return indexBuffer;
}

VertexBufferState* GraphicsDevice::createVertexBufferState()
{
	VertexBufferState* vertexBufferState = _implementation->createVertexBufferState();
	_resources.push_back(vertexBufferState);

	return vertexBufferState;
}

void GraphicsDevice::debindBufferIndexed(GraphicsBuffer* buffer, const Uint32 bindingIndex) const
{
	_implementation->debindBufferIndexed(buffer, bindingIndex);
}

void GraphicsDevice::draw(const PrimitiveType& primitiveType, const Uint32 vertexCount,
	const Uint32 vertexOffset) const
{
	_implementation->draw(primitiveType, vertexCount, vertexOffset);
}

void GraphicsDevice::drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount,
	const Uint32 indexOffset) const
{
	_implementation->drawIndexed(primitiveType, indexCount, indexOffset);
}

void GraphicsDevice::setEffect(Effect* effect) const
{
	_implementation->setEffect(effect);
}

void GraphicsDevice::setVertexBufferState(VertexBufferState* vertexBufferState) const
{
	_implementation->setVertexBufferState(vertexBufferState);
}

void GraphicsDevice::setViewport(const Viewport& viewport) const
{
	_implementation->setViewport(viewport);
}

const Viewport& GraphicsDevice::viewport() const
{
	return _implementation->viewport();
}

void GraphicsDevice::swapBuffers() const
{
	_implementation->swapBuffers();
}

// Private

GraphicsDevice::GraphicsDevice(GraphicsContext* graphicsContext)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(graphicsContext);
}

GraphicsDevice::~GraphicsDevice()
{
	destroyResources();
	DE_DELETE(_implementation, Implementation);
}
