/**
 * @file platform/x/XGraphicsAdapterManager.cpp
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

#include <algorithm>
#include <core/Memory.h>
#include <core/StringStream.h>
#include <core/Types.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/LogUtility.h>
#include <platform/x/X.h>
#include <platform/x/XGraphicsAdapter.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static Uint32 getAdapterDisplayModes(Display* xConnection, const Int32 adapterIndex, DisplayModeList& modes);
static String8 getAdapterName(const Uint32 adapterIndex);
static Uint32 getCurrentAdapterDisplayModeIndex(const DisplayMode& currentMode, const DisplayModeList& modes);


// Implementation

// TODO: check that Xrandr is supported
class GraphicsAdapterManager::Implementation final
{
public:

	Implementation()
	{
		const Int32 adapterCount = XScreenCount(_x.connection());

		for(Int32 i = 0; i < adapterCount; ++i)
			createAdapter(i);
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		for(GraphicsAdapterList::const_iterator i = _graphicsAdapters.begin(), end = _graphicsAdapters.end(); i != end;
			++i)
		{
			DE_DELETE(*i, GraphicsAdapter);
		}
	}

	const GraphicsAdapterList& graphicsAdapters() const
	{
		return _graphicsAdapters;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GraphicsAdapterList _graphicsAdapters;
	X _x;

	void createAdapter(const Int32 adapterIndex)
	{
		DisplayModeList displayModes;
		const Uint32 currentDisplayModeIndex = ::getAdapterDisplayModes(_x.connection(), adapterIndex, displayModes);

		GraphicsAdapter::Implementation* graphicsAdapterImplementation =
			DE_NEW(GraphicsAdapter::Implementation)(adapterIndex, ::getAdapterName(adapterIndex), displayModes,
				currentDisplayModeIndex);

		GraphicsAdapter* graphicsAdapter = DE_NEW(GraphicsAdapter)(graphicsAdapterImplementation);
		// TODO: is the first adapter the primary adapter?
		_graphicsAdapters.push_back(graphicsAdapter);
	}
};


// Graphics::GraphicsAdapterManager

// Public

GraphicsAdapterManager::GraphicsAdapterManager()
	: _implementation(DE_NEW(Implementation)())
{
	logGraphicsAdapters(_implementation->graphicsAdapters());
}

GraphicsAdapterManager::~GraphicsAdapterManager()
{
	DE_DELETE(_implementation, Implementation);
}

const GraphicsAdapterList& GraphicsAdapterManager::graphicsAdapters() const
{
	return _implementation->graphicsAdapters();
}


// External

static Uint32 getAdapterDisplayModes(Display* xConnection, const Int32 adapterIndex, DisplayModeList& modes)
{
	Int32 resolutionCount;
	XRRScreenSize* resolutions = XRRSizes(xConnection, adapterIndex, &resolutionCount);
	DisplayMode currentMode;

	for(Int32 i = 0; i < resolutionCount; ++i)
	{
		Int32 frequencyCount;
		Int16* frequencies = XRRRates(xConnection, adapterIndex, i, &frequencyCount);

		for(Int32 j = 0; j < frequencyCount; ++j)
		{
			// TODO: get colour depth
			DisplayMode mode(resolutions[i].width, resolutions[i].height, 0u, frequencies[j]);
			modes.push_back(mode);

			if(i == 0 && j == 0)
				currentMode = mode;
		}
	}

	modes.shrink_to_fit();
	return getCurrentAdapterDisplayModeIndex(currentMode, modes);
}

static String8 getAdapterName(const Uint32 adapterIndex)
{
	StringStream8 nameStream;
	nameStream << "Adapter " << adapterIndex;

	return nameStream.str();
}

static Uint32 getCurrentAdapterDisplayModeIndex(const DisplayMode& currentMode, const DisplayModeList& modes)
{
	DisplayModeList::const_iterator iterator = std::find(modes.begin(), modes.end(), currentMode);
	return iterator - modes.begin();
}
