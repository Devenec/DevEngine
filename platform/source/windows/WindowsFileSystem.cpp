/**
 * @file FileSystem.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/FileSystem.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

using namespace Core;

static const Char8* FILESYSTEM_CONTEXT = "[Platform::FileSystem - Windows]";

// Implementation

class FileSystem::Impl final
{
public:

	Impl() = default;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	Bool fileExists(const String8& filepath)
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

			defaultLog << LogLevel::Error << FILESYSTEM_CONTEXT << " Failed to get the attributes of file '" <<
				filepath << "'." << Log::Flush();

			DE_ERROR_WINDOWS(0x000100);
		}

		return (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0u;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

};


// Public

FileSystem::FileSystem()
	: _impl(nullptr) { }

void FileSystem::deinitialise()
{
	DE_DELETE(_impl, Impl);
}

Bool FileSystem::fileExists(const String8& filepath)
{
	DE_ASSERT(_impl != nullptr);
	return _impl->fileExists(filepath);
}

void FileSystem::initialise()
{
	_impl = DE_NEW(Impl)();
}
