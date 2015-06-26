/**
 * @file graphics/inline/DisplayMode.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

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

// Operators

Bool DisplayMode::operator ==(const DisplayMode& displayMode) const
{
	return _width == displayMode._width && _height == displayMode._height &&
		_colourDepth == displayMode._colourDepth && _frequency == displayMode._frequency;
}

Bool DisplayMode::operator !=(const DisplayMode& displayMode) const
{
	return !(*this == displayMode);
}
