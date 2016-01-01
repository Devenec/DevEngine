/**
 * @file core/Numeric.h
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
#include <core/UtilityMacros.h>

namespace Core
{
	/**
	 * Numeric constant helper
	 */
	template<typename T>
	class Numeric final
	{
	public:

		Numeric() = delete;
		
		Numeric(const Numeric& numeric) = delete;
		Numeric(Numeric&& numeric) = delete;
		
		~Numeric() = delete;

		Numeric& operator =(const Numeric& numeric) = delete;
		Numeric& operator =(Numeric&& numeric) = delete;

		/**
		 * Gets the epsilon of a floating point type.
		 *
		 * Epsilon is the difference between 1.0 and the next largest value
		 * representable by the floating point type T.
		 */
		static constexpr T epsilon();

		/**
		 * Gets the maximum value representable by the numeric type T.
		 */
		static constexpr T maximum();

		/**
		 * Gets the minimum value representable by the numeric type T.
		 */
		static constexpr T minimum();
	};

#include "inline/Numeric.inl"
}
