/**
 * @file graphics/GraphicsResource.h
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

#include <core/Types.h>

namespace Graphics
{
	using GraphicsInterface = Void*;

	class GraphicsResource
	{
	public:

		GraphicsResource(const GraphicsResource& graphicsResource) = delete;
		GraphicsResource(GraphicsResource&& graphicsResource) = delete;

		GraphicsResource& operator =(const GraphicsResource& graphicsResource) = delete;
		GraphicsResource& operator =(GraphicsResource&& graphicsResource) = delete;

	protected:

		GraphicsResource() = default;

		virtual ~GraphicsResource() = default;

	private:

		friend class GraphicsDevice;
	};
}
