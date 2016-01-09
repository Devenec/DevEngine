/**
 * @file core/Log.h
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
		Decimal		= 1,
		Hexadecimal = 2,
		Octal		= 4
	};

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

		Log& operator <<(const Int32 integer);

		inline Log& operator <<(const Uint32 integer);

		Log& operator <<(const Int64 integer);

		inline Log& operator <<(const Uint64 integer);

		inline Log& operator <<(const Float32 floatingPoint);

		Log& operator <<(const Float64 floatingPoint);

		Log& operator <<(const Char8 character);
		
		inline Log& operator <<(const Char8* characters);

		Log& operator <<(const Void* pointer);

		inline Log& operator <<(const String8& string);

		Log& operator <<(const Flush& flush);

		Log& operator <<(const LogLevel& streamLevel);

		inline Log& operator <<(const StreamFormat& streamFormat);

	private:

		friend class LogManager;

		LogBuffer _streamBuffer;
		LogLevel _filterLevel;
		StreamFormat _streamFormat;
		LogLevel _streamLevel;

		Log();

		void appendStreamLevel(const LogLevel& level);
		void appendUint32(const Uint32 integer);
		void appendUint64(const Uint64 integer);
		void createUint32Format(Char8* formatBuffer) const;
		void createUint64Format(Char8* formatBuffer) const;

		static void writeToConsole(const Char8* message);
	};

	inline StreamFormat operator &(StreamFormat streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat& operator &=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat operator |(StreamFormat streamFormatA, const StreamFormat& streamFormatB);

	inline StreamFormat& operator |=(StreamFormat& streamFormatA, const StreamFormat& streamFormatB);

#include "inline/Log.inl"

	extern Log& defaultLog;
}
