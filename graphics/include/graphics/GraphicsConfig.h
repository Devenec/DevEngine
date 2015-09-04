/**
 * @file graphics/GraphicsConfig.h
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

#include <core/Types.h>

namespace Platform
{
	class GraphicsConfigChooser;
}

namespace Graphics
{
	class GraphicsConfig final
	{
	public:

		GraphicsConfig();

		GraphicsConfig(const Uint32 redDepth, const Uint32 greenDepth, const Uint32 blueDepth, const Uint32 alphaDepth,
			const Uint32 depthBufferDepth, const Uint32 stencilBufferDepth);

		GraphicsConfig(const GraphicsConfig& graphicsConfig);

		GraphicsConfig(GraphicsConfig&& graphicsConfig);

		~GraphicsConfig();

		inline Uint32 alphaDepth() const;

		inline Uint32 blueDepth() const;

		inline Uint32 depthBufferDepth() const;

		inline Uint32 greenDepth() const;

		inline Uint32 redDepth() const;

		inline Uint32 stencilBufferDepth() const;

		GraphicsConfig& operator =(GraphicsConfig graphicsConfig);

	private:

		friend class GraphicsContext;
		friend class Platform::GraphicsConfigChooser;

		class Impl;

		Impl* _impl;
		Uint8 _alphaDepth;
		Uint8 _blueDepth;
		Uint8 _depthDepth;
		Uint8 _greenDepth;
		Uint8 _redDepth;
		Uint8 _stencilDepth;
	};

#include "inline/GraphicsConfig.inl"
}
