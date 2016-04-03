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

// Compiler and compiler version detection

#if defined(__clang__)
	#define DE_INTERNAL_COMPILER DE_COMPILER_CLANG

	#if __clang_major__ < 3 || (__clang_major__ == 3 && __clang_minor__ < 3)
		#error The CLANG compiler version is not supported. The minumum supported version is 3.3.
	#endif
#elif defined(__GNUG__)
	#define DE_INTERNAL_COMPILER DE_COMPILER_GCC

	#if __GNUC__ < 5 || (__GNUC__ == 5 && __GNUC_MINOR__ < 1)
		#error The GCC compiler version is not supported. The minumum supported version is 5.1.
	#endif
#elif defined(_MSC_VER)
	#define DE_INTERNAL_COMPILER DE_COMPILER_MSVC

	#if _MSC_VER < 1900
		#error The MSVC compiler version is not supported. The minumum supported version is 14.0 (1900).
	#endif
#else
	#error The current compiler is not supported.
#endif


// Target processor architecture detection

#if defined(_WIN64) || defined(__x86_64) || defined(__x86_64__)
	#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X64
#elif defined(_WIN32) || defined(__i386) || defined(__i386__)
	#define DE_INTERNAL_ARCHITECTURE DE_ARCHITECTURE_X86
#endif

#if !defined(DE_INTERNAL_ARCHITECTURE)
	#error The target processor architecture is not supported.
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


// Compiler specific internal keywords and variables

#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG || DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#define DE_INTERNAL_NO_OPERATION			   static_cast<void>(0)
	#define DE_INTERNAL_WARNING_NON_LITERAL_FORMAT "-Wformat-nonliteral"
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_CALL_STDCALL			   __stdcall
	#define DE_INTERNAL_NO_OPERATION			   __noop
	#define DE_INTERNAL_WARNING_NON_LITERAL_FORMAT 0 // TODO: assign proper value?
#endif


// Compiler specific internal functions

// Clang and GCC
#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG || DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#define DE_INTERNAL_PRAGMA(value) \
		_Pragma(#value)
#endif

// Clang
#if DE_INTERNAL_COMPILER == DE_COMPILER_CLANG
	#define DE_INTERNAL_BEGIN_DISABLE_COMPILER_WARNING(warning) \
		DE_INTERNAL_PRAGMA(clang diagnostic push) \
		DE_INTERNAL_PRAGMA(clang diagnostic ignored warning)

	#define DE_INTERNAL_WARN_COMPILER(msg) \
		DE_INTERNAL_PRAGMA(message(msg))

	#define DE_INTERNAL_BREAK_DEBUGGER()
		// TODO: implement

	#define DE_INTERNAL_END_DISABLE_COMPILER_WARNING() \
		DE_INTERNAL_PRAGMA(clang diagnostic pop)

// GCC
#elif DE_INTERNAL_COMPILER == DE_COMPILER_GCC
	#define DE_INTERNAL_BEGIN_DISABLE_COMPILER_WARNING(warning) \
		DE_INTERNAL_PRAGMA(GCC diagnostic push) \
		DE_INTERNAL_PRAGMA(GCC diagnostic ignored warning)

	#define DE_INTERNAL_WARN_COMPILER(msg) \
		DE_INTERNAL_PRAGMA(GCC warning msg)

	#define DE_INTERNAL_BREAK_DEBUGGER()
		// TODO: implement

	#define DE_INTERNAL_END_DISABLE_COMPILER_WARNING() \
		DE_INTERNAL_PRAGMA(GCC diagnostic pop)

// MSVC
#elif DE_INTERNAL_COMPILER == DE_COMPILER_MSVC
	#define DE_INTERNAL_BEGIN_DISABLE_COMPILER_WARNING(warning)
		// TODO: implement

	#define DE_INTERNAL_STRING8(value) \
		#value

	#define DE_INTERNAL_WARN_COMPILER(msg) \
		__pragma(message(__FILE__ "(" DE_INTERNAL_STRING8(__LINE__) ") : warning: " msg)) // TODO: fix

	#define DE_INTERNAL_BREAK_DEBUGGER() \
		__debugbreak()

	#define DE_INTERNAL_END_DISABLE_COMPILER_WARNING()
		// TODO: implement
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
	DE_INTERNAL_WARN_COMPILER("Could not detect the build configuration. DE_BUILD is set to DE_BUILD_DEBUG.")
#endif
