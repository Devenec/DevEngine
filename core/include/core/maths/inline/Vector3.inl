/**
 * @file maths/inline/Vector3.inl
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

Float32 Vector3::length() const
{
	return squareRoot(x * x + y * y + z * z);
}

void Vector3::normalise()
{
	operator /=(length());
}

Vector2 Vector3::xy() const
{
	return Vector2(x, y);
}

// Operators

Vector3 Vector3::operator -() const
{
	return Vector3(-x, -y, -z);
}

Float32& Vector3::operator [](const Uint32 index)
{
	DE_ASSERT(index < 3u);
	return (&x)[index];
}

const Float32& Vector3::operator [](const Uint32 index) const
{
	DE_ASSERT(index < 3u);
	return (&x)[index];
}

// Static

Float32 Vector3::distance(const Vector3& vectorA, const Vector3& vectorB)
{
	return (vectorB - vectorA).length();
}

Float32 Vector3::dot(const Vector3& vectorA, const Vector3& vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

Vector3 Vector3::lerp(const Vector3& vectorA, const Vector3& vectorB, const Float32 weight)
{
	return weight * (vectorB - vectorA) + vectorA;
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

Vector3 Vector3::normal(Vector3 vector)
{
	vector.normalise();
	return vector;
}


// Maths

Vector3 operator +(Vector3 vectorA, const Vector3& vectorB)
{
	vectorA += vectorB;
	return vectorA;
}

Vector3 operator +(Vector3 vector, const Float32 scalar)
{
	vector += scalar;
	return vector;
}

Vector3 operator +(const Float32 scalar, Vector3 vector)
{
	vector += scalar;
	return vector;
}

Vector3 operator -(Vector3 vectorA, const Vector3& vectorB)
{
	vectorA -= vectorB;
	return vectorA;
}

Vector3 operator -(Vector3 vector, const Float32 scalar)
{
	vector -= scalar;
	return vector;
}

Vector3 operator *(Vector3 vectorA, const Vector3& vectorB)
{
	vectorA *= vectorB;
	return vectorA;
}

Vector3 operator *(Vector3 vector, const Float32 scalar)
{
	vector *= scalar;
	return vector;
}

Vector3 operator *(const Float32 scalar, Vector3 vector)
{
	vector *= scalar;
	return vector;
}

Vector3 operator /(Vector3 vectorA, const Vector3& vectorB)
{
	vectorA /= vectorB;
	return vectorA;
}

Vector3 operator /(Vector3 vector, const Float32 scalar)
{
	vector /= scalar;
	return vector;
}

Bool operator ==(const Vector3& vectorA, const Vector3& vectorB)
{
	return vectorA.x == vectorB.x && vectorA.y == vectorB.y && vectorA.z == vectorB.z;
}

Bool operator !=(const Vector3& vectorA, const Vector3& vectorB)
{
	return !(vectorA == vectorB);
}
