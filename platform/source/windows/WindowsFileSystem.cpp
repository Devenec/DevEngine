/**
 * @file platform/windows/WindowsFileSystem.cpp
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

#include <core/FileSystem.h>
#include <core/Log.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Core::FileSystem - Windows] ";


// Public

// Static

Bool FileSystem::fileExists(const String8& filepath)
{
	const Uint32 fileAttributes = GetFileAttributesW(toString16(filepath).c_str());

	if(fileAttributes == INVALID_FILE_ATTRIBUTES)
	{
		if(getWindowsErrorCode() == ERROR_FILE_NOT_FOUND)
			return false;

		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the attributes of file '" <<
			filepath << "'." << Log::Flush();

		DE_ERROR_WINDOWS(0x0);
	}

	return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0u;
}
