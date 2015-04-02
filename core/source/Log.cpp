/**
 * @file core/Log.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Log.h>

using namespace Core;

// Public

void Log::write(const LogLevel& level, const String8& message) const
{
	if(level >= _filterLevel)
		writeToConsole(level, message);
}

// Operators

template<>
Log& Log::operator <<(const String16& value)
{
	_stream << toString8(value);
	return *this;
}
