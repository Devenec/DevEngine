/**
 * @file platform/windows/WindowsStackTrace.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Array.h>
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


// Implementation

class StackTrace::Impl final
{
public:

	Impl(const Uint32 maxEntryCount)
		: symbolAddresses(maxEntryCount),
		  processHandle(GetCurrentProcess()),
		  symbolInfo(reinterpret_cast<SymbolInfo*>(symbolInfoData.data())),
		  maxEntryCount(maxEntryCount)
	{
		// TODO: issue warning if maxEntryCount is clamped
		if(maxEntryCount > Numeric<Uint16>::maximum())
			this->maxEntryCount = Numeric<Uint16>::maximum();

		sourceInfo.SizeOfStruct = sizeof(sourceInfo);
		symbolInfo->MaxNameLen = MAX_FUNCTION_NAME_LENGTH;
		symbolInfo->SizeOfStruct = sizeof(SymbolInfo);
	}

	~Impl() = default;

	StackEntries generate()
	{
		const Uint32 entryCount = CaptureStackBackTrace(0u, maxEntryCount, symbolAddresses.data(), nullptr);
		StackEntries entries;

		if(entryCount > 0u)
		{
			initialiseSymbolHandler();
			entries = getStackEntries(entryCount);
			deinitialiseSymbolHandler();
		}

		return entries;
	}

private:

	using SourceInfo = IMAGEHLP_LINEW64;
	using SymbolInfo = SYMBOL_INFOW;

	Array<Byte, sizeof(SymbolInfo) + (MAX_FUNCTION_NAME_LENGTH - 1u) * sizeof(Char16)> symbolInfoData;
	SourceInfo sourceInfo;
	Vector<void*> symbolAddresses;
	HANDLE processHandle;
	SymbolInfo* symbolInfo;
	Uint32 maxEntryCount;
	
	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;
	
	void deinitialiseSymbolHandler()
	{
		const Int32 result = SymCleanup(processHandle);
		DE_ASSERT_WINDOWS(result != 0);
	}

	StackEntries getStackEntries(const Uint32 entryCount)
	{
		StackEntries entries(entryCount);

		for(Uint32 i = 0u; i < entryCount; ++i)
		{
			const Uint64 address = reinterpret_cast<Uint64>(symbolAddresses[i]);
			getSymbolInfo(address);
			entries[i].address = address;
			entries[i].filepath = toString8(sourceInfo.FileName);
			entries[i].functionName.assign(toString8(String16(symbolInfo->Name, symbolInfo->NameLen)));
			entries[i].fileLine = sourceInfo.LineNumber;
		}

		return entries;
	}

	inline void getSymbolInfo(const Uint64 address)
	{
		Int32 result = SymFromAddrW(processHandle, address, nullptr, symbolInfo);
		DE_ASSERT_WINDOWS(result != 0);
		unsigned long displacement;
		result = SymGetLineFromAddrW64(processHandle, address, &displacement, &sourceInfo);

		if(result == 0)
		{
			sourceInfo.FileName = DE_CHAR16("Unknown file");
			sourceInfo.LineNumber = 0u;
		}
	}
	
	void initialiseSymbolHandler()
	{
		SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
		const Int32 result = SymInitialize(processHandle, nullptr, 1);
		DE_ASSERT_WINDOWS(result != 0);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;
};


// Public

StackTrace::StackTrace(const Uint32 maxEntryCount)
	: _impl(DE_NEW Impl(maxEntryCount)) { }

StackTrace::~StackTrace()
{
	delete _impl;
}

StackEntries StackTrace::generate() const
{
	return _impl->generate();
}
