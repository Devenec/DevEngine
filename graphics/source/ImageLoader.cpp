/**
 * @file graphics/ImageLoader.cpp
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

#include <core/FileStream.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <graphics/Image.h>
#include <graphics/ImageLoader.h>
#include <graphics/PNGReader.h>

using namespace Content;
using namespace Core;
using namespace Graphics;

// Public

Image* ImageLoader::load(FileStream& fileStream)
{
	PNGReader pngReader;
	const ByteList imageData = pngReader.readImage(fileStream);

	return DE_NEW(Image)(pngReader.imageWidth(), pngReader.imageHeight(), pngReader.imageFormat(), imageData);
}


// External

template<>
ContentLoader<Image>* ContentLoader<Image>::createLoader()
{
	return DE_NEW(ImageLoader)();
}
