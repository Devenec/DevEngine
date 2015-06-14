/**
 * @file core/Error.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>

// Core

void Core::invokeError(const Uint32 errorCode)
{
	defaultLog << LogLevel::Error << "Error occurred with code 0x" << std::hex << std::uppercase << errorCode <<
		std::nouppercase << std::dec << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}
