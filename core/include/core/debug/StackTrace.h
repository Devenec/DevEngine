/**
 * @file core/debug/StackTrace.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Debug
{
	struct StackEntry final
	{
		Core::String8 filepath;
		Core::String8 functionName;
		Uint64 address;
		Uint32 fileLine;
	};

	using StackEntryList = Core::Vector<StackEntry>;

	class StackTrace final
	{
	public:

		explicit StackTrace(const Uint32 maxEntryCount);

		StackTrace(const StackTrace& stackTrace) = delete;
		StackTrace(StackTrace&& stackTrace) = delete;

		~StackTrace();

		StackEntryList generate(const Uint32 stackFrameOffset = 0u) const;

		StackTrace& operator =(const StackTrace& stackTrace) = delete;
		StackTrace& operator =(StackTrace&& stackTrace) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
