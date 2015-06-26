/**
 * @file graphics/WindowManager.h
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#pragma once

#include <core/List.h>
#include <core/Singleton.h>
#include <core/Types.h>

namespace Graphics
{
	class Window;

	class WindowManager final : public Core::Singleton<WindowManager>
	{
	public:

		WindowManager();

		WindowManager(const WindowManager& windowManager) = delete;
		WindowManager(WindowManager&& windowManager) = delete;

		~WindowManager();

		Window* createWindow();

		void destroyWindow(Window* window);

		void initialise();

		void processMessages() const;

		WindowManager& operator =(const WindowManager& windowManager) = delete;
		WindowManager& operator =(WindowManager&& windowManager) = delete;

	private:

		class Impl;

		using WindowList = Core::List<Window*>;

		WindowList _windows; // TODO: move to implementation
		Impl* _impl;
	};
}
