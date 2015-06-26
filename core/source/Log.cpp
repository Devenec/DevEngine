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

Log& Log::operator <<(const Flush& flush)
{
	static_cast<Void>(flush);
	write(_streamLevel, _stream.str());
	_stream.str(String8());
	_streamLevel = LogLevel::Debug;

	return *this;
}

template<>
Log& Log::operator <<(const String16& value)
{
	_stream << toString8(value);
	return *this;
}

// Private

Log::Log()
	: _filterLevel(LogLevel::Debug),
	  _streamLevel(LogLevel::Debug) { }

// Static

// Log::writeToConsole() is defined in platform/*/*Log.cpp
