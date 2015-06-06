/**
 * @file core/Rectangle.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Types.h>

namespace Core
{
	class Rectangle
	{
	public:

		Int32 x;

		Int32 y;

		Uint32 width;

		Uint32 height;

		Rectangle() = default;

		inline Rectangle(const Int32 x, const Int32 y, const Uint32 width, const Uint32 height);

		Rectangle(const Rectangle& rectangle) = default;

		Rectangle(Rectangle&& rectangle) = default;

		~Rectangle() = default;

		inline Int32 bottom() const;

		inline Int32 left() const;

		inline Int32 right() const;

		inline Int32 top() const;

		Rectangle& operator =(const Rectangle& rectangle) = default;

		Rectangle& operator =(Rectangle&& rectangle) = default;
	};

#include "inline/Rectangle.inl"
}
