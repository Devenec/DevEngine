/**
 * @file platform/wgl/WGL.cpp
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

#include <platform/GraphicsFunctionUtility.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::WGL] ";


// Public

// Standard

WGL::CreateContext WGL::createContext = wglCreateContext;
WGL::DeleteContext WGL::deleteContext = wglDeleteContext;
WGL::GetCurrentContext WGL::getCurrentContext = wglGetCurrentContext;
WGL::GetProcAddress WGL::getProcAddress = wglGetProcAddress;
WGL::MakeCurrent WGL::makeCurrent = wglMakeCurrent;

// WGL_ARB_create_context

WGL::CreateContextAttribsARB WGL::createContextAttribsARB = nullptr;

// WGL_ARB_extensions_string

WGL::GetExtensionsStringARB WGL::getExtensionsStringARB = nullptr;

// WGL_ARB_pixel_format

WGL::ChoosePixelFormatARB WGL::choosePixelFormatARB = nullptr;
WGL::GetPixelFormatAttribFVARB WGL::getPixelFormatAttribfvARB = nullptr;
WGL::GetPixelFormatAttribIVARB WGL::getPixelFormatAttribivARB = nullptr;


// Static

void WGL::initialise(const GraphicsContextBase& graphicsContext)
{
	// TODO: check current context state?

	initialiseExtensions();
	const ExtensionNameList extensionNames = getExtensionNames(graphicsContext);
	logGraphicsExtensions("graphics context", extensionNames);
	checkExtensionsSupport(extensionNames);
	getExtensionFunctions();
}

// Private

// Static

void WGL::initialiseExtensions()
{
	GraphicsFunctionUtility functionUtility;

	getExtensionsStringARB =
		functionUtility.getExtensionFunction<GetExtensionsStringARB>("wglGetExtensionsStringARB");
}

ExtensionNameList WGL::getExtensionNames(const GraphicsContextBase& graphicsContext)
{
	const String8 extensionNamesString(getExtensionsStringARB(graphicsContext.deviceContextHandle()));
	ExtensionNameList extensionNames;

	if(extensionNamesString.length() != 0u)
	{
		Uint currentPosition = 0u;
		Uint spacePosition;

		while((spacePosition = extensionNamesString.find(' ', currentPosition)) != String8::npos)
		{
			extensionNames.push_back(extensionNamesString.substr(currentPosition,
				spacePosition - currentPosition));

			currentPosition = spacePosition + 1u;
		}
	}

	return extensionNames;
}

void WGL::checkExtensionsSupport(const ExtensionNameList& extensionNames)
{
	const ExtensionNameSet extensionNameSet(extensionNames.begin(), extensionNames.end());
	GraphicsFunctionUtility::checkExtensionSupport(extensionNameSet, "WGL_ARB_create_context");
	GraphicsFunctionUtility::checkExtensionSupport(extensionNameSet, "WGL_ARB_pixel_format");
}

void WGL::getExtensionFunctions()
{
	GraphicsFunctionUtility functionUtility;

	// WGL_ARB_create_context

	createContextAttribsARB =
		functionUtility.getExtensionFunction<CreateContextAttribsARB>("wglCreateContextAttribsARB");

	// WGL_ARB_extensions_string

	// getExtensionsStringARB is initialised in WGL::initialiseExtensions()

	// WGL_ARB_pixel_format

	choosePixelFormatARB =
		functionUtility.getExtensionFunction<ChoosePixelFormatARB>("wglChoosePixelFormatARB");

	getPixelFormatAttribfvARB =
		functionUtility.getExtensionFunction<GetPixelFormatAttribFVARB>("wglGetPixelFormatAttribfvARB");

	getPixelFormatAttribivARB =
		functionUtility.getExtensionFunction<GetPixelFormatAttribIVARB>("wglGetPixelFormatAttribivARB");
}
