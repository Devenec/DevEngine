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
#include <core/Platform.h>
#include <core/Types.h>
#include <platform/GraphicsContext.h>
#include <platform/Version.h>
#include <platform/glx/GLX.h>
#include <platform/opengl/OpenGL.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsContext - GLX] ";

#if DE_BUILD == DE_BUILD_DEBUG
static const Int32 CONTEXT_FLAGS = GLX::CONTEXT_DEBUG_BIT_ARB;
#else
static const Int32 CONTEXT_FLAGS = 0;
#endif

static const Uint32 MAJOR_VERSION_ATTRIBUTE_INDEX = 3u;
static const Uint32 MINOR_VERSION_ATTRIBUTE_INDEX = 5u;

static Array<Int32, 9u> CONTEXT_ATTRIBUTES
{{
	GLX::CONTEXT_FLAGS_ARB,			::CONTEXT_FLAGS,
	GLX::CONTEXT_MAJOR_VERSION_ARB, 0,
	GLX::CONTEXT_MINOR_VERSION_ARB, 0,
	GLX::CONTEXT_PROFILE_MASK_ARB,	GLX::CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Implementation

class GraphicsContext::Implementation final
{
public:

	Implementation(WindowHandle windowHandle, ConfigHandle configHandle)
		: _graphicsContextHandle(nullptr),
		  _windowHandle(reinterpret_cast<::Window>(windowHandle))
	{
		createContext(static_cast<GLX::FBConfig>(configHandle));
		checkContext();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		X::instance().destroyGraphicsContext(_graphicsContextHandle);
	}

	void makeCurrent() const
	{
		X::instance().makeGraphicsContextCurrent(_windowHandle, _graphicsContextHandle);
	}

	void makeNonCurrent() const
	{
		X::instance().makeGraphicsContextCurrent(None, nullptr);
	}

	void swapBuffers() const
	{
		X::instance().swapBuffers(_windowHandle);
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GLX::Context _graphicsContextHandle;
	::Window _windowHandle;

	void createContext(GLX::FBConfig configHandle)
	{
		for(Uint i = OpenGL::SUPPORTED_VERSIONS.size(); i > 0u; --i)
		{
			_graphicsContextHandle =
				createContextWithVersion(configHandle, OpenGL::SUPPORTED_VERSIONS[i - 1u]);

			if(_graphicsContextHandle != nullptr)
				break;
		}

		if(_graphicsContextHandle == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the context." <<
				Log::Flush();

			DE_ERROR_X(0x0);
		}
	}

	void checkContext() const
	{
		if(!X::instance().isGraphicsContextDirect(_graphicsContextHandle))
		{
			defaultLog << LogLevel::Warning << ::COMPONENT_TAG << "The context is not direct." <<
				Log::Flush();
		}
	}

	GLX::Context createContextWithVersion(GLX::FBConfig configHandle, const Version& version) const
	{
		::CONTEXT_ATTRIBUTES[::MAJOR_VERSION_ATTRIBUTE_INDEX] = version.majorNumber();
		::CONTEXT_ATTRIBUTES[::MINOR_VERSION_ATTRIBUTE_INDEX] = version.minorNumber();

		return X::instance().createGraphicsContext(configHandle, ::CONTEXT_ATTRIBUTES.data(), true);
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
