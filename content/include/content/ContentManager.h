/**
 * @file content/ContentManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <content/ContentLoader.h>
#include <core/FileStream.h>
#include <core/String.h>
#include <core/Map.h>
#include <core/Memory.h>

namespace Content
{
	class ContentBase;

	class ContentManager final
	{
	public:

		inline ContentManager(const Core::String8& contentRootDirectory = "");

		ContentManager(const ContentManager& contentManager) = delete;
		ContentManager(ContentManager&& contentManager) = delete;

		~ContentManager();

		inline const Core::String8& contentRootDirectory() const;

		inline void setContentRootDirectory(const Core::String8& value);

		template<typename T>
		inline T* load(const Core::String8& filepath);

		ContentManager& operator =(const ContentManager& contentManager) = delete;
		ContentManager& operator =(ContentManager&& contentManager) = delete;

	private:

		using ContentMap = Core::Map<Core::String8, ContentBase*>;

		Core::String8 _contentRootDirectory;
		ContentMap _loadedContent;

		template<typename T>
		inline T* loadContent(const Core::String8& filepath);
	};

#include "inline/ContentManager.inl"
}
