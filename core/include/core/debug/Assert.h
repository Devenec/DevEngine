/**
 * @file core/debug/Assert.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Platform.h>
#include <core/UtilityMacros.h>
#include <core/Types.h>

/**
 * Calls Debug::failAssertion() if "expression" evaluates to false.
 *
 * @param expression
 *   A boolean expression to evaluate
 */
#if DE_BUILD_CONFIG == DE_BUILD_CONFIG_PRODUCTION
	#define DE_ASSERT(expression) \
		DE_NO_OPERATION
#else
	#define DE_ASSERT(expression) \
		(expression) ? DE_NO_OPERATION : Debug::failAssertion(DE_STRING8(expression), DE_FILE, DE_FUNCTION, DE_LINE)
#endif

namespace Debug
{
	/**
	 * Fails an assertion.
	 *
	 * Logs the assertion failure, breaks the debugger and finally aborts the program execution.
	 *
	 * @param expression
	 *   The expression that caused the assertion failure, as a string
	 * @param file
	 *   The path of the file in which the assertion failed
	 * @param function
	 *   The name of the function in which the assertion failed
	 * @param line
	 *   The line number on which the assertion failed
	 */
	void failAssertion(const Char8* expression, const Char8* file, const Char8* function, const Uint32 line);
}
