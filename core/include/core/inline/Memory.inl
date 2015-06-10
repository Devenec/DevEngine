/**
 * @file core/inline/Memory.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Core

template<typename T>
T* constructArray(T* pointer, const Uint32 size)
{
	for(Uint32 i = 0u; i < size; ++i)
		new (pointer + i) T();

	return pointer;
}

template<typename T>
void destructArray(T* pointer, const Uint32 size)
{
	for(Uint32 i = 0u; i < size; ++i)
		pointer[i].~T();
}
