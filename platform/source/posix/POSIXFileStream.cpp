/**
 * @file platform/posix/POSIXFileStream.cpp
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

#include <cstdio>
#include <fcntl.h>
#include <sys/stat.h>
#include <core/FileStream.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>

using namespace Core;

// External

static const Char8* COMPONENT_TAG		= "[Core::FileStream - POSIX]";
static const Int32 CREATION_PERMISSIONS = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

static Int32 getFileDescriptorAccessMode(const OpenMode& openMode);
static const char* getFileHandleAccessMode(const OpenMode& openMode);
static Int32 getSeekOrigin(const SeekPosition& position);


// Implementation

class FileStream::Implementation final
{
public:

	Implementation()
		: _handle(nullptr),
		  _previousAction(PreviousAction::None) { }

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
			const Int32 result = std::fclose(_handle);

			if(result != 0)
			{
				defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to close the file." << Log::Flush();
				//DE_ERROR_WINDOWS(0x0);
			}

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
		return _handle != nullptr;
	}

	void open(const String8& filepath, const OpenMode& openMode)
	{
		DE_ASSERT((openMode & OpenMode::Read) == OpenMode::Read || (openMode & OpenMode::Write) == OpenMode::Write);
		DE_ASSERT(!isOpen());

		const Int32 fileDescriptorAccessMode = ::getFileDescriptorAccessMode(openMode);
		const Int32 fileDescriptor = ::open(filepath.c_str(), fileDescriptorAccessMode, CREATION_PERMISSIONS);

		if(fileDescriptor == -1)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to open file '" << filepath << "'." <<
				Log::Flush();

			//DE_ERROR_WINDOWS(0x0);
		}

		const char* handleAccessMode = ::getFileHandleAccessMode(openMode);
		_handle = ::fdopen(fileDescriptor, handleAccessMode);

		if(_handle == nullptr)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to open file '" << filepath << "'." <<
				Log::Flush();

			//DE_ERROR_WINDOWS(0x0);
		}

		_openMode = openMode;
		calculateSize();
	}

	Int64 position() const
	{
		DE_ASSERT(isOpen());
		const Int64 result = std::ftell(_handle);

		if(result == -1)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to get the file pointer position." <<
				Log::Flush();

			//DE_ERROR_WINDOWS(0x0);
		}

		return result;
	}

	Uint32 read(Byte* buffer, const Uint32 size)
	{
		DE_ASSERT(buffer != nullptr);
		DE_ASSERT(isOpen());

		if(_previousAction == PreviousAction::Write)
			seek(SeekPosition::Current, 0);

		const Uint32 bytesRead = std::fread(buffer, 1u, size, _handle);
		const Int32 result = std::ferror(_handle);

		if(result != 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to read the file." << Log::Flush();
			//DE_ERROR_WINDOWS(0x0);
		}

		_previousAction = PreviousAction::Read;
		return bytesRead;
	}

	void seek(const SeekPosition& position, const Int64& offset)
	{
		DE_ASSERT(isOpen());
		const Int32 origin = ::getSeekOrigin(position);
		const Int32 result = std::fseek(_handle, offset, origin);

		if(result != 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to seek the file." << Log::Flush();
			//DE_ERROR_WINDOWS(0x0);
		}

		_previousAction = PreviousAction::None;
	}

	Int64 size() const
	{
		DE_ASSERT(isOpen());
		return _size;
	}

	Uint32 write(const Byte* data, const Uint32 size)
	{
		DE_ASSERT(data != nullptr);
		DE_ASSERT(isOpen());

		if(_previousAction == PreviousAction::Read)
			seek(SeekPosition::Current, 0);

		const Uint32 bytesWritten = std::fwrite(data, 1u, size, _handle);
		const Int32 result = std::ferror(_handle);

		if(result != 0)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to write to the file." << Log::Flush();
			//DE_ERROR_WINDOWS(0x0);
		}

		_previousAction = PreviousAction::Write;
		return bytesWritten;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	enum class PreviousAction
	{
		None,
		Read,
		Write
	};

	std::FILE* _handle;
	Int64 _size;
	PreviousAction _previousAction;
	OpenMode _openMode;

	void calculateSize()
	{
		seek(SeekPosition::End, 0);
		_size = position();
		seek(SeekPosition::Begin, 0);
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

Uint32 FileStream::read(Byte* buffer, const Uint32 size) const
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

Uint32 FileStream::write(const Byte* data, const Uint32 size) const
{
	return _implementation->write(data, size);
}


// External

static Int32 getFileDescriptorAccessMode(const OpenMode& openMode)
{
	const Bool read = (openMode & OpenMode::Read) == OpenMode::Read;
	const Bool write = (openMode & OpenMode::Write) == OpenMode::Write;
	Int32 accessMode = 0;

	if(read && write)
		accessMode = O_RDWR;
	else if(read)
		accessMode = O_RDONLY;
	else if(write)
		accessMode = O_WRONLY;

	if(write)
	{
		accessMode |= O_CREAT;

		if((openMode & OpenMode::Truncate) == OpenMode::Truncate)
			accessMode |= O_TRUNC;
	}

	return accessMode;
}

static const char* getFileHandleAccessMode(const OpenMode& openMode)
{
	const Bool read = (openMode & OpenMode::Read) == OpenMode::Read;
	const Bool write = (openMode & OpenMode::Write) == OpenMode::Write;

	if(read && write)
		return "r+";
	else if(read)
		return "r";
	else if(write)
		return "w";

	return nullptr;
}

static Int32 getSeekOrigin(const SeekPosition& position)
{
	switch(position)
	{
		case SeekPosition::Begin:
			return SEEK_SET;

		case SeekPosition::Current:
			return SEEK_CUR;

		case SeekPosition::End:
			return SEEK_END;

		default:
			return 0;
	}
}
