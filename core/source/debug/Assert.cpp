/**
 * @file core/debug/Assert.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/debug/Assert.h>

using namespace Core;

// Debug

void Debug::failAssertion(const Char* expression, const Char* file, const Char* function, const Uint32 line)
{
	if(LogManager::hasInstance())
	{
		LogManager::instance().log() << LogLevel::Error << DE_TEXT("Assertion failed @ ") << file <<
			DE_TEXT(" in function ") << function << DE_TEXT(" on line ") << line << DE_TEXT(": ") << expression <<
			Log::flush;
	}

	DE_DEBUG_BREAK();
	std::abort();
}
