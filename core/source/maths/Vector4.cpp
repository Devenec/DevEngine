/**
 * @file core/maths/Vector4.cpp
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

#include <core/maths/Vector4.h>

using namespace Maths;

// Public

const Vector4 Vector4::UNIT_X = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UNIT_W = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
const Vector4 Vector4::ZERO	  = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

Vector4::Vector4(const Float32 value)
	: Vector4(value, value, value, value) { }

Vector4::Vector4(const Float32 x, const Float32 y, const Float32 z, const Float32 w)
	: x(x),
	  y(y),
	  z(z),
	  w(w) { }

Vector4::Vector4(const Vector2& vector2, const Float32 z, const Float32 w)
	: Vector4(vector2.x, vector2.y, z, w) { }

Vector4::Vector4(const Vector3& vector3, const Float32 w)
	: Vector4(vector3.x, vector3.y, vector3.z, w) { }

Vector4& Vector4::operator +=(const Vector4& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

Vector4& Vector4::operator +=(const Float32 scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;

	return *this;
}

Vector4& Vector4::operator -=(const Vector4& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

Vector4& Vector4::operator -=(const Float32 scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;

	return *this;
}

Vector4& Vector4::operator *=(const Vector4& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;

	return *this;
}

Vector4& Vector4::operator *=(const Float32 scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}

Vector4& Vector4::operator /=(const Vector4& vector)
{
	DE_ASSERT(vector.x != 0.0f && vector.y != 0.0f && vector.z != 0.0f && vector.w != 0.0f);
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;

	return *this;
}

Vector4& Vector4::operator /=(const Float32 scalar)
{
	DE_ASSERT(scalar != 0.0f);
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;

	return *this;
}

// Static

Vector4 Vector4::maximum(const Vector4& vectorA, const Vector4& vectorB)
{
	return Vector4
	(
		Maths::maximum(vectorA.x, vectorB.x),
		Maths::maximum(vectorA.y, vectorB.y),
		Maths::maximum(vectorA.z, vectorB.z),
		Maths::maximum(vectorA.w, vectorB.w)
	);
}

Vector4 Vector4::minimum(const Vector4& vectorA, const Vector4& vectorB)
{
	return Vector4
	(
		Maths::minimum(vectorA.x, vectorB.x),
		Maths::minimum(vectorA.y, vectorB.y),
		Maths::minimum(vectorA.z, vectorB.z),
		Maths::minimum(vectorA.w, vectorB.w)
	);
}
