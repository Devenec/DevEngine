/**
 * @file core/maths/Matrix4.h
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
#include <core/maths/Vector3.h>
#include <core/maths/Vector4.h>

namespace Maths
{
	class Angle;

	class Matrix4 final
	{
	public:

		static const Matrix4 IDENTITY;

		Matrix4() = default;

		Matrix4(const Float32 e00, const Float32 e01, const Float32 e02, const Float32 e03,
			const Float32 e10, const Float32 e11, const Float32 e12, const Float32 e13,
			const Float32 e20, const Float32 e21, const Float32 e22, const Float32 e23,
			const Float32 e30, const Float32 e31, const Float32 e32, const Float32 e33);

		Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3);

		Matrix4(const Matrix4& matrix) = default;

		Matrix4(Matrix4&& matrix) = default;

		~Matrix4() = default;

		// TODO: decompose()

		Float32 determinant() const;

		inline const Float32* data() const;

		Matrix4 inverse() const;

		Matrix4 transpose() const;

		Matrix4& operator =(const Matrix4& matrix) = default;

		Matrix4& operator =(Matrix4&& matrix) = default;

		inline Matrix4 operator -() const;

		Matrix4& operator +=(const Matrix4& matrix);

		Matrix4& operator -=(const Matrix4& matrix);

		Matrix4& operator *=(const Matrix4& matrix);

		Matrix4& operator *=(const Float32 scalar);

		Matrix4& operator /=(const Float32 scalar);

		inline Vector4& operator [](const Uint32 index);

		inline const Vector4& operator [](const Uint32 index) const;

		static Matrix4 createRotation(const Vector3& axis, const Angle& angle);

		static Matrix4 createRotationX(const Angle& angle);

		static Matrix4 createRotationY(const Angle& angle);

		static Matrix4 createRotationZ(const Angle& angle);

		static Matrix4 createTranslation(const Float32 x, const Float32 y, const Float32 z);

		static inline Matrix4 createTranslation(const Vector3& translation);

	private:

		Vector4 _columns[4];
	};

	inline Matrix4 operator +(Matrix4 matrixA, const Matrix4& matrixB);

	inline Matrix4 operator -(Matrix4 matrixA, const Matrix4& matrixB);

	inline Matrix4 operator *(Matrix4 matrixA, const Matrix4& matrixB);

	inline Matrix4 operator *(Matrix4 matrix, const Float32 scalar);

	inline Matrix4 operator *(const Float32 scalar, Matrix4 matrix);

	inline Matrix4 operator /(Matrix4 matrix, const Float32 scalar);

	inline Bool operator ==(const Matrix4& matrixA, const Matrix4& matrixB);

	inline Bool operator !=(const Matrix4& matrixA, const Matrix4& matrixB);

#include "inline/Matrix4.inl"
}
