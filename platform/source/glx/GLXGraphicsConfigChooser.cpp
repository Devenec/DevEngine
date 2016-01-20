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

#include <core/Array.h>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/GraphicsConfig.h>
#include <platform/GraphicsConfigChooser.h>
#include <platform/glx/GLX.h>
#include <platform/x/X.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

using ConfigAttributeList = Array<Int32, 6u>;

static const Char8* COMPONENT_TAG = "[Platform::GraphicsConfigChooser - GLX] ";

static Bool isConfigLess(const ConfigAttributeList& configAttributesA,
	const ConfigAttributeList& configAttributesB);

// Implementation

class GraphicsConfigChooser::Implementation final
{
public:

	Implementation()
		: _x(X::instance()) { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	ConfigHandle chooseConfig(GraphicsConfig& chosenConfig) const
	{
		Uint32 configCount = 0u;
		GLX::FBConfig* configHandles = getConfigs(configCount);
		ConfigAttributeList configAttributes;
		GLX::FBConfig configHandle = chooseBestConfig(configHandles, configCount, configAttributes);
		XFree(configHandles);

		chosenConfig =
			GraphicsConfig(configAttributes[4], configAttributes[3], configAttributes[1], configAttributes[0],
				configAttributes[2], configAttributes[5]);

		return configHandle;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	using ConfigIndexList = Vector<Int32>;
	using RequiredConfigAttributeList = Array<Int32, 9u>;

	static const ConfigAttributeList CONFIG_ATTRIBUTE_IDS;
	static const RequiredConfigAttributeList REQUIRED_CONFIG_ATTRIBUTES;

	X& _x;

	GLX::FBConfig* getConfigs(Uint32& configCount) const
	{
		GLX::FBConfig* configHandles = _x.getGraphicsConfigs(::REQUIRED_CONFIG_ATTRIBUTES.data(),
			configCount);

		if(configCount == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "No matching configurations were found." <<
				Log::Flush();

			DE_ERROR(0x0);
		}

		return configHandles;
	}

	GLX::FBConfig chooseBestConfig(GLX::FBConfig* configHandles, const Uint32 configCount,
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

	ConfigAttributeList getConfigAttributes(GLX::FBConfig configHandle) const
	{
		ConfigAttributeList attributes;

		for(Uint32 i = 0u; i < attributes.size(); ++i)
			attributes[i] = _x.getGraphicsConfigAttribute(configHandle, CONFIG_ATTRIBUTE_IDS[i]);

		return attributes;
	}
};

const ConfigAttributeList GraphicsConfigChooser::Implementation::CONFIG_ATTRIBUTE_IDS
{{
	GLX::ALPHA_SIZE,
	GLX::BLUE_SIZE,
	GLX::DEPTH_SIZE,
	GLX::GREEN_SIZE,
	GLX::RED_SIZE,
	GLX::STENCIL_SIZE
}};

const GraphicsConfigChooser::Implementation::RequiredConfigAttributeList
GraphicsConfigChooser::Implementation::REQUIRED_CONFIG_ATTRIBUTES
{{
	GLX::DOUBLEBUFFER,	1,
	GLX::DRAWABLE_TYPE, GLX::WINDOW_BIT,
	GLX::RENDER_TYPE,	GLX::RGBA_BIT,
	GLX::X_VISUAL_TYPE, GLX::TRUE_COLOR,
	0
}};


// Platform::GraphicsConfigChooser

// Public

GraphicsConfigChooser::GraphicsConfigChooser(WindowHandle windowHandle)
	: _implementation(DE_NEW(Implementation)())
{
	static_cast<Void>(windowHandle);
}

GraphicsConfigChooser::~GraphicsConfigChooser()
{
	DE_DELETE(_implementation, Implementation);
}

ConfigHandle GraphicsConfigChooser::chooseConfig(Graphics::GraphicsConfig& chosenConfig) const
{
	return _implementation->chooseConfig(chosenConfig);
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
