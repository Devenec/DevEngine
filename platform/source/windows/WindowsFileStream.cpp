/**
 * @file platform/windows/WindowsFileStream.cpp
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

#include <core/FileStream.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

using namespace Core;

// External

static const Char8* COMPONENT_TAG = "[Core::FileStream - Windows] ";

static LARGE_INTEGER createLargeInteger(const Int64& value = 0);
static Uint32 getAccessMode(const OpenMode& openMode);
static Uint32 getCreationMode(const OpenMode& openMode);


// Implementation

class FileStream::Implementation final
{
public:

	Implementation()
		: _fileHandle(nullptr),
		  _openMode() { }

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		close();
	}

	void close()
	{
		if(isOpen())
		{
			if((_openMode & OpenMode::Write) == OpenMode::Write)
				flushBuffer();

			const Int32 result = CloseHandle(_fileHandle);

			if(result == 0)
			{
				defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to close the file." <<
					Log::Flush();

				DE_ERROR_WINDOWS(0x0);
			}

			_fileHandle = nullptr;
			_openMode = OpenMode();
		}
	}

	Bool isPastEndOfFile() const
	{
		DE_ASSERT(isOpen());
		return position() >= size();
	}

	Bool isOpen() const
	{
		return _fileHandle != nullptr;
	}

	void open(const String8& filepath, const OpenMode& openMode)
	{
		DE_ASSERT((openMode & OpenMode::Read) == OpenMode::Read ||
			(openMode & OpenMode::Write) == OpenMode::Write);

		DE_ASSERT(!isOpen());
		const String16 filepath16 = toString16(filepath);
		const Uint32 accessMode = ::getAccessMode(openMode);
		const Uint32 creationMode = ::getCreationMode(openMode);

		_fileHandle =
			CreateFileW(filepath16.c_str(), accessMode, FILE_SHARE_READ, nullptr, creationMode,
				FILE_ATTRIBUTE_NORMAL, nullptr);

		if(_fileHandle == INVALID_HANDLE_VALUE)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to open file '" << filepath << "'." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		SetLastError(0u);
		_openMode = openMode;
	}

	Int64 position() const
	{
		DE_ASSERT(isOpen());
		const LARGE_INTEGER offset = ::createLargeInteger();
		LARGE_INTEGER position;
		const Int32 result = SetFilePointerEx(_fileHandle, offset, &position, FILE_CURRENT);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the file pointer position." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		return position.QuadPart;
	}

	Uint32 read(Uint8* buffer, const Uint32 size) const
	{
		DE_ASSERT(buffer != nullptr);
		DE_ASSERT(isOpen());

		unsigned long bytesRead;
		const Int32 result = ReadFile(_fileHandle, buffer, size, &bytesRead, nullptr);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to read the file." << Log::Flush();
			DE_ERROR_WINDOWS(0x0);
		}

		return bytesRead;
	}

	void seek(const SeekPosition& position, const Int64& offset) const
	{
		DE_ASSERT(isOpen());
		const LARGE_INTEGER seekOffset = ::createLargeInteger(offset);
		const Int32 result = SetFilePointerEx(_fileHandle, seekOffset, nullptr, static_cast<Int32>(position));

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to seek the file." << Log::Flush();
			DE_ERROR_WINDOWS(0x0);
		}
	}

	Int64 size() const
	{
		DE_ASSERT(isOpen());
		LARGE_INTEGER size;
		const Int32 result = GetFileSizeEx(_fileHandle, &size);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to get the file size." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		return size.QuadPart;
	}

	Uint32 write(const Uint8* data, const Uint32 size) const
	{
		DE_ASSERT(data != nullptr);
		DE_ASSERT(isOpen());

		unsigned long bytesWritten;
		const Int32 result = WriteFile(_fileHandle, data, size, &bytesWritten, nullptr);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to write to the file." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}

		return bytesWritten;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	HANDLE _fileHandle;
	OpenMode _openMode;

	void flushBuffer() const
	{
		const Int32 result = FlushFileBuffers(_fileHandle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to flush the file buffer." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0x0);
		}
	}
};


// Core::FileStream

// Public

FileStream::FileStream()
	: _implementation(DE_NEW(Implementation)()) { }

FileStream::FileStream(const String8& filepath, const OpenMode& openMode)
	: FileStream()
{
	_implementation->open(filepath, openMode);
}

FileStream::~FileStream()
{
	DE_DELETE(_implementation, Implementation);
}

void FileStream::close() const
{
	_implementation->close();
}

Bool FileStream::isPastEndOfFile() const
{
	return _implementation->isPastEndOfFile();
}

Bool FileStream::isOpen() const
{
	return _implementation->isOpen();
}

void FileStream::open(const String8& filepath, const OpenMode& openMode) const
{
	_implementation->open(filepath, openMode);
}

Int64 FileStream::position() const
{
	return _implementation->position();
}

Uint32 FileStream::read(Uint8* buffer, const Uint32 size) const
{
	return _implementation->read(buffer, size);
}

void FileStream::seek(const SeekPosition& position, const Int64& offset) const
{
	_implementation->seek(position, offset);
}

Int64 FileStream::size() const
{
	return _implementation->size();
}

Uint32 FileStream::write(const Uint8* data, const Uint32 size) const
{
	return _implementation->write(data, size);
}


// External

static LARGE_INTEGER createLargeInteger(const Int64& value)
{
	LARGE_INTEGER integer;
	integer.QuadPart = value;

	return integer;
}

static Uint32 getAccessMode(const OpenMode& openMode)
{
	Uint32 mode = 0u;

	if((openMode & OpenMode::Read) == OpenMode::Read)
		mode |= GENERIC_READ;

	if((openMode & OpenMode::Write) == OpenMode::Write)
		mode |= GENERIC_WRITE;

	return mode;
}

static Uint32 getCreationMode(const OpenMode& openMode)
{
	Uint32 mode = 0u;

	if((openMode & OpenMode::Read) == OpenMode::Read)
		mode = OPEN_EXISTING;

	if((openMode & OpenMode::Write) == OpenMode::Write)
	{
		if((openMode & OpenMode::Truncate) == OpenMode::Truncate)
			mode = CREATE_ALWAYS;
		else
			mode = OPEN_ALWAYS;
	}

	return mode;
}
