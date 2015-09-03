/**
 * @file core/memory/AllocationPolicy.h
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

#include <core/Types.h>
#include <core/memory/AllocationPolicyBase.h>

namespace Memory
{
	class AllocationPolicy final : public AllocationPolicyBase
	{
	public:

		AllocationPolicy() = delete;

		AllocationPolicy(const AllocationPolicy& allocationPolicy) = delete;
		AllocationPolicy(AllocationPolicy&& allocationPolicy) = delete;

		~AllocationPolicy() = delete;

		AllocationPolicy& operator =(const AllocationPolicy& allocationPolicy) = delete;
		AllocationPolicy& operator =(AllocationPolicy&& allocationPolicy) = delete;

		static Void* allocate(const Uint32 size, const Char8* file = nullptr, const Uint32 line = 0u,
			const Char8* function = nullptr);

		static void deallocate(Void* pointer, const Uint32 size = 0u);

	private:

		using Base = AllocationPolicyBase;
	};
}
