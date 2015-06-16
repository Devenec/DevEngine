/**
 * @file core/inline/Rectangle.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

Rectangle::Rectangle(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height)
	: height(height),
	  width(width),
	  x(x),
	  y(y) { }

Int32 Rectangle::bottom() const
{
	return y + height;
}

Int32 Rectangle::left() const
{
	return x;
}

Int32 Rectangle::right() const
{
	return x + width;
}

Int32 Rectangle::top() const
{
	return y;
}
