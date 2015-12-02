/**
 * @file platform/x/X.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <core/Singleton.h>

namespace Platform
{
	class X : public Core::Singleton<X>
	{
	public:

		X();

		X(const X& x) = delete;
		X(X&& x) = delete;

		~X();

		inline Display* connection() const;

		X& operator =(const X& x) = delete;
		X& operator =(X&& x) = delete;

	private:

		Display* _connection;
	};

#include "inline/X.inl"
}
