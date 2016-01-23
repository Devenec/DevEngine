/**
 * @file platform/std/STDMain.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Main.h>

#if defined(DE_CONFIG_DEVENGINE_MAIN)

#include <core/Application.h>
#include <core/Types.h>

using namespace Core;

// External

static void runDevEngineMain(const Uint32 argumentCount, Char8** arguments);
static StartupParameters createStartupParameters(const Uint32 argumentCount, Char8** arguments);

Int32 main(Int32 argumentCount, Char8** arguments)
{
	Application application;
	application.initialise();
	::runDevEngineMain(argumentCount, arguments);
	application.deinitialise();

	return 0;
}

static void runDevEngineMain(const Uint32 argumentCount, Char8** arguments)
{
	StartupParameters startupParameters = ::createStartupParameters(argumentCount, arguments);
	devEngineMain(startupParameters);
}

static StartupParameters createStartupParameters(const Uint32 argumentCount, Char8** arguments)
{
	StartupParameters startupParameters(argumentCount);

	for(Uint32 i = 0u; i < argumentCount; ++i)
		startupParameters[i] = arguments[i];

	return startupParameters;
}

#endif
