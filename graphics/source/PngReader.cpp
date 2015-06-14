/**
 * @file graphics/PNGReader.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Error.h>
#include <core/FileStream.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/PNGReader.h>

static const Char8* PNGREADER_CONTEXT = "[Graphics::PNGReader]";

using namespace Core;
using namespace Graphics;

// Public

ImageFormat PNGReader::imageFormat() const
{
	switch(png_get_color_type(_pngStructure, _pngInfo))
	{
		case PNG_COLOR_TYPE_GRAY:
			return ImageFormat::R8;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			return ImageFormat::RA8;

		case PNG_COLOR_TYPE_RGB:
			return ImageFormat::RGB8;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			return ImageFormat::RGBA8;

		default:
			DE_ASSERT(false);
			return ImageFormat();
	}
}

Vector<Byte> PNGReader::readImage(FileStream& fileStream)
{
	validateSignature(fileStream);
	png_set_read_fn(_pngStructure, &fileStream, readData);
	const Int32 transforms = PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_SCALE_16;
	png_read_png(_pngStructure, _pngInfo, transforms, nullptr);
	const Uint32 height = png_get_image_height(_pngStructure, _pngInfo);
	const Uint32 rowByteCount = png_get_rowbytes(_pngStructure, _pngInfo);
	Vector<Byte> data(height * rowByteCount);
	data.shrink_to_fit();
	Byte** rows = png_get_rows(_pngStructure, _pngInfo);

	for(Uint32 i = 0u; i < height; ++i)
		std::copy(rows[i], rows[i] + rowByteCount, data.data() + i * rowByteCount);

	return data;
}

// Private

void PNGReader::initialiseStructure()
{
	_pngStructure = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, nullptr, handleError, handleWarning, nullptr,
		allocateMemory, deallocateMemory);

	if(_pngStructure == nullptr)
	{
		defaultLog << LogLevel::Error << PNGREADER_CONTEXT << " Failed to initialise the PNG structure." <<
			Log::Flush();

		DE_ERROR(0); // TODO: set errorCode
	}
}

void PNGReader::initialiseInfo()
{
	_pngInfo = png_create_info_struct(_pngStructure);

	if(_pngInfo == nullptr)
	{
		defaultLog << LogLevel::Error << PNGREADER_CONTEXT << " Failed to initialise the PNG info." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}
}

void PNGReader::validateSignature(FileStream& fileStream)
{
	Byte signature[8];
	fileStream.read(signature, sizeof(signature));
	const Int32 result = png_sig_cmp(signature, 0u, sizeof(signature));

	if(result != 0)
	{
		defaultLog << LogLevel::Error << PNGREADER_CONTEXT << " The PNG signature is invalid." << Log::Flush();
		DE_ERROR(0); // TODO: set errorCode
	}

	png_set_sig_bytes(_pngStructure, 8);
}

// Static

void PNGReader::handleError(PNGStructure* pngStructure, const Char8* message)
{
	static_cast<Void>(pngStructure);
	defaultLog << LogLevel::Error << PNGREADER_CONTEXT << " PNG error: " << message << '.' << Log::Flush();
	DE_ERROR(0); // TODO: set errorCode
}

void PNGReader::handleWarning(PNGStructure* pngStructure, const Char8* message)
{
	static_cast<Void>(pngStructure);
	defaultLog << LogLevel::Warning << PNGREADER_CONTEXT << " PNG warning: " << message << '.' << Log::Flush();
}

Void* PNGReader::allocateMemory(PNGStructure* pngStructure, Uint32 byteCount)
{
	static_cast<Void>(pngStructure);
	return DE_MALLOC(byteCount);
}

void PNGReader::deallocateMemory(PNGStructure* pngStructure, Void* pointer)
{
	static_cast<Void>(pngStructure);
	DE_FREE(pointer);
}

void PNGReader::readData(PNGStructure* pngStructure, Byte* buffer, Uint32 byteCount)
{
	FileStream* fileStream = static_cast<FileStream*>(png_get_io_ptr(pngStructure));

	if(fileStream->isAtEndOfFile())
		png_error(pngStructure, "Reached the end of the file");

	fileStream->read(buffer, byteCount);
}
