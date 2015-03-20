/**
 * @file core/Memory.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Memory.h>
#include <core/debug/AllocationTrace.h>
#include <core/debug/Assert.h>

using namespace Debug;

void* operator new(Uint32 size)
{
	void* pointer = std::malloc(size);
	DE_ASSERT(pointer != nullptr);

	return pointer;
}

void* operator new[](Uint32 size)
{
	return ::operator new(size);
}

void* operator new(Uint32 size, const Char8* file, const Char8* function, const Uint32 line)
{
	void* pointer = ::operator new(size);

	if(AllocationTrace::hasInstance()) // TODO: what if there is no instance?
		AllocationTrace::instance().addAllocation(pointer, file, function, line);

	return pointer;
}

void operator delete(void* pointer)
{
#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	if(pointer != nullptr && AllocationTrace::hasInstance()) // TODO: what if there is no instance?
		AllocationTrace::instance().removeAllocation(pointer);
#endif

	std::free(pointer);
}

void operator delete[](void* pointer)
{
	::operator delete(pointer);
}
