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

void Log::setfilterLevel(const LogLevel& level)
{
	_filterLevel = level;
}

// Operators

Log& Log::operator <<(const Char16* characters)
{
	DE_ASSERT(characters != nullptr);
	_stream << toString8(characters);

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
