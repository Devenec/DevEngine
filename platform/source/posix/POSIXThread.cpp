/**
 * @file platform/posix/POSIXThread.cpp
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
#include <platform/posix/POSIX.h>
#include <platform/posix/POSIXThread.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Core::Thread - POSIX] ";

static pthread_attr_t createThreadAttributes(const Bool isJoinable);
static void destroyThreadAttributes(pthread_attr_t& attributes);


// Implementation

// Public

Thread::Implementation::Implementation()
	: _id(0u),
	  _isJoinable(false) { }

void Thread::Implementation::detach()
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

Int32 Thread::Implementation::join() const
{
	Void* exitValue;
	const Int32 result = pthread_join(_threadHandle, &exitValue);

	if(result != POSIX_RESULT_OK)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to join the thread." << Log::Flush();
		DE_ERROR_POSIX_CODE(0x0, result);
	}

	return reinterpret_cast<Int32>(exitValue);
}

void Thread::Implementation::run(ThreadEntryFunction entryFunction, Void* parameter, const Bool isJoinable)
{
	pthread_attr_t attributes = ::createThreadAttributes(isJoinable);
	ThreadParameter* entryParameter = DE_NEW(ThreadParameter);
	entryParameter->entryFunction = entryFunction;
	entryParameter->userParameter = parameter;
	entryParameter->thread = this;

	const Int32 result = pthread_create(&_threadHandle, &attributes, Implementation::entryFunction,
		entryParameter);

	if(result != POSIX_RESULT_OK)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the thread." <<
			Log::Flush();

		DE_ERROR_POSIX_CODE(0x0, result);
	}

	_isJoinable = isJoinable;
	::destroyThreadAttributes(attributes);
}

// Static

// Thread::Implementation::currentID() is implemented in platform/source/linux/LinuxThread.cpp

// Private

// Static

Void* Thread::Implementation::entryFunction(Void* parameter)
{
	ThreadParameter* entryParameterPointer = static_cast<ThreadParameter*>(parameter);
	ThreadParameter entryParameter = *entryParameterPointer;
	DE_DELETE(entryParameterPointer, ThreadParameter);
	entryParameter.thread->_id = currentID();
	const Int32 exitValue = entryParameter.entryFunction(entryParameter.userParameter);

	return reinterpret_cast<Void*>(exitValue);
}


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
