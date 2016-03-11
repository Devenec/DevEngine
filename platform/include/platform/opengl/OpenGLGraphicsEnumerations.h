/**
 * @file platform/opengl/OpenGLGraphicsEnumerations.h
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

namespace Graphics
{
	/*
	 * Encoding:
	 *
	 * if BufferBinding::Index
	 *   OpenGL::ELEMENT_ARRAY_BUFFER << 4
	 * else
	 *   (OpenGL::*_BUFFER << 4) + <bit mask index>
	 */
	enum class BufferBinding
	{
		Index	= 0x088930,
		Uniform = 0x08A110,
		Vertex	= 0x088921
	};

	/*
	 * Encoding:
	 *
	 * OpenGL::*_DRAW
	 */
	enum class BufferUsage
	{
		Dynamic = 0x88E8,
		Static	= 0x88E4,
		Stream	= 0x88E0
	};

	/*
	 * Encoding:
	 *
	 * (OpenGL::UNSIGNED_* << 2) + (<type byte count> - 1)
	 */
	enum class IndexType
	{
		Uint8  = 0x5004,
		Uint16 = 0x500D,
		Uint32 = 0x5017
	};

	/*
	 * Encoding:
	 *
	 * OpenGL::*
	 */
	enum class PrimitiveType
	{
		Line		  = 0x01,
		LineLoop	  = 0x02,
		LineStrip	  = 0x03,
		Point		  = 0x00,
		Triangle	  = 0x04,
		TriangleFan	  = 0x06,
		TriangleStrip = 0x05
	};

	/*
	 * Encoding:
	 *
	 * (OpenGL::* << 4) | (<BGRA> ? 0x08 : 0x00) | (<normalised> ? 0x04 : 0x00) + (<component count> - 1)
	 */
	enum class VertexElementType
	{
		A2B10G10R10Int			   = 0x08D9F3,
		A2B10G10R10IntNormalised   = 0x08D9F7,
		A2B10G10R10Uint			   = 0x083683,
		A2B10G10R10UintNormalised  = 0x083687,
		A2R10G10B10IntNormalised   = 0x08D9FF,
		A2R10G10B10UintNormalised  = 0x08368F,
		B8G8R8A8UintNormalised	   = 0x01401F,
		R16Float				   = 0x0140B0,
		R16G16Float				   = 0x0140B1,
		R16G16B16Float			   = 0x0140B2,
		R16G16B16A16Float		   = 0x0140B3,
		R32Float				   = 0x014060,
		R32G32Float				   = 0x014061,
		R32G32B32Float			   = 0x014062,
		R32G32B32A32Float		   = 0x014063,
		R8Int					   = 0x014000,
		R8IntNormalised			   = 0x014004,
		R8G8Int					   = 0x014001,
		R8G8IntNormalised		   = 0x014005,
		R8G8B8Int				   = 0x014002,
		R8G8B8IntNormalised		   = 0x014006,
		R8G8B8A8Int				   = 0x014003,
		R8G8B8A8IntNormalised	   = 0x014007,
		R16Int					   = 0x014020,
		R16IntNormalised		   = 0x014024,
		R16G16Int				   = 0x014021,
		R16G16IntNormalised		   = 0x014025,
		R16G16B16Int			   = 0x014022,
		R16G16B16IntNormalised	   = 0x014026,
		R16G16B16A16Int			   = 0x014023,
		R16G16B16A16IntNormalised  = 0x014027,
		R32Int					   = 0x014040,
		R32IntNormalised		   = 0x014044,
		R32G32Int				   = 0x014041,
		R32G32IntNormalised		   = 0x014045,
		R32G32B32Int			   = 0x014042,
		R32G32B32IntNormalised	   = 0x014046,
		R32G32B32A32Int			   = 0x014043,
		R32G32B32A32IntNormalised  = 0x014047,
		R8Uint					   = 0x014010,
		R8UintNormalised		   = 0x014014,
		R8G8Uint				   = 0x014011,
		R8G8UintNormalised		   = 0x014015,
		R8G8B8Uint				   = 0x014012,
		R8G8B8UintNormalised	   = 0x014016,
		R8G8B8A8Uint			   = 0x014013,
		R8G8B8A8UintNormalised	   = 0x014017,
		R16Uint					   = 0x014030,
		R16UintNormalised		   = 0x014034,
		R16G16Uint				   = 0x014031,
		R16G16UintNormalised	   = 0x014035,
		R16G16B16Uint			   = 0x014032,
		R16G16B16UintNormalised	   = 0x014036,
		R16G16B16A16Uint		   = 0x014033,
		R16G16B16A16UintNormalised = 0x014037,
		R32Uint					   = 0x014050,
		R32UintNormalised		   = 0x014054,
		R32G32Uint				   = 0x014051,
		R32G32UintNormalised	   = 0x014055,
		R32G32B32Uint			   = 0x014052,
		R32G32B32UintNormalised	   = 0x014056,
		R32G32B32A32Uint		   = 0x014053,
		R32G32B32A32UintNormalised = 0x014057
	};
}
