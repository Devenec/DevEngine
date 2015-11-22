/**
 * @file platform/windows/Windows.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <cstdlib>
#include <core/Log.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

using namespace Core;

// Platform

void Platform::failWindowsAssertion(const Char8* file, const Uint32 line, const Char8* function)
{
	defaultLog << LogLevel::Error << "Windows assertion failed at " << file << ", on line " << line <<
		", in function " << function << ", with error code " << getWindowsErrorCode() << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}

HDC Platform::getWindowDeviceContextHandle(HWND windowHandle)
{
	DE_ASSERT(windowHandle != nullptr);
	HDC deviceContextHandle = GetDC(windowHandle);

	if(deviceContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << "[Platform::getWindowDeviceContextHandle() - Windows]"
			" Failed to get the device context handle of a window." << Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return deviceContextHandle;
}

Uint32 Platform::getWindowsErrorCode()
{
	const Uint32 errorCode = GetLastError();
	SetLastError(0u);

	return errorCode;
}

void Platform::invokeWindowsError(const Uint32 errorCode)
{
	defaultLog << LogLevel::Error << "Windows error occurred with code " << StreamFormat::Hexadecimal << errorCode <<
		StreamFormat::Decimal << '-' << getWindowsErrorCode() << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}
