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
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Colour.h>
#include <graphics/Effect.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsContext.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/Image.h>
#include <graphics/Shader.h>
#include <graphics/VertexBufferState.h>
#include <graphics/VertexElement.h>
#include <graphics/Viewport.h>
#include <graphics/Window.h>
#include <graphics/WindowManager.h>

using namespace Content;
using namespace Core;
using namespace Graphics;

static const String8 VERTEX_SHADER_SOURCE
(
	"#version 450\n"
	"\n"
	"layout(location = 0) in vec4 inPosition;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	gl_Position = inPosition;\n"
	"}\n"
);

static const String8 FRAGMENT_SHADER_SOURCE
(
	"#version 450\n"
	"\n"
	"out vec4 outColour;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	outColour = vec4(0.0, 1.0, 0.0, 1.0);\n"
	"}\n"
);

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

	Shader* vertexShader = graphicsDevice.createShader(ShaderType::Vertex, VERTEX_SHADER_SOURCE);
	Shader* fragmentShader = graphicsDevice.createShader(ShaderType::Fragment, FRAGMENT_SHADER_SOURCE);
	Effect* effect = graphicsDevice.createEffect();
	effect->attachShader(vertexShader);
	effect->attachShader(fragmentShader);
	effect->link();
	graphicsDevice.destroyResource(fragmentShader);
	graphicsDevice.destroyResource(vertexShader);

	const Vector<Float32> VERTEX_DATA
	{
		 0.0f,	0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f,
		 0.8f, -0.8f, 0.0f
	};

	GraphicsBuffer* vertexBuffer = graphicsDevice.createBuffer(sizeof(Float32) * VERTEX_DATA.size());
	vertexBuffer->setData(reinterpret_cast<const Byte*>(VERTEX_DATA.data()), sizeof(Float32) * VERTEX_DATA.size());
	VertexBufferState* vertexBufferState = graphicsDevice.createVertexBufferState();

	vertexBufferState->setVertexLayout(
	{
		{ 0u, 0u, 3u, VertexElementType::Float32, false }
	},
	true);

	vertexBufferState->setVertexBuffer(vertexBuffer, 0u, 3u * sizeof(Float32));
	graphicsDevice.setEffect(effect);
	graphicsDevice.setVertexBufferState(vertexBufferState);

	while(!window->shouldClose())
	{
		windowManager.processMessages();
		graphicsDevice.clear(Colour(0.8f, 0.0f, 1.0f));
		graphicsDevice.draw(PrimitiveType::Triangle, 3u);
		graphicsContext.swapBuffers();
	}
}
