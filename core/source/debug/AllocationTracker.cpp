/**
 * @file core/debug/AllocationTracker.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <utility>
#include <core/Log.h>
#include <core/debug/AllocationTracker.h>
#include <core/debug/Assert.h>

using namespace Core;
using namespace Debug;

// Public

AllocationTracker::AllocationTracker()
	: _isInitialised(false) { }

void AllocationTracker::deinitialise()
{
	_isInitialised = false;
	checkForMemoryLeaks();
}

void AllocationTracker::deregisterAllocation(Void* pointer)
{
	if(_isInitialised)
	{
		AllocationRecordMap::const_iterator iterator = _allocationRecords.find(pointer);

		if(iterator != _allocationRecords.end())
			_allocationRecords.erase(iterator);
	}
}

void AllocationTracker::initialise()
{
	_isInitialised = true;
}

void AllocationTracker::registerAllocation(Void* pointer, const Char8* file, const Uint32 line, const Char8* function)
{
	if(_isInitialised)
	{
		std::pair<AllocationRecordMap::const_iterator, Bool> result = _allocationRecords.emplace(
			std::make_pair(pointer, AllocationRecord(file, line, function)));

		DE_ASSERT(result.second);
	}
}

// Private

void AllocationTracker::checkForMemoryLeaks() const
{
	if(_allocationRecords.size() > 0u)
	{
		defaultLog << LogLevel::Warning << "[Debug::AllocationTracker] " << _allocationRecords.size() <<
			" memory leak(s) detected:" << Log::Flush();

		for(AllocationRecordMap::const_iterator i = _allocationRecords.begin(), end = _allocationRecords.end();
			i != end; ++i)
		{
			defaultLog << "0x" << std::hex << std::uppercase << i->first << std::nouppercase << std::dec << " at " <<
				i->second.file << " on line " << i->second.line << " in function " << i->second.function <<
				Log::Flush();
		}
	}

	DE_ASSERT(_allocationRecords.size() == 0u);
}
