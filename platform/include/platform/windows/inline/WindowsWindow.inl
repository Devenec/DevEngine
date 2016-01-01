/**
 * @file platform/windows/inline/WindowsWindow.inl
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

// Public

void Window::Implementation::close()
{
	_isOpen = false;
}

HWND Window::Implementation::handle() const
{
	return _windowHandle;
}

void Window::Implementation::hide() const
{
	ShowWindow(_windowHandle, SW_HIDE);
}

Bool Window::Implementation::isFullscreen() const
{
	return _isFullscreen;
}

void Window::Implementation::setPointerVisibility(const Bool isPointerVisible)
{
	_isPointerVisible = isPointerVisible;
}

Bool Window::Implementation::shouldClose() const
{
	return !_isOpen;
}

void Window::Implementation::show() const
{
	ShowWindow(_windowHandle, SW_SHOW);
}
