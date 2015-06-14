/**
 * @file platform/windows/WindowsFileStream.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/FileStream.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <platform/windows/Windows.h>

using namespace Core;

static const Char8* FILESTREAM_CONTEXT = "[Platform::WindowsFileStream]";

// Implementation

// TODO: support very long filepaths?
class FileStream::Impl final
{
public:

	Impl()
		: _handle(nullptr),
		  _openMode(static_cast<OpenMode>(0)) { }

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	void close()
	{
		if(_handle != nullptr)
		{
			if((_openMode & OpenMode::Write) == OpenMode::Write)
				flushBuffer();
			
			const Int32 result = CloseHandle(_handle);

			if(result == 0)
			{
				defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to close a file." << Log::Flush();
				DE_ERROR_WINDOWS(0); // TODO: set errorCode
			}

			_openMode = static_cast<OpenMode>(0);
			_handle = nullptr;
		}
	}

	Bool isAtEndOfFile() const
	{
		return position() >= size();
	}

	void open(const String8& filepath, const OpenMode& openMode)
	{
		DE_ASSERT(_handle == nullptr);
		const String16 filepath16 = toString16(filepath).c_str();
		const Uint32 accessMode = getAccessMode(openMode);
		const Uint32 creationMode = getCreationMode(openMode);

		// TODO: support FILE_FLAG_RANDOM_ACCESS/FILE_FLAG_SEQUENTIAL_ACCESS?
		_handle = CreateFileW(filepath16.c_str(), accessMode, FILE_SHARE_READ, nullptr, creationMode,
			FILE_ATTRIBUTE_NORMAL, nullptr);

		if(_handle == INVALID_HANDLE_VALUE)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to open file '" << filepath << "'." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}

		_openMode = openMode;
	}

	Int64 position() const
	{
		LARGE_INTEGER offset;
		offset.QuadPart = 0;
		LARGE_INTEGER position;
		const Int32 result = SetFilePointerEx(_handle, offset, &position, FILE_CURRENT);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to get the position of a file pointer." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}

		return position.QuadPart;
	}

	Uint32 read(Byte* buffer, const Uint32 byteCount) const
	{
		DE_ASSERT((_openMode & OpenMode::Read) == OpenMode::Read);
		unsigned long byteCountRead;
		const Int32 result = ReadFile(_handle, buffer, byteCount, &byteCountRead, nullptr);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to read a file." << Log::Flush();
			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}

		return byteCountRead;
	}

	void seek(const Int64 position) const
	{
		seek(SeekPosition::Begin, position);
	}

	void seek(const SeekPosition& position, const Int64 offset) const
	{
		LARGE_INTEGER seekOffset;
		seekOffset.QuadPart = offset;
		const Int32 result = SetFilePointerEx(_handle, seekOffset, nullptr, static_cast<Int32>(position));

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to seek a file." << Log::Flush();
			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}
	}

	Int64 size() const
	{
		LARGE_INTEGER size;
		const Int32 result = GetFileSizeEx(_handle, &size);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to get the size of a file." <<
				Log::Flush();

			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}

		return size.QuadPart;
	}

	Uint32 write(const Byte* data, const Uint32 byteCount) const
	{
		DE_ASSERT((_openMode & OpenMode::Write) == OpenMode::Write);
		unsigned long byteCountWritten;
		const Int32 result = WriteFile(_handle, data, byteCount, &byteCountWritten, nullptr);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to write to a file." << Log::Flush();
			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}

		return byteCountWritten;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	HANDLE _handle;
	OpenMode _openMode;

	void flushBuffer() const
	{
		const Int32 result = FlushFileBuffers(_handle);

		if(result == 0)
		{
			defaultLog << LogLevel::Error << FILESTREAM_CONTEXT << " Failed to flush the file buffer." << Log::Flush();
			DE_ERROR_WINDOWS(0); // TODO: set errorCode
		}
	}

	Uint32 getAccessMode(const OpenMode& openMode) const
	{
		Uint32 mode = 0u;

		if((openMode & OpenMode::Read) == OpenMode::Read)
			mode |= GENERIC_READ;

		if((openMode & OpenMode::Write) == OpenMode::Write)
			mode |= GENERIC_WRITE;

		return mode;
	}

	Uint32 getCreationMode(const OpenMode& openMode) const
	{
		Uint32 mode = 0u;

		if((openMode & OpenMode::Read) == OpenMode::Read)
			mode = OPEN_EXISTING;

		if((openMode & OpenMode::Write) == OpenMode::Write)
			mode = OPEN_ALWAYS;

		return mode;
	}
};


// Public

FileStream::FileStream()
	: _impl(DE_NEW(Impl)()) { }

FileStream::FileStream(const String8& filepath, const OpenMode& openMode)
	: _impl(DE_NEW(Impl)())
{
	_impl->open(filepath, openMode);
}

FileStream::~FileStream()
{
	DE_DELETE(_impl, Impl);
}

void FileStream::close() const
{
	_impl->close();
}

Bool FileStream::isAtEndOfFile() const
{
	return _impl->isAtEndOfFile();
}

void FileStream::open(const String8& filepath, const OpenMode& openMode) const
{
	_impl->open(filepath, openMode);
}

Int64 FileStream::position() const
{
	return _impl->position();
}

Uint32 FileStream::read(Byte* buffer, const Uint32 byteCount) const
{
	return _impl->read(buffer, byteCount);
}

void FileStream::seek(const Int64 position) const
{
	_impl->seek(position);
}

void FileStream::seek(const SeekPosition& position, const Int64 offset) const
{
	_impl->seek(position, offset);
}

Int64 FileStream::size() const
{
	return _impl->size();
}

Uint32 FileStream::write(const Byte* data, const Uint32 byteCount) const
{
	return _impl->write(data, byteCount);
}
