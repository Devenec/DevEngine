/**
 * @file graphics/GraphicsConfig.h
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

#include <core/Types.h>

namespace Graphics
{
	class GraphicsConfig final
	{
	public:

		GraphicsConfig();

		GraphicsConfig(const Uint32 redDepth, const Uint32 greenDepth, const Uint32 blueDepth,
			const Uint32 alphaDepth, const Uint32 depthBufferDepth, const Uint32 stencilBufferDepth);

		GraphicsConfig(const GraphicsConfig& graphicsConfig) = default;
		GraphicsConfig(GraphicsConfig&& graphicsConfig) = default;

		~GraphicsConfig() = default;

		inline Uint32 alphaDepth() const;

		inline Uint32 blueDepth() const;

		inline Uint32 depthBufferDepth() const;

		inline Uint32 greenDepth() const;

		inline Uint32 redDepth() const;

		inline Uint32 stencilBufferDepth() const;

		GraphicsConfig& operator =(const GraphicsConfig& graphicsConfig) = default;
		GraphicsConfig& operator =(GraphicsConfig&& graphicsConfig) = default;

	private:

		Uint8 _alphaDepth;
		Uint8 _blueDepth;
		Uint8 _depthDepth;
		Uint8 _greenDepth;
		Uint8 _redDepth;
		Uint8 _stencilDepth;
	};

#include "inline/GraphicsConfig.inl"
}
