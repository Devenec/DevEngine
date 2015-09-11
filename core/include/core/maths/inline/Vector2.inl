/**
 * @file maths/inline/Vector2.inl
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

// Public

Float32 Vector2::length() const
{
	return squareRoot(x * x + y * y);
}

void Vector2::normalise()
{
	operator /=(length());
}

// Operators

Vector2 Vector2::operator -() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator +=(const Vector2& vector)
{
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector2& Vector2::operator +=(const Float32 scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2& Vector2::operator -=(const Vector2& vector)
{
	x -= vector.x;
	y -= vector.y;

	return *this;
}

Vector2& Vector2::operator -=(const Float32 scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator *=(const Vector2& vector)
{
	x *= vector.x;
	y *= vector.y;

	return *this;
}

Vector2& Vector2::operator *=(const Float32 scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator /=(const Vector2& vector)
{
	DE_ASSERT(vector.x != 0.0f && vector.y != 0.0f);
	x /= vector.x;
	y /= vector.y;

	return *this;
}

Vector2& Vector2::operator /=(const Float32 scalar)
{
	DE_ASSERT(scalar != 0.0f);
	x /= scalar;
	y /= scalar;

	return *this;
}

Float32& Vector2::operator [](const Uint32 index)
{
	DE_ASSERT(index < 2u);
	return (&x)[index];
}

const Float32& Vector2::operator [](const Uint32 index) const
{
	DE_ASSERT(index < 2u);
	return (&x)[index];
}

// Static

Float32 Vector2::distance(const Vector2& vectorA, const Vector2& vectorB)
{
	return (vectorB - vectorA).length();
}

Float32 Vector2::dot(const Vector2& vectorA, const Vector2& vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y;
}

Vector2 Vector2::lerp(const Vector2& vectorA, const Vector2& vectorB, const Float32 weight)
{
	return weight * (vectorB - vectorA) + vectorA;
}

Vector2 Vector2::maximum(const Vector2& vectorA, const Vector2& vectorB)
{
	return Vector2
	(
		Maths::maximum(vectorA.x, vectorB.x),
		Maths::maximum(vectorA.y, vectorB.y)
	);
}

Vector2 Vector2::minimum(const Vector2& vectorA, const Vector2& vectorB)
{
	return Vector2
	(
		Maths::minimum(vectorA.x, vectorB.x),
		Maths::minimum(vectorA.y, vectorB.y)
	);
}

Vector2 Vector2::normal(Vector2 vector)
{
	vector.normalise();
	return vector;
}


// Maths

Vector2 operator +(Vector2 vectorA, const Vector2& vectorB)
{
	vectorA += vectorB;
	return vectorA;
}

Vector2 operator +(Vector2 vector, const Float32 scalar)
{
	vector += scalar;
	return vector;
}

Vector2 operator +(const Float32 scalar, Vector2 vector)
{
	vector += scalar;
	return vector;
}

Vector2 operator -(Vector2 vectorA, const Vector2& vectorB)
{
	vectorA -= vectorB;
	return vectorA;
}

Vector2 operator -(Vector2 vector, const Float32 scalar)
{
	vector -= scalar;
	return vector;
}

Vector2 operator *(Vector2 vectorA, const Vector2& vectorB)
{
	vectorA *= vectorB;
	return vectorA;
}

Vector2 operator *(Vector2 vector, const Float32 scalar)
{
	vector *= scalar;
	return vector;
}

Vector2 operator *(const Float32 scalar, Vector2 vector)
{
	vector *= scalar;
	return vector;
}

Vector2 operator /(Vector2 vectorA, const Vector2& vectorB)
{
	vectorA /= vectorB;
	return vectorA;
}

Vector2 operator /(Vector2 vector, const Float32 scalar)
{
	vector /= scalar;
	return vector;
}

Bool operator ==(const Vector2& vectorA, const Vector2& vectorB)
{
	return vectorA.x == vectorB.x && vectorA.y == vectorB.y;
}

Bool operator !=(const Vector2& vectorA, const Vector2& vectorB)
{
	return !(vectorA == vectorB);
}
