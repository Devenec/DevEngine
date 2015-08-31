/**
 * @file core/memory/inline/STDAllocator.inl
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

template<typename T, typename AllocationPolicy>
template<typename U>
STDAllocator<T, AllocationPolicy>::STDAllocator(const STDAllocator<U, AllocationPolicy>& stdAllocator)
{
	static_cast<Void>(stdAllocator);
}

template<typename T, typename AllocationPolicy>
template<typename U, typename OtherAllocationPolicy>
STDAllocator<T, AllocationPolicy>::STDAllocator(const STDAllocator<U, OtherAllocationPolicy>& stdAllocator)
{
	static_cast<Void>(stdAllocator);
}

template<typename T, typename AllocationPolicy>
T* STDAllocator<T, AllocationPolicy>::allocate(const Uint32 objectCount)
{
	return static_cast<T*>(AllocationPolicy::allocate(objectCount * sizeof(T)));
}

template<typename T, typename AllocationPolicy>
template<typename U, typename... Parameters>
void STDAllocator<T, AllocationPolicy>::construct(U* pointer, Parameters&&... parameters)
{
	::new (reinterpret_cast<Void*>(pointer)) U(std::forward<Parameters>(parameters)...);
}

template<typename T, typename AllocationPolicy>
void STDAllocator<T, AllocationPolicy>::deallocate(T* pointer, const Uint32 objectCount)
{
	AllocationPolicy::deallocate(pointer, objectCount * sizeof(T));
}

template<typename T, typename AllocationPolicy>
template<typename U>
void STDAllocator<T, AllocationPolicy>::destroy(U* pointer)
{
	static_cast<Void>(pointer);
	pointer->~U();
}


// Memory

template<typename T, typename U, typename AllocationPolicy>
Bool operator ==(const STDAllocator<T, AllocationPolicy>& stdAllocatorA,
	const STDAllocator<U, AllocationPolicy>& stdAllocatorB)
{
	static_cast<Void>(stdAllocatorA);
	static_cast<Void>(stdAllocatorB);

	return true;
}

template<typename T, typename U, typename AllocationPolicy, typename OtherAllocator>
Bool operator ==(const STDAllocator<T, AllocationPolicy>& stdAllocator, const OtherAllocator& allocator)
{
	static_cast<Void>(stdAllocator);
	static_cast<Void>(allocator);

	return true;
}

template<typename T, typename U, typename AllocationPolicy>
Bool operator !=(const STDAllocator<T, AllocationPolicy>& stdAllocatorA,
	const STDAllocator<U, AllocationPolicy>& stdAllocatorB)
{
	return !operator ==(stdAllocatorA, stdAllocatorB);
}

template<typename T, typename U, typename AllocationPolicy, typename OtherAllocator>
Bool operator !=(const STDAllocator<T, AllocationPolicy>& stdAllocator, const OtherAllocator& allocator)
{
	return !operator ==(stdAllocator, allocator);
}
