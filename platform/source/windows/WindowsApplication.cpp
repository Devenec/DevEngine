/**
 * @file platform/windows/WindowsApplication.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Application.h>
#include <core/Types.h>

using namespace Core;

#if defined(DE_CONFIG_DEVENGINE_MAIN)
	Int32 wmain(Int32 argumentCount, Char16** arguments)
	{
		StartupParameters startupParameters(argumentCount);

		for(Int32 i = 0; i < argumentCount; ++i)
			startupParameters[i] = toString8(arguments[i]);

		devEngineMain(startupParameters);
		return 0;
	}
#endif
