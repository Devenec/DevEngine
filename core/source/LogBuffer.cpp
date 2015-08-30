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

#include <algorithm>
#include <cstring>
#include <core/Config.h>
#include <core/LogBuffer.h>
#include <core/Numeric.h>

using namespace Core;

// Public

const Uint32 LogBuffer::NON_POSITION = Numeric<Uint32>::maximum();

LogBuffer::LogBuffer(FlushFunction flushFunction)
	: _flushFunction(flushFunction)
{
	_lineBuffer.reserve(Config::LOG_LINE_MAX_WIDTH + 1u);
	_mainBuffer.reserve(Config::LOG_BUFFER_SIZE);
}

void LogBuffer::appendCharacter(const Char8 character)
{
	if(character == '\n' || _lineBuffer.length() == Config::LOG_LINE_MAX_WIDTH)
	{
		appendLineBreakAndIndent();

		if(isWhitespaceCharacter(character))
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

			if(isWhitespaceCharacter(characters[characterOffset]))
				++characterOffset;
		}

		appendToLineBuffer(characters, characterOffset, characterCount);
		Bool hasExplicitLineBreak = false;
		const Uint32 whitespacePosition = findWhitespaceCharacter(hasExplicitLineBreak);

		if(whitespacePosition != NON_POSITION && (hasExplicitLineBreak || _lineBuffer.length() == 120u))
		{
			characterOffset -= _lineBuffer.length() - whitespacePosition - 1u;
			_lineBuffer.resize(whitespacePosition);
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
	characterCount = std::min(availableCapacity, characterCount - characterOffset);
	_lineBuffer.append(characters + characterOffset, characterCount);
	characterOffset += characterCount;
}

Uint32 LogBuffer::findWhitespaceCharacter(Bool& hasExplicitLineBreak) const
{
	Uint32 whitespacePosition = NON_POSITION;

	for(Uint32 i = 8u, end = _lineBuffer.length(); i < end; ++i)
	{
		if(_lineBuffer[i] == '\n')
		{
			hasExplicitLineBreak = true;
			return i;
		}

		if(_lineBuffer[i] == ' ')
			whitespacePosition = i;
	}

	return whitespacePosition;
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

	_mainBuffer.append(_lineBuffer, lineBufferOffset);
	_lineBuffer.clear();
}

void LogBuffer::flushMainBuffer()
{
	_flushFunction(_mainBuffer);
	_mainBuffer.clear();
}
