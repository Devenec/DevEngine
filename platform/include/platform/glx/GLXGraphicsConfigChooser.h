/**
 * @file platform/glx/GLXGraphicsConfigChooser.h
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
#include <platform/glx/GLX.h>
#include <platform/x/X.h>

namespace Graphics
{
	class GraphicsConfig;
}

namespace Platform
{
	using ConfigAttributeList = Core::Array<Int32, 6u>;

	class GraphicsConfigChooser final
	{
	public:

		GraphicsConfigChooser();

		GraphicsConfigChooser(const GraphicsConfigChooser& graphicsConfigChooser) = delete;
		GraphicsConfigChooser(GraphicsConfigChooser&& graphicsConfigChooser) = delete;

		~GraphicsConfigChooser() = default;

		GLX::FBConfig chooseConfig() const;

		Graphics::GraphicsConfig getConfig(GLX::FBConfig configHandle) const;

		GraphicsConfigChooser& operator =(const GraphicsConfigChooser& graphicsConfigChooser) = delete;
		GraphicsConfigChooser& operator =(GraphicsConfigChooser&& graphicsConfigChooser) = delete;

	private:

		using ConfigIndexList = Core::Vector<Int32>;

		static const ConfigAttributeList CONFIG_ATTRIBUTE_IDS;

		X& _x;

		GLX::FBConfig* getConfigs(Uint32& configCount) const;

		GLX::FBConfig chooseBestConfig(GLX::FBConfig* configHandles, const Uint32 configCount,
			ConfigAttributeList& configAttributes) const;

		ConfigAttributeList getConfigAttributes(GLX::FBConfig configHandle) const;
	};
}
