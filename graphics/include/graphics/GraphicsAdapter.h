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
	using DisplayModeList = Core::Vector<DisplayMode>;

	class GraphicsAdapter final
	{
	public:

		GraphicsAdapter(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter(GraphicsAdapter&& graphicsAdapter) = delete;

		const DisplayMode& currentDisplayMode() const;

		void setDisplayMode(const DisplayMode& mode) const;

		const DisplayModeList& supportedDisplayModes() const;

		GraphicsAdapter& operator =(const GraphicsAdapter& graphicsAdapter) = delete;
		GraphicsAdapter& operator =(GraphicsAdapter&& graphicsAdapter) = delete;

	private:

		friend class GraphicsAdapterManager;

		class Impl;
		
		Impl* _impl;

		GraphicsAdapter(const Core::String8& name, const DisplayModeList& supportedDisplayModes,
			const Uint32 currentDisplayModeIndex);

		~GraphicsAdapter();
	};
}
