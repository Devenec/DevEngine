/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <content/ContentManager.h>
#include <core/Application.h>
#include <core/FileStream.h>
#include <core/FileSystem.h>
#include <core/Log.h>
#include <core/String.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <core/Vector.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/Image.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

using namespace Content;
using namespace Core;
using namespace Graphics;

static void testLog(const StartupParameters& startupParameters);
static void testFileStream();
static void testWindow();

void devEngineMain(const StartupParameters& startupParameters)
{
	testLog(startupParameters);
	testFileStream();
	testWindow();
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
		" \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0 " << 66.6f << DE_CHAR16(" \x043A\x043E\x0448\x043A\x0430.") <<
		Log::Flush();

	defaultLog.setfilterLevel(LogLevel::Warning);
	defaultLog.write(LogLevel::Info, "This should not be logged.");
	defaultLog.setfilterLevel(LogLevel::Debug);
}

static void testFileStream()
{
	FileSystem& fileSystem = FileSystem::instance();

	defaultLog << LogLevel::Debug << "File exists: 'assets/test.txt' - " << fileSystem.fileExists("assets/test.txt") <<
		", 'assets/testi.txt' - " << fileSystem.fileExists("assets/testi.txt") << Log::Flush();

	//

	FileStream fileStream;
	fileStream.open("assets/\xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0.txt", OpenMode::Read);
	const Uint64 fileStreamSize = fileStream.size();
	Vector<Char8> buffer(static_cast<Uint32>(fileStreamSize));
	buffer[static_cast<Uint32>(fileStreamSize) - 1u] = '\0';
	
	const Uint32 bytesRead = fileStream.read(reinterpret_cast<Byte*>(buffer.data()),
		static_cast<Uint32>(fileStreamSize) - 1u);

	fileStream.close();

	defaultLog << LogLevel::Debug << "File size: " << fileStreamSize << " bytes, content: " << buffer.data() <<
		" (read " << bytesRead << " bytes)." << Log::Flush();

	//

	fileStream.open("assets/test.txt", OpenMode::Read | OpenMode::Write);
	fileStream.seek(8u);
	Char8 array[10];
	array[9] = '\0';
	fileStream.read(reinterpret_cast<Byte*>(array), 9u);

	defaultLog << LogLevel::Debug << "Read: " << array << ", current position: " << fileStream.position() << '.' <<
		Log::Flush();

	fileStream.seek(SeekPosition::End, -17);
	fileStream.seek(SeekPosition::Current, 7);
	array[8] = '\0';
	fileStream.read(reinterpret_cast<Byte*>(array), 8u);

	defaultLog << LogLevel::Debug << "Read: " << array << ", current position: " << fileStream.position() << '.' <<
		Log::Flush();

	defaultLog << LogLevel::Debug << "Is at end of file: " << fileStream.isAtEndOfFile() << '.' << Log::Flush();
	fileStream.seek(SeekPosition::Begin, 42);

	defaultLog << LogLevel::Debug << "Is at end of file (after seek): " << fileStream.isAtEndOfFile() << '.' <<
		Log::Flush();

	//const char* writeData = "testing write... \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0!\n";
	//fileStream.write(reinterpret_cast<const Byte*>(writeData), 28);

	fileStream.close();
}

static void testWindow()
{
	ContentManager contentManager;
	Image* image = contentManager.load<Image>("assets/icon.png");

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
