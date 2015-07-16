/**
 * @file platform/opengl/OpenGLGraphicsBuffer.h
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

#include <core/Types.h>
#include <graphics/GraphicsBuffer.h>

namespace Graphics
{
	enum class AccessMode;

	class GraphicsBuffer::Impl final
	{
	public:

		Impl(const Uint32 size, const AccessMode& accessMode);

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl();

		void demapData() const;

		Uint32 handle() const;

		Byte* mapData(const Uint32 size, const Uint32 bufferOffset) const;

		void setData(const Byte* data, const Uint32 dataSize, const Uint32 bufferOffset) const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

	private:

		static const Char8* COMPONENT_TAG;

		Uint32 _bufferHandle;
		Uint32 _flags;

		void createBuffer();
		void initialiseFlags(const AccessMode& accessMode);
		void initialiseStorage(const Uint32 size) const;
	};
}
