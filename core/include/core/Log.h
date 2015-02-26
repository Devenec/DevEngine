/**
 * @file core/Log.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	enum class LogLevel
	{
		Debug,
		Warning,
		Error
	};

	class Log final
	{
	public:

		Log();

		~Log();

		LogLevel filterLevel() const;

		void setfilterLevel(const LogLevel& value);

		void write(const LogLevel& level, const Char8* message);

		void write(const LogLevel& level, const Char16* message);

		template<typename T>
		void write(const LogLevel& level, const StringTemplate<T>& message);

	private:

		LogLevel _filterLevel;

		Log(const Log& log) = delete;
		Log(Log&& log) = delete;

		template<typename T>
		void writeToConsole(const LogLevel& level, const StringTemplate<T>& message);

		Log& operator =(const Log& log) = delete;
	};

#include "Log.inl"
}
