/**
 * @file graphics/Colour.cpp
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

#include <graphics/Colour.h>

using namespace Core;
using namespace Graphics;

// Public

Colour::Colour(const Float32 red, const Float32 green, const Float32 blue, const Float32 alpha)
	: alpha(alpha),
	  blue(blue),
	  green(green),
	  red(red) { }

Colour::Colour(const Uint8 red, const Uint8 green, const Uint8 blue, const Uint8 alpha)
	: alpha(static_cast<Float32>(alpha) / Numeric<Uint8>::maximum()),
	  blue(static_cast<Float32>(blue) / Numeric<Uint8>::maximum()),
	  green(static_cast<Float32>(green) / Numeric<Uint8>::maximum()),
	  red(static_cast<Float32>(red) / Numeric<Uint8>::maximum()) { }
