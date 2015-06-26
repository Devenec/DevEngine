/**
 * @file graphics/DisplayMode.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <graphics/DisplayMode.h>

using namespace Graphics;

// Public

DisplayMode::DisplayMode()
	: _colourDepth(0u),
	  _frequency(0u),
	  _height(0u),
	  _width(0u) { }

DisplayMode::DisplayMode(const Uint32 width, const Uint32 height, const Uint32 colourDepth, const Uint32 frequency)
	: _colourDepth(colourDepth),
	  _frequency(frequency),
	  _height(height),
	  _width(width) { }

// Operators

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
