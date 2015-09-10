/**
 * @file platform/opengl/OpenGLUniformBuffer.cpp
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

#include <graphics/UniformBuffer.h>
#include <platform/opengl/OpenGLGraphicsBuffer.h>

using namespace Graphics;

// Public

UniformBuffer::UniformBuffer(const Uint32 size, const AccessMode& accessMode)
	: Base(size, accessMode) { }

void UniformBuffer::bind(const Uint32 bindingIndex) const
{
	_impl->bindAsUniformBuffer(bindingIndex);
}

void UniformBuffer::debind(const Uint32 bindingIndex) const
{
	debindAsUniformBuffer(bindingIndex);
}
