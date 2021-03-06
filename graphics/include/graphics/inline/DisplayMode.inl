/**
 * @file graphics/inline/DisplayMode.inl
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

// Public

Uint32 DisplayMode::colourDepth() const
{
	return _colourDepth;
}

Uint32 DisplayMode::height() const
{
	return _height;
}

Uint32 DisplayMode::refreshRate() const
{
	return _refreshRate;
}

Uint32 DisplayMode::width() const
{
	return _width;
}


// Graphics

Bool operator ==(const DisplayMode& displayModeA, const DisplayMode& displayModeB)
{
	return
		displayModeA.refreshRate() == displayModeB.refreshRate() &&
		displayModeA.colourDepth() == displayModeB.colourDepth() &&
		displayModeA.height() == displayModeB.height() &&
		displayModeA.width() == displayModeB.width();
}

Bool operator !=(const DisplayMode& displayModeA, const DisplayMode& displayModeB)
{
	return !(displayModeA == displayModeB);
}
