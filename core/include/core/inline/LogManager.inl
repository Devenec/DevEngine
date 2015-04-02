/**
 * @file core/inline/LogManager.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

LogManager::LogManager()
{
	initialise();
}

Log& LogManager::log()
{
	return _log;
}
