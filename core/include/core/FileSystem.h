/**
 * @file core/FileSystem.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Singleton.h>
#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	class FileSystem final : public Singleton<FileSystem>
	{
	public:

		FileSystem();

		FileSystem(const FileSystem& fileSystem) = delete;
		FileSystem(FileSystem&& fileSystem) = delete;

		~FileSystem() = default;

		void deinitialise();

		Bool fileExists(const String8& filepath);

		void initialise();

		FileSystem& operator =(const FileSystem& fileSystem) = delete;
		FileSystem& operator =(FileSystem&& fileSystem) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
