/**
 * @file core/Vector.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <vector>

namespace Core
{
	/**
	 * Dynamic-size array.
	 */
	template<typename T>
	using Vector = std::vector<T>;
}
