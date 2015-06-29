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
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/wgl/WGLGraphicsExtensionManager.h>

using namespace Core;
using namespace Platform;

// Public

// Static

void GraphicsExtensionManager::initialiseExtensions(const GraphicsContextBase& graphicsContext)
{
	validateContextState();
	getContextExtensionFunctions();
	logSupportedContextExtensions(graphicsContext.deviceContextHandle());
}

// Private

const Char8* GraphicsExtensionManager::COMPONENT_TAG = "[Platform::GraphicsExtensionManager - WGL]";

// Static

void GraphicsExtensionManager::validateContextState()
{
	if(wglGetCurrentContext() == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " No current context exists." << Log::Flush();
		DE_ERROR(0x0);
	}
}

void GraphicsExtensionManager::getContextExtensionFunctions()
{
	wglChoosePixelFormatARB = getExtensionFunction<WGLChoosePixelFormatARB>("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = getExtensionFunction<WGLCreateContextAttribsARB>("wglCreateContextAttribsARB");
	wglGetExtensionsStringARB = getExtensionFunction<WGLGetExtensionsStringARB>("wglGetExtensionsStringARB");
	wglGetPixelFormatAttribfvARB = getExtensionFunction<WGLGetPixelFormatAttribFVARB>("wglGetPixelFormatAttribfvARB");
	wglGetPixelFormatAttribivARB = getExtensionFunction<WGLGetPixelFormatAttribIVARB>("wglGetPixelFormatAttribivARB");
	wglGetSwapIntervalEXT = getExtensionFunction<WGLGetSwapIntervalEXT>("wglGetSwapIntervalEXT");
	wglSwapIntervalEXT = getExtensionFunction<WGLSwapIntervalEXT>("wglSwapIntervalEXT");
}

void GraphicsExtensionManager::logSupportedContextExtensions(HDC deviceContextHandle)
{
	defaultLog << LogLevel::Info << COMPONENT_TAG;

	if(wglGetExtensionsStringARB == nullptr)
		defaultLog << " No WGL extensions are supported.";
	else
		defaultLog << " Supported WGL extensions: " << wglGetExtensionsStringARB(deviceContextHandle);
	
	defaultLog << Log::Flush();
}
