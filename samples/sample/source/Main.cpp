/**
 * @file samples/sample/Main.cpp
 *
 * DevEngine
 * Copyright 2015-2016 Eetu 'Devenec' Oinasmaa
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

#include <algorithm>
#include <content/ContentManager.h>
#include <core/Main.h>
#include <core/Singleton.h>
#include <core/Thread.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <core/maths/Angle.h>
#include <core/maths/Matrix4.h>
#include <core/maths/Utility.h>
#include <core/maths/Vector3.h>
#include <graphics/AccessMode.h>
#include <graphics/Colour.h>
#include <graphics/Effect.h>
#include <graphics/EffectCode.h>
#include <graphics/GraphicsAdapterManager.h>
#include <graphics/GraphicsBuffer.h>
#include <graphics/GraphicsDevice.h>
#include <graphics/GraphicsDeviceManager.h>
#include <graphics/GraphicsEnumerations.h>
#include <graphics/Image.h>
#include <graphics/IndexBuffer.h>
#include <graphics/VertexBufferState.h>
#include <graphics/VertexElement.h>
#include <graphics/Window.h>

using namespace Content;
using namespace Core;
using namespace Graphics;
using namespace Maths;

class App final : public Singleton<App>
{
public:

	App()
		: _graphicsDeviceManager(onWindowCreated),
		  _effect(nullptr),
		  _graphicsDevice(nullptr),
		  _indexBuffer(nullptr),
		  _uniformBuffer(nullptr),
		  _vertexBuffer(nullptr),
		  _vertexBufferState(nullptr),
		  _window(nullptr),
		  _isRunning(true) { }

	App(const App& app) = delete;
	App(App&& app) = delete;

	~App() = default;

	void run()
	{
		_graphicsDeviceManager.createWindow(960u, 640u);

		while(_isRunning)
			_graphicsDeviceManager.processWindowMessages();

		_updateThread.join();
	}

	App& operator =(const App& app) = delete;
	App& operator =(App&& app) = delete;

private:

	ContentManager _contentManager;
	GraphicsAdapterManager _graphicsAdapterManager;
	GraphicsDeviceManager _graphicsDeviceManager;
	Effect* _effect;
	GraphicsDevice* _graphicsDevice;
	IndexBuffer* _indexBuffer;
	GraphicsBuffer* _uniformBuffer;
	Thread _updateThread;
	GraphicsBuffer* _vertexBuffer;
	VertexBufferState* _vertexBufferState;
	Window* _window;
	Bool _isRunning;

	void initialise()
	{
		Image* image = _contentManager.load<Image>("assets/icon.png");
		_window->setIcon(image);
		_window->setTitle("DevEngine Sample - \xD0\xBA\xD0\xBE\xD1\x88\xD0\xBA\xD0\xB0");
		_window->show();

		_graphicsDevice = _graphicsDeviceManager.createDevice(_window);
		EffectCode* effectCode = _contentManager.load<EffectCode>("assets/effect.glsl");
		_effect = _graphicsDevice->createEffect(effectCode);
		_effect->setUniformBlockBinding(0u, 0u);
		initialiseVertexBuffer();
		initialiseIndexBuffer();
		initialiseVertexBufferState();
		_graphicsDevice->setEffect(_effect);
		_graphicsDevice->setVertexBufferState(_vertexBufferState);
		initialiseUniformBuffer();

	}

	void update() const
	{
		Vector3 axis(0.0f, 1.0f, 1.0f);
		axis.normalise();
		Angle rotation(0.0f);
		Matrix4 worldTransform;

		while(_window->isOpen())
		{
			_graphicsDevice->clear(Colour(0.8f, 0.0f, 1.0f));
			rotation += 0.01f;

			worldTransform =
				Matrix4::createTranslation(0.0f, 0.0f, -15.0f) * Matrix4::createRotation(axis, rotation);

			Float32* data =
				reinterpret_cast<Float32*>(_uniformBuffer->mapData(sizeof(Matrix4), sizeof(Matrix4)));

			std::copy(worldTransform.data(), worldTransform.data() + 16, data);
			_uniformBuffer->demapData();

			_graphicsDevice->draw(PrimitiveType::TriangleStrip, 4u);
			_graphicsDevice->swapBuffers();
		}
	}

	void deinitialise()
	{
		_graphicsDeviceManager.destroyDevice(_graphicsDevice);
	}

	void initialiseVertexBuffer()
	{
		Vector<Float32> VERTEX_DATA
		{
			 0.0f,	5.0f, 0.0f,
			 0.0f,

			-5.0f,	0.0f, 0.0f,
			 0.0f,

			 5.0f,	0.0f, 0.0f,
			 0.0f,

			 0.0f, -5.0f, 0.0f,
			 0.0f
		};

		Uint32 colour = 0x000003FF;
		VERTEX_DATA[3] = *reinterpret_cast<Float32*>(&colour);
		colour = 0x000FFC00;
		VERTEX_DATA[7] = *reinterpret_cast<Float32*>(&colour);
		colour = 0x3FF00000;
		VERTEX_DATA[11] = *reinterpret_cast<Float32*>(&colour);
		colour = 0x000FFFFF;
		VERTEX_DATA[15] = *reinterpret_cast<Float32*>(&colour);

		const Uint bufferSize = sizeof(Float32) * VERTEX_DATA.size();

		_vertexBuffer = _graphicsDevice->createBuffer(BufferBinding::Vertex, bufferSize, AccessMode::Write,
			BufferUsage::Static);

		Float32* data = reinterpret_cast<Float32*>(_vertexBuffer->mapData());
		std::copy(VERTEX_DATA.begin(), VERTEX_DATA.end(), data);
		_vertexBuffer->demapData();
	}

	void initialiseIndexBuffer()
	{
		const Vector<Uint8> INDEX_DATA
		{
			 0u, 1u, 2u,
			 3u, 2u, 1u,
		};

		const Uint bufferSize = sizeof(Uint8) * INDEX_DATA.size();

		_indexBuffer = _graphicsDevice->createIndexBuffer(bufferSize, IndexType::Uint8, AccessMode::Write,
			BufferUsage::Static);

		Uint8* data = _vertexBuffer->mapData();
		std::copy(INDEX_DATA.begin(), INDEX_DATA.end(), data);
		_vertexBuffer->demapData();
	}

	void initialiseVertexBufferState()
	{
		VertexElementList vertexElements
		{
			VertexElement(0u, VertexElementType::Float32Vector3),
			VertexElement(1u, VertexElementType::Uint32_R10G10B10A2)
		};

		_vertexBufferState = _graphicsDevice->createVertexBufferState();
		_vertexBufferState->setVertexBuffer(_vertexBuffer, vertexElements, 4u * sizeof(Float32));
		_vertexBufferState->setIndexBuffer(_indexBuffer);
	}

	void initialiseUniformBuffer()
	{
		const Float32 near = 0.1f;
		const Float32 far = 100.0f;
		const Float32 top = near * tangent(0.5f * 1.047f);
		const Float32 right = 800.0f / 600.0f * top;

		const Matrix4 projectionTransform
		(
			near / right, 0.0f,		   0.0f,							  0.0f,
			0.0f,		  near / top,  0.0f,							  0.0f,
			0.0f,		  0.0f,		  -(far + near) / (far - near),		 -1.0f,
			0.0f,		  0.0f,		  -2.0f * near * far / (far - near),  0.0f
		);

		_uniformBuffer =
			_graphicsDevice->createBuffer(BufferBinding::Uniform, 32u * sizeof(Float32), AccessMode::Write,
				BufferUsage::Stream);

		Float32* data = reinterpret_cast<Float32*>(_uniformBuffer->mapData(sizeof(Matrix4)));
		std::copy(projectionTransform.data(), projectionTransform.data() + 16, data);
		_uniformBuffer->demapData();
		_graphicsDevice->bindBufferIndexed(_uniformBuffer, 0u);
	}

	static void onWindowCreated(Window* window)
	{
		App& app = App::instance();
		app._window = window;
		app._updateThread.run(updateThreadMain, &app);
	}

	static Int32 updateThreadMain(Void* parameter)
	{
		App* app = static_cast<App*>(parameter);
		app->initialise();
		app->update();
		app->deinitialise();
		app->_isRunning = false;

		return 0;
	}
};

void devEngineMain(const StartupParameters& startupParameters)
{
	static_cast<Void>(startupParameters);

	App app;
	app.run();
}
