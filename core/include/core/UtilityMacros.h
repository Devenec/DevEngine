/**
 * @file core/UtilityMacros.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <core/UtilityMacrosInternal.h>

// Functions

/**
 * Converts "literal" to a Char16 literal by prefixing it with "L".
 *
 * @param literal
 *   A Char8 character or string literal.
 */
#define DE_CHAR16(literal) \
	DE_INTERNAL_CHAR16(literal)

/**
 * Invokes a compiler warning.
 *
 * @param message
 *   A warning message
 */
#define DE_COMPILER_WARN(message) \
	DE_INTERNAL_COMPILER_WARN(message)

/**
 * Breaks the debugger as if a breakpoint had been hit.
 */
#define DE_DEBUGGER_BREAK() \
	DE_INTERNAL_DEBUGGER_BREAK()

/**
 * Converts "value" to a Char8 string literal by surrounding it with quotation
 * marks.
 *
 * @param value
 *   An identifier
 */
#define DE_STRING8(value) \
	DE_INTERNAL_STRING8(value)


// Keywords and variables

/**
 * Constant expression
 *
 * Expands to "constexpr" specifier with compilers that support it. Otherwise
 * expands to "inline const" specifier. Intended for use with functions, since
 * not all supported compilers support constant expression functions.
 */
#define DE_CONSTEXPR DE_INTERNAL_CONSTEXPR

/**
 * Filename
 *
 * Expands to a string literal that indicates the name of the file in which the
 * macro appears.
 */
#define DE_FILE __FILE__

/**
 * Function name
 *
 * Expands to a string literal that indicates the name of the function in which
 * the macro appears.
 */
#define DE_FUNCTION __func__

/**
 * Line number
 *
 * Expands to the number of the line in which the macro appears.
 */
#define DE_LINE __LINE__

/**
 * No operation
 *
 * Expands to an instruction that does nothing. Intended for use in debug
 * utilities.
 */
#define DE_NO_OPERATION DE_INTERNAL_NO_OPERATION
