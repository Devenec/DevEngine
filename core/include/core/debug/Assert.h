/**
 * @file core/debug/Assert.h
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

#pragma once

#include <core/ConfigInternal.h>
#include <core/UtilityMacros.h>

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)

#include <core/Types.h>

#define DE_ASSERT(expression) \
	(expression) ? DE_NO_OPERATION : \
		Debug::failAssertion(DE_TO_STRING8(expression), DE_FILE, DE_LINE, DE_FUNCTION)

namespace Debug
{
	void failAssertion(const Char8* expression, const Char8* file, const Uint32 line, const Char8* function);
}

#else

#define DE_ASSERT(expression) \
	DE_NO_OPERATION

#endif
