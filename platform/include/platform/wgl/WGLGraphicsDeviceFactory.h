/**
 * @file platform/wgl/WGLGraphicsDeviceFactory.h
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

#pragma once

#include <core/Array.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <platform/windows/WindowsGraphics.h>

namespace Graphics
{
	class GraphicsConfig;
	class GraphicsDevice;
	class Window;
}

namespace Platform
{
	class GraphicsContext;

	using GraphicsConfigAttributeList = Core::Array<Int32, 7u>;

	class GraphicsDeviceFactory final
	{
	public:

		GraphicsDeviceFactory();

		GraphicsDeviceFactory(const GraphicsDeviceFactory& graphicsDeviceFactory) = delete;
		GraphicsDeviceFactory(GraphicsDeviceFactory&& graphicsDeviceFactory) = delete;

		~GraphicsDeviceFactory() = default;

		Graphics::GraphicsDevice* createDevice(Graphics::Window* window,
			Graphics::GraphicsConfig& chosenGraphicsConfig);

		GraphicsDeviceFactory& operator =(const GraphicsDeviceFactory& graphicsDeviceFactory) = delete;
		GraphicsDeviceFactory& operator =(GraphicsDeviceFactory&& graphicsDeviceFactory) = delete;

		static void logDeviceInfo(Graphics::GraphicsDevice* graphicsDevice);

	private:

		using GraphicsConfigIndexList = Core::Vector<Int32>;

		static const GraphicsConfigAttributeList GRAPHICS_CONFIG_ATTRIBUTE_IDS;

		HDC _deviceContextHandle;

		Int32 chooseGraphicsConfig(Graphics::GraphicsConfig& chosenConfig) const;
		GraphicsContext* createGraphicsContext(HWND windowHandle, const Int32 graphicsConfigIndex) const;
		Graphics::GraphicsDevice* createDeviceObject(GraphicsContext* graphicsContext) const;
		Uint32 getGraphicsConfigCount() const;
		GraphicsConfigIndexList getGraphicsConfigIndices(const Uint32 configCount) const;

		Int32 chooseBestGraphicsConfig(const GraphicsConfigIndexList& configIndices,
			GraphicsConfigAttributeList& configAttributes) const;

		GraphicsConfigAttributeList getGraphicsConfigAttributes(const Int32 configIndex) const;
	};
}
