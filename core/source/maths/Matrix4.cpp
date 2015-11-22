/**
 * @file core/maths/Matrix4.cpp
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

#include <core/maths/Angle.h>
#include <core/maths/Matrix4.h>
#include <core/maths/Utility.h>

using namespace Maths;

// Public

const Matrix4 Matrix4::IDENTITY = Matrix4
(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

Matrix4::Matrix4(const Float32 e00, const Float32 e01, const Float32 e02, const Float32 e03,
	const Float32 e10, const Float32 e11, const Float32 e12, const Float32 e13,
	const Float32 e20, const Float32 e21, const Float32 e22, const Float32 e23,
	const Float32 e30, const Float32 e31, const Float32 e32, const Float32 e33)
	: _columns { Vector4(e00, e01, e02, e03), Vector4(e10, e11, e12, e13), Vector4(e20, e21, e22, e23),
		  Vector4(e30, e31, e32, e33) } { }

Matrix4::Matrix4(const Vector4& column0, const Vector4& column1, const Vector4& column2, const Vector4& column3)
	: _columns { column0, column1, column2, column3 } { }

Float32 Matrix4::determinant() const
{
	const Float32& e10 = _columns[1][0];
	const Float32& e11 = _columns[1][1];
	const Float32& e12 = _columns[1][2];
	const Float32& e13 = _columns[1][3];
	const Float32& e20 = _columns[2][0];
	const Float32& e21 = _columns[2][1];
	const Float32& e22 = _columns[2][2];
	const Float32& e23 = _columns[2][3];
	const Float32& e30 = _columns[3][0];
	const Float32& e31 = _columns[3][1];
	const Float32& e32 = _columns[3][2];
	const Float32& e33 = _columns[3][3];

	return
		_columns[0][0] * (e11 * (e22 * e33 - e32 * e23) - e12 * (e21 * e33 - e31 * e23) +
			e13 * (e21 * e32 - e31 * e22)) -
		_columns[0][1] * (e10 * (e22 * e33 - e32 * e23) - e12 * (e20 * e33 - e30 * e23) +
			e13 * (e20 * e32 - e30 * e22)) +
		_columns[0][2] * (e10 * (e21 * e33 - e31 * e23) - e11 * (e20 * e33 - e30 * e23) +
			e13 * (e20 * e31 - e30 * e21)) -
		_columns[0][3] * (e10 * (e21 * e32 - e31 * e22) - e11 * (e20 * e32 - e30 * e22) +
			e12 * (e20 * e31 - e30 * e21));
}

Matrix4 Matrix4::inverse() const
{
	const Vector3 column0 = _columns[0].xyz();
	const Vector3 column1 = _columns[1].xyz();
	const Vector3 column2 = _columns[2].xyz();
	const Vector3 column3 = _columns[3].xyz();
	const Vector3 cross = Vector3::cross(column1, column2);
	const Float32 oneOverDeterminant = 1.0f / Vector3::dot(column0, cross);
	const Vector3 row0 = oneOverDeterminant * cross;
	const Vector3 row1 = oneOverDeterminant * Vector3::cross(column2, column0);
	const Vector3 row2 = oneOverDeterminant * Vector3::cross(column0, column1);

	return Matrix4
	(
		 row0[0],					   row1[0],						 row2[0],					  0.0f,
		 row0[1],					   row1[1],						 row2[1],					  0.0f,
		 row0[2],					   row1[2],						 row2[2],					  0.0f,
		-Vector3::dot(row0, column3), -Vector3::dot(row1, column3), -Vector3::dot(row2, column3), 1.0f
	);
}

Matrix4 Matrix4::transpose() const
{
	return Matrix4
	(
		_columns[0][0], _columns[1][0], _columns[2][0], _columns[3][0],
		_columns[0][1], _columns[1][1], _columns[2][1], _columns[3][1],
		_columns[0][2], _columns[1][2], _columns[2][2], _columns[3][2],
		_columns[0][3], _columns[1][3], _columns[2][3], _columns[3][3]
	);
}

// Operators

Matrix4& Matrix4::operator +=(const Matrix4& matrix)
{
	_columns[0] += matrix._columns[0];
	_columns[1] += matrix._columns[1];
	_columns[2] += matrix._columns[2];
	_columns[3] += matrix._columns[3];

	return *this;
}

Matrix4& Matrix4::operator -=(const Matrix4& matrix)
{
	_columns[0] -= matrix._columns[0];
	_columns[1] -= matrix._columns[1];
	_columns[2] -= matrix._columns[2];
	_columns[3] -= matrix._columns[3];

	return *this;
}

Matrix4& Matrix4::operator *=(const Matrix4& matrix)
{
	const Vector4 row0(_columns[0][0], _columns[1][0], _columns[2][0], _columns[3][0]);
	const Vector4 row1(_columns[0][1], _columns[1][1], _columns[2][1], _columns[3][1]);
	const Vector4 row2(_columns[0][2], _columns[1][2], _columns[2][2], _columns[3][2]);
	const Vector4 row3(_columns[0][3], _columns[1][3], _columns[2][3], _columns[3][3]);

	_columns[0] = Vector4(Vector4::dot(row0, matrix._columns[0]), Vector4::dot(row1, matrix._columns[0]),
		Vector4::dot(row2, matrix._columns[0]), Vector4::dot(row3, matrix._columns[0]));

	_columns[1] = Vector4(Vector4::dot(row0, matrix._columns[1]), Vector4::dot(row1, matrix._columns[1]),
		Vector4::dot(row2, matrix._columns[1]), Vector4::dot(row3, matrix._columns[1]));

	_columns[2] = Vector4(Vector4::dot(row0, matrix._columns[2]), Vector4::dot(row1, matrix._columns[2]),
		Vector4::dot(row2, matrix._columns[2]), Vector4::dot(row3, matrix._columns[2]));

	_columns[3] = Vector4(Vector4::dot(row0, matrix._columns[3]), Vector4::dot(row1, matrix._columns[3]),
		Vector4::dot(row2, matrix._columns[3]), Vector4::dot(row3, matrix._columns[3]));

	return *this;
}

Matrix4& Matrix4::operator *=(const Float32 scalar)
{
	_columns[0] *= scalar;
	_columns[1] *= scalar;
	_columns[2] *= scalar;
	_columns[3] *= scalar;

	return *this;
}

Matrix4& Matrix4::operator /=(const Float32 scalar)
{
	_columns[0] /= scalar;
	_columns[1] /= scalar;
	_columns[2] /= scalar;
	_columns[3] /= scalar;

	return *this;
}

// Static

Matrix4 Matrix4::createRotation(const Vector3& axis, const Angle& angle)
{
	const Float32 angleSine = sine(angle.size());
	const Float32 angleCosine = cosine(angle.size());
	const Float32 oneMinusAngleCosine = 1.0f - angleCosine;

	return Matrix4
	(
		axis.x * axis.x * oneMinusAngleCosine + angleCosine,
		axis.x * axis.y * oneMinusAngleCosine + axis.z * angleSine,
		axis.x * axis.z * oneMinusAngleCosine - axis.y * angleSine,
		0.0f,
		axis.x * axis.y * oneMinusAngleCosine - axis.z * angleSine,
		axis.y * axis.y * oneMinusAngleCosine + angleCosine,
		axis.y * axis.z * oneMinusAngleCosine + axis.x * angleSine,
		0.0f,
		axis.x * axis.z * oneMinusAngleCosine + axis.y * angleSine,
		axis.y * axis.z * oneMinusAngleCosine - axis.x * angleSine,
		axis.z * axis.z * oneMinusAngleCosine + angleCosine,
		0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 Matrix4::createRotationX(const Angle& angle)
{
	const Float32 angleSine = sine(angle.size());
	const Float32 angleCosine = cosine(angle.size());

	return Matrix4
	(
		1.0f,  0.0f,		0.0f,		 0.0f,
		0.0f,  angleCosine, angleSine,	 0.0f,
		0.0f, -angleSine,	angleCosine, 0.0f,
		0.0f,  0.0f,		0.0f,		 1.0f
	);
}

Matrix4 Matrix4::createRotationY(const Angle& angle)
{
	const Float32 angleSine = sine(angle.size());
	const Float32 angleCosine = cosine(angle.size());

	return Matrix4
	(
		angleCosine, 0.0f, -angleSine,	 0.0f,
		0.0f,		 1.0f,	0.0f,		 0.0f,		
		angleSine,	 0.0f,	angleCosine, 0.0f,
		0.0f,		 0.0f,	0.0f,		 1.0f
	);
}

Matrix4 Matrix4::createRotationZ(const Angle& angle)
{
	const Float32 angleSine = sine(angle.size());
	const Float32 angleCosine = cosine(angle.size());

	return Matrix4
	(
		 angleCosine, angleSine,   0.0f, 0.0f,
		-angleSine,	  angleCosine, 0.0f, 0.0f,
		 0.0f,		  0.0f,		   1.0f, 0.0f,		
		 0.0f,		  0.0f,		   0.0f, 1.0f
	);
}

Matrix4 Matrix4::createTranslation(const Float32 x, const Float32 y, const Float32 z)
{
	return Matrix4
	(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x,	  y,	z,	  1.0f
	);
}
