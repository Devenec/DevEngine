/**
 * @file core/Memory.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_NEW new
#else
	#define DE_NEW new (DE_FILE, DE_FUNCTION, DE_LINE)
#endif

#define DE_DELETE delete

Void* operator new(Uint32 size, const Char8* file, const Char8* function, const Uint32 line);

Void* operator new[](Uint32 size, const Char8* file, const Char8* function, const Uint32 line);
