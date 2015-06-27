/**
 * @file platform/windows/WindowsApplication.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/ConfigMacros.h>
#include <core/LogManager.h>
#include <core/Platform.h>
#include <core/Types.h>

#if DE_BUILD != DE_BUILD_PRODUCTION && defined(DE_CONFIG_TRACK_ALLOCATIONS)
	#define _DE_TRACK_ALLOCATIONS
	#include <core/debug/AllocationTracker.h>

	static Debug::AllocationTracker allocationTracker;
#endif

using namespace Core;

static LogManager logManager;

static StartupParameters createStartupParameters(const Int32 argumentCount, Char16** arguments);

#if defined(DE_CONFIG_DEVENGINE_MAIN)
Int32 wmain(Int32 argumentCount, Char16** arguments)
{
	logManager.initialise();

#if defined(_DE_TRACK_ALLOCATIONS)
	allocationTracker.initialise();
#endif

	StartupParameters startupParameters = createStartupParameters(argumentCount, arguments);
	devEngineMain(startupParameters);

#if defined(_DE_TRACK_ALLOCATIONS)
	allocationTracker.deinitialise();
#endif

	logManager.deinitialise();
	return 0;
}
#endif

static StartupParameters createStartupParameters(const Int32 argumentCount, Char16** arguments)
{
	StartupParameters startupParameters(argumentCount);

	for(Int32 i = 0; i < argumentCount; ++i)
		startupParameters[i] = toString8(arguments[i]);

	return startupParameters;
}
