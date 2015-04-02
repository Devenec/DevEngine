/**
 * @file graphics/inline/DisplayMode.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

DisplayMode::DisplayMode()
	: _width(0u),
	  _height(0u),
	  _colourDepth(0u),
	  _frequency(0u) { }

DisplayMode::DisplayMode(const Uint32 width, const Uint32 height, const Uint32 colourDepth, const Uint32 frequency)
	: _width(width),
	  _height(height),
	  _colourDepth(colourDepth),
	  _frequency(frequency) { }

Uint32 DisplayMode::colourDepth() const
{
	return _colourDepth;
}

Uint32 DisplayMode::frequency() const
{
	return _frequency;
}

Uint32 DisplayMode::height() const
{
	return _height;
}

Uint32 DisplayMode::width() const
{
	return _width;
}
