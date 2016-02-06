/**
 * @file platform/GraphicsFunctionUtility.h
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
 *
 * DevEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DevEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DevEngine. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <core/Set.h>
#include <core/String.h>
#include <core/Types.h>

namespace Platform
{
	using ExtensionNameSet = Core::Set<Core::String8>;

	class GraphicsFunctionUtility final
	{
	public:

		GraphicsFunctionUtility();

		GraphicsFunctionUtility(const GraphicsFunctionUtility& graphicsFunctionUtility) = delete;
		GraphicsFunctionUtility(GraphicsFunctionUtility&& graphicsFunctionUtility) = delete;

		~GraphicsFunctionUtility();

		template<typename T>
		inline T getExtensionFunction(const Char8* name, const Bool isRequired = true) const;

		template<typename T>
		inline T getStandardFunction(const Char8* name) const;

		GraphicsFunctionUtility& operator =(const GraphicsFunctionUtility& graphicsFunctionUtility) = delete;
		GraphicsFunctionUtility& operator =(GraphicsFunctionUtility&& graphicsFunctionUtility) = delete;

		static void checkExtensionSupport(const ExtensionNameSet& extensionNameSet,
			const Char8* extensionName);

	private:

		class Implementation;

		using Function = void (*)();

		Implementation* _implementation;

		Function getExtensionFunctionInternal(const Char8* name, const Bool isRequired) const;
		Function getStandardFunctionInternal(const Char8* name) const;
	};

#include "inline/GraphicsFunctionUtility.inl"
}
