/**
 * @file content/ContentBase.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

namespace Content
{
	class ContentBase
	{
	public:

		ContentBase(const ContentBase& contentBase) = delete;
		ContentBase(ContentBase&& contentBase) = delete;

		ContentBase& operator =(const ContentBase& contentBase) = delete;
		ContentBase& operator =(ContentBase&& contentBase) = delete;

	protected:

		ContentBase() = default;

		virtual ~ContentBase() = default;

	private:

		friend class ContentManager;
	};
}
