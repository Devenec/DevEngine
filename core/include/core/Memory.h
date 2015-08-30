/**
 * @file core/Memory.h
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

#pragma once

#include <new>
#include <core/Config.h>
#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)
	#define DE_ALLOCATE(size) \
		Core::allocateMemory(size, DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_ALLOCATE(size) \
		Core::allocateMemory(size)
#endif

#define DE_DEALLOCATE(pointer) \
	Core::deallocateMemory(pointer)

#define DE_DELETE(pointer, T) \
	if((pointer) != nullptr) { (pointer)->~T(); \
		Core::deallocateMemory(pointer); }

#define DE_DELETE_ARRAY(pointer, T, size) \
	if((pointer) != nullptr) { Core::destructArray<T>(pointer, size); \
		Core::deallocateMemory(pointer, size); }

#if defined(DE_INTERNAL_CONFIG_TRACK_ALLOCATIONS)
	#define DE_NEW(T) \
		new (Core::allocateMemory(sizeof(T), DE_FILE, DE_LINE, DE_FUNCTION)) T

	#define DE_NEW_ARRAY(T, size) \
		Core::constructArray(static_cast<T*>(Core::allocateMemory(sizeof(T) * (size), DE_FILE, DE_LINE, \
			DE_FUNCTION)), size)
#else
	#define DE_NEW(T) \
		new (Core::allocateMemory(sizeof(T))) T

	#define DE_NEW_ARRAY(T, size) \
		Core::constructArray(static_cast<T*>(Core::allocateMemory(sizeof(T) * (size))), size)
#endif

namespace Core
{
	Void* allocateMemory(const Uint32 size, const Char8* file = nullptr, const Uint32 line = 0u,
		const Char8* function = nullptr);

	void deallocateMemory(Void* pointer, const Uint32 size = 0u);

	template<typename T>
	T* constructArray(T* pointer, const Uint32 size);

	template<typename T>
	void destructArray(T* pointer, const Uint32 size);

#include "inline/Memory.inl"
}
