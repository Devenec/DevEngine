/**
 * @file platform/wgl/WGLGraphicsContext.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Array.h>
#include <core/Memory.h>
#include <core/Log.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsContext.h>
#include <graphics/Window.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsContext::Impl final : public GraphicsContextBase
{
public:

	explicit Impl(HWND windowHandle)
		: Base(windowHandle)
	{
		initialisePixelFormat();
		createContext();
		makeCurrent();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	using Base = GraphicsContextBase;

	static const Char8* COMPONENT_TAG;
	static const Array<Int32, 9u> CONTEXT_ATTRIBUTES;

	void initialisePixelFormat() const
	{
		setPixelFormat(1);
	}

	void createContext()
	{
		_graphicsContextHandle = wglCreateContextAttribsARB(_deviceContextHandle, nullptr, CONTEXT_ATTRIBUTES.data());

		if(_graphicsContextHandle == nullptr)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the context." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0); // TODO: set errorCode
		}
	}
};

const Char8* GraphicsContext::Impl::COMPONENT_TAG = "[Platform::GraphicsContext - WGL]";

// TODO: don't use the debug context in production build
const Array<Int32, 9u> GraphicsContext::Impl::CONTEXT_ATTRIBUTES
{{
	WGL_CONTEXT_FLAGS_ARB,		   WGL_CONTEXT_DEBUG_BIT_ARB,
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 5,
	WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
}};


// Public

GraphicsContext::GraphicsContext()
	: _impl(nullptr) { }

GraphicsContext::~GraphicsContext()
{
	DE_DELETE(_impl, Impl);
}

void GraphicsContext::initialise(Window* window)
{
	_impl = DE_NEW(Impl)(static_cast<HWND>(window->handle()));
}

void GraphicsContext::swapBuffers() const
{
	DE_ASSERT(_impl != nullptr);
	_impl->swapBuffers();
}
