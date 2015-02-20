/**
 * @file core/Map.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <unordered_map>

namespace Core
{
	/**
	 * Unordered map for storing key-value pairs with unique keys.
	 */
	template<typename Key, typename T>
	using Map = std::unordered_map<Key, T>;
}
