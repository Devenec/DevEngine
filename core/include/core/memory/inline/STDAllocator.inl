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
	static_cast<Void>(pointer); // TODO: find out why removing this invokes a warning
	pointer->~U();
}

// Operators

template<typename T, typename AllocationPolicy>
template<typename U>
Bool STDAllocator<T, AllocationPolicy>::operator ==(const STDAllocator<U, AllocationPolicy>& stdAllocator) const
{
	static_cast<Void>(stdAllocator);
	return true;
}

template<typename T, typename AllocationPolicy>
template<typename U, typename OtherAllocator>
Bool STDAllocator<T, AllocationPolicy>::operator ==(const OtherAllocator& allocator) const
{
	static_cast<Void>(allocator);
	return false;
}

template<typename T, typename AllocationPolicy>
template<typename U>
Bool STDAllocator<T, AllocationPolicy>::operator !=(const STDAllocator<U, AllocationPolicy>& stdAllocator) const
{
	static_cast<Void>(stdAllocator);
	return false;
}

template<typename T, typename AllocationPolicy>
template<typename U, typename OtherAllocator>
Bool STDAllocator<T, AllocationPolicy>::operator !=(const OtherAllocator& allocator) const
{
	static_cast<Void>(allocator);
	return true;
}
