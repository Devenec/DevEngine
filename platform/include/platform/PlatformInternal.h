/**
 * @file platform/PlatformInternal.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Target processor architecture detection

#if !defined(_WIN64)
	#define DE_ARCHITECTURE DE_ARCHITECTURE_X86
#else
	#error The target processor architecture is unsupported
#endif

// Compiler and compiler version detection

#if defined(_MSC_VER)
	#define DE_COMPILER			DE_COMPILER_MSVC
	#define DE_COMPILER_VERSION _MSC_VER

	#if DE_COMPILER_VERSION < DE_MIN_COMPILER_VERSION_MSVC
		#error The compiler version is unsupported. The minimum supported version is DE_MIN_COMPILER_VERSION_MSVC.
	#endif
#else
	#error "The compiler is unsupported"
#endif

// Build configuration detection

#if defined(_DEBUG)
	#define DE_CONFIG DE_CONFIG_DEBUG
#else
	#define DE_CONFIG DE_CONFIG_RELEASE
#endif

// Target platform detection

#if defined(_WIN32)
	#define DE_PLATFORM DE_PLATFORM_WINDOWS
#else
	#error The target platform is unsupported
#endif


// Internal functions

#define __DE_STRING(value) \
	_DE_STRING(value)


// Platform specific internal functions

#if DE_COMPILER == DE_COMPILER_MSVC
	#define _DE_WARNING(msg) \
		__pragma(message(__FILE__ "(" __DE_STRING(__LINE__) ") : warning: \"" msg "\""))
#endif


// Platform specific internal keywords and variables

#if DE_COMPILER == DE_COMPILER_MSVC
	#define _DE_CONSTEXPR	 inline const
	#define _DE_FUNCTION	 __FUNCSIG__
	#define _DE_NO_OPERATION __noop
#endif


#undef __DE_STRING
