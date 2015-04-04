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

		const DisplayMode& currentDisplayMode() const;

		void setDisplayMode(const DisplayMode& mode);

		const DisplayModes& supportedDisplayModes() const;

	private:

		friend class GraphicsAdapterManager;

		class Impl;
		
		Impl* _impl;

		GraphicsAdapter(const Core::String8& name, const DisplayModes& supportedDisplayModes,
			const Uint32 currentDisplayModeIndex);

		GraphicsAdapter(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter(GraphicsAdapter&& graphicsAdapter) = delete;
		~GraphicsAdapter();

		GraphicsAdapter& operator =(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter& operator =(GraphicsAdapter&& graphicsAdapter) = delete;
	};
}
