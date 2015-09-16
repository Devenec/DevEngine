/**
 * @file graphics/VertexBufferState.h
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

#pragma once

#include <core/InitialiserList.h>
#include <core/Types.h>
#include <graphics/GraphicsResource.h>

namespace Graphics
{
	struct VertexElement;

	class GraphicsBuffer;
	class IndexBuffer;

	class VertexBufferState final : public GraphicsResource
	{
	public:

		VertexBufferState(const VertexBufferState& vertexBufferState) = delete;
		VertexBufferState(VertexBufferState&& vertexBufferState) = delete;

		void bind() const;

		void debind() const;

		IndexBuffer* indexBuffer() const;

		void setIndexBuffer(IndexBuffer* buffer) const;

		void setVertexBuffer(const GraphicsBuffer* buffer, const Uint32 bufferIndex, const Uint32 stride,
			const Uint32 offset = 0u) const;

		void setVertexLayout(const Core::InitialiserList<VertexElement>& vertexElements) const;

		VertexBufferState& operator =(const VertexBufferState& vertexBufferState) = delete;
		VertexBufferState& operator =(VertexBufferState&& vertexBufferState) = delete;

	private:

		friend class GraphicsDevice;

		class Impl;

		Impl* _impl;

		VertexBufferState();
		~VertexBufferState();
	};
}
