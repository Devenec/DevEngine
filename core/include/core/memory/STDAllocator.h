/**
 * @file core/memory/STDAllocator.h
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

		T* allocate(const Uint32 objectCount);

		template<typename U, typename... Parameters>
		void construct(U* pointer, Parameters&&... parameters);

		void deallocate(T* pointer, const Uint32 objectCount);

		template<typename U>
		void destroy(U* pointer);

		STDAllocator& operator =(const STDAllocator& stdAllocator) = default;
		STDAllocator& operator =(STDAllocator&& stdAllocator) = default;

		template<typename U>
		Bool operator ==(const STDAllocator<U, AllocationPolicy>& stdAllocator) const;

		template<typename U, typename OtherAllocator>
		Bool operator ==(const OtherAllocator& allocator) const;

		template<typename U>
		Bool operator !=(const STDAllocator<U, AllocationPolicy>& stdAllocator) const;

		template<typename U, typename OtherAllocator>
		Bool operator !=(const OtherAllocator& allocator) const;
	};

#include "inline/STDAllocator.inl"
}
