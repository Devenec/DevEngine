/**
 * @file core/debug/AllocationTrace.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <utility>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/debug/Assert.h>
#include <core/debug/AllocationTrace.h>

using namespace Core;
using namespace Debug;

// Public

AllocationTrace::AllocationTrace()
	: _isInitialised(false) { }

void AllocationTrace::addAllocation(void* pointer, const String8& file, const String8& function, const Uint32 line)
{
	if(_isInitialised)
	{
		std::pair<Allocations::const_iterator, Bool> result = _allocations.emplace(
			std::make_pair(pointer, Allocation(file, function, line)));

		DE_ASSERT(result.second);
	}
}

void AllocationTrace::deinitialise()
{
	_isInitialised = false;
	checkForMemoryLeaks();
}

void AllocationTrace::initialise()
{
	_isInitialised = true;
}

void AllocationTrace::removeAllocation(void* pointer)
{
	if(_isInitialised)
	{
		Allocations::const_iterator iterator = _allocations.find(pointer);

		if(iterator != _allocations.end())
			_allocations.erase(iterator);
	}
}

// Private

void AllocationTrace::checkForMemoryLeaks() const
{
	if(_allocations.size() > 0u)
	{
		DE_ASSERT(LogManager::hasInstance());
		Log& log = LogManager::instance().log();

		log << LogLevel::Warning << "[Debug::AllocationTrace] " << _allocations.size() <<
			" memory leak(s) detected:" << Log::flush;

		for(Allocations::const_iterator i = _allocations.begin(), end = _allocations.end(); i != end; ++i)
		{
			log << "0x" << std::hex << std::uppercase << i->first << std::nouppercase << std::dec << " @ " <<
				i->second.file << " in function " << i->second.function << " on line " << i->second.line << Log::flush;
		}
	}

	DE_ASSERT(_allocations.size() == 0u);
}
