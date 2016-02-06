/**
 * @file core/maths/Vector2.h
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
#include <core/debug/Assert.h>
#include <core/maths/Utility.h>

namespace Maths
{
	class Vector2 final
	{
	public:

		static const Vector2 UNIT_X;

		static const Vector2 UNIT_Y;

		static const Vector2 ZERO;

		Float32 x;

		Float32 y;

		Vector2() = default;

		explicit Vector2(const Float32 value);

		Vector2(const Float32 x, const Float32 y);

		Vector2(const Vector2& vector) = default;

		Vector2(Vector2&& vector) = default;

		~Vector2() = default;

		inline Float32 length() const;

		inline Vector2 normal() const;

		inline void normalise();

		Vector2& operator =(const Vector2& vector) = default;

		Vector2& operator =(Vector2&& vector) = default;

		inline Vector2 operator -() const;

		inline Vector2& operator +=(const Vector2& vector);

		inline Vector2& operator +=(const Float32 scalar);

		inline Vector2& operator -=(const Vector2& vector);

		inline Vector2& operator -=(const Float32 scalar);

		inline Vector2& operator *=(const Vector2& vector);

		inline Vector2& operator *=(const Float32 scalar);

		inline Vector2& operator /=(const Vector2& vector);

		inline Vector2& operator /=(const Float32 scalar);

		inline Float32& operator [](const Uint32 index);

		inline const Float32& operator [](const Uint32 index) const;

		static inline Float32 distance(const Vector2& vectorA, const Vector2& vectorB);

		static inline Float32 dot(const Vector2& vectorA, const Vector2& vectorB);

		static inline Vector2 lerp(const Vector2& vectorA, const Vector2& vectorB, const Float32 weight);

		static inline Vector2 maximum(const Vector2& vectorA, const Vector2& vectorB);

		static inline Vector2 minimum(const Vector2& vectorA, const Vector2& vectorB);
	};

	inline Vector2 operator +(Vector2 vectorA, const Vector2& vectorB);

	inline Vector2 operator +(Vector2 vector, const Float32 scalar);

	inline Vector2 operator +(const Float32 scalar, Vector2 vector);

	inline Vector2 operator -(Vector2 vectorA, const Vector2& vectorB);

	inline Vector2 operator -(Vector2 vector, const Float32 scalar);

	inline Vector2 operator *(Vector2 vectorA, const Vector2& vectorB);

	inline Vector2 operator *(Vector2 vector, const Float32 scalar);

	inline Vector2 operator *(const Float32 scalar, Vector2 vector);

	inline Vector2 operator /(Vector2 vectorA, const Vector2& vectorB);

	inline Vector2 operator /(Vector2 vector, const Float32 scalar);

	inline Bool operator ==(const Vector2& vectorA, const Vector2& vectorB);

	inline Bool operator !=(const Vector2& vectorA, const Vector2& vectorB);

#include "inline/Vector2.inl"
}
