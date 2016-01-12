/**
 * @file core/LogBuffer.cpp
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

#include <algorithm>
#include <cstring>
#include <core/Config.h>
#include <core/FileSystem.h>
#include <core/LogBuffer.h>
#include <core/Numeric.h>
#include <core/maths/Utility.h>

using namespace Core;
using namespace Maths;

// External

static Bool isWhitespaceCharacter(const Char8 character);


// Public

const Uint LogBuffer::NON_POSITION = Numeric<Uint>::maximum();

LogBuffer::LogBuffer(FlushFunction flushFunction)
	: _flushFunction(flushFunction)
{
	_lineBuffer.reserve(Config::LOG_LINE_MAX_WIDTH + 1u);
	_mainBuffer.reserve(Config::LOG_BUFFER_SIZE);
	openFileStream();
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

void LogBuffer::appendCharacters(const Char8* characters, Uint characterCount)
{
	if(characterCount == NON_POSITION)
		characterCount = std::strlen(characters);

	const Char8* charactersEnd = characters + characterCount;

	while(characters < charactersEnd)
	{
		if(_lineBuffer.length() == Config::LOG_LINE_MAX_WIDTH)
		{
			appendLineBreakAndIndent();

			if(::isWhitespaceCharacter(*characters))
				++characters;
		}

		characters += appendToLineBuffer(characters, charactersEnd);
	}
}

void LogBuffer::flush()
{
	if(_lineBuffer.length() > 0u)
		appendLineBuffer();

	flushMainBuffer();
}

// Private

void LogBuffer::openFileStream() const
{
	const String8 logFilepath = FileSystem::getDefaultContentRootDirectory() + "log";
	_fileStream.open(logFilepath, OpenMode::Write | OpenMode::Truncate);
}

Uint LogBuffer::appendToLineBuffer(const Char8* characters, const Char8* charactersEnd)
{
	const Char8* lineBreakPosition = std::find(characters, charactersEnd, '\n');
	const Uint availableCapacity = Config::LOG_LINE_MAX_WIDTH - _lineBuffer.length();
	Uint characterCount = minimum(availableCapacity, static_cast<Uint>(charactersEnd - characters));

	if(lineBreakPosition != charactersEnd)
		characterCount = lineBreakPosition - characters;

	_lineBuffer.append(characters, characterCount);

	if(lineBreakPosition != charactersEnd)
	{
		appendLineBreakAndIndent();
		++characterCount;
	}

	return characterCount;
}

void LogBuffer::appendLineBuffer()
{
	const Uint availableMainBufferCapacity = _mainBuffer.capacity() - _mainBuffer.length();
	Uint lineBufferOffset = 0u;

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
	_flushFunction(_mainBuffer.c_str());

	if(_fileStream.isOpen())
	{
		_fileStream.write(reinterpret_cast<const Uint8*>(_mainBuffer.c_str()),
			static_cast<Uint32>(_mainBuffer.length()));
	}

	_mainBuffer.clear();
}


// External

static Bool isWhitespaceCharacter(const Char8 character)
{
	return character == '\n' || character == ' ';
}
