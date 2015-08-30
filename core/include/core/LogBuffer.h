/**
 * @file core/LogBuffer.h
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

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	using FlushFunction = void (*)(const String8& message);

	class LogBuffer final
	{
	public:

		static const Uint32 NON_POSITION;

		explicit LogBuffer(FlushFunction flushFunction);

		LogBuffer(const LogBuffer& logBuffer) = delete;
		LogBuffer(LogBuffer&& logBuffer) = delete;

		~LogBuffer() = default;

		void appendCharacter(const Char8 character);

		void appendCharacters(const Char8* characters, Uint32 characterCount);

		inline void appendLineBreak();

		void flush();

		LogBuffer& operator =(const LogBuffer& logBuffer) = delete;
		LogBuffer& operator =(LogBuffer&& logBuffer) = delete;

	private:

		String8 _lineBuffer;
		String8 _mainBuffer;
		FlushFunction _flushFunction;

		inline void appendLineBreakAndIndent();
		void appendToLineBuffer(const Char8* characters, Uint32& characterOffset, Uint32 characterCount);
		Uint32 findWhitespaceCharacter(Bool& hasExplicitLineBreak) const;
		void appendLineBuffer();
		void flushMainBuffer();

		static inline Bool isWhitespaceCharacter(const Char8 character);
	};

#include "inline/LogBuffer.inl"
}
