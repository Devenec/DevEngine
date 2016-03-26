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

#include <algorithm>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/GraphicsConfigChooser.h>
#include <platform/GraphicsContext.h>
#include <platform/glx/GLX.h>
#include <platform/x/X.h>
#include <platform/x/XWindow.h>

using namespace Graphics;
using namespace Platform;

// External

static const Char8* WINDOW_DEFAULT_TITLE = "DevEngine Application";


// Implementation

class GraphicsDeviceManager::Implementation final
{
public:

	explicit Implementation(WindowCreatedHandler windowCreatedHandler)
		: _graphicsConfigHandle(nullptr),
		  _createMessageAtom(0u),
		  _destroyMessageAtom(0u),
		  _windowCreatedHandler(windowCreatedHandler),
		  _x(X::instance())
	{
		_createMessageAtom = _x.createAtom("DE_CREATE_WINDOW");
		_destroyMessageAtom = _x.createAtom("WM_DELETE_WINDOW");
		chooseGraphicsConfig();
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	GraphicsDevice* createDeviceObject(Graphics::Window* window) const
	{
		logChosenGraphicsConfig(_graphicsConfig);
		GraphicsContext* graphicsContext = DE_NEW(GraphicsContext)(window->handle(), _graphicsConfigHandle);

		return DE_NEW(GraphicsDevice)(graphicsContext);
	}

	Graphics::Window* createWindowObject(const Uint32 width, const Uint32 height)
	{
		const ::Window windowHandle = createWindow(width, height);
		Graphics::Window* window = DE_NEW(Graphics::Window)(reinterpret_cast<WindowHandle>(windowHandle));
		_x.setWindowUserData(windowHandle, window);

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
					processClientMessage(event.xclient);
					break;

				default:
					break;
			}
		}
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GraphicsConfig _graphicsConfig;
	ConfigHandle _graphicsConfigHandle;
	Atom _createMessageAtom;
	Atom _destroyMessageAtom;
	GLX _glX;
	WindowCreatedHandler _windowCreatedHandler;
	X& _x;

	void chooseGraphicsConfig()
	{
		GraphicsConfigChooser configChooser(nullptr);
		_graphicsConfigHandle = configChooser.chooseConfig(_graphicsConfig);
	}

	::Window createWindow(const Uint32 width, const Uint32 height)
	{
		XVisualInfo* visualInfo =
			_x.getGraphicsConfigVisualInfo(static_cast<GLX::FBConfig>(_graphicsConfigHandle));

		Uint32 windowAttributeMask = 0u;
		XSetWindowAttributes windowAttributes = createWindowAttributes(windowAttributeMask);

		const ::Window windowHandle =
			_x.createWindow(0, 0, width, height, visualInfo, windowAttributes, windowAttributeMask);

		XFree(visualInfo);
		_x.setWindowMessageProtocols(windowHandle, &_destroyMessageAtom, 1u);
		_x.setWindowTitle(windowHandle, ::WINDOW_DEFAULT_TITLE);
		sendWindowCreationEvent(windowHandle);

		return windowHandle;
	}

	void processClientMessage(const XClientMessageEvent& event) const
	{
		if(event.message_type == _createMessageAtom)
			_windowCreatedHandler(getWindow(event.window));
		else if(static_cast<Atom>(event.data.l[0]) == _destroyMessageAtom)
			getWindow(event.window)->_implementation->close();
	}

	Graphics::Window* getWindow(::Window windowHandle) const
	{
		return static_cast<Graphics::Window*>(_x.getWindowUserData(windowHandle));
	}

	XSetWindowAttributes createWindowAttributes(Uint32& attributeMask) const
	{
		XSetWindowAttributes attributes;
		attributes.border_pixel = 0u;
		attributeMask = CWBorderPixel;

		return attributes;
	}

	void sendWindowCreationEvent(::Window windowHandle) const
	{
		XEvent event = XEvent();
		event.type = ClientMessage;
		event.xclient.format = 32;
		event.xclient.message_type = _createMessageAtom;
		event.xclient.window = windowHandle;
		_x.sendEvent(windowHandle, event, NoEventMask);
	}
};


// Graphics::GraphicsDeviceManager

// Public

GraphicsDeviceManager::GraphicsDeviceManager(WindowCreatedHandler windowCreatedHandler)
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)(windowCreatedHandler);
}

GraphicsDeviceManager::~GraphicsDeviceManager()
{
	destroyDevices();
	destroyWindows();
	DE_DELETE(_implementation, Implementation);
}

GraphicsDevice* GraphicsDeviceManager::createDevice(Graphics::Window* window)
{
	if(_devices.size() > 0u)
		return _devices.front();

	GraphicsDevice* device = _implementation->createDeviceObject(window);
	logGraphicsDeviceCreation(device);
	_devices.push_back(device);

	return device;
}

void GraphicsDeviceManager::createWindow(const Uint32 windowWidth, const Uint32 windowHeight)
{
	if(!_windows.empty())
		return;

	Graphics::Window* window = _implementation->createWindowObject(windowWidth, windowHeight);
	logWindowCreation(window);
	_windows.push_back(window);
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
