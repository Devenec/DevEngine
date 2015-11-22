/**
 * @file core/inline/Memory.inl
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

// Core

template<typename T>
T* constructArray(T* pointer, const Uint32 size)
{
	DE_ASSERT(pointer != nullptr);

	for(Uint32 i = 0u; i < size; ++i)
		new (static_cast<Void*>(pointer + i)) T();

	return pointer;
}

template<typename T>
void destructArray(T* pointer, const Uint32 size)
{
	DE_ASSERT(pointer != nullptr);

	for(Uint32 i = 0u; i < size; ++i)
		pointer[i].~T();
}
