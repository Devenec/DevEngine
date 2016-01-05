/**
 * @file platform/wgl/WGLGraphicsFunctionUtility.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/UtilityMacros.h>
#include <platform/GraphicsFunctionUtility.h>
#include <platform/wgl/WGL.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG	  = "[Platform::GraphicsFunctionUtility - WGL] ";
static const Char16* LIBRARY_FILENAME = DE_CHAR16("OpenGL32.dll");


// Implementation

class GraphicsFunctionUtility::Implementation final
{
public:

	Implementation()
		: _libraryHandle(GetModuleHandleW(::LIBRARY_FILENAME))
	{
		if(_libraryHandle == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the library handle to " <<
				::LIBRARY_FILENAME << '.';

			DE_ERROR_WINDOWS(0x0);
		}
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	Function getFunction(const Char8* name) const
	{
		Function function = reinterpret_cast<Function>(GetProcAddress(_libraryHandle, name));

		if(function == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
				"Failed to get the address of the function " << name << '.';

			DE_ERROR_WINDOWS(0x0);
		}

		return function;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	HMODULE _libraryHandle;
};


// Platform::GraphicsFunctionUtility

// Public

GraphicsFunctionUtility::GraphicsFunctionUtility()
	: _implementation(DE_NEW(Implementation)()) { }

GraphicsFunctionUtility::~GraphicsFunctionUtility()
{
	DE_DELETE(_implementation, Implementation);
}

// Private

GraphicsFunctionUtility::Function GraphicsFunctionUtility::getExtensionFunctionInternal(const Char8* name)
	const
{
	return reinterpret_cast<Function>(WGL::getProcAddress(name));
}

GraphicsFunctionUtility::Function GraphicsFunctionUtility::getStandardFunctionInternal(const Char8* name)
	const
{
	return _implementation->getFunction(name);
}
