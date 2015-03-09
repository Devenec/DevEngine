/**
 * @file core/Platform.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Supported processor architectures

#define DE_ARCHITECTURE_X86 1

// Supported compilers

#define DE_COMPILER_MSVC 1

// Minimum supported compiler versions

#define DE_MIN_COMPILER_VERSION_MSVC 1800

// Supported build configurations

#define DE_CONFIG_DEBUG	  1
#define DE_CONFIG_RELEASE 2

// Supported platforms

#define DE_PLATFORM_WINDOWS 1


/**
 * Defines the following macros:
 *
 * DE_ARCHITECTURE
 *   Specifies the target processor architecture. The value is one of the
 *   DE_ARCHITECTURE_* values defined above.
 *
 * DE_COMPILER
 *   Specifies the compiler. The value is one of the DE_COMPILER_* values
 *   defined above.
 *
 * DE_COMPILER_VERSION
 *   Specifies the version of the compiler.
 *
 * DE_CONFIG
 *   Specifies the build configuration. The value is one of the DE_CONFIG_*
 *   values defined above.
 *
 * DE_PLATFORM
 *   Specifies the target platform. The value is one of the DE_PLATFORM_*
 *   values defined above.
 */
#include <platform/PlatformInternal.h>
