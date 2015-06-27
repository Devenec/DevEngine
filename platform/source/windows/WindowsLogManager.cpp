/**
 * @file platform/windows/WindowsLogManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Array.h>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/Types.h>
#include <platform/windows/Windows.h>

using namespace Core;

static Array<Byte, sizeof(Log)> defaultLogMemory;

// Core

Log& Core::defaultLog = *reinterpret_cast<Log*>(defaultLogMemory.data());


// Implementation

class Impl final
{
public:

	Impl() = delete;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = delete;

	static void initialiseConsole()
	{
		const Int32 result = SetConsoleOutputCP(CP_UTF8);
		DE_ASSERT_WINDOWS(result != 0);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;
};


// Public

void LogManager::deinitialise() const
{
	defaultLog.~Log();
}

void LogManager::initialise() const
{
	Impl::initialiseConsole();
	new (defaultLogMemory.data()) Log();
}
