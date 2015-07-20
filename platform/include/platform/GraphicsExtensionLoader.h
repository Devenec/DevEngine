/**
 * @file platform/GraphicsExtensionLoader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <core/String.h>
#include <core/Types.h>
#include <core/Vector.h>

namespace Platform
{
	class GraphicsContextBase;

	class GraphicsExtensionLoader final
	{
	public:

		GraphicsExtensionLoader() = delete;

		GraphicsExtensionLoader(const GraphicsExtensionLoader& graphicsExtensionLoader) = delete;
		GraphicsExtensionLoader(GraphicsExtensionLoader&& graphicsExtensionLoader) = delete;

		~GraphicsExtensionLoader() = delete;

		GraphicsExtensionLoader& operator =(const GraphicsExtensionLoader& graphicsExtensionLoader) = delete;
		GraphicsExtensionLoader& operator =(GraphicsExtensionLoader&& graphicsExtensionLoader) = delete;

		static void loadContextExtensions(const GraphicsContextBase& graphicsContext);

		static void loadInterfaceExtensions();

	private:

		using ExtensionNameList = Core::Vector<Core::String8>;

		static const Uint32 LOG_COLUMN_WIDTH;

		class Impl;

		static void logSupportedContextExtensions(const Core::String8& extensionsString);
		static void logSupportedInterfaceExtensions(const ExtensionNameList& extensionNames);
		static ExtensionNameList splitExtensionsString(const Core::String8& extensionsString);
		static void logSupportedExtensions(const ExtensionNameList& extensionNames);
	};
}
