/**
 * @file core/Memory.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>
#include <core/UtilityMacros.h>

#define DE_ALLOC new (DE_FILE, DE_FUNCTION, DE_LINE)

#define DE_DEALLOC delete

void* operator new(Uint32 size, const Char8* file, const Char8* function, const Uint32 line);
