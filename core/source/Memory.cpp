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

using namespace Core;
using namespace Debug;

Void* operator new(Uint32 size)
{
	Void* pointer = std::malloc(size);

	if(pointer == nullptr)
	{
		defaultLog << LogLevel::Error << "[Core::new] Failed to allocate memory." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}

	return pointer;
}

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	Void* operator new(Uint32 size, const Char8* file, const Uint32 line, const Char8* function)
	{
		Void* pointer = ::operator new(size);

		if(AllocationTracker::hasInstance())
			AllocationTracker::instance().registerAllocation(pointer, file, line, function);

		return pointer;
	}
#endif

Void* operator new[](Uint32 size)
{
	return ::operator new(size);
}

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	Void* operator new[](Uint32 size, const Char8* file, const Uint32 line, const Char8* function)
	{
		return ::operator new(size, file, line, function);
	}
#endif

void operator delete(Void* pointer)
{
#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	if(AllocationTracker::hasInstance())
		AllocationTracker::instance().deregisterAllocation(pointer);
#endif

	std::free(pointer);
}

void operator delete[](Void* pointer)
{
	::operator delete(pointer);
}
