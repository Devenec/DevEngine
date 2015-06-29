/**
 * @file graphics/inline/DisplayMode.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
