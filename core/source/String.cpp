/**
 * @file core/String.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
