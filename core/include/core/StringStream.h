/**
 * @file core/StringStream.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <sstream>
#include <core/Types.h>
#include <core/memory/STDAllocator.h>

namespace Core
{
	/**
	 * Character array output stream template
	 */
	template<typename T, typename Allocator = Memory::STDAllocator<T>>
	using StringStreamTemplate = std::basic_ostringstream<T, std::char_traits<T>, Allocator>;

	/**
	 * Character array output stream for the Char8 type
	 */
	using StringStream8 = StringStreamTemplate<Char8>;

	/**
	 * Character array output stream for the Char16 type
	 */
	using StringStream16 = StringStreamTemplate<Char16>;
}
