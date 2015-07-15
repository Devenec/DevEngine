/**
 * @file content/inline/ContentManager.inl
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

// Public

const Core::String8& ContentManager::contentRootDirectory() const
{
	return _contentRootDirectory;
}

void ContentManager::setContentRootDirectory(const Core::String8& directoryPath)
{
	_contentRootDirectory = directoryPath;
}

template<typename T>
T* ContentManager::load(const Core::String8& filepath)
{
	const Core::String8 contentFilepath = _contentRootDirectory + filepath;
	ContentMap::iterator iterator = _loadedContent.find(contentFilepath);

	if(iterator == _loadedContent.end())
		return loadContent<T>(contentFilepath);
	else
		return static_cast<T*>(iterator->second);
}

// Private

template<typename T>
T* ContentManager::loadContent(const Core::String8& filepath)
{
	ContentLoader<T>* contentLoader = ContentLoader<T>::createLoader();
	Core::FileStream fileStream(filepath);
	T* content = contentLoader->load(fileStream);
	_loadedContent[filepath] = content;
	fileStream.close();
	DE_DELETE(contentLoader, ContentLoader<T>);

	return content;
}