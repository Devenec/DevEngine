/**
 * @file core/inline/Singleton.inl
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

// Static

template<typename T>
Bool Singleton<T>::hasInstance()
{
	return _instance != nullptr;
}

template<typename T>
T& Singleton<T>::instance()
{
	DE_ASSERT(_instance != nullptr);
	return *_instance;
}

// Protected

template<typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
Singleton<T>::Singleton()
{
	DE_ASSERT(_instance == nullptr);
	_instance = static_cast<T*>(this);
}

template<typename T>
Singleton<T>::~Singleton()
{
	_instance = nullptr;
}
