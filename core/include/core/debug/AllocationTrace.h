/**
 * @file core/debug/AllocationTrace.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Map.h>
#include <core/Singleton.h>
#include <core/String.h>
#include <core/Types.h>

namespace Debug
{
	struct Allocation
	{
		Core::String8 file;
		Core::String8 function;
		Uint32 line;

		Allocation(const Core::String8& file, const Core::String8& function, const Uint32 line)
			: file(file),
			  function(function),
			  line(line) { }
	};

	using Allocations = Core::Map<void*, Allocation>;
	
	class AllocationTrace final : public Core::Singleton<AllocationTrace>
	{
	public:
		
		AllocationTrace();

		~AllocationTrace();

		void addAllocation(void* pointer, const Core::String8& file, const Core::String8& function, const Uint32 line);

		void deinitialise();

		void initialise();

		void removeAllocation(void* pointer);

	private:

		Allocations _allocations;
		Bool _isInitialised;

		AllocationTrace(const AllocationTrace& allocationTrace) = delete;
		AllocationTrace(AllocationTrace&& allocationTrace) = delete;

		void checkForMemoryLeaks() const;

		AllocationTrace& operator =(const AllocationTrace& allocationTrace) = delete;
	};
}
