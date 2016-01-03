/**
 * @file platform/wgl/WGLGraphicsContext.cpp
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

#include <core/Array.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContext.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContext - WGL] ";

static const Array<Int32, 9u> CONTEXT_ATTRIBUTES
{{
	WGL::CONTEXT_FLAGS_ARB,			WGL::CONTEXT_DEBUG_BIT_ARB,
	WGL::CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL::CONTEXT_MINOR_VERSION_ARB, 5,
	WGL::CONTEXT_PROFILE_MASK_ARB,	WGL::CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Implementation

// Public

GraphicsContext::Implementation::Implementation(WindowHandle windowHandle, const Int32 pixelFormatIndex)
	: Base(static_cast<HWND>(windowHandle))
{
	setPixelFormat(pixelFormatIndex);
	initialise();
}

// Private

void GraphicsContext::Implementation::initialise()
{
	_graphicsContextHandle = WGL::createContextAttribsARB(_deviceContextHandle, nullptr, ::CONTEXT_ATTRIBUTES.data());

	if(_graphicsContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}


// Platform::GraphicsContext

// Public

GraphicsContext::GraphicsContext(Implementation* implementation)
	: _implementation(implementation) { }

GraphicsContext::~GraphicsContext()
{
	DE_DELETE(_implementation, Implementation);
}

void GraphicsContext::makeCurrent() const
{
	_implementation->makeCurrent();
}

void GraphicsContext::makeNonCurrent() const
{
	_implementation->makeNonCurrent();
}

void GraphicsContext::swapBuffers() const
{
	_implementation->swapBuffers();
}
