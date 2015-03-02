/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/ConfigMacros.h>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/String.h>

using namespace Core;

int main()
{
	LogManager logManager;
	Log& log = logManager.log();

#if defined(DE_CONFIG_CHAR16)
	String16 message(L"Hello wörld!");
	log.write(LogLevel::Debug, L"Hello wörld!");
	log.write(LogLevel::Debug, message);

	log << LogLevel::Info << L"Hell" << 0 << L" wörld" << L'!' << L' ' << 66.6f << Log::flush;

	log.setfilterLevel(LogLevel::Error);
	log.write(LogLevel::Info, L"This should not be logged");
#else
	String8 message("Hello world!");
	log.write(LogLevel::Debug, "Hello world!");
	log.write(LogLevel::Debug, message);

	log << LogLevel::Info << "Hell" << 0 << " world" << '!' << ' ' << 66.6f << Log::flush;

	log.setfilterLevel(LogLevel::Error);
	log.write(LogLevel::Info, "This should not be logged");
#endif

	return 0;
}
