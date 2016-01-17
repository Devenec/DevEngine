/**
 * @file graphics/GraphicsBuffer.h
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
#include <graphics/GraphicsResource.h>

namespace Graphics
{
	enum class AccessMode;
	enum class BufferBinding;
	enum class BufferUsage;

	class GraphicsBuffer : public GraphicsResource
	{
	public:

		GraphicsBuffer(const GraphicsBuffer& graphicsBuffer) = delete;
		GraphicsBuffer(GraphicsBuffer&& graphicsBuffer) = delete;

		void demapData() const;

		Uint8* mapData() const;

		Uint8* mapData(const Uint size, const Uint offset = 0u) const;

		GraphicsBuffer& operator =(const GraphicsBuffer& graphicsBuffer) = delete;
		GraphicsBuffer& operator =(GraphicsBuffer&& graphicsBuffer) = delete;

	protected:

		class Implementation;

		Implementation* _implementation;

		GraphicsBuffer(GraphicsInterfaceHandle graphicsInterfaceHandle, const BufferBinding& binding,
			const Uint size, const AccessMode& accessMode, const BufferUsage& usage);

		virtual ~GraphicsBuffer();

	private:

		friend class GraphicsDevice;
		friend class VertexBufferState;
	};
}
