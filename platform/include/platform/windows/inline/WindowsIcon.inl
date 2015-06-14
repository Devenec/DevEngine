/**
 * @file platform/windows/inline/WindowsIcon.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

Icon::Icon()
	: _iconHandle(nullptr) { }

Icon::~Icon()
{
	deinitialise();
}

void Icon::deinitialise()
{
	if(_iconHandle != nullptr)
		destroy();
}

const HICON Icon::handle() const
{
	return _iconHandle;
}
