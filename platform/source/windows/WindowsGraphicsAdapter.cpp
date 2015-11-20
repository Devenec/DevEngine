/**
 * @file platform/windows/WindowsGraphicsAdapter.cpp
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
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsAdapter - Windows]";

static DEVMODEW createDisplayModeInfo(const DisplayMode& mode);


// Implementation

class GraphicsAdapter::Impl final
{
public:

	Impl(const String8& name, const DisplayModeList& supportedDisplayModes, const Uint32 currentDisplayModeIndex)
		: _name(toString16(name)),
		  _supportedDisplayModes(supportedDisplayModes),
		  _currentDisplayModeIndex(currentDisplayModeIndex),
		  _initialDisplayModeIndex(currentDisplayModeIndex) { }

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		if(_currentDisplayModeIndex != _initialDisplayModeIndex)
			changeDisplaySettings(nullptr, 0u);
	}

	const DisplayMode& currentDisplayMode() const
	{
		return _supportedDisplayModes[_currentDisplayModeIndex];
	}

	String8 name() const
	{
		return toString8(_name);
	}

	void setDisplayMode(const DisplayMode& mode)
	{
		DisplayModeList::const_iterator iterator = std::find(_supportedDisplayModes.begin(),
			_supportedDisplayModes.end(), mode);

		DE_ASSERT(iterator != _supportedDisplayModes.end());
		DEVMODEW displayModeInfo = ::createDisplayModeInfo(mode);
		changeDisplaySettings(&displayModeInfo, CDS_FULLSCREEN);
		_currentDisplayModeIndex = iterator - _supportedDisplayModes.begin();
	}

	const DisplayModeList& supportedDisplayModes() const
	{
		return _supportedDisplayModes;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	String16 _name;
	DisplayModeList _supportedDisplayModes;
	Uint32 _currentDisplayModeIndex;
	Uint32 _initialDisplayModeIndex;

	void changeDisplaySettings(DEVMODEW* displayModeInfo, const Uint32 flags) const
	{
		const Int32 result = ChangeDisplaySettingsExW(_name.c_str(), displayModeInfo, nullptr, flags, nullptr);

		if(result != DISP_CHANGE_SUCCESSFUL)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to change the display mode, with"
				"ChangeDisplaySettingsEx return code " << result << '.' << Log::Flush();

			DE_ERROR(0x0);
		}
	}
};


// Graphics::GraphicsAdapter

// Public

const DisplayMode& GraphicsAdapter::currentDisplayMode() const
{
	return _impl->currentDisplayMode();
}

String8 GraphicsAdapter::name() const
{
	return _impl->name();
}

void GraphicsAdapter::setDisplayMode(const DisplayMode& mode) const
{
	_impl->setDisplayMode(mode);
}

const DisplayModeList& GraphicsAdapter::supportedDisplayModes() const
{
	return _impl->supportedDisplayModes();
}

// Private

GraphicsAdapter::GraphicsAdapter(const String8& name, const DisplayModeList& supportedDisplayModes,
	const Uint32 currentDisplayModeIndex)
	: _impl(DE_NEW(Impl)(name, supportedDisplayModes, currentDisplayModeIndex)) { }

GraphicsAdapter::~GraphicsAdapter()
{
	DE_DELETE(_impl, Impl);
}


// External

static DEVMODEW createDisplayModeInfo(const DisplayMode& mode)
{
	DEVMODEW displayModeInfo = DEVMODEW();
	displayModeInfo.dmBitsPerPel = mode.colourDepth();
	displayModeInfo.dmDisplayFrequency = mode.frequency();
	displayModeInfo.dmFields = DM_BITSPERPEL | DM_DISPLAYFREQUENCY | DM_PELSHEIGHT | DM_PELSWIDTH;
	displayModeInfo.dmPelsHeight = mode.height();
	displayModeInfo.dmPelsWidth = mode.width();
	displayModeInfo.dmSize = sizeof(DEVMODEW);

	return displayModeInfo;
}
