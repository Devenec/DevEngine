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
#include <core/Platform.h>
#include <core/Types.h>
#include <platform/GraphicsContext.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContext - WGL] ";

#if DE_BUILD == DE_BUILD_DEBUG
static const Int32 CONTEXT_FLAGS = WGL::CONTEXT_DEBUG_BIT_ARB;
#else
static const Int32 CONTEXT_FLAGS = 0;
#endif

static const Array<Int32, 9u> CONTEXT_ATTRIBUTES
{{
	WGL::CONTEXT_FLAGS_ARB,			::CONTEXT_FLAGS,
	WGL::CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL::CONTEXT_MINOR_VERSION_ARB, 3,
	WGL::CONTEXT_PROFILE_MASK_ARB,	WGL::CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Implementation

class GraphicsContext::Implementation final : public GraphicsContextBase
{
public:

	// Public

	Implementation(WindowHandle windowHandle, ConfigHandle configHandle)
		: Base(static_cast<HWND>(windowHandle))
	{
		const Int32 configIndex = static_cast<Int32>(reinterpret_cast<Int>(configHandle));
		setConfig(configIndex);
		initialise();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	using Base = GraphicsContextBase;

	void initialise()
	{
		_graphicsContextHandle =
			WGL::createContextAttribsARB(_deviceContextHandle, nullptr, ::CONTEXT_ATTRIBUTES.data());

		if(_graphicsContextHandle == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the context." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}
	}
};


// Platform::GraphicsContext

// Public

GraphicsContext::GraphicsContext(WindowHandle windowHandle, ConfigHandle configHandle)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(windowHandle, configHandle);
}

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
