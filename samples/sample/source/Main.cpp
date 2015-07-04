/**
 * @file samples/sample/Main.cpp
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

#include <content/ContentManager.h>
#include <core/Application.h>
#include <graphics/Colour.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/GraphicsContext.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/Image.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

#include <graphics/Viewport.h>

using namespace Content;
using namespace Core;
using namespace Graphics;

void devEngineMain(const StartupParameters& startupParameters)
{
	static_cast<Void>(startupParameters);
	ContentManager contentManager;
	GraphicsAdapterManager graphicsAdapterManager;
	WindowManager windowManager;

	Window* window = windowManager.createWindow();
	Image* image = contentManager.load<Image>("assets/icon.png");
	window->setIcon(image);
	window->setTitle("DevEngine - \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0");
	window->show();

	GraphicsContext graphicsContext(window);
	graphicsContext.makeCurrent();
	GraphicsDevice graphicsDevice;
	graphicsDevice.setViewport(Viewport(Rectangle(400, 300, 400u, 300u)));

	while(!window->shouldClose())
	{
		windowManager.processMessages();
		graphicsDevice.clear(Colour(0.8f, 0.0f, 1.0f));
		graphicsContext.swapBuffers();
	}
}
