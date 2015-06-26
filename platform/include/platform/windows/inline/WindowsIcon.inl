/**
 * @file platform/windows/inline/WindowsIcon.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

const HICON Icon::handle() const
{
	return _iconHandle;
}

// Operators

Icon& Icon::operator =(Icon&& icon)
{
	std::swap(_iconHandle, icon._iconHandle);
	return *this;
}
