/**
 * @file core/maths/Vector4.h
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
#include <core/maths/Vector3.h>

namespace Maths
{
	class Vector4 final
	{
	public:
		
		static const Vector4 UNIT_X;
		
		static const Vector4 UNIT_Y;
		
		static const Vector4 UNIT_Z;

		static const Vector4 UNIT_W;
		
		static const Vector4 ZERO;

		Float32 x;

		Float32 y;

		Float32 z;

		Float32 w;

		Vector4() = default;

		explicit Vector4(const Float32 value);

		Vector4(const Float32 x, const Float32 y, const Float32 z, const Float32 w);

		Vector4(const Vector2& vector2, const Float32 z, const Float32 w);

		Vector4(const Vector3& vector3, const Float32 w);

		Vector4(const Vector4& vector) = default;

		Vector4(Vector4&& vector) = default;

		~Vector4() = default;

		inline Float32 length() const;

		inline Vector4 normal() const;

		inline void normalise();

		inline Vector3 xyz() const;

		Vector4& operator =(const Vector4& vector) = default;

		Vector4& operator =(Vector4&& vector) = default;

		inline Vector4 operator -() const;

		Vector4& operator +=(const Vector4& vector);

		Vector4& operator +=(const Float32 scalar);

		Vector4& operator -=(const Vector4& vector);

		Vector4& operator -=(const Float32 scalar);

		Vector4& operator *=(const Vector4& vector);

		Vector4& operator *=(const Float32 scalar);

		Vector4& operator /=(const Vector4& vector);

		Vector4& operator /=(const Float32 scalar);

		inline Float32& operator [](const Uint32 index);

		inline const Float32& operator [](const Uint32 index) const;

		static inline Float32 distance(const Vector4& vectorA, const Vector4& vectorB);

		static inline Float32 dot(const Vector4& vectorA, const Vector4& vectorB);

		static inline Vector4 lerp(const Vector4& vectorA, const Vector4& vectorB, const Float32 weight);

		static Vector4 maximum(const Vector4& vectorA, const Vector4& vectorB);

		static Vector4 minimum(const Vector4& vectorA, const Vector4& vectorB);
	};

	inline Vector4 operator +(Vector4 vectorA, const Vector4& vectorB);

	inline Vector4 operator +(Vector4 vector, const Float32 scalar);

	inline Vector4 operator +(const Float32 scalar, Vector4 vector);

	inline Vector4 operator -(Vector4 vectorA, const Vector4& vectorB);

	inline Vector4 operator -(Vector4 vector, const Float32 scalar);

	inline Vector4 operator *(Vector4 vectorA, const Vector4& vectorB);

	inline Vector4 operator *(Vector4 vector, const Float32 scalar);

	inline Vector4 operator *(const Float32 scalar, Vector4 vector);

	inline Vector4 operator /(Vector4 vectorA, const Vector4& vectorB);

	inline Vector4 operator /(Vector4 vector, const Float32 scalar);

	inline Bool operator ==(const Vector4& vectorA, const Vector4& vectorB);

	inline Bool operator !=(const Vector4& vectorA, const Vector4& vectorB);

#include "inline/Vector4.inl"
}
