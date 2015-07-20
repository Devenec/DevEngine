/**
 * @file graphics/GraphicsAdapterManager.h
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

#include <core/Singleton.h>
#include <core/Vector.h>

namespace Graphics
{
	class DisplayMode;
	class GraphicsAdapter;

	using GraphicsAdapterList = Core::Vector<GraphicsAdapter*>;

	class GraphicsAdapterManager final : public Core::Singleton<GraphicsAdapterManager>
	{
	public:

		GraphicsAdapterManager();

		GraphicsAdapterManager(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager(GraphicsAdapterManager&& graphicsAdapterManager) = delete;

		~GraphicsAdapterManager();

		const GraphicsAdapterList& graphicsAdapters() const;

		GraphicsAdapterManager& operator =(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager& operator =(GraphicsAdapterManager&& graphicsAdapterManager) = delete;

	private:

		class Impl;

		Impl* _impl;

		void logAdapters() const;

		static void logAdapterDisplayModes(const GraphicsAdapter& graphicsAdapter);
		static void logAdapterDisplayMode(const DisplayMode& displayMode, const Bool insertSeparator);
	};
}
