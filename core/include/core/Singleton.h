/**
 * @file core/Singleton.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/debug/Assert.h>
#include <core/Types.h>

namespace Core
{
	template<typename T>
	class Singleton
	{
	public:

		static inline Bool hasInstance();

		static inline T& instance();

		static inline T* instancePointer();

	protected:

		static T* _instance;

		Singleton();

		~Singleton();

	private:

		Singleton(const Singleton& singleton) = delete;
		Singleton(Singleton&& singleton) = delete;

		Singleton& operator =(const Singleton& singleton) = delete;
	};

#include "Singleton.inl"
}
