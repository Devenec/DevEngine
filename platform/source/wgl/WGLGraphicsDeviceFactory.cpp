/**
 * @file platform/wgl/WGLGraphicsDeviceFactory.cpp
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
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/GraphicsContext.h>
#include <platform/wgl/WGLGraphicsConfigChooser.h>
#include <platform/wgl/WGLGraphicsDeviceFactory.h>
#include <platform/windows/Windows.h>

using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsDeviceFactory - WGL] ";


// Public

GraphicsDevice* GraphicsDeviceFactory::createDevice(Window* window)
{
	HDC deviceContextHandle = getWindowDeviceContextHandle(static_cast<HWND>(window->handle()));
	const Int32 graphicsConfigIndex = chooseGraphicsConfig(deviceContextHandle);

	GraphicsContext* graphicsContext =
		DE_NEW(GraphicsContext)(window->handle(), reinterpret_cast<ConfigHandle>(graphicsConfigIndex));

	return DE_NEW(GraphicsDevice)(graphicsContext);
}

// Private

Int32 GraphicsDeviceFactory::chooseGraphicsConfig(HDC deviceContextHandle) const
{
	GraphicsConfigChooser configChooser(deviceContextHandle);
	GraphicsConfig chosenConfig;
	const Int32 chosenConfigIndex = configChooser.chooseConfig(chosenConfig);
	logChosenGraphicsConfig(chosenConfig);

	return chosenConfigIndex;
}
