/**
 * @file core/FileStream.h
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

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	enum class OpenMode
	{
		Read	 = 1,
		Write	 = 2,
		Truncate = 4,
	};

	enum class SeekPosition
	{
		Begin,
		Current,
		End
	};

	class FileStream final
	{
	public:

		FileStream();

		explicit FileStream(const String8& filepath, const OpenMode& openMode = OpenMode::Read);

		FileStream(const FileStream& fileStream) = delete;
		FileStream(FileStream&& fileStream) = delete;

		~FileStream();

		void close() const;

		Bool isAtEndOfFile() const;

		Bool isOpen() const;

		void open(const String8& filepath, const OpenMode& openMode = OpenMode::Read) const;

		Int64 position() const;

		Uint32 read(Byte* buffer, const Uint32 size) const;

		void seek(const Int64& position) const;

		void seek(const SeekPosition& position, const Int64& offset) const;

		Int64 size() const;

		Uint32 write(const Byte* data, const Uint32 size) const;

		FileStream& operator =(const FileStream& fileStream) = delete;
		FileStream& operator =(FileStream&& fileStream) = delete;

	private:

		class Implementation;

		Implementation* _implementation;
	};

	inline OpenMode operator &(OpenMode openModeA, const OpenMode& openModeB);

	inline OpenMode& operator &=(OpenMode& openModeA, const OpenMode& openModeB);

	inline OpenMode operator |(OpenMode openModeA, const OpenMode& openModeB);

	inline OpenMode& operator |=(OpenMode& openModeA, const OpenMode& openModeB);

#include "inline/FileStream.inl"
}
