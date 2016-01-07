/**
 * @file platform/posix/POSIXFileSystem.cpp
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

#include <unistd.h>
#include <core/FileSystem.h>
#include <core/Log.h>
#include <core/Vector.h>
#include <platform/posix/POSIX.h>

using namespace Core;

// External

static const Char8* COMPONENT_TAG = "[Core::FileSystem - POSIX] ";
static const Char8* SYMLINK_PATH  = "/proc/self/exe";


// Public

// Static

Bool FileSystem::fileExists(const String8& filepath)
{
	return access(filepath.c_str(), F_OK) == 0;
}

String8 FileSystem::getDefaultContentRootDirectory()
{
	Uint32 pathBufferSize = 256u;
	Vector<Char8> pathBuffer(pathBufferSize);
	Int32 bytesStored = 0;

	while(true)
	{
		bytesStored = readlink(SYMLINK_PATH, pathBuffer.data(), pathBuffer.size());

		if(bytesStored == -1)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG <<
				"Failed to get the filepath of the executable." << Log::Flush();

			DE_ERROR_POSIX(0x0);
		}
		else if(bytesStored < pathBufferSize)
		{
			break;
		}

		pathBufferSize *= 2;
		pathBuffer.reserve(pathBufferSize);
	}

	const String8 path(pathBuffer.data(), pathBuffer.size());
	return path.substr(0u, path.rfind('/') + 1u);
}
