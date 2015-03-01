/**
 * @file core/List.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <list>

namespace Core
{
	/**
	 * Doubly-linked list
	 */
	template<typename T>
	using List = std::list<T>;
}
