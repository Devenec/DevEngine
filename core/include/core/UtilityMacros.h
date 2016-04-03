/**
 * @file core/UtilityMacros.h
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

#include <core/UtilityMacrosInternal.h>

// Keywords and variables

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
 * Expands to the line number in which the macro appears.
 */
#define DE_LINE __LINE__

/**
 * No operation
 *
 * Expands to an instruction that does nothing. Intended for use in debug
 * utilities.
 */
#define DE_NO_OPERATION DE_INTERNAL_NO_OPERATION


// Warnings (used for disabling compiler warnings)

/**
 * A non-literal format is passed to a function accepting variadic arguments
 * (e.g. printf()).
 */
#define DE_WARNING_NON_LITERAL_FORMAT DE_INTERNAL_WARNING_NON_LITERAL_FORMAT


// Functions

/**
 * Disables the specified compiler warning in a compilation unit until
 * DE_END_DISABLE_COMPILER_WARNING() is called.
 *
 * @param warning
 *   An identifier of the warning to disable (see "Warnings" above)
 */
#define DE_BEGIN_DISABLE_COMPILER_WARNING(warning) \
	DE_INTERNAL_BEGIN_DISABLE_COMPILER_WARNING(warning)

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
 * Undoes the previous call to DE_BEGIN_DISABLE_COMPILER_WARNING() in the same
 * compilation unit.
 */
#define DE_END_DISABLE_COMPILER_WARNING() \
	DE_INTERNAL_END_DISABLE_COMPILER_WARNING()

/**
 * Converts "value" to a Char8 string literal by surrounding it with quotation
 * marks.
 *
 * @param value
 *   An identifier
 */
#define DE_STRING8(value) \
	DE_INTERNAL_STRING8(value)
