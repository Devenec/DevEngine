/**
 * @file platform/windows/WindowsIcon.h
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

		static const Char8* COMPONENT_TAG;

		HICON _iconHandle;

		void createIcon(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle);

		static BITMAPV5HEADER createBitmapHeader(const Graphics::Image* image);
		static HBITMAP createColourBitmap(const BITMAPV5HEADER& bitmapHeader, Byte*& dataBuffer);
		static void setBitmapData(const Graphics::Image* image, Byte* dataBuffer);
		static HBITMAP createMaskBitmap(const Graphics::Image* image);
		static void destroyBitmap(HBITMAP bitmapHandle);
		static ICONINFO createIconInfo(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle);
		static Uint32 getBitDepth(const Graphics::ImageFormat& imageFormat);
		static HDC getDeviceContext();
		static void releaseDeviceContext(HDC deviceContextHandle);
		static void setGreyBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha);
		static void setColourBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha);
	};

#include "inline/WindowsIcon.inl"
}
