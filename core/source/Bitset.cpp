/**
 * @file core/Bitset.cpp
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

#include <core/Bitset.h>

using namespace Core;

// External

static const Uint32 BIT_COUNT = BITS_IN_BYTE * sizeof(Uint32);


// Public

Bitset::Bitset()
	: _value(0u) { }

Bitset::Bitset(const Uint32 value)
	: _value(value) { }

Bool Bitset::isSet(const Uint32 index) const
{
	DE_ASSERT(index < BIT_COUNT);
	return (_value & (1u << index)) == 1u;
}

void Bitset::set(const Uint32 index, const Bool value)
{
	DE_ASSERT(index < BIT_COUNT);
	const Uint32 mask = 1u << index;

	if(value)
		_value |= mask;
	else
		_value &= ~mask;
}
