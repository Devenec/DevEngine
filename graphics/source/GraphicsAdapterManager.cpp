/**
 * @file graphics/GraphicsAdapterManager.cpp
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

#include <cmath>
#include <core/Log.h>
#include <core/Types.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>

using namespace Core;
using namespace Graphics;

// External

static void logAdapterDisplayMode(const DisplayMode& displayMode, const Bool insertSeparator);
static void logAdapterDisplayModes(const GraphicsAdapter& graphicsAdapter);


// Some members are defined in platform/*/*GraphicsAdapterManager.cpp

// Private

void GraphicsAdapterManager::logAdapters() const
{
	defaultLog << LogLevel::Info << "Active graphics adapters and supported display modes:";
	const GraphicsAdapterList& graphicsAdapters = this->graphicsAdapters();

	for(GraphicsAdapterList::const_iterator i = graphicsAdapters.begin(), end = graphicsAdapters.end(); i != end; ++i)
	{
		defaultLog << "\n\n" << i - graphicsAdapters.begin() << ". " << (*i)->name();
		logAdapterDisplayModes(**i);
	}

	defaultLog << '\n' << Log::Flush();
}


// External

static void logAdapterDisplayMode(const DisplayMode& displayMode, const Bool insertSeparator)
{
	if(insertSeparator)
		defaultLog << "    ";

	if(displayMode.width() < 1000u)
		defaultLog << ' ';

	defaultLog << displayMode.width() << " x ";

	if(displayMode.height() < 1000u)
		defaultLog << ' ';

	defaultLog << displayMode.height() << ", ";

	if(displayMode.colourDepth() < 10u)
		defaultLog << ' ';

	defaultLog << displayMode.colourDepth() << " bit, ";

	if(displayMode.frequency() < 100u)
		defaultLog << ' ';

	defaultLog << displayMode.frequency() << "Hz";
}

static void logAdapterDisplayModes(const GraphicsAdapter& graphicsAdapter)
{
	const DisplayModeList& displayModes = graphicsAdapter.supportedDisplayModes();
	const Uint32 displayModeCount = displayModes.size();
	const Uint32 rowCount = static_cast<Uint32>(std::ceil(displayModeCount / 3.0f));

	for(Uint32 i = 0u; i < rowCount; ++i)
	{
		defaultLog << '\n';

		for(Uint32 j = i; j <= i + 3u * rowCount && j < displayModeCount; j += rowCount)
			logAdapterDisplayMode(displayModes[j], j != i);
	}
}
