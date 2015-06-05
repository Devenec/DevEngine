/**
 * @file platform/windows/WindowsGraphicsAdapter.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsAdapter.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// Implementation

class GraphicsAdapter::Impl
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

	void setDisplayMode(const DisplayMode& mode)
	{
		DisplayModeList::const_iterator iterator = std::find(_supportedDisplayModes.begin(),
			_supportedDisplayModes.end(), mode);

		DE_ASSERT(iterator != _supportedDisplayModes.end());
		DEVMODEW displayModeInfo;
		displayModeInfo.dmBitsPerPel = mode.colourDepth();
		displayModeInfo.dmDisplayFrequency = mode.frequency();
		displayModeInfo.dmDriverExtra = 0u;
		displayModeInfo.dmFields = DM_BITSPERPEL | DM_DISPLAYFREQUENCY | DM_PELSHEIGHT | DM_PELSWIDTH;
		displayModeInfo.dmPelsHeight = mode.height();
		displayModeInfo.dmPelsWidth = mode.width();
		displayModeInfo.dmSize = sizeof(displayModeInfo);

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
		DE_ASSERT(result == DISP_CHANGE_SUCCESSFUL);
	}
};


// Public

const DisplayMode& GraphicsAdapter::currentDisplayMode() const
{
	return _impl->currentDisplayMode();
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
	: _impl(DE_NEW Impl(name, supportedDisplayModes, currentDisplayModeIndex)) { }

GraphicsAdapter::~GraphicsAdapter()
{
	DE_DELETE _impl;
}
