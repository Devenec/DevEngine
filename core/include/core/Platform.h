/**
 * @file core/Platform.h
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

// Supported processor architectures

#define DE_ARCHITECTURE_X86 1
#define DE_ARCHITECTURE_X64 2


// Supported build configurations

#define DE_BUILD_DEBUG		1
#define DE_BUILD_RELEASE	2
#define DE_BUILD_PRODUCTION 3


// Supported compilers

#define DE_COMPILER_CLANG 1
#define DE_COMPILER_MSVC  2


// Minimum supported compiler versions

#define DE_COMPILER_VERSION_MIN_CLANG 0
#define DE_COMPILER_VERSION_MIN_MSVC  1900


// Supported platforms

#define DE_PLATFORM_LINUX   1
#define DE_PLATFORM_WINDOWS 2


/**
 * The following macros are defined in the internal header file:
 *
 * DE_ARCHITECTURE
 *   Specifies the target processor architecture. The value is one of the
 *   DE_ARCHITECTURE_* values defined above.
 *
 * DE_BUILD
 *   Specifies the build configuration. The value is one of the DE_BUILD_*
 *   values defined above.
 *
 * DE_COMPILER
 *   Specifies the compiler. The value is one of the DE_COMPILER_* values
 *   defined above.
 *
 * DE_COMPILER_VERSION
 *   Specifies the version of the compiler. Is 0 when not supported.
 *
 * DE_PLATFORM
 *   Specifies the target platform. The value is one of the DE_PLATFORM_*
 *   values defined above.
 */
#include <platform/PlatformInternal.h>
