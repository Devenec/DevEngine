/**
 * @file core/Types.h
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

/**
 * Signed 8-bit integer
 */
using Int8 = signed char;

/**
 * Unsigned 8-bit integer
 */
using Uint8 = unsigned char;

/**
 * Signed 16-bit integer
 */
using Int16 = signed short;

/**
 * Unsigned 16-bit integer
 */
using Uint16 = unsigned short;

/**
 * Signed 32-bit integer
 */
using Int32 = signed int;

/**
 * Unsigned 32-bit integer
 */
using Uint32 = unsigned int;

/**
 * Signed 64-bit integer
 */
using Int64 = signed long long;

/**
 * Unsigned 64-bit integer
 */
using Uint64 = unsigned long long;

/**
 * 32-bit floating point
 */
using Float32 = float;

/**
 * 64-bit floating point
 */
using Float64 = double;

/**
 * 8-bit unicode character (UTF-8)
 */
using Char8 = char;

/**
 * 16-bit unicode character (UTF-16)
 */
using Char16 = char16_t;

/**
 * Boolean
 */
using Bool = Int8;

/**
 * Void
 *
 * Used mainly with void pointers.
 */
using Void = void;


#include <platform/TypesInternal.h>

/**
 * Signed 32-bit integer on 32-bit architectures and signed 64-bit integer on
 * 64-bit architectures.
 */
using Int = IntInternal;

/**
 * Unsigned 32-bit integer on 32-bit architectures and unsigned 64-bit integer
 * on 64-bit architectures.
 */
using Uint = UintInternal;


namespace Core
{
	static constexpr Uint32 BITS_IN_BYTE = 8u;
}
