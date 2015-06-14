/**
 * @file platform/windows/Windows.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Log.h>
#include <platform/windows/Windows.h>

using namespace Core;

// Platform

void Platform::failWindowsAssertion(const Char8* file, const Uint32 line, const Char8* function)
{
	defaultLog << LogLevel::Error << "Windows assertion failed with error code " << GetLastError() << ", at " <<
		file << " on line " << line << " in function " << function << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}

void Platform::invokeWindowsError(const Uint32 errorCode)
{
	defaultLog << LogLevel::Error << "Windows error occurred with code 0x" << std::hex << std::uppercase <<
		errorCode << std::nouppercase << std::dec << '-' << GetLastError() << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}
