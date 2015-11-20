/**
 * @file graphics/GraphicsDeviceManager.cpp
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

#include <core/Log.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDeviceManager.h>

using namespace Core;
using namespace Graphics;

// Some members are defined in platform/*/*GraphicsDeviceManager.cpp

// Graphics

void Graphics::logGraphicsDeviceConfiguration(const GraphicsConfig& config)
{
	defaultLog << LogLevel::Info << "Created graphics device with configuration:\n\nColour buffer (RGBA): " <<
		config.redDepth() << ' ' << config.greenDepth() << ' ' << config.blueDepth() << ' ' << config.alphaDepth() <<
		" bits\nDepth buffer:         " << config.depthBufferDepth() << " bits\nStencil buffer:       " <<
		config.stencilBufferDepth() << " bits\n" << Log::Flush();
}
