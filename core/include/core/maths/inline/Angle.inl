/**
 * @file core/maths/inline/Angle.inl
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

// Public

void Angle::setSize(const Float32 size)
{
	_size = size;
}

Float32 Angle::size() const
{
	return _size;
}

Angle Angle::operator -() const
{
	return Angle(-_size);
}

Angle& Angle::operator +=(const Angle& angle)
{
	_size += angle._size;
	return *this;
}

Angle& Angle::operator -=(const Angle& angle)
{
	_size -= angle._size;
	return *this;
}

Angle& Angle::operator *=(const Angle& angle)
{
	_size *= angle._size;
	return *this;
}

Angle& Angle::operator /=(const Angle& angle)
{
	_size /= angle._size;
	return *this;
}


// Maths

Angle operator +(Angle angleA, const Angle& angleB)
{
	angleA += angleB;
	return angleA;
}

Angle operator -(Angle angleA, const Angle& angleB)
{
	angleA -= angleB;
	return angleA;
}

Angle operator *(Angle angleA, const Angle& angleB)
{
	angleA *= angleB;
	return angleA;
}

Angle operator /(Angle angleA, const Angle& angleB)
{
	angleA /= angleB;
	return angleA;
}

Bool operator ==(const Angle& angleA, const Angle& angleB)
{
	return angleA.size() == angleB.size();
}

Bool operator !=(const Angle& angleA, const Angle& angleB)
{
	return !(angleA == angleB);
}

Bool operator <(const Angle& angleA, const Angle& angleB)
{
	return angleA.size() < angleB.size();
}

Bool operator <=(const Angle& angleA, const Angle& angleB)
{
	return !(angleA > angleB);
}

Bool operator >(const Angle& angleA, const Angle& angleB)
{
	return angleB < angleA;
}

Bool operator >=(const Angle& angleA, const Angle& angleB)
{
	return !(angleA < angleB);
}
