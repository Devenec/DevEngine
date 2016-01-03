/**
 * @file platform/x/inline/X.inl
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

Atom X::createAtom(const Char8* name) const
{
	return XInternAtom(_connection, name, False);
}

void X::destroyGraphicsContext(GLX::Context contextHandle) const
{
	GLX::destroyContext(_connection, contextHandle);
}

void X::destroyPointer(const Cursor pointerHandle) const
{
	XFreeCursor(_connection, pointerHandle);
}

void X::destroyWindow(const Window windowHandle) const
{
	XDestroyWindow(_connection, windowHandle);
}

const Char8* X::getExtensionNameString() const
{
	return GLX::queryExtensionsString(_connection, GRAPHICS_ADAPTER_INDEX);
}

Uint32 X::getGraphicsAdapterCount() const
{
	return XScreenCount(_connection);
}

Int16* X::getGraphicsAdapterRefreshRates(const Uint32 adapterIndex, const Uint32 resolutionIndex,
	Uint32& rateCount) const
{
	return XRRRates(_connection, adapterIndex, resolutionIndex, reinterpret_cast<Int32*>(&rateCount));
}

XRRScreenSize* X::getGraphicsAdapterResolutions(const Uint32 adapterIndex, Uint32& resolutionCount) const
{
	return XRRSizes(_connection, adapterIndex, reinterpret_cast<Int32*>(&resolutionCount));
}

Window X::getRootWindowHandle(const Uint32 graphicsAdapterIndex) const
{
	return XRootWindow(_connection, graphicsAdapterIndex);
}

Bool X::hasPendingEvents() const
{
	return XPending(_connection) > 0;
}

void X::hideWindow(const Window windowHandle) const
{
	XUnmapWindow(_connection, windowHandle);
}

Bool X::isGraphicsContextDirect(GLX::Context contextHandle) const
{
	return GLX::isDirect(_connection, contextHandle) != 0;
}

void X::setWindowPointer(const Window windowHandle, const Cursor pointerHandle) const
{
	XDefineCursor(_connection, windowHandle, pointerHandle);
}

void X::showWindow(const Window windowHandle) const
{
	XMapWindow(_connection, windowHandle);
}

void X::swapBuffers(GLX::Drawable drawableHandle) const
{
	GLX::swapBuffers(_connection, drawableHandle);
}
