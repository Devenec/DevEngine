/**
 * @file platform/wgl/WGLGraphicsContext.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Memory.h>
#include <graphics/GraphicsContext.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsContext::Impl final : public GraphicsContextBase
{
public:

	Impl(HWND windowHandle)
		: Base(windowHandle) { }

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	using Base = GraphicsContextBase;
};


// Public

GraphicsContext::GraphicsContext()
	: _impl(nullptr) { }

void GraphicsContext::deinitialise()
{
	DE_DELETE(_impl, Impl);
	_impl = nullptr;
}

void GraphicsContext::initialise(Window* window)
{
	_impl = DE_NEW(Impl)(static_cast<HWND>(window->handle()));
}
