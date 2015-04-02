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

// External

static const Array<const Char8*, 4u> LOG_LEVEL_IDENTIFIERS =
{
	"DEBUG  ",
	"INFO   ",
	"WARNING",
	"ERROR  "
};


// Private

void Log::writeToConsole(const LogLevel& level, const String8& message) const
{
	const Char8* logLevelName = LOG_LEVEL_IDENTIFIERS[static_cast<Int32>(level)];
	std::wprintf(DE_CHAR16("%S | %S\n"), logLevelName, message.c_str());
}
