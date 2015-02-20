/**
 * @file core/Numeric.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Macros.h>
#include <core/Types.h>

namespace Core
{
	/**
	 * Provides numeric constants for numeric types.
	 */
	template<typename T>
	class Numeric
	{
	public:

		/**
		 * Gets the epsilon of a floating point type.
		 *
		 * Epsilon is the difference between 1.0 and the next value
		 * representable by the floating point type T.
		 */
		static DE_CONSTEXPR T epsilon();

		/**
		 * Gets the maximum value representable by the numeric type T.
		 */
		static DE_CONSTEXPR T max();

		/**
		 * Gets the minimum value representable by the numeric type T.
		 */
		static DE_CONSTEXPR T min();

	private:

		Numeric() = delete;
		Numeric(const Numeric& numeric) = delete;
		Numeric(Numeric&& numeric) = delete;
		~Numeric() = delete;

		Numeric& operator =(const Numeric& numeric) = delete;
	};

#include "Numeric.inl"
}
