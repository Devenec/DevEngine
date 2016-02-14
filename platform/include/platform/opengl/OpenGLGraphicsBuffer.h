/**
 * @file platform/opengl/OpenGLGraphicsBuffer.h
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

#include <graphics/GraphicsBuffer.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLGraphicsBufferBase.h>

namespace Graphics
{
	class GraphicsBuffer::Implementation final : public Platform::GraphicsBufferBase
	{
	public:

		Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle, const BufferBinding& binding,
			const Uint size, const AccessMode& accessMode, const BufferUsage& usage);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation() = default;

		inline void bind() const;

		inline void debind() const;

		void demapData() const;

		inline Uint8* mapData() const;

		Uint8* mapData(const Uint size, const Uint offset) const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		using Base = Platform::GraphicsBufferBase;
	};

#include "inline/OpenGLGraphicsBuffer.inl"
}
