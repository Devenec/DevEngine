/**
 * @file core/LogBuffer.h
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

#include <core/FileStream.h>
#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	class LogBuffer final
	{
	public:

		using FlushFunction = void (*)(const Char8* message);

		static const Uint NON_POSITION;

		explicit LogBuffer(FlushFunction flushFunction);

		LogBuffer(const LogBuffer& logBuffer) = delete;
		LogBuffer(LogBuffer&& logBuffer) = delete;

		~LogBuffer() = default;

		void appendCharacter(const Char8 character);

		void appendCharacters(const Char8* characters, Uint characterCount);

		inline void appendLineBreak();

		void flush();

		LogBuffer& operator =(const LogBuffer& logBuffer) = delete;
		LogBuffer& operator =(LogBuffer&& logBuffer) = delete;

	private:

		String8 _lineBuffer;
		String8 _mainBuffer;
		FileStream _fileStream;
		FlushFunction _flushFunction;

		void openFileStream() const;
		inline void appendLineBreakAndIndent();
		Uint appendToLineBuffer(const Char8* characters, const Char8* charactersEnd);
		void appendLineBuffer();
		void flushMainBuffer();
	};

#include "inline/LogBuffer.inl"
}
