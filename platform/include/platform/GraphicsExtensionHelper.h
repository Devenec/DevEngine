/**
 * @file platform/GraphicsExtensionHelper.h
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
	using ExtensionNameList = Core::Vector<Core::String8>;

	class GraphicsExtensionHelper
	{
	public:

		GraphicsExtensionHelper() = delete;

		GraphicsExtensionHelper(const GraphicsExtensionHelper& graphicsExtensionHelper) = delete;
		GraphicsExtensionHelper(GraphicsExtensionHelper&& graphicsExtensionHelper) = delete;

		~GraphicsExtensionHelper() = delete;

		GraphicsExtensionHelper& operator =(const GraphicsExtensionHelper& graphicsExtensionHelper) = delete;
		GraphicsExtensionHelper& operator =(GraphicsExtensionHelper&& graphicsExtensionHelper) = delete;

		static void logExtensions(const Char8* description, const ExtensionNameList& extensionNames);

		template<typename T>
		static T getFunction(const Char8* name);

	private:

		static Void* getFunctionPointer(const Char8* name);
	};

#include "inline/GraphicsExtensionHelper.inl"
}
