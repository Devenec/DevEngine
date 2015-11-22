/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <platform/opengl/OpenGL.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::TemporaryGraphicsContext - WGL]";
static const Int32 MIN_SUPPORTED_OPENGL_VERSION_MAJOR = 3;
static const Int32 MIN_SUPPORTED_OPENGL_VERSION_MINOR = 3;

static void checkOpenGLVersion();
static PIXELFORMATDESCRIPTOR createPixelFormatDescriptor();
static Bool isOpenGLVersionSupported(const Uint32 majorVersion, const Uint32 minorVersion);


// Public

TemporaryGraphicsContext::TemporaryGraphicsContext(HWND windowHandle)
	: Base(windowHandle)
{
	initialisePixelFormat();
	createContext();
	makeCurrent();
	::checkOpenGLVersion();
}

// Private

void TemporaryGraphicsContext::initialisePixelFormat() const
{
	const PIXELFORMATDESCRIPTOR pixelFormatDescriptor = ::createPixelFormatDescriptor();
	const Int32 pixelFormatIndex = choosePixelFormat(pixelFormatDescriptor);
	checkPixelFormat(pixelFormatIndex);
	setPixelFormat(pixelFormatIndex);
}

void TemporaryGraphicsContext::createContext()
{
	_graphicsContextHandle = WGL::createContext(_deviceContextHandle);

	if(_graphicsContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to create the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

Int32 TemporaryGraphicsContext::choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const
{
	const Int32 pixelFormatIndex = ChoosePixelFormat(_deviceContextHandle, &pixelFormatDescriptor);

	if(pixelFormatIndex == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to choose a pixel format." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return pixelFormatIndex;
}

void TemporaryGraphicsContext::checkPixelFormat(const Int32 pixelFormatIndex) const
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

	const Int32 result = DescribePixelFormat(_deviceContextHandle, pixelFormatIndex, sizeof(PIXELFORMATDESCRIPTOR),
		&pixelFormatDescriptor);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get the description of a pixel format." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	if((pixelFormatDescriptor.dwFlags & PFD_SUPPORT_OPENGL) == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " The device context does not support OpenGL." <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}


// External

static void checkOpenGLVersion()
{
	Uint32 majorVersion;
	Uint32 minorVersion;
	OpenGL::initialiseVersion(majorVersion, minorVersion);

	if(!::isOpenGLVersionSupported(majorVersion, minorVersion))
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " The OpenGL version " << majorVersion << '.' <<
			minorVersion << " is not supported. The minimum supported version is " <<
			::MIN_SUPPORTED_OPENGL_VERSION_MAJOR << '.' << ::MIN_SUPPORTED_OPENGL_VERSION_MINOR << '.' << Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

static PIXELFORMATDESCRIPTOR createPixelFormatDescriptor()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = PIXELFORMATDESCRIPTOR();
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1u;

	return pixelFormatDescriptor;
}

static Bool isOpenGLVersionSupported(const Uint32 majorVersion, const Uint32 minorVersion)
{
	if(majorVersion < ::MIN_SUPPORTED_OPENGL_VERSION_MAJOR)
		return false;
	else if(majorVersion == ::MIN_SUPPORTED_OPENGL_VERSION_MAJOR)
		return minorVersion >= ::MIN_SUPPORTED_OPENGL_VERSION_MINOR;
	else
		return true;
}
