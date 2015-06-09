/**
 * @file content/inline/ContentManager.inl
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

// Public

ContentManager::ContentManager(const Core::String8& contentDirectory)
	: _contentRootDirectory(contentDirectory) { }

const Core::String8& ContentManager::contentRootDirectory() const
{
	return _contentRootDirectory;
}

void ContentManager::setContentRootDirectory(const Core::String8& value)
{
	_contentRootDirectory = value;
}

template<typename T>
T* ContentManager::load(const Core::String8& filepath)
{
	Core::String8 contentFilepath = _contentRootDirectory + filepath;
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
	ContentLoader<T>* contentLoader = ContentLoader<T>::loader();
	Core::FileStream fileStream(filepath);
	T* content = contentLoader->load(fileStream);
	_loadedContent[filepath] = content;
	fileStream.close();
	DE_DELETE contentLoader; // TODO: remove when a better solution is found

	return content;
}
