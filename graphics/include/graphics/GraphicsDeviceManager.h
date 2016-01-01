/**
 * @file graphics/GraphicsDeviceManager.h
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

#pragma once

#include <functional>
#include <core/List.h>
#include <core/Singleton.h>
#include <core/Types.h>

namespace Graphics
{
	class GraphicsDevice;
	class Window;

	class GraphicsDeviceManager final : public Core::Singleton<GraphicsDeviceManager>
	{
	public:

		using WindowCreatedHandler = std::function<void(Window*)>;

		GraphicsDeviceManager(WindowCreatedHandler windowCreatedHandler);

		GraphicsDeviceManager(const GraphicsDeviceManager& graphicsDeviceManager) = delete;
		GraphicsDeviceManager(GraphicsDeviceManager&& graphicsDeviceManager) = delete;

		~GraphicsDeviceManager();

		GraphicsDevice* createDevice(Window* window);

		void createWindow(const Uint32 windowWidth, const Uint32 windowHeight);

		void destroyDevice(GraphicsDevice* device);

		void destroyWindow(Window* window);

		void processWindowMessages() const;

		GraphicsDeviceManager& operator =(const GraphicsDeviceManager& graphicsDeviceManager) = delete;
		GraphicsDeviceManager& operator =(GraphicsDeviceManager&& graphicsDeviceManager) = delete;

	private:

		class Implementation;

		using GraphicsDeviceList = Core::List<GraphicsDevice*>;
		using WindowList		 = Core::List<Window*>;

		GraphicsDeviceList _devices;
		WindowList _windows;
		Implementation* _implementation;
		WindowCreatedHandler _windowCreatedHandler;

		void destroyDevices();
		void destroyWindows();
	};
}
