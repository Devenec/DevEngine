/**
 * @file platform/windows/inline/WindowsWindow.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
