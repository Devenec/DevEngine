/**
 * @file graphics/ImageLoader.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Error.h>
#include <core/FileStream.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/Image.h>
#include <graphics/ImageLoader.h>

using namespace Core;
using namespace Graphics;

// External

static const Char8* IMAGELOADER_CONTEXT = "[Graphics::ImageLoader]";


// Public

ImageLoader::ImageLoader()
	: _pngReader(nullptr),
	  _pngInfo(nullptr) { }

Image* ImageLoader::load(FileStream& fileStream)
{
	validatePngSignature(fileStream);
	initialisePngReader(fileStream);
	initialisePngInfo();
	const Vector<Byte> imageData = readImage();
	const Uint32 imageWidth = png_get_image_width(_pngReader, _pngInfo);
	const Uint32 imageHeight = png_get_image_height(_pngReader, _pngInfo);
	const ImageFormat imageFormat = getImageFormat();
	deinitialisePngReader();

	return DE_NEW Image(imageWidth, imageHeight, imageFormat, imageData);
}

// Private

void ImageLoader::initialisePngReader(Core::FileStream& fileStream)
{
	_pngReader = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, nullptr, handlePngReaderError,
		handlePngReaderWarning, nullptr, allocatePngReaderMemory, deallocatePngReaderMemory);

	if(_pngReader == nullptr)
	{
		defaultLog << LogLevel::Error << IMAGELOADER_CONTEXT << " Failed to initialise the PNG reader." <<
			Log::Flush();

		DE_ERROR(0); // TODO: set errorCode
	}

	png_set_read_fn(_pngReader, &fileStream, readPngReader);
	png_set_sig_bytes(_pngReader, 8);
}

void ImageLoader::initialisePngInfo()
{
	_pngInfo = png_create_info_struct(_pngReader);

	if(_pngInfo == nullptr)
	{
		defaultLog << LogLevel::Error << IMAGELOADER_CONTEXT << " Failed to initialise the PNG info." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}
}

Vector<Byte> ImageLoader::readImage() const
{
	const Int32 transforms = PNG_TRANSFORM_PACKING | PNG_TRANSFORM_SCALE_16;
	png_read_png(_pngReader, _pngInfo, transforms, nullptr);

	const Uint32 height = png_get_image_height(_pngReader, _pngInfo);
	const Uint32 rowByteCount = png_get_rowbytes(_pngReader, _pngInfo);
	Vector<Byte> data(height * rowByteCount);
	data.shrink_to_fit();
	Byte** rows = png_get_rows(_pngReader, _pngInfo);

	for(Uint32 i = 0u; i < height; ++i)
		std::copy(rows[i], rows[i] + rowByteCount, data.data() + i * rowByteCount);

	return data;
}

ImageFormat ImageLoader::getImageFormat() const
{
	switch(png_get_color_type(_pngReader, _pngInfo))
	{
		case PNG_COLOR_TYPE_GRAY:
			return ImageFormat::R8;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			return ImageFormat::RA8;

		case PNG_COLOR_TYPE_PALETTE:
		case PNG_COLOR_TYPE_RGB:
			return ImageFormat::RGB8;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			return ImageFormat::RGBA8;

		default:
			defaultLog << LogLevel::Error << IMAGELOADER_CONTEXT << " The image format is not supported."
				<< Log::Flush();

			DE_ERROR(0); // TODO: set errorCode
			return ImageFormat();
	}
}

void ImageLoader::deinitialisePngReader()
{
	png_destroy_read_struct(&_pngReader, &_pngInfo, nullptr);
}

// Static

void ImageLoader::validatePngSignature(Core::FileStream& fileStream)
{
	Byte signature[8];
	fileStream.read(signature, sizeof(signature));
	const Int32 result = png_sig_cmp(signature, 0u, sizeof(signature));

	if(result != 0)
	{
		defaultLog << LogLevel::Error << IMAGELOADER_CONTEXT << " The PNG signature is invalid." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}
}

void ImageLoader::handlePngReaderError(png_struct* pngReader, const Char8* message)
{
	static_cast<Void>(pngReader);
	defaultLog << LogLevel::Error << IMAGELOADER_CONTEXT << " PNG error: " << message << '.' << Log::Flush();
	DE_ERROR(0); // TODO: set errorCode
}

void ImageLoader::handlePngReaderWarning(png_struct* pngReader, const Char8* message)
{
	static_cast<Void>(pngReader);
	defaultLog << LogLevel::Warning << IMAGELOADER_CONTEXT << " PNG warning: " << message << '.' << Log::Flush();
}

Void* ImageLoader::allocatePngReaderMemory(png_struct* pngReader, Uint32 size)
{
	static_cast<Void>(pngReader);
	return DE_NEW Byte[size];
}

void ImageLoader::deallocatePngReaderMemory(png_struct* pngReader, Void* pointer)
{
	static_cast<Void>(pngReader);
	DE_DELETE[] pointer;
}

void ImageLoader::readPngReader(png_struct* pngReader, Byte* buffer, Uint32 byteCount)
{
	FileStream* fileStream = static_cast<FileStream*>(png_get_io_ptr(pngReader));

	if(fileStream->isAtEndOfFile())
		png_error(pngReader, "Reached the end of the file");

	fileStream->read(buffer, byteCount);
}


// External

namespace Content
{
	template<>
	ContentLoader<Image>* ContentLoader<Image>::loader()
	{
		return DE_NEW ImageLoader();
	}
}
