/**
 * @file platform/wgl/WGLGraphicsDeviceManager.cpp
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

#include <algorithm>
#include <core/List.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsContext.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsConfigChooser.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>
#include <platform/windows/WindowsGraphics.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static void initialiseWGL(Window* window);


// Implementation

class GraphicsDeviceManager::Impl final
{
public:

	Impl()
	{
		const WindowManager& windowManager = WindowManager::instance();
		Window* temporaryWindow = windowManager.createWindow();
		::initialiseWGL(temporaryWindow);
		windowManager.destroyWindow(temporaryWindow);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		for(GraphicsDeviceList::const_iterator i = _devices.begin(), end = _devices.end(); i != end; ++i)
			DE_DELETE(*i, GraphicsDevice);
	}

	GraphicsDevice* createDevice(Window* window)
	{
		GraphicsContext* graphicsContext = createGraphicsContext(window);
		GraphicsDevice* device = DE_NEW(GraphicsDevice)(graphicsContext);
		_devices.push_back(device);

		return device;
	}

	void destroyDevice(GraphicsDevice* device)
	{
		DE_ASSERT(device != nullptr);
		GraphicsDeviceList::const_iterator iterator = std::find(_devices.begin(), _devices.end(), device);
		DE_ASSERT(iterator != _devices.end());
		_devices.erase(iterator);
		DE_DELETE(device, GraphicsDevice);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	using GraphicsDeviceList = List<GraphicsDevice*>;

	GraphicsDeviceList _devices;

	GraphicsContext* createGraphicsContext(Window* window) const
	{
		const GraphicsConfig graphicsConfig = chooseGraphicsConfig(window);
		GraphicsContext* graphicsContext = DE_NEW(GraphicsContext)(window, graphicsConfig);
		logGraphicsContextConfiguration(graphicsConfig);

		return graphicsContext;
	}

	GraphicsConfig chooseGraphicsConfig(Window* window) const
	{
		HDC deviceContextHandle = GraphicsContextBase::getWindowDeviceContext(static_cast<HWND>(window->handle()));
		GraphicsConfigChooser graphicsConfigChooser(deviceContextHandle);
		return graphicsConfigChooser.chooseConfig();
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager()
	: _impl(DE_NEW(Impl)()) { }

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	DE_DELETE(_impl, Impl);
}

GraphicsDevice* GraphicsDeviceManager::createDevice(Window* window) const
{
	return _impl->createDevice(window);
}

void GraphicsDeviceManager::destroyDevice(GraphicsDevice* device) const
{
	_impl->destroyDevice(device);
}


// External

static void initialiseWGL(Window* window)
{
	TemporaryGraphicsContext temporaryGraphicsContext(static_cast<HWND>(window->handle()));
	WGL::initialise(temporaryGraphicsContext);
}
