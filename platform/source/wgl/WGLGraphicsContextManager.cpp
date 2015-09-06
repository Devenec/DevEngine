/**
 * @file platform/wgl/WGLGraphicsContextManager.cpp
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

#include <algorithm>
#include <core/List.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <graphics/GraphicsConfig.h>
#include <graphics/GraphicsContext.h>
#include <graphics/GraphicsContextManager.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>
#include <platform/GraphicsExtensionLoader.h>
#include <platform/opengl/OpenGL.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsConfigChooser.h>
#include <platform/wgl/WGLGraphicsContextBase.h>
#include <platform/wgl/WGLTemporaryGraphicsContext.h>
#include <platform/windows/WindowsGraphics.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static void initialiseGraphicsInterface(GraphicsContext* graphicsContext);
static void loadContextExtensions(Window* window);


// Implementation

class GraphicsContextManager::Impl final
{
public:

	Impl()
	{
		const WindowManager& windowManager = WindowManager::instance();
		Window* temporaryWindow = windowManager.createWindow();
		loadContextExtensions(temporaryWindow);
		windowManager.destroyWindow(temporaryWindow);
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		for(GraphicsContextList::const_iterator i = _graphicsContexts.begin(), end = _graphicsContexts.end(); i != end;
			++i)
		{
			DE_DELETE(*i, GraphicsContext);
		}
	}

	GraphicsContext* createGraphicsContext(Window* window)
	{
		if(_graphicsContexts.size() == 0u)
			initialiseGraphicsConfig(window);

		GraphicsContext* graphicsContext = DE_NEW(GraphicsContext)(window, _graphicsConfig);

		if(_graphicsContexts.size() == 0u)
		{
			initialiseGraphicsInterface(graphicsContext);
			logGraphicsContextConfiguration(_graphicsConfig);
		}

		_graphicsContexts.push_back(graphicsContext);
		return graphicsContext;
	}

	void destroyGraphicsContext(GraphicsContext* graphicsContext)
	{
		DE_ASSERT(graphicsContext != nullptr);

		GraphicsContextList::const_iterator iterator = std::find(_graphicsContexts.begin(), _graphicsContexts.end(),
			graphicsContext);

		DE_ASSERT(iterator != _graphicsContexts.end());
		_graphicsContexts.erase(iterator);
		DE_DELETE(graphicsContext, GraphicsContext);
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	using GraphicsContextList = List<GraphicsContext*>;

	GraphicsContextList _graphicsContexts;
	GraphicsConfig _graphicsConfig;

	void initialiseGraphicsConfig(Window* window)
	{
		HDC deviceContextHandle = GraphicsContextBase::getWindowDeviceContext(static_cast<HWND>(window->handle()));
		GraphicsConfigChooser graphicsConfigChooser(deviceContextHandle);
		_graphicsConfig = graphicsConfigChooser.chooseConfig();
	}
};


// Public

GraphicsContextManager::GraphicsContextManager()
	: _impl(DE_NEW(Impl)()) { }

GraphicsContextManager::~GraphicsContextManager()
{
	DE_DELETE(_impl, Impl);
}

GraphicsContext* GraphicsContextManager::createGraphicsContext(Window* window) const
{
	return _impl->createGraphicsContext(window);
}

void GraphicsContextManager::destroyGraphicsContext(GraphicsContext* context) const
{
	_impl->destroyGraphicsContext(context);
}


// External

static void initialiseGraphicsInterface(GraphicsContext* graphicsContext)
{
	graphicsContext->makeCurrent();
	GraphicsExtensionLoader::loadInterfaceExtensions();
	OpenGL::initialise();
	graphicsContext->makeNonCurrent();
}

static void loadContextExtensions(Window* window)
{
	TemporaryGraphicsContext temporaryGraphicsContext(static_cast<HWND>(window->handle()));
	GraphicsExtensionLoader::loadContextExtensions(temporaryGraphicsContext);
}
