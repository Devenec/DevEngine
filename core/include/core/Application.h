/**
 * @file core/Application.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Vector.h>

namespace Core
{
	using StartupParameters = Vector<String8>;
}

/**
 * A custom application entry point.
 *
 * @params startupParameters
 *   Command line parameters
 */
extern void devEngineMain(const Core::StartupParameters& startupParameters);
