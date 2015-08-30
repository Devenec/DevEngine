/**
 * @file core/Log.h
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

#include <cstdio>
#include <core/Array.h>
#include <core/LogBuffer.h>
#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error
	};

	enum class StreamFormat
	{
		Decimal = 1,
		Hexadecimal = 2,
		Octal = 4
	};

	// TODO: support Char16 characters, c-strings and (std::)strings?
	class Log final
	{
	public:

		struct Flush final { };

		Log(const Log& log) = delete;
		Log(Log&& log) = delete;

		~Log() = default;

		inline LogLevel filterLevel() const;

		inline void setfilterLevel(const LogLevel& level);

		void write(const LogLevel& logLevel, const String8& message);

		Log& operator =(const Log& log) = delete;
		Log& operator =(Log&& log) = delete;

		Log& operator <<(const Bool boolean);

		Log& operator <<(const Int32 interger);

		Log& operator <<(const Uint32 interger);

		Log& operator <<(const Int64 interger);

		Log& operator <<(const Uint64 interger);

		inline Log& operator <<(const Float32 floatingPoint);

		Log& operator <<(const Float64 floatingPoint);

		Log& operator <<(const Char8 character);
		
		inline Log& operator <<(const Char8* characters);

		Log& operator <<(const Void* pointer);

		inline Log& operator <<(const String8& string);

		Log& operator <<(const Flush& flush);

		inline Log& operator <<(const LogLevel& streamLevel);

		inline Log& operator <<(const StreamFormat& streamFormat);

	private:

		friend class LogManager;

		static const Array<const Char8*, 4u> LOG_LEVEL_NAMES;
		static const Char8* LOG_LEVEL_SEPARATOR;

		LogBuffer _streamBuffer;
		LogLevel _filterLevel;
		StreamFormat _streamFormat;
		LogLevel _streamLevel;

		Log();

		void appendStreamLevel(const LogLevel& level);
		void formatUint32FormatString(Char8* format) const;
		void formatUint64FormatString(Char8* format) const;

		static void writeToConsole(const String8& message);

		template<typename... Parameters>
		static inline Uint32 toString(const Char8* format, Char8* buffer, const Uint32 bufferSize,
			Parameters... parameters);
	};

	inline StreamFormat operator &(const StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat& operator &=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat operator |(const StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat& operator |=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

#include "inline/Log.inl"

	extern Log& defaultLog;
}
