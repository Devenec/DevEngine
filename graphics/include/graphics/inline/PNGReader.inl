/**
 * @file graphics/inline/PNGReader.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

PNGReader::PNGReader()
	: _pngInfo(nullptr),
	  _pngStructure(nullptr)
{
	initialiseStructure();
	initialiseInfo();
}

PNGReader::~PNGReader()
{
	png_destroy_read_struct(&_pngStructure, &_pngInfo, nullptr);
}

const Uint32 PNGReader::imageHeight() const
{
	return png_get_image_height(_pngStructure, _pngInfo);
}

const Uint32 PNGReader::imageWidth() const
{
	return png_get_image_width(_pngStructure, _pngInfo);
}
