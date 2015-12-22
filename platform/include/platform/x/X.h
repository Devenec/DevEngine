/**
 * @file platform/x/X.h
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

#pragma once

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#undef Bool

#include <core/ConfigInternal.h>
#include <core/Singleton.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <platform/glx/GLXTypes.h>

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)
	#define DE_ERROR_X(errorCode) \
		Platform::X::instance().invokeError(errorCode, DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_ERROR_X(errorCode) \
		Platform::X::instance().invokeError(errorCode)
#endif

namespace Platform
{
	class X : public Core::Singleton<X>
	{
	public:

		X();

		X(const X& x) = delete;
		X(X&& x) = delete;

		~X();

		GLXContext createGraphicsContext(GLXFBConfig configHandle, const Int32* attributes, const Bool isDirect) const;

		Window createWindow(const Window parentWindowHandle, const Int32 x, const Int32 y, const Uint32 width,
			const Uint32 height, XVisualInfo* visualInfo, XSetWindowAttributes& attributes, const Uint32 attributeMask)
			const;

		void destroyGraphicsContext(GLXContext contextHandle) const;

		inline void destroyWindow(const Window windowHandle) const;

		inline Int32 getDefaultGraphicsAdapterIndex() const;

		const Char8* getExtensionNameString() const;

		XRRScreenConfiguration* getGraphicsAdapterConfig(const Uint32 adapterIndex) const;

		inline Uint32 getGraphicsAdapterCount() const;

		inline Int16* getGraphicsAdapterRefreshRates(const Uint32 adapterIndex, const Uint32 resolutionIndex,
			Uint32& rateCount) const;

		inline XRRScreenSize* getGraphicsAdapterResolutions(const Uint32 adapterIndex, Uint32& resolutionCount) const;

		Int32 getGraphicsConfigAttribute(GLXFBConfig configHandle, const Int32 attributeName) const;

		GLXFBConfig* getGraphicsConfigs(const Int32* attributes, Uint32& configCount) const;

		XVisualInfo* getGraphicsConfigVisualInfo(GLXFBConfig configHandle) const;

		inline Window getRootWindowHandle(const Uint32 graphicsAdapterIndex) const;

		inline Bool hasPendingEvents() const;

		void invokeError(const Uint32 errorCode) const;

		void invokeError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function) const;

		Bool isGLXSupported(Uint32& versionMajor, Uint32& versionMinor) const;

		Bool isGraphicsContextDirect(GLXContext contextHandle) const;

		void makeGraphicsContextCurrent(GLXDrawable drawableHandle, GLXContext contextHandle) const;

		XEvent popEvent() const;

		void setDisplayMode(XRRScreenConfiguration* graphicsAdapterConfig, const Drawable rootWindowHandle,
			const Uint32 resolutionIndex, const Uint32 refreshRate, const Time timestamp) const;

		void swapBuffers(GLXDrawable drawableHandle) const;

		X& operator =(const X& x) = delete;
		X& operator =(X&& x) = delete;

	private:

		Display* _connection;

		void checkConnection() const;
		void checkXRandRSupport() const;
	};

#include "inline/X.inl"
}
