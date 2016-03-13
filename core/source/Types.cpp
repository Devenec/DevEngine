/**
 * @file core/Types.cpp
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

#include <climits>
#include <core/Types.h>

static_assert(CHAR_BIT == 8, "The number of bits in a byte is invalid.");

static_assert(sizeof(Int8) == 1, "The size of Int8 is invalid.");
static_assert(sizeof(Uint8) == 1, "The size of Uint8 is invalid.");
static_assert(sizeof(Int16) == 2, "The size of Int16 is invalid.");
static_assert(sizeof(Uint16) == 2, "The size of Uint16 is invalid.");
static_assert(sizeof(Int32) == 4, "The size of Int32 is invalid.");
static_assert(sizeof(Uint32) == 4, "The size of Uint32 is invalid.");
static_assert(sizeof(Int64) == 8, "The size of Int64 is invalid.");
static_assert(sizeof(Uint64) == 8, "The size of Uint64 is invalid.");
static_assert(sizeof(Float32) == 4, "The size of Float32 is invalid.");
static_assert(sizeof(Float64) == 8, "The size of Float64 is invalid.");
static_assert(sizeof(Char8) == 1, "The size of Char8 is invalid.");
//static_assert(sizeof(Char16) == 2, "The size of Char16 is invalid.");

enum class Enumeration { };
static_assert(sizeof(Enumeration) == 4, "The size of enumeration (enum class) is invalid.");
