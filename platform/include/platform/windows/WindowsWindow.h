/**
 * @file platform/windows/WindowsWindow.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

		void setRectangle(const Core::Rectangle& rectangle, const Bool isFullscreenRectangle = false);

		void setTitle(const Core::String8& title) const;

		inline Bool shouldClose() const;

		Bool shouldHideCursor(const Bool isCursorInClientArea) const;

		inline void show() const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

		static Bool processMessages();

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
