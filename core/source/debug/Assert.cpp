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

void Debug::failAssertion(const Char8* expression, const Char8* file, const Char8* function, const Uint32 line)
{
	if(LogManager::hasInstance()) // TODO: what if there is no instance?
	{
		LogManager::instance().log() << LogLevel::Error << "Assertion failed @ " << file << " in function " <<
			function << " on line " << line << ": " << expression << Log::flush;
	}

	DE_DEBUGGER_BREAK();
	std::abort();
}
