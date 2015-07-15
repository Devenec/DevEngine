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

#include <core/String.h>
#include <core/StringStream.h>
#include <core/Types.h>
#include <core/debug/Assert.h>

namespace Core
{
	enum class LogLevel
	{
		Debug,
		Info,
		Warning,
		Error
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

		void write(const LogLevel& logLevel, const String8& message) const;

		Log& operator =(const Log& log) = delete;
		Log& operator =(Log&& log) = delete;

		inline Log& operator <<(const Char16* characters);

		Log& operator <<(const Flush& flush);

		inline Log& operator <<(const LogLevel& logLevel);

		template<typename T>
		inline Log& operator <<(const T& value);

	private:

		friend class LogManager;

		StringStream8 _stream;
		LogLevel _filterLevel;
		LogLevel _streamLevel;

		Log();

		static void writeToConsole(const LogLevel& logLevel, const String8& message);
	};

#include "inline/Log.inl"

	extern Log& defaultLog;
}
