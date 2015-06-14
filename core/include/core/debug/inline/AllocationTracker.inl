/**
 * @file core/debug/inline/AllocationTracker.inl
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

AllocationTracker::AllocationTracker()
	: _isInitialised(false) { }

void AllocationTracker::deinitialise()
{
	_isInitialised = false;
	checkForMemoryLeaks();
}

void AllocationTracker::initialise()
{
	_isInitialised = true;
}
