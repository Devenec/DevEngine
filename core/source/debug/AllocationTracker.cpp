/**
 * @file core/debug/AllocationTracker.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/debug/AllocationTracker.h>

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)

//#include <utility>
#include <core/Log.h>
#include <core/debug/Assert.h>

using namespace Core;
using namespace Debug;

// Public

AllocationTracker::AllocationTracker()
	: _isInitialised(false) { }

void AllocationTracker::deregisterAllocation(Void* pointer, const Uint32 size)
{
	if(_isInitialised)
	{
		AllocationRecordMap::const_iterator iterator = _allocationRecords.find(pointer);
		DE_ASSERT(iterator != _allocationRecords.end());

		if(iterator != _allocationRecords.end())
		{
			DE_ASSERT(size == 0u || size == iterator->second.size);
			_allocationRecords.erase(iterator);
		}
	}
}

void AllocationTracker::registerAllocation(Void* pointer, const Uint32 size, const Char8* file, const Uint32 line,
	const Char8* function)
{
	if(_isInitialised)
	{
		DE_ASSERT(pointer != nullptr);

		const std::pair<AllocationRecordMap::const_iterator, Bool> result = _allocationRecords.emplace(pointer,
			AllocationRecord(size, file, line, function));

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
			defaultLog << StreamFormat::Hexadecimal << i->first << StreamFormat::Decimal << " (" << i->second.size <<
				" bytes) at ";
			
			if(i->second.file == nullptr)
				defaultLog << "unknown file";
			else
				defaultLog << i->second.file;

			defaultLog << " on line " << i->second.line;
			
			if(i->second.function == nullptr)
				defaultLog << " in unknown function ";
			else
				defaultLog << " in function " << i->second.function;

			defaultLog << Log::Flush();
		}
	}

	DE_ASSERT(_allocationRecords.size() == 0u);
}

#endif
