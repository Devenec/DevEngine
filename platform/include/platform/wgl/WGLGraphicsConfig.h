/**
 * @file platform/wgl/WGLGraphicsConfig.h
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

#include <core/Types.h>
#include <graphics/GraphicsConfig.h>

namespace Graphics
{
	class GraphicsConfig::Impl final
	{
	public:

		Impl();

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl() = default;

		inline Int32 pixelFormatIndex() const;

		inline void setPixelFormatIndex(const Int32 pixelFormatIndex);

		Impl& operator =(const Impl& impl);

		Impl& operator =(Impl&& impl) = delete;

	private:

		Int32 _pixelFormatIndex;
	};

#include "inline/WGLGraphicsConfig.inl"
}
