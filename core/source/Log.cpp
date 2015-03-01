/**
 * @file core/Log.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Log.h>

using namespace Core;

// Public

Log::Log()
	: _filterLevel(LogLevel::Debug),
	  _streamLevel(LogLevel::Debug) { }

Log::~Log() { }

void Log::write(const LogLevel& level, const String& message)
{
	if(level >= _filterLevel)
		writeToConsole(level, message);
}
