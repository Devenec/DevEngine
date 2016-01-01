/**
 * @file graphics/Shader.h
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

#include <core/String.h>
#include <graphics/GraphicsResource.h>

namespace Graphics
{
	enum class ShaderType
	{
		Compute,
		Fragment,
		Geometry,
		TessellationControl,
		TessellationEvaluation,
		Vertex
	};

	class Shader final : public GraphicsResource
	{
	public:

		Shader(const Shader& shader) = delete;
		Shader(Shader&& shader) = delete;

		Shader& operator =(const Shader& shader) = delete;
		Shader& operator =(Shader&& shader) = delete;

	private:

		friend class Effect;
		friend class GraphicsDevice;

		class Implementation;

		Implementation* _implementation;

		Shader(GraphicsInterface graphicsInterface, const ShaderType& type, const Core::String8& source);
		~Shader();
	};
}
