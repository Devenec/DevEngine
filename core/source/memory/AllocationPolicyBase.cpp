/**
 * @file core/memory/AllocationPolicyBase.cpp
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

#include <core/ConfigInternal.h>
#include <core/memory/AllocationPolicyBase.h>

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)
	#include <core/debug/AllocationTracker.h>
#endif

using namespace Memory;

// Protected

// Static

void AllocationPolicyBase::deregisterAllocation(Void* pointer, const Uint32 size)
{

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)

	if(pointer != nullptr)
		Debug::AllocationTracker::instance().deregisterAllocation(pointer, size);

#else

	static_cast<Void>(pointer);
	static_cast<Void>(size);

#endif

}

void AllocationPolicyBase::registerAllocation(Void* pointer, const Uint32 size, const Char8* file,
	const Uint32 line, const Char8* function)
{

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)

	Debug::AllocationTracker::instance().registerAllocation(pointer, size, file, line, function);

#else

	static_cast<Void>(pointer);
	static_cast<Void>(size);
	static_cast<Void>(file);
	static_cast<Void>(line);
	static_cast<Void>(function);

#endif

}
