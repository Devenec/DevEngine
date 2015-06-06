/**
 * @file platform/windows/WindowsGraphicsAdapterManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Memory.h>
#include <core/String.h>
#include <core/Types.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsAdapterManager.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// Implementation

class GraphicsAdapterManager::Impl final
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

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		for(GraphicsAdapterList::const_iterator i = _graphicsAdapters.begin(), end = _graphicsAdapters.end(); i != end;
			++i)
		{
			DE_DELETE *i;
		}
	}

	const GraphicsAdapterList& graphicsAdapters() const
	{
		return _graphicsAdapters;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	GraphicsAdapterList _graphicsAdapters;

	Bool initialiseAdapter(const Uint32 adapterIndex, DISPLAY_DEVICEW& adapterInfo)
	{
		const Int32 result = EnumDisplayDevicesW(nullptr, adapterIndex, &adapterInfo, 0u);

		if(result != 0 && (adapterInfo.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0u)
		{
			DisplayModeList displayModes;
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

	Uint32 getAdapterDisplayModes(const Char16* adapterName, DisplayModeList& modes) const
	{
		DisplayMode displayMode(1u, 0u, 0u, 0u);
		DEVMODEW displayModeInfo;
		displayModeInfo.dmDriverExtra = 0u;
		displayModeInfo.dmSize = sizeof(displayModeInfo);

		for(Uint32 i = 0u; displayMode.width() != 0u; ++i)
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

	Uint32 getCurrentAdapterDisplayModeIndex(const Char16* adapterName, DEVMODEW& modeInfo,
		const DisplayModeList& modes) const
	{
		const DisplayMode displayMode = getAdapterDisplayMode(adapterName, ENUM_CURRENT_SETTINGS, modeInfo);
		DisplayModeList::const_iterator iterator = std::find(modes.begin(), modes.end(), displayMode);

		return iterator - modes.begin();
	}
};


// Public

GraphicsAdapterManager::GraphicsAdapterManager()
	: _impl(nullptr) { }

void GraphicsAdapterManager::deinitialise()
{
	DE_DELETE _impl;
}

const GraphicsAdapterList& GraphicsAdapterManager::graphicsAdapters() const
{
	DE_ASSERT(_impl != nullptr);
	return _impl->graphicsAdapters();
}

void GraphicsAdapterManager::initialise()
{
	_impl = DE_NEW Impl();
}
