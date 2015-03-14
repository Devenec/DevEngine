/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

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

	log.write(LogLevel::Debug, "Hello w\xC3\xB6rld!");
	String8 message("Hello w\xC3\xB6rld!");
	log.write(LogLevel::Debug, message);

	log << LogLevel::Info << "Hell" << 0 << " w\xC3\xB6rld" << '!' << ' ' << 66.6f <<
		DE_CHAR16(" \x043A\x043E\x0448\x043A\x0430 ") << Log::flush;

	log.setfilterLevel(LogLevel::Error);
	log.write(LogLevel::Info, "This should not be logged");

	Debug::StackTrace stackTrace(10u);
	Debug::StackEntries stackEntries = stackTrace.generate();
	log.setfilterLevel(LogLevel::Debug);
	log << LogLevel::Debug << "Stack trace:\n";

	for(Uint32 i = 0u, size = stackEntries.size(); i < size; i++)
	{
		if(i != 0u)
			log << '\n';

		log << '\t' << i << ": " << stackEntries[i].functionName << " (0x" << std::hex << stackEntries[i].address <<
			std::dec << ") @ " << stackEntries[i].filepath << " on line " << stackEntries[i].fileLine;
	}

	log << Log::flush;
	
	DE_ASSERT(true);
	//DE_ASSERT(false);

	return 0;
}
