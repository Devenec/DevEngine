/**
 * @file platform/posix/POSIX.cpp
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

#include <cstdlib>
#include <errno.h>
#include <core/Log.h>
#include <platform/posix/POSIX.h>

using namespace Core;

// Platform

void Platform::invokePOSIXError(const Uint32 errorCode)
{
	defaultLog << LogLevel::Error << "POSIX error occurred with code " << StreamFormat::Hexadecimal <<
		errorCode << StreamFormat::Decimal << '-' << errno << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}

void Platform::invokePOSIXError(const Uint32 errorCode, const Char8* file, const Uint32 line,
	const Char8* function)
{
	defaultLog << LogLevel::Error << "POSIX error occurred at " << file << ", on line " << line <<
		", in function " << function << ", with code " << StreamFormat::Hexadecimal << errorCode <<
		StreamFormat::Decimal << '-' << errno << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}
