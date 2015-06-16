/**
 * @file core/debug/AllocationTracker.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Log.h>
#include <core/debug/AllocationTracker.h>
#include <core/debug/Assert.h>

using namespace Core;
using namespace Debug;

// Public

void AllocationTracker::deregisterAllocation(Void* pointer, const Uint32 byteCount)
{
	DE_ASSERT(_isInitialised);
	AllocationRecordMap::const_iterator iterator = _allocationRecords.find(pointer);
	DE_ASSERT(iterator != _allocationRecords.end());

	if(iterator != _allocationRecords.end())
	{
		DE_ASSERT(byteCount == 0u || byteCount == iterator->second.byteCount);
		_allocationRecords.erase(iterator);
	}
}

void AllocationTracker::registerAllocation(Void* pointer, const Uint32 byteCount, const Char8* file, const Uint32 line,
	const Char8* function)
{
	DE_ASSERT(_isInitialised);

	std::pair<AllocationRecordMap::const_iterator, Bool> result = _allocationRecords.emplace(pointer,
		AllocationRecord(byteCount, file, line, function));

	DE_ASSERT(result.second);
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
			defaultLog << "0x" << std::hex << std::uppercase << i->first << std::nouppercase << std::dec << " (" <<
				i->second.byteCount << " bytes) at " << i->second.file << " on line " << i->second.line <<
				" in function " << i->second.function << Log::Flush();
		}
	}

	DE_ASSERT(_allocationRecords.size() == 0u);
}
