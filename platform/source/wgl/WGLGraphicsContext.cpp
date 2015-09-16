/**
 * @file platform/wgl/WGLGraphicsContext.cpp
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

#include <core/Array.h>
#include <core/Memory.h>
#include <core/Log.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsContext.h>
#include <graphics/Window.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsConfig.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContext - WGL]";

static const Array<Int32, 9u> CONTEXT_ATTRIBUTES
{{
	WGL::CONTEXT_FLAGS_ARB,			WGL::CONTEXT_DEBUG_BIT_ARB,
	WGL::CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL::CONTEXT_MINOR_VERSION_ARB, 4,
	WGL::CONTEXT_PROFILE_MASK_ARB,	WGL::CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Implementation

class GraphicsContext::Impl final : public GraphicsContextBase
{
public:

	explicit Impl(HWND windowHandle, const GraphicsConfig& graphicsConfig)
		: Base(windowHandle)
	{
		setPixelFormat(graphicsConfig._impl->pixelFormatIndex());
		createContext();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	using Base = GraphicsContextBase;

	void createContext()
	{
		_graphicsContextHandle = WGL::createContextAttribsARB(_deviceContextHandle, nullptr,
			CONTEXT_ATTRIBUTES.data());

		if(_graphicsContextHandle == nullptr)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the context." << Log::Flush();
			DE_ERROR_WINDOWS(0x0);
		}
	}
};


// Graphics::GraphicsContext

// Public

GraphicsContext::GraphicsContext(Window* window, const GraphicsConfig& graphicsConfig)
	: _impl(nullptr)
{
	DE_ASSERT(window != nullptr);
	_impl = DE_NEW(Impl)(static_cast<HWND>(window->handle()), graphicsConfig);
}

GraphicsContext::~GraphicsContext()
{
	DE_DELETE(_impl, Impl);
}

void GraphicsContext::makeCurrent() const
{
	_impl->makeCurrent();
}

void GraphicsContext::makeNonCurrent() const
{
	_impl->makeNonCurrent();
}

void GraphicsContext::swapBuffers() const
{
	_impl->swapBuffers();
}
