/**
 * @file platform/x/XGraphicsAdapter.cpp
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
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <platform/x/XGraphicsAdapter.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

// Public

GraphicsAdapter::Implementation::Implementation(const Uint32 adapterIndex, const String8& name,
	const DisplayModeList& supportedDisplayModes, const Uint32 currentDisplayModeIndex)
	: _name(name),
	  _supportedDisplayModes(supportedDisplayModes),
	  _config(nullptr),
	  _configTimestamp(0u),
	  _adapterIndex(adapterIndex),
	  _currentDisplayModeIndex(currentDisplayModeIndex),
	  _initialDisplayModeIndex(currentDisplayModeIndex)
{
	Display* xConnection = X::instance().connection();
	Window rootWindow = XRootWindow(xConnection, adapterIndex);
	_config = XRRGetScreenInfo(xConnection, rootWindow);
	XRRConfigTimes(_config, &_configTimestamp);
}

GraphicsAdapter::Implementation::~Implementation()
{
	if(_currentDisplayModeIndex != _initialDisplayModeIndex)
		changeDisplayMode(_initialDisplayModeIndex);

	XRRFreeScreenConfigInfo(_config);
}

void GraphicsAdapter::Implementation::setDisplayMode(const DisplayMode& mode)
{
	DisplayModeList::const_iterator iterator = std::find(_supportedDisplayModes.begin(),
		_supportedDisplayModes.end(), mode);

	DE_ASSERT(iterator != _supportedDisplayModes.end());
	const Uint32 modeIndex = iterator - _supportedDisplayModes.begin();
	changeDisplayMode(modeIndex);
	_currentDisplayModeIndex = modeIndex;
}

// Private

void GraphicsAdapter::Implementation::changeDisplayMode(const Uint32 modeIndex) const
{
	Display* xConnection = X::instance().connection();
	const DisplayMode& mode = _supportedDisplayModes[modeIndex];

	XRRSetScreenConfigAndRate(xConnection, _config, _adapterIndex, modeIndex, RR_Rotate_0,
		static_cast<Int16>(mode.refreshRate()), _configTimestamp);

	// TODO: check return value?
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
