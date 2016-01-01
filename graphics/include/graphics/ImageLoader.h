/**
 * @file graphics/ImageLoader.h
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
