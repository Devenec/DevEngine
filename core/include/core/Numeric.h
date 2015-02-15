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
	template<typename T>
	class Numeric
	{
	public:

		static DE_CONSTEXPR T epsilon();

		static DE_CONSTEXPR T max();

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
