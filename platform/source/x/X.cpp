/**
 * @file platform/x/X.cpp
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

#include <cstdlib>
#include <core/Error.h>
#include <core/Log.h>
#include <platform/Version.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG				  = "[Platform::X] ";
static const Version MIN_SUPPORTED_XRANDR_VERSION = Version(1u, 1u);

static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo);
static Int32 handleIOError(Display* xConnection);
static void initialiseMultithreading();
static void setErrorHandlers();

// Public

X::X()
	: _connection(nullptr),
	  _windowUserDataContext(0)
{
	::initialiseMultithreading();
	_windowUserDataContext = XUniqueContext();
	initialiseConnection();
	::setErrorHandlers();
	checkXRandRSupport();
}

X::~X()
{
	XCloseDisplay(_connection);
}

Cursor X::createHiddenPointer(const ::Window windowHandle) const
{
	const Char8 data[] { 0 };
	const Pixmap pixmap = XCreateBitmapFromData(_connection, windowHandle, data, 1u, 1u);

	if(pixmap == None)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed create a pixmap." << Log::Flush();
		DE_ERROR_X(0x0);
	}

	XColor foregroundColour;
	XColor backgroundColour;

	const Cursor pointerHandle = XCreatePixmapCursor(_connection, pixmap, pixmap, &foregroundColour,
		&backgroundColour, 0u, 0u);

	XFreePixmap(_connection, pixmap);
	return pointerHandle;
}

::Window X::createWindow(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height,
	XVisualInfo* visualInfo, XSetWindowAttributes attributes, Uint32 attributeMask) const
{
	const ::Window rootWindowHandle = XRootWindow(_connection, GRAPHICS_ADAPTER_INDEX);
	attributes.colormap = XCreateColormap(_connection, rootWindowHandle, visualInfo->visual, AllocNone);
	attributeMask |= CWColormap;

	return XCreateWindow(_connection, rootWindowHandle, x, y, width, height, 0u, visualInfo->depth,
		InputOutput, visualInfo->visual, attributeMask, &attributes);
}

void X::destroyWindowProperty(const ::Window windowHandle, const Char8* propertyName) const
{
	const Atom propertyAtom = createAtom(propertyName);
	XDeleteProperty(_connection, windowHandle, propertyAtom);
}

void X::destroyWindowUserData(const ::Window windowHandle) const
{
	const Int32 result = XDeleteContext(_connection, windowHandle, _windowUserDataContext);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to destroy the user data of a window." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}
}

Version X::getGLXVersion() const
{
	Int32 result = GLX::queryExtension(_connection, nullptr, nullptr);

	if(result == 0)
		return Version(0u, 0u);

	Int32 majorVersion;
	Int32 minorVersion;
	result = GLX::queryVersion(_connection, &majorVersion &minorVersion);

	if(result == 0)
		return Version(0u, 0u);

	return Version(majorVersion, minorVersion);
}

XRRScreenConfiguration* X::getGraphicsAdapterConfig(const Uint32 adapterIndex) const
{
	const ::Window rootWindowHandle = XRootWindow(_connection, adapterIndex);
	XRRScreenConfiguration* config = XRRGetScreenInfo(_connection, rootWindowHandle);

	if(config == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			"Failed to get the graphics adapter configuration." << Log::Flush();

		DE_ERROR_X(0x0);
	}

	return config;
}

Int32 X::getGraphicsConfigAttribute(GLX::FBConfig configHandle, const Int32 attributeName) const
{
	Int32 value = 0;
	const Int32 result = GLX::getFBConfigAttrib(_connection, configHandle, attributeName, &value);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get a configuration attribute." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}

	return value;
}

GLX::FBConfig* X::getGraphicsConfigs(const Int32* attributes, Uint32& configCount) const
{
	GLX::FBConfig* configHandles =
		GLX::chooseFBConfig(_connection, GRAPHICS_ADAPTER_INDEX, attributes,
			reinterpret_cast<Int32*>(&configCount));

	if(configHandles == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get matching configurations." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}

	return configHandles;
}

XVisualInfo* X::getGraphicsConfigVisualInfo(GLX::FBConfig configHandle) const
{
	XVisualInfo* visualInfo = GLX::getVisualFromFBConfig(_connection, configHandle);

	if(visualInfo == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			"Failed to get the visual info of a graphics configuration." << Log::Flush();

		DE_ERROR_X(0x0);
	}

	return visualInfo;
}

Rectangle X::getWindowClientRectangle(const ::Window windowHandle) const
{
	const ::Window rootWindowHandle = XRootWindow(_connection, GRAPHICS_ADAPTER_INDEX);
	Int32 x = 0;
	Int32 y = 0;
	::Window childWindowHandle;
	XTranslateCoordinates(_connection, windowHandle, rootWindowHandle, 0, 0, &x, &y, &childWindowHandle);
	const XWindowAttributes windowAttributes = getWindowAttributes(windowHandle);

	return Rectangle(x, y, windowAttributes.width, windowAttributes.height);
}

Void* X::getWindowUserData(const ::Window windowHandle) const
{
	Char8* data = nullptr;
	const Int32 result = XFindContext(_connection, windowHandle, _windowUserDataContext, &data);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the user data of a window." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}

	return data;
}

void X::invokeError(const Uint32 errorCode) const
{
	defaultLog << LogLevel::Error << "X error occurred with code " << StreamFormat::Hexadecimal <<
		errorCode << StreamFormat::Decimal << '.' << Log::Flush();

	XSync(_connection, False);
	DE_DEBUGGER_BREAK();
	std::abort();
}

void X::invokeError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function) const
{
	defaultLog << LogLevel::Error << "X error occurred at " << file << ", on line " << line <<
		", in function " << function << ", with code " << StreamFormat::Hexadecimal << errorCode <<
		StreamFormat::Decimal << '.' << Log::Flush();

	XSync(_connection, False);
	DE_DEBUGGER_BREAK();
	std::abort();
}

void X::makeGraphicsContextCurrent(GLX::Drawable drawableHandle, GLX::Context contextHandle) const
{
	const Int32 result = GLX::makeContextCurrent(_connection, drawableHandle, drawableHandle, contextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to make a graphics context current." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}
}

XEvent X::popEvent() const
{
	XEvent event;
	XNextEvent(_connection, &event);

	return event;
}

void X::sendEvent(const ::Window windowHandle, XEvent& event, const Int32 eventMask) const
{
	const Int32 result = XSendEvent(_connection, windowHandle, False, eventMask, &event);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the attributes of a window." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}
}

void X::setDisplayMode(XRRScreenConfiguration* graphicsAdapterConfig, const Drawable rootWindowHandle,
	const Uint32 resolutionIndex, const Uint32 refreshRate, const Time timestamp) const
{
	const Int32 result =
		XRRSetScreenConfigAndRate(_connection, graphicsAdapterConfig, rootWindowHandle, resolutionIndex,
			RR_Rotate_0, static_cast<Int16>(refreshRate), timestamp);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the display mode." << Log::Flush();
		DE_ERROR_X(0x0);
	}
}

void X::setWindowClientRectangle(const ::Window windowHandle, const Core::Rectangle& rectangle) const
{
	const XWindowAttributes windowAttributes = getWindowAttributes(windowHandle);
	const Int32 x = rectangle.x - windowAttributes.x;
	const Int32 y = rectangle.y - windowAttributes.y;
	XMoveResizeWindow(_connection, windowHandle, x, y, rectangle.width, rectangle.height);
}

void X::setWindowFullscreen(const ::Window windowHandle, const Bool isFullscreen) const
{
	const Atom fullscreenAtom = createAtom("_NET_WM_STATE_FULLSCREEN");
	const Uint32 dataElementCount = isFullscreen ? 1u : 0u;

	setWindowProperty(windowHandle, "_NET_WM_STATE", "ATOM", reinterpret_cast<const Uint8*>(&fullscreenAtom),
		32u, dataElementCount);

	const ::Window rootWindowHandle = XRootWindow(_connection, GRAPHICS_ADAPTER_INDEX);
	XEvent event = XEvent();
	event.type = ClientMessage;
	event.xclient.data.l[0] = isFullscreen ? 1 : 0;
	event.xclient.data.l[1] = fullscreenAtom;
	event.xclient.format = 32;
	event.xclient.message_type = createAtom("_NET_WM_STATE");
	event.xclient.window = windowHandle;
	sendEvent(rootWindowHandle, event, SubstructureNotifyMask);
}

void X::setWindowMessageProtocols(const ::Window windowHandle, Atom* protocolAtoms,
	const Uint32 protocolAtomCount) const
{
	const Int32 result = XSetWMProtocols(_connection, windowHandle, protocolAtoms, protocolAtomCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			"Failed to set the message protocols of a window." << Log::Flush();

		DE_ERROR_X(0x0);
	}
}

void X::setWindowProperty(const ::Window windowHandle, const Char8* propertyName, const Char8* typeName,
	const Uint8* data, const Uint32 dataElementBitSize, const Uint32 dataElementCount) const
{
	const Atom propertyAtom = createAtom(propertyName);
	const Atom typeAtom = createAtom(typeName);

	XChangeProperty(_connection, windowHandle, propertyAtom, typeAtom, dataElementBitSize, PropModeReplace,
		data, dataElementCount);
}

void X::setWindowTitle(const ::Window windowHandle, const String8& title) const
{
	const Uint8* titleData = reinterpret_cast<const Uint8*>(title.c_str());
	const Uint32 titleLength = static_cast<Uint32>(title.length()) + 1u;
	setWindowProperty(windowHandle, "_NET_WM_NAME", "UTF8_STRING", titleData, 8u, titleLength);
	setWindowProperty(windowHandle, "WM_NAME", "UTF8_STRING", titleData, 8u, titleLength);
}

void X::setWindowUserData(const ::Window windowHandle, Void* data) const
{
	const Int32 result =
		XSaveContext(_connection, windowHandle, _windowUserDataContext, static_cast<Char8*>(data));

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to set the user data of a window." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}
}

// Private

const Int32 X::GRAPHICS_ADAPTER_INDEX = 0;

void X::initialiseConnection()
{
	_connection = XOpenDisplay(nullptr);

	if(_connection == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to initialise a connection." <<
			Log::Flush();

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
	const Version xrandrVersion = getXRandRVersion();

	if(xrandrVersion == Version(0u, 0u))
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "XRandR is not supported." << Log::Flush();
		DE_ERROR_X(0x0);
	}
	else if(xrandrVersion < ::MIN_SUPPORTED_XRANDR_VERSION)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "XRandR version " <<
			xrandrVersion.majorNumber() << '.' << xrandrVersion.minorNumber() <<
			" is not supported. The minimum supported version is " <<
			::MIN_SUPPORTED_XRANDR_VERSION.majorNumber() << '.' <<
			::MIN_SUPPORTED_XRANDR_VERSION.minorNumber() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
	else
	{
		defaultLog << LogLevel::Info << "Using XRandR version " << xrandrVersion.majorNumber() << '.' <<
			xrandrVersion.minorNumber() << '.' << Log::Flush();
	}
}

XWindowAttributes X::getWindowAttributes(const ::Window windowHandle) const
{
	XWindowAttributes windowAttributes;
	const Int32 result = XGetWindowAttributes(_connection, windowHandle, &windowAttributes);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the attributes of a window." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}

	return windowAttributes;
}

Version X::getXRandRVersion() const
{
	Int32 baseEventType;
	Int32 baseErrorCode;
	Int32 result = XRRQueryExtension(_connection, &baseEventType, &baseErrorCode);

	if(result == 0)
		return Version(0u, 0u);

	Int32 majorVersion = 0;
	Int32 minorVersion = 0;
	result = XRRQueryVersion(_connection, &majorVersion, &minorVersion);

	if(result == 0)
		return Version(0u, 0u);

	return Version(majorVersion, minorVersion);
}


// External

static Int32 handleError(Display* xConnection, XErrorEvent* errorInfo)
{
	Char8 errorMessage[512];
	XGetErrorText(xConnection, errorInfo->error_code, errorMessage, sizeof(errorMessage));

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << "X error occurred, " << errorMessage << " (" <<
		StreamFormat::Hexadecimal << static_cast<Uint32>(errorInfo->error_code) << StreamFormat::Decimal <<
		")." << Log::Flush();

	std::abort();
	return 0;
}

static Int32 handleIOError(Display* xConnection)
{
	static_cast<Void>(xConnection);

	defaultLog << LogLevel::Error << ::COMPONENT_TAG << "X error occurred, the connection was terminated." <<
		Log::Flush();

	std::abort();
	return 0;
}

static void initialiseMultithreading()
{
	const Int32 result = XInitThreads();

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to initialise multithreading." <<
			Log::Flush();

		DE_ERROR_X(0x0);
	}
}

static void setErrorHandlers()
{
	XSetErrorHandler(::handleError);
	XSetIOErrorHandler(::handleIOError);
}
