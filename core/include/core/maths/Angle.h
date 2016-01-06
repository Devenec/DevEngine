/**
 * @file core/maths/Angle.h
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

namespace Maths
{
	class Angle final
	{
	public:

		Angle() = default;

		Angle(const Float32 size);

		Angle(const Angle& angle) = default;

		Angle(Angle&& angle) = default;

		~Angle() = default;

		inline void setSize(const Float32 size);

		inline Float32 size() const;

		Angle& operator =(const Angle& angle) = default;

		Angle& operator =(Angle&& angle) = default;

		inline Angle operator -() const;

		inline Angle& operator +=(const Angle& angle);

		inline Angle& operator -=(const Angle& angle);

		inline Angle& operator *=(const Angle& angle);

		inline Angle& operator /=(const Angle& angle);

	private:

		Float32 _size;
	};

	inline Angle operator +(Angle angleA, const Angle& angleB);

	inline Angle operator -(Angle angleA, const Angle& angleB);

	inline Angle operator *(Angle angleA, const Angle& angleB);

	inline Angle operator /(Angle angleA, const Angle& angleB);

	inline Bool operator ==(const Angle& angleA, const Angle& angleB);

	inline Bool operator !=(const Angle& angleA, const Angle& angleB);

	inline Bool operator <(const Angle& angleA, const Angle& angleB);

	inline Bool operator <=(const Angle& angleA, const Angle& angleB);

	inline Bool operator >(const Angle& angleA, const Angle& angleB);

	inline Bool operator >=(const Angle& angleA, const Angle& angleB);

#include "inline/Angle.inl"
}
