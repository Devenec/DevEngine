/**
 * @file graphics/ImageLoader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <content/ContentLoader.h>

namespace Core
{
	class FileStream;
}

namespace Graphics
{
	class Image;

	class ImageLoader final : public Content::ContentLoader<Image>
	{
	public:

		ImageLoader() = default;

		ImageLoader(const ImageLoader& imageLoader) = delete;
		ImageLoader(ImageLoader&& imageLoader) = delete;

		~ImageLoader() = default;

		Image* load(Core::FileStream& fileStream) override;

		ImageLoader& operator =(const ImageLoader& imageLoader) = delete;
		ImageLoader& operator =(ImageLoader&& imageLoader) = delete;
	};
}
