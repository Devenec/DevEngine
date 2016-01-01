/**
 * @file platform/glx/GLXGraphicsContext.cpp
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
#include <platform/glx/GLXGraphicsContext.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContext - GLX]";

static const Array<Int32, 9u> CONTEXT_ATTRIBUTES
{{
	GLX::CONTEXT_FLAGS_ARB,			GLX::CONTEXT_DEBUG_BIT_ARB,
	GLX::CONTEXT_MAJOR_VERSION_ARB, 3,
	GLX::CONTEXT_MINOR_VERSION_ARB, 3,
	GLX::CONTEXT_PROFILE_MASK_ARB,	GLX::CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Implementation

// Public

GraphicsContext::Implementation::Implementation(const Window windowHandle, GLX::FBConfig configHandle)
	: _graphicsContextHandle(nullptr),
	  _windowHandle(windowHandle)
{
	_graphicsContextHandle = X::instance().createGraphicsContext(configHandle, ::CONTEXT_ATTRIBUTES.data(), true);
	checkContext();
}

GraphicsContext::Implementation::~Implementation()
{
	X::instance().destroyGraphicsContext(_graphicsContextHandle);
}

void GraphicsContext::Implementation::makeCurrent() const
{
	X::instance().makeGraphicsContextCurrent(_windowHandle, _graphicsContextHandle);
}

void GraphicsContext::Implementation::makeNonCurrent() const
{
	X::instance().makeGraphicsContextCurrent(None, nullptr);
}

void GraphicsContext::Implementation::swapBuffers() const
{
	X::instance().swapBuffers(_windowHandle);
}

// Private

void GraphicsContext::Implementation::checkContext() const
{
	if(!X::instance().isGraphicsContextDirect(_graphicsContextHandle))
		defaultLog << LogLevel::Warning << ::COMPONENT_TAG << " The graphics context is not direct." << Log::Flush();
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
