/**
 * @file core/FileStream.h
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

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	/**
	 * Specifies how to open a file.
	 *
	 * A value of OpenMode can be a combination of the following items:
	 *
	 * Read
	 *   A file is opened for reading. An error is invoked if the file doesn't
	 *   exist, unless Read is combined with Write.
	 *
	 * Write
	 *   A file is opened for writing. The file is created if it doesn't exist.
	 *
	 * Truncate
	 *   A file is truncated to zero length. Truncate has to be combined with
	 *   Write.
	 */
	enum class OpenMode
	{
		Read	 = 1,
		Write	 = 2,
		Truncate = 4,
	};

	/**
	 * Specifies the origin of a seek operation.
	 *
	 * Begin
	 *   The origin is at the beginning of the file.
	 *
	 * Current
	 *   The origin is at the current position of the file pointer.
	 *
	 * End
	 *   The origin is at the end of the file.
	 */
	enum class SeekPosition
	{
		Begin,
		Current,
		End
	};

	/**
	 * A readable and/or writable file stream
	 */
	class FileStream final
	{
	public:

		/**
		 * Does nothing.
		 */
		FileStream();

		/**
		 * Opens a file.
		 *
		 * @param filepath
		 *   An absolute or relative path to the file
		 * @param openMode
		 *   Specifies how to open the file, see the declaration of OpenMode.
		 */
		explicit FileStream(const String8& filepath, const OpenMode& openMode = OpenMode::Read);

		FileStream(const FileStream& fileStream) = delete;
		FileStream(FileStream&& fileStream) = delete;

		/**
		 * Closes the file if it is open.
		 */
		~FileStream();

		/**
		 * Closes the file if it is open.
		 */
		void close() const;

		/**
		 * Indicates whether the file pointer is past the end of the file.
		 */
		Bool isPastEndOfFile() const;

		/**
		 * Indicates whether the file is open.
		 */
		Bool isOpen() const;

		/**
		 * Opens a file.
		 *
		 * @param filepath
		 *   An absolute or relative path to the file
		 * @param openMode
		 *   Specifies how to open the file, see the declaration of OpenMode.
		 */
		void open(const String8& filepath, const OpenMode& openMode = OpenMode::Read) const;

		/**
		 * Gets the position of the file pointer, relative to the beginning of
		 * the file.
		 */
		Int64 position() const;

		/**
		 * Reads the file.
		 *
		 * Reads until the specified number of bytes is read, or the end of the
		 * file is reached.
		 *
		 * @param buffer
		 *   Contiguous block of memory into which data is read
		 * @param size
		 *   The number of bytes to read
		 * @return
		 *   The number of bytes read
		 */
		Uint32 read(Uint8* buffer, const Uint32 size) const;

		/**
		 * Sets the position of the file pointer.
		 *
		 * Calls seek(SeekPosition::Begin, position), see its declaration.
		 *
		 * @param position
		 *   The new position, relative to the beginning of the file
		 */
		inline void seek(const Int64& position) const;

		/**
		 * Sets the position of the file pointer.
		 *
		 * Positioning the file pointer outside the file boundaries (except one
		 * byte past the end of the file) is undefined behaviour.
		 *
		 * @param position
		 *   The origin of the new position, see the declaration of SeekPosition
		 * @param offset
		 *   The new position, relative to 'position'
		 */
		void seek(const SeekPosition& position, const Int64& offset) const;

		/**
		 * Gets the size of the file.
		 */
		Int64 size() const;

		/**
		 * Writes to the file.
		 *
		 * Starting a write outside the file boundaries (except one byte past the
		 * end of the file) is undefined behaviour.
		 *
		 * @param data
		 *   The data to write
		 * @param size
		 *   The number of bytes to write
		 * @return
		 *   The number of bytes written
		 */
		Uint32 write(const Uint8* data, const Uint32 size) const;

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
