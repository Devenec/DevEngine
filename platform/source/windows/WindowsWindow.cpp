/**
 * @file platform/windows/WindowsWindow.cpp
 *
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 */

#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/Window.h>
#include <platform/windows/Windows.h>

using namespace Core;
using namespace Graphics;

// Implementation

class Window::Impl
{
public:

	Impl(HWND handle)
		: _handle(handle) { }

	~Impl() { }

	HWND handle() const
	{
		return _handle;
	}

	Bool processMessages() const
	{
		MSG message;

		while(PeekMessageW(&message, nullptr, 0u, 0u, PM_REMOVE) != 0)
		{
			if(message.message == WM_QUIT)
				return false;

			DispatchMessageW(&message);
		}

		return true;
	}

	void setTitle(const String8& title) const
	{
		const String16 title16 = toString16(title);
		const Int32 result = SetWindowTextW(_handle, title16.c_str());
		DE_ASSERT(result != 0);
	}

	void show() const
	{
		ShowWindow(_handle, SW_SHOWNORMAL);
	}

private:

	HWND _handle;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	Impl& operator =(const Impl& impl) = delete;
};


// Public

WindowHandle Window::handle() const
{
	return _impl->handle();
}

Bool Window::processMessages() const
{
	return _impl->processMessages();
}

void Window::setTitle(const String8& title) const
{
	_impl->setTitle(title);
}

void Window::show() const
{
	_impl->show();
}

// Private

Window::Window(WindowHandle windowHandle)
	: _impl(DE_NEW Impl(static_cast<HWND>(windowHandle))) { }

Window::~Window()
{
	DE_DELETE _impl;
}
