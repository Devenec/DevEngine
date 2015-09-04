/**
 * @file graphics/GraphicsContextManager.h
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

namespace Graphics
{
	class GraphicsConfig;
	class GraphicsContext;
	class Window;

	class GraphicsContextManager final : public Core::Singleton<GraphicsContextManager>
	{
	public:

		GraphicsContextManager();

		GraphicsContextManager(const GraphicsContextManager& graphicsContextManager) = delete;
		GraphicsContextManager(GraphicsContextManager&& graphicsContextManager) = delete;

		~GraphicsContextManager();

		GraphicsContext* createGraphicsContext(Window* window) const;

		void destroyGraphicsContext(GraphicsContext* graphicsContext) const;

		GraphicsContextManager& operator =(const GraphicsContextManager& graphicsContextManager) = delete;
		GraphicsContextManager& operator =(GraphicsContextManager&& graphicsContextManager) = delete;

	private:

		class Impl;

		Impl* _impl;
	};

	void logGraphicsContextConfiguration(const GraphicsConfig& config);
}
