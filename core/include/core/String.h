/**
 * @file core/String.h
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

#include <string>
#include <core/Types.h>
#include <core/memory/STDAllocator.h>

namespace Core
{
	/**
	 * Character array template
	 */
	template<typename T, typename Allocator = Memory::STDAllocator<T>>
	using StringTemplate = std::basic_string<T, std::char_traits<T>, Allocator>;

	/**
	 * Character array for the Char8 type
	 */
	using String8 = StringTemplate<Char8>;
	
	/**
	 * Character array for the Char16 type
	 */
	using String16 = StringTemplate<Char16>;

	/**
	 * Converts a String16 string to a String8 string.
	 *
	 * @param string
	 *   The string to convert
	 * @return
	 *   The converted string
	 */
	String8 toString8(const String16& string);

	/**
	 * Converts a String8 string to a String16 string.
	 *
	 * @param string
	 *   The string to convert
	 * @return
	 *   The converted string
	 */
	String16 toString16(const String8& string);
}
