/**
 * @file core/maths/Vector3.cpp
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

#include <core/maths/Vector3.h>

using namespace Maths;

// Public

const Vector3 Vector3::BACKWARD = Vector3(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::DOWN		= Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::FORWARD	= Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::LEFT		= Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::RIGHT	= Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X	= Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y	= Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z	= Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UP		= Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZERO		= Vector3(0.0f, 0.0f, 0.0f);

Vector3::Vector3(const Float32 value)
	: Vector3(value, value, value) { }

Vector3::Vector3(const Float32 x, const Float32 y, const Float32 z)
	: x(x),
	  y(y),
	  z(z) { }

Vector3::Vector3(const Vector2& vector2, const Float32 z)
	: Vector3(vector2.x, vector2.y, z) { }

// Operators

Vector3& Vector3::operator +=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3& Vector3::operator +=(const Float32 scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;

	return *this;
}

Vector3& Vector3::operator -=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3& Vector3::operator -=(const Float32 scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;

	return *this;
}

Vector3& Vector3::operator *=(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;

	return *this;
}

Vector3& Vector3::operator *=(const Float32 scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator /=(const Vector3& vector)
{
	DE_ASSERT(vector.x != 0.0f && vector.y != 0.0f && vector.z != 0.0f);
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;

	return *this;
}

Vector3& Vector3::operator /=(const Float32 scalar)
{
	DE_ASSERT(scalar != 0.0f);
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

// Static

Vector3 Vector3::cross(const Vector3& vectorA, const Vector3& vectorB)
{
	return Vector3
	(
		vectorA.y * vectorB.z - vectorA.z * vectorB.y,
		vectorA.z * vectorB.x - vectorA.x * vectorB.z,
		vectorA.x * vectorB.y - vectorA.y * vectorB.x
	);
}

Vector3 Vector3::maximum(const Vector3& vectorA, const Vector3& vectorB)
{
	return Vector3
	(
		Maths::maximum(vectorA.x, vectorB.x),
		Maths::maximum(vectorA.y, vectorB.y),
		Maths::maximum(vectorA.z, vectorB.z)
	);
}

Vector3 Vector3::minimum(const Vector3& vectorA, const Vector3& vectorB)
{
	return Vector3
	(
		Maths::minimum(vectorA.x, vectorB.x),
		Maths::minimum(vectorA.y, vectorB.y),
		Maths::minimum(vectorA.z, vectorB.z)
	);
}
