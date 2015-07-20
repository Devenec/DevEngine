/**
 * @file platform/windows/WindowsLog.cpp
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

#include <cstdio>
#include <core/Array.h>
#include <core/Log.h>
#include <core/UtilityMacros.h>

using namespace Core;

// External

static const Array<const Char8*, 4u> LOG_LEVEL_NAMES =
{
	"DEBUG  ",
	"INFO   ",
	"WARNING",
	"ERROR  "
};


// Private

const Char8* Log::LINE_BREAK		= "\n          ";
const Uint32 Log::LINE_BREAK_LENGTH = 11u;
const Uint32 Log::MAX_LINE_LENGTH	= 120u;

// Static

void Log::writeToConsole(const LogLevel& logLevel, const String8& message)
{
	const Char8* levelName = LOG_LEVEL_NAMES[static_cast<Int32>(logLevel)];
	std::wprintf(DE_CHAR16("%S | %S\n"), levelName, message.c_str());
}
