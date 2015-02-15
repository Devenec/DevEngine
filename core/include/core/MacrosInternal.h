/**
 * @file core/MacrosInternal.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Functions

#define _DE_STRING(value) \
	#value

#define _DE_TO_CHAR16(literal) \
	L ## literal

// Platform specifics

#if defined(DE_COMPILER_MSVC)
	#define _DE_FUNCTION	 __FUNCSIG__
	#define _DE_NO_OPERATION __noop
#endif


// Keywords and variables

// Platform specifics

#if defined(DE_COMPILER_MSVC)
	#define _DE_CONSTEXPR inline const
#endif
