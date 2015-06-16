/**
 * @file core/UtilityMacros.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/UtilityMacrosInternal.h>

// Functions

/**
 * Converts "value" to a Char16 literal.
 *
 * @param value
 *   A Char8 character or string literal.
 */
#define DE_CHAR16(value) \
	_DE_CHAR16(value)

/**
 * Invokes a compiler warning.
 *
 * @param message
 *   A warning message
 */
#define DE_COMPILER_WARN(message) \
	_DE_COMPILER_WARN(message)

/**
 * Breaks the debugger as if a breakpoint had been hit.
 */
#define DE_DEBUGGER_BREAK() \
	_DE_DEBUGGER_BREAK()

/**
 * Converts "value" to a Char8 string literal by surrounding it with quotation
 * marks.
 *
 * @param value
 *   An identifier
 */
#define DE_STRING8(value) \
	_DE_STRING8(value)


// Keywords and variables

/**
 * Constant expression
 *
 * Expands to "constexpr" specifier with compilers that support it. Otherwise
 * expands to "inline const" specifier. Intended for use with functions, since
 * not all supported compilers support constant expression functions.
 */
#define DE_CONSTEXPR _DE_CONSTEXPR

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
#define DE_FUNCTION _DE_FUNCTION

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
#define DE_NO_OPERATION _DE_NO_OPERATION
