/**
 * @file platform/wgl/WGLGraphicsDeviceFactory.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/Window.h>
#include <platform/opengl/OpenGLGraphicsDevice.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContext.h>
#include <platform/wgl/WGLGraphicsDeviceFactory.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

using PixelFormatRequiredAttributeList = Array<Int32, 9u>;

static const Char8* COMPONENT_TAG = "[Platform::GraphicsDeviceFactory - WGL]";

static const PixelFormatRequiredAttributeList PIXEL_FORMAT_REQUIRED_ATTRIBUTES
{{
	WGL::DOUBLE_BUFFER_ARB,	 1,
	WGL::DRAW_TO_WINDOW_ARB, 1,
	WGL::PIXEL_TYPE_ARB,	 WGL::TYPE_RGBA_ARB,
	WGL::SUPPORT_OPENGL_ARB, 1,
	0
}};

static Bool isPixelFormatAccelerationLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB);

static Bool isPixelFormatLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB);


// Public

GraphicsDeviceFactory::GraphicsDeviceFactory()
	: _deviceContextHandle(nullptr) { }

GraphicsDevice* GraphicsDeviceFactory::createDevice(Window* window, GraphicsConfig& chosenGraphicsConfig)
{
	HWND windowHandle = static_cast<HWND>(window->handle());
	_deviceContextHandle = getWindowDeviceContextHandle(windowHandle);
	const Int32 pixelFormatIndex = chooseGraphicsConfig(chosenGraphicsConfig);
	GraphicsContext* graphicsContext = createGraphicsContext(windowHandle, pixelFormatIndex);

	return createDeviceObject(window, graphicsContext);
}

// Static

void GraphicsDeviceFactory::logDeviceInfo(GraphicsDevice* graphicsDevice)
{
	graphicsDevice->_implementation->logInfo();
}

// Private

const PixelFormatAttributeList GraphicsDeviceFactory::PIXEL_FORMAT_ATTRIBUTE_IDS
{{
	WGL::ACCELERATION_ARB,
	WGL::ALPHA_BITS_ARB,
	WGL::BLUE_BITS_ARB,
	WGL::DEPTH_BITS_ARB,
	WGL::GREEN_BITS_ARB,
	WGL::RED_BITS_ARB,
	WGL::STENCIL_BITS_ARB
}};

Int32 GraphicsDeviceFactory::chooseGraphicsConfig(GraphicsConfig& chosenConfig) const
{
	const Uint32 pixelFormatCount = getPixelFormatCount();
	const PixelFormatIndexList pixelFormatIndices = getPixelFormatIndices(pixelFormatCount);
	PixelFormatAttributeList pixelFormatAttributes;
	const Int32 pixelFormatIndex = chooseBestPixelFormat(pixelFormatIndices, pixelFormatAttributes);

	chosenConfig = GraphicsConfig(pixelFormatAttributes[5], pixelFormatAttributes[4], pixelFormatAttributes[2],
		pixelFormatAttributes[1], pixelFormatAttributes[3], pixelFormatAttributes[6]);

	return pixelFormatIndex;
}

GraphicsContext* GraphicsDeviceFactory::createGraphicsContext(HWND windowHandle, const Int32 pixelFormatIndex) const
{
	GraphicsContext::Implementation* implementation =
		DE_NEW(GraphicsContext::Implementation)(windowHandle, pixelFormatIndex);

	return DE_NEW(GraphicsContext)(implementation);
}

GraphicsDevice* GraphicsDeviceFactory::createDeviceObject(Window* window, GraphicsContext* graphicsContext) const
{
	GraphicsDevice::Implementation* implementation = DE_NEW(GraphicsDevice::Implementation)(graphicsContext);
	return DE_NEW(GraphicsDevice)(implementation, window);
}

Uint32 GraphicsDeviceFactory::getPixelFormatCount() const
{
	const Int32 attributeName = WGL::NUMBER_PIXEL_FORMATS_ARB;
	Int32 formatCount;
	const Int32 result = WGL::getPixelFormatAttribivARB(_deviceContextHandle, 0, 0, 1u, &attributeName, &formatCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get the number of configurations." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return formatCount;
}

GraphicsDeviceFactory::PixelFormatIndexList GraphicsDeviceFactory::getPixelFormatIndices(const Uint32 formatCount)
	const
{
	PixelFormatIndexList formatIndices(formatCount);
	Uint32 matchingFormatCount;

	const Int32 result = WGL::choosePixelFormatARB(_deviceContextHandle, ::PIXEL_FORMAT_REQUIRED_ATTRIBUTES.data(),
		nullptr, formatCount, formatIndices.data(), &matchingFormatCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get matching configurations." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}
	else if(matchingFormatCount == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " No matching configurations were found." << Log::Flush();
		DE_ERROR(0x0);
	}

	formatIndices.resize(matchingFormatCount);
	return formatIndices;
}

Int32 GraphicsDeviceFactory::chooseBestPixelFormat(const PixelFormatIndexList& formatIndices,
	PixelFormatAttributeList& formatAttributes) const
{
	Int32 bestFormatIndex = formatIndices.front();
	formatAttributes = getPixelFormatAttributes(bestFormatIndex);

	for(PixelFormatIndexList::const_iterator i = formatIndices.begin() + 1u, end = formatIndices.end(); i != end; ++i)
	{
		const PixelFormatAttributeList compareFormatAttributes = getPixelFormatAttributes(*i);

		if(::isPixelFormatLess(formatAttributes, compareFormatAttributes))
		{
			bestFormatIndex = *i;
			formatAttributes = compareFormatAttributes;
		}
	}

	return bestFormatIndex;
}

PixelFormatAttributeList GraphicsDeviceFactory::getPixelFormatAttributes(const Int32 formatIndex) const
{
	PixelFormatAttributeList attributes;

	const Int32 result = WGL::getPixelFormatAttribivARB(_deviceContextHandle, formatIndex, 0, attributes.size(),
		PIXEL_FORMAT_ATTRIBUTE_IDS.data(), attributes.data());

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get configuration attributes." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return attributes;
}


// External

static Bool isPixelFormatAccelerationLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB)
{
	return formatAttributesA[0] == WGL::NO_ACCELERATION_ARB ||
		(formatAttributesA[0] == WGL::GENERIC_ACCELERATION_ARB && formatAttributesB[0] == WGL::FULL_ACCELERATION_ARB);
}

static Bool isPixelFormatLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB)
{
	if(formatAttributesA[0] != formatAttributesB[0])
	{
		return ::isPixelFormatAccelerationLess(formatAttributesA, formatAttributesB);
	}
	else
	{
		return
			formatAttributesA[1] < formatAttributesB[1] ||
			formatAttributesA[2] < formatAttributesB[2] ||
			formatAttributesA[3] < formatAttributesB[3] ||
			formatAttributesA[4] < formatAttributesB[4] ||
			formatAttributesA[5] < formatAttributesB[5] ||
			formatAttributesA[6] < formatAttributesB[6];
	}
}
