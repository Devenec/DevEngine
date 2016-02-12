/**
 * @file platform/opengl/OpenGLGraphicsBufferBase.h
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

namespace Graphics
{
	enum class AccessMode;
	enum class BufferBinding;
	enum class BufferUsage;
}

namespace Platform
{
	class GraphicsBufferBase
	{
	public:

		GraphicsBufferBase(const Graphics::BufferBinding& binding, const Uint size,
			const Graphics::AccessMode& accessMode, const Graphics::BufferUsage& usage);

		GraphicsBufferBase(const GraphicsBufferBase& graphicsBufferBase) = delete;
		GraphicsBufferBase(GraphicsBufferBase&& graphicsBufferBase) = delete;

		~GraphicsBufferBase();

		inline void bind() const;

		inline Graphics::BufferBinding binding() const;

		inline void debind() const;

		void demapData() const;

		inline Uint32 handle() const;

		inline Uint8* mapData() const;

		Uint8* mapData(const Uint size, const Uint offset) const;

		GraphicsBufferBase& operator =(const GraphicsBufferBase& graphicsBufferBase) = delete;
		GraphicsBufferBase& operator =(GraphicsBufferBase&& graphicsBufferBase) = delete;

	private:

		Uint _size;
		Uint32 _binding;
		Uint32 _bufferHandle;
		Uint32 _flags;

		void initialiseAccessMode(const Graphics::AccessMode& accessMode);
		void createBuffer();
		void initialiseStorage(const Graphics::AccessMode& accessMode, const Graphics::BufferUsage& usage)
			const;

		void bind(const Uint32 bufferHandle) const;

		static Uint32 getUsageValue(const Graphics::AccessMode& accessMode,
			const Graphics::BufferUsage& usage);
	};

#include "inline/OpenGLGraphicsBufferBase.inl"
}
