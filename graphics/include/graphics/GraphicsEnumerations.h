/**
 * @file graphics/GraphicsEnumerations.h
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

#include <core/Platform.h>

/**
 * The following enumerations are defined in the internal header file (the
 * values are platform defined):
 *
 * enum class BufferBinding
 * {
 *   Index,
 *   Uniform,
 *   Vertex
 * };
 *
 * enum class BufferUsage
 * {
 *   Dynamic,
 *   Static,
 *   Stream
 * };
 *
 * enum class IndexType
 * {
 *   Uint8,
 *   Uint16,
 *   Uint32
 * };
 *
 * enum class PrimitiveType
 * {
 *   Line,
 *   LineLoop,
 *   LineStrip,
 *   Point,
 *   Triangle,
 *   TriangleFan,
 *   TriangleStrip
 * };
 *
 * enum class VertexElementType
 * {
 *   Float16,
 *   Float16Vector2,
 *   Float16Vector3,
 *   Float16Vector4,
 *   Float32,
 *   Float32Vector2,
 *   Float32Vector3,
 *   Float32Vector4,
 *   Float64,
 *   Float64Vector2,
 *   Float64Vector3,
 *   Float64Vector4,
 *   Int8,
 *   Int8Vector2,
 *   Int8Vector3,
 *   Int8Vector4,
 *   Int16,
 *   Int16Vector2,
 *   Int16Vector3,
 *   Int16Vector4,
 *   Int32,
 *   Int32Vector2,
 *   Int32Vector3,
 *   Int32Vector4,
 *   Int32_A2B10G10R10,
 *   Int32_A2R10G10B10,
 *   Uint8,
 *   Uint8Vector2,
 *   Uint8Vector3,
 *   Uint8Vector4,
 *   Uint16,
 *   Uint16Vector2,
 *   Uint16Vector3,
 *   Uint16Vector4,
 *   Uint32,
 *   Uint32Vector2,
 *   Uint32Vector3,
 *   Uint32Vector4,
 *   Uint32_A2B10G10R10,
 *   Uint32_A2R10G10B10
 * };
 */
#if DE_PLATFORM == DE_PLATFORM_LINUX || DE_PLATFORM == DE_PLATFORM_WINDOWS
	#include <platform/opengl/OpenGLGraphicsEnumerations.h>
#else
	#error The target platform is not supported.
#endif
