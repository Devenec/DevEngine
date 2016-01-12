/**
 * @file platform/wgl/WGLGraphicsConfigChooser.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <graphics/GraphicsConfig.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsConfigChooser.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::GraphicsConfigChooser - WGL] ";

static const Array<Int32, 9u> REQUIRED_CONFIG_ATTRIBUTES
{{
	WGL::DOUBLE_BUFFER_ARB,	 1,
	WGL::DRAW_TO_WINDOW_ARB, 1,
	WGL::PIXEL_TYPE_ARB,	 WGL::TYPE_RGBA_ARB,
	WGL::SUPPORT_OPENGL_ARB, 1,
	0
}};

static Bool isConfigLess(const ConfigAttributeList& configAttributesA,
	const ConfigAttributeList& configAttributesB);


// Public

GraphicsConfigChooser::GraphicsConfigChooser(HDC deviceContextHandle)
	: _deviceContextHandle(deviceContextHandle) { }

Int32 GraphicsConfigChooser::chooseConfig(GraphicsConfig& chosenConfig) const
{
	const Uint32 configCount = getConfigCount();
	const ConfigIndexList configIndices = getConfigIndices(configCount);
	ConfigAttributeList configAttributes;
	const Int32 chosenConfigIndex = chooseBestConfig(configIndices, configAttributes);

	chosenConfig =
		GraphicsConfig(configAttributes[5], configAttributes[4], configAttributes[2], configAttributes[1],
			configAttributes[3], configAttributes[6]);

	return chosenConfigIndex;
}

// Private

const ConfigAttributeList GraphicsConfigChooser::CONFIG_ATTRIBUTE_IDS
{{
	WGL::ACCELERATION_ARB,
	WGL::ALPHA_BITS_ARB,
	WGL::BLUE_BITS_ARB,
	WGL::DEPTH_BITS_ARB,
	WGL::GREEN_BITS_ARB,
	WGL::RED_BITS_ARB,
	WGL::STENCIL_BITS_ARB
}};

Uint32 GraphicsConfigChooser::getConfigCount() const
{
	const Int32 attributeName = WGL::NUMBER_PIXEL_FORMATS_ARB;
	Int32 configCount;

	const Int32 result =
		WGL::getPixelFormatAttribivARB(_deviceContextHandle, 0, 0, 1u, &attributeName, &configCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the number of configurations." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return configCount;
}

GraphicsConfigChooser::ConfigIndexList GraphicsConfigChooser::getConfigIndices(const Uint32 configCount)
	const
{
	ConfigIndexList configIndices(configCount);
	Uint32 matchingConfigCount;

	const Int32 result =
		WGL::choosePixelFormatARB(_deviceContextHandle, ::REQUIRED_CONFIG_ATTRIBUTES.data(), nullptr,
			configCount, configIndices.data(), &matchingConfigCount);

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get matching configurations." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}
	else if(matchingConfigCount == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "No matching configurations were found."
			<< Log::Flush();

		DE_ERROR(0x0);
	}

	configIndices.resize(matchingConfigCount);
	return configIndices;
}

Int32 GraphicsConfigChooser::chooseBestConfig(const ConfigIndexList& configIndices,
	ConfigAttributeList& configAttributes) const
{
	Int32 bestConfigIndex = configIndices.front();
	configAttributes = getConfigAttributes(bestConfigIndex);

	for(ConfigIndexList::const_iterator i = configIndices.begin() + 1u, end = configIndices.end(); i != end;
		++i)
	{
		const ConfigAttributeList compareConfigAttributes = getConfigAttributes(*i);

		if(::isConfigLess(configAttributes, compareConfigAttributes))
		{
			bestConfigIndex = *i;
			configAttributes = compareConfigAttributes;
		}
	}

	return bestConfigIndex;
}

ConfigAttributeList GraphicsConfigChooser::getConfigAttributes(const Int32 configIndex) const
{
	ConfigAttributeList attributes;

	const Int32 result =
		WGL::getPixelFormatAttribivARB(_deviceContextHandle, configIndex, 0,
			static_cast<Uint32>(attributes.size()), CONFIG_ATTRIBUTE_IDS.data(), attributes.data());

	if(result == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get configuration attributes." <<
			Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return attributes;
}


// External

static Bool isConfigLess(const ConfigAttributeList& configAttributesA,
	const ConfigAttributeList& configAttributesB)
{
	if(configAttributesA[0] != configAttributesB[0])
	{
		return configAttributesA[0] < configAttributesB[0];
	}
	else
	{
		return
			configAttributesA[0] < configAttributesB[0] ||
			configAttributesA[1] < configAttributesB[1] ||
			configAttributesA[2] < configAttributesB[2] ||
			configAttributesA[3] < configAttributesB[3] ||
			configAttributesA[4] < configAttributesB[4] ||
			configAttributesA[5] < configAttributesB[5] ||
			configAttributesA[6] < configAttributesB[6];
	}
}
