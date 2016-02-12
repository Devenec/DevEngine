/**
 * @file core/Bitset.h
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

#include <core/Types.h>
#include <core/debug/Assert.h>

namespace Core
{
	class Bitset final
	{
	public:

		Bitset();

		explicit Bitset(const Uint32 value);

		Bitset(const Bitset& bitset) = default;
		Bitset(Bitset&& bitset) = default;

		~Bitset() = default;

		Bool isSet(const Uint32 index) const;

		inline void reset();

		void set(const Uint32 index, const Bool value);

		Bitset& operator =(const Bitset& bitset) = default;
		Bitset& operator =(Bitset&& bitset) = default;

	private:

		Uint32 _value;
	};

#include "inline/Bitset.inl"
}
