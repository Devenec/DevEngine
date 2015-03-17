/**
 * @file core/Application.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/ConfigMacros.h>
#include <core/String.h>
#include <core/Vector.h>

namespace Core
{
	using StartupParameters = Vector<String8>;
}

#if defined(DE_CONFIG_DEVENGINE_MAIN)
	/**
	 * A custom application entry point.
	 *
	 * @params startupParameters
	 *   Command line parameters
	 */
	extern void devEngineMain(const Core::StartupParameters& startupParameters);
#endif
