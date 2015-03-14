/**
 * @file platform/windows/Windows.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Log.h>
#include <core/LogManager.h>
#include <platform/windows/Windows.h>

using namespace Core;

// Platform

void Platform::failWindowsAssertion(const Char8* file, const Char8* function, const Uint32 line)
{
	if(LogManager::hasInstance())
	{
		LogManager::instance().log() << LogLevel::Error << "Windows assertion failed @ " << file << " in function " <<
			function << " on line " << line << ", error code " << GetLastError() << Log::flush;
	}

	DE_DEBUGGER_BREAK();
	std::abort();
}
