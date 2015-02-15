/**
 * @file core/Types.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/ConfigMacros.h>

/**
 * Boolean
 *
 * The size is platform-dependent.
 */
using Bool = bool;

/**
 * 8-bit byte
 */
using Byte = unsigned char;

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
 * 8-bit character
 *
 * The encoding is platform-dependent.
 */
using Char8 = char;

/**
 * 16-bit unicode character
 */
using Char16 = wchar_t;

/**
 * Common character
 *
 * If DE_CONFIG_CHAR16 is defined, the type is Char16. Otherwise the type is
 * Char8.
 */
using Char =
#if defined(DE_CONFIG_CHAR16)
	Char16;
#else
	Char8;
#endif
