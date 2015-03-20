/**
 * @file platform/windows/WindowsApplication.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/LogManager.h>
#include <core/Types.h>
#include <core/debug/AllocationTrace.h>

using namespace Core;
using namespace Debug;

#if defined(DE_CONFIG_DEVENGINE_MAIN)
	Int32 wmain(Int32 argumentCount, Char16** arguments)
	{
		AllocationTrace allocationTrace;
		allocationTrace.initialise();
		LogManager logManager;
		StartupParameters startupParameters(argumentCount);

		for(Int32 i = 0; i < argumentCount; ++i)
			startupParameters[i] = toString8(arguments[i]);

		devEngineMain(startupParameters);
		allocationTrace.deinitialise();

		return 0;
	}
#endif
