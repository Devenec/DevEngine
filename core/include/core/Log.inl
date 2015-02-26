/**
 * @file core/Log.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

template<typename T>
void Log::write(const LogLevel& level, const StringTemplate<T>& message)
{
	if(level >= _filterLevel)
		writeToConsole(level, message);
}
