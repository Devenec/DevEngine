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
#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_ASSERT_WINDOWS(expression) \
		DE_NO_OPERATION

	#define DE_ERROR_WINDOWS(errorCode) \
		Platform::invokeWindowsError(errorCode)
#else
	#define DE_ASSERT_WINDOWS(expression) \
		(expression) ? DE_NO_OPERATION : Platform::failWindowsAssertion(DE_FILE, DE_LINE, DE_FUNCTION)

	#define DE_ERROR_WINDOWS(errorCode) \
		Platform::failWindowsAssertion(DE_FILE, DE_LINE, DE_FUNCTION)
#endif

namespace Platform
{
	void failWindowsAssertion(const Char8* file, const Uint32 line, const Char8* function);

	void invokeWindowsError(const Uint32 errorCode);
}
