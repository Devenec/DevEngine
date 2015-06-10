/**
 * @file core/Memory.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define _DE_TRACK_ALLOCATIONS
	#include <core/debug/AllocationTracker.h>
	
	using namespace Debug;
#endif

// Core

Void* Core::allocateMemory(const Uint32 byteCount)
{
	Void* pointer = std::malloc(byteCount);

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << "[Core::allocateMemory] Failed to allocate memory." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}

	return pointer;
}

#if defined(_DE_TRACK_ALLOCATIONS)
Void* Core::allocateMemory(const Uint32 byteCount, const Char8* file, const Uint32 line, const Char8* function)
{
	Void* pointer = allocateMemory(byteCount);
	AllocationTracker::instance().registerAllocation(pointer, byteCount, file, line, function);

	return pointer;
}
#endif

void Core::deallocateMemory(Void* pointer, const Uint32 byteCount)
{
#if defined(_DE_TRACK_ALLOCATIONS)
	AllocationTracker::instance().deregisterAllocation(pointer, byteCount);
#endif

	std::free(pointer);
}
