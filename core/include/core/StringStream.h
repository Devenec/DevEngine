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
	 * Character array output stream template
	 */
	template<typename T>
	using StringStreamTemplate = std::basic_ostringstream<T>;

	/**
	 * Character array output stream for Char8 type
	 */
	using StringStream8 = StringStreamTemplate<Char8>;
	
	/**
	 * Character array output stream for Char16 type
	 */
	using StringStream16 = StringStreamTemplate<Char16>;

	/**
	 * Common character array output stream
	 *
	 * If DE_CONFIG_CHAR16 is defined, the underlying type is Char16. Otherwise
	 * the type is Char8.
	 */
	using StringStream =
#if defined(DE_CONFIG_CHAR16)
		StringStreamTemplate<Char16>;
#else
		StringStreamTemplate<Char8>;
#endif
}
