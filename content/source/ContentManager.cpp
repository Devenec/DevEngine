/**
 * @file content/ContentManager.cpp
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

#include <content/ContentBase.h>
#include <content/ContentManager.h>
#include <core/FileSystem.h>

using namespace Content;
using namespace Core;

// Public

ContentManager::ContentManager()
	: _contentRootDirectory(FileSystem::getDefaultContentRootDirectory()) { }

ContentManager::~ContentManager()
{
	for(ContentMap::const_iterator i = _loadedContent.begin(), end = _loadedContent.end(); i != end; ++i)
		DE_DELETE(i->second, ContentBase);
}
