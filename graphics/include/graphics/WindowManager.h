/**
 * @file graphics/WindowManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/Singleton.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Window.h>

namespace Graphics
{
	class WindowManager final : public Core::Singleton<WindowManager>
	{
	public:

		WindowManager();

		~WindowManager();

		Window* createWindow();

	private:

		class Impl;

		Impl* _impl;
		Window* _window;

		WindowManager(const WindowManager& windowManager) = delete;
		WindowManager(WindowManager&& windowManager) = delete;

		void destroyWindow();

		WindowManager& operator =(const WindowManager& windowManager) = delete;
		WindowManager& operator =(WindowManager&& windowManager) = delete;
	};
}
