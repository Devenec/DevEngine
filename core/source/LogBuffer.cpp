/**
 * @file core/LogBuffer.cpp
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

#include <cstring>
#include <core/Config.h>
#include <core/LogBuffer.h>
#include <core/Numeric.h>
#include <core/maths/Utility.h>

using namespace Core;
using namespace Maths;

// External

static Bool isWhitespaceCharacter(const Char8 character);


// Public

const Uint32 LogBuffer::NON_POSITION = Numeric<Uint32>::maximum();

LogBuffer::LogBuffer(FlushFunction flushFunction)
	: _fileStream("log", OpenMode::Write | OpenMode::Truncate),
	  _flushFunction(flushFunction)
{
	_lineBuffer.reserve(Config::LOG_LINE_MAX_WIDTH + 1u);
	_mainBuffer.reserve(Config::LOG_BUFFER_SIZE);
}

void LogBuffer::appendCharacter(const Char8 character)
{
	if(character == '\n' || _lineBuffer.length() == Config::LOG_LINE_MAX_WIDTH)
	{
		appendLineBreakAndIndent();

		if(::isWhitespaceCharacter(character))
			return;
	}

	_lineBuffer.append(1u, character);
}

void LogBuffer::appendCharacters(const Char8* characters, Uint32 characterCount)
{
	if(characterCount == NON_POSITION)
		characterCount = std::strlen(characters);

	Uint32 characterOffset = 0u;

	while(characterOffset < characterCount)
	{
		if(_lineBuffer.length() == Config::LOG_LINE_MAX_WIDTH)
		{
			appendLineBreakAndIndent();

			if(::isWhitespaceCharacter(characters[characterOffset]))
				++characterOffset;
		}

		appendToLineBuffer(characters, characterOffset, characterCount);
		const Uint32 lineBreakPosition = _lineBuffer.find('\n', 8u);

		if(lineBreakPosition != NON_POSITION)
		{
			characterOffset -= _lineBuffer.length() - lineBreakPosition - 1u;
			_lineBuffer.resize(lineBreakPosition);
			appendLineBreakAndIndent();
		}
	}
}

void LogBuffer::flush()
{
	if(_lineBuffer.length() > 0u)
		appendLineBuffer();

	flushMainBuffer();
}

// Private

void LogBuffer::appendToLineBuffer(const Char8* characters, Uint32& characterOffset, Uint32 characterCount)
{
	const Uint32 availableCapacity = Config::LOG_LINE_MAX_WIDTH - _lineBuffer.length();
	characterCount = minimum(availableCapacity, characterCount - characterOffset);
	_lineBuffer.append(characters + characterOffset, characterCount);
	characterOffset += characterCount;
}

void LogBuffer::appendLineBuffer()
{
	const Uint32 availableMainBufferCapacity = _mainBuffer.capacity() - _mainBuffer.length();
	Uint32 lineBufferOffset = 0u;

	if(_lineBuffer.length() > availableMainBufferCapacity)
	{
		_mainBuffer.append(_lineBuffer, 0u, availableMainBufferCapacity);
		flushMainBuffer();
		lineBufferOffset = availableMainBufferCapacity;
	}

	_mainBuffer.append(_lineBuffer, lineBufferOffset, String8::npos);
	_lineBuffer.clear();
}

void LogBuffer::flushMainBuffer()
{
	_flushFunction(_mainBuffer);
	_fileStream.write(reinterpret_cast<const Byte*>(_mainBuffer.c_str()), _mainBuffer.length());
	_mainBuffer.clear();
}


// External

static Bool isWhitespaceCharacter(const Char8 character)
{
	return character == '\n' || character == ' ';
}
