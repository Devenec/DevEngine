/**
 * @file content/ContentManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

namespace Content
{
	class ContentManager
	{
	public:

		ContentManager();

		ContentManager(const ContentManager& contentManager) = delete;
		ContentManager(ContentManager&& contentManager) = delete;

		~ContentManager();

		ContentManager& operator =(const ContentManager& contentManager) = delete;
		ContentManager& operator =(ContentManager&& contentManager) = delete;
	};
}
