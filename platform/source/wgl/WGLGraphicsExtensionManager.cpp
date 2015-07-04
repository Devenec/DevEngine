/**
 * @file platform/wgl/WGLGraphicsExtensionManager.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <platform/GraphicsExtensionManager.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// Implementation

class GraphicsExtensionManager::Impl final
{
public:

	Impl() = delete;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = delete;

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

	static void validateContextState()
	{
		if(wglGetCurrentContext() == nullptr)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " No current context exists." << Log::Flush();
			DE_ERROR(0x0);
		}
	}

	static void getContextExtensionFunctions()
	{
		wglChoosePixelFormatARB = getExtensionFunction<WGLChoosePixelFormatARB>("wglChoosePixelFormatARB");
		wglCreateContextAttribsARB = getExtensionFunction<WGLCreateContextAttribsARB>("wglCreateContextAttribsARB");
		wglGetExtensionsStringARB = getExtensionFunction<WGLGetExtensionsStringARB>("wglGetExtensionsStringARB");

		wglGetPixelFormatAttribfvARB = getExtensionFunction<WGLGetPixelFormatAttribFVARB>(
			"wglGetPixelFormatAttribfvARB");

		wglGetPixelFormatAttribivARB = getExtensionFunction<WGLGetPixelFormatAttribIVARB>(
			"wglGetPixelFormatAttribivARB");

		wglGetSwapIntervalEXT = getExtensionFunction<WGLGetSwapIntervalEXT>("wglGetSwapIntervalEXT");
		wglSwapIntervalEXT = getExtensionFunction<WGLSwapIntervalEXT>("wglSwapIntervalEXT");
	}

	static void logSupportedContextExtensions(HDC deviceContextHandle)
	{
		defaultLog << LogLevel::Info << COMPONENT_TAG;

		if(wglGetExtensionsStringARB == nullptr)
			defaultLog << " No WGL extensions are supported.";
		else
			defaultLog << " Supported WGL extensions: " << wglGetExtensionsStringARB(deviceContextHandle);
	
		defaultLog << Log::Flush();
	}

	template<typename T>
	static T getExtensionFunction(const Char8* functionName)
	{
		return reinterpret_cast<T>(wglGetProcAddress(functionName));
	}

private:

	static const Char8* COMPONENT_TAG;
};

const Char8* GraphicsExtensionManager::Impl::COMPONENT_TAG = "[Platform::GraphicsExtensionManager - WGL]";


// Public

// Static

Void* GraphicsExtensionManager::getExtensionFunction(const Char8* functionName)
{
	return Impl::getExtensionFunction<Void*>(functionName);
}

void GraphicsExtensionManager::initialiseContextExtensions(const GraphicsContextBase& graphicsContext)
{
	Impl::validateContextState();
	Impl::getContextExtensionFunctions();
	Impl::logSupportedContextExtensions(graphicsContext.deviceContextHandle());
}
