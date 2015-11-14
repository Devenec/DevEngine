/**
 * @file core/maths/Utility.h
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

#include <cmath>
#include <cstdlib>
#include <core/Types.h>
#include <core/debug/Assert.h>

namespace Maths
{
	// TODO: add safe comparisons between 1) Float32 and Float32, 2) Float32 and 0

	const Float32 PI = 3.1415926535897932f;

	const Float32 TO_DEGREES = 180.0f / PI;

	const Float32 TO_RADIANS = PI / 180.0f;

	inline Int32 absolute(const Int32 value);

	inline Float32 absolute(const Float32 value);

	inline Float32 arcCosine(const Float32 value);

	inline Float32 arcSine(const Float32 value);

	inline Float32 arcTangent(const Float32 value);

	inline Float32 arcTangentAngle(const Float32 y, const Float32 x);

	inline Float32 ceiling(const Float32 value);

	inline Int32 clamp(const Int32 value, const Int32 min, const Int32 max);

	inline Uint32 clamp(const Uint32 value, const Uint32 min, const Uint32 max);

	inline Float32 clamp(const Float32 value, const Float32 min, const Float32 max);

	inline Float32 cosine(const Float32 value);

	inline Float32 floor(const Float32 value);

	inline Float32 lerp(const Float32 valueA, const Float32 valueB, const Float32 weight);

	inline Int32 maximum(const Int32 valueA, const Int32 valueB);

	inline Uint32 maximum(const Uint32 valueA, const Uint32 valueB);

	inline Float32 maximum(const Float32 valueA, const Float32 valueB);

	inline Int32 minimum(const Int32 valueA, const Int32 valueB);

	inline Uint32 minimum(const Uint32 valueA, const Uint32 valueB);

	inline Float32 minimum(const Float32 valueA, const Float32 valueB);

	inline Float32 power(const Float32 base, const Float32 exponent);

	inline Float32 round(const Float32 value);

	inline Float32 squareRoot(const Float32 value);

	inline Int32 sign(const Int32 value);

	inline Float32 sign(const Float32 value);

	inline Float32 sine(const Float32 value);

	inline Float32 tangent(const Float32 value);

	inline Float32 toDegrees(const Float32 angle);

	inline Float32 toRadians(const Float32 angle);

	inline Float32 wrapAngle(const Float32 angle);

#include "inline/Utility.inl"
}
