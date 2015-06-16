/**
 * @file core/Memory.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <new>
#include <core/ConfigMacros.h>
#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if DE_BUILD == DE_BUILD_PRODUCTION || !defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define DE_ALLOCATE(byteCount) \
		Core::allocateMemory(byteCount)
#else
	#define DE_ALLOCATE(byteCount) \
		Core::allocateMemory(byteCount, DE_FILE, DE_LINE, DE_FUNCTION)
#endif

#define DE_DEALLOCATE(pointer) \
	Core::deallocateMemory(pointer)

#define DE_DELETE(pointer, T) \
	if((pointer) != nullptr) { (pointer)->~T(); \
		Core::deallocateMemory(pointer); }

#define DE_DELETE_ARRAY(pointer, T, byteCount) \
	if((pointer) != nullptr) { Core::destructArray<T>(pointer, byteCount); \
		Core::deallocateMemory(pointer, byteCount); }

#if DE_BUILD == DE_BUILD_PRODUCTION || !defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define DE_NEW(T) \
		new (Core::allocateMemory(sizeof(T))) T

	#define DE_NEW_ARRAY(T, byteCount) \
		Core::constructArray(static_cast<T*>(Core::allocateMemory(sizeof(T) * (byteCount))), byteCount)
#else
	#define DE_NEW(T) \
		new (Core::allocateMemory(sizeof(T), DE_FILE, DE_LINE, DE_FUNCTION)) T

	#define DE_NEW_ARRAY(T, byteCount) \
		Core::constructArray(static_cast<T*>(Core::allocateMemory(sizeof(T) * (byteCount), DE_FILE, DE_LINE, \
			DE_FUNCTION)), byteCount)
#endif

namespace Core
{
	Void* allocateMemory(const Uint32 byteCount);

#if DE_BUILD != DE_BUILD_PRODUCTION && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	Void* allocateMemory(const Uint32 byteCount, const Char8* file, const Uint32 line, const Char8* function);
#endif

	void deallocateMemory(Void* pointer, const Uint32 byteCount = 0u);

	template<typename T>
	inline T* constructArray(T* pointer, const Uint32 size);

	template<typename T>
	inline void destructArray(T* pointer, const Uint32 size);

#include "inline/Memory.inl"
}
