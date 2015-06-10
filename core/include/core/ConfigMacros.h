/**
 * @file core/ConfigMacros.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

/**
 * If defined, a custom application entry point is used.
 *
 * For more information, see core/Application.h in which the entry point is
 * declared.
 */
#define DE_CONFIG_DEVENGINE_MAIN

/**
 * If defined, Debug::AllocationTracker (in core) is used to track memory leaks
 * in debug and release builds.
 */
#define DE_CONFIG_TRACK_ALLOCATIONS
