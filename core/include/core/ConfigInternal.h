/**
 * @file core/ConfigInternal.h
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

#include <core/Platform.h>
#include <core/Config.h>

#if DE_BUILD != DE_BUILD_PRODUCTION
	#define DE_INTERNAL_BUILD_DEVELOPMENT
#endif

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT) && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS
#endif
