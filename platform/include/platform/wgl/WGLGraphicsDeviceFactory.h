/**
 * @file platform/wgl/WGLGraphicsDeviceFactory.h
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
	using PixelFormatAttributeList = Core::Array<Int32, 7u>;

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

		static void logDeviceInterfaceExtensions(Graphics::GraphicsDevice* graphicsDevice);

	private:

		using PixelFormatIndexList = Core::Vector<Int32>;

		static const PixelFormatAttributeList PIXEL_FORMAT_ATTRIBUTE_IDS;

		HDC _deviceContextHandle;

		Int32 chooseGraphicsConfig(Graphics::GraphicsConfig& chosenConfig) const;
		Uint32 getPixelFormatCount() const;
		PixelFormatIndexList getPixelFormatIndices(const Uint32 formatCount) const;
		
		Int32 chooseBestPixelFormat(const PixelFormatIndexList& formatIndices,
			PixelFormatAttributeList& formatAttributes) const;

		PixelFormatAttributeList getPixelFormatAttributes(const Int32 formatIndex) const;
	};
}
