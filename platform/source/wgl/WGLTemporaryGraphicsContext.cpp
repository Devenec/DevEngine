/**
 * @file platform/wgl/WGLTemporaryGraphicsContext.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::TemporaryGraphicsContext - WGL] ";

static PIXELFORMATDESCRIPTOR createConfigDescriptor();


// Public

TemporaryGraphicsContext::TemporaryGraphicsContext(HWND windowHandle)
	: Base(windowHandle)
{
	initialiseConfig();
	createContext();
	makeCurrent();
}

// Private

void TemporaryGraphicsContext::initialiseConfig() const
{
	const PIXELFORMATDESCRIPTOR configDescriptor = ::createConfigDescriptor();
	const Int32 configIndex = chooseConfig(configDescriptor);
	checkConfig(configIndex);
	setConfig(configIndex);
}

void TemporaryGraphicsContext::createContext()
{
	_graphicsContextHandle = WGL::createContext(_deviceContextHandle);

	if(_graphicsContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

Int32 TemporaryGraphicsContext::chooseConfig(const PIXELFORMATDESCRIPTOR& configDescriptor) const
{
	const Int32 configIndex = ChoosePixelFormat(_deviceContextHandle, &configDescriptor);

	if(configIndex == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to choose a configuration." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return configIndex;
}

void TemporaryGraphicsContext::checkConfig(const Int32 configIndex) const
{
	PIXELFORMATDESCRIPTOR configDescriptor;

	const Int32 result =
		DescribePixelFormat(_deviceContextHandle, configIndex, sizeof(PIXELFORMATDESCRIPTOR),
			&configDescriptor);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get configuration attributes." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	if((configDescriptor.dwFlags & PFD_SUPPORT_OPENGL) == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "The device context does not support OpenGL." <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}


// External

static PIXELFORMATDESCRIPTOR createConfigDescriptor()
{
	PIXELFORMATDESCRIPTOR configDescriptor = PIXELFORMATDESCRIPTOR();
	configDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	configDescriptor.iPixelType = PFD_TYPE_RGBA;
	configDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	configDescriptor.nVersion = 1u;

	return configDescriptor;
}
