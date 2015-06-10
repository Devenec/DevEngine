/**
 * @file platform/windows/WindowsApplication.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/ConfigMacros.h>
#include <core/FileSystem.h>
#include <core/LogManager.h>
#include <core/Platform.h>
#include <core/Types.h>

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define _DE_TRACK_ALLOCATIONS
	#include <core/debug/AllocationTracker.h>

	using namespace Debug;
#endif

using namespace Core;

#if defined(DE_CONFIG_DEVENGINE_MAIN)
Int32 wmain(Int32 argumentCount, Char16** arguments)
{
#if defined(_DE_TRACK_ALLOCATIONS)
	AllocationTracker allocationTracker;
	allocationTracker.initialise();
#endif

	LogManager logManager;
	logManager.initialise();
	FileSystem fileSystem;
	fileSystem.initialise();
	StartupParameters startupParameters(argumentCount);

	for(Int32 i = 0; i < argumentCount; ++i)
		startupParameters[i] = toString8(arguments[i]);

	devEngineMain(startupParameters);
	fileSystem.deinitialise();
	logManager.deinitialise();

#if defined(_DE_TRACK_ALLOCATIONS)
	allocationTracker.deinitialise();
#endif

	return 0;
}
#endif
