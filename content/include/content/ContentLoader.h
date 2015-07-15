/**
 * @file content/ContentLoader.h
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