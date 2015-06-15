/**
 * @file graphics/GraphicsContext.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <graphics/Window.h>

namespace Graphics
{
	class GraphicsContext final
	{
	public:

		GraphicsContext();

		GraphicsContext(const GraphicsContext& graphicsContext) = delete;
		GraphicsContext(GraphicsContext&& graphicsContext) = delete;

		~GraphicsContext() = default;

		void deinitialise();

		void initialise(Window* window);

		GraphicsContext& operator =(const GraphicsContext& graphicsContext) = delete;
		GraphicsContext& operator =(GraphicsContext&& graphicsContext) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
