/**
 * @file platform/windows/WindowsThread.cpp
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

#include <core/Log.h>
#include <core/Memory.h>
#include <core/Platform.h>
#include <core/Thread.h>
#include <platform/windows/Windows.h>

using namespace Core;

// External

struct ThreadParameter
{
	Thread::ThreadEntryFunction entryFunction;
	Void* userParameter;
};

static const Char8* COMPONENT_TAG = "[Core::Thread - Windows] ";

static unsigned long DE_INTERNAL_CALL_STDCALL threadEntryFunction(Void* parameter);


// Implementation

class Thread::Implementation final
{
public:

	Implementation()
		: _threadHandle(nullptr) { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	void detach()
	{
		closeThreadHandle();
	}

	Uint32 id() const
	{
		const Uint32 id = GetThreadId(_threadHandle);

		if(id == 0u)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the thread ID." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		return id;
	}

	Bool isJoinable() const
	{
		return _isJoinable;
	}

	Int32 join()
	{
		waitForExit();
		const Int32 exitValue = getExitValue();
		closeThreadHandle();

		return exitValue;
	}

	void run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable)
	{
		ThreadParameter* threadParameter = DE_NEW(ThreadParameter);
		threadParameter->entryFunction = entryFunction;
		threadParameter->userParameter = parameter;
		_threadHandle = CreateThread(nullptr, 0u, threadEntryFunction, threadParameter, 0u, nullptr);

		if(_threadHandle == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the thread." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		if(!isJoinable)
			closeThreadHandle();

		_isJoinable = isJoinable;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

	static Uint32 currentID()
	{
		return GetCurrentThreadId();
	}

private:

	HANDLE _threadHandle;
	Bool _isJoinable;

	void closeThreadHandle()
	{
		const Int32 result = CloseHandle(_threadHandle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to close the thread handle." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}
	}

	void waitForExit() const
	{
		const Uint32 result = WaitForSingleObject(_threadHandle, INFINITE);

		if(result == WAIT_FAILED)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to join the thread." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}
	}

	Int32 getExitValue() const
	{
		unsigned long exitValue;
		const Int32 result = GetExitCodeThread(_threadHandle, &exitValue);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the exit value." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		return exitValue;
	}
};


// Core::Thread

// Public

Thread::Thread()
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)();
}

Thread::~Thread()
{
	DE_DELETE(_implementation, Implementation);
}

void Thread::detach() const
{
	_implementation->detach();
}

Uint32 Thread::id() const
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

Uint32 Thread::currentID()
{
	return Implementation::currentID();
}


// External

static unsigned long DE_INTERNAL_CALL_STDCALL threadEntryFunction(Void* parameter)
{
	ThreadParameter* threadParameter = static_cast<ThreadParameter*>(parameter);
	ThreadParameter threadParameterCopy = *threadParameter;
	DE_DELETE(threadParameter, ThreadParameter);

	return threadParameterCopy.entryFunction(threadParameterCopy.userParameter);
}
