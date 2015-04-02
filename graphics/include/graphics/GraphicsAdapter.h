/**
 * @file graphics/GraphicsAdapter.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/DisplayMode.h>

namespace Graphics
{
	using DisplayModes = Core::Vector<DisplayMode>;

	class GraphicsAdapter final
	{
	public:

		~GraphicsAdapter() = default;

		inline const DisplayMode& currentDisplayMode() const;

		inline const Core::String8& name() const;

		inline const DisplayModes& supportedDisplayModes() const;

	private:

		friend class WindowManager;

		Core::String8 _name;
		DisplayModes _supportedDisplayModes;
		Uint32 _currentDisplayModeIndex;

		inline GraphicsAdapter(const Core::String8& name, const DisplayModes& supportedDisplayModes,
			const Uint32 currentDisplayModeIndex);

		GraphicsAdapter(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter(GraphicsAdapter&& graphicsAdapter) = delete;

		GraphicsAdapter& operator =(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter& operator =(GraphicsAdapter&& graphicsAdapter) = delete;
	};

#include "inline/GraphicsAdapter.inl"
}
