/**
 * @file content/ContentLoader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/FileStream.h>

namespace Content
{
	// TODO: figure out how to create each ContentLoader<T> once, reuse them and destroy them when no longer needed
	template<typename T>
	class ContentLoader
	{
	public:

		ContentLoader(const ContentLoader& contentLoader) = delete;

		ContentLoader(ContentLoader&& contentLoader) = default;
		
		virtual ~ContentLoader() = default;

		virtual T* load(const Core::FileStream& fileStream) = 0;

		ContentLoader& operator =(const ContentLoader& contentLoader) = delete;

		ContentLoader& operator =(ContentLoader&& contentLoader) = default;

		static inline ContentLoader loader(); // TODO: use ContentLoader<T>?

	protected:

		ContentLoader() = default;
	};
}
