/**
 * @file platform/opengl/OpenGLShader.h
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

#pragma once

#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Shader.h>

namespace Platform
{
	class OpenGL;
}

namespace Graphics
{
	class Shader::Implementation final
	{
	public:

		Implementation(GraphicsInterfaceHandle graphicsInterfaceHandle, const ShaderType& type,
			const Core::String8& source);

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		inline Uint32 handle() const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		using CharacterBuffer = Core::Vector<Char8>;

		Platform::OpenGL* _openGL;
		Uint32 _shaderHandle;

		void createShader(const ShaderType& type);
		void compileShader(const Core::String8& source) const;
		void checkCompilationStatus() const;
		Int32 getParameter(const Uint32 parameterName) const;
		void outputCompilerFailureLog() const;
		void outputCompilerSuccessLog() const;
		CharacterBuffer getInfoLog(const Uint32 logLength) const;
	};

#include "inline/OpenGLShader.inl"
}
