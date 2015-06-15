/**
 * @file graphics/ImageLoader.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/FileStream.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Image.h>
#include <graphics/ImageLoader.h>
#include <graphics/PNGReader.h>

using namespace Core;
using namespace Graphics;

// Public

Image* ImageLoader::load(FileStream& fileStream)
{
	PNGReader pngReader;
	const Vector<Byte> imageData = pngReader.readImage(fileStream);
	const Uint32 imageWidth = pngReader.imageWidth();
	const Uint32 imageHeight = pngReader.imageHeight();
	const ImageFormat imageFormat = pngReader.imageFormat();

	return DE_NEW(Image)(imageWidth, imageHeight, imageFormat, imageData);
}


// External

namespace Content
{
	template<>
	ContentLoader<Image>* ContentLoader<Image>::createLoader()
	{
		return DE_NEW(ImageLoader)();
	}
}
