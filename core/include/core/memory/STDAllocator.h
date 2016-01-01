/**
 * @file core/memory/STDAllocator.h
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

#pragma once

#include <utility>
#include <core/Types.h>
#include <core/memory/AllocationPolicy.h>

namespace Memory
{
	template<typename T, typename AllocationPolicy = AllocationPolicy>
	class STDAllocator
	{
	public:

		template<typename U>
		struct rebind
		{
			using other = STDAllocator<U, AllocationPolicy>;
		};

		using value_type = T;

		STDAllocator() = default;

		STDAllocator(const STDAllocator& stdAllocator) = default;
		STDAllocator(STDAllocator&& stdAllocator) = default;

		template<typename U>
		STDAllocator(const STDAllocator<U, AllocationPolicy>& stdAllocator);

		template<typename U, typename OtherAllocationPolicy>
		STDAllocator(const STDAllocator<U, OtherAllocationPolicy>& stdAllocator);

		~STDAllocator() = default;

		inline T* allocate(const Uint32 objectCount);

		template<typename U, typename... Parameters>
		inline void construct(U* pointer, Parameters&&... parameters);

		inline void deallocate(T* pointer, const Uint32 objectCount);

		template<typename U>
		inline void destroy(U* pointer);

		STDAllocator& operator =(const STDAllocator& stdAllocator) = default;
		STDAllocator& operator =(STDAllocator&& stdAllocator) = default;
	};

	template<typename T, typename U, typename AllocationPolicy>
	inline Bool operator ==(const STDAllocator<T, AllocationPolicy>& stdAllocatorA,
		const STDAllocator<U, AllocationPolicy>& stdAllocatorB);

	template<typename T, typename U, typename AllocationPolicy, typename OtherAllocator>
	inline Bool operator ==(const STDAllocator<T, AllocationPolicy>& stdAllocator, const OtherAllocator& allocator);

	template<typename T, typename U, typename AllocationPolicy>
	inline Bool operator !=(const STDAllocator<T, AllocationPolicy>& stdAllocatorA,
		const STDAllocator<U, AllocationPolicy>& stdAllocatorB);

	template<typename T, typename U, typename AllocationPolicy, typename OtherAllocator>
	inline Bool operator !=(const STDAllocator<T, AllocationPolicy>& stdAllocator, const OtherAllocator& allocator);

#include "inline/STDAllocator.inl"
}
