/**
 * @file graphics/DisplayMode.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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


// Graphics

Bool Graphics::operator <(const DisplayMode& displayModeA, const DisplayMode& displayModeB)
{
	if(displayModeA.width() != displayModeB.width())
		return displayModeA.width() < displayModeB.width();
	else if(displayModeA.height() != displayModeB.height())
		return displayModeA.height() < displayModeB.height();
	else if(displayModeA.colourDepth() != displayModeB.colourDepth())
		return displayModeA.colourDepth() < displayModeB.colourDepth();
	else if(displayModeA.frequency() != displayModeB.frequency())
		return displayModeA.frequency() < displayModeB.frequency();
	else
		return false;
}
