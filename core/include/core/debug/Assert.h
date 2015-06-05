/**
 * @file core/debug/Assert.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>

#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_ASSERT(expression) \
		DE_NO_OPERATION
#else
	#define DE_ASSERT(expression) \
		(expression) ? DE_NO_OPERATION : Debug::failAssertion(DE_STRING8(expression), DE_FILE, DE_LINE, DE_FUNCTION)
#endif

namespace Debug
{
	void failAssertion(const Char8* expression, const Char8* file, const Uint32 line, const Char8* function);
}
