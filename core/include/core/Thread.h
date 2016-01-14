/**
 * @file core/Thread.h
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

namespace Core
{
	class Thread final
	{
	public:

		using ThreadEntryFunction = Int32 (*)(Void* parameter);

		Thread();

		Thread(const Thread& thread) = delete;
		Thread(Thread&& thread) = delete;

		~Thread();

		void detach() const;

		// TODO: change to Uint for Linux x64 compatibility?
		Uint32 id() const;

		Bool isJoinable() const;

		Int32 join() const;

		void run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable = true) const;

		Thread& operator =(const Thread& thread) = delete;
		Thread& operator =(Thread&& thread) = delete;

		// TODO: change to Uint for Linux x64 compatibility?
		static Uint32 currentID();

	private:

		class Implementation;

		Implementation* _implementation;
	};
}
