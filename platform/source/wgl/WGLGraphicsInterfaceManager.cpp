/**
 * @file platform/wgl/WGLGraphicsInterfaceManager.cpp
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

#include <core/Memory.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>
#include <platform/windows/WindowsGraphicsInterfaceManager.h>

using namespace Platform;

// Implementation

class GraphicsInterfaceManager::Implementation final
{
public:

	Implementation() = default;

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	void initialiseInterface(HWND temporaryWindowHandle) const
	{
		TemporaryGraphicsContext temporaryGraphicsContext(temporaryWindowHandle);
		_wgl.initialise(temporaryGraphicsContext);
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	WGL _wgl;
};


// Platform::GraphicsInterfaceManager

// Public

GraphicsInterfaceManager::GraphicsInterfaceManager()
	: _implementation(DE_NEW(Implementation)()) { }

GraphicsInterfaceManager::~GraphicsInterfaceManager()
{
	DE_DELETE(_implementation, Implementation);
}

void GraphicsInterfaceManager::initialiseInterface(HWND temporaryWindowHandle) const
{
	_implementation->initialiseInterface(temporaryWindowHandle);
}

Bool GraphicsInterfaceManager::interfaceRequiresInitialisation() const
{
	return true;
}
