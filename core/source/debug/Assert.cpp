/**
 * @file core/debug/Assert.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Log.h>
#include <core/debug/Assert.h>

using namespace Core;

// Debug

void Debug::failAssertion(const Char8* expression, const Char8* file, const Uint32 line, const Char8* function)
{
	defaultLog << LogLevel::Error << "Assertion failed with expression '" << expression << "', at " << file <<
		" on line " << line << " in function " << function << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}
