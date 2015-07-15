/**
 * @file platform/windows/WindowsWindow.h
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

#pragma once

#include <core/Rectangle.h>
#include <graphics/Window.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsIcon.h>

namespace Graphics
{
	class Image;

	class Window::Impl final
	{
	public:

		explicit Impl(HWND windowHandle);

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl() = default;

		inline void close();

		inline HWND handle() const;

		inline void hide() const;

		inline Bool isFullscreen() const;

		inline Core::Rectangle rectangle() const;

		inline void setCursorVisibility(const Bool isCursorVisible);

		void setFullscreen(const Bool isFullscreen);

		void setIcon(const Image* image);

		void setRectangle(const Core::Rectangle& rectangle, const Bool isFullscreenRectangle);

		void setTitle(const Core::String8& title) const;

		inline Bool shouldClose() const;

		Bool shouldHideCursor(const Bool isCursorInClientArea) const;

		inline void show() const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

	private:

		static const Char8* COMPONENT_TAG;

		Core::Rectangle _rectangle;
		Platform::Icon _icon;
		HWND _windowHandle;
		Bool _isCursorVisible;
		Bool _isFullscreen;
		Bool _isOpen;

		Core::Rectangle getRectangle() const;
		void setFullscreenStyle(const Bool isFullscreen) const;
		Core::Rectangle getFullscreenRectangle() const;
		RECT getMonitorRectangle() const;
	};

#include "inline/WindowsWindow.inl"
}
