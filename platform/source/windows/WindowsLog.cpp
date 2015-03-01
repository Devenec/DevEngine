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

#define _DE_LOG_MESSAGE_FORMAT "%s | %s\n"

using namespace Core;

// External

static const Array<const Char8*, 4u> LEVEL_IDENTIFIERS_8 =
{
	"DEBUG  ",
	"INFO   ",
	"WARNING",
	"ERROR  "
};

static const Array<const Char16*, 4u> LEVEL_IDENTIFIERS_16 =
{
	L"DEBUG  ",
	L"INFO   ",
	L"WARNING",
	L"ERROR  "
};


// Private

template<>
void Log::writeToConsole(const LogLevel& level, const StringTemplate<Char8>& message)
{
	const Char8* logLevelName = LEVEL_IDENTIFIERS_8[static_cast<Int32>(level)];
	printf(_DE_LOG_MESSAGE_FORMAT, logLevelName, message.c_str());
}

template<>
void Log::writeToConsole<Char16>(const LogLevel& level, const StringTemplate<Char16>& message)
{
	const Char16* logLevelName = LEVEL_IDENTIFIERS_16[static_cast<Int32>(level)];
	wprintf(DE_CHAR16(_DE_LOG_MESSAGE_FORMAT), logLevelName, message.c_str());
}
