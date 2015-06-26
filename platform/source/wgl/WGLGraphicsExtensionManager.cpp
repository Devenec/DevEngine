/**
 * @file platform/wgl/WGLGraphicsExtensionManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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
	getOpenGLExtensionFunction();
}

// Private

const Char8* GraphicsExtensionManager::COMPONENT_TAG = "[Platform::GraphicsExtensionManager - WGL]";

// Static

void GraphicsExtensionManager::validateContextState()
{
	if(wglGetCurrentContext() == nullptr)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " No current context exists." << Log::Flush();
		DE_ERROR(0x0); // TODO: set errorCode
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

void GraphicsExtensionManager::getOpenGLExtensionFunction()
{
	// TODO: implement
}
