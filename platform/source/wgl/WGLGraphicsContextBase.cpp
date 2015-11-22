/**
 * @file platform/wgl/WGLGraphicsContextBase.cpp
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

#include <core/Log.h>
#include <core/debug/Assert.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContextBase - WGL]";


// Public

void GraphicsContextBase::makeCurrent() const
{
	const Int32 result = WGL::makeCurrent(_deviceContextHandle, _graphicsContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to make the context current." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

void GraphicsContextBase::makeNonCurrent() const
{
	const Int32 result = WGL::makeCurrent(_deviceContextHandle, nullptr);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to make the context non-current." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

void GraphicsContextBase::swapBuffers() const
{
	const Int32 result = SwapBuffers(_deviceContextHandle);
	DE_ASSERT(result != 0);
}

// Protected

GraphicsContextBase::GraphicsContextBase(HWND windowHandle)
	: _deviceContextHandle(nullptr),
	  _graphicsContextHandle(nullptr)
{
	DE_ASSERT(windowHandle != nullptr);
	_deviceContextHandle = getWindowDeviceContextHandle(windowHandle);
}

GraphicsContextBase::~GraphicsContextBase()
{
	if(_graphicsContextHandle != nullptr)
		destroyContext();
}

void GraphicsContextBase::destroyContext()
{
	const Int32 result = WGL::deleteContext(_graphicsContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to destroy the context." << Log::Flush();
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
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to set a pixel format." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}
