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

		inline LogManager();

		~LogManager() = default;

		inline Log& log();

	private:

		Log _log;

		LogManager(const LogManager& logManager) = delete;
		LogManager(LogManager&& logManager) = delete;

		void initialise() const;

		LogManager& operator =(const LogManager& logManager) = delete;
		LogManager& operator =(LogManager&& logManager) = delete;
	};

#include "inline/LogManager.inl"
}
