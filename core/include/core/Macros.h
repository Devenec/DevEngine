/**
 * @file core/Macros.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/MacrosInternals.h>

// Functions

#define DE_ARGS(...) \
	, ## __VA_ARGS__

#define DE_STRING(value) \
	_DE_STRING(value)

#define DE_TEXT(text) \
	text


// Variables

#define DE_FILE DE_TEXT(__FILE__)

#define DE_FUNCTION _DE_FUNCTION

#define DE_LINE __LINE__

#define DE_NO_OP _DE_NO_OP
