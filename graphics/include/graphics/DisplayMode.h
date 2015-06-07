/**
 * @file graphics/DisplayMode.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>

namespace Graphics
{
	class DisplayMode final
	{
	public:

		inline DisplayMode();

		inline DisplayMode(const Uint32 width, const Uint32 height, const Uint32 colourDepth, const Uint32 frequency);

		DisplayMode(const DisplayMode& displayMode) = default;

		DisplayMode(DisplayMode&& displayMode) = default;

		~DisplayMode() = default;

		inline Uint32 colourDepth() const;

		inline Uint32 frequency() const;

		inline Uint32 height() const;

		inline Uint32 width() const;

		DisplayMode& operator =(const DisplayMode& displayMode) = default;

		DisplayMode& operator =(DisplayMode&& displayMode) = default;

		inline Bool operator ==(const DisplayMode& displayMode) const;

		inline Bool operator !=(const DisplayMode& displayMode) const;

		Bool operator <(const DisplayMode& displayMode) const;

	private:

		Uint32 _colourDepth;
		Uint32 _frequency;
		Uint32 _height;
		Uint32 _width;
	};

#include "inline/DisplayMode.inl"
}
