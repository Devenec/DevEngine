/**
 * @file content/ContentManager.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <content/ContentBase.h>
#include <content/ContentManager.h>
#include <core/Memory.h>

using namespace Content;

// Public

ContentManager::~ContentManager()
{
	for(ContentMap::const_iterator i = _loadedContent.begin(), end = _loadedContent.end(); i != end; ++i)
		DE_DELETE(i->second, ContentBase);
}
