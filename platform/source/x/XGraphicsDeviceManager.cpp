/**
 * @file platform/x/XGraphicsDeviceManager.cpp
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
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/GraphicsContext.h>
#include <platform/glx/GLX.h>
#include <platform/glx/GLXGraphicsConfigChooser.h>
#include <platform/x/X.h>
#include <platform/x/XWindow.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* WINDOW_DEFAULT_TITLE = "DevEngine Application";

static GLX::FBConfig chooseGraphicsConfig();
static void logGraphicsConfig(GLX::FBConfig configHandle);


// Implementation

class GraphicsDeviceManager::Implementation final
{
public:

	Implementation()
		: _destroyMessageAtom(0u),
		  _graphicsConfigHandle(::chooseGraphicsConfig()),
		  _x(X::instance())
	{
		_destroyMessageAtom = _x.createAtom("WM_DELETE_WINDOW");
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	GraphicsDevice* createDeviceObject(Graphics::Window* window) const
	{
		logGraphicsConfig(_graphicsConfigHandle);
		GraphicsContext* graphicsContext = DE_NEW(GraphicsContext)(window->handle(), _graphicsConfigHandle);

		return DE_NEW(GraphicsDevice)(graphicsContext);
	}

	Graphics::Window* createWindowObject(const Uint32 width, const Uint32 height)
	{
		const ::Window windowHandle = createWindow(width, height);
		Graphics::Window* window = DE_NEW(Graphics::Window)(reinterpret_cast<WindowHandle>(windowHandle));
		_x.setWindowUserData(windowHandle, window->_implementation);

		return window;
	}

	void destroyWindow(Graphics::Window* window) const
	{
		using Graphics::Window;

		const ::Window windowHandle = reinterpret_cast<::Window>(window->handle());
		_x.destroyWindowUserData(windowHandle);
		DE_DELETE(window, Window);
		_x.destroyWindow(windowHandle);
	}

	void processMessages() const
	{
		while(_x.hasPendingEvents())
		{
			const XEvent event = _x.popEvent();

			switch(event.type)
			{
				case ClientMessage:
					if(event.xclient.data.l[0] == _destroyMessageAtom)
						getWindow(event.xclient.window)->close();

					break;

				default:
					break;
			}
		}
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	Atom _destroyMessageAtom;
	GLX _glX;
	GLX::FBConfig _graphicsConfigHandle;
	X& _x;

	::Window createWindow(const Uint32 width, const Uint32 height)
	{
		XVisualInfo* visualInfo = _x.getGraphicsConfigVisualInfo(_graphicsConfigHandle);
		Int32 windowAttributeMask = 0;
		XSetWindowAttributes windowAttributes = createWindowAttributes(windowAttributeMask);

		const ::Window windowHandle =
			_x.createWindow(0, 0, width, height, visualInfo, windowAttributes, windowAttributeMask);

		XFree(visualInfo);
		_x.setWindowMessageProtocols(windowHandle, &_destroyMessageAtom, 1u);
		_x.setWindowTitle(windowHandle, ::WINDOW_DEFAULT_TITLE);

		return windowHandle;
	}

	Graphics::Window::Implementation* getWindow(::Window windowHandle) const
	{
		return static_cast<Graphics::Window::Implementation*>(_x.getWindowUserData(windowHandle));
	}

	XSetWindowAttributes createWindowAttributes(Int32& attributeMask) const
	{
		XSetWindowAttributes attributes;
		attributes.border_pixel = 0u;
		attributeMask = CWBorderPixel | CWColormap;

		return attributes;
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager(WindowCreatedHandler windowCreatedHandler)
	: _implementation(DE_NEW(Implementation)()),
	  _windowCreatedHandler(windowCreatedHandler) { }

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	destroyDevices();
	destroyWindows();
	DE_DELETE(_implementation, Implementation);
}

GraphicsDevice* GraphicsDeviceManager::createDevice(Graphics::Window* window)
{
	GraphicsDevice* device = _implementation->createDeviceObject(window);
	logGraphicsDeviceCreation(device);
	_devices.push_back(device);

	return device;
}

void GraphicsDeviceManager::createWindow(const Uint32 windowWidth, const Uint32 windowHeight)
{
	Graphics::Window* window = _implementation->createWindowObject(windowWidth, windowHeight);
	logWindowCreation(window);
	_windows.push_back(window);
	_windowCreatedHandler(window);
}

void GraphicsDeviceManager::destroyDevice(GraphicsDevice* device)
{
	DE_ASSERT(device != nullptr);
	GraphicsDeviceList::const_iterator iterator = std::find(_devices.begin(), _devices.end(), device);
	DE_ASSERT(iterator != _devices.end());
	_devices.erase(iterator);
	DE_DELETE(device, GraphicsDevice);
}

void GraphicsDeviceManager::destroyWindow(Graphics::Window* window)
{
	DE_ASSERT(window != nullptr);
	WindowList::const_iterator iterator = std::find(_windows.begin(), _windows.end(), window);
	DE_ASSERT(iterator != _windows.end());
	_windows.erase(iterator);
	_implementation->destroyWindow(window);
}

void GraphicsDeviceManager::processWindowMessages() const
{
	_implementation->processMessages();
}

// Private

void GraphicsDeviceManager::destroyWindows()
{
	for(WindowList::const_iterator i = _windows.begin(), end = _windows.end(); i != end; ++i)
		_implementation->destroyWindow(*i);
}


// External

static GLX::FBConfig chooseGraphicsConfig()
{
	GraphicsConfigChooser graphicsConfigChooser;
	return graphicsConfigChooser.chooseConfig();
}

static void logGraphicsConfig(GLX::FBConfig configHandle)
{
	GraphicsConfigChooser graphicsConfigChooser;
	GraphicsConfig config = graphicsConfigChooser.getConfig(configHandle);
	logChosenGraphicsConfig(config);
}
