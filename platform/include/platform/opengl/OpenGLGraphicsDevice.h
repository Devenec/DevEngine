/**
 * @file platform/opengl/OpenGLGraphicsDevice.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#pragma once

#include <graphics/GraphicsDevice.h>
#include <graphics/Viewport.h>

namespace Platform
{
	class GraphicsContext;
	class OpenGL;
}

namespace Graphics
{
	class GraphicsDevice::Impl final
	{
	public:

		Impl(Platform::GraphicsContext* graphicsContext);

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl();

		void clear(const Colour& colour) const;
		
		GraphicsBuffer* createBuffer(const Uint32 binding, const Uint32 size, const AccessMode& accessMode) const;

		Effect* createEffect() const;

		IndexBuffer* createIndexBuffer(const Uint32 size, const IndexType& indexType, const AccessMode& accessMode)
			const;

		Shader* createShader(const ShaderType& type, const Core::String8& source) const;

		VertexBufferState* createVertexBufferState() const;

		void draw(const PrimitiveType& primitiveType, const Uint32 vertexCount, const Uint32 vertexOffset) const;

		void drawIndexed(const PrimitiveType& primitiveType, const Uint32 indexCount, const Uint32 indexOffset) const;

		inline void setEffect(Effect* effect);

		inline void setVertexBufferState(VertexBufferState* vertexBufferState);

		void setViewport(const Viewport& viewport);

		void swapBuffers() const;

		inline const Viewport& viewport() const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

	private:

		Viewport _viewport;
		Effect* _activeEffect;
		Platform::GraphicsContext* _graphicsContext;
		VertexBufferState* _activeVertexBufferState;
		Platform::OpenGL* _openGL;

		void initialiseOpenGL();
		void initialiseViewport();
		void initialiseDrawing() const;
		void deinitialiseDrawing() const;
	};

#include "inline/OpenGLGraphicsDevice.inl"
}
