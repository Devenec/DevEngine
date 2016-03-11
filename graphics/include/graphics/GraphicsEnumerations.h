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
 *   A2B10G10R10Int,
 *   A2B10G10R10IntNormalised,
 *   A2B10G10R10Uint,
 *   A2B10G10R10UintNormalised,
 *   A2R10G10B10IntNormalised,
 *   A2R10G10B10UintNormalised,
 *   B8G8R8A8UintNormalised,
 *   R16Float,
 *   R16G16Float,
 *   R16G16B16Float,
 *   R16G16B16A16Float,
 *   R32Float,
 *   R32G32Float,
 *   R32G32B32Float,
 *   R32G32B32A32Float,
 *   R8Int,
 *   R8IntNormalised,
 *   R8G8Int,
 *   R8G8IntNormalised,
 *   R8G8B8Int,
 *   R8G8B8IntNormalised,
 *   R8G8B8A8Int,
 *   R8G8B8A8IntNormalised,
 *   R16Int,
 *   R16IntNormalised,
 *   R16G16Int,
 *   R16G16IntNormalised,
 *   R16G16B16Int,
 *   R16G16B16IntNormalised,
 *   R16G16B16A16Int,
 *   R16G16B16A16IntNormalised,
 *   R32Int,
 *   R32IntNormalised,
 *   R32G32Int,
 *   R32G32IntNormalised,
 *   R32G32B32Int,
 *   R32G32B32IntNormalised,
 *   R32G32B32A32Int,
 *   R32G32B32A32IntNormalised,
 *   R8Uint,
 *   R8UintNormalised,
 *   R8G8Uint,
 *   R8G8UintNormalised,
 *   R8G8B8Uint,
 *   R8G8B8UintNormalised,
 *   R8G8B8A8Uint,
 *   R8G8B8A8UintNormalised,
 *   R16Uint,
 *   R16UintNormalised,
 *   R16G16Uint,
 *   R16G16UintNormalised,
 *   R16G16B16Uint,
 *   R16G16B16UintNormalised,
 *   R16G16B16A16Uint,
 *   R16G16B16A16UintNormalised,
 *   R32Uint,
 *   R32UintNormalised,
 *   R32G32Uint,
 *   R32G32UintNormalised,
 *   R32G32B32Uint,
 *   R32G32B32UintNormalised,
 *   R32G32B32A32Uint,
 *   R32G32B32A32UintNormalised
 * };
 */
#if DE_PLATFORM == DE_PLATFORM_LINUX || DE_PLATFORM == DE_PLATFORM_WINDOWS
	#include <platform/opengl/OpenGLGraphicsEnumerations.h>
#else
	#error The target platform is not supported.
#endif
