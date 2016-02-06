/**
 * @file platform/windows/WindowsIcon.cpp
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

#include <utility>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Types.h>
#include <core/debug/Assert.h>
#include <graphics/Image.h>
#include <graphics/ImageFormat.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsIcon.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::Icon - Windows] ";

static void checkImageFormat(const ImageFormat& format);
static BITMAPV5HEADER createBitmapHeader(const Image* image);
static HBITMAP createColourBitmap(const BITMAPV5HEADER& bitmapHeader, Uint8*& dataBuffer);
static ICONINFO createIconInfo(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle);
static HBITMAP createMaskBitmap(const Image* image);
static void destroyBitmap(HBITMAP bitmapHandle);
static HDC getDeviceContext();
static Uint32 getImageBitDepth(const ImageFormat& imageFormat);
static void releaseDeviceContext(HDC deviceContextHandle);
static void setBitmapData(const Image* image, Uint8* dataBuffer);
static void setColourBitmapData(const Image* image, Uint8* dataBuffer, const Bool hasAlpha);
static void setGreyBitmapData(const Image* image, Uint8* dataBuffer, const Bool hasAlpha);


// Public

Icon::Icon()
	: _iconHandle(nullptr) { }

Icon::Icon(const Image* image)
	: Icon()
{
	DE_ASSERT(image != nullptr);
	checkImageFormat(image->format());
	BITMAPV5HEADER bitmapHeader = ::createBitmapHeader(image);
	Uint8* bitmapDataBuffer;
	HBITMAP colourBitmapHandle = ::createColourBitmap(bitmapHeader, bitmapDataBuffer);
	::setBitmapData(image, bitmapDataBuffer);
	HBITMAP maskBitmapHandle = ::createMaskBitmap(image);
	createIcon(colourBitmapHandle, maskBitmapHandle);
	::destroyBitmap(maskBitmapHandle);
	::destroyBitmap(colourBitmapHandle);
}

Icon::Icon(Icon&& icon)
	: _iconHandle(icon._iconHandle)
{
	icon._iconHandle = nullptr;
}

Icon::~Icon()
{
	if(_iconHandle != nullptr)
	{
		const Int32 result = DestroyIcon(_iconHandle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to destroy the icon." << Log::Flush();
			DE_ERROR_WINDOWS(0x0);
		}
	}
}

Icon& Icon::operator =(Icon&& icon)
{
	std::swap(_iconHandle, icon._iconHandle);
	return *this;
}

// Private

void Icon::createIcon(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle)
{
	ICONINFO iconInfo = ::createIconInfo(colourBitmapHandle, maskBitmapHandle);
	_iconHandle = CreateIconIndirect(&iconInfo);

	if(_iconHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the icon." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}


// External

static void checkImageFormat(const ImageFormat& format)
{
	switch(format)
	{
		case ImageFormat::R8:
		case ImageFormat::RA8:
		case ImageFormat::RGB8:
		case ImageFormat::RGBA8:
			break;

		default:
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "The image format is invalid." <<
				Log::Flush();

			DE_ERROR(0x0);
	}
}

static BITMAPV5HEADER createBitmapHeader(const Image* image)
{
	BITMAPV5HEADER bitmapHeader = BITMAPV5HEADER();
	bitmapHeader.bV5AlphaMask = 0xFF000000;
	bitmapHeader.bV5BitCount = static_cast<Uint16>(::getImageBitDepth(image->format()));
	bitmapHeader.bV5BlueMask = 0x000000FF;
	bitmapHeader.bV5Compression = bitmapHeader.bV5BitCount == 24u ? BI_RGB : BI_BITFIELDS;
	bitmapHeader.bV5CSType = LCS_WINDOWS_COLOR_SPACE;
	bitmapHeader.bV5GreenMask = 0x0000FF00;
	bitmapHeader.bV5Height = -static_cast<Int32>(image->height());
	bitmapHeader.bV5Planes = 1u;
	bitmapHeader.bV5RedMask = 0x00FF0000;
	bitmapHeader.bV5Size = sizeof(BITMAPV5HEADER);
	bitmapHeader.bV5Width = image->width();

	return bitmapHeader;
}

static HBITMAP createColourBitmap(const BITMAPV5HEADER& bitmapHeader, Uint8*& dataBuffer)
{
	HDC deviceContextHandle = ::getDeviceContext();
	const BITMAPINFO* bitmapInfo = reinterpret_cast<const BITMAPINFO*>(&bitmapHeader);

	HBITMAP bitmapHandle =
		CreateDIBSection(deviceContextHandle, bitmapInfo, DIB_RGB_COLORS,
			reinterpret_cast<Void**>(&dataBuffer), nullptr, 0u);

	if(bitmapHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the colour bitmap." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	::releaseDeviceContext(deviceContextHandle);
	return bitmapHandle;
}

static ICONINFO createIconInfo(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle)
{
	ICONINFO iconInfo = ICONINFO();
	iconInfo.fIcon = TRUE;
	iconInfo.hbmColor = colourBitmapHandle;
	iconInfo.hbmMask = maskBitmapHandle;

	return iconInfo;
}

static HBITMAP createMaskBitmap(const Image* image)
{
	HBITMAP bitmapHandle = CreateBitmap(image->width(), image->height(), 1u, 1u, nullptr);

	if(bitmapHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the mask bitmap." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return bitmapHandle;
}

static void destroyBitmap(HBITMAP bitmapHandle)
{
	const Int32 result = DeleteObject(bitmapHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to destroy a bitmap." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
}

static HDC getDeviceContext()
{
	HDC deviceContextHandle = GetDC(nullptr);

	if(deviceContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get a device context." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return deviceContextHandle;
}

static Uint32 getImageBitDepth(const ImageFormat& imageFormat)
{
	switch(imageFormat)
	{
		case ImageFormat::R8:
		case ImageFormat::RGB8:
			return 24u;

		case ImageFormat::RA8:
		case ImageFormat::RGBA8:
			return 32u;

		default:
			return 0u;
	}
}

static void releaseDeviceContext(HDC deviceContextHandle)
{
	const Int32 result = ReleaseDC(nullptr, deviceContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to release the device context." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
}

static void setBitmapData(const Image* image, Uint8* dataBuffer)
{
	const ImageFormat imageFormat = image->format();

	switch(imageFormat)
	{
		case ImageFormat::R8:
		case ImageFormat::RA8:
			::setGreyBitmapData(image, dataBuffer, imageFormat == ImageFormat::RA8);
			break;

		case ImageFormat::RGB8:
		case ImageFormat::RGBA8:
			::setColourBitmapData(image, dataBuffer, imageFormat == ImageFormat::RGBA8);
			break;

		default:
			break;
	}
}

static void setColourBitmapData(const Image* image, Uint8* dataBuffer, const Bool hasAlpha)
{
	const Uint32 pixelCount = image->width() * image->height();
	const Uint32 componentCount = hasAlpha ? 4u : 3u;
	const ByteList& imageData = image->data();

	for(Uint32 i = 0u; i < pixelCount; ++i)
	{
		dataBuffer[componentCount * i]		= imageData[componentCount * i + 2u];
		dataBuffer[componentCount * i + 1u] = imageData[componentCount * i + 1u];
		dataBuffer[componentCount * i + 2u] = imageData[componentCount * i];

		if(hasAlpha)
			dataBuffer[componentCount * i + 3u] = imageData[componentCount * i + 3u];
	}
}

static void setGreyBitmapData(const Image* image, Uint8* dataBuffer, const Bool hasAlpha)
{
	const Uint32 pixelCount = image->width() * image->height();
	const Uint32 sourceComponentCount = hasAlpha ? 2u : 1u;
	const Uint32 destinationComponentCount = hasAlpha ? 4u : 3u;
	const ByteList& imageData = image->data();

	for(Uint32 i = 0u; i < pixelCount; ++i)
	{
		const Uint8 greyComponent = imageData[sourceComponentCount * i];
		dataBuffer[destinationComponentCount * i]	   = greyComponent;
		dataBuffer[destinationComponentCount * i + 1u] = greyComponent;
		dataBuffer[destinationComponentCount * i + 2u] = greyComponent;

		if(hasAlpha)
			dataBuffer[destinationComponentCount * i + 3u] = imageData[sourceComponentCount * i + 1u];
	}
}
