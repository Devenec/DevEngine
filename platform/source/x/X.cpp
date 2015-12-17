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
#include <platform/Utility.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG 					  = "[Platform::X]";
static const Int32 MIN_SUPPORTED_XRANDR_VERSION_MAJOR = 1;
static const Int32 MIN_SUPPORTED_XRANDR_VERSION_MINOR = 1;

static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo);
static Int32 handleIOError(Display* xConnection);
static void setErrorHandlers();


// Public

X::X()
	: _connection(XOpenDisplay(nullptr))
{
	checkConnection();
	::setErrorHandlers();
	checkXRandRSupport();
}

X::~X()
{
	XCloseDisplay(_connection);
}

void X::invokeError(const Uint32 errorCode) const
{
	defaultLog << LogLevel::Error << "Error occurred with code " << StreamFormat::Hexadecimal << errorCode <<
		StreamFormat::Decimal << '.' << Log::Flush();

	XSync(_connection, False);
	DE_DEBUGGER_BREAK();
	std::abort();
}

void X::invokeError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function) const
{
	defaultLog << LogLevel::Error << "Error occurred at " << file << ", on line " << line << ", in function " <<
		function << ", with error code " << StreamFormat::Hexadecimal << errorCode << StreamFormat::Decimal << '.' <<
		Log::Flush();

	XSync(_connection, False);
	DE_DEBUGGER_BREAK();
	std::abort();
}

// Private

void X::checkConnection() const
{
	if(_connection == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to initialise a connection." << Log::Flush();
		DE_ERROR(0x0);
	}
	else
	{
		defaultLog << LogLevel::Info << "Initialised a connection with X.\n\nVersion: " <<
			XProtocolVersion(_connection) << '.' << XProtocolRevision(_connection) << '\n' << Log::Flush();
	}
}

void X::checkXRandRSupport() const
{
	Int32 baseEventType;
	Int32 baseErrorCode;
	const Int32 result = XRRQueryExtension(_connection, &baseEventType, &baseErrorCode);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " XRandR is not supported." << Log::Flush();
		DE_ERROR_X(0x0);
	}
	else
	{
		Int32 versionMajor = 0;
		Int32 versionMinor = 0;
		XRRQueryVersion(_connection, &versionMajor, &versionMinor);

		if(isVersionLess(versionMajor, versionMinor, MIN_SUPPORTED_XRANDR_VERSION_MAJOR,
			MIN_SUPPORTED_XRANDR_VERSION_MINOR))
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " XRandR version " << versionMajor << '.' <<
				versionMinor << " is not supported. The minimum supported version is " <<
				MIN_SUPPORTED_XRANDR_VERSION_MAJOR << '.' << MIN_SUPPORTED_XRANDR_VERSION_MINOR << '.' << Log::Flush();

			DE_ERROR(0x0);
		}
		else
		{
			defaultLog << LogLevel::Info << "Using XRandR version " << versionMajor << '.' << versionMinor << '.' <<
				Log::Flush();
		}
	}
}


// External

static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo)
{
	Char8 errorMessage[512];
	XGetErrorText(xConnection, errorInfo->error_code, errorMessage, sizeof(errorMessage));

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << " X error occurred, " << errorMessage << " (" <<
		StreamFormat::Hexadecimal << static_cast<Uint32>(errorInfo->error_code) << StreamFormat::Decimal << ")." <<
		Log::Flush();

	std::abort();
	return 0;
}

static Int32 handleIOError(Display* xConnection)
{
	static_cast<Void>(xConnection);

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << " X error occurred, the connection was terminated." <<
		Log::Flush();

	std::abort();
	return 0;
}

static void setErrorHandlers()
{
	XSetErrorHandler(::handleError);
	XSetIOErrorHandler(::handleIOError);
}
