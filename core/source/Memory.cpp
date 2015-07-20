/**
 * @file core/Memory.cpp
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

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>

#if DE_BUILD != DE_BUILD_PRODUCTION && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define DE_INTERNAL_TRACK_ALLOCATIONS
	#include <core/debug/AllocationTracker.h>
#endif

// Core

Void* Core::allocateMemory(const Uint32 size)
{
	DE_ASSERT(size > 0u);
	Void* pointer = std::malloc(size);

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << "[Core::allocateMemory] Failed to allocate memory." << Log::Flush();
		DE_ERROR(0x0);
	}

	return pointer;
}

#if defined(DE_INTERNAL_TRACK_ALLOCATIONS)
Void* Core::allocateMemory(const Uint32 size, const Char8* file, const Uint32 line, const Char8* function)
{
	Void* pointer = allocateMemory(size);
	Debug::AllocationTracker::instance().registerAllocation(pointer, size, file, line, function);

	return pointer;
}
#endif

void Core::deallocateMemory(Void* pointer, const Uint32 size)
{
#if defined(DE_INTERNAL_TRACK_ALLOCATIONS)
	if(pointer != nullptr)
		Debug::AllocationTracker::instance().deregisterAllocation(pointer, size);
#else
	static_cast<Void>(size);
#endif

	std::free(pointer);
}
