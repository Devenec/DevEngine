/**
 * @file platform/posix/POSIXThread.h
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

#include <pthread.h>
#include <core/Thread.h>

namespace Core
{
	class Thread::Implementation final
	{
	public:

		Implementation();

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation() = default;

		void detach();

		inline Uint32 id() const;

		inline Bool isJoinable() const;

		Int32 join() const;

		void run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable);

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

		static Uint32 currentID();

	private:

		struct ThreadParameter
		{
			ThreadEntryFunction entryFunction;
			Void* userParameter;
			Implementation* thread;
		};

		pthread_t _threadHandle;
		Uint32 _id;
		Bool _isJoinable;

		static Void* entryFunction(Void* parameter);
	};

#include "inline/POSIXThread.inl"
}
