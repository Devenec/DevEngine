/**
 * @file core/Tokeniser.h
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

#pragma once

#include <core/String.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Core
{
	struct Token
	{
		enum class Type
		{
			Delimiter,
			Unknown
		};

		String8 lexeme;
		Type type;
	};

	using TokenList = Vector<Token>;

	class Tokeniser
	{
	public:

		Tokeniser(const String8& delimiterCharacters = String8(),
			const String8& whitespaceCharacters = String8());

		Tokeniser(const Tokeniser& tokeniser) = delete;
		Tokeniser(Tokeniser&& tokeniser) = delete;

		~Tokeniser() = default;

		const TokenList& tokenise(const String8& tokenStream);

		Tokeniser& operator =(const Tokeniser& tokeniser) = delete;
		Tokeniser& operator =(Tokeniser&& tokeniser) = delete;

	private:

		String8 _delimiterCharacters;
		String8 _whitespaceCharacters;
		TokenList _tokens;
		const String8* _tokenStream;

		Bool isWhitespaceCharacter(const Uint streamPosition) const;
		Bool isDelimiterCharacter(const Uint streamPosition) const;
		void addToken(const Token::Type& type, const Uint streamPosition, const Uint lexemeLength);
		Uint findNextDelimiterPosition(const Uint streamPosition) const;
	};
}
