/**
 * @file platform/windows/WindowsWindow.h
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

#include <core/Rectangle.h>
#include <graphics/Window.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsIcon.h>

namespace Graphics
{
	class Window::Implementation final
	{
	public:

		explicit Implementation(WindowHandle windowHandle);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation() = default;

		Core::Rectangle clientRectangle() const;

		inline void close();

		inline WindowHandle handle() const;

		inline void hide() const;

		inline Bool inFullscreen() const;

		inline Bool isOpen() const;

		void setClientRectangle(const Core::Rectangle& rectangle) const;

		void setFullscreen(const Bool inFullscreen);

		void setIcon(const Image* image);

		inline void setPointerVisibility(const Bool isPointerVisible);

		void setTitle(const Core::String8& title) const;

		Bool shouldHidePointer(const Bool isPointerInClientArea) const;

		inline void show() const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		Core::Rectangle _windowedClientRectangle;
		Platform::Icon _icon;
		HWND _windowHandle;
		Bool _inFullscreen;
		Bool _isOpen;
		Bool _isPointerVisible;

		Core::Rectangle calculateWindowRectangle(const Core::Rectangle& clientRectangle) const;
		void setStyle(const Bool inFullscreen) const;
		void setFullscreenClientRectangle(const Bool inFullscreen);
		Core::Rectangle getFullscreenRectangle() const;
	};

#include "inline/WindowsWindow.inl"
}
