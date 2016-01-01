/**
 * @file core/maths/Vector3.h
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
#include <core/maths/Vector2.h>

namespace Maths
{
	class Vector3 final
	{
	public:

		static const Vector3 BACKWARD;
		
		static const Vector3 DOWN;

		static const Vector3 FORWARD;
		
		static const Vector3 LEFT;
		
		static const Vector3 RIGHT;
		
		static const Vector3 UNIT_X;
		
		static const Vector3 UNIT_Y;
		
		static const Vector3 UNIT_Z;

		static const Vector3 UP;
		
		static const Vector3 ZERO;

		Float32 x;

		Float32 y;

		Float32 z;

		Vector3() = default;

		explicit Vector3(const Float32 value);

		Vector3(const Float32 x, const Float32 y, const Float32 z);

		Vector3(const Vector2& vector2, const Float32 z);

		Vector3(const Vector3& vector) = default;

		Vector3(Vector3&& vector) = default;

		~Vector3() = default;

		inline Float32 length() const;

		inline Vector3 normal() const;

		inline void normalise();

		inline Vector2 xy() const;

		Vector3& operator =(const Vector3& vector) = default;

		Vector3& operator =(Vector3&& vector) = default;

		inline Vector3 operator -() const;

		Vector3& operator +=(const Vector3& vector);

		Vector3& operator +=(const Float32 scalar);

		Vector3& operator -=(const Vector3& vector);

		Vector3& operator -=(const Float32 scalar);

		Vector3& operator *=(const Vector3& vector);

		Vector3& operator *=(const Float32 scalar);

		Vector3& operator /=(const Vector3& vector);

		Vector3& operator /=(const Float32 scalar);

		inline Float32& operator [](const Uint32 index);

		inline const Float32& operator [](const Uint32 index) const;

		static Vector3 cross(const Vector3& vectorA, const Vector3& vectorB);

		static inline Float32 distance(const Vector3& vectorA, const Vector3& vectorB);

		static inline Float32 dot(const Vector3& vectorA, const Vector3& vectorB);

		static inline Vector3 lerp(const Vector3& vectorA, const Vector3& vectorB, const Float32 weight);

		static Vector3 maximum(const Vector3& vectorA, const Vector3& vectorB);

		static Vector3 minimum(const Vector3& vectorA, const Vector3& vectorB);
	};

	inline Vector3 operator +(Vector3 vectorA, const Vector3& vectorB);

	inline Vector3 operator +(Vector3 vector, const Float32 scalar);

	inline Vector3 operator +(const Float32 scalar, Vector3 vector);

	inline Vector3 operator -(Vector3 vectorA, const Vector3& vectorB);

	inline Vector3 operator -(Vector3 vector, const Float32 scalar);

	inline Vector3 operator *(Vector3 vectorA, const Vector3& vectorB);

	inline Vector3 operator *(Vector3 vector, const Float32 scalar);

	inline Vector3 operator *(const Float32 scalar, Vector3 vector);

	inline Vector3 operator /(Vector3 vectorA, const Vector3& vectorB);

	inline Vector3 operator /(Vector3 vector, const Float32 scalar);

	inline Bool operator ==(const Vector3& vectorA, const Vector3& vectorB);

	inline Bool operator !=(const Vector3& vectorA, const Vector3& vectorB);

#include "inline/Vector3.inl"
}
