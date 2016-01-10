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

#include <pthread.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Thread.h>
#include <platform/posix/POSIX.h>

using namespace Core;
using namespace Platform;

// External

struct ThreadParameter
{
	Thread::ThreadEntryFunction entryFunction;
	Void* userParameter;
};

static const Char8* COMPONENT_TAG = "[Core::Thread - POSIX] ";

static pthread_attr_t createThreadAttributes(const Bool isJoinable);
static void destroyThreadAttributes(pthread_attr_t& attributes);
static Void* threadEntryFunction(Void* parameter);


// Implementation

class Thread::Implementation final
{
public:

	Implementation()
		: _isJoinable(false) { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	void detach()
	{
		const Int32 result = pthread_detach(_threadHandle);

		if(result != POSIX_RESULT_OK)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to detach the thread." <<
				Log::Flush();

			DE_ERROR_POSIX_CODE(0x0, result);
		}

		_isJoinable = false;
	}

	ThreadID id() const
	{
		return reinterpret_cast<ThreadID>(_threadHandle);
	}

	Bool isJoinable() const
	{
		return _isJoinable;
	}

	Int32 join() const
	{
		Void* returnValue;
		const Int32 result = pthread_join(_threadHandle, &returnValue);

		if(result != POSIX_RESULT_OK)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to join the thread." << Log::Flush();
			DE_ERROR_POSIX_CODE(0x0, result);
		}

		return reinterpret_cast<Int32>(returnValue);
	}

	void run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable)
	{
		pthread_attr_t attributes = ::createThreadAttributes(isJoinable);
		ThreadParameter* threadParameter = DE_NEW(ThreadParameter);
		threadParameter->entryFunction = entryFunction;
		threadParameter->userParameter = parameter;

		const Int32 result = pthread_create(&_threadHandle, &attributes, threadEntryFunction,
			threadParameter);

		if(result != POSIX_RESULT_OK)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the thread." <<
				Log::Flush();

			DE_ERROR_POSIX_CODE(0x0, result);
		}

		_isJoinable = isJoinable;
		::destroyThreadAttributes(attributes);
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

	static ThreadID currentID()
	{
		return reinterpret_cast<ThreadID>(pthread_self());
	}

private:

	pthread_t _threadHandle;
	Bool _isJoinable;
};


// Core::Thread

// Public

Thread::Thread()
	: _implementation(DE_NEW(Implementation)()) { }

Thread::~Thread()
{
	DE_DELETE(_implementation, Implementation);
}

void Thread::detach() const
{
	_implementation->detach();
}

ThreadID Thread::id() const
{
	return _implementation->id();
}

Bool Thread::isJoinable() const
{
	return _implementation->isJoinable();
}

Int32 Thread::join() const
{
	return _implementation->join();
}

void Thread::run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable) const
{
	_implementation->run(entryFunction, parameter, isJoinable);
}

// Static

ThreadID Thread::currentID()
{
	return Implementation::currentID();
}


// External

static pthread_attr_t createThreadAttributes(const Bool isJoinable)
{
	pthread_attr_t attributes;
	Int32 result = pthread_attr_init(&attributes);

	if(result != POSIX_RESULT_OK)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to initialise the thread attributes." <<
			Log::Flush();

		DE_ERROR_POSIX_CODE(0x0, result);
	}

	const Int32 joinableState = isJoinable ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED;
	result = pthread_attr_setdetachstate(&attributes, joinableState);

	if(result != POSIX_RESULT_OK)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the thread joinable state." <<
			Log::Flush();

		DE_ERROR_POSIX_CODE(0x0, result);
	}

	return attributes;
}

static void destroyThreadAttributes(pthread_attr_t& attributes)
{
	const Int32 result = pthread_attr_destroy(&attributes);

	if(result != POSIX_RESULT_OK)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to destroy the thread attributes." <<
			Log::Flush();

		DE_ERROR_POSIX_CODE(0x0, result);
	}
}

static Void* threadEntryFunction(Void* parameter)
{
	ThreadParameter* threadParameter = static_cast<ThreadParameter*>(parameter);
	ThreadParameter threadParameterCopy = *threadParameter;
	DE_DELETE(threadParameter, ThreadParameter);
	const Int32 returnValue = threadParameterCopy.entryFunction(threadParameterCopy.userParameter);

	return reinterpret_cast<Void*>(returnValue);
}
