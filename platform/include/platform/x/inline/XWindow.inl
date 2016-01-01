/**
 * @file platform/x/inline/XWindow.inl
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

// Public

void Graphics::Window::Implementation::close()
{
	_isOpen = false;
}

::Window Graphics::Window::Implementation::handle() const
{
	return _windowHandle;
}

void Graphics::Window::Implementation::hide() const
{
	Platform::X::instance().hideWindow(_windowHandle);
}

Bool Graphics::Window::Implementation::isFullscreen() const
{
	return _isFullscreen;
}

void Graphics::Window::Implementation::setPointerVisibility(const Bool isPointerVisible)
{
	const Cursor pointerHandle = isPointerVisible ? None : _hiddenPointerHandle;
	Platform::X::instance().setPointer(_windowHandle, pointerHandle);
}

Bool Graphics::Window::Implementation::shouldClose() const
{
	return !_isOpen;
}

void Graphics::Window::Implementation::show() const
{
	Platform::X::instance().showWindow(_windowHandle);
}
