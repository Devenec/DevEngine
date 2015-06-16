/**
 * @file platform/windows/inline/WindowsIcon.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

Icon::Icon()
	: _iconHandle(nullptr) { }

Icon::Icon(Icon&& icon)
	: _iconHandle(icon._iconHandle)
{
	icon._iconHandle = nullptr;
}

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
