/**
 * @file core/Array.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <array>
#include <core/Types.h>

namespace Core
{
	/**
	 * Fixed-size array
	 */
	template<typename T, Uint32 Size>
	using Array = std::array<T, Size>;
}
