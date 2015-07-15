/**
 * @file graphics/VertexElement.h
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

namespace Graphics
{
	// TODO: support packed types
	enum class VertexElementType
	{
		Float16,
		Float32,
		Float64,
		Int8,
		Int16,
		Int32,
		Uint8,
		Uint16,
		Uint32
	};

	struct VertexElement final
	{
		Uint32 componentCount;
		Uint32 index;
		Uint32 offset;
		Uint32 slot;
		VertexElementType type;
		Bool normalise;

		VertexElement(const Uint32 index, const Uint32 slot, const Uint32 componentCount,
			const VertexElementType& type, const Bool normalise, const Uint32 offset = 0u)
			: index(index),
			  slot(slot),
			  componentCount(componentCount),
			  type(type),
			  normalise(normalise),
			  offset(offset) { }  
	};
}
