/**
 * @file core/memory/AllocationPolicyBase.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <core/Types.h>

namespace Memory
{
	class AllocationPolicyBase
	{
	public:

		AllocationPolicyBase() = delete;

		AllocationPolicyBase(const AllocationPolicyBase& allocationPolicy) = delete;
		AllocationPolicyBase(AllocationPolicyBase&& allocationPolicy) = delete;

		~AllocationPolicyBase() = delete;

		AllocationPolicyBase& operator =(const AllocationPolicyBase& allocationPolicy) = delete;
		AllocationPolicyBase& operator =(AllocationPolicyBase&& allocationPolicy) = delete;

	protected:

		static void deregisterAllocation(Void* pointer, const Uint32 size = 0u);

		static void registerAllocation(Void* pointer, const Uint32 size, const Char8* file = nullptr,
			const Uint32 line = 0u, const Char8* function = nullptr);
	};
}
