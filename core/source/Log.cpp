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

// Some members are defined in platform/*/*Log.cpp

// Public

void Log::write(const LogLevel& logLevel, const String8& message) const
{
	if(logLevel >= _filterLevel)
	{
		const String8 parsedMessage = parseMessage(message);
		writeToConsole(logLevel, parsedMessage);
	}
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

String8 Log::parseMessage(String8 message)
{
	Uint32 currentPosition = 0u;
	Uint32 lineBreakPosition;

	while((lineBreakPosition = message.find('\n', currentPosition)) != String8::npos ||
		message.length() > currentPosition + MAX_LINE_LENGTH)
	{
		if(lineBreakPosition == String8::npos)
			lineBreakPosition = message.rfind(' ', currentPosition + MAX_LINE_LENGTH - 1u);

		if(lineBreakPosition == String8::npos || lineBreakPosition > currentPosition + MAX_LINE_LENGTH)
		{
			lineBreakPosition = currentPosition + MAX_LINE_LENGTH;
			currentPosition = 0u;
		}
		else
		{
			currentPosition = 1u;
		}

		message.replace(lineBreakPosition, currentPosition, LINE_BREAK);
		currentPosition = lineBreakPosition + LINE_BREAK_LENGTH;
	}

	return message;
}
