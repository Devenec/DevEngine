/**
 * @file core/Memory.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_MALLOC(byteCount) \
		Core::allocate(byteCount)
#else
	#define DE_MALLOC(byteCount) \
		Core::allocate(byteCount, DE_FILE, DE_LINE, DE_FUNCTION)
#endif

#define DE_DELETE(pointer, T) \
	if((pointer) != nullptr) { (pointer)->~T(); Core::deallocate(pointer); }

#define DE_DELETE_ARRAY(pointer, T, byteCount) \
	if((pointer) != nullptr) { Core::destructArray<T>(pointer, byteCount); Core::deallocate(pointer); }

#define DE_FREE(pointer) \
	Core::deallocate(pointer)

#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_NEW(T) \
		new (Core::allocate(sizeof(T)) T

	#define DE_NEW_ARRAY(T, byteCount) \
		Core::constructArray(static_cast<T*>(Core::allocate(sizeof(T) * (byteCount))), byteCount)
#else
	#define DE_NEW(T) \
		new (Core::allocate(sizeof(T), DE_FILE, DE_LINE, DE_FUNCTION)) T

	#define DE_NEW_ARRAY(T, byteCount) \
		Core::constructArray(static_cast<T*>(Core::allocate(sizeof(T) * (byteCount), DE_FILE, DE_LINE, DE_FUNCTION)), \
			byteCount)
#endif

namespace Core
{
	Void* allocate(const Uint32 size);

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	Void* allocate(const Uint32 size, const Char8* file, const Uint32 line, const Char8* function);
#endif

	template<typename T>
	T* constructArray(T* pointer, const Uint32 size)
	{
		for(Uint32 i = 0u; i < size; ++i)
			new (pointer + i) T();

		return pointer;
	}

	void deallocate(Void* pointer);

	template<typename T>
	void destructArray(T* pointer, const Uint32 size)
	{
		for(Uint32 i = 0u; i < size; ++i)
			pointer[i].~T();
	}
}
