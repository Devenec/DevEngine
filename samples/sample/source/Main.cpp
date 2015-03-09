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
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>
#include <core/debug/StackTrace.h>

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

	Debug::StackTrace stackTrace(10u);
	Debug::StackEntries stackEntries = stackTrace.generate();
	log.setfilterLevel(LogLevel::Debug);
	log << LogLevel::Debug << DE_TEXT("Stack trace:\n");

	for(Uint32 i = 0u, size = stackEntries.size(); i < size; i++)
	{
		if(i != 0u)
			log << DE_TEXT('\n');

		log << DE_TEXT('\t') << i << DE_TEXT(": ") << stackEntries[i].functionName << DE_TEXT(" (0x") << std::hex <<
			stackEntries[i].address << std::dec << DE_TEXT(") @ ") << stackEntries[i].filepath <<
			DE_TEXT(" on line ") << stackEntries[i].fileLine;
	}

	log << Log::flush;
	
	DE_ASSERT(true);
	//DE_ASSERT(false);

	return 0;
}
