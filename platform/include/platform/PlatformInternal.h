/**
 * @file platform/PlatformInternal.h
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

// Internal functions

#define DE_INTERNAL1_STRING8(value) \
	#value

#define DE_INTERNAL2_STRING8(value) \
	DE_INTERNAL1_STRING8(value)


// Compiler and compiler version detection

#if defined(__clang__)
	#define DE_COMPILER			DE_COMPILER_CLANG
	#define DE_COMPILER_VERSION 0

	// TODO: check the clang features
#elif defined(_MSC_VER)
	#define DE_COMPILER			DE_COMPILER_MSVC
	#define DE_COMPILER_VERSION _MSC_VER

	#if DE_COMPILER_VERSION < DE_COMPILER_VERSION_MIN_MSVC
		#error The compiler version is not supported. See the minimum supported version in core/Platform.h.
	#endif
#else
	#error The compiler is not supported.
#endif


// Target processor architecture detection

#if DE_COMPILER == DE_COMPILER_CLANG
	#if defined(__i386) || defined(__i386__)
		#define DE_ARCHITECTURE DE_ARCHITECTURE_X86
	#else
		#define DE_ARCHITECTURE 0
	#endif
#elif DE_COMPILER == DE_COMPILER_MSVC
	#if defined(_WIN64)
		#define DE_ARCHITECTURE DE_ARCHITECTURE_X64
	#elif defined(_WIN32)
		#define DE_ARCHITECTURE DE_ARCHITECTURE_X86
	#else
		#define DE_ARCHITECTURE 0
	#endif
#endif

#if DE_ARCHITECTURE == 0
	#error The target processor architecture is not supported.
#endif


// Compiler specific internal keywords and variables

#if DE_COMPILER == DE_COMPILER_CLANG
	#define DE_INTERNAL_NO_OPERATION static_cast<Void>(0)
#elif DE_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_CALL_STDCALL __stdcall
	#define DE_INTERNAL_NO_OPERATION __noop
#endif


// Compiler specific internal functions

#if DE_COMPILER == DE_COMPILER_CLANG
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		_Pragma(DE_INTERNAL1_STRING8(message(msg)))

	#define DE_INTERNAL_DEBUGGER_BREAK()
		// TODO: implement
#elif DE_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		__pragma(message(__FILE__ "(" DE_INTERNAL2_STRING8(__LINE__) ") : warning: " msg))

	#define DE_INTERNAL_DEBUGGER_BREAK() \
		__debugbreak()
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

#if DE_COMPILER == DE_COMPILER_CLANG
	#if defined(__linux) || defined(__linux__)
		#define DE_PLATFORM DE_PLATFORM_LINUX
	#else
		#define DE_PLATFORM 0
	#endif
#elif DE_COMPILER == DE_COMPILER_MSVC
	#if defined(_WIN32)
		#define DE_PLATFORM DE_PLATFORM_WINDOWS
	#else
		#define DE_PLATFORM 0
	#endif
#endif

#if DE_PLATFORM == 0
	#error The target platform is not supported.
#endif
