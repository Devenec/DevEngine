/**
 * @file core/LogManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Array.h>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/Types.h>

using namespace Core;

static Array<Byte, sizeof(Log)> defaultLogMemory;

// Core

Log& Core::defaultLog = *reinterpret_cast<Log*>(defaultLogMemory.data());


// Public

LogManager::LogManager()
{
	new (defaultLogMemory.data()) Log();
}

LogManager::~LogManager()
{
	defaultLog.~Log();
}

// LogManager::deinitialise() is defined in platform/*/*LogManager.cpp

// LogManager::initialise() is defined in platform/*/*LogManager.cpp
