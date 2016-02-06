/**
 * @file graphics/VertexBufferState.h
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

#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/GraphicsResource.h>

namespace Graphics
{
	struct VertexElement;

	class GraphicsBuffer;
	class IndexBuffer;

	using VertexElementList = Core::Vector<VertexElement>;

	class VertexBufferState final : public GraphicsResource
	{
	public:

		VertexBufferState(const VertexBufferState& vertexBufferState) = delete;
		VertexBufferState(VertexBufferState&& vertexBufferState) = delete;

		void setIndexBuffer(IndexBuffer* buffer) const;

		void setVertexBuffer(const GraphicsBuffer* buffer, const VertexElementList& vertexElements,
			const Uint32 stride, const Uint offset = 0u) const;

		VertexBufferState& operator =(const VertexBufferState& vertexBufferState) = delete;
		VertexBufferState& operator =(VertexBufferState&& vertexBufferState) = delete;

	private:

		friend class GraphicsDevice;

		class Implementation;

		Implementation* _implementation;

		explicit VertexBufferState(GraphicsInterfaceHandle graphicsInterfaceHandle);
		~VertexBufferState();
	};
}
