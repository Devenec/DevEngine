/**
 * @file graphics/DisplayMode.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <graphics/DisplayMode.h>

using namespace Graphics;

// Public

// Operators

Bool DisplayMode::operator ==(const DisplayMode& displayMode) const
{
	return _width == displayMode._width && _height == displayMode._height &&
		_colourDepth == displayMode._colourDepth && _frequency == displayMode._frequency;
}

Bool DisplayMode::operator <(const DisplayMode& displayMode) const
{
	if(_width != displayMode._width)
		return _width < displayMode._width;
	else if(_height != displayMode._height)
		return _height < displayMode._height;
	else if(_colourDepth != displayMode._colourDepth)
		return _colourDepth < displayMode._colourDepth;
	else if(_frequency != displayMode._frequency)
		return _frequency < displayMode._frequency;
	else
		return false;
}
