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

		inline LogLevel filterLevel() const;

		inline void setfilterLevel(const LogLevel& value);

		void write(const LogLevel& level, const String8& message) const;

		inline Log& operator <<(const LogLevel& logLevel);

		inline Log& operator <<(const Flush& flush);

		inline Log& operator <<(const Char16* characters);

		template<typename T>
		inline Log& operator <<(const T& value);

		static inline void flush(Log& log);

	private:

		friend class LogManager;

		StringStream8 _stream;
		LogLevel _filterLevel;
		LogLevel _streamLevel;

		inline Log();
		Log(const Log& log) = delete;
		Log(Log&& log) = delete;
		~Log() = default;

		void writeToConsole(const LogLevel& level, const String8& message) const;

		Log& operator =(const Log& log) = delete;
		Log& operator =(Log&& log) = delete;
	};

#include "inline/Log.inl"
}
