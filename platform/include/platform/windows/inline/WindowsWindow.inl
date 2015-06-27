/**
 * @file platform/windows/inline/WindowsWindow.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

void Window::Impl::close()
{
	_isOpen = false;
}

HWND Window::Impl::handle() const
{
	return _windowHandle;
}

void Window::Impl::hide() const
{
	ShowWindow(_windowHandle, SW_HIDE);
}

Bool Window::Impl::isFullscreen() const
{
	return _isFullscreen;
}

Core::Rectangle Window::Impl::rectangle() const
{
	if(_isFullscreen)
		return getRectangle();
	else
		return _rectangle;
}

void Window::Impl::setCursorVisibility(const Bool isCursorVisible)
{
	_isCursorVisible = isCursorVisible;
}

Bool Window::Impl::shouldClose() const
{
	return _isOpen;
}

void Window::Impl::show() const
{
	ShowWindow(_windowHandle, SW_SHOW);
}
