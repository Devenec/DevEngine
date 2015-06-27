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
#include <graphics/GraphicsContext.h>
#include <graphics/Image.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

using namespace Content;
using namespace Core;
using namespace Graphics;

static void testLog(const StartupParameters& startupParameters);
static void testFileStream();
static void testWindowAndGraphics();

void devEngineMain(const StartupParameters& startupParameters)
{
	testLog(startupParameters);
	testFileStream();
	testWindowAndGraphics();
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
	defaultLog << LogLevel::Debug << "File exists: 'assets/test.txt' - " <<
		FileSystem::fileExists("assets/test.txt") << ", 'assets/testi.txt' - " <<
		FileSystem::fileExists("assets/testi.txt") << Log::Flush();

	//

	FileStream fileStream;
	fileStream.open("assets/\xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0.txt", OpenMode::Read);
	const Uint64 fileStreamSize = fileStream.size() - 2u;
	Vector<Char8> buffer(static_cast<Uint32>(fileStreamSize + 1u));
	buffer[static_cast<Uint32>(fileStreamSize) - 1u] = '\0';
	
	const Uint32 bytesRead = fileStream.read(reinterpret_cast<Byte*>(buffer.data()),
		static_cast<Uint32>(fileStreamSize));

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

	fileStream.seek(SeekPosition::End, -18);
	fileStream.seek(SeekPosition::Current, 7);
	array[8] = '\0';
	fileStream.read(reinterpret_cast<Byte*>(array), 8u);

	defaultLog << LogLevel::Debug << "Read: " << array << ", current position: " << fileStream.position() << '.' <<
		Log::Flush();

	defaultLog << LogLevel::Debug << "Is at end of file: " << fileStream.isAtEndOfFile() << '.' << Log::Flush();
	fileStream.seek(SeekPosition::Begin, 43);

	defaultLog << LogLevel::Debug << "Is at end of file (after seek): " << fileStream.isAtEndOfFile() << '.' <<
		Log::Flush();

	//const char* writeData = "testing write... \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0!\n";
	//fileStream.write(reinterpret_cast<const Byte*>(writeData), 28);

	fileStream.close();
}

#include <platform/windows/Windows.h>
#include <gl/GL.h>

static void testWindowAndGraphics()
{
	ContentManager contentManager;
	Image* image = contentManager.load<Image>("assets/icon.png");
	GraphicsAdapterManager graphicsAdapterManager;
	graphicsAdapterManager.initialise();
	WindowManager windowManager;
	windowManager.initialise();

	Window* window = windowManager.createWindow();
	window->setIcon(image);
	window->setTitle("DevEngine - \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0");
	window->show();

	/*Window* window2 = windowManager.createWindow();
	window2->setTitle("A second window!");
	window2->setCursorVisibility(false);
	window2->show();*/

	//window->setFullscreen(true);
	//window->setFullscreen(false);

	GraphicsContext graphicsContext;
	graphicsContext.initialise(window);
	graphicsContext.makeCurrent();
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	while(window->shouldClose())// || window2->shouldClose())
	{
		windowManager.processMessages();
		glClear(GL_COLOR_BUFFER_BIT);
		graphicsContext.swapBuffers();
	}
}
