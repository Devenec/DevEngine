/**
 * @file graphics/inline/GraphicsAdapter.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

const DisplayMode& GraphicsAdapter::currentDisplayMode() const
{
	return _supportedDisplayModes[_currentDisplayModeIndex];
}

const Core::String8& GraphicsAdapter::name() const
{
	return _name;
}

const DisplayModes& GraphicsAdapter::supportedDisplayModes() const
{
	return _supportedDisplayModes;
}

// Private

GraphicsAdapter::GraphicsAdapter(const Core::String8& name, const DisplayModes& supportedDisplayModes,
	const Uint32 currentDisplayModeIndex)
	: _name(name),
	  _supportedDisplayModes(supportedDisplayModes),
	  _currentDisplayModeIndex(currentDisplayModeIndex) { }
