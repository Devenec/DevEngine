/**
 * @file core/Numeric.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>

namespace Core
{
	template<typename T>
	class Numeric
	{
	public:

		inline static T epsilon(); // TODO: make constexpr

		inline static T max(); // TODO: make constexpr

		inline static T min(); // TODO: make constexpr

	private:

		Numeric() = delete;
		Numeric(const Numeric& numeric) = delete;
		Numeric(Numeric&& numeric) = delete;
		~Numeric() = delete;

		Numeric& operator =(const Numeric& numeric) = delete;
	};

#include "Numeric.inl"
}
