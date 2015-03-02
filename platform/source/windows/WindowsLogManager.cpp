/**
 * @file platform/windows/LogManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/ConfigMacros.h>
#include <core/LogManager.h>

#if defined(DE_CONFIG_CHAR16)
	#include <fcntl.h>
	#include <io.h>
#endif

using namespace Core;

// Private

void LogManager::initialise()
{
#if defined(DE_CONFIG_CHAR16)
	_setmode(_fileno(stdout), _O_U16TEXT);
#endif
}
