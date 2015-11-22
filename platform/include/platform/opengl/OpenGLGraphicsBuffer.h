/**
 * @file platform/opengl/OpenGLGraphicsBuffer.h
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

#include <graphics/GraphicsBuffer.h>

namespace Platform
{
	class OpenGL;
}

namespace Graphics
{
	class GraphicsBuffer::Implementation final
	{
	public:

		Implementation(Platform::OpenGL* openGL, const Uint32 binding, const Uint32 size,
			const AccessMode& accessMode);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		inline void bind() const;

		void bindIndexed(const Uint32 bindingIndex) const;

		inline Uint32 binding() const;

		inline void debind() const;

		void debindIndexed(const Uint32 bindingIndex) const;

		void demapData() const;

		inline Uint32 handle() const;

		inline Byte* mapData() const;

		Byte* mapData(const Uint32 size, const Uint32 offset) const;

		void setData(const Byte* data, const Uint32 size, const Uint32 offset) const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		Platform::OpenGL* _openGL;
		Uint32 _binding;
		Uint32 _bufferHandle;
		Uint32 _flags;
		Uint32 _size;

		void bind(const Uint32 bufferHandle) const;
		void initialiseAccessMode(const AccessMode& accessMode);
		void createBuffer();
		void initialiseStorage() const;
	};

#include "inline/OpenGLGraphicsBuffer.inl"
}
