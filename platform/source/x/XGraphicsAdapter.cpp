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

#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/DisplayMode.h>
#include <platform/x/XGraphicsAdapter.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsAdapter - X]";


// Implementation

// Public

GraphicsAdapter::Implementation::Implementation(const Uint32 adapterIndex, const String8& name,
	const DisplayModeList& supportedDisplayModes, const Uint32 currentDisplayModeIndex, XRRScreenConfiguration* config)
	: _name(name),
	  _supportedDisplayModes(supportedDisplayModes),
	  _config(config),
	  _configTimestamp(0u),
	  _rootWindow(0u),
	  _currentDisplayModeIndex(currentDisplayModeIndex),
	  _initialDisplayModeIndex(currentDisplayModeIndex)
{
	_rootWindow = XRootWindow(X::instance().connection(), adapterIndex);
	XRRConfigTimes(config, &_configTimestamp);
}

GraphicsAdapter::Implementation::~Implementation()
{
	if(_currentDisplayModeIndex != _initialDisplayModeIndex)
		setDisplayMode(_supportedDisplayModes[_initialDisplayModeIndex]);

	XRRFreeScreenConfigInfo(_config);
}

void GraphicsAdapter::Implementation::setDisplayMode(const DisplayMode& mode)
{
	Uint32 resolutionIndex;
	DisplayModeList::const_iterator iterator = findDisplayMode(mode, resolutionIndex);
	DE_ASSERT(iterator != _supportedDisplayModes.end());
	changeDisplayMode(resolutionIndex, iterator->refreshRate());
	_currentDisplayModeIndex = iterator - _supportedDisplayModes.begin();
}

// Private

DisplayModeList::const_iterator GraphicsAdapter::Implementation::findDisplayMode(const DisplayMode& mode,
	Uint32& resolutionIndex) const
{
	DisplayModeList::const_iterator iterator = _supportedDisplayModes.begin();
	DisplayModeList::const_iterator previous = iterator;
	resolutionIndex = 0u;

	for(DisplayModeList::const_iterator end = _supportedDisplayModes.end(); iterator != end; ++iterator)
	{
		if(*iterator == mode)
			break;
		else if(iterator->width() != previous->width() || iterator->height() != previous->height())
			++resolutionIndex;

		previous = iterator;
	}

	return iterator;
}

void GraphicsAdapter::Implementation::changeDisplayMode(const Uint32 resolutionIndex, const Uint32 refreshRate) const
{
	Display* xConnection = X::instance().connection();

	const Int32 result = XRRSetScreenConfigAndRate(xConnection, _config, _rootWindow, resolutionIndex, RR_Rotate_0,
		static_cast<Int16>(refreshRate), _configTimestamp);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to change the display mode." << Log::Flush();
		DE_ERROR_X(0x0);
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
