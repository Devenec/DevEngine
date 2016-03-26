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

#define DE_INTERNAL_STRING8_1(value) \
	#value

#define DE_INTERNAL_STRING8_2(value) \
	DE_INTERNAL_STRING8_1(value)


// Compiler and compiler version detection

#if defined(__clang__)
	#define DE_INTERNAL_COMPILER		 DE_COMPILER_CLANG

	#if __clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ < 3)
		#error The CLANG compiler version is not supported. The minumum supported version is 3.3.
	#endif
#elif defined(__GNUG__)
	#define DE_INTERNAL_COMPILER		 DE_COMPILER_GCC

	#if __GNUC__ < 5 || (__GNUC__ == 5 && __GNUC_MINOR__ < 1)
		#error The GCC compiler version is not supported. The minumum supported version is 5.1.
	#endif
#elif defined(_MSC_VER)
	#define DE_INTERNAL_COMPILER		 DE_COMPILER_MSVC

	#if _MSC_VER < 1900
		#error The MSVC compiler version is not supported. The minumum supported version is 14.0 (1900).
	#endif
#else
	#error The current compiler is not supported.
#endif


// Target processor architecture detection

#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG || DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#if defined(__i386) || defined(__i386__)
		#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X86
	#elif defined(__x86_64) || defined(__x86_64__)
		#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X64
	#endif
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#if defined(_WIN64)
		#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X64
	#elif defined(_WIN32)
		#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X86
	#endif
#endif

#if !defined(DE_INTERNAL_ARCHITECTURE)
	#error The target processor architecture is not supported.
#endif


// Compiler specific internal keywords and variables

#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG || DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#define DE_INTERNAL_NO_OPERATION static_cast<Void>(0)
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_CALL_STDCALL __stdcall
	#define DE_INTERNAL_NO_OPERATION __noop
#endif


// Compiler specific internal functions

#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		_Pragma(DE_INTERNAL_STRING8_1(message(msg)))

	#define DE_INTERNAL_DEBUGGER_BREAK()
		// TODO: implement
#elif DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		_Pragma(DE_INTERNAL_STRING8_1(GCC warning msg))

	#define DE_INTERNAL_DEBUGGER_BREAK()
		// TODO: implement
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_COMPILER_WARN(msg) \
		__pragma(message(__FILE__ "(" DE_INTERNAL_STRING8_1(__LINE__) ") : warning: " msg))

	#define DE_INTERNAL_DEBUGGER_BREAK() \
		__debugbreak()
#endif


// Build configuration detection

#if defined(DE_BUILD_CONFIG_DEBUG)
	#define DE_INTERNAL_BUILD DE_BUILD_DEBUG
#elif defined(DE_BUILD_CONFIG_RELEASE)
	#define DE_INTERNAL_BUILD DE_BUILD_RELEASE
#elif defined(DE_BUILD_CONFIG_PRODUCTION)
	#define DE_INTERNAL_BUILD DE_BUILD_PRODUCTION
#else
	#define DE_INTERNAL_BUILD DE_BUILD_DEBUG
	DE_INTERNAL_COMPILER_WARN("Could not detect the build configuration. DE_BUILD is set to DE_BUILD_DEBUG.");
#endif


// Target platform detection

#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG || DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#if defined(__linux) || defined(__linux__)
		#define DE_INTERNAL_PLATFORM DE_PLATFORM_LINUX
	#endif
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#if defined(_WIN32)
		#define DE_INTERNAL_PLATFORM DE_PLATFORM_WINDOWS
	#endif
#endif

#if !defined(DE_INTERNAL_PLATFORM)
	#error The target platform is not supported with the current compiler.
#endif
