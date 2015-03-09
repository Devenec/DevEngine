/**
 * @file core/LogManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Log.h>
#include <core/Singleton.h>

namespace Core
{
	class LogManager final : public Singleton<LogManager>
	{
	public:

		LogManager();

		~LogManager();

		inline Log& log();

	private:

		Log _log;

		LogManager(const LogManager& logManager) = delete;
		LogManager(LogManager&& logManager) = delete;

		void initialise();

		LogManager& operator =(const LogManager& logManager) = delete;
	};

	Log& LogManager::log()
	{
		return _log;
	}
}
