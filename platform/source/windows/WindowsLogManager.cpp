/**
 * @file platform/windows/WindowsLogManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/LogManager.h>
#include <core/Types.h>
#include <platform/windows/Windows.h>

using namespace Core;

// Public

void LogManager::deinitialise() { }

void LogManager::initialise()
{
	// TODO: should console be supported in production build?
	const Int32 result = SetConsoleOutputCP(CP_UTF8);
	DE_ASSERT_WINDOWS(result != 0);
}
