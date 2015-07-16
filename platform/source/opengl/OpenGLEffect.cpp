/**
 * @file platform/opengl/OpenGLEffect.cpp
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

#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Effect.h>
#include <graphics/Shader.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLInterface.h>
#include <platform/opengl/OpenGLShader.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

class Effect::Impl
{
public:

	Impl()
		: _programHandle(0u)
	{
		createProgram();
	}

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl()
	{
		OpenGL::deleteProgram(_programHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	void apply() const
	{
		applyProgram(_programHandle);
	}

	void deapply() const
	{
		applyProgram(0u);
	}

	void attachShader(Shader* shader) const
	{
		const Uint32 shaderHandle = shader->_impl->handle();
		OpenGL::attachShader(_programHandle, shaderHandle);
		DE_CHECK_ERROR_OPENGL();
	}

	void link() const
	{
		OpenGL::linkProgram(_programHandle);
		DE_CHECK_ERROR_OPENGL();
		checkLinkingStatus();
		detachShaders();
	}

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

private:

	static const Char8* COMPONENT_TAG;

	Uint32 _programHandle;

	void createProgram()
	{
		_programHandle = OpenGL::createProgram();

		if(_programHandle == 0u)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the program." << Log::Flush();
			DE_ERROR(0x0);
		}
	}

	void checkLinkingStatus() const
	{
		const Int32 linkingStatus = getParameter(GL_LINK_STATUS);

		if(linkingStatus == GL_FALSE)
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
		const Uint32 attachedShaderCount = getParameter(GL_ATTACHED_SHADERS);

		if(attachedShaderCount > 0u)
		{
			Vector<Uint32> attachedShaderHandles(attachedShaderCount);
			OpenGL::getAttachedShaders(_programHandle, attachedShaderCount, nullptr, attachedShaderHandles.data());
			DE_CHECK_ERROR_OPENGL();

			for(Vector<Uint32>::const_iterator i = attachedShaderHandles.begin(), end = attachedShaderHandles.end();
				i != end; ++i)
			{
				OpenGL::detachShader(_programHandle, *i);
				DE_CHECK_ERROR_OPENGL();
			}
		}
	}

	Int32 getParameter(const Uint32 parameterName) const
	{
		Int32 parameter = 0;
		OpenGL::getProgramiv(_programHandle, parameterName, &parameter);
		DE_CHECK_ERROR_OPENGL();

		return parameter;
	}

	void outputLinkerFailureLog() const
	{
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to link the program:\n\t";
		const Uint32 logLength = getParameter(GL_INFO_LOG_LENGTH);

		if(logLength > 1u)
			defaultLog << getInfoLog(logLength).data();
		else
			defaultLog << "No linker log available.";

		defaultLog << Log::Flush();
	}

	void outputLinkerSuccessLog() const
	{
		const Uint32 logLength = getParameter(GL_INFO_LOG_LENGTH);

		if(logLength > 1u)
		{
			defaultLog << LogLevel::Warning << COMPONENT_TAG << " The program linked with warning(s):\n\t" <<
				getInfoLog(logLength).data() << Log::Flush();
		}
	}

	Vector<Char8> getInfoLog(const Uint32 logLength) const
	{
		Vector<Char8> logBuffer(logLength);
		OpenGL::getProgramInfoLog(_programHandle, logBuffer.size(), nullptr, logBuffer.data());
		DE_CHECK_ERROR_OPENGL();

		return logBuffer;
	}

	static void applyProgram(const Uint32 programHandle)
	{
		OpenGL::useProgram(programHandle);
		DE_CHECK_ERROR_OPENGL();
	}
};

const Char8* Effect::Impl::COMPONENT_TAG = "[Platform::Effect - OpenGL]";


// Private

Effect::Effect()
	: _impl(DE_NEW(Impl)()) { }

Effect::~Effect()
{
	DE_DELETE(_impl, Impl);
}

void Effect::apply() const
{
	_impl->apply();
}

void Effect::attachShader(Shader* shader) const
{
	_impl->attachShader(shader);
}

void Effect::deapply() const
{
	_impl->deapply();
}

void Effect::link() const
{
	_impl->link();
}
