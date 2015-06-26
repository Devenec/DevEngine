/**
 * @file graphics/Image.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <graphics/Image.h>

using namespace Core;
using namespace Graphics;

// Public

Image::Image(const Uint32 width, const Uint32 height, const ImageFormat& format, const Vector<Byte>& data)
	: _data(data),
	  _format(format),
	  _height(height),
	  _width(width) { }
