/**
 * @file platform/opengl/OpenGLShader.h
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

#pragma once

#include <core/Types.h>
#include <core/Vector.h>
#include <graphics/Shader.h>

namespace Graphics
{
	class Shader::Impl final
	{
	public:

		Impl(const ShaderType& type, const Core::String8& source);

		Impl(const Impl& impl) = delete;
		Impl(Impl&& impl) = delete;

		~Impl();

		Uint32 handle() const;

		Impl& operator =(const Impl& impl) = delete;
		Impl& operator =(Impl&& impl) = delete;

	private:

		static const Char8* COMPONENT_TAG;

		Uint32 _shaderHandle;

		void createShader(const Uint32 typeId);
		void compileShader(const Core::String8& source) const;
		void checkCompilationStatus() const;
		Int32 getParameter(const Uint32 parameterName) const;
		void outputCompilerFailureLog() const;
		void outputCompilerSuccessLog() const;
		Core::Vector<Char8> getInfoLog(const Uint32 logLength) const;

		static Uint32 getTypeId(const ShaderType& shaderType);
	};
}
