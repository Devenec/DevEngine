/**
 * @file core/StringStream.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <sstream>
#include <core/Types.h>

namespace Core
{
	/**
	 * Character array output stream template
	 */
	template<typename T>
	using StringStreamTemplate = std::basic_ostringstream<T>;

	/**
	 * Character array output stream for the Char8 type
	 */
	using StringStream8 = StringStreamTemplate<Char8>;
	
	/**
	 * Character array output stream for the Char16 type
	 */
	using StringStream16 = StringStreamTemplate<Char16>;
}
