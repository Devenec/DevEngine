/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/Log.h>
#include <core/String.h>
#include <core/UtilityMacros.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

using namespace Core;
using namespace Graphics;

static void testLog(const StartupParameters& startupParameters);
static void testWindow();

void devEngineMain(const StartupParameters& startupParameters)
{
	testLog(startupParameters);
	testWindow();
}

static void testWindow()
{
	GraphicsAdapterManager graphicsAdapterManager;
	graphicsAdapterManager.initialise();
	WindowManager windowManager;
	windowManager.initialise();
	Window* window = windowManager.createWindow();
	window->setTitle("DevEngine - \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0");
	window->show();

	//window->setFullscreen(true);
	//window->setFullscreen(false);

	while(window->processMessages()) { }
	windowManager.deinitialise();
	graphicsAdapterManager.deinitialise();
}

static void testLog(const StartupParameters& startupParameters)
{
	defaultLog.write(LogLevel::Debug, "-- Startup parameters --");

	for(StartupParameters::const_iterator i = startupParameters.begin(), end = startupParameters.end(); i != end; ++i)
		defaultLog.write(LogLevel::Debug, *i);

	defaultLog.write(LogLevel::Debug, "-- End of startup parameters --");
	defaultLog.write(LogLevel::Debug, "Hello w\xC3\xB6rld!");
	const String8 message("Hello w\xC3\xB6rld!");
	defaultLog.write(LogLevel::Debug, message);

	defaultLog << LogLevel::Info << "Hell" << 0 << " w\xC3\xB6rld" << '!' <<
		" \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0 " << 66.6f << DE_CHAR16(" \x043A\x043E\x0448\x043A\x0430") <<
		Log::Flush();

	defaultLog.setfilterLevel(LogLevel::Warning);
	defaultLog.write(LogLevel::Info, "This should not be logged");
	defaultLog.setfilterLevel(LogLevel::Debug);
}
