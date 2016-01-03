/**
 * @file platform/glx/GLXGraphicsConfigChooser.cpp
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
#include <platform/glx/GLXGraphicsConfigChooser.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

using RequiredConfigAttributeList = Array<Int32, 9u>;

static const Char8* COMPONENT_TAG = "[Platform::GraphicsConfigChooser - GLX] ";

static const RequiredConfigAttributeList REQUIRED_CONFIG_ATTRIBUTES
{{
	GLX::DOUBLEBUFFER,	1,
	GLX::DRAWABLE_TYPE, GLX::WINDOW_BIT,
	GLX::RENDER_TYPE,	GLX::RGBA_BIT,
	GLX::X_VISUAL_TYPE, GLX::TRUE_COLOR,
	0
}};

static Bool isConfigLess(const ConfigAttributeList& configAttributesA,
	const ConfigAttributeList& configAttributesB);


// Public

GraphicsConfigChooser::GraphicsConfigChooser()
	: _x(X::instance()) { }

GLX::FBConfig GraphicsConfigChooser::chooseConfig() const
{
	Uint32 configCount = 0;
	GLX::FBConfig* configHandles = getConfigs(configCount);
	ConfigAttributeList configAttributes;
	GLX::FBConfig bestConfigHandle = chooseBestConfig(configHandles, configCount, configAttributes);
	XFree(configHandles);

	return bestConfigHandle;
}

GraphicsConfig GraphicsConfigChooser::getConfig(GLX::FBConfig configHandle) const
{
	ConfigAttributeList configAttributes = getConfigAttributes(configHandle);

	return
		GraphicsConfig(configAttributes[4], configAttributes[3], configAttributes[1], configAttributes[0],
			configAttributes[2], configAttributes[5]);
}

// Private

const ConfigAttributeList GraphicsConfigChooser::CONFIG_ATTRIBUTE_IDS
{{
	GLX::ALPHA_SIZE,
	GLX::BLUE_SIZE,
	GLX::DEPTH_SIZE,
	GLX::GREEN_SIZE,
	GLX::RED_SIZE,
	GLX::STENCIL_SIZE
}};

GLX::FBConfig* GraphicsConfigChooser::getConfigs(Uint32& configCount) const
{
	GLX::FBConfig* configHandles = _x.getGraphicsConfigs(::REQUIRED_CONFIG_ATTRIBUTES.data(), configCount);

	if(configCount == 0)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "No matching configurations were found." <<
			Log::Flush();

		DE_ERROR(0x0);
	}

	return configHandles;
}

GLX::FBConfig GraphicsConfigChooser::chooseBestConfig(GLX::FBConfig* configHandles, const Uint32 configCount,
	ConfigAttributeList& configAttributes) const
{
	GLX::FBConfig bestConfigHandle = configHandles[0u];
	configAttributes = getConfigAttributes(bestConfigHandle);

	for(Uint32 i = 1u; i < configCount; ++i)
	{
		const ConfigAttributeList compareConfigAttributes = getConfigAttributes(configHandles[i]);

		if(::isConfigLess(configAttributes, compareConfigAttributes))
		{
			bestConfigHandle = configHandles[i];
			configAttributes = compareConfigAttributes;
		}
	}

	return bestConfigHandle;
}

ConfigAttributeList GraphicsConfigChooser::getConfigAttributes(GLX::FBConfig configHandle) const
{
	ConfigAttributeList attributes;

	for(Uint32 i = 0u; i < attributes.size(); ++i)
		attributes[i] = _x.getGraphicsConfigAttribute(configHandle, CONFIG_ATTRIBUTE_IDS[i]);

	return attributes;
}


// External

static Bool isConfigLess(const ConfigAttributeList& configAttributesA,
	const ConfigAttributeList& configAttributesB)
{
	return
		configAttributesA[1] < configAttributesB[1] ||
		configAttributesA[2] < configAttributesB[2] ||
		configAttributesA[3] < configAttributesB[3] ||
		configAttributesA[4] < configAttributesB[4] ||
		configAttributesA[5] < configAttributesB[5] ||
		configAttributesA[6] < configAttributesB[6];
}
