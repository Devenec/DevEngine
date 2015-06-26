/**
 * @file core/Rectangle.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Rectangle.h>

using namespace Core;

// Public

Rectangle::Rectangle(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height)
	: height(height),
	  width(width),
	  x(x),
	  y(y) { }
