/**
 * @file core/MacrosInternals.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Functions

#define _DE_STRING(value) \
	# value

#define _DE_TEXT(value) \
	text

#define _DE_WIDEN(text) \
	L ## text

// Platform specifics

#if defined(DE_COMPILER_MSVC)
	#define _DE_FUNCTION _DE_TEXT(__FUNCSIG__)
	#define _DE_NO_OP __noop
#endif
