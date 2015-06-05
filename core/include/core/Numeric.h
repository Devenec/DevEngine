/**
 * @file core/Numeric.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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
		static DE_CONSTEXPR T epsilon();

		/**
		 * Gets the maximum value representable by the numeric type T.
		 */
		static DE_CONSTEXPR T maximum();

		/**
		 * Gets the minimum value representable by the numeric type T.
		 */
		static DE_CONSTEXPR T minimum();
	};

#include "inline/Numeric.inl"
}
