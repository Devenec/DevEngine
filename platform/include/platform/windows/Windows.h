/**
 * @file platform/windows/Windows.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <core/UtilityMacros.h>
#include <core/Types.h>

#define DE_ASSERT_WINDOWS(expression) \
	(expression) ? DE_NO_OPERATION : Platform::failWindowsAssertion(DE_FILE, DE_FUNCTION, DE_LINE)

namespace Platform
{
	void failWindowsAssertion(const Char* file, const Char* function, const Uint32 line);
}
