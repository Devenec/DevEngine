/**
 * @file platform/x/XGraphicsDeviceManager.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/glx/GLX.h>
#include <platform/glx/GLXGraphicsConfigChooser.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static GLXFBConfig chooseGraphicsConfig(GraphicsConfig& chosenConfig);


// Implementation

class GraphicsDeviceManager::Implementation final
{
public:

	Implementation()
		: _x(X::instance()) { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	Graphics::Window* createWindowObject(const Uint32 width, const Uint32 height) const
	{
		::Window windowHandle = createWindow(width, height);
		return DE_NEW(Graphics::Window)(reinterpret_cast<WindowHandle>(windowHandle));
	}

	void destroyWindowAndDevice(GraphicsDevice* device) const
	{
		using Graphics::Window;

		//Window* window = device->window();
		//DE_DELETE(device, GraphicsDevice);
		//::Window windowHandle = reinterpret_cast<::Window>(window->handle());
		//DE_DELETE(window, Window);
		//_x.destroyWindow(windowHandle);
	}

	void processMessages() const
	{
		while(_x.hasPendingEvents())
		{
			XEvent event = _x.popEvent();

			switch(event.type)
			{
				case ClientMessage:
					// TODO: implement
					//if(event.xclient.data.l[0] == deleteMessageAtom)

					break;

				case MapNotify:
					// TODO: implement
					break;

				default:
					break;
			}
		}
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GLX _glX;
	X& _x;

	::Window createWindow(const Uint32 width, const Uint32 height) const
	{
		GraphicsConfig chosenGraphicsConfig;
		GLXFBConfig graphicsConfigHandle = ::chooseGraphicsConfig(chosenGraphicsConfig);
		XVisualInfo* visualInfo = _x.getGraphicsConfigVisualInfo(graphicsConfigHandle);
		::Window rootWindowHandle = _x.getRootWindowHandle(visualInfo->screen);
		Int32 windowAttributeMask = 0;

		XSetWindowAttributes windowAttributes = createWindowAttributes(windowAttributeMask);

		::Window windowHandle = _x.createWindow(rootWindowHandle, 0, 0, width, height, visualInfo, windowAttributes,
			windowAttributeMask);

		XFree(visualInfo);
		return windowHandle;
	}

	XSetWindowAttributes createWindowAttributes(Int32& attributeMask) const
	{
		XSetWindowAttributes attributes;
		attributes.border_pixel = 0u;
		attributes.event_mask = StructureNotifyMask;
		attributeMask = CWBorderPixel | CWColormap | CWEventMask;

		return attributes;
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager()
	: _implementation(DE_NEW(Implementation)()) { }

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	for(GraphicsDeviceList::const_iterator i = _devices.begin(), end = _devices.end(); i != end; ++i)
		_implementation->destroyWindowAndDevice(*i);

	DE_DELETE(_implementation, Implementation);
}

GraphicsDevice* GraphicsDeviceManager::createWindowAndDevice(const Uint32 windowWidth, const Uint32 windowHeight)
{
	//Graphics::Window* window = _implementation->createWindowObject(windowWidth, windowHeight);
	//logWindowCreation();
	/*GraphicsDeviceFactory graphicsDeviceFactory;
	GraphicsConfig graphicsConfig;
	GraphicsDevice* device = graphicsDeviceFactory.createDevice(window, graphicsConfig);
	_devices.push_back(device);
	logChosenGraphicsConfig(graphicsConfig);
	logGraphicsDeviceCreation(device);
	GraphicsDeviceFactory::logDeviceInfo(device);*/

	return nullptr;
}

void GraphicsDeviceManager::destroyWindowAndDevice(GraphicsDevice* device)
{
	DE_ASSERT(device != nullptr);
	GraphicsDeviceList::const_iterator iterator = std::find(_devices.begin(), _devices.end(), device);
	DE_ASSERT(iterator != _devices.end());
	_devices.erase(iterator);
	_implementation->destroyWindowAndDevice(device);
}

void GraphicsDeviceManager::processWindowMessages() const
{
	_implementation->processMessages();
}


// External

static GLXFBConfig chooseGraphicsConfig(GraphicsConfig& chosenConfig)
{
	GraphicsConfigChooser graphicsConfigChooser;
	return graphicsConfigChooser.chooseConfig(chosenConfig);
}
