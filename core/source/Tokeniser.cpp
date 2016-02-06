/**
 * @file core/Tokeniser.cpp
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

#include <core/Tokeniser.h>
#include <core/maths/Utility.h>

using namespace Core;
using namespace Maths;

// Public

Tokeniser::Tokeniser(const String8& delimiterCharacters, const String8& whitespaceCharacters)
	: _delimiterCharacters(delimiterCharacters),
	  _whitespaceCharacters(whitespaceCharacters),
	  _tokenStream(nullptr)
{
	_whitespaceCharacters.append(1u, '\r');
}

const TokenList& Tokeniser::tokenise(const String8& tokenStream)
{
	_tokenStream = &tokenStream;
	_tokens.clear();
	Uint streamPosition = 0u;
	const Uint streamEndPosition = _tokenStream->length();

	while(streamPosition < streamEndPosition)
	{
		if(!isWhitespaceCharacter(streamPosition))
		{
			if(isDelimiterCharacter(streamPosition))
			{
				addToken(Token::Type::Delimiter, streamPosition, 1u);
			}
			else
			{
				Uint delimiterPosition = findNextDelimiterPosition(streamPosition);

				if(delimiterPosition == String8::npos)
					delimiterPosition = streamEndPosition;

				addToken(Token::Type::Unknown, streamPosition, delimiterPosition - streamPosition);
				streamPosition = delimiterPosition - 1u;
			}
		}

		++streamPosition;
	}

	return _tokens;
}

// Private

Bool Tokeniser::isWhitespaceCharacter(const Uint streamPosition) const
{
	const Char8 character = (*_tokenStream)[streamPosition];

	for(String8::const_iterator i = _whitespaceCharacters.begin(), end = _whitespaceCharacters.end();
		i != end; ++i)
	{
		if(*i == character)
			return true;
	}

	return false;
}

Bool Tokeniser::isDelimiterCharacter(const Uint streamPosition) const
{
	const Char8 character = (*_tokenStream)[streamPosition];

	for(String8::const_iterator i = _delimiterCharacters.begin(), end = _delimiterCharacters.end(); i != end;
		++i)
	{
		if(*i == character)
			return true;
	}

	return false;
}

void Tokeniser::addToken(const Token::Type& type, const Uint streamPosition, const Uint lexemeLength)
{
	Token token;
	token.lexeme.assign(*_tokenStream, streamPosition, lexemeLength);
	token.type = type;
	_tokens.emplace_back(token);
}

Uint Tokeniser::findNextDelimiterPosition(const Uint streamPosition) const
{
	const Uint whitespacePosition = _tokenStream->find_first_of(_whitespaceCharacters, streamPosition);
	Uint delimiterPosition = _tokenStream->find_first_of(_delimiterCharacters, streamPosition);

	return minimum(whitespacePosition, delimiterPosition);
}
