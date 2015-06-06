/**
 * @file core/FileStream.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	enum class OpenMode
	{
		Read  = 1,
		Write = 2
	};

	enum class SeekPosition
	{
		Begin,
		Current,
		End
	};

	class FileStream
	{
	public:

		FileStream();

		FileStream(const FileStream& fileStream) = delete;
		FileStream(FileStream&& fileStream) = delete;

		~FileStream();

		void close() const;

		Bool isAtEndOfFile() const;

		void open(const String8& filepath, const OpenMode& openMode = OpenMode::Read) const;

		Int64 position() const;

		Uint32 read(Byte* buffer, const Uint32 byteCount) const;

		void seek(const Int64 position) const;

		void seek(const SeekPosition& position, const Int64 offset) const;

		Int64 size() const;

		Uint32 write(const Byte* data, const Uint32 byteCount) const;

		FileStream& operator =(const FileStream& fileStream) = delete;
		FileStream& operator =(FileStream&& fileStream) = delete;

	private:

		class Impl;

		Impl* _impl;
	};

	inline OpenMode operator &(const OpenMode& openModeA, const OpenMode& openModeB);

	inline OpenMode& operator &=(OpenMode& openModeA, const OpenMode& openModeB);

	inline OpenMode operator |(const OpenMode& openModeA, const OpenMode& openModeB);

	inline OpenMode& operator |=(OpenMode& openModeA, const OpenMode& openModeB);

#include "inline/FileStream.inl"
}
