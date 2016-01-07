/**
 * @file content/ContentManager.h
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

#include <content/ContentLoader.h>
#include <core/FileStream.h>
#include <core/Map.h>
#include <core/Memory.h>
#include <core/String.h>

namespace Content
{
	class ContentBase;

	class ContentManager final
	{
	public:

		ContentManager();

		ContentManager(const ContentManager& contentManager) = delete;
		ContentManager(ContentManager&& contentManager) = delete;

		~ContentManager();

		inline const Core::String8& contentRootDirectory() const;

		inline void setContentRootDirectory(const Core::String8& directoryPath);

		template<typename T>
		T* load(const Core::String8& filepath);

		ContentManager& operator =(const ContentManager& contentManager) = delete;
		ContentManager& operator =(ContentManager&& contentManager) = delete;

	private:

		using ContentMap = Core::Map<Core::String8, ContentBase*>;

		Core::String8 _contentRootDirectory;
		ContentMap _loadedContent;

		template<typename T>
		T* loadContent(const Core::String8& filepath);
	};

#include "inline/ContentManager.inl"
}
