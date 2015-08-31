/**
 * @file core/Application.h
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

#include <core/ConfigInternal.h>
#include <core/LogManager.h>
#include <core/Singleton.h>

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)
	#include <core/debug/AllocationTracker.h>
#endif

namespace Core
{
	class Application final
	{
	public:

		Application() = default;

		Application(const Application& application) = delete;
		Application(Application&& application) = delete;

		~Application() = default;

		void deinitialise();

		void initialise();

		Application& operator =(const Application& application) = delete;
		Application& operator =(Application&& application) = delete;

	private:

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)
		Debug::AllocationTracker _allocationTracker;
#endif

		LogManager _logManager;
	};
}
