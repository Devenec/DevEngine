/**
 * @file core/Variadic.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <cstdarg>

/**
 * Gets the next parameter from a variable parameter list.
 */
#define VariadicParameter(parameterList, parameterType) \
	va_arg(parameterList, parameterType)

/**
 * Begins the access to a variable parameter list.
 */
#define VariadicBegin(parameterList, namedParameter) \
	va_start(parameterList, namedParameter)

/**
 * Ends the access to a variable parameter list.
 */
#define VariadicEnd(parameterList) \
	va_end(parameterList)

namespace Core
{
	/**
	 * Variable parameter list
	 */
	using ParameterList = std::va_list;
}
