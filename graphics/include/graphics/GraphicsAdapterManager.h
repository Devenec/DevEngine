/**
 * @file graphics/GraphicsAdapterManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Singleton.h>
#include <core/Vector.h>

namespace Graphics
{
	class GraphicsAdapter;

	using GraphicsAdapterList = Core::Vector<GraphicsAdapter*>;

	class GraphicsAdapterManager final : public Core::Singleton<GraphicsAdapterManager>
	{
	public:

		GraphicsAdapterManager();

		GraphicsAdapterManager(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager(GraphicsAdapterManager&& graphicsAdapterManager) = delete;

		~GraphicsAdapterManager() = default;

		void deinitialise();

		const GraphicsAdapterList& graphicsAdapters() const;

		void initialise();

		GraphicsAdapterManager& operator =(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager& operator =(GraphicsAdapterManager&& graphicsAdapterManager) = delete;

	private:

		class Impl;

		Impl* _impl;
	};
}
