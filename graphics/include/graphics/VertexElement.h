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
#include <graphics/GraphicsEnumerations.h>

namespace Graphics
{
	struct VertexElement final
	{
		static const Uint32 AFTER_PREVIOUS = 0xFFFFFFFF;

		Uint32 index;
		Uint32 offset;
		VertexElementType type;
		Bool normalise;

		VertexElement(const Uint32 index, const VertexElementType& type, const Bool normalise = false,
			const Uint32 offset = AFTER_PREVIOUS)
			: index(index),
			  offset(offset),
			  type(type),
			  normalise(normalise) { }
	};
}
