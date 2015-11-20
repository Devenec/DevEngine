/**
 * @file platform/opengl/OpenGLGraphicsDevice.inl
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

void GraphicsDevice::Impl::setEffect(Effect* effect)
{
	_activeEffect = effect;
}

void GraphicsDevice::Impl::setVertexBufferState(VertexBufferState* vertexBufferState)
{
	_activeVertexBufferState = vertexBufferState;
}

const Viewport& GraphicsDevice::Impl::viewport() const
{
	return _viewport;
}
