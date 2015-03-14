/**
 * @file core/String.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <string>
#include <core/Types.h>

namespace Core
{
	/**
	 * Character array template 
	 */
	template<typename T>
	using StringTemplate = std::basic_string<T>;

	/**
	 * Character array for the Char8 type
	 */
	using String8 = StringTemplate<Char8>;
	
	/**
	 * Character array for the Char16 type
	 */
	using String16 = StringTemplate<Char16>;

	/**
	 * Converts a String16 string to a String8 string.
	 *
	 * @param string
	 *   The string to convert
	 * @return
	 *   The converted string
	 */
	String8 toString8(const String16& string);

	/**
	 * Converts a String8 string to a String16 string.
	 *
	 * @param string
	 *   The string to convert
	 * @return
	 *   The converted string
	 */
	String16 toString16(const String8& string);
}
