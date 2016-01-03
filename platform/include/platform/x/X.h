/**
 * @file platform/x/X.h
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

#pragma once

#include <core/ConfigInternal.h>
#include <core/Rectangle.h>
#include <core/Singleton.h>
#include <core/String.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <platform/glx/GLX.h>
#include <platform/x/XInclude.h>

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

		inline Atom createAtom(const Char8* name) const;

		GLX::Context createGraphicsContext(GLX::FBConfig configHandle, const Int32* attributes,
			const Bool isDirect) const;

		Cursor createHiddenPointer(const Window windowHandle) const;

		Window createWindow(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height,
			XVisualInfo* visualInfo, XSetWindowAttributes& attributes, const Uint32 attributeMask) const;

		inline void destroyGraphicsContext(GLX::Context contextHandle) const;

		inline void destroyPointer(const Cursor pointerHandle) const;

		inline void destroyWindow(const Window windowHandle) const;

		void destroyWindowProperty(const Window windowHandle, const Char8* propertyName) const;

		void destroyWindowUserData(const Window windowHandle) const;

		inline const Char8* getExtensionNameString() const;

		XRRScreenConfiguration* getGraphicsAdapterConfig(const Uint32 adapterIndex) const;

		inline Uint32 getGraphicsAdapterCount() const;

		inline Int16* getGraphicsAdapterRefreshRates(const Uint32 adapterIndex, const Uint32 resolutionIndex,
			Uint32& rateCount) const;

		inline XRRScreenSize* getGraphicsAdapterResolutions(const Uint32 adapterIndex,
			Uint32& resolutionCount) const;

		Int32 getGraphicsConfigAttribute(GLX::FBConfig configHandle, const Int32 attributeName) const;

		GLX::FBConfig* getGraphicsConfigs(const Int32* attributes, Uint32& configCount) const;

		XVisualInfo* getGraphicsConfigVisualInfo(GLX::FBConfig configHandle) const;

		inline Window getRootWindowHandle(const Uint32 graphicsAdapterIndex) const;

		Core::Rectangle getWindowClientRectangle(const Window windowHandle) const;

		Void* getWindowUserData(const Window windowHandle) const;

		inline Bool hasPendingEvents() const;

		inline void hideWindow(const Window windowHandle) const;

		void invokeError(const Uint32 errorCode) const;

		void invokeError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function)
			const;

		Bool isGLXSupported(Uint32& versionMajor, Uint32& versionMinor) const;

		inline Bool isGraphicsContextDirect(GLX::Context contextHandle) const;

		void makeGraphicsContextCurrent(GLX::Drawable drawableHandle, GLX::Context contextHandle) const;

		XEvent popEvent() const;

		void setDisplayMode(XRRScreenConfiguration* graphicsAdapterConfig, const Drawable rootWindowHandle,
			const Uint32 resolutionIndex, const Uint32 refreshRate, const Time timestamp) const;

		void setWindowClientRectangle(const Window windowHandle, const Core::Rectangle& rectangle) const;

		void setWindowFullscreen(const Window windowHandle, const Bool isFullscreen) const;

		void setWindowMessageProtocols(const Window windowHandle, Atom* protocolAtoms,
			const Uint32 protocolAtomCount) const;

		inline void setWindowPointer(const Window windowHandle, const Cursor pointerHandle) const;

		void setWindowProperty(const Window windowHandle, const Char8* propertyName, const Char8* typeName,
			const Uint8* data, const Uint32 dataElementBitSize, const Uint32 dataElementCount) const;

		void setWindowTitle(const Window windowHandle, const Core::String8& title) const;

		void setWindowUserData(const Window windowHandle, Void* data) const;

		inline void showWindow(const Window windowHandle) const;

		inline void swapBuffers(GLX::Drawable drawableHandle) const;

		X& operator =(const X& x) = delete;
		X& operator =(X&& x) = delete;

	private:

		static const Int32 GRAPHICS_ADAPTER_INDEX;

		Display* _connection;
		Int32 _windowUserDataContext;

		void checkConnection() const;
		void checkXRandRSupport() const;
		XWindowAttributes getWindowAttributes(const Window windowHandle) const;
		void sendEvent(const Window windowHandle, XEvent& event, const Int32 eventMask) const;
	};

#include "inline/X.inl"
}
