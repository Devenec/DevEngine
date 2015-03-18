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
	class AllocationTrace final : public Core::Singleton<AllocationTrace>
	{
	public:

		AllocationTrace();

		~AllocationTrace();

		void addAllocation(void* pointer, const Core::String8& file, const Core::String8& function, const Uint32 line);

		void removeAllocation(void* pointer);

	private:

		struct Allocation
		{
			Core::String8 file;
			Core::String8 function;
			Uint32 line;
		};

		using Allocations = Core::Map<void*, Allocation>;

		Allocations _allocations;

		AllocationTrace(const AllocationTrace& allocationTrace) = delete;
		AllocationTrace(AllocationTrace&& allocationTrace) = delete;

		AllocationTrace& operator =(const AllocationTrace& allocationTrace) = delete;
	};
}
