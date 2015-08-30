/**
 * @file core/debug/Assert.cpp
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

#include <core/debug/Assert.h>

#if DE_BUILD != DE_BUILD_PRODUCTION

#include <cstdlib>
#include <core/Log.h>

using namespace Core;

// Debug

void Debug::failAssertion(const Char8* expression, const Char8* file, const Uint32 line, const Char8* function)
{
	defaultLog << LogLevel::Error << "Assertion failed with expression '" << expression << "', at " << file <<
		" on line " << line << " in function " << function << '.' << Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();
}

#endif
