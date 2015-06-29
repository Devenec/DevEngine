/**
 * @file core/Log.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Log.h>

using namespace Core;

// Public

void Log::write(const LogLevel& logLevel, const String8& message) const
{
	if(logLevel >= _filterLevel)
		writeToConsole(logLevel, message);
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
Log& Log::operator <<(const String16& characters)
{
	_stream << toString8(characters);
	return *this;
}

// Private

Log::Log()
	: _filterLevel(LogLevel::Debug),
	  _streamLevel(LogLevel::Debug) { }

// Static

// Log::writeToConsole() is defined in platform/*/*Log.cpp
