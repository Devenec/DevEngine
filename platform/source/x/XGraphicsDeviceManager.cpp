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

#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/LogUtility.h>
#include <graphics/Window.h>
#include <platform/glx/GLX.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class GraphicsDeviceManager::Implementation final
{
public:

	Implementation() = default;

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	Window* createWindowObject(const Uint32 width, const Uint32 height)
	{
		// TODO: implement
		return nullptr;
	}

	void destroyWindowAndDevice(GraphicsDevice* device)
	{
		// TODO: implement
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GLX _glX;
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
	// TODO: implement

	/*Window* window = _implementation->createWindowObject(windowWidth, windowHeight);
	logWindowCreation();
	GraphicsDeviceFactory graphicsDeviceFactory;
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
	// TODO: implement
	//::processMessages();
}
