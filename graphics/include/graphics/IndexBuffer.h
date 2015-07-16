/**
 * @file graphics/IndexBuffer.h
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

#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsEnumerations.h>

namespace Graphics
{
	enum class AccessMode;

	class IndexBuffer final : public GraphicsBuffer
	{
	public:

		IndexBuffer(const IndexBuffer& indexBuffer) = delete;
		IndexBuffer(IndexBuffer&& indexBuffer) = delete;

		inline IndexType indexType() const;

		IndexBuffer& operator =(const IndexBuffer& indexBuffer) = delete;
		IndexBuffer& operator =(IndexBuffer&& indexBuffer) = delete;

	private:

		friend class GraphicsDevice;

		using Base = GraphicsBuffer;

		IndexType _indexType;

		IndexBuffer(const Uint32 size, const IndexType& indexType, const AccessMode& accessMode);
		~IndexBuffer() = default;
	};

#include "inline/IndexBuffer.inl"
}
