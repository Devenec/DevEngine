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
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLEffect.h>
#include <platform/opengl/OpenGLShader.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Graphics::Effect - OpenGL] ";


// Implementation

// Public

Effect::Implementation::Implementation()
	: _programHandle(0u)
{
	_programHandle = OpenGL::createProgram();

	if(_programHandle == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to create the program." <<
			Log::Flush();

		DE_ERROR(0x0);
	}
}

Effect::Implementation::~Implementation()
{
	OpenGL::deleteProgram(_programHandle);
	DE_CHECK_ERROR_OPENGL();
}

void Effect::Implementation::attachShader(Shader* shader) const
{
	const Uint32 shaderHandle = shader->_implementation->handle();
	OpenGL::attachShader(_programHandle, shaderHandle);
	DE_CHECK_ERROR_OPENGL();
}

void Effect::Implementation::link() const
{
	OpenGL::linkProgram(_programHandle);
	DE_CHECK_ERROR_OPENGL();
	checkLinkingStatus();
	detachShaders();
}

void Effect::Implementation::setUniformBlockBinding(const Uint32 blockIndex, const Uint32 bindingIndex) const
{
	OpenGL::uniformBlockBinding(_programHandle, blockIndex, bindingIndex);
	DE_CHECK_ERROR_OPENGL();
}

// Private

void Effect::Implementation::bind(const Uint32 programHandle) const
{
	OpenGL::useProgram(programHandle);
	DE_CHECK_ERROR_OPENGL();
}

void Effect::Implementation::checkLinkingStatus() const
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

void Effect::Implementation::detachShaders() const
{
	using ShaderHandleList = Vector<Uint32>;
	const Int32 shaderCount = getParameter(OpenGL::ATTACHED_SHADERS);

	if(shaderCount > 0)
	{
		ShaderHandleList shaderHandles(shaderCount);
		OpenGL::getAttachedShaders(_programHandle, shaderCount, nullptr, shaderHandles.data());
		DE_CHECK_ERROR_OPENGL();

		for(ShaderHandleList::const_iterator i = shaderHandles.begin(), end = shaderHandles.end(); i != end;
			++i)
		{
			OpenGL::detachShader(_programHandle, *i);
			DE_CHECK_ERROR_OPENGL();
		}
	}
}

Int32 Effect::Implementation::getParameter(const Uint32 parameterName) const
{
	Int32 parameter = 0;
	OpenGL::getProgramiv(_programHandle, parameterName, &parameter);
	DE_CHECK_ERROR_OPENGL();

	return parameter;
}

void Effect::Implementation::outputLinkerFailureLog() const
{
	defaultLog << LogLevel::Error << ::COMPONENT_TAG << "Failed to link the program:";
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
		defaultLog << '\n' << getInfoLog(logLength).data();
	else
		defaultLog << " No linker log available.";

	defaultLog << Log::Flush();
}

void Effect::Implementation::outputLinkerSuccessLog() const
{
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
	{
		defaultLog << LogLevel::Warning << ::COMPONENT_TAG << "The program linked with warning(s):\n" <<
			getInfoLog(logLength).data() << Log::Flush();
	}
}

Effect::Implementation::CharacterBuffer Effect::Implementation::getInfoLog(const Uint32 logLength) const
{
	CharacterBuffer logBuffer(logLength);

	OpenGL::getProgramInfoLog(_programHandle, static_cast<Int32>(logBuffer.size()), nullptr,
		logBuffer.data());

	DE_CHECK_ERROR_OPENGL();
	return logBuffer;
}


// Graphics::Effect

// Public

void Effect::setUniformBlockBinding(const Uint32 blockIndex, const Uint32 bindingIndex) const
{
	_implementation->setUniformBlockBinding(blockIndex, bindingIndex);
}

// Private

Effect::Effect(GraphicsInterfaceHandle graphicsInterfaceHandle)
	: _implementation(nullptr)
{
	static_cast<Void>(graphicsInterfaceHandle);
	_implementation = DE_NEW(Implementation)();
}

Effect::~Effect()
{
	DE_DELETE(_implementation, Implementation);
}
