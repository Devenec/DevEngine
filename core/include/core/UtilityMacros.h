/**
 * @file core/UtilityMacros.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/ConfigMacros.h>
#include <core/UtilityMacrosInternal.h>

// Functions

/**
 * Converts a character or string literal to Char16 literal.
 *
 * Prefixes the literal with "L".
 *
 * @param literal
 *   A character or string literal
 */
#define DE_CHAR16(literal) \
	_DE_CHAR16(literal)

/**
 * Stringifies a value.
 *
 * Converts "value" to a string literal by surrounding it with quotation marks.
 *
 * @param value
 *   An identifier or a macro argument
 */
#define DE_STRING(value) \
	_DE_STRING(value)

/**
 * Processes a character or string literal.
 *
 * If DE_CONFIG_CHAR16 is defined, "literal" is converted to a Char16 literal
 * by prefixing it with "L". Otherwise "literal" is not changed.
 *
 * @param literal
 *   A character or string literal
 */
#if defined(DE_CONFIG_CHAR16)
	#define DE_TEXT(literal) \
		_DE_CHAR16(literal)
#else
	#define DE_TEXT(literal) \
		literal
#endif

/**
 * Issues a compiler warning.
 *
 * @param message
 *   A warning message
 */
#define DE_WARNING(message) \
	_DE_WARNING(message)


// Keywords and variables

/**
 * Constant expression
 *
 * Expands to "constexpr" specifier with compilers that support it. Otherwise
 * expands to "inline const" specifier. Intended for use with functions, since
 * not all supported compilers support constant expression functions yet.
 */
#define DE_CONSTEXPR _DE_CONSTEXPR

/**
 * Filename
 *
 * Expands to a string literal that indicates the name of the file in which
 * the macro appears. The literal is processed with DE_TEXT().
 */
#define DE_FILE DE_TEXT(__FILE__)

/**
 * Function name
 *
 * Expands to a string literal that indicates the name and signature of
 * the function in which the macro appears. The literal is processed with
 * DE_TEXT().
 */
#define DE_FUNCTION DE_TEXT(_DE_FUNCTION)

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
