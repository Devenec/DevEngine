/**
 * @file graphics/UniformBuffer.h
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

#include <core/Types.h>
#include <graphics/GraphicsBuffer.h>

namespace Graphics
{
	class UniformBuffer final : public GraphicsBuffer
	{
	public:

		UniformBuffer(const UniformBuffer& uniformBuffer) = delete;
		UniformBuffer(UniformBuffer&& uniformBuffer) = delete;

		void bind(const Uint32 bindingIndex) const;

		void debind(const Uint32 bindingIndex) const;

		UniformBuffer& operator =(const UniformBuffer& uniformBuffer) = delete;
		UniformBuffer& operator =(UniformBuffer&& uniformBuffer) = delete;

	private:

		friend class GraphicsDevice;

		using Base = GraphicsBuffer;

		UniformBuffer(const Uint32 size, const AccessMode& accessMode);
		~UniformBuffer() = default;
	};
}
