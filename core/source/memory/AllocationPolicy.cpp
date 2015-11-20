/**
 * @file core/memory/AllocationPolicy.cpp
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
#include <core/Error.h>
#include <core/Log.h>
#include <core/memory/AllocationPolicy.h>

using namespace Core;
using namespace Memory;

// External

static const Char8* COMPONENT_TAG = "[Memory::AllocationPolicy]";


// Public

// Static

Void* AllocationPolicy::allocate(const Uint32 size, const Char8* file, const Uint32 line, const Char8* function)
{
	DE_ASSERT(size > 0u);
	Void* pointer = std::malloc(size);

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to allocate memory." << Log::Flush();
		DE_ERROR(0x0);
	}

	Base::registerAllocation(pointer, size, file, line, function);
	return pointer;
}

void AllocationPolicy::deallocate(Void* pointer, const Uint32 size)
{
	Base::deregisterAllocation(pointer, size);
	std::free(pointer);
}
