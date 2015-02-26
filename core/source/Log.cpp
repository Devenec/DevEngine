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
	: _filterLevel(LogLevel::Debug) { }

Log::~Log() { }

LogLevel Log::filterLevel() const
{
	return _filterLevel;
}

void Log::setfilterLevel(const LogLevel& value)
{
	_filterLevel = value;
}

void Log::write(const LogLevel& level, const Char8* message)
{
	write<Char8>(level, message);
}

void Log::write(const LogLevel& level, const Char16* message)
{
	write<Char16>(level, message);
}
