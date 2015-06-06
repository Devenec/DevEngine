/**
 * @file core/inline/FileStream.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Core

OpenMode operator &(const OpenMode& openModeA, const OpenMode& openModeB)
{
	return static_cast<OpenMode>(static_cast<Int32>(openModeA) & static_cast<Int32>(openModeB));
}

OpenMode& operator &=(OpenMode& openModeA, const OpenMode& openModeB)
{
	openModeA = openModeA & openModeB;
	return openModeA;
}

OpenMode operator |(const OpenMode& openModeA, const OpenMode& openModeB)
{
	return static_cast<OpenMode>(static_cast<Int32>(openModeA) | static_cast<Int32>(openModeB));
}

OpenMode& operator |=(OpenMode& openModeA, const OpenMode& openModeB)
{
	openModeA = openModeA | openModeB;
	return openModeA;
}
