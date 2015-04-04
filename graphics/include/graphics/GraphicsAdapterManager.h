/**
 * @file graphics/GraphicsAdapterManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Singleton.h>
#include <core/Vector.h>
#include <graphics/GraphicsAdapter.h>

namespace Graphics
{
	using GraphicsAdapters = Core::Vector<GraphicsAdapter*>;

	class GraphicsAdapterManager final : public Core::Singleton<GraphicsAdapterManager>
	{
	public:

		GraphicsAdapterManager();

		~GraphicsAdapterManager();

		const GraphicsAdapters& graphicsAdapters() const;

	private:

		class Impl;

		Impl* _impl;

		GraphicsAdapterManager(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager(GraphicsAdapterManager&& graphicsAdapterManager) = delete;

		GraphicsAdapterManager& operator =(const GraphicsAdapterManager& graphicsAdapterManager) = delete;
		GraphicsAdapterManager& operator =(GraphicsAdapterManager&& graphicsAdapterManager) = delete;
	};
}
