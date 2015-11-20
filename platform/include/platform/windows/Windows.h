/**
 * @file platform/windows/Windows.h
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

#pragma once

#if !defined(WIN32_LEAN_AND_MEAN)
	#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <core/ConfigInternal.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)
	#define DE_ASSERT_WINDOWS(expression) \
		(expression) ? DE_NO_OPERATION : Platform::failWindowsAssertion(DE_FILE, DE_LINE, DE_FUNCTION)

	#define DE_ERROR_WINDOWS(errorCode) \
		Platform::failWindowsAssertion(DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_ASSERT_WINDOWS(expression) \
		DE_NO_OPERATION

	#define DE_ERROR_WINDOWS(errorCode) \
		Platform::invokeWindowsError(errorCode)
#endif

namespace Platform
{
	void failWindowsAssertion(const Char8* file, const Uint32 line, const Char8* function);

	HDC getWindowDeviceContextHandle(HWND windowHandle);

	Uint32 getWindowsErrorCode();

	void invokeWindowsError(const Uint32 errorCode);
}
