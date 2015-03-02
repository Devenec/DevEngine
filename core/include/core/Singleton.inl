/**
 * @file core/Singleton.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

// Static

template<typename T>
bool Singleton<T>::hasInstance()
{
	return _instance != nullptr;
}

template<typename T>
T& Singleton<T>::instance()
{
	return *_instance;
}

template<typename T>
T* Singleton<T>::instancePointer()
{
	return _instance;
}

// Protected

template<typename T>
T* Singleton<T>::_instance = nullptr;

template<typename T>
Singleton<T>::Singleton()
{
	// TODO: check whether an instance already exists
	_instance = static_cast<T*>(this);
}

template<typename T>
Singleton<T>::~Singleton()
{
	_instance = nullptr;
}
