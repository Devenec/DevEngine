/**
 * @file core/Log.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Array.h>
#include <core/Log.h>

using namespace Core;

// External

static const Array<const Char8*, 4u> LOG_LEVEL_NAMES =
{
	"DEBUG",
	"INFO ",
	"WARN ",
	"ERROR"
};

static const Char8* LOG_LEVEL_SEPARATOR = " | ";


// Some functions are defined in platform/*/*Log.cpp

// Public

void Log::write(const LogLevel& logLevel, const String8& message)
{
	if(logLevel >= _filterLevel)
	{
		appendStreamLevel(logLevel);
		_streamBuffer.appendCharacters(message.c_str(), message.length());
		_streamBuffer.flush();
	}
}

// Operators

Log& Log::operator <<(const Bool boolean)
{
	if(_streamLevel >= _filterLevel)
	{
		const Char8* characters = boolean ? "true" : "false";
		_streamBuffer.appendCharacters(characters, LogBuffer::NON_POSITION);
	}

	return *this;
}

Log& Log::operator <<(const Int32 integer)
{
	if(_streamLevel >= _filterLevel)
	{
		if((_streamFormat & StreamFormat::Hexadecimal) == StreamFormat::Hexadecimal ||
			(_streamFormat & StreamFormat::Octal) == StreamFormat::Octal)
		{
			appendUint32(integer);
		}
		else
		{
			Char8 buffer[12];
			const Uint32 characterCount = toString("%d", buffer, sizeof(buffer), static_cast<Uint32>(integer));
			_streamBuffer.appendCharacters(buffer, characterCount);
		}
	}

	return *this;
}

Log& Log::operator <<(const Int64 integer)
{
	if(_streamLevel >= _filterLevel)
	{
		if((_streamFormat & StreamFormat::Hexadecimal) == StreamFormat::Hexadecimal ||
			(_streamFormat & StreamFormat::Octal) == StreamFormat::Octal)
		{
			appendUint64(integer);
		}
		else
		{
			Char8 buffer[22];
			const Uint32 characterCount = toString("%lld", buffer, sizeof(buffer), static_cast<Uint64>(integer));
			_streamBuffer.appendCharacters(buffer, characterCount);
		}
	}

	return *this;
}

Log& Log::operator <<(const Float64 floatingPoint)
{
	if(_streamLevel >= _filterLevel)
	{
		Char8 buffer[31];
		const Uint32 characterCount = toString("%f", buffer, sizeof(buffer), floatingPoint);
		_streamBuffer.appendCharacters(buffer, characterCount);
	}

	return *this;
}

Log& Log::operator <<(const Char8 character)
{
	if(_streamLevel >= _filterLevel)
		_streamBuffer.appendCharacter(character);

	return *this;
}

Log& Log::operator <<(const Void* pointer)
{
	if(_streamLevel >= _filterLevel)
	{
		Char8 buffer[19];
		const Uint32 characterCount = toString("0x%X", buffer, sizeof(buffer), reinterpret_cast<Uint64>(pointer));
		_streamBuffer.appendCharacters(buffer, characterCount);
	}

	return *this;
}

Log& Log::operator <<(const Flush& flush)
{
	static_cast<Void>(flush);
	_streamBuffer.flush();

	return *this;
}

Log& Log::operator <<(const LogLevel& streamLevel)
{
	_streamLevel = streamLevel;
	
	if(streamLevel >= _filterLevel)
		appendStreamLevel(_streamLevel);

	return *this;
}

// Private

Log::Log()
	: _streamBuffer(writeToConsole),
	  _filterLevel(LogLevel::Debug),
	  _streamFormat(StreamFormat::Decimal),
	  _streamLevel(LogLevel::Debug) { }

void Log::appendStreamLevel(const LogLevel& level)
{
	_streamBuffer.appendLineBreak();
	const Char8* levelName = ::LOG_LEVEL_NAMES[static_cast<Int32>(level)];
	_streamBuffer.appendCharacters(levelName, LogBuffer::NON_POSITION);
	_streamBuffer.appendCharacters(::LOG_LEVEL_SEPARATOR, LogBuffer::NON_POSITION);
}

void Log::appendUint32(const Uint32 integer)
{
	Char8 format[5] = "";
	formatUint32FormatCharacters(format);
	Char8 buffer[13];
	const Uint32 characterCount = toString(format, buffer, sizeof(buffer), integer);
	_streamBuffer.appendCharacters(buffer, characterCount);
}

void Log::appendUint64(const Uint64 integer)
{
	Char8 format[7] = "";
	formatUint64FormatCharacters(format);
	Char8 buffer[24];
	const Uint32 characterCount = toString(format, buffer, sizeof(buffer), integer);
	_streamBuffer.appendCharacters(buffer, characterCount);
}

void Log::formatUint32FormatCharacters(Char8* format) const
{
	if((_streamFormat & StreamFormat::Decimal) == StreamFormat::Decimal)
	{
		format[0] = '%';
		format[1] = 'u';
	}
	else if((_streamFormat & StreamFormat::Hexadecimal) == StreamFormat::Hexadecimal)
	{
		format[0] = '0';
		format[1] = 'x';
		format[2] = '%';
		format[3] = 'X';
	}
	else if((_streamFormat & StreamFormat::Octal) == StreamFormat::Octal)
	{
		format[0] = '0';
		format[1] = '%';
		format[2] = 'o';
	}
}

void Log::formatUint64FormatCharacters(Char8* format) const
{
	if((_streamFormat & StreamFormat::Decimal) == StreamFormat::Decimal)
	{
		format[0] = '%';
		format[1] = 'l';
		format[2] = 'l';
		format[3] = 'u';
	}
	else if((_streamFormat & StreamFormat::Hexadecimal) == StreamFormat::Hexadecimal)
	{
		format[0] = '0';
		format[1] = 'x';
		format[2] = '%';
		format[3] = 'l';
		format[4] = 'l';
		format[5] = 'X';
	}
	else if((_streamFormat & StreamFormat::Octal) == StreamFormat::Octal)
	{
		format[0] = '0';
		format[1] = '%';
		format[2] = 'l';
		format[3] = 'l';
		format[4] = 'o';
	}
}
