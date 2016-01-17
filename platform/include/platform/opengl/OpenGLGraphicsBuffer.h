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

namespace Graphics
{
	class GraphicsBuffer::Implementation final
	{
	public:

		Implementation(const BufferBinding& binding, const Uint size, const AccessMode& accessMode,
			const BufferUsage& usage);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		inline void bind() const;

		inline Uint32 binding() const;

		inline void debind() const;

		void demapData() const;

		inline Uint32 handle() const;

		inline Uint8* mapData() const;

		Uint8* mapData(const Uint size, const Uint offset) const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		Uint _size;
		Uint32 _binding;
		Uint32 _bufferHandle;
		Uint32 _flags;

		void initialiseAccessMode(const AccessMode& accessMode);
		void createBuffer();
		void initialiseStorage(const AccessMode& accessMode, const BufferUsage& usage) const;
		void bind(const Uint32 bufferHandle) const;
		Uint32 getUsageValue(const AccessMode& accessMode, const BufferUsage& usage) const;
	};

#include "inline/OpenGLGraphicsBuffer.inl"
}
