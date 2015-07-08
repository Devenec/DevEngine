/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Error.h>
#include <core/Log.h>
#include <platform/opengl/OpenGL.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>

using namespace Core;
using namespace Platform;

// Public

TemporaryGraphicsContext::TemporaryGraphicsContext(HWND windowHandle)
	: Base(windowHandle) { }

void TemporaryGraphicsContext::deinitialise()
{
	destroyContext();
}

void TemporaryGraphicsContext::initialise()
{
	initialisePixelFormat();
	createContext();
	makeCurrent();
	checkOpenGLVersion();
}

// Private

const Char8* TemporaryGraphicsContext::COMPONENT_TAG = "[Platform::TemporaryGraphicsContext - WGL]";

void TemporaryGraphicsContext::initialisePixelFormat() const
{
	const PIXELFORMATDESCRIPTOR pixelFormatDescriptor = createPixelFormatDescriptor();
	const Int32 pixelFormatIndex = choosePixelFormat(pixelFormatDescriptor);
	checkPixelFormat(pixelFormatIndex);
	setPixelFormat(pixelFormatIndex);
}

void TemporaryGraphicsContext::createContext()
{
	_graphicsContextHandle = wglCreateContext(_deviceContextHandle);

	if(_graphicsContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

Int32 TemporaryGraphicsContext::choosePixelFormat(const PIXELFORMATDESCRIPTOR& pixelFormatDescriptor) const
{
	const Int32 pixelFormatIndex = ChoosePixelFormat(_deviceContextHandle, &pixelFormatDescriptor);

	if(pixelFormatIndex == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to choose a pixel format." << Log::Flush();
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
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the description of a pixel format." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	if((pixelFormatDescriptor.dwFlags & PFD_SUPPORT_OPENGL) == 0u)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " The device context does not support OpenGL." <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}

// Static

void TemporaryGraphicsContext::checkOpenGLVersion()
{
	const String8 versionString(reinterpret_cast<const Char8*>(glGetString(GL_VERSION)));
	const Uint32 majorVersion = getOpenGLMajorVersion(versionString);
	const Uint32 minorVersion = getOpenGLMinorVersion(versionString);

	if(!isOpenGLVersionSupported(majorVersion, minorVersion))
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " The OpenGL version " << majorVersion << '.' <<
			minorVersion << " is not supported. The minimum supported version is " <<
			MIN_SUPPORTED_OPENGL_VERSION_MAJOR << '.' << MIN_SUPPORTED_OPENGL_VERSION_MINOR << '.' << Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

PIXELFORMATDESCRIPTOR TemporaryGraphicsContext::createPixelFormatDescriptor()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor = PIXELFORMATDESCRIPTOR();
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1u;

	return pixelFormatDescriptor;
}

Uint32 TemporaryGraphicsContext::getOpenGLMajorVersion(const String8& versionString)
{
	const Uint32 delimiterPosition = versionString.find('.');
	return std::stoi(versionString.substr(0u, delimiterPosition));
}

Uint32 TemporaryGraphicsContext::getOpenGLMinorVersion(const String8& versionString)
{
	const Uint32 minorNumberPosition = versionString.find('.') + 1u;
	const Uint32 secondDelimiterPosition = versionString.find('.', minorNumberPosition);
	Uint32 versionEndPosition = versionString.find(' ');

	if(secondDelimiterPosition < versionEndPosition)
		versionEndPosition = secondDelimiterPosition;

	return std::stoi(versionString.substr(minorNumberPosition, versionEndPosition - minorNumberPosition));
}

Bool TemporaryGraphicsContext::isOpenGLVersionSupported(const Uint32 majorVersion, const Uint32 minorVersion)
{
	if(majorVersion < MIN_SUPPORTED_OPENGL_VERSION_MAJOR)
		return false;
	else if(majorVersion == MIN_SUPPORTED_OPENGL_VERSION_MAJOR)
		return minorVersion >= MIN_SUPPORTED_OPENGL_VERSION_MINOR;
	else
		return true;
}
