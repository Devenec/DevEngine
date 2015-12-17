/**
 * @file platform/glx/GLX.cpp
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

#include <dlfcn.h>
#include <core/Error.h>
#include <core/Log.h>
#include <platform/GraphicsExtensionHelper.h>
#include <platform/Utility.h>
#include <platform/glx/GLX.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG				   = "[Platform::GLX]";
static const Char8* LIBRARY_FILENAME			   = "libGL.so";
static const Int32 MIN_SUPPORTED_GLX_VERSION_MAJOR = 1;
static const Int32 MIN_SUPPORTED_GLX_VERSION_MINOR = 4;


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

// GLX_EXT_swap_control

GLX::SwapIntervalEXT GLX::swapIntervalEXT = nullptr;

GLX::GLX()
	: _libraryHandle(nullptr)
{
	loadLibrary();
	loadStandardFunctions();
	checkSupport();
	getExtensionFunctions();
	checkExtensions();
	logGraphicsExtensions("graphics context", getExtensionNames());
}

GLX::~GLX()
{
	unloadFunctions();
	//unloadLibrary(); // TODO: unloading the library causes XCloseDisplay() to crash at X.cpp, find out why
}

// Private

void GLX::loadLibrary()
{
	_libraryHandle = dlopen(::LIBRARY_FILENAME, RTLD_LAZY);

	if(_libraryHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to load " << ::LIBRARY_FILENAME << ": " <<
			dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
}

void GLX::loadStandardFunctions() const
{
	// Version 1.0

	destroyContext = loadFunction<DestroyContext>("glXDestroyContext");
	isDirect = loadFunction<IsDirect>("glXIsDirect");
	queryExtension = loadFunction<QueryExtension>("glXQueryExtension");
	queryVersion = loadFunction<QueryVersion>("glXQueryVersion");
	swapBuffers = loadFunction<SwapBuffers>("glXSwapBuffers");

	// Version 1.1

	queryExtensionsString = loadFunction<QueryExtensionsString>("glXQueryExtensionsString");

	// Version 1.3

	chooseFBConfig = loadFunction<ChooseFBConfig>("glXChooseFBConfig");
	getFBConfigAttrib = loadFunction<GetFBConfigAttrib>("glXGetFBConfigAttrib");
	getVisualFromFBConfig = loadFunction<GetVisualFromFBConfig>("glXGetVisualFromFBConfig");
	makeContextCurrent = loadFunction<MakeContextCurrent>("glXMakeContextCurrent");

	// Version 1.4

	getProcAddress = loadFunction<GLX::GetProcAddress>("glXGetProcAddress");
}

void GLX::checkSupport() const
{
	Display* xConnection = X::instance().connection();
	const Int32 result = queryExtension(xConnection, nullptr, nullptr);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " GLX is not supported." << Log::Flush();
		DE_ERROR_X(0x0);
	}
	else
	{
		Int32 versionMajor = 0;
		Int32 versionMinor = 0;
		queryVersion(xConnection, &versionMajor, &versionMinor);

		if(isVersionLess(versionMajor, versionMinor, MIN_SUPPORTED_GLX_VERSION_MAJOR, MIN_SUPPORTED_GLX_VERSION_MINOR))
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " GLX version " << versionMajor << '.' << versionMinor <<
				" is not supported. The minimum supported version is " << MIN_SUPPORTED_GLX_VERSION_MAJOR << '.' <<
				MIN_SUPPORTED_GLX_VERSION_MINOR << '.' << Log::Flush();

			DE_ERROR(0x0);
		}
		else
		{
			defaultLog << LogLevel::Info << "Using GLX version " << versionMajor << '.' << versionMinor << '.' <<
				Log::Flush();
		}
	}
}

void GLX::getExtensionFunctions() const
{
	// GLX_ARB_create_context

	createContextAttribsARB =
		GraphicsExtensionHelper::getFunction<CreateContextAttribsARB>("glXCreateContextAttribsARB");

	// GLX_EXT_swap_control

	swapIntervalEXT = GraphicsExtensionHelper::getFunction<SwapIntervalEXT>("glXSwapIntervalEXT");
}

void GLX::checkExtensions() const
{
	// TODO: implement
}

ExtensionNameList GLX::getExtensionNames() const
{
	Display* xConnection = X::instance().connection();
	const Int32 screen = XDefaultScreen(xConnection);
	const String8 extensionNamesString(queryExtensionsString(xConnection, screen));
	ExtensionNameList extensionNames;

	if(extensionNamesString.length() != 0u)
	{
		Uint32 currentPosition = 0u;
		Uint32 spacePosition;

		while((spacePosition = extensionNamesString.find(' ', currentPosition)) != String8::npos)
		{
			extensionNames.push_back(extensionNamesString.substr(currentPosition, spacePosition - currentPosition));
			currentPosition = spacePosition + 1u;
		}
	}

	return extensionNames;
}

void GLX::unloadFunctions() const
{
	destroyContext = nullptr;
	isDirect = nullptr;
	queryExtension = nullptr;
	queryVersion = nullptr;
	swapBuffers = nullptr;
	queryExtensionsString = nullptr;
	chooseFBConfig = nullptr;
	getFBConfigAttrib = nullptr;
	getVisualFromFBConfig = nullptr;
	makeContextCurrent = nullptr;
	getProcAddress = nullptr;
	createContextAttribsARB = nullptr;
	swapIntervalEXT = nullptr;
}

void GLX::unloadLibrary() const
{
	const Int32 result = dlclose(_libraryHandle);

	if(result != 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to unload " << ::LIBRARY_FILENAME << ": " <<
			dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
}

Void* GLX::loadFunctionInternal(const Char8* name) const
{
	Void* functionPointer = dlsym(_libraryHandle, name);

	if(functionPointer == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to load a standard function '" << name << "': " <<
			dlerror() << '.' << Log::Flush();

		DE_ERROR(0x0);
	}

	return functionPointer;
}


// Platform::GraphicsExtensionHelper

// Private

// Static

GraphicsExtensionHelper::Function GraphicsExtensionHelper::getFunctionInternal(const Char8* name)
{
	return GLX::getProcAddress(reinterpret_cast<const Uint8*>(name));
}
