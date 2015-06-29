/**
 * @file core/Rectangle.h
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

namespace Core
{
	class Rectangle final
	{
	public:

		Uint32 height;

		Uint32 width;

		Int32 x;

		Int32 y;

		Rectangle() = default;

		Rectangle(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height);

		Rectangle(const Rectangle& rectangle) = default;

		Rectangle(Rectangle&& rectangle) = default;

		~Rectangle() = default;

		inline Int32 bottom() const;

		inline Int32 left() const;

		inline Int32 right() const;

		inline Int32 top() const;

		Rectangle& operator =(const Rectangle& rectangle) = default;

		Rectangle& operator =(Rectangle&& rectangle) = default;
	};

#include "inline/Rectangle.inl"
}
