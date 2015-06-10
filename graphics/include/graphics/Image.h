/**
 * @file graphics/Image.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <content/ContentBase.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/ImageFormat.h>

namespace Graphics
{
	class Image final : public Content::ContentBase
	{
	public:

		inline Image(const Uint32 width, const Uint32 height, const ImageFormat& format,
			const Core::Vector<Byte>& data);

		Image(const Image& image) = delete;
		Image(Image&& image) = delete;

		~Image() = default;

		inline const Core::Vector<Byte>& data() const;

		inline const ImageFormat format() const;

		inline const Uint32 height() const;

		inline const Uint32 width() const;

		Image& operator =(const Image& image) = delete;
		Image& operator =(Image&& image) = delete;

	private:

		Core::Vector<Byte> _data;
		ImageFormat _format;
		Uint32 _height;
		Uint32 _width;
	};

#include "inline/Image.inl"
}
