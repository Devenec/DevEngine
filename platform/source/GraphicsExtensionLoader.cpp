/**
 * @file platform/GraphicsExtensionLoader.cpp
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

#include <algorithm>
#include <core/Log.h>
#include <core/maths/Utility.h>
#include <platform/GraphicsExtensionLoader.h>

using namespace Core;
using namespace Platform;
using namespace Maths;

// External

static const Uint32 LOG_COLUMN_WIDTH = 50u;

static void logSupportedExtensions(const ExtensionNameList& extensionNames);
static ExtensionNameList splitExtensionsString(const String8& extensionsString);


// Some members are defined in platform/*/*GraphicsExtensionLoader.cpp

// Private

// Static

void GraphicsExtensionLoader::logSupportedContextExtensions(const String8& extensionsString)
{
	defaultLog << LogLevel::Info;

	if(extensionsString.empty())
	{
		defaultLog << "No graphics context extensions are supported.";
	}
	else
	{
		defaultLog << "Supported graphics context extensions:\n\n";
		const Vector<String8> extensionNames = splitExtensionsString(extensionsString);
		logSupportedExtensions(extensionNames);
	}

	defaultLog << Log::Flush();
}

void GraphicsExtensionLoader::logSupportedInterfaceExtensions(const ExtensionNameList& extensionNames)
{
	defaultLog << LogLevel::Info;

	if(extensionNames.empty())
	{
		defaultLog << "No graphics interface extensions are supported.";
	}
	else
	{
		defaultLog << "Supported graphics interface extensions:\n\n";
		logSupportedExtensions(extensionNames);
	}

	defaultLog << Log::Flush();
}


// External

static void logSupportedExtensions(const ExtensionNameList& extensionNames)
{
	const Uint32 extensionCount = extensionNames.size();
	const Uint32 rowCount = static_cast<Uint32>(ceiling(extensionCount / 2.0f));

	for(Uint32 i = 0u; i < rowCount; ++i)
	{
		for(Uint32 j = i; j <= i + 2u * rowCount && j < extensionCount; j += rowCount)
		{
			if(j != i)
				defaultLog << String8(LOG_COLUMN_WIDTH - extensionNames[j - rowCount].length() + 4u, ' ');

			defaultLog << extensionNames[j];
		}

		defaultLog << '\n';
	}
}

static ExtensionNameList splitExtensionsString(const String8& extensionsString)
{
	Uint32 currentPosition = 0u;
	Uint32 spacePosition;
	Vector<String8> extensionNames;

	while((spacePosition = extensionsString.find(' ', currentPosition)) != String8::npos)
	{
		extensionNames.push_back(extensionsString.substr(currentPosition, spacePosition - currentPosition));
		currentPosition = spacePosition + 1u;
	}

	return extensionNames;
}
	