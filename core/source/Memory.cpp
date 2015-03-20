/**
 * @file core/Memory.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <cstdlib>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <core/debug/AllocationTrace.h>

using namespace Core;
using namespace Debug;

void* operator new(Uint32 size)
{
	void* pointer = std::malloc(size);
	DE_ASSERT(pointer != nullptr);

	return pointer;
}

void* operator new(Uint32 size, const Char8* file, const Char8* function, const Uint32 line)
{
	void* pointer = ::operator new(size);

	if(AllocationTrace::hasInstance())
		AllocationTrace::instance().addAllocation(pointer, file, function, line);

	return pointer;
}

void* operator new[](Uint32 size)
{
	return ::operator new(size);
}

void* operator new[](Uint32 size, const Char8* file, const Char8* function, const Uint32 line)
{
	return ::operator new(size, file, function, line);
}

void operator delete(void* pointer)
{
	if(AllocationTrace::hasInstance())
		AllocationTrace::instance().removeAllocation(pointer);

	std::free(pointer);
}

void operator delete[](void* pointer)
{
	::operator delete(pointer);
}
