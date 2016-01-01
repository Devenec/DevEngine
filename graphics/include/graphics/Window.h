/**
 * @file graphics/Window.h
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

#pragma once

#include <core/String.h>
#include <core/Types.h>

namespace Core
{
	class Rectangle;
}

namespace Graphics
{
	class Image;

	using WindowHandle = Void*;

	class Window final
	{
	public:

		Window(const Window& window) = delete;
		Window(Window&& window) = delete;

		WindowHandle handle() const;

		void hide() const;

		Core::Rectangle rectangle() const;

		void setPointerVisibility(const Bool isPointerVisible) const;

		void setFullscreen(const Bool isFullscreen) const;

		void setIcon(const Image* image) const;

		void setRectangle(const Core::Rectangle& rectangle) const;

		void setTitle(const Core::String8& title) const;

		Bool shouldClose() const;

		void show() const;

		Window& operator =(const Window& window) = delete;
		Window& operator =(Window&& window) = delete;

	private:

		friend class GraphicsDeviceManager;

		class Implementation;

		Implementation* _implementation;

		explicit Window(WindowHandle windowHandle);
		~Window();
	};
}
