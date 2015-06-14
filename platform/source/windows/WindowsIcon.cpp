/**
 * @file platform/windows/WindowsIcon.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Error.h>
#include <core/Log.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <core/debug/Assert.h>
#include <graphics/Image.h>
#include <platform/windows/WindowsIcon.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

static const Char8* ICON_CONTEXT = "[Platform::WindowsIcon]";

// Public

void Icon::initialise(const Image* image)
{
	BITMAPV5HEADER bitmapHeader = createBitmapHeader(image);
	Byte* bitmapDataBuffer;
	HBITMAP colourBitmapHandle = createColourBitmap(bitmapHeader, bitmapDataBuffer);
	setBitmapData(image, bitmapDataBuffer);
	HBITMAP maskBitmapHandle = createMaskBitmap(image);
	create(colourBitmapHandle, maskBitmapHandle);
	destroyBitmap(maskBitmapHandle);
	destroyBitmap(colourBitmapHandle);
}

// Private

void Icon::create(HBITMAP colourBitmapHandle, HBITMAP maskBitmapHandle)
{
	ICONINFO iconInfo = ICONINFO();
	iconInfo.fIcon = TRUE;
	iconInfo.hbmColor = colourBitmapHandle;
	iconInfo.hbmMask = maskBitmapHandle;

	_iconHandle = CreateIconIndirect(&iconInfo);

	if(_iconHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to create the icon." << Log::Flush();
		DE_ERROR_WINDOWS(0x000200);
	}
}

void Icon::destroy() const
{
	const Int32 result = DestroyIcon(_iconHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to destroy the icon." << Log::Flush();
		DE_ERROR_WINDOWS(0x000201);
	}
}

// Static

BITMAPV5HEADER Icon::createBitmapHeader(const Image* image)
{
	BITMAPV5HEADER bitmapHeader = BITMAPV5HEADER();
	bitmapHeader.bV5AlphaMask = 0xFF000000;
	bitmapHeader.bV5BitCount = static_cast<Uint16>(getBitDepth(image->format()));
	bitmapHeader.bV5BlueMask  = 0x000000FF;
	bitmapHeader.bV5CSType = LCS_WINDOWS_COLOR_SPACE;
	bitmapHeader.bV5GreenMask = 0x0000FF00;
	bitmapHeader.bV5Height = -static_cast<Int32>(image->height());
	bitmapHeader.bV5Planes = 1u;
	bitmapHeader.bV5RedMask	  = 0x00FF0000;
	bitmapHeader.bV5Size = sizeof(BITMAPV5HEADER);
	bitmapHeader.bV5Width = image->width();

	if(bitmapHeader.bV5BitCount == 24u)
		bitmapHeader.bV5Compression = BI_RGB;
	else
		bitmapHeader.bV5Compression = BI_BITFIELDS;

	return bitmapHeader;
}

HBITMAP Icon::createColourBitmap(const BITMAPV5HEADER& bitmapHeader, Byte*& dataBuffer)
{
	HDC deviceContextHandle = getDeviceContext();

	HBITMAP bitmapHandle = CreateDIBSection(deviceContextHandle, reinterpret_cast<const BITMAPINFO*>(&bitmapHeader),
		DIB_RGB_COLORS, reinterpret_cast<Void**>(&dataBuffer), nullptr, 0u);

	if(bitmapHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to create the colour bitmap." << Log::Flush();
		DE_ERROR_WINDOWS(0x000202);
	}

	releaseDeviceContext(deviceContextHandle);
	return bitmapHandle;
}

void Icon::setBitmapData(const Graphics::Image* image, Byte* dataBuffer)
{
	const ImageFormat imageFormat = image->format();

	switch(imageFormat)
	{
		case ImageFormat::R8:
		case ImageFormat::RA8:
			setGreyBitmapData(image, dataBuffer, imageFormat == ImageFormat::RA8);
			break;

		case ImageFormat::RGB8:
		case ImageFormat::RGBA8:
			setColourBitmapData(image, dataBuffer, imageFormat == ImageFormat:: RGBA8);
			break;

		default:
			DE_ASSERT(false);
			break;
	}
}

HBITMAP Icon::createMaskBitmap(const Image* image)
{
	HBITMAP bitmapHandle = CreateBitmap(image->width(), image->height(), 1u, 1u, nullptr);

	if(bitmapHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to create the mask bitmap." << Log::Flush();
		DE_ERROR_WINDOWS(0x000203);
	}

	return bitmapHandle;
}

void Icon::destroyBitmap(HBITMAP bitmapHandle)
{
	const Int32 result = DeleteObject(bitmapHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to destroy a bitmap." << Log::Flush();
		DE_ERROR_WINDOWS(0x000204);
	}

}

Uint32 Icon::getBitDepth(const ImageFormat& imageFormat)
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
			DE_ASSERT(false);
			return 0u;
	}
}

HDC Icon::getDeviceContext()
{
	HDC deviceContextHandle = GetDC(nullptr);

	if(deviceContextHandle == nullptr)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to get a device context." << Log::Flush();
		DE_ERROR_WINDOWS(0x000205);
	}

	return deviceContextHandle;
}

void Icon::releaseDeviceContext(HDC deviceContextHandle)
{
	const Int32 result = ReleaseDC(nullptr, deviceContextHandle);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ICON_CONTEXT << " Failed to release the device context." << Log::Flush();
		DE_ERROR_WINDOWS(0x000206);
	}
}

void Icon::setGreyBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha)
{
	const Uint32 pixelCount = image->width() * image->height();
	const Uint32 sourceComponentCount = hasAlpha ? 2u : 1u;
	const Uint32 destinationComponentCount = hasAlpha ? 4u : 3u;
	const Vector<Byte>& imageData = image->data();

	for(Uint32 i = 0u; i < pixelCount; ++i)
	{
		const Byte greyComponent = imageData[sourceComponentCount * i];
		dataBuffer[destinationComponentCount * i]	   = greyComponent;
		dataBuffer[destinationComponentCount * i + 1u] = greyComponent;
		dataBuffer[destinationComponentCount * i + 2u] = greyComponent;

		if(hasAlpha)
			dataBuffer[destinationComponentCount * i + 3u] = imageData[sourceComponentCount * i + 1u];
	}
}

void Icon::setColourBitmapData(const Graphics::Image* image, Byte* dataBuffer, const Bool hasAlpha)
{
	const Uint32 pixelCount = image->width() * image->height();
	const Uint32 componentCount = hasAlpha ? 4u : 3u;
	const Vector<Byte>& imageData = image->data();

	for(Uint32 i = 0u; i < pixelCount; ++i)
	{
		dataBuffer[componentCount * i]		= imageData[componentCount * i + 2u];
		dataBuffer[componentCount * i + 1u] = imageData[componentCount * i + 1u];
		dataBuffer[componentCount * i + 2u] = imageData[componentCount * i];

		if(hasAlpha)
			dataBuffer[componentCount * i + 3u] = imageData[componentCount * i + 3u];
	}
}
