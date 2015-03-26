/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/Log.h>
#include <core/LogManager.h>
#include <core/String.h>
#include <core/UtilityMacros.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

using namespace Core;
using namespace Graphics;

void devEngineMain(const StartupParameters& startupParameters)
{
	Log& log = LogManager::instance().log();
	log.write(LogLevel::Debug, "Startup parameters:");

	for(StartupParameters::const_iterator i = startupParameters.begin(), end = startupParameters.end(); i != end; ++i)
		log.write(LogLevel::Debug, *i);

	log.write(LogLevel::Debug, "Hello w\xC3\xB6rld!");
	const String8 message("Hello w\xC3\xB6rld!");
	log.write(LogLevel::Debug, message);

	log << LogLevel::Info << "Hell" << 0 << " w\xC3\xB6rld" << '!' << " \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0 " <<
		66.6f << DE_CHAR16(" \x043A\x043E\x0448\x043A\x0430") << Log::flush;

	log.setfilterLevel(LogLevel::Warning);
	log.write(LogLevel::Info, "This should not be logged");
	log.setfilterLevel(LogLevel::Debug);

	WindowManager windowManager;
	Window* window = windowManager.createWindow();
	window->setTitle("DevEngine - \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0");
	window->show();

	while(window->processMessages()) { }
}
