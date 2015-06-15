/**
 * @file content/ContentLoader.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

namespace Core
{
	class FileStream;
}

namespace Content
{
	template<typename T>
	class ContentLoader
	{
	public:

		ContentLoader(const ContentLoader& contentLoader) = delete;
		ContentLoader(ContentLoader&& contentLoader) = delete;

		virtual T* load(Core::FileStream& fileStream) = 0;

		ContentLoader& operator =(const ContentLoader& contentLoader) = delete;
		ContentLoader& operator =(ContentLoader&& contentLoader) = delete;

		static ContentLoader<T>* createLoader();

	protected:

		ContentLoader() = default;

		virtual ~ContentLoader() = default;

	private:

		friend class ContentManager;
	};
}
