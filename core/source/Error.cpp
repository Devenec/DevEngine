/**
 * @file core/Error.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>

void Core::invokeError(const Uint32 errorCode)
{
	defaultLog << LogLevel::Error << "Error occurred with code " << errorCode << '.' << Log::Flush();
	DE_DEBUGGER_BREAK();
	std::abort();
}
