/**
 * @file platform/windows/WindowsStackTrace.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#include <core/Array.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Numeric.h>
#include <core/UtilityMacros.h>
#include <core/debug/StackTrace.h>
#include <platform/windows/Windows.h>
#include <DbgHelp.h> // Needs to be included after Windows.h (platform/windows/Windows.h)

using namespace Core;
using namespace Debug;

// External

static constexpr Uint32 MAX_FUNCTION_NAME_LENGTH = 256u;

static const Char8* COMPONENT_TAG = "[Debug::StackTrace - Windows] ";


// Implementation

class StackTrace::Implementation final
{
public:

	explicit Implementation(const Uint32 maxEntryCount)
		: _symbolAddresses(maxEntryCount),
		  _processHandle(GetCurrentProcess()),
		  _symbolInfo(reinterpret_cast<SYMBOL_INFOW*>(_symbolInfoMemory.data())),
		  _maxEntryCount(maxEntryCount)
	{
		if(maxEntryCount > Numeric<Uint16>::maximum())
		{
			defaultLog << LogLevel::Warning << ::COMPONENT_TAG <<
				"maxEntryCount is too large and is clamped to Core::Numeric<Uint16>::maximum()." << Log::Flush();

			_maxEntryCount = Numeric<Uint16>::maximum();
		}

		_sourceInfo.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);
		_symbolInfo->MaxNameLen = ::MAX_FUNCTION_NAME_LENGTH;
		_symbolInfo->SizeOfStruct = sizeof(SYMBOL_INFOW);
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation() = default;

	StackEntryList generate(const Uint32 stackFrameOffset)
	{
		const Uint32 entryCount = RtlCaptureStackBackTrace(stackFrameOffset, _maxEntryCount, _symbolAddresses.data(),
			nullptr);

		StackEntryList entries;

		if(entryCount > 0u)
		{
			initialiseSymbolHandler();
			entries = getStackEntries(entryCount);
			deinitialiseSymbolHandler();
		}

		return entries;
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	Array<Uint8, sizeof(SYMBOL_INFOW) + (::MAX_FUNCTION_NAME_LENGTH - 1u) * sizeof(Char16)> _symbolInfoMemory;
	IMAGEHLP_LINEW64 _sourceInfo;
	Vector<Void*> _symbolAddresses;
	HANDLE _processHandle;
	SYMBOL_INFOW* _symbolInfo;
	Uint32 _maxEntryCount;

	void initialiseSymbolHandler() const
	{
		SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
		const Int32 result = SymInitialize(_processHandle, nullptr, TRUE);
		DE_ASSERT_WINDOWS(result != 0);
	}

	StackEntryList getStackEntries(const Uint32 entryCount)
	{
		StackEntryList entries(entryCount);

		for(Uint32 i = 0u; i < entryCount; ++i)
		{
			const Uint64 address = reinterpret_cast<Uint64>(_symbolAddresses[i]);
			getSymbolInfo(address);
			entries[i].filepath = toString8(_sourceInfo.FileName);
			entries[i].functionName.assign(toString8(String16(_symbolInfo->Name, _symbolInfo->NameLen)));
			entries[i].address = address;
			entries[i].fileLine = _sourceInfo.LineNumber;
		}

		return entries;
	}

	void deinitialiseSymbolHandler() const
	{
		const Int32 result = SymCleanup(_processHandle);
		DE_ASSERT_WINDOWS(result != 0);
	}

	void getSymbolInfo(const Uint64& address)
	{
		Int32 result = SymFromAddrW(_processHandle, address, nullptr, _symbolInfo);
		DE_ASSERT_WINDOWS(result != 0);
		unsigned long displacement;
		result = SymGetLineFromAddrW64(_processHandle, address, &displacement, &_sourceInfo);

		if(result == 0)
		{
			_sourceInfo.FileName = DE_CHAR16("Unknown file");
			_sourceInfo.LineNumber = 0u;
		}
	}
};


// Debug::StackTrace

// Public

StackTrace::StackTrace(const Uint32 maxEntryCount)
	: _implementation(DE_NEW(Implementation)(maxEntryCount)) { }

StackTrace::~StackTrace()
{
	DE_DELETE(_implementation, Implementation);
}

StackEntryList StackTrace::generate(const Uint32 stackFrameOffset) const
{
	return _implementation->generate(stackFrameOffset);
}
