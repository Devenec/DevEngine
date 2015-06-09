/**
 * @file graphics/Image.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

Image::Image(const Uint32 width, const Uint32 height, const ImageFormat& format,const Core::Vector<Byte>& data)
	: _data(data),
	  _format(format),
	  _height(height),
	  _width(width) { }

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
