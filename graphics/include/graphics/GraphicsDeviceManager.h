/**
 * @file graphics/GraphicsDeviceManager.h
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

#pragma once

#include <core/Singleton.h>

namespace Graphics
{
	class GraphicsConfig;
	class GraphicsDevice;
	class Window;

	class GraphicsDeviceManager final : public Core::Singleton<GraphicsDeviceManager>
	{
	public:

		GraphicsDeviceManager();

		GraphicsDeviceManager(const GraphicsDeviceManager& graphicsDeviceManager) = delete;
		GraphicsDeviceManager(GraphicsDeviceManager&& graphicsDeviceManager) = delete;

		~GraphicsDeviceManager();

		GraphicsDevice* createDevice(Window* window) const;

		void destroyDevice(GraphicsDevice* device) const;

		GraphicsDeviceManager& operator =(const GraphicsDeviceManager& graphicsDeviceManager) = delete;
		GraphicsDeviceManager& operator =(GraphicsDeviceManager&& graphicsDeviceManager) = delete;

	private:

		class Impl;

		Impl* _impl;
	};

	void logGraphicsContextConfiguration(const GraphicsConfig& config);
}
