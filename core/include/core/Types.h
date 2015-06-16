/**
 * @file core/Types.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

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
 * 8-bit unicode character (UTF-8)
 */
using Char8 = char;

/**
 * 16-bit unicode character (UTF-16)
 */
using Char16 = wchar_t;

/**
 * Void
 *
 * Used mainly with void pointers.
 */
using Void = void;
