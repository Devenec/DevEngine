/**
 * @file core/String.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <codecvt>
#include <locale>
#include <core/String.h>

using namespace Core;

// Core

String8 Core::toString8(const String16& string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<Char16>> converter;
	return converter.to_bytes(string);
}

String16 Core::toString16(const String8& string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<Char16>> converter;
	return converter.from_bytes(string);
}
