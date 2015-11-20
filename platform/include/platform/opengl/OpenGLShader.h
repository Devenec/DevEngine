/**
 * @file platform/opengl/OpenGLShader.h
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

#pragma once

#include <core/Vector.h>
#include <graphics/Shader.h>

namespace Platform
{
	class OpenGL;
}

namespace Graphics
{
	class Shader::Impl final
	{
	public:

		Impl(Platform::OpenGL* openGL, const ShaderType& type, const Core::String8& source);

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl();

		inline Uint32 handle() const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

	private:

		Platform::OpenGL* _openGL;
		Uint32 _shaderHandle;

		void createShader(const ShaderType& type);
		void compileShader(const Core::String8& source) const;
		void checkCompilationStatus() const;
		Int32 getParameter(const Uint32 parameterName) const;
		void outputCompilerFailureLog() const;
		void outputCompilerSuccessLog() const;
		Core::Vector<Char8> getInfoLog(const Uint32 logLength) const;
	};

#include "inline/OpenGLShader.inl"
}
