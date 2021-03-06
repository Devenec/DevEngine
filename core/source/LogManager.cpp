/**
 * @file core/LogManager.cpp
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

#include <new>
#include <core/Array.h>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/Types.h>

using namespace Core;

// External

alignas(Log) static Array<Uint8, sizeof(Log)> defaultLogStorage;


// Core

Log& Core::defaultLog = reinterpret_cast<Log&>(*::defaultLogStorage.data());


// Some members are defined in platform/*/*LogManager.cpp

// Public

void LogManager::deinitialise() const
{
	defaultLog << LogLevel::Debug << "LogManager deinitialising..." << Log::Flush();
	defaultLog.~Log();
}

void LogManager::initialise() const
{
	initialisePlatform();
	::new (static_cast<Void*>(::defaultLogStorage.data())) Log();
	defaultLog << LogLevel::Debug << "LogManager initialised." << Log::Flush();
}
