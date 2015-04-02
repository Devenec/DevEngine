/**
 * @file core/inline/Singleton.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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
	DE_ASSERT(_instance == nullptr);
	_instance = static_cast<T*>(this);
}

template<typename T>
Singleton<T>::~Singleton()
{
	_instance = nullptr;
}
