/**
 * @file graphics/inline/Image.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

const Core::Vector<Byte>& Image::data() const
{
	return _data;
}

const ImageFormat Image::format() const
{
	return _format;
}

const Uint32 Image::height() const
{
	return _height;
}

const Uint32 Image::width() const
{
	return _width;
}
