/**
 * @file platform/wgl/WGLGraphicsConfigChooser.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsConfigChooser.h>

using namespace Core;
using namespace Platform;

// Public

GraphicsConfigChooser::GraphicsConfigChooser(HDC deviceContextHandle)
	: _deviceContextHandle(deviceContextHandle) { }

Int32 GraphicsConfigChooser::chooseConfig() const
{
	const Uint32 pixelFormatCount = getPixelFormatCount();
	const PixelFormatIndexList pixelFormatIndices = getPixelFormatIndices(pixelFormatCount);
	
	return chooseBestPixelFormat(pixelFormatIndices);
}

// Private

const Char8* GraphicsConfigChooser::COMPONENT_TAG = "[Platform::GraphicsConfigChooser - WGL]";

const GraphicsConfigChooser::PixelFormatAttributeList GraphicsConfigChooser::PIXEL_FORMAT_ATTRIBUTE_IDS
{{
	WGL_ACCELERATION_ARB,
	WGL_ALPHA_BITS_ARB,
	WGL_BLUE_BITS_ARB,
	WGL_DEPTH_BITS_ARB,
	WGL_GREEN_BITS_ARB,
	WGL_RED_BITS_ARB,
	WGL_STENCIL_BITS_ARB
}};

const GraphicsConfigChooser::PixelFormatRequiredAttributeList GraphicsConfigChooser::PIXEL_FORMAT_REQUIRED_ATTRIBUTES
{{
	WGL_DOUBLE_BUFFER_ARB,	1,
	WGL_DRAW_TO_WINDOW_ARB, 1,
	WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB,
	WGL_SUPPORT_OPENGL_ARB, 1,
	0
}};

Uint32 GraphicsConfigChooser::getPixelFormatCount() const
{
	const Int32 attributeName = WGL_NUMBER_PIXEL_FORMATS_ARB;
	Int32 formatCount;
	const Int32 result = wglGetPixelFormatAttribivARB(_deviceContextHandle, 0, 0, 1u, &attributeName, &formatCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the config count." << Log::Flush();
		DE_ERROR_WINDOWS(0x0);
	}

	return formatCount;
}

GraphicsConfigChooser::PixelFormatIndexList GraphicsConfigChooser::getPixelFormatIndices(
	const Uint32 formatCount) const
{
	PixelFormatIndexList formatIndices(formatCount);
	Uint32 matchingFormatCount;

	const Int32 result = wglChoosePixelFormatARB(_deviceContextHandle, PIXEL_FORMAT_REQUIRED_ATTRIBUTES.data(),
		nullptr, formatCount, formatIndices.data(), &matchingFormatCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the matching configurations." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	if(matchingFormatCount == 0u)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " No matching configurations were found." << Log::Flush();
		DE_ERROR(0x0);
	}

	formatIndices.resize(matchingFormatCount);
	formatIndices.shrink_to_fit();

	return formatIndices;
}

Int32 GraphicsConfigChooser::chooseBestPixelFormat(const PixelFormatIndexList& formatIndices) const
{
	Int32 bestFormatIndex = formatIndices.front();
	PixelFormatAttributeList bestFormatAttributes = getPixelFormatAttributes(bestFormatIndex);

	for(PixelFormatIndexList::const_iterator i = formatIndices.begin() + 1u, end = formatIndices.end(); i != end; ++i)
	{
		const PixelFormatAttributeList compareFormatAttributes = getPixelFormatAttributes(*i);

		if(isPixelFormatLess(bestFormatAttributes, compareFormatAttributes))
		{
			bestFormatIndex = *i;
			bestFormatAttributes = compareFormatAttributes;
		}
	}

	return bestFormatIndex;
}

GraphicsConfigChooser::PixelFormatAttributeList GraphicsConfigChooser::getPixelFormatAttributes(
	const Int32 formatIndex) const
{
	PixelFormatAttributeList attributes;

	const Int32 result = wglGetPixelFormatAttribivARB(_deviceContextHandle, formatIndex, 0, attributes.size(),
		PIXEL_FORMAT_ATTRIBUTE_IDS.data(), attributes.data());

	if(result == 0)
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the attributes of a configuration." <<
			Log::Flush();
		
		DE_ERROR_WINDOWS(0x0);
	}

	return attributes;
}

// Static

Bool GraphicsConfigChooser::isPixelFormatLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB)
{
	if(formatAttributesA[0] != formatAttributesB[0])
	{
		return isPixelFormatAccelerationLess(formatAttributesA, formatAttributesB);
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

Bool GraphicsConfigChooser::isPixelFormatAccelerationLess(const PixelFormatAttributeList& formatAttributesA,
	const PixelFormatAttributeList& formatAttributesB)
{
	return formatAttributesA[0] == WGL_NO_ACCELERATION_ARB || (formatAttributesA[0] == WGL_GENERIC_ACCELERATION_ARB &&
		formatAttributesB[0] == WGL_FULL_ACCELERATION_ARB);
}
