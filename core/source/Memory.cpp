/**
 * @file core/Memory.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Memory.h>
#include <core/Types.h>
#include <core/debug/AllocationTrace.h>

using namespace Debug;

void* operator new(Uint32 size)
{
	return std::malloc(size); // TODO: error checking
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
	if(AllocationTrace::hasInstance()) // TODO: what if there is no instance?
		AllocationTrace::instance().removeAllocation(pointer);

	std::free(pointer);
}
