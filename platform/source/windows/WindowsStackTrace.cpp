/**
 * @file platform/windows/WindowsStackTrace.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

// Implementation

class StackTrace::Impl final
{
public:

	Impl(const Uint32 maxEntryCount)
		: _symbolAddresses(maxEntryCount),
		  _processHandle(GetCurrentProcess()),
		  _symbolInfo(reinterpret_cast<SYMBOL_INFOW*>(_symbolInfoMemory.data())),
		  _maxEntryCount(maxEntryCount)
	{
		if(maxEntryCount > Numeric<Uint16>::maximum())
		{
			defaultLog << LogLevel::Warning << "[Platform::WindowsStackTrace] maxEntryCount is too large and is"
				" clamped to Numeric<Uint16>::maximum()." << Log::Flush();

			this->_maxEntryCount = Numeric<Uint16>::maximum();
		}

		_sourceInfo.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);
		_symbolInfo->MaxNameLen = MAX_FUNCTION_NAME_LENGTH;
		_symbolInfo->SizeOfStruct = sizeof(SYMBOL_INFOW);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = default;

	StackEntryList generate()
	{
		const Uint32 entryCount = RtlCaptureStackBackTrace(0u, _maxEntryCount, _symbolAddresses.data(), nullptr);
		StackEntryList entries;

		if(entryCount > 0u)
		{
			initialiseSymbolHandler();
			entries = getStackEntries(entryCount);
			deinitialiseSymbolHandler();
		}

		return entries;
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	static constexpr Uint32 MAX_FUNCTION_NAME_LENGTH = 256u;

	Array<Byte, sizeof(SYMBOL_INFOW) + (MAX_FUNCTION_NAME_LENGTH - 1u) * sizeof(Char16)> _symbolInfoMemory;
	IMAGEHLP_LINEW64 _sourceInfo;
	Vector<Void*> _symbolAddresses;
	HANDLE _processHandle;
	SYMBOL_INFOW* _symbolInfo;
	Uint32 _maxEntryCount;

	void initialiseSymbolHandler()
	{
		SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
		const Int32 result = SymInitialize(_processHandle, nullptr, TRUE); // TODO: support UserSearchPath?
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

	void deinitialiseSymbolHandler()
	{
		const Int32 result = SymCleanup(_processHandle);
		DE_ASSERT_WINDOWS(result != 0);
	}

	void getSymbolInfo(const Uint64 address)
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


// Public

StackTrace::StackTrace(const Uint32 maxEntryCount)
	: _impl(DE_NEW Impl(maxEntryCount)) { }

StackTrace::~StackTrace()
{
	DE_DELETE _impl;
}

StackEntryList StackTrace::generate() const
{
	return _impl->generate();
}
