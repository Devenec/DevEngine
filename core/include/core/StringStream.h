/**
 * @file core/StringStream.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <sstream>
#include <core/ConfigMacros.h>
#include <core/Types.h>

namespace Core
{
	/**
	 * Character array stream for Char8 type.
	 */
	using StringStream8 = std::basic_stringstream<Char8>;
	
	/**
	 * Character array stream for Char16 type.
	 */
	using StringStream16 = std::basic_stringstream<Char16>;

	/**
	 * Common character array stream.
	 *
	 * If DE_CONFIG_CHAR16 is defined, the underlying type is Char16. Otherwise
	 * the type is Char8.
	 */
	using StringStream =
#if defined(DE_CONFIG_CHAR16)
	StringStream16;
#else
	StringStream8;
#endif
}
