/**
 * @file core/debug/AllocationTracker.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Map.h>
#include <core/Singleton.h>
#include <core/Types.h>

namespace Debug
{
	class AllocationTracker final : public Core::Singleton<AllocationTracker>
	{
	public:
		
		AllocationTracker();

		AllocationTracker(const AllocationTracker& allocationTracker) = delete;
		AllocationTracker(AllocationTracker&& allocationTracker) = delete;

		~AllocationTracker() = default;

		void deinitialise();

		void deregisterAllocation(Void* pointer);

		void initialise();

		void registerAllocation(Void* pointer, const Char8* file, const Uint32 line, const Char8* function);

		AllocationTracker& operator =(const AllocationTracker& allocationTracker) = delete;
		AllocationTracker& operator =(AllocationTracker&& allocationTracker) = delete;

	private:

		struct AllocationRecord final
		{
			const Char8* file;
			const Char8* function;

			Uint32 line;

			AllocationRecord(const Char8* file, const Uint32 line, const Char8* function)
				: file(file),
				  function(function),
				  line(line) { }
		};

		using AllocationRecordMap = Core::Map<Void*, AllocationRecord>;

		AllocationRecordMap _allocationRecords;
		Bool _isInitialised;

		void checkForMemoryLeaks() const;
	};
}
