/**
 * @file platform/opengl/inline/OpenGLIndexBuffer.inl
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

void IndexBuffer::Implementation::bind() const
{
	bind(_bufferHandle);
}

void IndexBuffer::Implementation::debind() const
{
	bind(0u);
}

Uint8* IndexBuffer::Implementation::mapData() const
{
	return mapData(_size, 0u);
}
