/**
 * @file platform/wgl/WGLGraphicsContextBase.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

namespace Platform
{
	class GraphicsContextBase
	{
	public:

		GraphicsContextBase(const GraphicsContextBase& graphicsContext) = delete;
		GraphicsContextBase(GraphicsContextBase&& graphicsContext) = delete;

		inline void swapBuffers() const;

		GraphicsContextBase& operator =(const GraphicsContextBase& graphicsContext) = delete;
		GraphicsContextBase& operator =(GraphicsContextBase&& graphicsContext) = delete;

	protected:

		HDC _deviceContextHandle;
		HGLRC _graphicsContextHandle;

		inline GraphicsContextBase(HWND windowHandle);

		inline ~GraphicsContextBase();

		void createContext();

		void destroyContext();

		void makeCurrent() const;

		void makeNonCurrent() const;

		void setPixelFormat(const Int32 pixelFormatIndex) const;

	private:

		void initialiseDeviceContext(HWND windowHandle);
	};

#include "inline/WGLGraphicsContextBase.inl"
}
