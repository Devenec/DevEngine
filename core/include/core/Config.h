/**
 * @file core/Config.h
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

/**
 * If defined, a custom application entry point is used.
 *
 * For more information, see core/Application.h in which the entry point is
 * declared.
 */
#define DE_CONFIG_DEVENGINE_MAIN

/**
 * If defined, Debug::AllocationTracker (see core/debug/AllocationTracker.h) is
 * used to track memory leaks in debug and release builds.
 */
#define DE_CONFIG_TRACK_ALLOCATIONS


namespace Config
{
	const Uint32 LOG_BUFFER_SIZE = 1024u;

	const Uint32 LOG_LINE_MAX_WIDTH = 120u;
}
