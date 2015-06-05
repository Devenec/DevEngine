/**
 * @file core/Types.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Types.h>

static_assert(sizeof(Byte) == 1, "The size of Byte is incorrect.");
static_assert(sizeof(Int8) == 1, "The size of Int8 is incorrect.");
static_assert(sizeof(Uint8) == 1, "The size of Uint8 is incorrect.");
static_assert(sizeof(Int16) == 2, "The size of Int16 is incorrect.");
static_assert(sizeof(Uint16) == 2, "The size of Uint16 is incorrect.");
static_assert(sizeof(Int32) == 4, "The size of Int32 is incorrect.");
static_assert(sizeof(Uint32) == 4, "The size of Uint32 is incorrect.");
static_assert(sizeof(Int64) == 8, "The size of Int64 is incorrect.");
static_assert(sizeof(Uint64) == 8, "The size of Uint64 is incorrect.");
static_assert(sizeof(Float32) == 4, "The size of Float32 is incorrect.");
static_assert(sizeof(Float64) == 8, "The size of Float64 is incorrect.");
static_assert(sizeof(Char8) == 1, "The size of Char8 is incorrect.");
static_assert(sizeof(Char16) == 2, "The size of Char16 is incorrect.");
static_assert(sizeof(Void*) == 4, "The size of pointer is incorrect.");
