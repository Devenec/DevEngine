/**
 * @file platform/PlatformInternal.h
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

// Internal functions

#define DE_INTERNAL1_STRING8(value) \
	#value

#define DE_INTERNAL2_STRING8(value) \
	DE_INTERNAL1_STRING8(value)


// Compiler and compiler version detection

#if defined(_MSC_VER)
	#define DE_COMPILER			DE_COMPILER_MSVC
	#define DE_COMPILER_VERSION _MSC_VER

	#if DE_COMPILER_VERSION < DE_COMPILER_VERSION_MIN_MSVC
		#error The compiler version is not supported. The minimum supported version is DE_COMPILER_VERSION_MIN_MSVC.
	#endif
#else
	#error The compiler is not supported.
#endif


// Compiler specific internal functions

#if DE_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		__pragma(message(__FILE__ "(" DE_INTERNAL2_STRING8(__LINE__) ") : warning: " msg))

	#define DE_INTERNAL_DEBUGGER_BREAK() \
		__asm int 3
#endif


// Compiler specific internal keywords and variables

#if DE_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_CALL_STDCALL __stdcall
	#define DE_INTERNAL_CONSTEXPR	 inline const
	#define DE_INTERNAL_FUNCTION	 __FUNCTION__
	#define DE_INTERNAL_NO_OPERATION __noop
#endif


// Target processor architecture detection

#if !defined(_WIN64)
	#define DE_ARCHITECTURE DE_ARCHITECTURE_X86
#else
	#error The target processor architecture is not supported.
#endif


// Build configuration detection

#if defined(DE_BUILD_CONFIG_DEBUG)
	#define DE_BUILD DE_BUILD_DEBUG
#elif defined(DE_BUILD_CONFIG_RELEASE)
	#define DE_BUILD DE_BUILD_RELEASE
#elif defined(DE_BUILD_CONFIG_PRODUCTION)
	#define DE_BUILD DE_BUILD_PRODUCTION
#else
	#define DE_BUILD DE_BUILD_DEBUG
	
	DE_INTERNAL_COMPILER_WARN("Could not detect the build configuration correctly." \
		" DE_BUILD is set to DE_BUILD_DEBUG.");
#endif


// Target platform detection

#if defined(_WIN32)
	#define DE_PLATFORM DE_PLATFORM_WINDOWS
#else
	#error The target platform is not supported.
#endif


#undef DE_INTERNAL2_STRING8
#undef DE_INTERNAL1_STRING8
