/**
 * @file core/Log.inl
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

Log& Log::operator <<(const LogLevel& value)
{
	_streamLevel = value;
	return *this;
}

Log& Log::operator <<(const Flush& flush)
{
	flush(*this);
	return *this;
}

template<typename T>
Log& Log::operator <<(const T& value)
{
	_stream << value;
	return *this;
}

// Static

void Log::flush(Log& log)
{
	log.write(log._streamLevel, log._stream.str());
	log._stream.str(String());
}
