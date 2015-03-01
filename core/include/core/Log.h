/**
 * @file core/Log.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/StringStream.h>
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

	class Log final
	{
	public:

		typedef void (*Flush)(Log& log);

		Log();

		~Log();

		inline LogLevel filterLevel() const;

		inline void setfilterLevel(const LogLevel& value);

		void write(const LogLevel& level, const String& message);

		inline Log& operator <<(const LogLevel& value);

		inline Log& operator <<(const Flush& flush);

		template<typename T>
		Log& operator <<(const T& value);

		static inline void flush(Log& log);

	private:

		StringStreamTemplate<Char> _stream;
		LogLevel _filterLevel;
		LogLevel _streamLevel;

		Log(const Log& log) = delete;
		Log(Log&& log) = delete;

		template<typename T>
		void writeToConsole(const LogLevel& level, const StringTemplate<T>& message);

		Log& operator =(const Log& log) = delete;
	};

#include "Log.inl"
}
