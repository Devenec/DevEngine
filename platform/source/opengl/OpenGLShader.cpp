/**
 * @file platform/opengl/OpenGLShader.cpp
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
#include <platform/opengl/OpenGL.h>
#include <platform/opengl/OpenGLShader.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// Implementation

// Public

Shader::Impl::Impl(const ShaderType& type, const String8& source)
	: _shaderHandle(0u)
{
	const Uint32 typeId = getTypeId(type);
	createShader(typeId);
	compileShader(source);
	checkCompilationStatus();
}

Shader::Impl::~Impl()
{
	OpenGL::deleteShader(_shaderHandle);
	DE_CHECK_ERROR_OPENGL();
}

Uint32 Shader::Impl::handle() const
{
	return _shaderHandle;
}

// Private

const Char8* Shader::Impl::COMPONENT_TAG = "[Platform::Shader - OpenGL]";

void Shader::Impl::createShader(const Uint32 typeId)
{
	_shaderHandle = OpenGL::createShader(typeId);
	DE_CHECK_ERROR_OPENGL();

	if(_shaderHandle == 0u)
	{
		// TODO: add shader type to the error message?
		defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to create the shader." << Log::Flush();
		DE_ERROR(0x0);
	}
}

void Shader::Impl::compileShader(const String8& source) const
{
	const Char8* sourceCharacters = source.c_str();
	OpenGL::shaderSource(_shaderHandle, 1, &sourceCharacters, nullptr);
	DE_CHECK_ERROR_OPENGL();
	OpenGL::compileShader(_shaderHandle);
	DE_CHECK_ERROR_OPENGL();
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
	OpenGL::getShaderiv(_shaderHandle, parameterName, &parameter);
	DE_CHECK_ERROR_OPENGL();

	return parameter;
}

void Shader::Impl::outputCompilerFailureLog() const
{
	defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to compile the shader:\n\t";
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
		defaultLog << getInfoLog(logLength).data();
	else
		defaultLog << "No compiler log available.";

	defaultLog << Log::Flush();
}

void Shader::Impl::outputCompilerSuccessLog() const
{
	const Uint32 logLength = getParameter(OpenGL::INFO_LOG_LENGTH);

	if(logLength > 1u)
	{
		defaultLog << LogLevel::Warning << COMPONENT_TAG << " The shader compiled with warning(s):\n\t" <<
			getInfoLog(logLength).data() << Log::Flush();
	}
}

Vector<Char8> Shader::Impl::getInfoLog(const Uint32 logLength) const
{
	Vector<Char8> logBuffer(logLength);
	OpenGL::getShaderInfoLog(_shaderHandle, logBuffer.size(), nullptr, logBuffer.data());
	DE_CHECK_ERROR_OPENGL();

	return logBuffer;
}

// Static

Uint32 Shader::Impl::getTypeId(const ShaderType& shaderType)
{
	switch(shaderType)
	{
		case ShaderType::Compute:
			return OpenGL::COMPUTE_SHADER;

		case ShaderType::Fragment:
			return OpenGL::FRAGMENT_SHADER;

		case ShaderType::Geometry:
			return OpenGL::GEOMETRY_SHADER;

		case ShaderType::TessellationControl:
			return OpenGL::TESS_CONTROL_SHADER;

		case ShaderType::TessellationEvaluation:
			return OpenGL::TESS_EVALUATION_SHADER;

		case ShaderType::Vertex:
			return OpenGL::VERTEX_SHADER;

		default:
			return 0u;
	}
}


// Graphics::Shader

// Private

Shader::Shader(const ShaderType& type, const String8& source)
	: _impl(DE_NEW(Impl)(type, source)) { }

Shader::~Shader()
{
	DE_DELETE(_impl, Impl);
}
