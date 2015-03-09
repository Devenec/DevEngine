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

void Platform::failWindowsAssertion(const Char* file, const Char* function, const Uint32 line)
{
	if(LogManager::hasInstance())
	{
		LogManager::instance().log() << LogLevel::Error << DE_TEXT("Windows assertion failed @ ") << file <<
			DE_TEXT(" in function ") << function << DE_TEXT(" on line ") << line << DE_TEXT(", error code ") <<
			GetLastError() << Log::flush;
	}

	DE_DEBUG_BREAK();
	std::abort();
}
