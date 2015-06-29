/**
 * @file platform/wgl/WGLGraphicsContextBase.cpp
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

#include <core/Log.h>
#include <platform/wgl/WGLGraphicsContextBase.h>

using namespace Core;
using namespace Platform;

// Public

void GraphicsContextBase::makeCurrent() const
{
	const Int32 result = wglMakeCurrent(_deviceContextHandle, _graphicsContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to make the context current." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

void GraphicsContextBase::makeNonCurrent() const
{
	const Int32 result = wglMakeCurrent(_deviceContextHandle, nullptr);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to make the context non-current." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

// Protected

GraphicsContextBase::GraphicsContextBase(HWND windowHandle)
	: _deviceContextHandle(nullptr),
	  _graphicsContextHandle(nullptr)
{
	DE_ASSERT(windowHandle != nullptr);
	initialiseDeviceContext(windowHandle);
}

GraphicsContextBase::~GraphicsContextBase()
{
	if(_graphicsContextHandle != nullptr)
		destroyContext();
}

void GraphicsContextBase::destroyContext()
{
	const Int32 result = wglDeleteContext(_graphicsContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to destroy the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	_graphicsContextHandle = nullptr;
}

void GraphicsContextBase::setPixelFormat(const Int32 pixelFormatIndex) const
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	const Int32 result = SetPixelFormat(_deviceContextHandle, pixelFormatIndex, &pixelFormatDescriptor);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to set a pixel format." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

// Private

const Char8* GraphicsContextBase::COMPONENT_TAG = "[Platform::GraphicsContextBase - WGL]";

void GraphicsContextBase::initialiseDeviceContext(HWND windowHandle)
{
	_deviceContextHandle = GetDC(windowHandle);

	if(_deviceContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the device context of a window." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}
