/**
 * @file platform/opengl/OpenGLVertexBufferState.h
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

#pragma once

#include <graphics/VertexBufferState.h>

namespace Graphics
{
	class VertexBufferState::Implementation final
	{
	public:

		Implementation();

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		inline void bind() const;

		inline void debind() const;

		inline IndexBuffer* indexBuffer() const;

		void setIndexBuffer(IndexBuffer* buffer);

		void setVertexBuffer(const GraphicsBuffer* buffer, const VertexElementList& vertexElements,
			const Uint32 stride, const Uint offset) const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		IndexBuffer* _indexBuffer;
		Uint32 _vertexArrayHandle;

		void bind(const Uint32 vertexArrayHandle) const;

		void setVertexLayout(const VertexElementList& vertexElements, const Uint32 stride,
			const Uint bufferOffset) const;

		void setVertexElementFormat(const VertexElement& element, const Uint elementOffset,
			const Uint32 stride) const;
	};

#include "inline/OpenGLVertexBufferState.inl"
}
