/**
 * @file core/FileSystem.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	class FileSystem final
	{
	public:

		FileSystem() = delete;

		FileSystem(const FileSystem& fileSystem) = delete;
		FileSystem(FileSystem&& fileSystem) = delete;

		~FileSystem() = delete;

		static Bool fileExists(const String8& filepath);

		FileSystem& operator =(const FileSystem& fileSystem) = delete;
		FileSystem& operator =(FileSystem&& fileSystem) = delete;
	};
}
