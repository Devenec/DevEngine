/**
 * @file graphics/Window.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

		void setCursorVisibility(const Bool value) const;

		void setFullscreen(const Bool value) const;

		void setIcon(const Image* value) const;

		void setRectangle(const Core::Rectangle& value) const;

		void setTitle(const Core::String8& value) const;

		Bool shouldClose() const;

		void show() const;

		Window& operator =(const Window& window) = delete;
		Window& operator =(Window&& window) = delete;

	private:

		friend class WindowManager;

		class Impl;

		Impl* _impl;

		explicit Window(WindowHandle handle);
		~Window();
	};
}
