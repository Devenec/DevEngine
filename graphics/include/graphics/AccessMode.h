/**
 * @file graphics/AccessMode.h
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

namespace Graphics
{
	enum class AccessMode
	{
		Read  = 1,
		Write = 2
	};

	inline AccessMode operator &(AccessMode accessModeA, const AccessMode& accessModeB);

	inline AccessMode& operator &=(AccessMode& accessModeA, const AccessMode& accessModeB);

	inline AccessMode operator |(AccessMode accessModeA, const AccessMode& accessModeB);

	inline AccessMode& operator |=(AccessMode& accessModeA, const AccessMode& accessModeB);

#include "inline/AccessMode.inl"
}
