/**
 * @file platform/windows/WindowsLogManager.cpp
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
