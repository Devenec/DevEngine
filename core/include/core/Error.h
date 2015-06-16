/**
 * @file core/Error.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <core/debug/Assert.h>

#if DE_BUILD == DE_BUILD_PRODUCTION
	#define DE_ERROR(errorCode) \
		Core::invokeError(errorCode)
#else
	#define DE_ERROR(errorCode) \
		Debug::failAssertion("Error code " DE_STRING8(errorCode), DE_FILE, DE_LINE, DE_FUNCTION)
#endif

namespace Core
{
	void invokeError(const Uint32 errorCode);
}
