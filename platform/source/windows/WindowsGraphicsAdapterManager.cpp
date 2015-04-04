/**
 * @file platform/windows/WindowsGraphicsAdapterManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Memory.h>
#include <core/String.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapterManager.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// Implementation

class GraphicsAdapterManager::Impl
{
public:

	Impl()
	{
		Bool areAdaptersAvailable = true;
		DISPLAY_DEVICEW adapterInfo;
		adapterInfo.cb = sizeof(adapterInfo);

		for(Uint32 i = 0u; areAdaptersAvailable; ++i)
			areAdaptersAvailable = initialiseAdapter(i, adapterInfo);
	}

	~Impl()
	{
		for(GraphicsAdapters::const_iterator i = _graphicsAdapters.begin(), end = _graphicsAdapters.end(); i != end;
			++i)
		{
			DE_DELETE *i;
		}
	}

	const GraphicsAdapters& graphicsAdapters() const
	{
		return _graphicsAdapters;
	}

private:

	GraphicsAdapters _graphicsAdapters;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	Bool initialiseAdapter(const Uint32 adapterIndex, DISPLAY_DEVICEW& adapterInfo)
	{
		const Int32 result = EnumDisplayDevicesW(nullptr, adapterIndex, &adapterInfo, 0u);

		if(result != 0 && (adapterInfo.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0u)
		{
			DisplayModes displayModes;
			const Uint32 currentDisplayModeIndex = getAdapterDisplayModes(adapterInfo.DeviceName, displayModes);

			GraphicsAdapter* graphicsAdapter = DE_NEW GraphicsAdapter(toString8(adapterInfo.DeviceName), displayModes,
				currentDisplayModeIndex);

			if((adapterInfo.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) != 0u)
				_graphicsAdapters.insert(_graphicsAdapters.begin(), graphicsAdapter);
			else
				_graphicsAdapters.push_back(graphicsAdapter);
		}

		return result != 0;
	}

	Uint32 getAdapterDisplayModes(const Char16* adapterName, DisplayModes& modes) const
	{
		DisplayMode displayMode(1u, 0u, 0u, 0u);
		DEVMODEW displayModeInfo;
		displayModeInfo.dmDriverExtra = 0u;
		displayModeInfo.dmSize = sizeof(displayModeInfo);

		for(Uint32 i = 0u; displayMode.width() != 0; ++i)
		{
			displayMode = getAdapterDisplayMode(adapterName, i, displayModeInfo);

			if(displayMode.width() != 0u && std::find(modes.begin(), modes.end(), displayMode) == modes.end())
				modes.push_back(displayMode);
		}

		modes.shrink_to_fit();
		std::sort(modes.begin(), modes.end());

		return getCurrentAdapterDisplayModeIndex(adapterName, displayModeInfo, modes);
	}

	DisplayMode getAdapterDisplayMode(const Char16* adapterName, const Uint32 modeIndex, DEVMODEW& modeInfo) const
	{
		const Int32 result = EnumDisplaySettingsW(adapterName, modeIndex, &modeInfo);

		if(result == 0)
		{
			return DisplayMode();
		}
		else
		{
			return DisplayMode(modeInfo.dmPelsWidth, modeInfo.dmPelsHeight, modeInfo.dmBitsPerPel,
				modeInfo.dmDisplayFrequency);
		}
	}

	Uint32 getCurrentAdapterDisplayModeIndex(const Char16* adapterName, DEVMODEW& modeInfo, const DisplayModes& modes)
		const
	{
		const DisplayMode displayMode = getAdapterDisplayMode(adapterName, ENUM_CURRENT_SETTINGS, modeInfo);
		DisplayModes::const_iterator iterator = std::find(modes.begin(), modes.end(), displayMode);
		DE_ASSERT(iterator != modes.end());

		return iterator - modes.begin();
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;
};


// Public

GraphicsAdapterManager::GraphicsAdapterManager()
	: _impl(DE_NEW Impl()) { }

GraphicsAdapterManager::~GraphicsAdapterManager()
{
	DE_DELETE _impl;
}

const GraphicsAdapters& GraphicsAdapterManager::graphicsAdapters() const
{
	return _impl->graphicsAdapters();
}
