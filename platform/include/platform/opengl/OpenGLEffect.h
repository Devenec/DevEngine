/**
 * @file platform/opengl/OpenGLEffect.h
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
#include <graphics/Effect.h>

namespace Graphics
{
	class Effect::Implementation final
	{
	public:

		Implementation();

		Implementation(const Implementation& implementation) = delete;
		Implementation(Implementation&& implementation) = delete;

		~Implementation();

		void attachShader(Shader* shader) const;

		inline void bind() const;

		inline void debind() const;

		void link() const;

		void setUniformBlockBinding(const Uint32 blockIndex, const Uint32 bindingIndex) const;

		Implementation& operator =(const Implementation& implementation) = delete;
		Implementation& operator =(Implementation&& implementation) = delete;

	private:

		using CharacterBuffer = Core::Vector<Char8>;

		Uint32 _programHandle;

		void checkLinkingStatus() const;
		void detachShaders() const;
		Int32 getParameter(const Uint32 parameterName) const;
		void outputLinkerFailureLog() const;
		void outputLinkerSuccessLog() const;
		CharacterBuffer getInfoLog(const Uint32 logLength) const;

		static void bind(const Uint32 programHandle);
	};

#include "inline/OpenGLEffect.inl"
}
