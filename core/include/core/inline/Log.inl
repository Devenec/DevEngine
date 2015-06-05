/**
 * @file core/inline/Log.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

LogLevel Log::filterLevel() const
{
	return _filterLevel;
}

void Log::setfilterLevel(const LogLevel& value)
{
	_filterLevel = value;
}

// Operators

Log& Log::operator <<(const Char16* characters)
{
	_stream << toString8(characters);
	return *this;
}

Log& Log::operator <<(const Flush& flush)
{
	static_cast<Void>(flush);
	write(_streamLevel, _stream.str());
	_stream.str(String8());
	_streamLevel = LogLevel::Debug;

	return *this;
}

Log& Log::operator <<(const LogLevel& logLevel)
{
	_streamLevel = logLevel;
	return *this;
}

template<typename T>
Log& Log::operator <<(const T& value)
{
	_stream << value;
	return *this;
}

// Private

Log::Log()
	: _filterLevel(LogLevel::Debug),
	  _streamLevel(LogLevel::Debug) { }
