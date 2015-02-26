/**
 * @file core/String.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <string>
#include <core/ConfigMacros.h>
#include <core/Types.h>

namespace Core
{
	/**
	 * Character array template 
	 */
	template<typename T>
	using StringTemplate = std::basic_string<T>;

	/**
	 * Character array for Char8 type.
	 */
	using String8 = std::basic_string<Char8>;
	
	/**
	 * Character array for Char16 type.
	 */
	using String16 = std::basic_string<Char16>;

	/**
	 * Common character array.
	 *
	 * If DE_CONFIG_CHAR16 is defined, the underlying type is Char16. Otherwise
	 * the type is Char8.
	 */
	using String =
#if defined(DE_CONFIG_CHAR16)
	String16;
#else
	String8;
#endif
}
