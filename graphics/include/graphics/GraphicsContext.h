/**
 * @file graphics/GraphicsContext.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

namespace Graphics
{
	class Window;

	class GraphicsContext final
	{
	public:

		GraphicsContext();

		GraphicsContext(const GraphicsContext& graphicsContext) = delete;
		GraphicsContext(GraphicsContext&& graphicsContext) = delete;

		~GraphicsContext();

		void initialise(Window* window);

		void swapBuffers() const;

		GraphicsContext& operator =(const GraphicsContext& graphicsContext) = delete;
		GraphicsContext& operator =(GraphicsContext&& graphicsContext) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
