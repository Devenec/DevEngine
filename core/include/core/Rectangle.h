/**
 * @file core/Rectangle.h
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

namespace Core
{
	class Rectangle final
	{
	public:

		/**
		 * The x position of the upper-left corner of the rectangle
		 */
		Int32 x;

		/**
		 * The y position of the upper-left corner of the rectangle
		 */
		Int32 y;

		/**
		 * The width of the rectangle
		 *
		 * Using a negative width is undefined.
		 */
		Int32 width;

		/**
		 * The height of the rectangle
		 *
		 * Using a negative height is undefined.
		 */
		Int32 height;

		Rectangle() = default;

		Rectangle(const Int32 x, const Int32 y, const Int32 width, const Int32 height);

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
