/**
 * @file graphics/EffectCode.h
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

#include <content/ContentBase.h>
#include <core/Utility.h>

namespace Graphics
{
	class EffectCode final : public Content::ContentBase
	{
	public:

		EffectCode() = default;

		EffectCode(const EffectCode& effectCode) = delete;
		EffectCode(EffectCode&& effectCode) = delete;

		~EffectCode() = default;

		inline const Core::ByteList& fragmentShaderCode() const;

		inline void setFragmentShaderCode(const Core::ByteList& code);

		inline void setVertexShaderCode(const Core::ByteList& code);

		inline const Core::ByteList& vertexShaderCode() const;

		EffectCode& operator =(const EffectCode& effectCode) = delete;
		EffectCode& operator =(EffectCode&& effectCode) = delete;

	private:

		Core::ByteList _fragmentShaderCode;
		Core::ByteList _vertexShaderCode;
	};

#include "inline/EffectCode.inl"
}
