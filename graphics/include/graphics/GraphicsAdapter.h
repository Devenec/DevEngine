/**
 * @file graphics/GraphicsAdapter.h
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

#include <core/String.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Graphics
{
	class DisplayMode;

	using DisplayModeList = Core::Vector<DisplayMode>;

	class GraphicsAdapter final
	{
	public:

		GraphicsAdapter(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter(GraphicsAdapter&& graphicsAdapter) = delete;

		const DisplayMode& currentDisplayMode() const;

		Core::String8 name() const;

		void setDisplayMode(const DisplayMode& mode) const;

		const DisplayModeList& supportedDisplayModes() const;

		GraphicsAdapter& operator =(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter& operator =(GraphicsAdapter&& graphicsAdapter) = delete;

	private:

		friend class GraphicsAdapterManager;

		class Impl;
		
		Impl* _impl;

		GraphicsAdapter(const Core::String8& name, const DisplayModeList& supportedDisplayModes,
			const Uint32 currentDisplayModeIndex);

		~GraphicsAdapter();
	};
}
