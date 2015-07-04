/**
 * @file graphics/GraphicsDevice.h
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

namespace Graphics
{
	class Colour;
	class Viewport;

	class GraphicsDevice final
	{
	public:

		GraphicsDevice();

		GraphicsDevice(const GraphicsDevice& graphicsDevice) = delete;
		GraphicsDevice(GraphicsDevice&& graphicsDevice) = delete;

		~GraphicsDevice();

		void clear(const Colour& colour) const;

		void setViewport(const Viewport& viewport);

		const Viewport& viewport() const;

		GraphicsDevice& operator =(const GraphicsDevice& graphicsDevice) = delete;
		GraphicsDevice& operator =(GraphicsDevice&& graphicsDevice) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
