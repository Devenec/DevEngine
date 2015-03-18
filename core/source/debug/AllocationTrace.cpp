/**
 * @file AllocationTrace.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <utility>
#include <core/debug/AllocationTrace.h>

using namespace Core;
using namespace Debug;

// Public

AllocationTrace::AllocationTrace() { }

AllocationTrace::~AllocationTrace() { }

void AllocationTrace::addAllocation(void* pointer, const String8& file, const String8& function, const Uint32 line)
{
	Allocation allocation;
	allocation.file = file;
	allocation.function = function;
	allocation.line = line;
	_allocations.insert(std::make_pair(pointer, allocation));

	// TODO: issue error if the pointer existed in _allocations
}

void AllocationTrace::removeAllocation(void* pointer)
{
	Allocations::const_iterator iterator = _allocations.find(pointer);

	if(iterator != _allocations.end())
		_allocations.erase(iterator);

	// TODO: issue error if the pointer was not found in _allocations
}
