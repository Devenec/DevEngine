/**
 * @file platform/glx/GLX.cpp
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

#include <dlfcn.h>
#include <core/Error.h>
#include <core/Log.h>
#include <platform/GraphicsFunctionUtility.h>
#include <platform/Utility.h>
#include <platform/glx/GLX.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG			   = "[Platform::GLX] ";
static const Char8* LIBRARY_FILENAME		   = "libGL.so";
static const Int32 MIN_SUPPORTED_VERSION_MAJOR = 1;
static const Int32 MIN_SUPPORTED_VERSION_MINOR = 4;


// Public

// Version 1.0

GLX::DestroyContext GLX::destroyContext = nullptr;
GLX::IsDirect GLX::isDirect = nullptr;
GLX::QueryExtension GLX::queryExtension = nullptr;
GLX::QueryVersion GLX::queryVersion = nullptr;
GLX::SwapBuffers GLX::swapBuffers = nullptr;

// Version 1.1

GLX::QueryExtensionsString GLX::queryExtensionsString = nullptr;

// Version 1.3

GLX::ChooseFBConfig GLX::chooseFBConfig = nullptr;
GLX::GetFBConfigAttrib GLX::getFBConfigAttrib = nullptr;
GLX::GetVisualFromFBConfig GLX::getVisualFromFBConfig = nullptr;
GLX::MakeContextCurrent GLX::makeContextCurrent = nullptr;

// Version 1.4

GLX::GetProcAddress GLX::getProcAddress = nullptr;

// GLX_ARB_create_context

GLX::CreateContextAttribsARB GLX::createContextAttribsARB = nullptr;


GLX::GLX()
	: _libraryHandle(nullptr)
{
	loadLibrary();
	getStandardFunctions();
	checkSupport();
	initialiseExtensions();
}

GLX::~GLX()
{
	clearFunctions();
	//unloadLibrary(); // TODO: unloading the library causes XCloseDisplay() to crash at X.cpp, find out why
}

// Private

void GLX::loadLibrary()
{
	_libraryHandle = dlopen(::LIBRARY_FILENAME, RTLD_LAZY);

	if(_libraryHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to load the library " <<
			::LIBRARY_FILENAME << ": " << dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
}

void GLX::getStandardFunctions() const
{
	// Version 1.0

	destroyContext = getStandardFunction<DestroyContext>("glXDestroyContext");
	isDirect = getStandardFunction<IsDirect>("glXIsDirect");
	queryExtension = getStandardFunction<QueryExtension>("glXQueryExtension");
	queryVersion = getStandardFunction<QueryVersion>("glXQueryVersion");
	swapBuffers = getStandardFunction<SwapBuffers>("glXSwapBuffers");

	// Version 1.1

	queryExtensionsString = getStandardFunction<QueryExtensionsString>("glXQueryExtensionsString");

	// Version 1.3

	chooseFBConfig = getStandardFunction<ChooseFBConfig>("glXChooseFBConfig");
	getFBConfigAttrib = getStandardFunction<GetFBConfigAttrib>("glXGetFBConfigAttrib");
	getVisualFromFBConfig = getStandardFunction<GetVisualFromFBConfig>("glXGetVisualFromFBConfig");
	makeContextCurrent = getStandardFunction<MakeContextCurrent>("glXMakeContextCurrent");

	// Version 1.4

	getProcAddress = getStandardFunction<GLX::GetProcAddress>("glXGetProcAddress");
}

void GLX::checkSupport() const
{
	Uint32 versionMajor = 0u;
	Uint32 versionMinor = 0u;
	const Bool isSupported = X::instance().isGLXSupported(versionMajor, versionMinor);

	if(isSupported)
	{
		if(isVersionLess(versionMajor, versionMinor, ::MIN_SUPPORTED_VERSION_MAJOR,
			::MIN_SUPPORTED_VERSION_MINOR))
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "GLX version " << versionMajor << '.' <<
				versionMinor << " is not supported. The minimum supported version is " <<
				::MIN_SUPPORTED_VERSION_MAJOR << '.' << ::MIN_SUPPORTED_VERSION_MINOR << '.' << Log::Flush();

			DE_ERROR(0x0);
		}
		else
		{
			defaultLog << LogLevel::Info << "Using GLX version " << versionMajor << '.' << versionMinor <<
				'.' << Log::Flush();
		}
	}
	else
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "GLX is not supported." << Log::Flush();
		DE_ERROR_X(0x0);
	}
}

void GLX::initialiseExtensions() const
{
	const ExtensionNameList extensionNames = getExtensionNames();
	logGraphicsExtensions("graphics context", extensionNames);
	checkExtensionsSupport(extensionNames);
	getExtensionFunctions();
}

void GLX::clearFunctions() const
{
	createContextAttribsARB = nullptr;
	getProcAddress = nullptr;
	makeContextCurrent = nullptr;
	getVisualFromFBConfig = nullptr;
	getFBConfigAttrib = nullptr;
	chooseFBConfig = nullptr;
	queryExtensionsString = nullptr;
	swapBuffers = nullptr;
	queryVersion = nullptr;
	queryExtension = nullptr;
	isDirect = nullptr;
	destroyContext = nullptr;
}

void GLX::unloadLibrary() const
{
	const Int32 result = dlclose(_libraryHandle);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to unload the library " <<
			::LIBRARY_FILENAME << ": " << dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
}

ExtensionNameList GLX::getExtensionNames() const
{
	const String8 extensionNamesString(X::instance().getExtensionNameString());
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

void GLX::checkExtensionsSupport(const ExtensionNameList& extensionNames) const
{
	const ExtensionNameSet extensionNameSet(extensionNames.begin(), extensionNames.end());
	GraphicsFunctionUtility::checkExtensionSupport(extensionNameSet, "GLX_ARB_create_context");
}

void GLX::getExtensionFunctions() const
{
	GraphicsFunctionUtility functionUtility;

	// GLX_ARB_create_context

	createContextAttribsARB =
		functionUtility.getExtensionFunction<CreateContextAttribsARB>("glXCreateContextAttribsARB");
}

Void* GLX::getStandardFunctionInternal(const Char8* name) const
{
	Void* functionPointer = dlsym(_libraryHandle, name);

	if(functionPointer == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the address of the function '" <<
			name << "': " << dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}

	return functionPointer;
}
