/**
 * @file core/maths/Vector2.cpp
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

#include <core/maths/Vector2.h>

using namespace Maths;

// Public

const Vector2 Vector2::UNIT_X = Vector2(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y = Vector2(0.0f, 1.0f);
const Vector2 Vector2::ZERO	  = Vector2(0.0f, 0.0f);

Vector2::Vector2(const Float32 value)
	: Vector2(value, value) { }

Vector2::Vector2(const Float32 x, const Float32 y)
	: x(x),
	  y(y) { }
