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
	#define DE_NEW new (DE_FILE, DE_LINE, DE_FUNCTION)
#endif

#define DE_DELETE delete

#if DE_BUILD_CONFIG != DE_BUILD_CONFIG_PRODUCTION
	Void* operator new(Uint32 size, const Char8* file, const Uint32 line, const Char8* function);

	Void* operator new[](Uint32 size, const Char8* file, const Uint32 line, const Char8* function);
#endif
