/**
 * @file platform/GraphicsExtensionHelper.cpp
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

#include <core/Log.h>
#include <core/maths/Utility.h>
#include <platform/GraphicsExtensionHelper.h>

using namespace Core;
using namespace Maths;
using namespace Platform;

// External

static const Uint32 LOG_COLUMN_COUNT = 2u;
static const Uint32 LOG_COLUMN_WIDTH = 50u;

static void logExtensionsInColumns(const ExtensionNameList& extensionNames);


// Some members are defined in platform/*/*GraphicsExtensionHelper.cpp

// Public

void GraphicsExtensionHelper::logExtensions(const Char8* description, const ExtensionNameList& extensionNames)
{
	defaultLog << LogLevel::Info;

	if(extensionNames.empty())
	{
		defaultLog << "No " << description << " extensions are supported.";
	}
	else
	{
		defaultLog << "Supported " << description << " extensions:\n\n";
		::logExtensionsInColumns(extensionNames);
	}

	defaultLog << Log::Flush();
}


// External

static void logExtensionsInColumns(const ExtensionNameList& extensionNames)
{
	const Uint32 extensionCount = extensionNames.size();
	const Uint32 rowCount = static_cast<Uint32>(ceiling(static_cast<Float32>(extensionCount) / ::LOG_COLUMN_COUNT));

	for(Uint32 i = 0u; i < rowCount; ++i)
	{
		for(Uint32 j = i; j <= i + ::LOG_COLUMN_COUNT * rowCount && j < extensionCount; j += rowCount)
		{
			if(j != i)
				defaultLog << String8(::LOG_COLUMN_WIDTH - extensionNames[j - rowCount].length() + 4u, ' ');

			defaultLog << extensionNames[j];
		}

		defaultLog << '\n';
	}
}
