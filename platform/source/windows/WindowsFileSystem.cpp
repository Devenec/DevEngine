/**
 * @file platform/windows/WindowsFileSystem.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/FileSystem.h>
#include <core/Log.h>
#include <platform/windows/Windows.h>

using namespace Core;

static const Char8* FILESYSTEM_COMPONENT_TAG = "[Platform::FileSystem - Windows]";

// Public

// Static

Bool FileSystem::fileExists(const String8& filepath)
{
	const String16 filepath16 = toString16(filepath);
	const Uint32 fileAttributes = GetFileAttributesW(filepath16.c_str());

	if(fileAttributes == INVALID_FILE_ATTRIBUTES)
	{
		if(GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			SetLastError(0u);
			return false;
		}

		defaultLog << LogLevel::Error << FILESYSTEM_COMPONENT_TAG << " Failed to get the attributes of file '" <<
			filepath << "'." << Log::Flush();

		DE_ERROR_WINDOWS(0x000100);
	}

	return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0u;
}
