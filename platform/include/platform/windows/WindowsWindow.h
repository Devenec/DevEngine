/**
 * @file platform/windows/WindowsWindow.h
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
#include <graphics/Window.h>
#include <platform/windows/Windows.h>
#include <platform/windows/WindowsIcon.h>

namespace Graphics
{
	class Window::Implementation final
	{
	public:

		explicit Implementation(HWND windowHandle);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation() = default;

		inline void close();

		inline HWND handle() const;

		inline void hide() const;

		inline Bool isFullscreen() const;

		Core::Rectangle rectangle() const;

		inline void setPointerVisibility(const Bool isPointerVisible);

		void setFullscreen(const Bool isFullscreen);

		void setIcon(const Image* image);

		void setRectangle(const Core::Rectangle& rectangle, const Bool isFullscreenRectangle);

		void setTitle(const Core::String8& title) const;

		inline Bool shouldClose() const;

		Bool shouldHidePointer(const Bool isPointerInClientArea) const;

		inline void show() const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		Core::Rectangle _rectangle;
		Platform::Icon _icon;
		HWND _windowHandle;
		Bool _isPointerVisible;
		Bool _isFullscreen;
		Bool _isOpen;

		Core::Rectangle getRectangle() const;
		void setFullscreenStyle(const Bool isFullscreen) const;
		Core::Rectangle getFullscreenRectangle() const;
		RECT getMonitorRectangle() const;
	};

#include "inline/WindowsWindow.inl"
}
