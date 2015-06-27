/**
 * @file core/UtilityMacrosInternal.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

// Internal functions

#define _DE_CHAR16(literal) \
	L ## literal

#define _DE_STRING8(value) \
	#value


#include <core/Platform.h>
