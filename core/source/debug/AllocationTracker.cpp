/**
 * @file core/debug/AllocationTracker.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/debug/AllocationTracker.h>

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)

#include <utility>
#include <core/Log.h>
#include <core/debug/Assert.h>

using namespace Core;
using namespace Debug;

// External

static const Char8* COMPONENT_TAG = "[Debug::AllocationTracker] ";


// Public

AllocationTracker::AllocationTracker()
	: _isInitialised(false) { }

void AllocationTracker::deinitialise()
{
	_isInitialised = false;
	checkForMemoryLeaks();
	defaultLog << LogLevel::Debug << "AllocationTracker deinitialised." << Log::Flush();
}

void AllocationTracker::deregisterAllocation(Void* pointer, const Uint size)
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

void AllocationTracker::initialise()
{
	_isInitialised = true;
	defaultLog << LogLevel::Debug << "AllocationTracker initialised." << Log::Flush();
}

void AllocationTracker::registerAllocation(Void* pointer, const Uint size, const Char8* file,
	const Uint32 line, const Char8* function)
{
	if(_isInitialised)
	{
		DE_ASSERT(pointer != nullptr);

		const std::pair<AllocationRecordMap::const_iterator, Bool> result =
			_allocationRecords.emplace(pointer, AllocationRecord(size, file, line, function));

		DE_ASSERT(result.second);
	}
}

// Private

void AllocationTracker::checkForMemoryLeaks() const
{
	if(_allocationRecords.size() > 0u)
	{
		defaultLog << LogLevel::Warning << ::COMPONENT_TAG << static_cast<Uint>(_allocationRecords.size()) <<
			" memory leak(s) detected:\n\n";

		for(AllocationRecordMap::const_iterator i = _allocationRecords.begin(),
			end = _allocationRecords.end(); i != end; ++i)
		{
			logAllocationRecord(i->first, i->second);
		}

		defaultLog << Log::Flush();
	}

	DE_ASSERT(_allocationRecords.size() == 0u);
}

// Static

void AllocationTracker::logAllocationRecord(const Void* address, const AllocationRecord& allocationRecord)
{
	defaultLog << StreamFormat::Hexadecimal << address << StreamFormat::Decimal << " (" <<
		allocationRecord.size << " bytes) at ";

	if(allocationRecord.file == nullptr)
		defaultLog << "unknown file";
	else
		defaultLog << allocationRecord.file;

	defaultLog << ", on line " << allocationRecord.line;

	if(allocationRecord.function == nullptr)
		defaultLog << ", in unknown function";
	else
		defaultLog << ", in function " << allocationRecord.function;

	defaultLog << ".\n";
}

#endif
