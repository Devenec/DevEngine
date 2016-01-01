/**
 * @file graphics/GraphicsConfig.cpp
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

#include <graphics/GraphicsConfig.h>

using namespace Graphics;

// Public

GraphicsConfig::GraphicsConfig()
	: GraphicsConfig(0u, 0u, 0u, 0u, 0u, 0u) { }

GraphicsConfig::GraphicsConfig(const Uint32 redDepth, const Uint32 greenDepth, const Uint32 blueDepth,
	const Uint32 alphaDepth, const Uint32 depthBufferDepth, const Uint32 stencilBufferDepth)
	: _alphaDepth(static_cast<Uint8>(alphaDepth)),
	  _blueDepth(static_cast<Uint8>(blueDepth)),
	  _depthDepth(static_cast<Uint8>(depthBufferDepth)),
	  _greenDepth(static_cast<Uint8>(greenDepth)),
	  _redDepth(static_cast<Uint8>(redDepth)),
	  _stencilDepth(static_cast<Uint8>(stencilBufferDepth)) { }
