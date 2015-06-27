/**
 * @file core/Singleton.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>
#include <core/debug/Assert.h>

namespace Core
{
	template<typename T>
	class Singleton
	{
	public:

		Singleton(const Singleton& singleton) = delete;
		Singleton(Singleton&& singleton) = delete;

		Singleton& operator =(const Singleton& singleton) = delete;
		Singleton& operator =(Singleton&& singleton) = delete;

		static inline Bool hasInstance();

		static inline T& instance();

	protected:

		static T* _instance;

		Singleton();

		~Singleton();
	};

#include "inline/Singleton.inl"
}
