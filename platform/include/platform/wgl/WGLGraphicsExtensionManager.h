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

	class GraphicsExtensionManager final
	{
	public:

		GraphicsExtensionManager() = delete;

		GraphicsExtensionManager(const GraphicsExtensionManager& graphicsExtensionManager) = delete;
		GraphicsExtensionManager(GraphicsExtensionManager&& graphicsExtensionManager) = delete;

		~GraphicsExtensionManager() = delete;

		static void initialiseExtensions(const GraphicsContextBase& graphicsContext);

		GraphicsExtensionManager& operator =(const GraphicsExtensionManager& graphicsExtensionManager) = delete;
		GraphicsExtensionManager& operator =(GraphicsExtensionManager&& graphicsExtensionManager) = delete;

	private:

		static const Char8* COMPONENT_TAG;

		static void validateContextState();
		static void getContextExtensionFunctions();
		static void logSupportedContextExtensions(HDC deviceContextHandle);
		static void getOpenGLExtensionFunction();

		template<typename T>
		static inline T getExtensionFunction(const Char8* functionName);
	};

#include "inline/WGLGraphicsExtensionManager.inl"
}
