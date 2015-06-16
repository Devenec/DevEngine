/**
 * @file platform/windows/WindowsLog.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdio>
#include <core/Array.h>
#include <core/Log.h>
#include <core/UtilityMacros.h>

using namespace Core;

static const Array<const Char8*, 4u> LOG_LEVEL_NAMES =
{
	"DEBUG  ",
	"INFO   ",
	"WARNING",
	"ERROR  "
};

// Private

// Static

void Log::writeToConsole(const LogLevel& level, const String8& message)
{
	const Char8* levelName = LOG_LEVEL_NAMES[static_cast<Int32>(level)];
	std::wprintf(DE_CHAR16("%S | %S\n"), levelName, message.c_str());
}
