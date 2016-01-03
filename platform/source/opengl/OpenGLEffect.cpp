/**
 * @file platform/opengl/OpenGLEffect.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Effect.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLShader.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::Effect - OpenGL] ";


// Implementation

class Effect::Implementation final
{
public:

	explicit Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle)
		: _openGL(static_cast<OpenGL*>(graphicsInterfaceHandle)),
		  _programHandle(0u)
	{
		_programHandle = _openGL->createProgram();

		if(_programHandle == 0u)
		{
			defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the program." << Log::Flush();
			DE_ERROR(0x0);
		}
	}

	Implementation(const Implementation& implementation) = delete;
	Implementation(Implementation&& implementation) = delete;

	~Implementation()
	{
		_openGL->deleteProgram(_programHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void attachShader(Shader* shader) const
	{
		const Uint32 shaderHandle = shader->_implementation->handle();
		_openGL->attachShader(_programHandle, shaderHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void disuse() const
	{
		use(0u);
	}

	void link() const
	{
		_openGL->linkProgram(_programHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
		checkLinkingStatus();
		detachShaders();
	}

	void use() const
	{
		use(_programHandle);
	}

	Implementation& operator =(const Implementation& implementation) = delete;
	Implementation& operator =(Implementation&& implementation) = delete;

private:

	using CharacterBuffer = Core::Vector<Char8>;

	Platform::OpenGL* _openGL;
	Uint32 _programHandle;

	void use(const Uint32 programHandle) const
	{
		_openGL->useProgram(programHandle);
		DE_CHECK_ERROR_OPENGL(_openGL);
	}

	void checkLinkingStatus() const
	{
		const Int32 linkingStatus = getParameter(OpenGL::LINK_STATUS);

		if(linkingStatus == OpenGL::FALSE)
		{
			outputLinkerFailureLog();
			DE_ERROR(0x0);
		}
		else
		{
			outputLinkerSuccessLog();
		}
	}

	void detachShaders() const
	{
		const Uint32 shaderCount = getParameter(OpenGL::ATTACHED_SHADERS);

		if(shaderCount > 0u)
		{
			Vector<Uint32> shaderHandles(shaderCount);
			_openGL->getAttachedShaders(_programHandle, shaderCount, nullptr, shaderHandles.data());
			DE_CHECK_ERROR_OPENGL(_openGL);

			for(Vector<Uint32>::const_iterator i = shaderHandles.begin(), end = shaderHandles.end(); i != end; ++i)
			{
				_openGL->detachShader(_programHandle, *i);
				DE_CHECK_ERROR_OPENGL(_openGL);
			}
		}
	}

	Int32 getParameter(const Uint32 parameterName) const
	{
		Int32 parameter = 0;
		_openGL->getProgramiv(_programHandle, parameterName, &parameter);
		DE_CHECK_ERROR_OPENGL(_openGL);

		return parameter;
	}

	void outputLinkerFailureLog() const
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to link the program:";
		const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

		if(logLength > 1u)
			defaultLog << '\n' << getInfoLog(logLength).data();
		else
			defaultLog << " No linker log available.";

		defaultLog << Log::Flush();
	}

	void outputLinkerSuccessLog() const
	{
		const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

		if(logLength > 1u)
		{
			defaultLog << LogLevel::Warning << ::COMPONENT_TAG << "The program linked with warning(s):\n" <<
				getInfoLog(logLength).data() << Log::Flush();
		}
	}

	CharacterBuffer getInfoLog(const Uint32 logLength) const
	{
		CharacterBuffer logBuffer(logLength);
		_openGL->getProgramInfoLog(_programHandle, logBuffer.size(), nullptr, logBuffer.data());
		DE_CHECK_ERROR_OPENGL(_openGL);

		return logBuffer;
	}
};


// Graphics::Effect

// Public

void Effect::attachShader(Shader* shader) const
{
	_implementation->attachShader(shader);
}

void Effect::disuse() const
{
	_implementation->disuse();
}

void Effect::link() const
{
	_implementation->link();
}

void Effect::use() const
{
	_implementation->use();
}

// Private

Effect::Effect(GraphicsInterfaceHandle graphicsInterfaceHandle)
	: _implementation(DE_NEW(Implementation)(graphicsInterfaceHandle)) { }

Effect::~Effect()
{
	DE_DELETE(_implementation, Implementation);
}
