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

#undef Bool

#include <core/ConfigInternal.h>
#include <core/Singleton.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)
	#define DE_ERROR_X(errorCode) \
		Platform::X::instance().invokeError(errorCode, DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_ERROR_X(errorCode) \
		Platform::X::instance().invokeError(errorCode)
#endif

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

		void invokeError(const Uint32 errorCode) const;

		void invokeError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function) const;

		X& operator =(const X& x) = delete;
		X& operator =(X&& x) = delete;

	private:

		Display* _connection;

		void checkConnection() const;
		void checkXRandRSupport() const;
	};

#include "inline/X.inl"
}
