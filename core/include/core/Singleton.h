/**
 * @file core/Singleton.h
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
