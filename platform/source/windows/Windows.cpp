/**
 * @file platform/windows/Windows.cpp
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

#include <codecvt>
#include <cstdlib>
#include <locale>
#include <core/Log.h>
#include <core/Rectangle.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Memory;

// External

using StringConverter =
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t, STDAllocator<wchar_t>,
		STDAllocator<Char8>>;


// Platform

Core::Rectangle Platform::createRectangle(const RECT& rectangle)
{
	const Int32 width = rectangle.right - rectangle.left;
	const Int32 height = rectangle.bottom - rectangle.top;

	return Core::Rectangle(rectangle.left, rectangle.top, width, height);
}

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
	defaultLog << LogLevel::Error << "Windows error occurred with code " << StreamFormat::Hexadecimal <<
		errorCode << StreamFormat::Decimal << '-' << getWindowsErrorCode() << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}

String8 Platform::fromWideString(const WideString& string)
{
	StringConverter converter;
	return converter.to_bytes(string);
}

Platform::WideString Platform::toWideString(const Core::String8& string)
{
	StringConverter converter;
	return converter.from_bytes(string);
}
