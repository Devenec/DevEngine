/**
 * @file graphics/Image.h
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

#include <content/ContentBase.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/ImageFormat.h>

namespace Graphics
{
	using ByteData = Core::Vector<Uint8>;

	class Image final : public Content::ContentBase
	{
	public:

		Image(const Uint32 width, const Uint32 height, const ImageFormat& format, const ByteData& data);

		Image(const Image& image) = delete;
		Image(Image&& image) = delete;

		~Image() = default;

		inline const ByteData& data() const;

		inline const ImageFormat format() const;

		inline const Uint32 height() const;

		inline const Uint32 width() const;

		Image& operator =(const Image& image) = delete;
		Image& operator =(Image&& image) = delete;

	private:

		ByteData _data;
		ImageFormat _format;
		Uint32 _height;
		Uint32 _width;
	};

#include "inline/Image.inl"
}
