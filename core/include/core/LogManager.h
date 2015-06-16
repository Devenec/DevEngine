/**
 * @file core/LogManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Singleton.h>

namespace Core
{
	class LogManager final : public Singleton<LogManager>
	{
	public:

		LogManager() = default;

		LogManager(const LogManager& logManager) = delete;
		LogManager(LogManager&& logManager) = delete;

		~LogManager() = default;

		void deinitialise();

		void initialise();

		LogManager& operator =(const LogManager& logManager) = delete;
		LogManager& operator =(LogManager&& logManager) = delete;
	};
}
