/**
 * @file platform/x/X.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::X]";

static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo);
static Int32 handleIOError(Display* xConnection);


// Public

X::X()
{
	_connection = XOpenDisplay(nullptr);

	if(_connection == nullptr)
	{
		// TODO: handle error?
	}

	// TODO: enable synchronisation on debug builds?
	XSetErrorHandler(::handleError);
	XSetIOErrorHandler(::handleIOError);
}

X::~X()
{
	XCloseDisplay(_connection);
	// TODO: handle error?
}


// External

// TODO: add more info to the error message
static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo)
{
	Char8 errorText[512];
	XGetErrorText(xConnection, errorInfo->error_code, errorText, sizeof(errorText));

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << " X error occurred, " << errorText << " (" <<
		StreamFormat::Hexadecimal << static_cast<Uint32>(errorInfo->error_code) << StreamFormat::Decimal << ")." <<
		Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();

	return 0;
}

// TODO: add more info to the error message?
static Int32 handleIOError(Display* xConnection)
{
	static_cast<Void>(xConnection);

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << " X error occurred, the connection was terminated." <<
		Log::Flush();

	DE_DEBUGGER_BREAK();
	std::abort();

	return 0;
}
