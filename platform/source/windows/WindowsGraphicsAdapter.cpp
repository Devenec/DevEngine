/**
 * @file platform/windows/WindowsGraphicsAdapter.cpp
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
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsGraphicsAdapter.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::GraphicsAdapter - Windows] ";

static DEVMODEW createDisplayModeInfo(const DisplayMode& mode);


// Implementation

// Public

GraphicsAdapter::Implementation::Implementation(const NameString& name,
	const DisplayModeList& supportedDisplayModes, const Uint32 currentDisplayModeIndex)
	: _name(name.c_str()),
	  _supportedDisplayModes(supportedDisplayModes),
	  _currentDisplayModeIndex(currentDisplayModeIndex),
	  _initialDisplayModeIndex(currentDisplayModeIndex) { }

GraphicsAdapter::Implementation::~Implementation()
{
	if(_currentDisplayModeIndex != _initialDisplayModeIndex)
		changeDisplayMode(nullptr, 0u);
}

String8 GraphicsAdapter::Implementation::name() const
{
	return fromWideString(_name);
}

void GraphicsAdapter::Implementation::setDisplayMode(const DisplayMode& mode)
{
	DisplayModeList::const_iterator iterator =
		std::find(_supportedDisplayModes.begin(), _supportedDisplayModes.end(), mode);

	DE_ASSERT(iterator != _supportedDisplayModes.end());
	DEVMODEW displayModeInfo = ::createDisplayModeInfo(mode);
	changeDisplayMode(&displayModeInfo, CDS_FULLSCREEN);
	_currentDisplayModeIndex = static_cast<Uint32>(iterator - _supportedDisplayModes.begin());
}

// Private

void GraphicsAdapter::Implementation::changeDisplayMode(DEVMODEW* displayModeInfo, const Uint32 flags) const
{
	const Int32 result = ChangeDisplaySettingsExW(_name.c_str(), displayModeInfo, nullptr, flags, nullptr);

	if(result != DISP_CHANGE_SUCCESSFUL)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
			"Failed to change the display mode, ChangeDisplaySettingsEx returned " << result << '.' <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}


// Graphics::GraphicsAdapter

// Public

const DisplayMode& GraphicsAdapter::currentDisplayMode() const
{
	return _implementation->currentDisplayMode();
}

String8 GraphicsAdapter::name() const
{
	return _implementation->name();
}

void GraphicsAdapter::setDisplayMode(const DisplayMode& mode) const
{
	_implementation->setDisplayMode(mode);
}

const DisplayModeList& GraphicsAdapter::supportedDisplayModes() const
{
	return _implementation->supportedDisplayModes();
}

// Private

GraphicsAdapter::GraphicsAdapter(Implementation* implementation)
	: _implementation(implementation) { }

GraphicsAdapter::~GraphicsAdapter()
{
	DE_DELETE(_implementation, Implementation);
}


// External

static DEVMODEW createDisplayModeInfo(const DisplayMode& mode)
{
	DEVMODEW displayModeInfo = DEVMODEW();
	displayModeInfo.dmBitsPerPel = mode.colourDepth();
	displayModeInfo.dmDisplayFrequency = mode.refreshRate();
	displayModeInfo.dmFields = DM_BITSPERPEL | DM_DISPLAYFREQUENCY | DM_PELSHEIGHT | DM_PELSWIDTH;
	displayModeInfo.dmPelsHeight = mode.height();
	displayModeInfo.dmPelsWidth = mode.width();
	displayModeInfo.dmSize = sizeof(DEVMODEW);

	return displayModeInfo;
}
