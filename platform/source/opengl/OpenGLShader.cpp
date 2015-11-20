/**
 * @file platform/opengl/OpenGLShader.cpp
 *
 * DevEngine
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
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

#include <core/Array.h>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Memory.h>
#include <core/debug/Assert.h>
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLShader.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::Shader - OpenGL]";

static const Array<const Char8*, 6u> SHADER_TYPE_NAMES
{{
	"compute",
	"fragment",
	"geometry",
	"tessellation control",
	"tessellation evaluation"
	"vertex"
}};

static Uint32 getShaderTypeId(const ShaderType& shaderType);


// Implementation

// Public

Shader::Impl::Impl(OpenGL* openGL, const ShaderType& type, const Core::String8& source)
	: _openGL(openGL),
	  _shaderHandle(0u)
{
	createShader(type);
	compileShader(source);
	checkCompilationStatus();
}	

Shader::Impl::~Impl()
{
	_openGL->deleteShader(_shaderHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

// Private

void Shader::Impl::createShader(const ShaderType& type)
{
	_shaderHandle = _openGL->createShader(::getShaderTypeId(type));
	DE_CHECK_ERROR_OPENGL(_openGL);

	if(_shaderHandle == 0u)
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to create the " <<
			::SHADER_TYPE_NAMES[static_cast<Int32>(type)] << " shader." << Log::Flush();

		DE_ERROR(0x0);
	}
}

void Shader::Impl::compileShader(const String8& source) const
{
	const Char8* sourceCharacters = source.c_str();
	_openGL->shaderSource(_shaderHandle, 1, &sourceCharacters, nullptr);
	DE_CHECK_ERROR_OPENGL(_openGL);
	_openGL->compileShader(_shaderHandle);
	DE_CHECK_ERROR_OPENGL(_openGL);
}

void Shader::Impl::checkCompilationStatus() const
{
	const Int32 compilationStatus = getParameter(OpenGL::COMPILE_STATUS);

	if(compilationStatus == OpenGL::FALSE)
	{
		outputCompilerFailureLog();
		DE_ERROR(0x0);
	}
	else
	{
		outputCompilerSuccessLog();
	}
}

Int32 Shader::Impl::getParameter(const Uint32 parameterName) const
{
	Int32 parameter;
	_openGL->getShaderiv(_shaderHandle, parameterName, &parameter);
	DE_CHECK_ERROR_OPENGL(_openGL);

	return parameter;
}

void Shader::Impl::outputCompilerFailureLog() const
{
	defaultLog << LogLevel::Error << ::COMPONENT_TAG << " Failed to compile the shader:";
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
		defaultLog << '\n' << getInfoLog(logLength).data();
	else
		defaultLog << " No compiler log available.";

	defaultLog << Log::Flush();
}

void Shader::Impl::outputCompilerSuccessLog() const
{
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
	{
		defaultLog << LogLevel::Warning << ::COMPONENT_TAG << " The shader compiled with warning(s):\n" <<
			getInfoLog(logLength).data() << Log::Flush();
	}
}

Vector<Char8> Shader::Impl::getInfoLog(const Uint32 logLength) const
{
	Vector<Char8> logBuffer(logLength);
	_openGL->getShaderInfoLog(_shaderHandle, logBuffer.size(), nullptr, logBuffer.data());
	DE_CHECK_ERROR_OPENGL(_openGL);

	return logBuffer;
}


// Graphics::Shader

// Private

Shader::Shader(GraphicsInterface graphicsInterface, const ShaderType& type, const String8& source)
	: _impl(DE_NEW(Impl)(static_cast<OpenGL*>(graphicsInterface), type, source)) { }

Shader::~Shader()
{
	DE_DELETE(_impl, Impl);
}


// External

static Uint32 getShaderTypeId(const ShaderType& shaderType)
{
	switch(shaderType)
	{
		case ShaderType::Compute:
			return OpenGL::COMPUTE_SHADER; // TODO: OpenGL 4.3

		case ShaderType::Fragment:
			return OpenGL::FRAGMENT_SHADER;

		case ShaderType::Geometry:
			return OpenGL::GEOMETRY_SHADER;

		case ShaderType::TessellationControl:
			return OpenGL::TESS_CONTROL_SHADER; // TODO: OpenGL 4.0

		case ShaderType::TessellationEvaluation:
			return OpenGL::TESS_EVALUATION_SHADER;

		case ShaderType::Vertex:
			return OpenGL::VERTEX_SHADER;

		default:
			DE_ASSERT(false);
			return 0u;
	}
}
