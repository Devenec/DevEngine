/**
 * @file graphics/Viewport.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#pragma once

#include <core/Rectangle.h>
#include <core/Types.h>

namespace Graphics
{
	class Viewport final
	{
	public:

		Viewport() = default;

		explicit Viewport(const Core::Rectangle& bounds);

		Viewport(const Viewport& viewport) = default;

		Viewport(Viewport&& viewport) = default;

		~Viewport() = default;

		inline Float32 aspectRatio() const;

		inline const Core::Rectangle& bounds() const;

		inline void setBounds(const Core::Rectangle& bounds);

		Viewport& operator =(const Viewport& viewport) = default;

		Viewport& operator =(Viewport&& viewport) = default;

	private:

		Core::Rectangle _bounds;
	};

#include "inline/Viewport.inl"
}
