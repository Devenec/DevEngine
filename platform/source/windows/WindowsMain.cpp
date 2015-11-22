/**
 * @file platform/windows/WindowsMain.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <core/Application.h>
#include <core/Config.h>
#include <core/Main.h>
#include <core/Types.h>

using namespace Core;

// External

static void runDevEngineMain(const Int32 argumentCount, Char16** arguments);
static StartupParameters createStartupParameters(const Int32 argumentCount, Char16** arguments);

#if defined(DE_CONFIG_DEVENGINE_MAIN)

Int32 wmain(Int32 argumentCount, Char16** arguments)
{
	Application application;
	application.initialise();
	::runDevEngineMain(argumentCount, arguments);
	application.deinitialise();

	return 0;
}

#endif

static void runDevEngineMain(const Int32 argumentCount, Char16** arguments)
{
	StartupParameters startupParameters = ::createStartupParameters(argumentCount, arguments);
	devEngineMain(startupParameters);
}

static StartupParameters createStartupParameters(const Int32 argumentCount, Char16** arguments)
{
	StartupParameters startupParameters(argumentCount);

	for(Int32 i = 0; i < argumentCount; ++i)
		startupParameters[i] = toString8(arguments[i]);

	return startupParameters;
}
