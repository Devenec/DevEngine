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

	// Encoding: OpenGL::*_DRAW
	enum class BufferUsage
	{
		Dynamic = 0x88E8,
		Static	= 0x88E4,
		Stream	= 0x88E0
	};

	// Encoding: (OpenGL::UNSIGNED_* << 2) + (<type byte count> - 1)
	enum class IndexType
	{
		Uint8  = 0x5004,
		Uint16 = 0x500D,
		Uint32 = 0x5017
	};

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
	 * if BGRA
	 *   ((OpenGL::* << 3) | 0x04) + (<component count> - 1)
	 * else
	 *   (OpenGL::* << 3) + (<component count> - 1)
	 */
	enum class VertexElementType
	{
		Float16				   = 0x00A058,
		Float16Vector2		   = 0x00A059,
		Float16Vector3		   = 0x00A05A,
		Float16Vector4		   = 0x00A05B,
		Float32				   = 0x00A030,
		Float32Vector2		   = 0x00A031,
		Float32Vector3		   = 0x00A032,
		Float32Vector4		   = 0x00A033,
		Float64				   = 0x00A050,
		Float64Vector2		   = 0x00A051,
		Float64Vector3		   = 0x00A052,
		Float64Vector4		   = 0x00A053,
		Int8				   = 0x00A000,
		Int8Vector2			   = 0x00A001,
		Int8Vector3			   = 0x00A002,
		Int8Vector4			   = 0x00A003,
		Int16				   = 0x00A010,
		Int16Vector2		   = 0x00A011,
		Int16Vector3		   = 0x00A012,
		Int16Vector4		   = 0x00A013,
		Int32				   = 0x00A020,
		Int32Vector2		   = 0x00A021,
		Int32Vector3		   = 0x00A022,
		Int32Vector4		   = 0x00A023,
		Int32_A2B10G10R10	   = 0x046CFF,
		Int32_A2R10G10B10	   = 0x046CFB,
		Uint8				   = 0x00A008,
		Uint8Vector2		   = 0x00A009,
		Uint8Vector3		   = 0x00A00A,
		Uint8Vector4		   = 0x00A00B,
		Uint16				   = 0x00A018,
		Uint16Vector2		   = 0x00A019,
		Uint16Vector3		   = 0x00A01A,
		Uint16Vector4		   = 0x00A01B,
		Uint32				   = 0x00A028,
		Uint32Vector2		   = 0x00A029,
		Uint32Vector3		   = 0x00A02A,
		Uint32Vector4		   = 0x00A02B,
		Uint32_A2B10G10R10	   = 0x041B47,
		Uint32_A2R10G10B10	   = 0x041B43
	};
}
