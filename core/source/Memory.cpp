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

Void* operator new(Uint32 size)
{
	Void* pointer = std::malloc(size);
	DE_ASSERT(pointer != nullptr);

	return pointer;
}

Void* operator new(Uint32 size, const Char8* file, const Char8* function, const Uint32 line)
{
	Void* pointer = ::operator new(size);

	if(AllocationTrace::hasInstance())
		AllocationTrace::instance().addAllocation(pointer, file, function, line);

	return pointer;
}

Void* operator new[](Uint32 size)
{
	return ::operator new(size);
}

Void* operator new[](Uint32 size, const Char8* file, const Char8* function, const Uint32 line)
{
	return ::operator new(size, file, function, line);
}

void operator delete(Void* pointer)
{
	if(AllocationTrace::hasInstance())
		AllocationTrace::instance().removeAllocation(pointer);

	std::free(pointer);
}

void operator delete[](Void* pointer)
{
	::operator delete(pointer);
}
