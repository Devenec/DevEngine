/**
 * @file platform/windows/WindowsIcon.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <utility>
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

		inline Icon();

		explicit Icon(const Graphics::Image* image);

		Icon(const Icon& icon) = delete;

		inline Icon(Icon&& icon);

		~Icon();

		inline const HICON handle() const;

		Icon& operator =(const Icon& icon) = delete;

		inline Icon& operator =(Icon&& icon);

	private:

		HICON _iconHandle;

		void create(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle);

		static BITMAPV5HEADER createBitmapHeader(const Graphics::Image* image);
		static HBITMAP createColourBitmap(const BITMAPV5HEADER& bitmapHeader, Byte*& dataBuffer);
		static void setBitmapData(const Graphics::Image* image, Byte* dataBuffer);
		static HBITMAP createMaskBitmap(const Graphics::Image* image);
		static void destroyBitmap(HBITMAP bitmapHandle);
		static Uint32 getBitDepth(const Graphics::ImageFormat& imageFormat);
		static HDC getDeviceContext();
		static void releaseDeviceContext(HDC deviceContextHandle);
		static void setGreyBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha);
		static void setColourBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha);
	};

#include "inline/WindowsIcon.inl"
}
