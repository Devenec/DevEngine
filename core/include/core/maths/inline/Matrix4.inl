/**
 * @file core/maths/inline/Matrix4.inl
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

const Float32* Matrix4::data() const
{
	return &_columns[0][0];
}

// Operators

Matrix4 Matrix4::operator -() const
{
	return Matrix4(-_columns[0], -_columns[1], -_columns[2], -_columns[3]);
}

Vector4& Matrix4::operator [](const Uint32 index)
{
	DE_ASSERT(index < 4u);
	return _columns[index];
}

const Vector4& Matrix4::operator [](const Uint32 index) const
{
	DE_ASSERT(index < 4u);
	return _columns[index];
}

// Static

Matrix4 Matrix4::createTranslation(const Vector3& translation)
{
	return createTranslation(translation.x, translation.y, translation.z);
}


// Maths

Matrix4 operator +(Matrix4 matrixA, const Matrix4& matrixB)
{
	matrixA += matrixB;
	return matrixA;
}

Matrix4 operator -(Matrix4 matrixA, const Matrix4& matrixB)
{
	matrixA -= matrixB;
	return matrixA;
}

Matrix4 operator *(Matrix4 matrixA, const Matrix4& matrixB)
{
	matrixA *= matrixB;
	return matrixA;
}

Matrix4 operator *(Matrix4 matrix, const Float32 scalar)
{
	matrix *= scalar;
	return matrix;
}

Matrix4 operator *(const Float32 scalar, Matrix4 matrix)
{
	matrix *= scalar;
	return matrix;
}

Matrix4 operator /(Matrix4 matrix, const Float32 scalar)
{
	matrix /= scalar;
	return matrix;
}

Bool operator ==(const Matrix4& matrixA, const Matrix4& matrixB)
{
	return matrixA[0] == matrixB[0] && matrixA[1] == matrixB[1] && matrixA[2] == matrixB[2] &&
		matrixA[3] == matrixB[3];
}

Bool operator !=(const Matrix4& matrixA, const Matrix4& matrixB)
{
	return !(matrixA == matrixB);
}
