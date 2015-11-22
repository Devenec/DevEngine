/**
 * @file graphics/Colour.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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
#include <core/Numeric.h>

namespace Graphics
{
	class Colour
	{
	public:

		Float32 alpha;

		Float32 blue;

		Float32 green;

		Float32 red;

		Colour() = default;

		Colour(const Float32 red, const Float32 green, const Float32 blue, const Float32 alpha = 1.0f);

		Colour(const Uint8 red, const Uint8 green, const Uint8 blue,
			const Uint8 alpha = Core::Numeric<Uint8>::maximum());

		Colour(const Colour& colour) = default;

		Colour(Colour&& colour) = default;

		~Colour() = default;

		Colour& operator =(const Colour& colour) = default;

		Colour& operator =(Colour&& colour) = default;
	};
}
