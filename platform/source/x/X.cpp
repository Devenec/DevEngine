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

//

#include <platform/glx/GLX.h>

GLXContext X::createGraphicsContext(GLXFBConfig configHandle, const Int32* attributes, const Bool isDirect) const
{
	// TODO: implement
	return nullptr;
}

Window X::createWindow(const Window parentWindowHandle, const Int32 x, const Int32 y, const Uint32 width,
	const Uint32 height, XVisualInfo* visualInfo, XSetWindowAttributes& attributes, const Uint32 attributeMask) const
{
	attributes.colormap = XCreateColormap(_connection, parentWindowHandle, visualInfo->visual, AllocNone);

	return XCreateWindow(_connection, parentWindowHandle, x, y, width, height, 0u, visualInfo->depth,
		InputOutput, visualInfo->visual, attributeMask, &attributes);
}

void X::destroyGraphicsContext(GLXContext contextHandle) const
{
	// TODO: implement
}

const Char8* X::getExtensionNameString() const
{
	const Int32 screen = XDefaultScreen(_connection);
	return GLX::queryExtensionsString(_connection, screen);
}

XRRScreenConfiguration* X::getGraphicsAdapterConfig(const Uint32 adapterIndex) const
{
	const Window rootWindowHandle = XRootWindow(_connection, adapterIndex);
	XRRScreenConfiguration* config = XRRGetScreenInfo(_connection, rootWindowHandle);

	if(config == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the graphics adapter configuration." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}

	return config;
}

Int32 X::getGraphicsConfigAttribute(GLXFBConfig configHandle, const Int32 attributeName) const
{
	Int32 value = 0;
	const Int32 result = GLX::getFBConfigAttrib(_connection, configHandle, attributeName, &value);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get a configuration attribute." << Log::Flush();
		DE_ERROR_X(0x0);
	}

	return value;
}

GLXFBConfig* X::getGraphicsConfigs(const Int32* attributes, Uint32& configCount) const
{
	const Int32 screen = XDefaultScreen(_connection);

	GLXFBConfig* configHandles = GLX::chooseFBConfig(_connection, screen, attributes,
		reinterpret_cast<Int32*>(&configCount));

	if(configHandles == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get matching configurations." << Log::Flush();
		DE_ERROR_X(0x0);
	}

	return configHandles;
}

XVisualInfo* X::getGraphicsConfigVisualInfo(GLXFBConfig configHandle) const
{
	XVisualInfo* visualInfo = GLX::getVisualFromFBConfig(_connection, configHandle);

	if(visualInfo == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			" Failed to get the visual info of a graphics configuration." << Log::Flush();

		DE_ERROR_X(0x0);
	}

	return visualInfo;
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

Bool X::isGLXSupported(Uint32& versionMajor, Uint32& versionMinor) const
{
	Int32 result = GLX::queryExtension(_connection, nullptr, nullptr);

	if(result == 0)
	{
		return false;
	}
	else
	{
		result = GLX::queryVersion(_connection, reinterpret_cast<Int32*>(&versionMajor),
			reinterpret_cast<Int32*>(&versionMinor));

		return result != 0;
	}
}

Bool X::isGraphicsContextDirect(GLXContext contextHandle) const
{
	// TODO: implement
	return false;
}

void X::makeGraphicsContextCurrent(GLXDrawable drawableHandle, GLXContext contextHandle) const
{
	// TODO: implement
}

XEvent X::popEvent() const
{
	XEvent event;
	XNextEvent(_connection, &event);

	return event;
}

void X::setDisplayMode(XRRScreenConfiguration* graphicsAdapterConfig, const Drawable rootWindowHandle,
	const Uint32 resolutionIndex, const Uint32 refreshRate, const Time timestamp) const
{
	const Int32 result = XRRSetScreenConfigAndRate(_connection, graphicsAdapterConfig, rootWindowHandle, resolutionIndex,
		RR_Rotate_0, static_cast<Int16>(refreshRate), timestamp);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to set the display mode." << Log::Flush();
		DE_ERROR_X(0x0);
	}
}

void X::swapBuffers(GLXDrawable drawableHandle) const
{
	// TODO: implement
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
