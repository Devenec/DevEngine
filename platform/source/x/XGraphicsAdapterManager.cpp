/**
 * @file platform/x/XGraphicsAdapterManager.cpp
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

static String8 getAdapterName(const Uint32 adapterIndex);
static Uint32 getCurrentAdapterResolutionIndex(XRRScreenConfiguration* adapterConfig);


// Implementation

class GraphicsAdapterManager::Implementation final
{
public:

	Implementation()
	{
		const Uint32 adapterCount = _x.getGraphicsAdapterCount();

		for(Uint32 i = 0u; i < adapterCount; ++i)
		{
			GraphicsAdapter::Implementation* adapterImplementation = createAdapterImplementation(i);
			createAdapter(adapterImplementation);
		}
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		for(GraphicsAdapterList::const_iterator i = _adapters.begin(), end = _adapters.end(); i != end; ++i)
			DE_DELETE(*i, GraphicsAdapter);
	}

	const GraphicsAdapterList& adapters() const
	{
		return _adapters;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	GraphicsAdapterList _adapters;
	X _x;

	GraphicsAdapter::Implementation* createAdapterImplementation(const Uint32 adapterIndex) const
	{
		XRRScreenConfiguration* adapterConfig = X::instance().getGraphicsAdapterConfig(adapterIndex);
		const Uint32 currentResolutionIndex = ::getCurrentAdapterResolutionIndex(adapterConfig);
		const Uint32 currentRefreshRate = XRRConfigCurrentRate(adapterConfig);
		DisplayModeList displayModes;

		const Uint32 currentDisplayModeIndex =
			getAdapterDisplayModes(adapterIndex, displayModes, currentResolutionIndex, currentRefreshRate);

		return
			DE_NEW(GraphicsAdapter::Implementation)(adapterIndex, ::getAdapterName(adapterIndex),
				displayModes, currentDisplayModeIndex, adapterConfig);
	}

	void createAdapter(GraphicsAdapter::Implementation* adapterImplementation)
	{
		GraphicsAdapter* adapter = DE_NEW(GraphicsAdapter)(adapterImplementation);
		_adapters.push_back(adapter);
	}

	Uint32 getAdapterDisplayModes(const Uint32 adapterIndex, DisplayModeList& modes,
		const Uint32 currentResolutionIndex, const Uint32 currentRefreshRate) const
	{
		X& x = X::instance();
		Uint32 resolutionCount;
		XRRScreenSize* resolutions = x.getGraphicsAdapterResolutions(adapterIndex, resolutionCount);
		Uint32 currentModeIndex = 0u;

		for(Uint32 i = 0u; i < resolutionCount; ++i)
		{
			Uint32 refreshRateCount;
			Int16* refreshRates = x.getGraphicsAdapterRefreshRates(adapterIndex, i, refreshRateCount);

			for(Uint32 j = 0u; j < refreshRateCount; ++j)
			{
				if(i == currentResolutionIndex && refreshRates[j] == currentRefreshRate)
					currentModeIndex = static_cast<Uint32>(modes.size());

				DisplayMode mode(resolutions[i].width, resolutions[i].height, 0u, refreshRates[j]);
				modes.push_back(mode);
			}
		}

		modes.shrink_to_fit();
		return currentModeIndex;
	}
};


// Graphics::GraphicsAdapterManager

// Public

GraphicsAdapterManager::GraphicsAdapterManager()
	: _implementation(nullptr)
{
	_implementation = DE_NEW(Implementation)();
	logGraphicsAdapters(_implementation->adapters());
}

GraphicsAdapterManager::~GraphicsAdapterManager()
{
	DE_DELETE(_implementation, Implementation);
}

const GraphicsAdapterList& GraphicsAdapterManager::adapters() const
{
	return _implementation->adapters();
}


// External

static String8 getAdapterName(const Uint32 adapterIndex)
{
	StringStream8 nameStream;
	nameStream << "Adapter " << adapterIndex;

	return nameStream.str();
}

static Uint32 getCurrentAdapterResolutionIndex(XRRScreenConfiguration* adapterConfig)
{
	Rotation rotation;
	return XRRConfigCurrentConfiguration(adapterConfig, &rotation);
}
