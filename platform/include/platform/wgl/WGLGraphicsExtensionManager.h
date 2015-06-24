/**
 * @file platform/wgl/WGLGraphicsExtensionManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>
#include <platform/windows/Windows.h>

namespace Platform
{
	class GraphicsContextBase;

	class GraphicsExtensionManager
	{
	public:

		GraphicsExtensionManager() = default;

		GraphicsExtensionManager(const GraphicsExtensionManager& graphicsExtensionManager) = delete;
		GraphicsExtensionManager(GraphicsExtensionManager&& graphicsExtensionManager) = delete;

		~GraphicsExtensionManager() = default;

		void initialiseExtensions(const GraphicsContextBase& graphicsContext) const;

		GraphicsExtensionManager& operator =(const GraphicsExtensionManager& graphicsExtensionManager) = delete;
		GraphicsExtensionManager& operator =(GraphicsExtensionManager&& graphicsExtensionManager) = delete;

	private:

		static void validateContextState();
		static void getContextExtensionFunctions();
		static void logSupportedContextExtensions(HDC deviceContextHandle);
		static void getOpenGLExtensionFunction();

		template<typename T>
		static inline T getExtensionFunction(const Char8* name);
	};

#include "inline/WGLGraphicsExtensionManager.inl"
}
