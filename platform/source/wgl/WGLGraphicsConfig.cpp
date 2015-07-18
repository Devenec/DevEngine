/**
 * @file platform/wgl/WGLGraphicsConfig.cpp
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

#include <utility>
#include <core/Memory.h>
#include <graphics/GraphicsConfig.h>
#include <platform/wgl/WGLGraphicsConfig.h>

using namespace Graphics;

// Implementation

// Public

GraphicsConfig::Impl::Impl()
	: _pixelFormatIndex(0) { }

// Operators

GraphicsConfig::Impl& GraphicsConfig::Impl::operator =(const Impl& impl)
{
	_pixelFormatIndex = impl._pixelFormatIndex;
	return *this;
}


// Graphics::GraphicsConfig

// Public

GraphicsConfig::GraphicsConfig()
	: _impl(DE_NEW(Impl)()) { }

GraphicsConfig::GraphicsConfig(const GraphicsConfig& graphicsConfig)
	: _impl(DE_NEW(Impl)())
{
	*_impl = *graphicsConfig._impl;
}

GraphicsConfig::GraphicsConfig(GraphicsConfig&& graphicsConfig)
	: _impl(graphicsConfig._impl)
{
	graphicsConfig._impl = nullptr;
}

GraphicsConfig::~GraphicsConfig()
{
	DE_DELETE(_impl, Impl);
}

// Operators

GraphicsConfig& GraphicsConfig::operator =(GraphicsConfig graphicsConfig)
{
	std::swap(_impl, graphicsConfig._impl);
	return *this;
}
