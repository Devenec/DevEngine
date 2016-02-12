/**
 * @file graphics/IndexBuffer.h
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
#include <graphics/GraphicsResource.h>

namespace Graphics
{
	enum class AccessMode;
	enum class BufferUsage;
	enum class IndexType;

	class IndexBuffer final : public GraphicsResource
	{
	public:

		IndexBuffer(const IndexBuffer& indexBuffer) = delete;
		IndexBuffer(IndexBuffer&& indexBuffer) = delete;

		void demapData() const;

		inline IndexType indexType() const;

		Uint8* mapData() const;

		Uint8* mapData(const Uint size, const Uint offset = 0u) const;

		IndexBuffer& operator =(const IndexBuffer& indexBuffer) = delete;
		IndexBuffer& operator =(IndexBuffer&& indexBuffer) = delete;

	private:

		friend class GraphicsDevice;
		friend class VertexBufferState;

		class Implementation;

		Implementation* _implementation;
		IndexType _indexType;

		IndexBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const Uint size,
			const IndexType& indexType, const AccessMode& accessMode, const BufferUsage& usage);

		~IndexBuffer();
	};

#include "inline/IndexBuffer.inl"
}
