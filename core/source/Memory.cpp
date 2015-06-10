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
#include <core/debug/AllocationTracker.h>

using namespace Debug;

Void* Core::allocate(const Uint32 byteCount)
{
	Void* pointer = std::malloc(byteCount);

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << "[Core::allocate] Failed to allocate memory." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}

	return pointer;
}

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
Void* Core::allocate(const Uint32 byteCount, const Char8* file, const Uint32 line, const Char8* function)
{
	Void* pointer = allocate(byteCount);

	if(AllocationTracker::hasInstance())
		AllocationTracker::instance().registerAllocation(pointer, file, line, function);

	return pointer;
}
#endif

void Core::deallocate(Void* pointer)
{
#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	if(AllocationTracker::hasInstance())
		AllocationTracker::instance().deregisterAllocation(pointer);
#endif

	std::free(pointer);
}
