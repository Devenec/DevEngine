/**
 * @file platform/windows/WindowsGraphicsAdapterManager.cpp
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

#include <algorithm>
#include <core/Memory.h>
#include <core/Types.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/LogUtility.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsGraphicsAdapter.h>

using namespace Core;
using namespace Graphics;

// External

static DISPLAY_DEVICEW createAdapterInfo();
static DEVMODEW createDisplayModeInfo();
static DisplayMode getDisplayMode(const Char16* adapterName, const Uint32 modeIndex, DEVMODEW& modeInfo);
static Uint32 getDisplayModes(const Char16* adapterName, DisplayModeList& modes);

static Uint32 getCurrentDisplayModeIndex(const Char16* adapterName, DEVMODEW& modeInfo,
	const DisplayModeList& modes);


// Implementation

class GraphicsAdapterManager::Implementation final
{
public:

	Implementation()
	{
		Bool isAdapterAvailable = true;
		DISPLAY_DEVICEW adapterInfo = ::createAdapterInfo();

		for(Uint32 i = 0u; isAdapterAvailable; ++i)
			isAdapterAvailable = createAdapter(i, adapterInfo);
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

	Bool createAdapter(const Uint32 adapterIndex, DISPLAY_DEVICEW& adapterInfo)
	{
		const Int32 result = EnumDisplayDevicesW(nullptr, adapterIndex, &adapterInfo, 0u);

		if(result != 0 && (adapterInfo.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0u)
		{
			GraphicsAdapter::Implementation* adapterImplementation = createAdapterImplementation(adapterInfo);
			GraphicsAdapter* adapter = DE_NEW(GraphicsAdapter)(adapterImplementation);

			if((adapterInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0u)
				_adapters.insert(_adapters.begin(), adapter);
			else
				_adapters.push_back(adapter);
		}

		return result != 0;
	}

	GraphicsAdapter::Implementation* createAdapterImplementation(DISPLAY_DEVICEW& adapterInfo)
		const
	{
		DisplayModeList displayModes;
		const Uint32 currentDisplayModeIndex = ::getDisplayModes(adapterInfo.DeviceName, displayModes);

		return
			DE_NEW(GraphicsAdapter::Implementation)(adapterInfo.DeviceName, displayModes,
				currentDisplayModeIndex);
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

static DISPLAY_DEVICEW createAdapterInfo()
{
	DISPLAY_DEVICEW adapterInfo;
	adapterInfo.cb = sizeof(DISPLAY_DEVICEW);

	return adapterInfo;
}

static DEVMODEW createDisplayModeInfo()
{
	DEVMODEW displayModeInfo = DEVMODEW();
	displayModeInfo.dmSize = sizeof(DEVMODEW);

	return displayModeInfo;
}

static DisplayMode getDisplayMode(const Char16* adapterName, const Uint32 modeIndex, DEVMODEW& modeInfo)
{
	const Int32 result = EnumDisplaySettingsW(adapterName, modeIndex, &modeInfo);

	if(result == 0)
	{
		return DisplayMode();
	}
	else
	{
		return
			DisplayMode(modeInfo.dmPelsWidth, modeInfo.dmPelsHeight, modeInfo.dmBitsPerPel,
				modeInfo.dmDisplayFrequency);
	}
}

static Uint32 getDisplayModes(const Char16* adapterName, DisplayModeList& modes)
{
	DisplayMode mode(1u, 0u, 0u, 0u);
	DEVMODEW modeInfo = ::createDisplayModeInfo();

	for(Uint32 i = 0u; mode.width() != 0u; ++i)
	{
		mode = ::getDisplayMode(adapterName, i, modeInfo);

		if(mode.width() != 0u && std::find(modes.begin(), modes.end(), mode) == modes.end())
			modes.push_back(mode);
	}

	modes.shrink_to_fit();
	std::sort(modes.begin(), modes.end());

	return ::getCurrentDisplayModeIndex(adapterName, modeInfo, modes);
}

static Uint32 getCurrentDisplayModeIndex(const Char16* adapterName, DEVMODEW& modeInfo,
	const DisplayModeList& modes)
{
	const DisplayMode displayMode = ::getDisplayMode(adapterName, ENUM_CURRENT_SETTINGS, modeInfo);
	DisplayModeList::const_iterator iterator = std::find(modes.begin(), modes.end(), displayMode);

	return static_cast<Uint32>(iterator - modes.begin());
}
