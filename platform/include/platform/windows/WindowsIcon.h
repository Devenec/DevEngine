/**
 * @file platform/windows/WindowsIcon.h
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

#include <utility>
#include <core/Types.h>
#include <platform/windows/Windows.h>

namespace Graphics
{
	enum class ImageFormat;
	class Image;
}

namespace Platform
{
	class Icon final
	{
	public:

		Icon();

		explicit Icon(const Graphics::Image* image);

		Icon(const Icon& icon) = delete;

		Icon(Icon&& icon);

		~Icon();

		inline const HICON handle() const;

		Icon& operator =(const Icon& icon) = delete;

		inline Icon& operator =(Icon&& icon);

	private:

		HICON _iconHandle;

		void createIcon(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle);
	};

#include "inline/WindowsIcon.inl"
}
