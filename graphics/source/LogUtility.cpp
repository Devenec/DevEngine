/**
 * @file graphics/LogUtility.cpp
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

#include <functional>
#include <core/Log.h>
#include <core/maths/Utility.h>
#include <graphics/DisplayMode.h>
#include <graphics/GraphicsAdapter.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/LogUtility.h>
#include <graphics/Viewport.h>
#include <graphics/Window.h>

using namespace Core;
using namespace Graphics;
using namespace Maths;

// External

template<typename T>
using LogElementFunction = std::function<void(const T&, const Bool)>;

static void logGraphicsAdapterDisplayMode(const DisplayMode& mode, const Bool insertSeparator);
static void logGraphicsExtensionName(const String8& name, const Bool insertSeparator);

template<typename T>
static void logElementsInColumns(const Vector<T>& elements, const Uint32 columnCount,
	LogElementFunction<T> logElementFunction);


// Graphics

void Graphics::logChosenGraphicsConfig(const GraphicsConfig& config)
{
	defaultLog << LogLevel::Info << "Chosen graphics configuration:\n\nColour buffer (RGBA): " <<
		config.redDepth() << ' ' << config.greenDepth() << ' ' << config.blueDepth() << ' ' <<
		config.alphaDepth() << " bits\nDepth buffer:         " << config.depthBufferDepth() <<
		" bits\nStencil buffer:       " << config.stencilBufferDepth() << " bits\n" << Log::Flush();
}

void Graphics::logGraphicsAdapters(const GraphicsAdapterList& adapters)
{
	defaultLog << LogLevel::Info << "Active graphics adapters and supported display modes:\n";

	for(GraphicsAdapterList::const_iterator i = adapters.begin(), end = adapters.end(); i != end; ++i)
	{
		defaultLog << '\n' << (*i)->name() << " (current: ";
		::logGraphicsAdapterDisplayMode((*i)->currentDisplayMode(), false);
		defaultLog << ")\n";

		::logElementsInColumns<DisplayMode>((*i)->supportedDisplayModes(), 3u,
			::logGraphicsAdapterDisplayMode);
	}

	defaultLog << Log::Flush();
}

void Graphics::logGraphicsDeviceCreation(GraphicsDevice* device)
{
	const Viewport& viewport = device->viewport();

	defaultLog << LogLevel::Info << "Created a graphics device\n\nFramebuffer dimensions: " <<
		viewport.bounds().width << " x " << viewport.bounds().height << '\n' << Log::Flush();
}

void Graphics::logGraphicsExtensions(const Char8* description, const ExtensionNameList& extensionNames)
{
	defaultLog << LogLevel::Info;

	if(extensionNames.empty())
	{
		defaultLog << "No " << description << " extensions are supported.";
	}
	else
	{
		defaultLog << "Supported " << description << " extensions:\n\n";
		::logElementsInColumns<String8>(extensionNames, 2u, ::logGraphicsExtensionName);
	}

	defaultLog << Log::Flush();
}

void Graphics::logWindowCreation(Window* window)
{
	const Rectangle clientRectangle = window->clientRectangle();

	defaultLog << LogLevel::Info << "Created a window\n\nClient rectangle: [" << clientRectangle.x << ", " <<
		clientRectangle.y << ", " << clientRectangle.width << ", " << clientRectangle.height << "]\n" <<
		Log::Flush();
}


// External

static void logGraphicsAdapterDisplayMode(const DisplayMode& mode, const Bool insertSeparator)
{
	if(mode.width() < 1000u)
		defaultLog << ' ';

	defaultLog << mode.width() << " x ";

	if(mode.height() < 1000u)
		defaultLog << ' ';

	defaultLog << mode.height() << ", ";

	if(mode.colourDepth() < 10u)
		defaultLog << ' ';

	defaultLog << mode.colourDepth() << " bit, ";

	if(mode.refreshRate() < 100u)
		defaultLog << ' ';

	defaultLog << mode.refreshRate() << " Hz";

	if(insertSeparator)
		defaultLog << "    ";
}

static void logGraphicsExtensionName(const String8& name, const Bool insertSeparator)
{
	defaultLog << name;

	if(insertSeparator)
		defaultLog << String8(50u - name.length() + 4u, ' ');
}

template<typename T>
static void logElementsInColumns(const Vector<T>& elements, const Uint32 columnCount,
	LogElementFunction<T> logElementFunction)
{
	const Uint32 elementCount = elements.size();
	const Uint32 rowCount = static_cast<Uint32>(ceiling(static_cast<Float32>(elementCount) / columnCount));

	for(Uint32 i = 0u; i < rowCount; ++i)
	{
		for(Uint32 j = i; j <= rowCount * columnCount + i && j < elementCount; j += rowCount)
			logElementFunction(elements[j], j < rowCount * columnCount + i);

		defaultLog << '\n';
	}
}
