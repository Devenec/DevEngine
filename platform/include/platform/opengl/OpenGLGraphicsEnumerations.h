/**
 * @file platform/opengl/OpenGLGraphicsEnumerations.h
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

namespace Graphics
{
	enum class BufferBinding
	{
		Index	= 0x8893,
		Uniform = 0x8A11,
		Vertex	= 0x8892
	};

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

	enum class VertexElementType
	{
		Float16				   = 0x00A059,
		Float16Vector2		   = 0x00A05A,
		Float16Vector3		   = 0x00A05B,
		Float16Vector4		   = 0x00A05C,
		Float32				   = 0x00A031,
		Float32Vector2		   = 0x00A032,
		Float32Vector3		   = 0x00A033,
		Float32Vector4		   = 0x00A034,
		Float64				   = 0x00A051,
		Float64Vector2		   = 0x00A052,
		Float64Vector3		   = 0x00A053,
		Float64Vector4		   = 0x00A054,
		Int8				   = 0x00A001,
		Int8Vector2			   = 0x00A002,
		Int8Vector3			   = 0x00A003,
		Int8Vector4			   = 0x00A004,
		Int16				   = 0x00A011,
		Int16Vector2		   = 0x00A012,
		Int16Vector3		   = 0x00A013,
		Int16Vector4		   = 0x00A014,
		Int32				   = 0x00A021,
		Int32Vector2		   = 0x00A022,
		Int32Vector3		   = 0x00A023,
		Int32Vector4		   = 0x00A024,
		Int32_B10G10R10A2	   = 0x046CFE,
		Int32_R10G10B10A2	   = 0x046CFD,
		Uint8				   = 0x00A009,
		Uint8Vector2		   = 0x00A00A,
		Uint8Vector3		   = 0x00A00B,
		Uint8Vector4		   = 0x00A00C,
		Uint16				   = 0x00A019,
		Uint16Vector2		   = 0x00A01A,
		Uint16Vector3		   = 0x00A01B,
		Uint16Vector4		   = 0x00A01C,
		Uint32				   = 0x00A029,
		Uint32Vector2		   = 0x00A02A,
		Uint32Vector3		   = 0x00A02B,
		Uint32Vector4		   = 0x00A02C,
		Uint32_B10G10R10A2	   = 0x041B46,
		Uint32_R10G10B10A2	   = 0x041B45,
		Uint32_R11G11B10_Float = 0x0461DB
	};
}
