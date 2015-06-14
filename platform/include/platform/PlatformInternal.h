/**
 * @file platform/PlatformInternal.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Internal functions

#define ___DE_STRING8(value) \
	#value

#define __DE_STRING8(value) \
	___DE_STRING8(value)


// Compiler and compiler version detection

#if defined(_MSC_VER)
	#define DE_COMPILER			DE_COMPILER_MSVC
	#define DE_COMPILER_VERSION _MSC_VER

	#if DE_COMPILER_VERSION < DE_COMPILER_VERSION_MIN_MSVC
		#error The compiler version is unsupported. The minimum supported version is DE_COMPILER_VERSION_MIN_MSVC.
	#endif
#else
	#error "The compiler is unsupported."
#endif


// Compiler specific internal functions

#if DE_COMPILER == DE_COMPILER_MSVC
	#define _DE_CHAR16(value) \
		L ## value

	#define _DE_COMPILER_WARN(msg) \
		__pragma(message(__FILE__ "(" __DE_STRING8(__LINE__) ") : warning: \"" msg "\""))

	#define _DE_DEBUGGER_BREAK() \
		__asm int 3
#endif


// Compiler specific internal keywords and variables

#if DE_COMPILER == DE_COMPILER_MSVC
	#define _DE_CONSTEXPR	 inline const
	#define _DE_FUNCTION	 __FUNCTION__
	#define _DE_NO_OPERATION __noop
#endif


// Target processor architecture detection

#if !defined(_WIN64)
	#define DE_ARCHITECTURE DE_ARCHITECTURE_X86
#else
	#error The target processor architecture is unsupported.
#endif


// Build configuration detection

#if defined(_DE_BUILD_CONFIG_DEBUG)
	#define DE_BUILD_CONFIG DE_BUILD_CONFIG_DEBUG
#elif defined(_DE_BUILD_CONFIG_RELEASE)
	#define DE_BUILD_CONFIG DE_BUILD_CONFIG_RELEASE
#elif defined(_DE_BUILD_CONFIG_PRODUCTION)
	#define DE_BUILD_CONFIG DE_BUILD_CONFIG_PRODUCTION
#else
	#define DE_BUILD_CONFIG DE_BUILD_CONFIG_DEBUG

	_DE_COMPILER_WARN("Could not detect the build configuration correctly."
		" DE_BUILD_CONFIG is set to DE_BUILD_CONFIG_DEBUG.");
#endif


// Target platform detection

#if defined(_WIN32)
	#define DE_PLATFORM DE_PLATFORM_WINDOWS
#else
	#error The target platform is unsupported.
#endif


#undef __DE_STRING8
#undef ___DE_STRING8
