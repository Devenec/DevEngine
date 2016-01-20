/**
 * @file platform/opengl/OpenGL.h
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
 *
 *
 * Copyright (c) 2013-2015 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and/or associated documentation files (the
 * "Materials"), to deal in the Materials without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Materials, and to
 * permit persons to whom the Materials are furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
 */

#pragma once

#include <core/ConfigInternal.h>
#include <core/Platform.h>
#include <core/Singleton.h>
#include <core/String.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <core/Vector.h>
#include <graphics/LogUtility.h>

#if DE_COMPILER == DE_COMPILER_MSVC
	#define DE_CALL_OPENGL DE_INTERNAL_CALL_STDCALL
#else
	#define DE_CALL_OPENGL
#endif

#if defined(DE_INTERNAL_BUILD_DEVELOPMENT)
	#define DE_CHECK_ERROR_OPENGL() \
		OpenGL::checkForErrors(DE_FILE, DE_LINE, DE_FUNCTION)
#else
	#define DE_CHECK_ERROR_OPENGL() \
		DE_NO_OPERATION
#endif

namespace Platform
{
	class OpenGL final : public Core::Singleton<OpenGL>
	{
	public:

		// Version 1.0

		using Bitfield = Uint32;
		using Boolean  = Uint8;
		using Enum	   = Uint32;
		using Sizei	   = Int32;

		using BlendFunc = void (DE_CALL_OPENGL*)(Enum sfactor, Enum dfactor);
		using Clear = void (DE_CALL_OPENGL*)(Bitfield mask);
		using ClearColor = void (DE_CALL_OPENGL*)(Float32 red, Float32 green, Float32 blue, Float32 alpha);
		using ClearDepth = void (DE_CALL_OPENGL*)(Float64 depth);
		using ClearStencil = void (DE_CALL_OPENGL*)(Int32 s);
		using ColorMask = void (DE_CALL_OPENGL*)(Boolean red, Boolean green, Boolean blue, Boolean alpha);
		using CullFace = void (DE_CALL_OPENGL*)(Enum mode);
		using DepthFunc = void (DE_CALL_OPENGL*)(Enum func);
		using DepthMask = void (DE_CALL_OPENGL*)(Boolean flag);
		using DepthRange = void (DE_CALL_OPENGL*)(Float64 near, Float64 far);
		using Disable = void (DE_CALL_OPENGL*)(Enum cap);
		using DrawBuffer = void (DE_CALL_OPENGL*)(Enum buf);
		using Enable = void (DE_CALL_OPENGL*)(Enum cap);
		using Finish = void (DE_CALL_OPENGL*)();
		using Flush = void (DE_CALL_OPENGL*)();
		using FrontFace = void (DE_CALL_OPENGL*)(Enum mode);
		using GetBooleanV = void (DE_CALL_OPENGL*)(Enum pname, Boolean* data);
		using GetDoubleV = void (DE_CALL_OPENGL*)(Enum pname, Float64* data);
		using GetError = Enum (DE_CALL_OPENGL*)();
		using GetFloatV = void (DE_CALL_OPENGL*)(Enum pname, Float32* data);
		using GetIntegerV = void (DE_CALL_OPENGL*)(Enum pname, Int32* data);
		using GetString = const Uint8* (DE_CALL_OPENGL*)(Enum name);

		using GetTexImage =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum format, Enum type, Void* pixels);

		using GetTexLevelParameterFV =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum pname, Float32* params);

		using GetTexLevelParameterIV =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum pname, Int32* params);

		using GetTexParameterFV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Float32* params);
		using GetTexParameterIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);
		using Hint = void (DE_CALL_OPENGL*)(Enum target, Enum mode);
		using IsEnabled = Boolean (DE_CALL_OPENGL*)(Enum cap);
		using LineWidth = void (DE_CALL_OPENGL*)(Float32 width);
		using LogicOp = void (DE_CALL_OPENGL*)(Enum opcode);
		using PixelStoreF = void (DE_CALL_OPENGL*)(Enum pname, Float32 param);
		using PixelStoreI = void (DE_CALL_OPENGL*)(Enum pname, Int32 param);
		using PointSize = void (DE_CALL_OPENGL*)(Float32 size);
		using PolygonMode = void (DE_CALL_OPENGL*)(Enum face, Enum mode);
		using ReadBuffer = void (DE_CALL_OPENGL*)(Enum src);

		using ReadPixels =
			void (DE_CALL_OPENGL*)(Int32 x, Int32 y, Sizei width, Sizei height, Enum format, Enum type,
				Void* pixels);

		using Scissor = void (DE_CALL_OPENGL*)(Int32 x, Int32 y, Sizei width, Sizei height);
		using StencilFunc = void (DE_CALL_OPENGL*)(Enum func, Int32 ref, Uint32 mask);
		using StencilMask = void (DE_CALL_OPENGL*)(Uint32 mask);
		using StencilOp = void (DE_CALL_OPENGL*)(Enum fail, Enum zfail, Enum zpass);

		using TexImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 internalformat, Sizei width, Int32 border,
				Enum format, Enum type, const Void* pixels);

		using TexImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 internalformat, Sizei width, Sizei height,
				Int32 border, Enum format, Enum type, const Void* pixels);

		using TexParameterF = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Float32 param);
		using TexParameterFV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, const Float32* params);
		using TexParameterI = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32 param);
		using TexParameterIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, const Int32* params);
		using Viewport = void (DE_CALL_OPENGL*)(Int32 x, Int32 y, Sizei width, Sizei height);

		// Version 1.1

		using BindTexture = void (DE_CALL_OPENGL*)(Enum target, Uint32 texture);

		using CopyTexImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum internalformat, Int32 x, Int32 y,
				Sizei width, Int32 border);

		using CopyTexImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum internalformat, Int32 x, Int32 y,
				Sizei width, Sizei height, Int32 border);

		using CopyTexSubImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 x, Int32 y, Sizei width);

		using CopyTexSubImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Int32 x, Int32 y,
				Sizei width, Sizei height);

		using DeleteTextures = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* textures);
		using DrawArrays = void (DE_CALL_OPENGL*)(Enum mode, Int32 first, Sizei count);
		using DrawElements = void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices);
		using GenTextures = void (DE_CALL_OPENGL*)(Sizei n, Uint32* textures);
		using GetPointerV = void (DE_CALL_OPENGL*)(Enum pname, Void** params);
		using IsTexture = Boolean (DE_CALL_OPENGL*)(Uint32 texture);
		using PolygonOffset = void (DE_CALL_OPENGL*)(Float32 factor, Float32 units);

		using TexSubImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Sizei width, Enum format,
				Enum type, const Void* pixels);

		using TexSubImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Sizei width,
				Sizei height, Enum format, Enum type, const Void* pixels);

		// Version 1.2

		using CopyTexSubImage3D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Int32 x, Int32 y, Sizei width, Sizei height);

		using DrawRangeElements =
			void (DE_CALL_OPENGL*)(Enum mode, Uint32 start, Uint32 end, Sizei count, Enum type,
				const Void* indices);

		using TexImage3D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 internalformat, Sizei width, Sizei height,
				Sizei depth, Int32 border, Enum format, Enum type, const Void* pixels);

		using TexSubImage3D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Enum type, const Void* pixels);

		// Version 1.3

		using ActiveTexture = void (DE_CALL_OPENGL*)(Enum texture);

		using CompressedTexImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum internalformat, Sizei width, Int32 border,
				Sizei imageSize, const Void* data);

		using CompressedTexImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum internalformat, Sizei width, Sizei height,
				Int32 border, Sizei imageSize, const Void* data);

		using CompressedTexImage3D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum internalformat, Sizei width, Sizei height,
				Sizei depth, Int32 border, Sizei imageSize, const Void* data);

		using CompressedTexSubImage1D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Sizei width, Enum format,
				Sizei imageSize, const Void* data);

		using CompressedTexSubImage2D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Sizei width,
				Sizei height, Enum format, Sizei imageSize, const Void* data);

		using CompressedTexSubImage3D =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Sizei imageSize, const Void* data);

		using GetCompressedTexImage = void (DE_CALL_OPENGL*)(Enum target, Int32 level, Void* img);
		using SampleCoverage = void (DE_CALL_OPENGL*)(Float32 value, Boolean invert);

		// Version 1.4

		using BlendColor = void (DE_CALL_OPENGL*)(Float32 red, Float32 green, Float32 blue, Float32 alpha);
		using BlendEquation = void (DE_CALL_OPENGL*)(Enum mode);

		using BlendFuncSeparate =
			void (DE_CALL_OPENGL*)(Enum sfactorRGB, Enum dfactorRGB, Enum sfactorAlpha, Enum dfactorAlpha);

		using MultiDrawArrays =
			void (DE_CALL_OPENGL*)(Enum mode, const Int32* first, const Sizei* count, Sizei drawcount);

		using MultiDrawElements =
			void (DE_CALL_OPENGL*)(Enum mode, const Sizei* count, Enum type, const Void* const* indices,
				Sizei drawcount);

		using PointParameterF = void (DE_CALL_OPENGL*)(Enum pname, Float32 param);
		using PointParameterFV = void (DE_CALL_OPENGL*)(Enum pname, const Float32* params);
		using PointParameterI = void (DE_CALL_OPENGL*)(Enum pname, Int32 param);
		using PointParameterIV = void (DE_CALL_OPENGL*)(Enum pname, const Int32* params);

		// Version 1.5

		using Intptr   = Int;
		using Sizeiptr = Int;

		using BeginQuery = void (DE_CALL_OPENGL*)(Enum target, Uint32 id);
		using BindBuffer = void (DE_CALL_OPENGL*)(Enum target, Uint32 buffer);
		using BufferData = void (DE_CALL_OPENGL*)(Enum target, Sizeiptr size, const Void* data, Enum usage);

		using BufferSubData =
			void (DE_CALL_OPENGL*)(Enum target, Intptr offset, Sizeiptr size, const Void* data);

		using DeleteBuffers = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* buffers);
		using DeleteQueries = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* ids);
		using EndQuery = void (DE_CALL_OPENGL*)(Enum target);
		using GenBuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* buffers);
		using GenQueries = void (DE_CALL_OPENGL*)(Sizei n, Uint32* ids);
		using GetBufferParameterIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);
		using GetBufferPointerV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Void** params);

		using GetBufferSubData =
			void (DE_CALL_OPENGL*)(Enum target, Intptr offset, Sizeiptr size, Void* data);

		using GetQueryIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);
		using GetQueryObjectIV = void (DE_CALL_OPENGL*)(Uint32 id, Enum pname, Int32* params);
		using GetQueryObjectUIV = void (DE_CALL_OPENGL*)(Uint32 id, Enum pname, Uint32* params);
		using IsBuffer = Boolean (DE_CALL_OPENGL*)(Uint32 buffer);
		using IsQuery = Boolean (DE_CALL_OPENGL*)(Uint32 id);
		using MapBuffer = Void* (DE_CALL_OPENGL*)(Enum target, Enum access);
		using UnmapBuffer = Boolean (DE_CALL_OPENGL*)(Enum target);

		// Version 2.0

		using AttachShader = void (DE_CALL_OPENGL*)(Uint32 program, Uint32 shader);
		using BindAttribLocation = void (DE_CALL_OPENGL*)(Uint32 program, Uint32 index, const Char8* name);
		using BlendEquationSeparate = void (DE_CALL_OPENGL*)(Enum modeRGB, Enum modeAlpha);
		using CompileShader = void (DE_CALL_OPENGL*)(Uint32 shader);
		using CreateProgram = Uint32 (DE_CALL_OPENGL*)();
		using CreateShader = Uint32 (DE_CALL_OPENGL*)(Enum type);
		using DeleteProgram = void (DE_CALL_OPENGL*)(Uint32 program);
		using DeleteShader = void (DE_CALL_OPENGL*)(Uint32 shader);
		using DetachShader = void (DE_CALL_OPENGL*)(Uint32 program, Uint32 shader);
		using DisableVertexAttribArray = void (DE_CALL_OPENGL*)(Uint32 index);
		using DrawBuffers = void (DE_CALL_OPENGL*)(Sizei n, const Enum* bufs);
		using EnableVertexAttribArray = void (DE_CALL_OPENGL*)(Uint32 index);

		using GetActiveAttrib =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 index, Sizei bufSize, Sizei* length, Int32* size,
				Enum* type, Char8* name);

		using GetActiveUniform =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 index, Sizei bufSize, Sizei* length, Int32* size,
				Enum* type, Char8* name);

		using GetAttachedShaders =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei maxCount, Sizei* count, Uint32* shaders);

		using GetAttribLocation = Int32 (DE_CALL_OPENGL*)(Uint32 program, const Char8* name);

		using GetProgramInfoLog =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei bufSize, Sizei* length, Char8* infoLog);

		using GetProgramIV = void (DE_CALL_OPENGL*)(Uint32 program, Enum pname, Int32* params);

		using GetShaderInfoLog =
			void (DE_CALL_OPENGL*)(Uint32 shader, Sizei bufSize, Sizei* length, Char8* infoLog);

		using GetShaderIV = void (DE_CALL_OPENGL*)(Uint32 shader, Enum pname, Int32* params);

		using GetShaderSource =
			void (DE_CALL_OPENGL*)(Uint32 shader, Sizei bufSize, Sizei* length, Char8* source);

		using GetUniformFV = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float32* params);
		using GetUniformIV = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Int32* params);
		using GetUniformLocation = Int32 (DE_CALL_OPENGL*)(Uint32 program, const Char8* name);
		using GetVertexAttribDV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Float64* params);
		using GetVertexAttribFV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Float32* params);
		using GetVertexAttribIV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Int32* params);
		using GetVertexAttribPointerV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Void** pointer);
		using IsProgram = Boolean (DE_CALL_OPENGL*)(Uint32 program);
		using IsShader = Boolean (DE_CALL_OPENGL*)(Uint32 shader);
		using LinkProgram = void (DE_CALL_OPENGL*)(Uint32 program);

		using ShaderSource =
			void (DE_CALL_OPENGL*)(Uint32 shader, Sizei count, const Char8* const* string,
				const Int32* length);

		using StencilFuncSeparate = void (DE_CALL_OPENGL*)(Enum face, Enum func, Int32 ref, Uint32 mask);
		using StencilMaskSeparate = void (DE_CALL_OPENGL*)(Enum face, Uint32 mask);
		using StencilOpSeparate = void (DE_CALL_OPENGL*)(Enum face, Enum sfail, Enum dpfail, Enum dppass);
		using Uniform1F = void (DE_CALL_OPENGL*)(Int32 location, Float32 v0);
		using Uniform1FV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float32* value);
		using Uniform1I = void (DE_CALL_OPENGL*)(Int32 location, Int32 v0);
		using Uniform1IV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Int32* value);
		using Uniform2F = void (DE_CALL_OPENGL*)(Int32 location, Float32 v0, Float32 v1);
		using Uniform2FV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float32* value);
		using Uniform2I = void (DE_CALL_OPENGL*)(Int32 location, Int32 v0, Int32 v1);
		using Uniform2IV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Int32* value);
		using Uniform3F = void (DE_CALL_OPENGL*)(Int32 location, Float32 v0, Float32 v1, Float32 v2);
		using Uniform3FV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float32* value);
		using Uniform3I = void (DE_CALL_OPENGL*)(Int32 location, Int32 v0, Int32 v1, Int32 v2);
		using Uniform3IV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Int32* value);

		using Uniform4F =
			void (DE_CALL_OPENGL*)(Int32 location, Float32 v0, Float32 v1, Float32 v2, Float32 v3);

		using Uniform4FV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float32* value);
		using Uniform4I = void (DE_CALL_OPENGL*)(Int32 location, Int32 v0, Int32 v1, Int32 v2, Int32 v3);
		using Uniform4IV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Int32* value);

		using UniformMatrix2FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix3FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix4FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UseProgram = void (DE_CALL_OPENGL*)(Uint32 program);
		using ValidateProgram = void (DE_CALL_OPENGL*)(Uint32 program);
		using VertexAttrib1D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x);
		using VertexAttrib1DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);
		using VertexAttrib1F = void (DE_CALL_OPENGL*)(Uint32 index, Float32 x);
		using VertexAttrib1FV = void (DE_CALL_OPENGL*)(Uint32 index, const Float32* v);
		using VertexAttrib1S = void (DE_CALL_OPENGL*)(Uint32 index, Int16 x);
		using VertexAttrib1SV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttrib2D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y);
		using VertexAttrib2DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);
		using VertexAttrib2F = void (DE_CALL_OPENGL*)(Uint32 index, Float32 x, Float32 y);
		using VertexAttrib2FV = void (DE_CALL_OPENGL*)(Uint32 index, const Float32* v);
		using VertexAttrib2S = void (DE_CALL_OPENGL*)(Uint32 index, Int16 x, Int16 y);
		using VertexAttrib2SV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttrib3D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y, Float64 z);
		using VertexAttrib3DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);
		using VertexAttrib3F = void (DE_CALL_OPENGL*)(Uint32 index, Float32 x, Float32 y, Float32 z);
		using VertexAttrib3FV = void (DE_CALL_OPENGL*)(Uint32 index, const Float32* v);
		using VertexAttrib3S = void (DE_CALL_OPENGL*)(Uint32 index, Int16 x, Int16 y, Int16 z);
		using VertexAttrib3SV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttrib4BV = void (DE_CALL_OPENGL*)(Uint32 index, const Int8* v);

		using VertexAttrib4D =
			void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y, Float64 z, Float64 w);

		using VertexAttrib4DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);

		using VertexAttrib4F =
			void (DE_CALL_OPENGL*)(Uint32 index, Float32 x, Float32 y, Float32 z, Float32 w);

		using VertexAttrib4FV = void (DE_CALL_OPENGL*)(Uint32 index, const Float32* v);
		using VertexAttrib4IV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttrib4NBV = void (DE_CALL_OPENGL*)(Uint32 index, const Int8* v);
		using VertexAttrib4NIV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttrib4NSV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttrib4NUB = void (DE_CALL_OPENGL*)(Uint32 index, Uint8 x, Uint8 y, Uint8 z, Uint8 w);
		using VertexAttrib4NUBV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint8* v);
		using VertexAttrib4NUIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttrib4NUSV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint16* v);
		using VertexAttrib4S = void (DE_CALL_OPENGL*)(Uint32 index, Int16 x, Int16 y, Int16 z, Int16 w);
		using VertexAttrib4SV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttrib4UBV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint8* v);
		using VertexAttrib4UIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttrib4USV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint16* v);

		using VertexAttribPointer =
			void (DE_CALL_OPENGL*)(Uint32 index, Int32 size, Enum type, Boolean normalized, Sizei stride,
				const Void* pointer);

		// Version 2.1

		using UniformMatrix2X3FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix2X4FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix3X2FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix3X4FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix4X2FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		using UniformMatrix4X3FV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float32* value);

		// Version 3.0

		using Half = Uint16;

		using BeginConditionalRender = void (DE_CALL_OPENGL*)(Uint32 id, Enum mode);
		using BeginTransformFeedback = void (DE_CALL_OPENGL*)(Enum primitiveMode);
		using BindBufferBase = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Uint32 buffer);

		using BindBufferRange =
			void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Uint32 buffer, Intptr offset, Sizeiptr size);

		using BindFragDataLocation = void (DE_CALL_OPENGL*)(Uint32 program, Uint32 color, const Char8* name);
		using BindFramebuffer = void (DE_CALL_OPENGL*)(Enum target, Uint32 framebuffer);
		using BindRenderbuffer = void (DE_CALL_OPENGL*)(Enum target, Uint32 renderbuffer);
		using BindVertexArray = void (DE_CALL_OPENGL*)(Uint32 array);

		using BlitFramebuffer =
			void (DE_CALL_OPENGL*)(Int32 srcX0, Int32 srcY0, Int32 srcX1, Int32 srcY1, Int32 dstX0,
				Int32 dstY0, Int32 dstX1, Int32 dstY1, Bitfield mask, Enum filter);

		using CheckFramebufferStatus = Enum (DE_CALL_OPENGL*)(Enum target);
		using ClampColor = void (DE_CALL_OPENGL*)(Enum target, Enum clamp);

		using ClearBufferFI =
			void (DE_CALL_OPENGL*)(Enum buffer, Int32 drawbuffer, Float32 depth, Int32 stencil);

		using ClearBufferFV = void (DE_CALL_OPENGL*)(Enum buffer, Int32 drawbuffer, const Float32* value);
		using ClearBufferIV = void (DE_CALL_OPENGL*)(Enum buffer, Int32 drawbuffer, const Int32* value);
		using ClearBufferUIV = void (DE_CALL_OPENGL*)(Enum buffer, Int32 drawbuffer, const Uint32* value);
		using ColorMaskI = void (DE_CALL_OPENGL*)(Uint32 index, Boolean r, Boolean g, Boolean b, Boolean a);
		using DeleteFramebuffers = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* framebuffers);
		using DeleteRenderbuffers = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* renderbuffers);
		using DeleteVertexArrays = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* arrays);
		using DisableI = void (DE_CALL_OPENGL*)(Enum target, Uint32 index);
		using EnableI = void (DE_CALL_OPENGL*)(Enum target, Uint32 index);
		using EndConditionalRender = void (DE_CALL_OPENGL*)();
		using EndTransformFeedback = void (DE_CALL_OPENGL*)();
		using FlushMappedBufferRange = void (DE_CALL_OPENGL*)(Enum target, Intptr offset, Sizeiptr length);

		using FramebufferRenderbuffer =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Enum renderbuffertarget,
				Uint32 renderbuffer);

		using FramebufferTexture1D =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Enum textarget, Uint32 texture, Int32 level);

		using FramebufferTexture2D =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Enum textarget, Uint32 texture, Int32 level);

		using FramebufferTexture3D =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Enum textarget, Uint32 texture, Int32 level,
				Int32 zoffset);

		using FramebufferTextureLayer =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Uint32 texture, Int32 level, Int32 layer);

		using GenerateMipmap = void (DE_CALL_OPENGL*)(Enum target);
		using GenFramebuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* framebuffers);
		using GenRenderbuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* renderbuffers);
		using GenVertexArrays = void (DE_CALL_OPENGL*)(Sizei n, Uint32* arrays);
		using GetBooleanI_V = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Boolean* data);
		using GetFragDataLocation = Int32 (DE_CALL_OPENGL*)(Uint32 program, const Char8* name);

		using GetFramebufferAttachmentParameterIV =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Enum pname, Int32* params);

		using GetIntegerI_V = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Int32* data);
		using GetRenderbufferParameterIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);
		using GetStringI = const Uint8* (DE_CALL_OPENGL*)(Enum name, Uint32 index);
		using GetTexParameterIIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);
		using GetTexParameterIUIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Uint32* params);

		using GetTransformFeedbackVarying =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 index, Sizei bufSize, Sizei* length, Sizei* size,
				Enum* type, Char8* name);

		using GetUniformUIV = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Uint32* params);
		using GetVertexAttribIIV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Int32* params);
		using GetVertexAttribIUIV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Uint32* params);
		using IsEnabledI = Boolean (DE_CALL_OPENGL*)(Enum target, Uint32 index);
		using IsFramebuffer = Boolean (DE_CALL_OPENGL*)(Uint32 framebuffer);
		using IsRenderbuffer = Boolean (DE_CALL_OPENGL*)(Uint32 renderbuffer);
		using IsVertexArray = Boolean (DE_CALL_OPENGL*)(Uint32 array);

		using MapBufferRange =
			Void* (DE_CALL_OPENGL*)(Enum target, Intptr offset, Sizeiptr length, Bitfield access);

		using RenderbufferStorage =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Sizei width, Sizei height);

		using RenderbufferStorageMultisample =
			void (DE_CALL_OPENGL*)(Enum target, Sizei samples, Enum internalformat, Sizei width,
				Sizei height);

		using TexParameterIIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, const Int32* params);
		using TexParameterIUIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, const Uint32* params);

		using TransformFeedbackVaryings =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei count, const Char8* const* varyings,
				Enum bufferMode);

		using Uniform1UI = void (DE_CALL_OPENGL*)(Int32 location, Uint32 v0);
		using Uniform1UIV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Uint32* value);
		using Uniform2UI = void (DE_CALL_OPENGL*)(Int32 location, Uint32 v0, Uint32 v1);
		using Uniform2UIV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Uint32* value);
		using Uniform3UI = void (DE_CALL_OPENGL*)(Int32 location, Uint32 v0, Uint32 v1, Uint32 v2);
		using Uniform3UIV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Uint32* value);
		using Uniform4UI = void (DE_CALL_OPENGL*)(Int32 location, Uint32 v0, Uint32 v1, Uint32 v2, Uint32 v3);
		using Uniform4UIV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Uint32* value);
		using VertexAttribI1I = void (DE_CALL_OPENGL*)(Uint32 index, Int32 x);
		using VertexAttribI1IV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttribI1UI = void (DE_CALL_OPENGL*)(Uint32 index, Uint32 x);
		using VertexAttribI1UIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttribI2I = void (DE_CALL_OPENGL*)(Uint32 index, Int32 x, Int32 y);
		using VertexAttribI2IV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttribI2UI = void (DE_CALL_OPENGL*)(Uint32 index, Uint32 x, Uint32 y);
		using VertexAttribI2UIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttribI3I = void (DE_CALL_OPENGL*)(Uint32 index, Int32 x, Int32 y, Int32 z);
		using VertexAttribI3IV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttribI3UI = void (DE_CALL_OPENGL*)(Uint32 index, Uint32 x, Uint32 y, Uint32 z);
		using VertexAttribI3UIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttribI4BV = void (DE_CALL_OPENGL*)(Uint32 index, const Int8* v);
		using VertexAttribI4I = void (DE_CALL_OPENGL*)(Uint32 index, Int32 x, Int32 y, Int32 z, Int32 w);
		using VertexAttribI4IV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using VertexAttribI4SV = void (DE_CALL_OPENGL*)(Uint32 index, const Int16* v);
		using VertexAttribI4UBV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint8* v);
		using VertexAttribI4UI = void (DE_CALL_OPENGL*)(Uint32 index, Uint32 x, Uint32 y, Uint32 z, Uint32 w);
		using VertexAttribI4UIV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint32* v);
		using VertexAttribI4USV = void (DE_CALL_OPENGL*)(Uint32 index, const Uint16* v);

		using VertexAttribIPointer =
			void (DE_CALL_OPENGL*)(Uint32 index, Int32 size, Enum type, Sizei stride, const Void* pointer);

		// Version 3.1

		using CopyBufferSubData =
			void (DE_CALL_OPENGL*)(Enum readTarget, Enum writeTarget, Intptr readOffset, Intptr writeOffset,
				Sizeiptr size);

		using DrawArraysInstanced =
			void (DE_CALL_OPENGL*)(Enum mode, Int32 first, Sizei count, Sizei instancecount);

		using DrawElementsInstanced =
			void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices,
				Sizei instancecount);

		using GetActiveUniformBlockIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 uniformBlockIndex, Enum pname, Int32* params);

		using GetActiveUniformBlockName =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 uniformBlockIndex, Sizei bufSize, Sizei* length,
				Char8* uniformBlockName);

		using GetActiveUniformName =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 uniformIndex, Sizei bufSize, Sizei* length,
				Char8* uniformName);

		using GetActiveUniformsIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei uniformCount, const Uint32* uniformIndices,
				Enum pname, Int32* params);

		using GetUniformBlockIndex = Uint32 (DE_CALL_OPENGL*)(Uint32 program, const Char8* uniformBlockName);

		using GetUniformIndices =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei uniformCount, const Char8* const* uniformNames,
				Uint32* uniformIndices);

		using PrimitiveRestartIndex = void (DE_CALL_OPENGL*)(Uint32 index);
		using TexBuffer = void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Uint32 buffer);

		using UniformBlockBinding =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 uniformBlockIndex, Uint32 uniformBlockBinding);

		// Version 3.2

		struct SyncStruct;
		using Sync = SyncStruct*;

		using ClientWaitSync = Enum (DE_CALL_OPENGL*)(Sync sync, Bitfield flags, Uint64 timeout);
		using DeleteSync = void (DE_CALL_OPENGL*)(Sync sync);

		using DrawElementsBaseVertex =
			void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices, Int32 basevertex);

		using DrawElementsInstancedBaseVertex =
			void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices,
				Sizei instancecount, Int32 basevertex);

		using DrawRangeElementsBaseVertex =
			void (DE_CALL_OPENGL*)(Enum mode, Uint32 start, Uint32 end, Sizei count, Enum type,
				const Void* indices, Int32 basevertex);

		using FenceSync = Sync (DE_CALL_OPENGL*)(Enum condition, Bitfield flags);

		using FramebufferTexture =
			void (DE_CALL_OPENGL*)(Enum target, Enum attachment, Uint32 texture, Int32 level);

		using GetBufferParameterI64V = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int64* params);
		using GetInteger64I_V = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Int64* data);
		using GetInteger64V = void (DE_CALL_OPENGL*)(Enum pname, Int64* data);
		using GetMultisampleFV = void (DE_CALL_OPENGL*)(Enum pname, Uint32 index, Float32* val);

		using GetSyncIV =
			void (DE_CALL_OPENGL*)(Sync sync, Enum pname, Sizei bufSize, Sizei* length, Int32* values);

		using IsSync = Boolean (DE_CALL_OPENGL*)(Sync sync);

		using MultiDrawElementsBaseVertex =
			void (DE_CALL_OPENGL*)(Enum mode, const Sizei* count, Enum type, const Void* const* indices,
				Sizei drawcount, const Int32* basevertex);

		using ProvokingVertex = void (DE_CALL_OPENGL*)(Enum mode);
		using SampleMaskI = void (DE_CALL_OPENGL*)(Uint32 maskNumber, Bitfield mask);

		using TexImage2DMultisample =
			void (DE_CALL_OPENGL*)(Enum target, Sizei samples, Enum internalformat, Sizei width, Sizei height,
				Boolean fixedsamplelocations);

		using TexImage3DMultisample =
			void (DE_CALL_OPENGL*)(Enum target, Sizei samples, Enum internalformat, Sizei width, Sizei height,
				Sizei depth, Boolean fixedsamplelocations);

		using WaitSync = void (DE_CALL_OPENGL*)(Sync sync, Bitfield flags, Uint64 timeout);

		// Version 3.3

		using BindFragDataLocationIndexed =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 colorNumber, Uint32 index, const Char8* name);

		using BindSampler = void (DE_CALL_OPENGL*)(Uint32 unit, Uint32 sampler);
		using DeleteSamplers = void (DE_CALL_OPENGL*)(Sizei count, const Uint32* samplers);
		using GenSamplers = void (DE_CALL_OPENGL*)(Sizei count, Uint32* samplers);
		using GetFragDataIndex = Int32 (DE_CALL_OPENGL*)(Uint32 program, const Char8* name);
		using GetQueryObjectI64V = void (DE_CALL_OPENGL*)(Uint32 id, Enum pname, Int64* params);
		using GetQueryObjectUI64V = void (DE_CALL_OPENGL*)(Uint32 id, Enum pname, Uint64* params);
		using GetSamplerParameterFV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Float32* params);
		using GetSamplerParameterIIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Int32* params);
		using GetSamplerParameterIUIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Uint32* params);
		using GetSamplerParameterIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Int32* params);
		using IsSampler = Boolean (DE_CALL_OPENGL*)(Uint32 sampler);
		using QueryCounter = void (DE_CALL_OPENGL*)(Uint32 id, Enum target);
		using SamplerParameterF = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Float32 param);
		using SamplerParameterFV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, const Float32* param);
		using SamplerParameterI = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, Int32 param);
		using SamplerParameterIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, const Int32* param);
		using SamplerParameterIIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, const Int32* param);
		using SamplerParameterIUIV = void (DE_CALL_OPENGL*)(Uint32 sampler, Enum pname, const Uint32* param);
		using VertexAttribDivisor = void (DE_CALL_OPENGL*)(Uint32 index, Uint32 divisor);

		using VertexAttribP1UI =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, Uint32 value);

		using VertexAttribP1UIV =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, const Uint32* value);

		using VertexAttribP2UI =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, Uint32 value);

		using VertexAttribP2UIV =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, const Uint32* value);

		using VertexAttribP3UI =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, Uint32 value);

		using VertexAttribP3UIV =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, const Uint32* value);

		using VertexAttribP4UI =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, Uint32 value);

		using VertexAttribP4UIV =
			void (DE_CALL_OPENGL*)(Uint32 index, Enum type, Boolean normalized, const Uint32* value);

		// Version 4.0

		using BeginQueryIndexed = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Uint32 id);
		using BindTransformFeedback = void (DE_CALL_OPENGL*)(Enum target, Uint32 id);
		using BlendEquationI = void (DE_CALL_OPENGL*)(Uint32 buf, Enum mode);
		using BlendEquationSeparateI = void (DE_CALL_OPENGL*)(Uint32 buf, Enum modeRGB, Enum modeAlpha);
		using BlendFuncI = void (DE_CALL_OPENGL*)(Uint32 buf, Enum src, Enum dst);

		using BlendFuncSeparateI =
			void (DE_CALL_OPENGL*)(Uint32 buf, Enum srcRGB, Enum dstRGB, Enum srcAlpha, Enum dstAlpha);

		using DeleteTransformFeedbacks = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* ids);
		using DrawArraysIndirect = void (DE_CALL_OPENGL*)(Enum mode, const Void* indirect);
		using DrawElementsIndirect = void (DE_CALL_OPENGL*)(Enum mode, Enum type, const Void* indirect);
		using DrawTransformFeedback = void (DE_CALL_OPENGL*)(Enum mode, Uint32 id);
		using DrawTransformFeedbackStream = void (DE_CALL_OPENGL*)(Enum mode, Uint32 id, Uint32 stream);
		using EndQueryIndexed = void (DE_CALL_OPENGL*)(Enum target, Uint32 index);
		using GenTransformFeedbacks = void (DE_CALL_OPENGL*)(Sizei n, Uint32* ids);

		using GetActiveSubroutineName =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, Uint32 index, Sizei bufsize,
				Sizei* length, Char8* name);

		using GetActiveSubroutineUniformIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, Uint32 index, Enum pname, Int32* values);

		using GetActiveSubroutineUniformName =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, Uint32 index, Sizei bufsize,
				Sizei* length, Char8* name);

		using GetProgramStageIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, Enum pname, Int32* values);

		using GetQueryIndexedIV =
			void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Enum pname, Int32* params);

		using GetSubroutineIndex =
			Uint32 (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, const Char8* name);

		using GetSubroutineUniformLocation =
			Int32 (DE_CALL_OPENGL*)(Uint32 program, Enum shadertype, const Char8* name);

		using GetUniformDV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float64* params);

		using GetUniformSubroutineUIV =
			void (DE_CALL_OPENGL*)(Enum shadertype, Int32 location, Uint32* params);

		using IsTransformFeedback = Boolean (DE_CALL_OPENGL*)(Uint32 id);
		using MinSampleShading = void (DE_CALL_OPENGL*)(Float32 value);
		using PatchParameterFV = void (DE_CALL_OPENGL*)(Enum pname, const Float32* values);
		using PatchParameterI = void (DE_CALL_OPENGL*)(Enum pname, Int32 value);
		using PauseTransformFeedback = void (DE_CALL_OPENGL*)();
		using ResumeTransformFeedback = void (DE_CALL_OPENGL*)();
		using Uniform1D = void (DE_CALL_OPENGL*)(Int32 location, Float64 x);
		using Uniform1DV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float64* value);
		using Uniform2D = void (DE_CALL_OPENGL*)(Int32 location, Float64 x, Float64 y);
		using Uniform2DV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float64* value);
		using Uniform3D = void (DE_CALL_OPENGL*)(Int32 location, Float64 x, Float64 y, Float64 z);
		using Uniform3DV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float64* value);
		using Uniform4D = void (DE_CALL_OPENGL*)(Int32 location, Float64 x, Float64 y, Float64 z, Float64 w);
		using Uniform4DV = void (DE_CALL_OPENGL*)(Int32 location, Sizei count, const Float64* value);

		using UniformMatrix2DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix2X3DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix2X4DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix3DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix3X2DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix3X4DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix4DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix4X2DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformMatrix4X3DV =
			void (DE_CALL_OPENGL*)(Int32 location, Sizei count, Boolean transpose, const Float64* value);

		using UniformSubroutineSUIV =
			void (DE_CALL_OPENGL*)(Enum shadertype, Sizei count, const Uint32* indices);

		// Version 4.1

		using ActiveShaderProgram = void (DE_CALL_OPENGL*)(Uint32 pipeline, Uint32 program);
		using BindProgramPipeline = void (DE_CALL_OPENGL*)(Uint32 pipeline);
		using ClearDepthF = void (DE_CALL_OPENGL*)(Float32 d);

		using CreateShaderProgramV =
			Uint32 (DE_CALL_OPENGL*)(Enum type, Sizei count, const Char8* const* strings);

		using DeleteProgramPipelines = void (DE_CALL_OPENGL*)(Sizei n, const Uint32* pipelines);
		using DepthRangeArrayV = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Float64* v);
		using DepthRangeF = void (DE_CALL_OPENGL*)(Float32 n, Float32 f);
		using DepthRangeIndexed = void (DE_CALL_OPENGL*)(Uint32 index, Float64 n, Float64 f);
		using GenProgramPipelines = void (DE_CALL_OPENGL*)(Sizei n, Uint32* pipelines);
		using GetDoubleI_V = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Float64* data);
		using GetFloatI_V = void (DE_CALL_OPENGL*)(Enum target, Uint32 index, Float32* data);

		using GetProgramBinary =
			void (DE_CALL_OPENGL*)(Uint32 program, Sizei bufSize, Sizei* length, Enum* binaryFormat,
				Void* binary);

		using GetProgramPipelineInfoLog =
			void (DE_CALL_OPENGL*)(Uint32 pipeline, Sizei bufSize, Sizei* length, Char8* infoLog);

		using GetProgramPipelineIV = void (DE_CALL_OPENGL*)(Uint32 pipeline, Enum pname, Int32* params);

		using GetShaderPrecisionFormat = void
			(DE_CALL_OPENGL*)(Enum shadertype, Enum precisiontype, Int32* range, Int32* precision);

		using GetVertexAttribLDV = void (DE_CALL_OPENGL*)(Uint32 index, Enum pname, Float64* params);
		using IsProgramPipeline = Boolean (DE_CALL_OPENGL*)(Uint32 pipeline);

		using ProgramBinary =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum binaryFormat, const Void* binary, Sizei length);

		using ProgramParameterI = void (DE_CALL_OPENGL*)(Uint32 program, Enum pname, Int32 value);
		using ProgramUniform1D = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float64 v0);

		using ProgramUniform1DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float64* value);

		using ProgramUniform1F = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float32 v0);

		using ProgramUniform1FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float32* value);

		using ProgramUniform1I = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Int32 v0);

		using ProgramUniform1IV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Int32* value);

		using ProgramUniform1UI = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Uint32 v0);

		using ProgramUniform1UIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Uint32* value);

		using ProgramUniform2D =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float64 v0, Float64 v1);

		using ProgramUniform2DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float64* value);

		using ProgramUniform2F =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float32 v0, Float32 v1);

		using ProgramUniform2FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float32* value);

		using ProgramUniform2I = void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Int32 v0, Int32 v1);

		using ProgramUniform2IV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Int32* value);

		using ProgramUniform2UI =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Uint32 v0, Uint32 v1);

		using ProgramUniform2UIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Uint32* value);

		using ProgramUniform3D =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float64 v0, Float64 v1, Float64 v2);

		using ProgramUniform3DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float64* value);

		using ProgramUniform3F =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float32 v0, Float32 v1, Float32 v2);

		using ProgramUniform3FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float32* value);

		using ProgramUniform3I =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Int32 v0, Int32 v1, Int32 v2);

		using ProgramUniform3IV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Int32* value);

		using ProgramUniform3UI =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Uint32 v0, Uint32 v1, Uint32 v2);

		using ProgramUniform3UIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Uint32* value);

		using ProgramUniform4D =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float64 v0, Float64 v1, Float64 v2,
				Float64 v3);

		using ProgramUniform4DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float64* value);

		using ProgramUniform4F =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Float32 v0, Float32 v1, Float32 v2,
				Float32 v3);

		using ProgramUniform4FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Float32* value);

		using ProgramUniform4I =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Int32 v0, Int32 v1, Int32 v2, Int32 v3);

		using ProgramUniform4IV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Int32* value);

		using ProgramUniform4UI =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Uint32 v0, Uint32 v1, Uint32 v2,
				Uint32 v3);

		using ProgramUniform4UIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, const Uint32* value);

		using ProgramUniformMatrix2DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix2FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix2X3DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix2X3FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix2X4DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix2X4FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix3DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix3FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix3X2DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix3X2FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix3X4DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix3X4FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix4DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix4FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix4X2DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix4X2FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ProgramUniformMatrix4X3DV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float64* value);

		using ProgramUniformMatrix4X3FV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei count, Boolean transpose,
				const Float32* value);

		using ReleaseShaderCompiler = void (DE_CALL_OPENGL*)();

		using ShaderBinary =
			void (DE_CALL_OPENGL*)(Sizei count, const Uint32* shaders, Enum binaryformat, const Void* binary,
				Sizei length);

		using ScissorArrayV = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Int32* v);

		using ScissorIndexed =
			void (DE_CALL_OPENGL*)(Uint32 index, Int32 left, Int32 bottom, Sizei width, Sizei height);

		using ScissorIndexedV = void (DE_CALL_OPENGL*)(Uint32 index, const Int32* v);
		using UseProgramStages = void (DE_CALL_OPENGL*)(Uint32 pipeline, Bitfield stages, Uint32 program);
		using ValidateProgramPipeline = void (DE_CALL_OPENGL*)(Uint32 pipeline);
		using VertexAttribL1D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x);
		using VertexAttribL1DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);
		using VertexAttribL2D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y);
		using VertexAttribL2DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);
		using VertexAttribL3D = void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y, Float64 z);
		using VertexAttribL3DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);

		using VertexAttribL4D =
			void (DE_CALL_OPENGL*)(Uint32 index, Float64 x, Float64 y, Float64 z, Float64 w);

		using VertexAttribL4DV = void (DE_CALL_OPENGL*)(Uint32 index, const Float64* v);

		using VertexAttribLPointer =
			void (DE_CALL_OPENGL*)(Uint32 index, Int32 size, Enum type, Sizei stride, const Void* pointer);

		using ViewportArrayV = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Float32* v);

		using ViewportIndexedF =
			void (DE_CALL_OPENGL*)(Uint32 index, Float32 x, Float32 y, Float32 w, Float32 h);

		using ViewportIndexedFV = void (DE_CALL_OPENGL*)(Uint32 index, const Float32* v);

		// Version 4.2

		using BindImageTexture =
			void (DE_CALL_OPENGL*)(Uint32 unit, Uint32 texture, Int32 level, Boolean layered, Int32 layer,
				Enum access, Enum format);

		using DrawArraysInstancedBaseInstance =
			void (DE_CALL_OPENGL*)(Enum mode, Int32 first, Sizei count, Sizei instancecount,
				Uint32 baseinstance);

		using DrawElementsInstancedBaseInstance =
			void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices,
				Sizei instancecount, Uint32 baseinstance);

		using DrawElementsInstancedBaseVertexBaseInstance =
			void (DE_CALL_OPENGL*)(Enum mode, Sizei count, Enum type, const Void* indices,
				Sizei instancecount, Int32 basevertex, Uint32 baseinstance);

		using DrawTransformFeedbackInstanced =
			void (DE_CALL_OPENGL*)(Enum mode, Uint32 id, Sizei instancecount);

		using DrawTransformFeedbackStreamInstanced =
			void (DE_CALL_OPENGL*)(Enum mode, Uint32 id, Uint32 stream, Sizei instancecount);

		using GetActiveAtomicCounterBufferIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 bufferIndex, Enum pname, Int32* params);

		using GetInternalformatIV =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Enum pname, Sizei bufSize,
				Int32* params);

		using MemoryBarrier = void (DE_CALL_OPENGL*)(Bitfield barriers);

		using TexStorage1D =
			void (DE_CALL_OPENGL*)(Enum target, Sizei levels, Enum internalformat, Sizei width);

		using TexStorage2D =
			void (DE_CALL_OPENGL*)(Enum target, Sizei levels, Enum internalformat, Sizei width, Sizei height);

		using TexStorage3D =
			void (DE_CALL_OPENGL*)(Enum target, Sizei levels, Enum internalformat, Sizei width, Sizei height,
				Sizei depth);

		// Version 4.3

		using DebugFunction =
			void (DE_CALL_OPENGL*)(Enum source, Enum type, Uint32 id, Enum severity, Sizei length,
				const Char8* message, const Void* userParam);

		using BindVertexBuffer =
			void (DE_CALL_OPENGL*)(Uint32 bindingindex, Uint32 buffer, Intptr offset, Sizei stride);

		using ClearBufferData =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Enum format, Enum type,
				const Void* data);

		using ClearBufferSubData =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Intptr offset, Sizeiptr size,
				Enum format, Enum type, const Void* data);

		using CopyImageSubData =
			void (DE_CALL_OPENGL*)(Uint32 srcName, Enum srcTarget, Int32 srcLevel, Int32 srcX, Int32 srcY,
				Int32 srcZ, Uint32 dstName, Enum dstTarget, Int32 dstLevel, Int32 dstX, Int32 dstY,
				Int32 dstZ, Sizei srcWidth, Sizei srcHeight, Sizei srcDepth);

		using DispatchCompute =
			void (DE_CALL_OPENGL*)(Uint32 num_groups_x, Uint32 num_groups_y, Uint32 num_groups_z);

		using DispatchComputeIndirect = void (DE_CALL_OPENGL*)(Intptr indirect);
		using DebugMessageCallback = void (DE_CALL_OPENGL*)(DebugFunction callback, const Void* userParam);

		using DebugMessageControl =
			void (DE_CALL_OPENGL*)(Enum source, Enum type, Enum severity, Sizei count, const Uint32* ids,
				Boolean enabled);

		using DebugMessageInsert =
			void (DE_CALL_OPENGL*)(Enum source, Enum type, Uint32 id, Enum severity, Sizei length,
				const Char8* buf);

		using FramebufferParameterI = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32 param);

		using GetDebugMessageLog =
			Uint32(DE_CALL_OPENGL*)(Uint32 count, Sizei bufSize, Enum* sources, Enum* types, Uint32* ids,
				Enum* severities, Sizei* lengths, Char8* messageLog);

		using GetFramebufferParameterIV = void (DE_CALL_OPENGL*)(Enum target, Enum pname, Int32* params);

		using GetInternalformatI64V =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Enum pname, Sizei bufSize,
				Int64* params);

		using GetObjectLabel =
			void (DE_CALL_OPENGL*)(Enum identifier, Uint32 name, Sizei bufSize, Sizei* length, Char8* label);

		using GetObjectPtrLabel =
			void (DE_CALL_OPENGL*)(const Void* ptr, Sizei bufSize, Sizei* length, Char8* label);

		using GetProgramInterfaceIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, Enum pname, Int32* params);

		using GetProgramResourceIndex =
			Uint32 (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, const Char8* name);

		using GetProgramResourceIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, Uint32 index, Sizei propCount,
				const Enum* props, Sizei bufSize, Sizei* length, Int32* params);

		using GetProgramResourceLocation =
			Int32 (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, const Char8* name);

		using GetProgramResourceLocationIndex =
			Int32 (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, const Char8* name);

		using GetProgramResourceName =
			void (DE_CALL_OPENGL*)(Uint32 program, Enum programInterface, Uint32 index, Sizei bufSize,
				Sizei* length, Char8* name);

		using InvalidateBufferData = void (DE_CALL_OPENGL*)(Uint32 buffer);
		using InvalidateBufferSubData = void (DE_CALL_OPENGL*)(Uint32 buffer, Intptr offset, Sizeiptr length);

		using InvalidateFramebuffer =
			void (DE_CALL_OPENGL*)(Enum target, Sizei numAttachments, const Enum* attachments);

		using InvalidateSubFramebuffer =
			void (DE_CALL_OPENGL*)(Enum target, Sizei numAttachments, const Enum* attachments, Int32 x,
				Int32 y, Sizei width, Sizei height);

		using InvalidateTexImage = void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level);

		using InvalidateTexSubImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth);

		using MultiDrawArraysIndirect =
			void (DE_CALL_OPENGL*)(Enum mode, const Void* indirect, Sizei drawcount, Sizei stride);

		using MultiDrawElementsIndirect =
			void (DE_CALL_OPENGL*)(Enum mode, Enum type, const Void* indirect, Sizei drawcount, Sizei stride);

		using ObjectLabel =
			void (DE_CALL_OPENGL*)(Enum identifier, Uint32 name, Sizei length, const Char8* label);

		using ObjectPtrLabel = void (DE_CALL_OPENGL*)(const Void* ptr, Sizei length, const Char8* label);
		using PopDebugGroup = void (DE_CALL_OPENGL*)();

		using PushDebugGroup =
			void (DE_CALL_OPENGL*)(Enum source, Uint32 id, Sizei length, const Char8* message);

		using ShaderStorageBlockBinding =
			void (DE_CALL_OPENGL*)(Uint32 program, Uint32 storageBlockIndex, Uint32 storageBlockBinding);

		using TexBufferRange =
			void (DE_CALL_OPENGL*)(Enum target, Enum internalformat, Uint32 buffer, Intptr offset,
				Sizeiptr size);

		using TexStorage2DMultisample =
			void (DE_CALL_OPENGL*)(Enum target, Sizei samples, Enum internalformat, Sizei width, Sizei height,
				Boolean fixedsamplelocations);

		using TexStorage3DMultisample =
			void (DE_CALL_OPENGL*)(Enum target, Sizei samples, Enum internalformat, Sizei width, Sizei height,
				Sizei depth, Boolean fixedsamplelocations);

		using TextureView =
			void (DE_CALL_OPENGL*)(Uint32 texture, Enum target, Uint32 origtexture, Enum internalformat,
				Uint32 minlevel, Uint32 numlevels, Uint32 minlayer, Uint32 numlayers);

		using VertexAttribBinding = void (DE_CALL_OPENGL*)(Uint32 attribindex, Uint32 bindingindex);

		using VertexAttribFormat =
			void (DE_CALL_OPENGL*)(Uint32 attribindex, Int32 size, Enum type, Boolean normalized,
				Uint32 relativeoffset);

		using VertexAttribIFormat =
			void (DE_CALL_OPENGL*)(Uint32 attribindex, Int32 size, Enum type, Uint32 relativeoffset);

		using VertexAttribLFormat =
			void (DE_CALL_OPENGL*)(Uint32 attribindex, Int32 size, Enum type, Uint32 relativeoffset);

		using VertexBindingDivisor = void (DE_CALL_OPENGL*)(Uint32 bindingindex, Uint32 divisor);

		// Version 4.4

		using BindBuffersBase =
			void (DE_CALL_OPENGL*)(Enum target, Uint32 first, Sizei count, const Uint32* buffers);

		using BindBuffersRange =
			void (DE_CALL_OPENGL*)(Enum target, Uint32 first, Sizei count, const Uint32* buffers,
				const Intptr* offsets, const Sizeiptr* sizes);

		using BindImageTextures = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Uint32* textures);
		using BindSamplers = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Uint32* samplers);
		using BindTextures = void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Uint32* textures);

		using BindVertexBuffers =
			void (DE_CALL_OPENGL*)(Uint32 first, Sizei count, const Uint32* buffers, const Intptr* offsets,
				const Sizei* strides);

		using BufferStorage =
			void (DE_CALL_OPENGL*)(Enum target, Sizeiptr size, const Void* data, Bitfield flags);

		using ClearTexImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Enum format, Enum type, const Void* data);

		using ClearTexSubImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Enum type, const Void* data);

		// Version 4.5

		using BindTextureUnit = void (DE_CALL_OPENGL*)(Uint32 unit, Uint32 texture);

		using BlitNamedFramebuffer =
			void (DE_CALL_OPENGL*)(Uint32 readFramebuffer, Uint32 drawFramebuffer, Int32 srcX0, Int32 srcY0,
				Int32 srcX1, Int32 srcY1, Int32 dstX0, Int32 dstY0, Int32 dstX1, Int32 dstY1, Bitfield mask,
				Enum filter);

		using CheckNamedFramebufferStatus = Enum (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum target);

		using ClearNamedBufferData =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Enum internalformat, Enum format, Enum type,
				const Void* data);

		using ClearNamedBufferSubData =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Enum internalformat, Intptr offset, Sizeiptr size,
				Enum format, Enum type, const Void* data);

		using ClearNamedFramebufferFI =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum buffer, const Float32 depth, Int32 stencil);

		using ClearNamedFramebufferFV =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum buffer, Int32 drawbuffer, const Float32* value);

		using ClearNamedFramebufferIV =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum buffer, Int32 drawbuffer, const Int32* value);

		using ClearNamedFramebufferUIV =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum buffer, Int32 drawbuffer, const Uint32* value);

		using ClipControl = void (DE_CALL_OPENGL*)(Enum origin, Enum depth);

		using CompressedTextureSubImage1D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Sizei width, Enum format,
				Sizei imageSize, const Void* data);

		using CompressedTextureSubImage2D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Sizei width,
				Sizei height, Enum format, Sizei imageSize, const Void* data);

		using CompressedTextureSubImage3D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Sizei imageSize, const Void* data);

		using CopyNamedBufferSubData =
			void (DE_CALL_OPENGL*)(Uint32 readBuffer, Uint32 writeBuffer, Intptr readOffset,
				Intptr writeOffset, Sizeiptr size);

		using CopyTextureSubImage1D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 x, Int32 y, Sizei width);

		using CopyTextureSubImage2D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 x,
				Int32 y, Sizei width, Sizei height);

		using CopyTextureSubImage3D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Int32 x, Int32 y, Sizei width, Sizei height);

		using CreateBuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* buffers);
		using CreateFramebuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* framebuffers);
		using CreateProgramPipelines = void (DE_CALL_OPENGL*)(Sizei n, Uint32* pipelines);
		using CreateQueries = void (DE_CALL_OPENGL*)(Enum target, Sizei n, Uint32* ids);
		using CreateRenderbuffers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* renderbuffers);
		using CreateSamplers = void (DE_CALL_OPENGL*)(Sizei n, Uint32* samplers);
		using CreateTextures = void (DE_CALL_OPENGL*)(Enum target, Sizei n, Uint32* textures);
		using CreateTransformFeedbacks = void (DE_CALL_OPENGL*)(Sizei n, Uint32* ids);
		using CreateVertexArrays = void (DE_CALL_OPENGL*)(Sizei n, Uint32* arrays);
		using DisableVertexArrayAttrib = void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 index);
		using EnableVertexArrayAttrib = void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 index);

		using FlushMappedNamedBufferRange =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Intptr offset, Sizeiptr length);

		using GenerateTextureMipmap = void (DE_CALL_OPENGL*)(Uint32 texture);

		using GetCompressedTextureImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Sizei bufSize, Void* pixels);

		using GetCompressedTextureSubImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Sizei bufSize, Void* pixels);

		using GetGraphicsResetStatus = Enum (DE_CALL_OPENGL*)();
		using GetNamedBufferParameterI64V = void (DE_CALL_OPENGL*)(Uint32 buffer, Enum pname, Int64* params);
		using GetNamedBufferParameterIV = void (DE_CALL_OPENGL*)(Uint32 buffer, Enum pname, Int32* params);
		using GetNamedBufferPointerV = void (DE_CALL_OPENGL*)(Uint32 buffer, Enum pname, Void** params);

		using GetNamedBufferSubData =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Intptr offset, Sizeiptr size, Void* data);

		using GetNamedFramebufferAttachmentParameterIV =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum attachment, Enum pname, Int32* params);

		using GetNamedFramebufferParameterIV =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum pname, Int32* param);

		using GetNamedRenderbufferParameterIV =
			void (DE_CALL_OPENGL*)(Uint32 renderbuffer, Enum pname, Int32* params);

		using GetnCompressedTexImage =
			void (DE_CALL_OPENGL*)(Enum target, Int32 lod, Sizei bufSize, Void* pixels);

		using GetnTexImage =
			void (DE_CALL_OPENGL*)(Enum target, Int32 level, Enum format, Enum type, Sizei bufSize,
				Void* pixels);

		using GetnUniformDV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei bufSize, Float64* params);

		using GetnUniformFV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei bufSize, Float32* params);

		using GetnUniformIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei bufSize, Int32* params);

		using GetnUniformUIV =
			void (DE_CALL_OPENGL*)(Uint32 program, Int32 location, Sizei bufSize, Uint32* params);

		using GetQueryBufferObjectI64V =
			void (DE_CALL_OPENGL*)(Uint32 id, Uint32 buffer, Enum pname, Intptr offset);

		using GetQueryBufferObjectIV =
			void (DE_CALL_OPENGL*)(Uint32 id, Uint32 buffer, Enum pname, Intptr offset);

		using GetQueryBufferObjectUI64V =
			void (DE_CALL_OPENGL*)(Uint32 id, Uint32 buffer, Enum pname, Intptr offset);

		using GetQueryBufferObjectUIV =
			void (DE_CALL_OPENGL*)(Uint32 id, Uint32 buffer, Enum pname, Intptr offset);

		using GetTextureImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Enum format, Enum type, Sizei bufSize,
				Void* pixels);

		using GetTextureLevelParameterFV =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Enum pname, Float32* params);

		using GetTextureLevelParameterIV =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Enum pname, Int32* params);

		using GetTextureParameterFV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Float32* params);
		using GetTextureParameterIIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Int32* params);
		using GetTextureParameterIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Int32* params);
		using GetTextureParameterIUIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Uint32* params);

		using GetTextureSubImage =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Enum type, Sizei bufSize, Void* pixels);

		using GetTransformFeedbackI64_V =
			void (DE_CALL_OPENGL*)(Uint32 xfb, Enum pname, Uint32 index, Int64* param);

		using GetTransformFeedbackIV = void (DE_CALL_OPENGL*)(Uint32 xfb, Enum pname, Int32* param);

		using GetTransformFeedbackI_V =
			void (DE_CALL_OPENGL*)(Uint32 xfb, Enum pname, Uint32 index, Int32* param);

		using GetVertexArrayIndexed64IV =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 index, Enum pname, Int64* param);

		using GetVertexArrayIndexedIV =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 index, Enum pname, Int32* param);

		using GetVertexArrayIV = void (DE_CALL_OPENGL*)(Uint32 vaobj, Enum pname, Int32* param);

		using InvalidateNamedFramebufferData =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Sizei numAttachments, const Enum* attachments);

		using InvalidateNamedFramebufferSubData =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Sizei numAttachments, const Enum* attachments, Int32 x,
				Int32 y, Sizei width, Sizei height);

		using MapNamedBuffer = Void* (DE_CALL_OPENGL*)(Uint32 buffer, Enum access);

		using MapNamedBufferRange =
			Void* (DE_CALL_OPENGL*)(Uint32 buffer, Intptr offset, Sizeiptr length, Bitfield access);

		using MemoryBarrierByRegion = void (DE_CALL_OPENGL*)(Bitfield barriers);

		using NamedBufferData =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Sizeiptr size, const Void* data, Enum usage);

		using NamedBufferStorage =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Sizeiptr size, const Void* data, Bitfield flags);

		using NamedBufferSubData =
			void (DE_CALL_OPENGL*)(Uint32 buffer, Intptr offset, Sizeiptr size, const Void* data);

		using NamedFramebufferDrawBuffer = void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum buf);

		using NamedFramebufferDrawBuffers =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Sizei n, const Enum* bufs);

		using NamedFramebufferParameterI =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum pname, Int32 param);

		using NamedFramebufferReadBuffer = void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum src);

		using NamedFramebufferRenderbuffer =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum attachment, Enum renderbuffertarget,
				Uint32 renderbuffer);

		using NamedFramebufferTexture =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum attachment, Uint32 texture, Int32 level);

		using NamedFramebufferTextureLayer =
			void (DE_CALL_OPENGL*)(Uint32 framebuffer, Enum attachment, Uint32 texture, Int32 level,
				Int32 layer);

		using NamedRenderbufferStorage =
			void (DE_CALL_OPENGL*)(Uint32 renderbuffer, Enum internalformat, Sizei width, Sizei height);

		using NamedRenderbufferStorageMultisample =
			void (DE_CALL_OPENGL*)(Uint32 renderbuffer, Sizei samples, Enum internalformat, Sizei width,
				Sizei height);

		using ReadnPixels =
			void (DE_CALL_OPENGL*)(Int32 x, Int32 y, Sizei width, Sizei height, Enum format, Enum type,
				Sizei bufSize, Void* data);

		using TransformFeedbackBufferBase = void (DE_CALL_OPENGL*)(Uint32 xfb, Uint32 index, Uint32 buffer);

		using TransformFeedbackBufferRange =
			void (DE_CALL_OPENGL*)(Uint32 xfb, Uint32 index, Uint32 buffer, Intptr offset, Sizeiptr size);

		using TextureBarrier = void (DE_CALL_OPENGL*)();
		using TextureBuffer = void (DE_CALL_OPENGL*)(Uint32 texture, Enum internalformat, Uint32 buffer);

		using TextureBufferRange =
			void (DE_CALL_OPENGL*)(Uint32 texture, Enum internalformat, Uint32 buffer, Intptr offset,
				Sizeiptr size);

		using TextureParameterF = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Float32 param);
		using TextureParameterFV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, const Float32* param);
		using TextureParameterI = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, Int32 param);
		using TextureParameterIIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, const Int32* params);
		using TextureParameterIUIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, const Uint32* params);
		using TextureParameterIV = void (DE_CALL_OPENGL*)(Uint32 texture, Enum pname, const Int32* param);

		using TextureStorage1D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Sizei levels, Enum internalformat, Sizei width);

		using TextureStorage2D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Sizei levels, Enum internalformat, Sizei width,
				Sizei height);

		using TextureStorage2DMultisample =
			void (DE_CALL_OPENGL*)(Uint32 texture, Sizei samples, Enum internalformat, Sizei width,
				Sizei height, Boolean fixedsamplelocations);

		using TextureStorage3D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Sizei levels, Enum internalformat, Sizei width,
				Sizei height, Sizei depth);

		using TextureStorage3DMultisample =
			void (DE_CALL_OPENGL*)(Uint32 texture, Sizei samples, Enum internalformat, Sizei width,
				Sizei height, Sizei depth, Boolean fixedsamplelocations);

		using TextureSubImage1D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Sizei width, Enum format,
				Enum type, const Void* pixels);

		using TextureSubImage2D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Sizei width,
				Sizei height, Enum format, Enum type, const Void* pixels);

		using TextureSubImage3D =
			void (DE_CALL_OPENGL*)(Uint32 texture, Int32 level, Int32 xoffset, Int32 yoffset, Int32 zoffset,
				Sizei width, Sizei height, Sizei depth, Enum format, Enum type, const Void* pixels);

		using UnmapNamedBuffer = Boolean (DE_CALL_OPENGL*)(Uint32 buffer);

		using VertexArrayAttribBinding =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 attribindex, Uint32 bindingindex);

		using VertexArrayAttribFormat =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 attribindex, Int32 size, Enum type,
				Boolean normalized, Uint32 relativeoffset);

		using VertexArrayAttribIFormat =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 attribindex, Int32 size, Enum type,
				Uint32 relativeoffset);

		using VertexArrayAttribLFormat =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 attribindex, Int32 size, Enum type,
				Uint32 relativeoffset);

		using VertexArrayBindingDivisor =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 bindingindex, Uint32 divisor);

		using VertexArrayElementBuffer = void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 buffer);

		using VertexArrayVertexBuffer =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 bindingindex, Uint32 buffer, Intptr offset,
				Sizei stride);

		using VertexArrayVertexBuffers =
			void (DE_CALL_OPENGL*)(Uint32 vaobj, Uint32 first, Sizei count, const Uint32* buffers,
				const Intptr* offsets, const Sizei* strides);

		// Version 1.0

		static BlendFunc blendFunc;
		static Clear clear;
		static ClearColor clearColor;
		static ClearDepth clearDepth;
		static ClearStencil clearStencil;
		static ColorMask colorMask;
		static CullFace cullFace;
		static DepthFunc depthFunc;
		static DepthMask depthMask;
		static DepthRange depthRange;
		static Disable disable;
		static DrawBuffer drawBuffer;
		static Enable enable;
		static Finish finish;
		static Flush flush;
		static FrontFace frontFace;
		static GetBooleanV getBooleanv;
		static GetDoubleV getDoublev;
		static GetError getError;
		static GetFloatV getFloatv;
		static GetIntegerV getIntegerv;
		static GetString getString;
		static GetTexImage getTexImage;
		static GetTexLevelParameterFV getTexLevelParameterfv;
		static GetTexLevelParameterIV getTexLevelParameteriv;
		static GetTexParameterFV getTexParameterfv;
		static GetTexParameterIV getTexParameteriv;
		static Hint hint;
		static IsEnabled isEnabled;
		static LineWidth lineWidth;
		static LogicOp logicOp;
		static PixelStoreF pixelStoref;
		static PixelStoreI pixelStorei;
		static PointSize pointSize;
		static PolygonMode polygonMode;
		static ReadBuffer readBuffer;
		static ReadPixels readPixels;
		static Scissor scissor;
		static StencilFunc stencilFunc;
		static StencilMask stencilMask;
		static StencilOp stencilOp;
		static TexImage1D texImage1D;
		static TexImage2D texImage2D;
		static TexParameterF texParameterf;
		static TexParameterFV texParameterfv;
		static TexParameterI texParameteri;
		static TexParameterIV texParameteriv;
		static Viewport viewport;

		// Version 1.1

		static const Uint32 FALSE					= 0;
		static const Uint32 TRUE					= 1;
		static const Uint32 NONE					= 0;
		static const Uint32 ZERO					= 0;
		static const Uint32 ONE						= 1;
		static const Uint32 POINTS					= 0x0000;
		static const Uint32 LINES					= 0x0001;
		static const Uint32 LINE_LOOP				= 0x0002;
		static const Uint32 LINE_STRIP				= 0x0003;
		static const Uint32 TRIANGLES				= 0x0004;
		static const Uint32 TRIANGLE_STRIP			= 0x0005;
		static const Uint32 TRIANGLE_FAN			= 0x0006;
		static const Uint32 QUADS					= 0x0007;
		static const Uint32 DEPTH_BUFFER_BIT		= 0x0100;
		static const Uint32 STENCIL_BUFFER_BIT		= 0x0400;
		static const Uint32 COLOR_BUFFER_BIT		= 0x4000;
		static const Uint32 NEVER					= 0x0200;
		static const Uint32 LESS					= 0x0201;
		static const Uint32 EQUAL					= 0x0202;
		static const Uint32 LEQUAL					= 0x0203;
		static const Uint32 GREATER					= 0x0204;
		static const Uint32 NOTEQUAL				= 0x0205;
		static const Uint32 GEQUAL					= 0x0206;
		static const Uint32 ALWAYS					= 0x0207;
		static const Uint32 SRC_COLOR				= 0x0300;
		static const Uint32 ONE_MINUS_SRC_COLOR		= 0x0301;
		static const Uint32 SRC_ALPHA				= 0x0302;
		static const Uint32 ONE_MINUS_SRC_ALPHA		= 0x0303;
		static const Uint32 DST_ALPHA				= 0x0304;
		static const Uint32 ONE_MINUS_DST_ALPHA		= 0x0305;
		static const Uint32 DST_COLOR				= 0x0306;
		static const Uint32 ONE_MINUS_DST_COLOR		= 0x0307;
		static const Uint32 SRC_ALPHA_SATURATE		= 0x0308;
		static const Uint32 FRONT_LEFT				= 0x0400;
		static const Uint32 FRONT_RIGHT				= 0x0401;
		static const Uint32 BACK_LEFT				= 0x0402;
		static const Uint32 BACK_RIGHT				= 0x0403;
		static const Uint32 FRONT					= 0x0404;
		static const Uint32 BACK					= 0x0405;
		static const Uint32 LEFT					= 0x0406;
		static const Uint32 RIGHT					= 0x0407;
		static const Uint32 FRONT_AND_BACK			= 0x0408;
		static const Uint32 NO_ERROR				= 0x0000;
		static const Uint32 INVALID_ENUM			= 0x0500;
		static const Uint32 INVALID_VALUE			= 0x0501;
		static const Uint32 INVALID_OPERATION		= 0x0502;
		static const Uint32 STACK_OVERFLOW			= 0x0503;
		static const Uint32 STACK_UNDERFLOW			= 0x0504;
		static const Uint32 OUT_OF_MEMORY			= 0x0505;
		static const Uint32 CW						= 0x0900;
		static const Uint32 CCW						= 0x0901;
		static const Uint32 POINT_SIZE				= 0x0B11;
		static const Uint32 POINT_SIZE_RANGE		= 0x0B12;
		static const Uint32 POINT_SIZE_GRANULARITY	= 0x0B13;
		static const Uint32 LINE_SMOOTH				= 0x0B20;
		static const Uint32 LINE_WIDTH				= 0x0B21;
		static const Uint32 LINE_WIDTH_RANGE		= 0x0B22;
		static const Uint32 LINE_WIDTH_GRANULARITY	= 0x0B23;
		static const Uint32 POLYGON_MODE			= 0x0B40;
		static const Uint32 POLYGON_SMOOTH			= 0x0B41;
		static const Uint32 CULL_FACE				= 0x0B44;
		static const Uint32 CULL_FACE_MODE			= 0x0B45;
		static const Uint32 FRONT_FACE				= 0x0B46;
		static const Uint32 DEPTH_RANGE				= 0x0B70;
		static const Uint32 DEPTH_TEST				= 0x0B71;
		static const Uint32 DEPTH_WRITEMASK			= 0x0B72;
		static const Uint32 DEPTH_CLEAR_VALUE		= 0x0B73;
		static const Uint32 DEPTH_FUNC				= 0x0B74;
		static const Uint32 STENCIL_TEST			= 0x0B90;
		static const Uint32 STENCIL_CLEAR_VALUE		= 0x0B91;
		static const Uint32 STENCIL_FUNC			= 0x0B92;
		static const Uint32 STENCIL_VALUE_MASK		= 0x0B93;
		static const Uint32 STENCIL_FAIL			= 0x0B94;
		static const Uint32 STENCIL_PASS_DEPTH_FAIL = 0x0B95;
		static const Uint32 STENCIL_PASS_DEPTH_PASS = 0x0B96;
		static const Uint32 STENCIL_REF				= 0x0B97;
		static const Uint32 STENCIL_WRITEMASK		= 0x0B98;
		static const Uint32 VIEWPORT				= 0x0BA2;
		static const Uint32 DITHER					= 0x0BD0;
		static const Uint32 BLEND_DST				= 0x0BE0;
		static const Uint32 BLEND_SRC				= 0x0BE1;
		static const Uint32 BLEND					= 0x0BE2;
		static const Uint32 LOGIC_OP_MODE			= 0x0BF0;
		static const Uint32 COLOR_LOGIC_OP			= 0x0BF2;
		static const Uint32 DRAW_BUFFER				= 0x0C01;
		static const Uint32 READ_BUFFER				= 0x0C02;
		static const Uint32 SCISSOR_BOX				= 0x0C10;
		static const Uint32 SCISSOR_TEST			= 0x0C11;
		static const Uint32 COLOR_CLEAR_VALUE		= 0x0C22;
		static const Uint32 COLOR_WRITEMASK			= 0x0C23;
		static const Uint32 DOUBLEBUFFER			= 0x0C32;
		static const Uint32 STEREO					= 0x0C33;
		static const Uint32 LINE_SMOOTH_HINT		= 0x0C52;
		static const Uint32 POLYGON_SMOOTH_HINT		= 0x0C53;
		static const Uint32 UNPACK_SWAP_BYTES		= 0x0CF0;
		static const Uint32 UNPACK_LSB_FIRST		= 0x0CF1;
		static const Uint32 UNPACK_ROW_LENGTH		= 0x0CF2;
		static const Uint32 UNPACK_SKIP_ROWS		= 0x0CF3;
		static const Uint32 UNPACK_SKIP_PIXELS		= 0x0CF4;
		static const Uint32 UNPACK_ALIGNMENT		= 0x0CF5;
		static const Uint32 PACK_SWAP_BYTES			= 0x0D00;
		static const Uint32 PACK_LSB_FIRST			= 0x0D01;
		static const Uint32 PACK_ROW_LENGTH			= 0x0D02;
		static const Uint32 PACK_SKIP_ROWS			= 0x0D03;
		static const Uint32 PACK_SKIP_PIXELS		= 0x0D04;
		static const Uint32 PACK_ALIGNMENT			= 0x0D05;
		static const Uint32 MAX_TEXTURE_SIZE		= 0x0D33;
		static const Uint32 MAX_VIEWPORT_DIMS		= 0x0D3A;
		static const Uint32 SUBPIXEL_BITS			= 0x0D50;
		static const Uint32 TEXTURE_1D				= 0x0DE0;
		static const Uint32 TEXTURE_2D				= 0x0DE1;
		static const Uint32 TEXTURE_WIDTH			= 0x1000;
		static const Uint32 TEXTURE_HEIGHT			= 0x1001;
		static const Uint32 TEXTURE_INTERNAL_FORMAT = 0x1003;
		static const Uint32 TEXTURE_BORDER_COLOR	= 0x1004;
		static const Uint32 DONT_CARE				= 0x1100;
		static const Uint32 FASTEST					= 0x1101;
		static const Uint32 NICEST					= 0x1102;
		static const Uint32 BYTE					= 0x1400;
		static const Uint32 UNSIGNED_BYTE			= 0x1401;
		static const Uint32 SHORT					= 0x1402;
		static const Uint32 UNSIGNED_SHORT			= 0x1403;
		static const Uint32 INT						= 0x1404;
		static const Uint32 UNSIGNED_INT			= 0x1405;
		static const Uint32 FLOAT					= 0x1406;
		static const Uint32 DOUBLE					= 0x140A;
		static const Uint32 CLEAR					= 0x1500;
		static const Uint32 AND						= 0x1501;
		static const Uint32 AND_REVERSE				= 0x1502;
		static const Uint32 COPY					= 0x1503;
		static const Uint32 AND_INVERTED			= 0x1504;
		static const Uint32 NOOP					= 0x1505;
		static const Uint32 XOR						= 0x1506;
		static const Uint32 OR						= 0x1507;
		static const Uint32 NOR						= 0x1508;
		static const Uint32 EQUIV					= 0x1509;
		static const Uint32 INVERT					= 0x150A;
		static const Uint32 OR_REVERSE				= 0x150B;
		static const Uint32 COPY_INVERTED			= 0x150C;
		static const Uint32 OR_INVERTED				= 0x150D;
		static const Uint32 NAND					= 0x150E;
		static const Uint32 SET						= 0x150F;
		static const Uint32 TEXTURE					= 0x1702;
		static const Uint32 COLOR					= 0x1800;
		static const Uint32 DEPTH					= 0x1801;
		static const Uint32 STENCIL					= 0x1802;
		static const Uint32 STENCIL_INDEX			= 0x1901;
		static const Uint32 DEPTH_COMPONENT			= 0x1902;
		static const Uint32 RED						= 0x1903;
		static const Uint32 GREEN					= 0x1904;
		static const Uint32 BLUE					= 0x1905;
		static const Uint32 ALPHA					= 0x1906;
		static const Uint32 RGB						= 0x1907;
		static const Uint32 RGBA					= 0x1908;
		static const Uint32 POINT					= 0x1B00;
		static const Uint32 LINE					= 0x1B01;
		static const Uint32 FILL					= 0x1B02;
		static const Uint32 KEEP					= 0x1E00;
		static const Uint32 REPLACE					= 0x1E01;
		static const Uint32 INCR					= 0x1E02;
		static const Uint32 DECR					= 0x1E03;
		static const Uint32 VENDOR					= 0x1F00;
		static const Uint32 RENDERER				= 0x1F01;
		static const Uint32 VERSION					= 0x1F02;
		static const Uint32 EXTENSIONS				= 0x1F03;
		static const Uint32 NEAREST					= 0x2600;
		static const Uint32 LINEAR					= 0x2601;
		static const Uint32 NEAREST_MIPMAP_NEAREST	= 0x2700;
		static const Uint32 LINEAR_MIPMAP_NEAREST	= 0x2701;
		static const Uint32 NEAREST_MIPMAP_LINEAR	= 0x2702;
		static const Uint32 LINEAR_MIPMAP_LINEAR	= 0x2703;
		static const Uint32 TEXTURE_MAG_FILTER		= 0x2800;
		static const Uint32 TEXTURE_MIN_FILTER		= 0x2801;
		static const Uint32 TEXTURE_WRAP_S			= 0x2802;
		static const Uint32 TEXTURE_WRAP_T			= 0x2803;
		static const Uint32 REPEAT					= 0x2901;
		static const Uint32 POLYGON_OFFSET_UNITS	= 0x2A00;
		static const Uint32 POLYGON_OFFSET_POINT	= 0x2A01;
		static const Uint32 POLYGON_OFFSET_LINE		= 0x2A02;
		static const Uint32 POLYGON_OFFSET_FILL		= 0x8037;
		static const Uint32 POLYGON_OFFSET_FACTOR	= 0x8038;
		static const Uint32 R3_G3_B2				= 0x2A10;
		static const Uint32 RGB4					= 0x804F;
		static const Uint32 RGB5					= 0x8050;
		static const Uint32 RGB8					= 0x8051;
		static const Uint32 RGB10					= 0x8052;
		static const Uint32 RGB12					= 0x8053;
		static const Uint32 RGB16					= 0x8054;
		static const Uint32 RGBA2					= 0x8055;
		static const Uint32 RGBA4					= 0x8056;
		static const Uint32 RGB5_A1					= 0x8057;
		static const Uint32 RGBA8					= 0x8058;
		static const Uint32 RGB10_A2				= 0x8059;
		static const Uint32 RGBA12					= 0x805A;
		static const Uint32 RGBA16					= 0x805B;
		static const Uint32 TEXTURE_RED_SIZE		= 0x805C;
		static const Uint32 TEXTURE_GREEN_SIZE		= 0x805D;
		static const Uint32 TEXTURE_BLUE_SIZE		= 0x805E;
		static const Uint32 TEXTURE_ALPHA_SIZE		= 0x805F;
		static const Uint32 PROXY_TEXTURE_1D		= 0x8063;
		static const Uint32 PROXY_TEXTURE_2D		= 0x8064;
		static const Uint32 TEXTURE_BINDING_1D		= 0x8068;
		static const Uint32 TEXTURE_BINDING_2D		= 0x8069;
		static const Uint32 VERTEX_ARRAY			= 0x8074;

		static BindTexture bindTexture;
		static CopyTexImage1D copyTexImage1D;
		static CopyTexImage2D copyTexImage2D;
		static CopyTexSubImage1D copyTexSubImage1D;
		static CopyTexSubImage2D copyTexSubImage2D;
		static DeleteTextures deleteTextures;
		static DrawArrays drawArrays;
		static DrawElements drawElements;
		static GenTextures genTextures;
		static GetPointerV getPointerv;
		static IsTexture isTexture;
		static PolygonOffset polygonOffset;
		static TexSubImage1D texSubImage1D;
		static TexSubImage2D texSubImage2D;

		// Version 1.2

		static const Uint32 SMOOTH_POINT_SIZE_RANGE		  = 0x0B12;
		static const Uint32 SMOOTH_POINT_SIZE_GRANULARITY = 0x0B13;
		static const Uint32 SMOOTH_LINE_WIDTH_RANGE		  = 0x0B22;
		static const Uint32 SMOOTH_LINE_WIDTH_GRANULARITY = 0x0B23;
		static const Uint32 UNSIGNED_BYTE_3_3_2			  = 0x8032;
		static const Uint32 UNSIGNED_SHORT_4_4_4_4		  = 0x8033;
		static const Uint32 UNSIGNED_SHORT_5_5_5_1		  = 0x8034;
		static const Uint32 UNSIGNED_INT_8_8_8_8		  = 0x8035;
		static const Uint32 UNSIGNED_INT_10_10_10_2		  = 0x8036;
		static const Uint32 TEXTURE_BINDING_3D			  = 0x806A;
		static const Uint32 PACK_SKIP_IMAGES			  = 0x806B;
		static const Uint32 PACK_IMAGE_HEIGHT			  = 0x806C;
		static const Uint32 UNPACK_SKIP_IMAGES			  = 0x806D;
		static const Uint32 UNPACK_IMAGE_HEIGHT			  = 0x806E;
		static const Uint32 TEXTURE_3D					  = 0x806F;
		static const Uint32 PROXY_TEXTURE_3D			  = 0x8070;
		static const Uint32 TEXTURE_DEPTH				  = 0x8071;
		static const Uint32 TEXTURE_WRAP_R				  = 0x8072;
		static const Uint32 MAX_3D_TEXTURE_SIZE			  = 0x8073;
		static const Uint32 BGR							  = 0x80E0;
		static const Uint32 BGRA						  = 0x80E1;
		static const Uint32 MAX_ELEMENTS_VERTICES		  = 0x80E8;
		static const Uint32 MAX_ELEMENTS_INDICES		  = 0x80E9;
		static const Uint32 CLAMP_TO_EDGE				  = 0x812F;
		static const Uint32 TEXTURE_MIN_LOD				  = 0x813A;
		static const Uint32 TEXTURE_MAX_LOD				  = 0x813B;
		static const Uint32 TEXTURE_BASE_LEVEL			  = 0x813C;
		static const Uint32 TEXTURE_MAX_LEVEL			  = 0x813D;
		static const Uint32 UNSIGNED_BYTE_2_3_3_REV		  = 0x8362;
		static const Uint32 UNSIGNED_SHORT_5_6_5		  = 0x8363;
		static const Uint32 UNSIGNED_SHORT_5_6_5_REV	  = 0x8364;
		static const Uint32 UNSIGNED_SHORT_4_4_4_4_REV	  = 0x8365;
		static const Uint32 UNSIGNED_SHORT_1_5_5_5_REV	  = 0x8366;
		static const Uint32 UNSIGNED_INT_8_8_8_8_REV	  = 0x8367;
		static const Uint32 UNSIGNED_INT_2_10_10_10_REV	  = 0x8368;
		static const Uint32 ALIASED_LINE_WIDTH_RANGE	  = 0x846E;

		static CopyTexSubImage3D copyTexSubImage3D;
		static DrawRangeElements drawRangeElements;
		static TexImage3D texImage3D;
		static TexSubImage3D texSubImage3D;

		// Version 1.3

		static const Uint32 MULTISAMPLE					   = 0x809D;
		static const Uint32 SAMPLE_ALPHA_TO_COVERAGE	   = 0x809E;
		static const Uint32 SAMPLE_ALPHA_TO_ONE			   = 0x809F;
		static const Uint32 SAMPLE_COVERAGE				   = 0x80A0;
		static const Uint32 SAMPLE_BUFFERS				   = 0x80A8;
		static const Uint32 SAMPLES						   = 0x80A9;
		static const Uint32 SAMPLE_COVERAGE_VALUE		   = 0x80AA;
		static const Uint32 SAMPLE_COVERAGE_INVERT		   = 0x80AB;
		static const Uint32 CLAMP_TO_BORDER				   = 0x812D;
		static const Uint32 TEXTURE0					   = 0x84C0;
		static const Uint32 TEXTURE1					   = 0x84C1;
		static const Uint32 TEXTURE2					   = 0x84C2;
		static const Uint32 TEXTURE3					   = 0x84C3;
		static const Uint32 TEXTURE4					   = 0x84C4;
		static const Uint32 TEXTURE5					   = 0x84C5;
		static const Uint32 TEXTURE6					   = 0x84C6;
		static const Uint32 TEXTURE7					   = 0x84C7;
		static const Uint32 TEXTURE8					   = 0x84C8;
		static const Uint32 TEXTURE9					   = 0x84C9;
		static const Uint32 TEXTURE10					   = 0x84CA;
		static const Uint32 TEXTURE11					   = 0x84CB;
		static const Uint32 TEXTURE12					   = 0x84CC;
		static const Uint32 TEXTURE13					   = 0x84CD;
		static const Uint32 TEXTURE14					   = 0x84CE;
		static const Uint32 TEXTURE15					   = 0x84CF;
		static const Uint32 TEXTURE16					   = 0x84D0;
		static const Uint32 TEXTURE17					   = 0x84D1;
		static const Uint32 TEXTURE18					   = 0x84D2;
		static const Uint32 TEXTURE19					   = 0x84D3;
		static const Uint32 TEXTURE20					   = 0x84D4;
		static const Uint32 TEXTURE21					   = 0x84D5;
		static const Uint32 TEXTURE22					   = 0x84D6;
		static const Uint32 TEXTURE23					   = 0x84D7;
		static const Uint32 TEXTURE24					   = 0x84D8;
		static const Uint32 TEXTURE25					   = 0x84D9;
		static const Uint32 TEXTURE26					   = 0x84DA;
		static const Uint32 TEXTURE27					   = 0x84DB;
		static const Uint32 TEXTURE28					   = 0x84DC;
		static const Uint32 TEXTURE29					   = 0x84DD;
		static const Uint32 TEXTURE30					   = 0x84DE;
		static const Uint32 TEXTURE31					   = 0x84DF;
		static const Uint32 ACTIVE_TEXTURE				   = 0x84E0;
		static const Uint32 COMPRESSED_RGB				   = 0x84ED;
		static const Uint32 COMPRESSED_RGBA				   = 0x84EE;
		static const Uint32 TEXTURE_COMPRESSION_HINT	   = 0x84EF;
		static const Uint32 TEXTURE_CUBE_MAP			   = 0x8513;
		static const Uint32 TEXTURE_BINDING_CUBE_MAP	   = 0x8514;
		static const Uint32 TEXTURE_CUBE_MAP_POSITIVE_X	   = 0x8515;
		static const Uint32 TEXTURE_CUBE_MAP_NEGATIVE_X	   = 0x8516;
		static const Uint32 TEXTURE_CUBE_MAP_POSITIVE_Y	   = 0x8517;
		static const Uint32 TEXTURE_CUBE_MAP_NEGATIVE_Y	   = 0x8518;
		static const Uint32 TEXTURE_CUBE_MAP_POSITIVE_Z	   = 0x8519;
		static const Uint32 TEXTURE_CUBE_MAP_NEGATIVE_Z	   = 0x851A;
		static const Uint32 PROXY_TEXTURE_CUBE_MAP		   = 0x851B;
		static const Uint32 MAX_CUBE_MAP_TEXTURE_SIZE	   = 0x851C;
		static const Uint32 TEXTURE_COMPRESSED_IMAGE_SIZE  = 0x86A0;
		static const Uint32 TEXTURE_COMPRESSED			   = 0x86A1;
		static const Uint32 NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
		static const Uint32 COMPRESSED_TEXTURE_FORMATS	   = 0x86A3;

		static ActiveTexture activeTexture;
		static CompressedTexImage1D compressedTexImage1D;
		static CompressedTexImage2D compressedTexImage2D;
		static CompressedTexImage3D compressedTexImage3D;
		static CompressedTexSubImage1D compressedTexSubImage1D;
		static CompressedTexSubImage2D compressedTexSubImage2D;
		static CompressedTexSubImage3D compressedTexSubImage3D;
		static GetCompressedTexImage getCompressedTexImage;
		static SampleCoverage sampleCoverage;

		// Version 1.4

		static const Uint32 CONSTANT_COLOR			  = 0x8001;
		static const Uint32 ONE_MINUS_CONSTANT_COLOR  = 0x8002;
		static const Uint32 CONSTANT_ALPHA			  = 0x8003;
		static const Uint32 ONE_MINUS_CONSTANT_ALPHA  = 0x8004;
		static const Uint32 FUNC_ADD				  = 0x8006;
		static const Uint32 MIN						  = 0x8007;
		static const Uint32 MAX						  = 0x8008;
		static const Uint32 FUNC_SUBTRACT			  = 0x800A;
		static const Uint32 FUNC_REVERSE_SUBTRACT	  = 0x800B;
		static const Uint32 BLEND_DST_RGB			  = 0x80C8;
		static const Uint32 BLEND_SRC_RGB			  = 0x80C9;
		static const Uint32 BLEND_DST_ALPHA			  = 0x80CA;
		static const Uint32 BLEND_SRC_ALPHA			  = 0x80CB;
		static const Uint32 POINT_FADE_THRESHOLD_SIZE = 0x8128;
		static const Uint32 DEPTH_COMPONENT16		  = 0x81A5;
		static const Uint32 DEPTH_COMPONENT24		  = 0x81A6;
		static const Uint32 DEPTH_COMPONENT32		  = 0x81A7;
		static const Uint32 MIRRORED_REPEAT			  = 0x8370;
		static const Uint32 MAX_TEXTURE_LOD_BIAS	  = 0x84FD;
		static const Uint32 TEXTURE_LOD_BIAS		  = 0x8501;
		static const Uint32 INCR_WRAP				  = 0x8507;
		static const Uint32 DECR_WRAP				  = 0x8508;
		static const Uint32 TEXTURE_DEPTH_SIZE		  = 0x884A;
		static const Uint32 TEXTURE_COMPARE_MODE	  = 0x884C;
		static const Uint32 TEXTURE_COMPARE_FUNC	  = 0x884D;

		static BlendColor blendColor;
		static BlendEquation blendEquation;
		static BlendFuncSeparate blendFuncSeparate;
		static MultiDrawArrays multiDrawArrays;
		static MultiDrawElements multiDrawElements;
		static PointParameterF pointParameterf;
		static PointParameterFV pointParameterfv;
		static PointParameterI pointParameteri;
		static PointParameterIV pointParameteriv;

		// Version 1.5

		static const Uint32 SRC1_ALPHA						   = 0x8589;
		static const Uint32 BUFFER_SIZE						   = 0x8764;
		static const Uint32 BUFFER_USAGE					   = 0x8765;
		static const Uint32 QUERY_COUNTER_BITS				   = 0x8864;
		static const Uint32 CURRENT_QUERY					   = 0x8865;
		static const Uint32 QUERY_RESULT					   = 0x8866;
		static const Uint32 QUERY_RESULT_AVAILABLE			   = 0x8867;
		static const Uint32 ARRAY_BUFFER					   = 0x8892;
		static const Uint32 ELEMENT_ARRAY_BUFFER			   = 0x8893;
		static const Uint32 ARRAY_BUFFER_BINDING			   = 0x8894;
		static const Uint32 ELEMENT_ARRAY_BUFFER_BINDING	   = 0x8895;
		static const Uint32 VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
		static const Uint32 READ_ONLY						   = 0x88B8;
		static const Uint32 WRITE_ONLY						   = 0x88B9;
		static const Uint32 READ_WRITE						   = 0x88BA;
		static const Uint32 BUFFER_ACCESS					   = 0x88BB;
		static const Uint32 BUFFER_MAPPED					   = 0x88BC;
		static const Uint32 BUFFER_MAP_POINTER				   = 0x88BD;
		static const Uint32 STREAM_DRAW						   = 0x88E0;
		static const Uint32 STREAM_READ						   = 0x88E1;
		static const Uint32 STREAM_COPY						   = 0x88E2;
		static const Uint32 STATIC_DRAW						   = 0x88E4;
		static const Uint32 STATIC_READ						   = 0x88E5;
		static const Uint32 STATIC_COPY						   = 0x88E6;
		static const Uint32 DYNAMIC_DRAW					   = 0x88E8;
		static const Uint32 DYNAMIC_READ					   = 0x88E9;
		static const Uint32 DYNAMIC_COPY					   = 0x88EA;
		static const Uint32 SAMPLES_PASSED					   = 0x8914;

		static BeginQuery beginQuery;
		static BindBuffer bindBuffer;
		static BufferData bufferData;
		static BufferSubData bufferSubData;
		static DeleteBuffers deleteBuffers;
		static DeleteQueries deleteQueries;
		static EndQuery endQuery;
		static GenBuffers genBuffers;
		static GenQueries genQueries;
		static GetBufferParameterIV getBufferParameteriv;
		static GetBufferPointerV getBufferPointerv;
		static GetBufferSubData getBufferSubData;
		static GetQueryIV getQueryiv;
		static GetQueryObjectIV getQueryObjectiv;
		static GetQueryObjectUIV getQueryObjectuiv;
		static IsBuffer isBuffer;
		static IsQuery isQuery;
		static MapBuffer mapBuffer;
		static UnmapBuffer unmapBuffer;

		// Version 2.0

		static const Uint32 BLEND_EQUATION_RGB				 = 0x8009;
		static const Uint32 VERTEX_ATTRIB_ARRAY_ENABLED		 = 0x8622;
		static const Uint32 VERTEX_ATTRIB_ARRAY_SIZE		 = 0x8623;
		static const Uint32 VERTEX_ATTRIB_ARRAY_STRIDE		 = 0x8624;
		static const Uint32 VERTEX_ATTRIB_ARRAY_TYPE		 = 0x8625;
		static const Uint32 CURRENT_VERTEX_ATTRIB			 = 0x8626;
		static const Uint32 VERTEX_PROGRAM_POINT_SIZE		 = 0x8642;
		static const Uint32 VERTEX_ATTRIB_ARRAY_POINTER		 = 0x8645;
		static const Uint32 STENCIL_BACK_FUNC				 = 0x8800;
		static const Uint32 STENCIL_BACK_FAIL				 = 0x8801;
		static const Uint32 STENCIL_BACK_PASS_DEPTH_FAIL	 = 0x8802;
		static const Uint32 STENCIL_BACK_PASS_DEPTH_PASS	 = 0x8803;
		static const Uint32 MAX_DRAW_BUFFERS				 = 0x8824;
		static const Uint32 DRAW_BUFFER0					 = 0x8825;
		static const Uint32 DRAW_BUFFER1					 = 0x8826;
		static const Uint32 DRAW_BUFFER2					 = 0x8827;
		static const Uint32 DRAW_BUFFER3					 = 0x8828;
		static const Uint32 DRAW_BUFFER4					 = 0x8829;
		static const Uint32 DRAW_BUFFER5					 = 0x882A;
		static const Uint32 DRAW_BUFFER6					 = 0x882B;
		static const Uint32 DRAW_BUFFER7					 = 0x882C;
		static const Uint32 DRAW_BUFFER8					 = 0x882D;
		static const Uint32 DRAW_BUFFER9					 = 0x882E;
		static const Uint32 DRAW_BUFFER10					 = 0x882F;
		static const Uint32 DRAW_BUFFER11					 = 0x8830;
		static const Uint32 DRAW_BUFFER12					 = 0x8831;
		static const Uint32 DRAW_BUFFER13					 = 0x8832;
		static const Uint32 DRAW_BUFFER14					 = 0x8833;
		static const Uint32 DRAW_BUFFER15					 = 0x8834;
		static const Uint32 BLEND_EQUATION_ALPHA			 = 0x883D;
		static const Uint32 MAX_VERTEX_ATTRIBS				 = 0x8869;
		static const Uint32 VERTEX_ATTRIB_ARRAY_NORMALIZED	 = 0x886A;
		static const Uint32 MAX_TEXTURE_IMAGE_UNITS			 = 0x8872;
		static const Uint32 FRAGMENT_SHADER					 = 0x8B30;
		static const Uint32 VERTEX_SHADER					 = 0x8B31;
		static const Uint32 MAX_FRAGMENT_UNIFORM_COMPONENTS	 = 0x8B49;
		static const Uint32 MAX_VERTEX_UNIFORM_COMPONENTS	 = 0x8B4A;
		static const Uint32 MAX_VARYING_FLOATS				 = 0x8B4B;
		static const Uint32 MAX_VERTEX_TEXTURE_IMAGE_UNITS	 = 0x8B4C;
		static const Uint32 MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
		static const Uint32 SHADER_TYPE						 = 0x8B4F;
		static const Uint32 FLOAT_VEC2						 = 0x8B50;
		static const Uint32 FLOAT_VEC3						 = 0x8B51;
		static const Uint32 FLOAT_VEC4						 = 0x8B52;
		static const Uint32 INT_VEC2						 = 0x8B53;
		static const Uint32 INT_VEC3						 = 0x8B54;
		static const Uint32 INT_VEC4						 = 0x8B55;
		static const Uint32 BOOL							 = 0x8B56;
		static const Uint32 BOOL_VEC2						 = 0x8B57;
		static const Uint32 BOOL_VEC3						 = 0x8B58;
		static const Uint32 BOOL_VEC4						 = 0x8B59;
		static const Uint32 FLOAT_MAT2						 = 0x8B5A;
		static const Uint32 FLOAT_MAT3						 = 0x8B5B;
		static const Uint32 FLOAT_MAT4						 = 0x8B5C;
		static const Uint32 SAMPLER_1D						 = 0x8B5D;
		static const Uint32 SAMPLER_2D						 = 0x8B5E;
		static const Uint32 SAMPLER_3D						 = 0x8B5F;
		static const Uint32 SAMPLER_CUBE					 = 0x8B60;
		static const Uint32 SAMPLER_1D_SHADOW				 = 0x8B61;
		static const Uint32 SAMPLER_2D_SHADOW				 = 0x8B62;
		static const Uint32 DELETE_STATUS					 = 0x8B80;
		static const Uint32 COMPILE_STATUS					 = 0x8B81;
		static const Uint32 LINK_STATUS						 = 0x8B82;
		static const Uint32 VALIDATE_STATUS					 = 0x8B83;
		static const Uint32 INFO_LOG_LENGTH					 = 0x8B84;
		static const Uint32 ATTACHED_SHADERS				 = 0x8B85;
		static const Uint32 ACTIVE_UNIFORMS					 = 0x8B86;
		static const Uint32 ACTIVE_UNIFORM_MAX_LENGTH		 = 0x8B87;
		static const Uint32 SHADER_SOURCE_LENGTH			 = 0x8B88;
		static const Uint32 ACTIVE_ATTRIBUTES				 = 0x8B89;
		static const Uint32 ACTIVE_ATTRIBUTE_MAX_LENGTH		 = 0x8B8A;
		static const Uint32 FRAGMENT_SHADER_DERIVATIVE_HINT	 = 0x8B8B;
		static const Uint32 SHADING_LANGUAGE_VERSION		 = 0x8B8C;
		static const Uint32 CURRENT_PROGRAM					 = 0x8B8D;
		static const Uint32 POINT_SPRITE_COORD_ORIGIN		 = 0x8CA0;
		static const Uint32 LOWER_LEFT						 = 0x8CA1;
		static const Uint32 UPPER_LEFT						 = 0x8CA2;
		static const Uint32 STENCIL_BACK_REF				 = 0x8CA3;
		static const Uint32 STENCIL_BACK_VALUE_MASK			 = 0x8CA4;
		static const Uint32 STENCIL_BACK_WRITEMASK			 = 0x8CA5;

		static AttachShader attachShader;
		static BindAttribLocation bindAttribLocation;
		static BlendEquationSeparate blendEquationSeparate;
		static CompileShader compileShader;
		static CreateProgram createProgram;
		static CreateShader createShader;
		static DeleteProgram deleteProgram;
		static DeleteShader deleteShader;
		static DetachShader detachShader;
		static DisableVertexAttribArray disableVertexAttribArray;
		static DrawBuffers drawBuffers;
		static EnableVertexAttribArray enableVertexAttribArray;
		static GetActiveAttrib getActiveAttrib;
		static GetActiveUniform getActiveUniform;
		static GetAttachedShaders getAttachedShaders;
		static GetAttribLocation getAttribLocation;
		static GetProgramInfoLog getProgramInfoLog;
		static GetProgramIV getProgramiv;
		static GetShaderInfoLog getShaderInfoLog;
		static GetShaderIV getShaderiv;
		static GetShaderSource getShaderSource;
		static GetUniformFV getUniformfv;
		static GetUniformIV getUniformiv;
		static GetUniformLocation getUniformLocation;
		static GetVertexAttribDV getVertexAttribdv;
		static GetVertexAttribFV getVertexAttribfv;
		static GetVertexAttribIV getVertexAttribiv;
		static GetVertexAttribPointerV getVertexAttribPointerv;
		static IsProgram isProgram;
		static IsShader isShader;
		static LinkProgram linkProgram;
		static ShaderSource shaderSource;
		static StencilFuncSeparate stencilFuncSeparate;
		static StencilMaskSeparate stencilMaskSeparate;
		static StencilOpSeparate stencilOpSeparate;
		static Uniform1F uniform1f;
		static Uniform1FV uniform1fv;
		static Uniform1I uniform1i;
		static Uniform1IV uniform1iv;
		static Uniform2F uniform2f;
		static Uniform2FV uniform2fv;
		static Uniform2I uniform2i;
		static Uniform2IV uniform2iv;
		static Uniform3F uniform3f;
		static Uniform3FV uniform3fv;
		static Uniform3I uniform3i;
		static Uniform3IV uniform3iv;
		static Uniform4F uniform4f;
		static Uniform4FV uniform4fv;
		static Uniform4I uniform4i;
		static Uniform4IV uniform4iv;
		static UniformMatrix2FV uniformMatrix2fv;
		static UniformMatrix3FV uniformMatrix3fv;
		static UniformMatrix4FV uniformMatrix4fv;
		static UseProgram useProgram;
		static ValidateProgram validateProgram;
		static VertexAttrib1D vertexAttrib1d;
		static VertexAttrib1DV vertexAttrib1dv;
		static VertexAttrib1F vertexAttrib1f;
		static VertexAttrib1FV vertexAttrib1fv;
		static VertexAttrib1S vertexAttrib1s;
		static VertexAttrib1SV vertexAttrib1sv;
		static VertexAttrib2D vertexAttrib2d;
		static VertexAttrib2DV vertexAttrib2dv;
		static VertexAttrib2F vertexAttrib2f;
		static VertexAttrib2FV vertexAttrib2fv;
		static VertexAttrib2S vertexAttrib2s;
		static VertexAttrib2SV vertexAttrib2sv;
		static VertexAttrib3D vertexAttrib3d;
		static VertexAttrib3DV vertexAttrib3dv;
		static VertexAttrib3F vertexAttrib3f;
		static VertexAttrib3FV vertexAttrib3fv;
		static VertexAttrib3S vertexAttrib3s;
		static VertexAttrib3SV vertexAttrib3sv;
		static VertexAttrib4BV vertexAttrib4bv;
		static VertexAttrib4D vertexAttrib4d;
		static VertexAttrib4DV vertexAttrib4dv;
		static VertexAttrib4F vertexAttrib4f;
		static VertexAttrib4FV vertexAttrib4fv;
		static VertexAttrib4IV vertexAttrib4iv;
		static VertexAttrib4NBV vertexAttrib4Nbv;
		static VertexAttrib4NIV vertexAttrib4Niv;
		static VertexAttrib4NSV vertexAttrib4Nsv;
		static VertexAttrib4NUB vertexAttrib4Nub;
		static VertexAttrib4NUBV vertexAttrib4Nubv;
		static VertexAttrib4NUIV vertexAttrib4Nuiv;
		static VertexAttrib4NUSV vertexAttrib4Nusv;
		static VertexAttrib4S vertexAttrib4s;
		static VertexAttrib4SV vertexAttrib4sv;
		static VertexAttrib4UBV vertexAttrib4ubv;
		static VertexAttrib4UIV vertexAttrib4uiv;
		static VertexAttrib4USV vertexAttrib4usv;
		static VertexAttribPointer vertexAttribPointer;

		// Version 2.1

		static const Uint32 PIXEL_PACK_BUFFER			= 0x88EB;
		static const Uint32 PIXEL_UNPACK_BUFFER			= 0x88EC;
		static const Uint32 PIXEL_PACK_BUFFER_BINDING	= 0x88ED;
		static const Uint32 PIXEL_UNPACK_BUFFER_BINDING = 0x88EF;
		static const Uint32 FLOAT_MAT2x3				= 0x8B65;
		static const Uint32 FLOAT_MAT2x4				= 0x8B66;
		static const Uint32 FLOAT_MAT3x2				= 0x8B67;
		static const Uint32 FLOAT_MAT3x4				= 0x8B68;
		static const Uint32 FLOAT_MAT4x2				= 0x8B69;
		static const Uint32 FLOAT_MAT4x3				= 0x8B6A;
		static const Uint32 SRGB						= 0x8C40;
		static const Uint32 SRGB8						= 0x8C41;
		static const Uint32 SRGB_ALPHA					= 0x8C42;
		static const Uint32 SRGB8_ALPHA8				= 0x8C43;
		static const Uint32 COMPRESSED_SRGB				= 0x8C48;
		static const Uint32 COMPRESSED_SRGB_ALPHA		= 0x8C49;

		static UniformMatrix2X3FV uniformMatrix2x3fv;
		static UniformMatrix2X4FV uniformMatrix2x4fv;
		static UniformMatrix3X2FV uniformMatrix3x2fv;
		static UniformMatrix3X4FV uniformMatrix3x4fv;
		static UniformMatrix4X2FV uniformMatrix4x2fv;
		static UniformMatrix4X3FV uniformMatrix4x3fv;

		// Version 3.0

		static const Uint32 CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT			  = 0x0001;
		static const Uint32 MAP_READ_BIT								  = 0x0001;
		static const Uint32 MAP_WRITE_BIT								  = 0x0002;
		static const Uint32 MAP_INVALIDATE_RANGE_BIT					  = 0x0004;
		static const Uint32 MAP_INVALIDATE_BUFFER_BIT					  = 0x0008;
		static const Uint32 MAP_FLUSH_EXPLICIT_BIT						  = 0x0010;
		static const Uint32 MAP_UNSYNCHRONIZED_BIT						  = 0x0020;
		static const Uint32 INVALID_FRAMEBUFFER_OPERATION				  = 0x0506;
		static const Uint32 MAX_CLIP_DISTANCES							  = 0x0D32;
		static const Uint32 HALF_FLOAT									  = 0x140B;
		static const Uint32 CLIP_DISTANCE0								  = 0x3000;
		static const Uint32 CLIP_DISTANCE1								  = 0x3001;
		static const Uint32 CLIP_DISTANCE2								  = 0x3002;
		static const Uint32 CLIP_DISTANCE3								  = 0x3003;
		static const Uint32 CLIP_DISTANCE4								  = 0x3004;
		static const Uint32 CLIP_DISTANCE5								  = 0x3005;
		static const Uint32 CLIP_DISTANCE6								  = 0x3006;
		static const Uint32 CLIP_DISTANCE7								  = 0x3007;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING		  = 0x8210;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE		  = 0x8211;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_RED_SIZE				  = 0x8212;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_GREEN_SIZE			  = 0x8213;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_BLUE_SIZE			  = 0x8214;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE			  = 0x8215;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE			  = 0x8216;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE			  = 0x8217;
		static const Uint32 FRAMEBUFFER_DEFAULT							  = 0x8218;
		static const Uint32 FRAMEBUFFER_UNDEFINED						  = 0x8219;
		static const Uint32 DEPTH_STENCIL_ATTACHMENT					  = 0x821A;
		static const Uint32 MAJOR_VERSION								  = 0x821B;
		static const Uint32 MINOR_VERSION								  = 0x821C;
		static const Uint32 NUM_EXTENSIONS								  = 0x821D;
		static const Uint32 CONTEXT_FLAGS								  = 0x821E;
		static const Uint32 COMPRESSED_RED								  = 0x8225;
		static const Uint32 COMPRESSED_RG								  = 0x8226;
		static const Uint32 RG											  = 0x8227;
		static const Uint32 RG_INTEGER									  = 0x8228;
		static const Uint32 R8											  = 0x8229;
		static const Uint32 R16											  = 0x822A;
		static const Uint32 RG8											  = 0x822B;
		static const Uint32 RG16										  = 0x822C;
		static const Uint32 R16F										  = 0x822D;
		static const Uint32 R32F										  = 0x822E;
		static const Uint32 RG16F										  = 0x822F;
		static const Uint32 RG32F										  = 0x8230;
		static const Uint32 R8I											  = 0x8231;
		static const Uint32 R8UI										  = 0x8232;
		static const Uint32 R16I										  = 0x8233;
		static const Uint32 R16UI										  = 0x8234;
		static const Uint32 R32I										  = 0x8235;
		static const Uint32 R32UI										  = 0x8236;
		static const Uint32 RG8I										  = 0x8237;
		static const Uint32 RG8UI										  = 0x8238;
		static const Uint32 RG16I										  = 0x8239;
		static const Uint32 RG16UI										  = 0x823A;
		static const Uint32 RG32I										  = 0x823B;
		static const Uint32 RG32UI										  = 0x823C;
		static const Uint32 MAX_RENDERBUFFER_SIZE						  = 0x84E8;
		static const Uint32 DEPTH_STENCIL								  = 0x84F9;
		static const Uint32 UNSIGNED_INT_24_8							  = 0x84FA;
		static const Uint32 VERTEX_ARRAY_BINDING						  = 0x85B5;
		static const Uint32 RGBA32F										  = 0x8814;
		static const Uint32 RGB32F										  = 0x8815;
		static const Uint32 RGBA16F										  = 0x881A;
		static const Uint32 RGB16F										  = 0x881B;
		static const Uint32 COMPARE_REF_TO_TEXTURE						  = 0x884E;
		static const Uint32 DEPTH24_STENCIL8							  = 0x88F0;
		static const Uint32 TEXTURE_STENCIL_SIZE						  = 0x88F1;
		static const Uint32 VERTEX_ATTRIB_ARRAY_INTEGER					  = 0x88FD;
		static const Uint32 MAX_ARRAY_TEXTURE_LAYERS					  = 0x88FF;
		static const Uint32 MIN_PROGRAM_TEXEL_OFFSET					  = 0x8904;
		static const Uint32 MAX_PROGRAM_TEXEL_OFFSET					  = 0x8905;
		static const Uint32 CLAMP_READ_COLOR							  = 0x891C;
		static const Uint32 FIXED_ONLY									  = 0x891D;
		static const Uint32 MAX_VARYING_COMPONENTS						  = 0x8B4B;
		static const Uint32 TEXTURE_RED_TYPE							  = 0x8C10;
		static const Uint32 TEXTURE_GREEN_TYPE							  = 0x8C11;
		static const Uint32 TEXTURE_BLUE_TYPE							  = 0x8C12;
		static const Uint32 TEXTURE_ALPHA_TYPE							  = 0x8C13;
		static const Uint32 TEXTURE_DEPTH_TYPE							  = 0x8C16;
		static const Uint32 UNSIGNED_NORMALIZED							  = 0x8C17;
		static const Uint32 TEXTURE_1D_ARRAY							  = 0x8C18;
		static const Uint32 PROXY_TEXTURE_1D_ARRAY						  = 0x8C19;
		static const Uint32 TEXTURE_2D_ARRAY							  = 0x8C1A;
		static const Uint32 PROXY_TEXTURE_2D_ARRAY						  = 0x8C1B;
		static const Uint32 TEXTURE_BINDING_1D_ARRAY					  = 0x8C1C;
		static const Uint32 TEXTURE_BINDING_2D_ARRAY					  = 0x8C1D;
		static const Uint32 R11F_G11F_B10F								  = 0x8C3A;
		static const Uint32 UNSIGNED_INT_10F_11F_11F_REV				  = 0x8C3B;
		static const Uint32 RGB9_E5										  = 0x8C3D;
		static const Uint32 UNSIGNED_INT_5_9_9_9_REV					  = 0x8C3E;
		static const Uint32 TEXTURE_SHARED_SIZE							  = 0x8C3F;
		static const Uint32 TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH		  = 0x8C76;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_MODE				  = 0x8C7F;
		static const Uint32 MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS	  = 0x8C80;
		static const Uint32 TRANSFORM_FEEDBACK_VARYINGS					  = 0x8C83;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_START				  = 0x8C84;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_SIZE				  = 0x8C85;
		static const Uint32 PRIMITIVES_GENERATED						  = 0x8C87;
		static const Uint32 TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN		  = 0x8C88;
		static const Uint32 RASTERIZER_DISCARD							  = 0x8C89;
		static const Uint32 MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A;
		static const Uint32 MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS		  = 0x8C8B;
		static const Uint32 INTERLEAVED_ATTRIBS							  = 0x8C8C;
		static const Uint32 SEPARATE_ATTRIBS							  = 0x8C8D;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER					  = 0x8C8E;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_BINDING			  = 0x8C8F;
		static const Uint32 DRAW_FRAMEBUFFER_BINDING					  = 0x8CA6;
		static const Uint32 FRAMEBUFFER_BINDING							  = 0x8CA6;
		static const Uint32 RENDERBUFFER_BINDING						  = 0x8CA7;
		static const Uint32 READ_FRAMEBUFFER							  = 0x8CA8;
		static const Uint32 DRAW_FRAMEBUFFER							  = 0x8CA9;
		static const Uint32 READ_FRAMEBUFFER_BINDING					  = 0x8CAA;
		static const Uint32 RENDERBUFFER_SAMPLES						  = 0x8CAB;
		static const Uint32 DEPTH_COMPONENT32F							  = 0x8CAC;
		static const Uint32 DEPTH32F_STENCIL8							  = 0x8CAD;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE			  = 0x8CD0;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_OBJECT_NAME			  = 0x8CD1;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL		  = 0x8CD2;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE  = 0x8CD3;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER		  = 0x8CD4;
		static const Uint32 FRAMEBUFFER_COMPLETE						  = 0x8CD5;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_ATTACHMENT			  = 0x8CD6;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	  = 0x8CD7;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER			  = 0x8CDB;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_READ_BUFFER			  = 0x8CDC;
		static const Uint32 FRAMEBUFFER_UNSUPPORTED						  = 0x8CDD;
		static const Uint32 MAX_COLOR_ATTACHMENTS						  = 0x8CDF;
		static const Uint32 COLOR_ATTACHMENT0							  = 0x8CE0;
		static const Uint32 COLOR_ATTACHMENT1							  = 0x8CE1;
		static const Uint32 COLOR_ATTACHMENT2							  = 0x8CE2;
		static const Uint32 COLOR_ATTACHMENT3							  = 0x8CE3;
		static const Uint32 COLOR_ATTACHMENT4							  = 0x8CE4;
		static const Uint32 COLOR_ATTACHMENT5							  = 0x8CE5;
		static const Uint32 COLOR_ATTACHMENT6							  = 0x8CE6;
		static const Uint32 COLOR_ATTACHMENT7							  = 0x8CE7;
		static const Uint32 COLOR_ATTACHMENT8							  = 0x8CE8;
		static const Uint32 COLOR_ATTACHMENT9							  = 0x8CE9;
		static const Uint32 COLOR_ATTACHMENT10							  = 0x8CEA;
		static const Uint32 COLOR_ATTACHMENT11							  = 0x8CEB;
		static const Uint32 COLOR_ATTACHMENT12							  = 0x8CEC;
		static const Uint32 COLOR_ATTACHMENT13							  = 0x8CED;
		static const Uint32 COLOR_ATTACHMENT14							  = 0x8CEE;
		static const Uint32 COLOR_ATTACHMENT15							  = 0x8CEF;
		static const Uint32 COLOR_ATTACHMENT16							  = 0x8CF0;
		static const Uint32 COLOR_ATTACHMENT17							  = 0x8CF1;
		static const Uint32 COLOR_ATTACHMENT18							  = 0x8CF2;
		static const Uint32 COLOR_ATTACHMENT19							  = 0x8CF3;
		static const Uint32 COLOR_ATTACHMENT20							  = 0x8CF4;
		static const Uint32 COLOR_ATTACHMENT21							  = 0x8CF5;
		static const Uint32 COLOR_ATTACHMENT22							  = 0x8CF6;
		static const Uint32 COLOR_ATTACHMENT23							  = 0x8CF7;
		static const Uint32 COLOR_ATTACHMENT24							  = 0x8CF8;
		static const Uint32 COLOR_ATTACHMENT25							  = 0x8CF9;
		static const Uint32 COLOR_ATTACHMENT26							  = 0x8CFA;
		static const Uint32 COLOR_ATTACHMENT27							  = 0x8CFB;
		static const Uint32 COLOR_ATTACHMENT28							  = 0x8CFC;
		static const Uint32 COLOR_ATTACHMENT29							  = 0x8CFD;
		static const Uint32 COLOR_ATTACHMENT30							  = 0x8CFE;
		static const Uint32 COLOR_ATTACHMENT31							  = 0x8CFF;
		static const Uint32 DEPTH_ATTACHMENT							  = 0x8D00;
		static const Uint32 STENCIL_ATTACHMENT							  = 0x8D20;
		static const Uint32 FRAMEBUFFER									  = 0x8D40;
		static const Uint32 RENDERBUFFER								  = 0x8D41;
		static const Uint32 RENDERBUFFER_WIDTH							  = 0x8D42;
		static const Uint32 RENDERBUFFER_HEIGHT							  = 0x8D43;
		static const Uint32 RENDERBUFFER_INTERNAL_FORMAT				  = 0x8D44;
		static const Uint32 STENCIL_INDEX1								  = 0x8D46;
		static const Uint32 STENCIL_INDEX4								  = 0x8D47;
		static const Uint32 STENCIL_INDEX8								  = 0x8D48;
		static const Uint32 STENCIL_INDEX16								  = 0x8D49;
		static const Uint32 RENDERBUFFER_RED_SIZE						  = 0x8D50;
		static const Uint32 RENDERBUFFER_GREEN_SIZE						  = 0x8D51;
		static const Uint32 RENDERBUFFER_BLUE_SIZE						  = 0x8D52;
		static const Uint32 RENDERBUFFER_ALPHA_SIZE						  = 0x8D53;
		static const Uint32 RENDERBUFFER_DEPTH_SIZE						  = 0x8D54;
		static const Uint32 RENDERBUFFER_STENCIL_SIZE					  = 0x8D55;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_MULTISAMPLE			  = 0x8D56;
		static const Uint32 MAX_SAMPLES									  = 0x8D57;
		static const Uint32 RGBA32UI									  = 0x8D70;
		static const Uint32 RGB32UI										  = 0x8D71;
		static const Uint32 RGBA16UI									  = 0x8D76;
		static const Uint32 RGB16UI										  = 0x8D77;
		static const Uint32 RGBA8UI										  = 0x8D7C;
		static const Uint32 RGB8UI										  = 0x8D7D;
		static const Uint32 RGBA32I										  = 0x8D82;
		static const Uint32 RGB32I										  = 0x8D83;
		static const Uint32 RGBA16I										  = 0x8D88;
		static const Uint32 RGB16I										  = 0x8D89;
		static const Uint32 RGBA8I										  = 0x8D8E;
		static const Uint32 RGB8I										  = 0x8D8F;
		static const Uint32 RED_INTEGER									  = 0x8D94;
		static const Uint32 GREEN_INTEGER								  = 0x8D95;
		static const Uint32 BLUE_INTEGER								  = 0x8D96;
		static const Uint32 RGB_INTEGER									  = 0x8D98;
		static const Uint32 RGBA_INTEGER								  = 0x8D99;
		static const Uint32 BGR_INTEGER									  = 0x8D9A;
		static const Uint32 BGRA_INTEGER								  = 0x8D9B;
		static const Uint32 FLOAT_32_UNSIGNED_INT_24_8_REV				  = 0x8DAD;
		static const Uint32 FRAMEBUFFER_SRGB							  = 0x8DB9;
		static const Uint32 COMPRESSED_RED_RGTC1						  = 0x8DBB;
		static const Uint32 COMPRESSED_SIGNED_RED_RGTC1					  = 0x8DBC;
		static const Uint32 COMPRESSED_RG_RGTC2							  = 0x8DBD;
		static const Uint32 COMPRESSED_SIGNED_RG_RGTC2					  = 0x8DBE;
		static const Uint32 SAMPLER_1D_ARRAY							  = 0x8DC0;
		static const Uint32 SAMPLER_2D_ARRAY							  = 0x8DC1;
		static const Uint32 SAMPLER_1D_ARRAY_SHADOW						  = 0x8DC3;
		static const Uint32 SAMPLER_2D_ARRAY_SHADOW						  = 0x8DC4;
		static const Uint32 SAMPLER_CUBE_SHADOW							  = 0x8DC5;
		static const Uint32 UNSIGNED_INT_VEC2							  = 0x8DC6;
		static const Uint32 UNSIGNED_INT_VEC3							  = 0x8DC7;
		static const Uint32 UNSIGNED_INT_VEC4							  = 0x8DC8;
		static const Uint32 INT_SAMPLER_1D								  = 0x8DC9;
		static const Uint32 INT_SAMPLER_2D								  = 0x8DCA;
		static const Uint32 INT_SAMPLER_3D								  = 0x8DCB;
		static const Uint32 INT_SAMPLER_CUBE							  = 0x8DCC;
		static const Uint32 INT_SAMPLER_1D_ARRAY						  = 0x8DCE;
		static const Uint32 INT_SAMPLER_2D_ARRAY						  = 0x8DCF;
		static const Uint32 UNSIGNED_INT_SAMPLER_1D						  = 0x8DD1;
		static const Uint32 UNSIGNED_INT_SAMPLER_2D						  = 0x8DD2;
		static const Uint32 UNSIGNED_INT_SAMPLER_3D						  = 0x8DD3;
		static const Uint32 UNSIGNED_INT_SAMPLER_CUBE					  = 0x8DD4;
		static const Uint32 UNSIGNED_INT_SAMPLER_1D_ARRAY				  = 0x8DD6;
		static const Uint32 UNSIGNED_INT_SAMPLER_2D_ARRAY				  = 0x8DD7;
		static const Uint32 QUERY_WAIT									  = 0x8E13;
		static const Uint32 QUERY_NO_WAIT								  = 0x8E14;
		static const Uint32 QUERY_BY_REGION_WAIT						  = 0x8E15;
		static const Uint32 QUERY_BY_REGION_NO_WAIT						  = 0x8E16;
		static const Uint32 BUFFER_ACCESS_FLAGS							  = 0x911F;
		static const Uint32 BUFFER_MAP_LENGTH							  = 0x9120;
		static const Uint32 BUFFER_MAP_OFFSET							  = 0x9121;

		static BeginConditionalRender beginConditionalRender;
		static BeginTransformFeedback beginTransformFeedback;
		static BindBufferBase bindBufferBase;
		static BindBufferRange bindBufferRange;
		static BindFragDataLocation bindFragDataLocation;
		static BindFramebuffer bindFramebuffer;
		static BindRenderbuffer bindRenderbuffer;
		static BindVertexArray bindVertexArray;
		static BlitFramebuffer blitFramebuffer;
		static CheckFramebufferStatus checkFramebufferStatus;
		static ClampColor clampColor;
		static ClearBufferFI clearBufferfi;
		static ClearBufferFV clearBufferfv;
		static ClearBufferIV clearBufferiv;
		static ClearBufferUIV clearBufferuiv;
		static ColorMaskI colorMaski;
		static DeleteFramebuffers deleteFramebuffers;
		static DeleteRenderbuffers deleteRenderbuffers;
		static DeleteVertexArrays deleteVertexArrays;
		static DisableI disablei;
		static EnableI enablei;
		static EndConditionalRender endConditionalRender;
		static EndTransformFeedback endTransformFeedback;
		static FlushMappedBufferRange flushMappedBufferRange;
		static FramebufferRenderbuffer framebufferRenderbuffer;
		static FramebufferTexture1D framebufferTexture1D;
		static FramebufferTexture2D framebufferTexture2D;
		static FramebufferTexture3D framebufferTexture3D;
		static FramebufferTextureLayer framebufferTextureLayer;
		static GenerateMipmap generateMipmap;
		static GenFramebuffers genFramebuffers;
		static GenRenderbuffers genRenderbuffers;
		static GenVertexArrays genVertexArrays;
		static GetBooleanI_V getBooleani_v;
		static GetFragDataLocation getFragDataLocation;
		static GetFramebufferAttachmentParameterIV getFramebufferAttachmentParameteriv;
		static GetIntegerI_V getIntegeri_v;
		static GetRenderbufferParameterIV getRenderbufferParameteriv;
		static GetStringI getStringi;
		static GetTexParameterIIV getTexParameterIiv;
		static GetTexParameterIUIV getTexParameterIuiv;
		static GetTransformFeedbackVarying getTransformFeedbackVarying;
		static GetUniformUIV getUniformuiv;
		static GetVertexAttribIIV getVertexAttribIiv;
		static GetVertexAttribIUIV getVertexAttribIuiv;
		static IsEnabledI isEnabledi;
		static IsFramebuffer isFramebuffer;
		static IsRenderbuffer isRenderbuffer;
		static IsVertexArray isVertexArray;
		static MapBufferRange mapBufferRange;
		static RenderbufferStorage renderbufferStorage;
		static RenderbufferStorageMultisample renderbufferStorageMultisample;
		static TexParameterIIV texParameterIiv;
		static TexParameterIUIV texParameterIuiv;
		static TransformFeedbackVaryings transformFeedbackVaryings;
		static Uniform1UI uniform1ui;
		static Uniform1UIV uniform1uiv;
		static Uniform2UI uniform2ui;
		static Uniform2UIV uniform2uiv;
		static Uniform3UI uniform3ui;
		static Uniform3UIV uniform3uiv;
		static Uniform4UI uniform4ui;
		static Uniform4UIV uniform4uiv;
		static VertexAttribI1I vertexAttribI1i;
		static VertexAttribI1IV vertexAttribI1iv;
		static VertexAttribI1UI vertexAttribI1ui;
		static VertexAttribI1UIV vertexAttribI1uiv;
		static VertexAttribI2I vertexAttribI2i;
		static VertexAttribI2IV vertexAttribI2iv;
		static VertexAttribI2UI vertexAttribI2ui;
		static VertexAttribI2UIV vertexAttribI2uiv;
		static VertexAttribI3I vertexAttribI3i;
		static VertexAttribI3IV vertexAttribI3iv;
		static VertexAttribI3UI vertexAttribI3ui;
		static VertexAttribI3UIV vertexAttribI3uiv;
		static VertexAttribI4BV vertexAttribI4bv;
		static VertexAttribI4I vertexAttribI4i;
		static VertexAttribI4IV vertexAttribI4iv;
		static VertexAttribI4SV vertexAttribI4sv;
		static VertexAttribI4UBV vertexAttribI4ubv;
		static VertexAttribI4UI vertexAttribI4ui;
		static VertexAttribI4UIV vertexAttribI4uiv;
		static VertexAttribI4USV vertexAttribI4usv;
		static VertexAttribIPointer vertexAttribIPointer;

		// Version 3.1

		static const Uint32 TEXTURE_RECTANGLE							= 0x84F5;
		static const Uint32 TEXTURE_BINDING_RECTANGLE					= 0x84F6;
		static const Uint32 PROXY_TEXTURE_RECTANGLE						= 0x84F7;
		static const Uint32 MAX_RECTANGLE_TEXTURE_SIZE					= 0x84F8;
		static const Uint32 UNIFORM_BUFFER								= 0x8A11;
		static const Uint32 UNIFORM_BUFFER_BINDING						= 0x8A28;
		static const Uint32 UNIFORM_BUFFER_START						= 0x8A29;
		static const Uint32 UNIFORM_BUFFER_SIZE							= 0x8A2A;
		static const Uint32 MAX_VERTEX_UNIFORM_BLOCKS					= 0x8A2B;
		static const Uint32 MAX_GEOMETRY_UNIFORM_BLOCKS					= 0x8A2C;
		static const Uint32 MAX_FRAGMENT_UNIFORM_BLOCKS					= 0x8A2D;
		static const Uint32 MAX_COMBINED_UNIFORM_BLOCKS					= 0x8A2E;
		static const Uint32 MAX_UNIFORM_BUFFER_BINDINGS					= 0x8A2F;
		static const Uint32 MAX_UNIFORM_BLOCK_SIZE						= 0x8A30;
		static const Uint32 MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS		= 0x8A31;
		static const Uint32 MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS	= 0x8A32;
		static const Uint32 MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS	= 0x8A33;
		static const Uint32 UNIFORM_BUFFER_OFFSET_ALIGNMENT				= 0x8A34;
		static const Uint32 ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH		= 0x8A35;
		static const Uint32 ACTIVE_UNIFORM_BLOCKS						= 0x8A36;
		static const Uint32 UNIFORM_TYPE								= 0x8A37;
		static const Uint32 UNIFORM_SIZE								= 0x8A38;
		static const Uint32 UNIFORM_NAME_LENGTH							= 0x8A39;
		static const Uint32 UNIFORM_BLOCK_INDEX							= 0x8A3A;
		static const Uint32 UNIFORM_OFFSET								= 0x8A3B;
		static const Uint32 UNIFORM_ARRAY_STRIDE						= 0x8A3C;
		static const Uint32 UNIFORM_MATRIX_STRIDE						= 0x8A3D;
		static const Uint32 UNIFORM_IS_ROW_MAJOR						= 0x8A3E;
		static const Uint32 UNIFORM_BLOCK_BINDING						= 0x8A3F;
		static const Uint32 UNIFORM_BLOCK_DATA_SIZE						= 0x8A40;
		static const Uint32 UNIFORM_BLOCK_NAME_LENGTH					= 0x8A41;
		static const Uint32 UNIFORM_BLOCK_ACTIVE_UNIFORMS				= 0x8A42;
		static const Uint32 UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES		= 0x8A43;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER	= 0x8A44;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46;
		static const Uint32 SAMPLER_2D_RECT								= 0x8B63;
		static const Uint32 SAMPLER_2D_RECT_SHADOW						= 0x8B64;
		static const Uint32 TEXTURE_BUFFER								= 0x8C2A;
		static const Uint32 MAX_TEXTURE_BUFFER_SIZE						= 0x8C2B;
		static const Uint32 TEXTURE_BINDING_BUFFER						= 0x8C2C;
		static const Uint32 TEXTURE_BUFFER_DATA_STORE_BINDING			= 0x8C2D;
		static const Uint32 SAMPLER_BUFFER								= 0x8DC2;
		static const Uint32 INT_SAMPLER_2D_RECT							= 0x8DCD;
		static const Uint32 INT_SAMPLER_BUFFER							= 0x8DD0;
		static const Uint32 UNSIGNED_INT_SAMPLER_2D_RECT				= 0x8DD5;
		static const Uint32 UNSIGNED_INT_SAMPLER_BUFFER					= 0x8DD8;
		static const Uint32 COPY_READ_BUFFER							= 0x8F36;
		static const Uint32 COPY_WRITE_BUFFER							= 0x8F37;
		static const Uint32 R8_SNORM									= 0x8F94;
		static const Uint32 RG8_SNORM									= 0x8F95;
		static const Uint32 RGB8_SNORM									= 0x8F96;
		static const Uint32 RGBA8_SNORM									= 0x8F97;
		static const Uint32 R16_SNORM									= 0x8F98;
		static const Uint32 RG16_SNORM									= 0x8F99;
		static const Uint32 RGB16_SNORM									= 0x8F9A;
		static const Uint32 RGBA16_SNORM								= 0x8F9B;
		static const Uint32 SIGNED_NORMALIZED							= 0x8F9C;
		static const Uint32 PRIMITIVE_RESTART							= 0x8F9D;
		static const Uint32 PRIMITIVE_RESTART_INDEX						= 0x8F9E;
		static const Uint32 INVALID_INDEX								= 0xFFFFFFFF;

		static CopyBufferSubData copyBufferSubData;
		static DrawArraysInstanced drawArraysInstanced;
		static DrawElementsInstanced drawElementsInstanced;
		static GetActiveUniformBlockIV getActiveUniformBlockiv;
		static GetActiveUniformBlockName getActiveUniformBlockName;
		static GetActiveUniformName getActiveUniformName;
		static GetActiveUniformsIV getActiveUniformsiv;
		static GetUniformBlockIndex getUniformBlockIndex;
		static GetUniformIndices getUniformIndices;
		static PrimitiveRestartIndex primitiveRestartIndex;
		static TexBuffer texBuffer;
		static UniformBlockBinding uniformBlockBinding;

		// Version 3.2

		static const Uint32 CONTEXT_CORE_PROFILE_BIT				  = 0x0001;
		static const Uint32 CONTEXT_COMPATIBILITY_PROFILE_BIT		  = 0x0002;
		static const Uint32 SYNC_FLUSH_COMMANDS_BIT					  = 0x0001;
		static const Uint32 LINES_ADJACENCY							  = 0x000A;
		static const Uint32 LINE_STRIP_ADJACENCY					  = 0x000B;
		static const Uint32 TRIANGLES_ADJACENCY						  = 0x000C;
		static const Uint32 TRIANGLE_STRIP_ADJACENCY				  = 0x000D;
		static const Uint32 PROGRAM_POINT_SIZE						  = 0x8642;
		static const Uint32 DEPTH_CLAMP								  = 0x864F;
		static const Uint32 TEXTURE_CUBE_MAP_SEAMLESS				  = 0x884F;
		static const Uint32 GEOMETRY_VERTICES_OUT					  = 0x8916;
		static const Uint32 GEOMETRY_INPUT_TYPE						  = 0x8917;
		static const Uint32 GEOMETRY_OUTPUT_TYPE					  = 0x8918;
		static const Uint32 MAX_GEOMETRY_TEXTURE_IMAGE_UNITS		  = 0x8C29;
		static const Uint32 FRAMEBUFFER_ATTACHMENT_LAYERED			  = 0x8DA7;
		static const Uint32 FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS	  = 0x8DA8;
		static const Uint32 GEOMETRY_SHADER							  = 0x8DD9;
		static const Uint32 MAX_GEOMETRY_UNIFORM_COMPONENTS			  = 0x8DDF;
		static const Uint32 MAX_GEOMETRY_OUTPUT_VERTICES			  = 0x8DE0;
		static const Uint32 MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS	  = 0x8DE1;
		static const Uint32 QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION  = 0x8E4C;
		static const Uint32 FIRST_VERTEX_CONVENTION					  = 0x8E4D;
		static const Uint32 LAST_VERTEX_CONVENTION					  = 0x8E4E;
		static const Uint32 PROVOKING_VERTEX						  = 0x8E4F;
		static const Uint32 SAMPLE_POSITION							  = 0x8E50;
		static const Uint32 SAMPLE_MASK								  = 0x8E51;
		static const Uint32 SAMPLE_MASK_VALUE						  = 0x8E52;
		static const Uint32 MAX_SAMPLE_MASK_WORDS					  = 0x8E59;
		static const Uint32 TEXTURE_2D_MULTISAMPLE					  = 0x9100;
		static const Uint32 PROXY_TEXTURE_2D_MULTISAMPLE			  = 0x9101;
		static const Uint32 TEXTURE_2D_MULTISAMPLE_ARRAY			  = 0x9102;
		static const Uint32 PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY		  = 0x9103;
		static const Uint32 TEXTURE_BINDING_2D_MULTISAMPLE			  = 0x9104;
		static const Uint32 TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY	  = 0x9105;
		static const Uint32 TEXTURE_SAMPLES							  = 0x9106;
		static const Uint32 TEXTURE_FIXED_SAMPLE_LOCATIONS			  = 0x9107;
		static const Uint32 SAMPLER_2D_MULTISAMPLE					  = 0x9108;
		static const Uint32 INT_SAMPLER_2D_MULTISAMPLE				  = 0x9109;
		static const Uint32 UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE		  = 0x910A;
		static const Uint32 SAMPLER_2D_MULTISAMPLE_ARRAY			  = 0x910B;
		static const Uint32 INT_SAMPLER_2D_MULTISAMPLE_ARRAY		  = 0x910C;
		static const Uint32 UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D;
		static const Uint32 MAX_COLOR_TEXTURE_SAMPLES				  = 0x910E;
		static const Uint32 MAX_DEPTH_TEXTURE_SAMPLES				  = 0x910F;
		static const Uint32 MAX_INTEGER_SAMPLES						  = 0x9110;
		static const Uint32 MAX_SERVER_WAIT_TIMEOUT					  = 0x9111;
		static const Uint32 OBJECT_TYPE								  = 0x9112;
		static const Uint32 SYNC_CONDITION							  = 0x9113;
		static const Uint32 SYNC_STATUS								  = 0x9114;
		static const Uint32 SYNC_FLAGS								  = 0x9115;
		static const Uint32 SYNC_FENCE								  = 0x9116;
		static const Uint32 SYNC_GPU_COMMANDS_COMPLETE				  = 0x9117;
		static const Uint32 UNSIGNALED								  = 0x9118;
		static const Uint32 SIGNALED								  = 0x9119;
		static const Uint32 ALREADY_SIGNALED						  = 0x911A;
		static const Uint32 TIMEOUT_EXPIRED							  = 0x911B;
		static const Uint32 CONDITION_SATISFIED						  = 0x911C;
		static const Uint32 WAIT_FAILED								  = 0x911D;
		static const Uint32 MAX_VERTEX_OUTPUT_COMPONENTS			  = 0x9122;
		static const Uint32 MAX_GEOMETRY_INPUT_COMPONENTS			  = 0x9123;
		static const Uint32 MAX_GEOMETRY_OUTPUT_COMPONENTS			  = 0x9124;
		static const Uint32 MAX_FRAGMENT_INPUT_COMPONENTS			  = 0x9125;
		static const Uint32 CONTEXT_PROFILE_MASK					  = 0x9126;
		static const Uint64 TIMEOUT_IGNORED							  = 0xFFFFFFFFFFFFFFFFull;

		static ClientWaitSync clientWaitSync;
		static DeleteSync deleteSync;
		static DrawElementsBaseVertex drawElementsBaseVertex;
		static DrawElementsInstancedBaseVertex drawElementsInstancedBaseVertex;
		static DrawRangeElementsBaseVertex drawRangeElementsBaseVertex;
		static FenceSync fenceSync;
		static FramebufferTexture framebufferTexture;
		static GetBufferParameterI64V getBufferParameteri64v;
		static GetInteger64I_V getInteger64i_v;
		static GetInteger64V getInteger64v;
		static GetMultisampleFV getMultisamplefv;
		static GetSyncIV getSynciv;
		static IsSync isSync;
		static MultiDrawElementsBaseVertex multiDrawElementsBaseVertex;
		static ProvokingVertex provokingVertex;
		static SampleMaskI sampleMaski;
		static TexImage2DMultisample texImage2DMultisample;
		static TexImage3DMultisample texImage3DMultisample;
		static WaitSync waitSync;

		// Version 3.3

		static const Uint32 TIME_ELAPSED				 = 0x88BF;
		static const Uint32 SRC1_COLOR					 = 0x88F9;
		static const Uint32 ONE_MINUS_SRC1_COLOR		 = 0x88FA;
		static const Uint32 ONE_MINUS_SRC1_ALPHA		 = 0x88FB;
		static const Uint32 MAX_DUAL_SOURCE_DRAW_BUFFERS = 0x88FC;
		static const Uint32 VERTEX_ATTRIB_ARRAY_DIVISOR	 = 0x88FE;
		static const Uint32 SAMPLER_BINDING				 = 0x8919;
		static const Uint32 ANY_SAMPLES_PASSED			 = 0x8C2F;
		static const Uint32 INT_2_10_10_10_REV			 = 0x8D9F;
		static const Uint32 TIMESTAMP					 = 0x8E28;
		static const Uint32 TEXTURE_SWIZZLE_R			 = 0x8E42;
		static const Uint32 TEXTURE_SWIZZLE_G			 = 0x8E43;
		static const Uint32 TEXTURE_SWIZZLE_B			 = 0x8E44;
		static const Uint32 TEXTURE_SWIZZLE_A			 = 0x8E45;
		static const Uint32 TEXTURE_SWIZZLE_RGBA		 = 0x8E46;
		static const Uint32 RGB10_A2UI					 = 0x906F;

		static BindFragDataLocationIndexed bindFragDataLocationIndexed;
		static BindSampler bindSampler;
		static DeleteSamplers deleteSamplers;
		static GenSamplers genSamplers;
		static GetFragDataIndex getFragDataIndex;
		static GetQueryObjectI64V getQueryObjecti64v;
		static GetQueryObjectUI64V getQueryObjectui64v;
		static GetSamplerParameterFV getSamplerParameterfv;
		static GetSamplerParameterIIV getSamplerParameterIiv;
		static GetSamplerParameterIUIV getSamplerParameterIuiv;
		static GetSamplerParameterIV getSamplerParameteriv;
		static IsSampler isSampler;
		static QueryCounter queryCounter;
		static SamplerParameterF samplerParameterf;
		static SamplerParameterFV samplerParameterfv;
		static SamplerParameterI samplerParameteri;
		static SamplerParameterIV samplerParameteriv;
		static SamplerParameterIIV samplerParameterIiv;
		static SamplerParameterIUIV samplerParameterIuiv;
		static VertexAttribDivisor vertexAttribDivisor;
		static VertexAttribP1UI vertexAttribP1ui;
		static VertexAttribP1UIV vertexAttribP1uiv;
		static VertexAttribP2UI vertexAttribP2ui;
		static VertexAttribP2UIV vertexAttribP2uiv;
		static VertexAttribP3UI vertexAttribP3ui;
		static VertexAttribP3UIV vertexAttribP3uiv;
		static VertexAttribP4UI vertexAttribP4ui;
		static VertexAttribP4UIV vertexAttribP4uiv;

		// Version 4.0

		static const Uint32 PATCHES											   = 0x000E;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER	   = 0x84F0;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1;
		static const Uint32 MAX_TESS_CONTROL_INPUT_COMPONENTS				   = 0x886C;
		static const Uint32 MAX_TESS_EVALUATION_INPUT_COMPONENTS			   = 0x886D;
		static const Uint32 GEOMETRY_SHADER_INVOCATIONS						   = 0x887F;
		static const Uint32 SAMPLE_SHADING									   = 0x8C36;
		static const Uint32 MIN_SAMPLE_SHADING_VALUE						   = 0x8C37;
		static const Uint32 ACTIVE_SUBROUTINES								   = 0x8DE5;
		static const Uint32 ACTIVE_SUBROUTINE_UNIFORMS						   = 0x8DE6;
		static const Uint32 MAX_SUBROUTINES									   = 0x8DE7;
		static const Uint32 MAX_SUBROUTINE_UNIFORM_LOCATIONS				   = 0x8DE8;
		static const Uint32 MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS	   = 0x8E1E;
		static const Uint32 MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS	   = 0x8E1F;
		static const Uint32 TRANSFORM_FEEDBACK								   = 0x8E22;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_PAUSED				   = 0x8E23;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_ACTIVE				   = 0x8E24;
		static const Uint32 TRANSFORM_FEEDBACK_BINDING						   = 0x8E25;
		static const Uint32 ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS				   = 0x8E47;
		static const Uint32 ACTIVE_SUBROUTINE_MAX_LENGTH					   = 0x8E48;
		static const Uint32 ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH			   = 0x8E49;
		static const Uint32 NUM_COMPATIBLE_SUBROUTINES						   = 0x8E4A;
		static const Uint32 COMPATIBLE_SUBROUTINES							   = 0x8E4B;
		static const Uint32 MAX_GEOMETRY_SHADER_INVOCATIONS					   = 0x8E5A;
		static const Uint32 MIN_FRAGMENT_INTERPOLATION_OFFSET				   = 0x8E5B;
		static const Uint32 MAX_FRAGMENT_INTERPOLATION_OFFSET				   = 0x8E5C;
		static const Uint32 FRAGMENT_INTERPOLATION_OFFSET_BITS				   = 0x8E5D;
		static const Uint32 MIN_PROGRAM_TEXTURE_GATHER_OFFSET				   = 0x8E5E;
		static const Uint32 MAX_PROGRAM_TEXTURE_GATHER_OFFSET				   = 0x8E5F;
		static const Uint32 MAX_TRANSFORM_FEEDBACK_BUFFERS					   = 0x8E70;
		static const Uint32 MAX_VERTEX_STREAMS								   = 0x8E71;
		static const Uint32 PATCH_VERTICES									   = 0x8E72;
		static const Uint32 PATCH_DEFAULT_INNER_LEVEL						   = 0x8E73;
		static const Uint32 PATCH_DEFAULT_OUTER_LEVEL						   = 0x8E74;
		static const Uint32 TESS_CONTROL_OUTPUT_VERTICES					   = 0x8E75;
		static const Uint32 TESS_GEN_MODE									   = 0x8E76;
		static const Uint32 TESS_GEN_SPACING								   = 0x8E77;
		static const Uint32 TESS_GEN_VERTEX_ORDER							   = 0x8E78;
		static const Uint32 TESS_GEN_POINT_MODE								   = 0x8E79;
		static const Uint32 ISOLINES										   = 0x8E7A;
		static const Uint32 FRACTIONAL_ODD									   = 0x8E7B;
		static const Uint32 FRACTIONAL_EVEN									   = 0x8E7C;
		static const Uint32 MAX_PATCH_VERTICES								   = 0x8E7D;
		static const Uint32 MAX_TESS_GEN_LEVEL								   = 0x8E7E;
		static const Uint32 MAX_TESS_CONTROL_UNIFORM_COMPONENTS				   = 0x8E7F;
		static const Uint32 MAX_TESS_EVALUATION_UNIFORM_COMPONENTS			   = 0x8E80;
		static const Uint32 MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS			   = 0x8E81;
		static const Uint32 MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS			   = 0x8E82;
		static const Uint32 MAX_TESS_CONTROL_OUTPUT_COMPONENTS				   = 0x8E83;
		static const Uint32 MAX_TESS_PATCH_COMPONENTS						   = 0x8E84;
		static const Uint32 MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS		   = 0x8E85;
		static const Uint32 MAX_TESS_EVALUATION_OUTPUT_COMPONENTS			   = 0x8E86;
		static const Uint32 TESS_EVALUATION_SHADER							   = 0x8E87;
		static const Uint32 TESS_CONTROL_SHADER								   = 0x8E88;
		static const Uint32 MAX_TESS_CONTROL_UNIFORM_BLOCKS					   = 0x8E89;
		static const Uint32 MAX_TESS_EVALUATION_UNIFORM_BLOCKS				   = 0x8E8A;
		static const Uint32 DRAW_INDIRECT_BUFFER							   = 0x8F3F;
		static const Uint32 DRAW_INDIRECT_BUFFER_BINDING					   = 0x8F43;
		static const Uint32 DOUBLE_MAT2										   = 0x8F46;
		static const Uint32 DOUBLE_MAT3										   = 0x8F47;
		static const Uint32 DOUBLE_MAT4										   = 0x8F48;
		static const Uint32 DOUBLE_MAT2x3									   = 0x8F49;
		static const Uint32 DOUBLE_MAT2x4									   = 0x8F4A;
		static const Uint32 DOUBLE_MAT3x2									   = 0x8F4B;
		static const Uint32 DOUBLE_MAT3x4									   = 0x8F4C;
		static const Uint32 DOUBLE_MAT4x2									   = 0x8F4D;
		static const Uint32 DOUBLE_MAT4x3									   = 0x8F4E;
		static const Uint32 DOUBLE_VEC2										   = 0x8FFC;
		static const Uint32 DOUBLE_VEC3										   = 0x8FFD;
		static const Uint32 DOUBLE_VEC4										   = 0x8FFE;
		static const Uint32 TEXTURE_CUBE_MAP_ARRAY							   = 0x9009;
		static const Uint32 TEXTURE_BINDING_CUBE_MAP_ARRAY					   = 0x900A;
		static const Uint32 PROXY_TEXTURE_CUBE_MAP_ARRAY					   = 0x900B;
		static const Uint32 SAMPLER_CUBE_MAP_ARRAY							   = 0x900C;
		static const Uint32 SAMPLER_CUBE_MAP_ARRAY_SHADOW					   = 0x900D;
		static const Uint32 INT_SAMPLER_CUBE_MAP_ARRAY						   = 0x900E;
		static const Uint32 UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY				   = 0x900F;

		static BeginQueryIndexed beginQueryIndexed;
		static BindTransformFeedback bindTransformFeedback;
		static BlendEquationI blendEquationi;
		static BlendEquationSeparateI blendEquationSeparatei;
		static BlendFuncI blendFunci;
		static BlendFuncSeparateI blendFuncSeparatei;
		static DeleteTransformFeedbacks deleteTransformFeedbacks;
		static DrawArraysIndirect drawArraysIndirect;
		static DrawElementsIndirect drawElementsIndirect;
		static DrawTransformFeedback drawTransformFeedback;
		static DrawTransformFeedbackStream drawTransformFeedbackStream;
		static EndQueryIndexed endQueryIndexed;
		static GenTransformFeedbacks genTransformFeedbacks;
		static GetActiveSubroutineName getActiveSubroutineName;
		static GetActiveSubroutineUniformIV getActiveSubroutineUniformiv;
		static GetActiveSubroutineUniformName getActiveSubroutineUniformName;
		static GetProgramStageIV getProgramStageiv;
		static GetQueryIndexedIV getQueryIndexediv;
		static GetSubroutineIndex getSubroutineIndex;
		static GetSubroutineUniformLocation getSubroutineUniformLocation;
		static GetUniformDV getUniformdv;
		static GetUniformSubroutineUIV getUniformSubroutineuiv;
		static IsTransformFeedback isTransformFeedback;
		static MinSampleShading minSampleShading;
		static PatchParameterFV patchParameterfv;
		static PatchParameterI patchParameteri;
		static PauseTransformFeedback pauseTransformFeedback;
		static ResumeTransformFeedback resumeTransformFeedback;
		static Uniform1D uniform1d;
		static Uniform1DV uniform1dv;
		static Uniform2D uniform2d;
		static Uniform2DV uniform2dv;
		static Uniform3D uniform3d;
		static Uniform3DV uniform3dv;
		static Uniform4D uniform4d;
		static Uniform4DV uniform4dv;
		static UniformMatrix2DV uniformMatrix2dv;
		static UniformMatrix2X3DV uniformMatrix2x3dv;
		static UniformMatrix2X4DV uniformMatrix2x4dv;
		static UniformMatrix3DV uniformMatrix3dv;
		static UniformMatrix3X2DV uniformMatrix3x2dv;
		static UniformMatrix3X4DV uniformMatrix3x4dv;
		static UniformMatrix4DV uniformMatrix4dv;
		static UniformMatrix4X2DV uniformMatrix4x2dv;
		static UniformMatrix4X3DV uniformMatrix4x3dv;
		static UniformSubroutineSUIV uniformSubroutinesuiv;

		// Version 4.1

		static const Uint32 VERTEX_SHADER_BIT				 = 0x00000001;
		static const Uint32 FRAGMENT_SHADER_BIT				 = 0x00000002;
		static const Uint32 GEOMETRY_SHADER_BIT				 = 0x00000004;
		static const Uint32 TESS_CONTROL_SHADER_BIT			 = 0x00000008;
		static const Uint32 TESS_EVALUATION_SHADER_BIT		 = 0x00000010;
		static const Uint32 ALL_SHADER_BITS					 = 0xFFFFFFFF;
		static const Uint32 FIXED							 = 0x140C;
		static const Uint32 PROGRAM_BINARY_RETRIEVABLE_HINT	 = 0x8257;
		static const Uint32 PROGRAM_SEPARABLE				 = 0x8258;
		static const Uint32 ACTIVE_PROGRAM					 = 0x8259;
		static const Uint32 PROGRAM_PIPELINE_BINDING		 = 0x825A;
		static const Uint32 MAX_VIEWPORTS					 = 0x825B;
		static const Uint32 VIEWPORT_SUBPIXEL_BITS			 = 0x825C;
		static const Uint32 VIEWPORT_BOUNDS_RANGE			 = 0x825D;
		static const Uint32 LAYER_PROVOKING_VERTEX			 = 0x825E;
		static const Uint32 VIEWPORT_INDEX_PROVOKING_VERTEX	 = 0x825F;
		static const Uint32 UNDEFINED_VERTEX				 = 0x8260;
		static const Uint32 PROGRAM_BINARY_LENGTH			 = 0x8741;
		static const Uint32 NUM_PROGRAM_BINARY_FORMATS		 = 0x87FE;
		static const Uint32 PROGRAM_BINARY_FORMATS			 = 0x87FF;
		static const Uint32 IMPLEMENTATION_COLOR_READ_TYPE	 = 0x8B9A;
		static const Uint32 IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;
		static const Uint32 RGB565							 = 0x8D62;
		static const Uint32 LOW_FLOAT						 = 0x8DF0;
		static const Uint32 MEDIUM_FLOAT					 = 0x8DF1;
		static const Uint32 HIGH_FLOAT						 = 0x8DF2;
		static const Uint32 LOW_INT							 = 0x8DF3;
		static const Uint32 MEDIUM_INT						 = 0x8DF4;
		static const Uint32 HIGH_INT						 = 0x8DF5;
		static const Uint32 SHADER_BINARY_FORMATS			 = 0x8DF8;
		static const Uint32 NUM_SHADER_BINARY_FORMATS		 = 0x8DF9;
		static const Uint32 SHADER_COMPILER					 = 0x8DFA;
		static const Uint32 MAX_VERTEX_UNIFORM_VECTORS		 = 0x8DFB;
		static const Uint32 MAX_VARYING_VECTORS				 = 0x8DFC;
		static const Uint32 MAX_FRAGMENT_UNIFORM_VECTORS	 = 0x8DFD;

		static ActiveShaderProgram activeShaderProgram;
		static BindProgramPipeline bindProgramPipeline;
		static ClearDepthF clearDepthf;
		static CreateShaderProgramV createShaderProgramv;
		static DeleteProgramPipelines deleteProgramPipelines;
		static DepthRangeArrayV depthRangeArrayv;
		static DepthRangeF depthRangef;
		static DepthRangeIndexed depthRangeIndexed;
		static GenProgramPipelines genProgramPipelines;
		static GetDoubleI_V getDoublei_v;
		static GetFloatI_V getFloati_v;
		static GetProgramBinary getProgramBinary;
		static GetProgramPipelineInfoLog getProgramPipelineInfoLog;
		static GetProgramPipelineIV getProgramPipelineiv;
		static GetShaderPrecisionFormat getShaderPrecisionFormat;
		static GetVertexAttribLDV getVertexAttribLdv;
		static IsProgramPipeline isProgramPipeline;
		static ProgramBinary programBinary;
		static ProgramParameterI programParameteri;
		static ProgramUniform1D programUniform1d;
		static ProgramUniform1DV programUniform1dv;
		static ProgramUniform1F programUniform1f;
		static ProgramUniform1FV programUniform1fv;
		static ProgramUniform1I programUniform1i;
		static ProgramUniform1IV programUniform1iv;
		static ProgramUniform1UI programUniform1ui;
		static ProgramUniform1UIV programUniform1uiv;
		static ProgramUniform2D programUniform2d;
		static ProgramUniform2DV programUniform2dv;
		static ProgramUniform2F programUniform2f;
		static ProgramUniform2FV programUniform2fv;
		static ProgramUniform2I programUniform2i;
		static ProgramUniform2IV programUniform2iv;
		static ProgramUniform2UI programUniform2ui;
		static ProgramUniform2UIV programUniform2uiv;
		static ProgramUniform3D programUniform3d;
		static ProgramUniform3DV programUniform3dv;
		static ProgramUniform3F programUniform3f;
		static ProgramUniform3FV programUniform3fv;
		static ProgramUniform3I programUniform3i;
		static ProgramUniform3IV programUniform3iv;
		static ProgramUniform3UI programUniform3ui;
		static ProgramUniform3UIV programUniform3uiv;
		static ProgramUniform4D programUniform4d;
		static ProgramUniform4DV programUniform4dv;
		static ProgramUniform4F programUniform4f;
		static ProgramUniform4FV programUniform4fv;
		static ProgramUniform4I programUniform4i;
		static ProgramUniform4IV programUniform4iv;
		static ProgramUniform4UI programUniform4ui;
		static ProgramUniform4UIV programUniform4uiv;
		static ProgramUniformMatrix2DV programUniformMatrix2dv;
		static ProgramUniformMatrix2FV programUniformMatrix2fv;
		static ProgramUniformMatrix2X3DV programUniformMatrix2x3dv;
		static ProgramUniformMatrix2X3FV programUniformMatrix2x3fv;
		static ProgramUniformMatrix2X4DV programUniformMatrix2x4dv;
		static ProgramUniformMatrix2X4FV programUniformMatrix2x4fv;
		static ProgramUniformMatrix3DV programUniformMatrix3dv;
		static ProgramUniformMatrix3FV programUniformMatrix3fv;
		static ProgramUniformMatrix3X2DV programUniformMatrix3x2dv;
		static ProgramUniformMatrix3X2FV programUniformMatrix3x2fv;
		static ProgramUniformMatrix3X4DV programUniformMatrix3x4dv;
		static ProgramUniformMatrix3X4FV programUniformMatrix3x4fv;
		static ProgramUniformMatrix4DV programUniformMatrix4dv;
		static ProgramUniformMatrix4FV programUniformMatrix4fv;
		static ProgramUniformMatrix4X2DV programUniformMatrix4x2dv;
		static ProgramUniformMatrix4X2FV programUniformMatrix4x2fv;
		static ProgramUniformMatrix4X3DV programUniformMatrix4x3dv;
		static ProgramUniformMatrix4X3FV programUniformMatrix4x3fv;
		static ReleaseShaderCompiler releaseShaderCompiler;
		static ShaderBinary shaderBinary;
		static ScissorArrayV scissorArrayv;
		static ScissorIndexed scissorIndexed;
		static ScissorIndexedV scissorIndexedv;
		static UseProgramStages useProgramStages;
		static ValidateProgramPipeline validateProgramPipeline;
		static VertexAttribL1D vertexAttribL1d;
		static VertexAttribL1DV vertexAttribL1dv;
		static VertexAttribL2D vertexAttribL2d;
		static VertexAttribL2DV vertexAttribL2dv;
		static VertexAttribL3D vertexAttribL3d;
		static VertexAttribL3DV vertexAttribL3dv;
		static VertexAttribL4D vertexAttribL4d;
		static VertexAttribL4DV vertexAttribL4dv;
		static VertexAttribLPointer vertexAttribLPointer;
		static ViewportArrayV viewportArrayv;
		static ViewportIndexedF viewportIndexedf;
		static ViewportIndexedFV viewportIndexedfv;

		// Version 4.2

		static const Uint32 VERTEX_ATTRIB_ARRAY_BARRIER_BIT							   = 0x00000001;
		static const Uint32 ELEMENT_ARRAY_BARRIER_BIT								   = 0x00000002;
		static const Uint32 UNIFORM_BARRIER_BIT										   = 0x00000004;
		static const Uint32 TEXTURE_FETCH_BARRIER_BIT								   = 0x00000008;
		static const Uint32 SHADER_IMAGE_ACCESS_BARRIER_BIT							   = 0x00000020;
		static const Uint32 COMMAND_BARRIER_BIT										   = 0x00000040;
		static const Uint32 PIXEL_BUFFER_BARRIER_BIT								   = 0x00000080;
		static const Uint32 TEXTURE_UPDATE_BARRIER_BIT								   = 0x00000100;
		static const Uint32 BUFFER_UPDATE_BARRIER_BIT								   = 0x00000200;
		static const Uint32 FRAMEBUFFER_BARRIER_BIT									   = 0x00000400;
		static const Uint32 TRANSFORM_FEEDBACK_BARRIER_BIT							   = 0x00000800;
		static const Uint32 ATOMIC_COUNTER_BARRIER_BIT								   = 0x00001000;
		static const Uint32 ALL_BARRIER_BITS										   = 0xFFFFFFFF;
		static const Uint32 TRANSFORM_FEEDBACK_ACTIVE								   = 0x8E24;
		static const Uint32 TRANSFORM_FEEDBACK_PAUSED								   = 0x8E23;
		static const Uint32 COMPRESSED_RGBA_BPTC_UNORM								   = 0x8E8C;
		static const Uint32 COMPRESSED_SRGB_ALPHA_BPTC_UNORM						   = 0x8E8D;
		static const Uint32 COMPRESSED_RGB_BPTC_SIGNED_FLOAT						   = 0x8E8E;
		static const Uint32 COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT						   = 0x8E8F;
		static const Uint32 COPY_READ_BUFFER_BINDING								   = 0x8F36;
		static const Uint32 COPY_WRITE_BUFFER_BINDING								   = 0x8F37;
		static const Uint32 MAX_IMAGE_UNITS											   = 0x8F38;
		static const Uint32 MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS			   = 0x8F39;
		static const Uint32 IMAGE_BINDING_NAME										   = 0x8F3A;
		static const Uint32 IMAGE_BINDING_LEVEL										   = 0x8F3B;
		static const Uint32 IMAGE_BINDING_LAYERED									   = 0x8F3C;
		static const Uint32 IMAGE_BINDING_LAYER										   = 0x8F3D;
		static const Uint32 IMAGE_BINDING_ACCESS									   = 0x8F3E;
		static const Uint32 IMAGE_1D												   = 0x904C;
		static const Uint32 IMAGE_2D												   = 0x904D;
		static const Uint32 IMAGE_3D												   = 0x904E;
		static const Uint32 IMAGE_2D_RECT											   = 0x904F;
		static const Uint32 IMAGE_CUBE												   = 0x9050;
		static const Uint32 IMAGE_BUFFER											   = 0x9051;
		static const Uint32 IMAGE_1D_ARRAY											   = 0x9052;
		static const Uint32 IMAGE_2D_ARRAY											   = 0x9053;
		static const Uint32 IMAGE_CUBE_MAP_ARRAY									   = 0x9054;
		static const Uint32 IMAGE_2D_MULTISAMPLE									   = 0x9055;
		static const Uint32 IMAGE_2D_MULTISAMPLE_ARRAY								   = 0x9056;
		static const Uint32 INT_IMAGE_1D											   = 0x9057;
		static const Uint32 INT_IMAGE_2D											   = 0x9058;
		static const Uint32 INT_IMAGE_3D											   = 0x9059;
		static const Uint32 INT_IMAGE_2D_RECT										   = 0x905A;
		static const Uint32 INT_IMAGE_CUBE											   = 0x905B;
		static const Uint32 INT_IMAGE_BUFFER										   = 0x905C;
		static const Uint32 INT_IMAGE_1D_ARRAY										   = 0x905D;
		static const Uint32 INT_IMAGE_2D_ARRAY										   = 0x905E;
		static const Uint32 INT_IMAGE_CUBE_MAP_ARRAY								   = 0x905F;
		static const Uint32 INT_IMAGE_2D_MULTISAMPLE								   = 0x9060;
		static const Uint32 INT_IMAGE_2D_MULTISAMPLE_ARRAY							   = 0x9061;
		static const Uint32 UNSIGNED_INT_IMAGE_1D									   = 0x9062;
		static const Uint32 UNSIGNED_INT_IMAGE_2D									   = 0x9063;
		static const Uint32 UNSIGNED_INT_IMAGE_3D									   = 0x9064;
		static const Uint32 UNSIGNED_INT_IMAGE_2D_RECT								   = 0x9065;
		static const Uint32 UNSIGNED_INT_IMAGE_CUBE									   = 0x9066;
		static const Uint32 UNSIGNED_INT_IMAGE_BUFFER								   = 0x9067;
		static const Uint32 UNSIGNED_INT_IMAGE_1D_ARRAY								   = 0x9068;
		static const Uint32 UNSIGNED_INT_IMAGE_2D_ARRAY								   = 0x9069;
		static const Uint32 UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY						   = 0x906A;
		static const Uint32 UNSIGNED_INT_IMAGE_2D_MULTISAMPLE						   = 0x906B;
		static const Uint32 UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY					   = 0x906C;
		static const Uint32 MAX_IMAGE_SAMPLES										   = 0x906D;
		static const Uint32 IMAGE_BINDING_FORMAT									   = 0x906E;
		static const Uint32 MIN_MAP_BUFFER_ALIGNMENT								   = 0x90BC;
		static const Uint32 IMAGE_FORMAT_COMPATIBILITY_TYPE							   = 0x90C7;
		static const Uint32 IMAGE_FORMAT_COMPATIBILITY_BY_SIZE						   = 0x90C8;
		static const Uint32 IMAGE_FORMAT_COMPATIBILITY_BY_CLASS						   = 0x90C9;
		static const Uint32 MAX_VERTEX_IMAGE_UNIFORMS								   = 0x90CA;
		static const Uint32 MAX_TESS_CONTROL_IMAGE_UNIFORMS							   = 0x90CB;
		static const Uint32 MAX_TESS_EVALUATION_IMAGE_UNIFORMS						   = 0x90CC;
		static const Uint32 MAX_GEOMETRY_IMAGE_UNIFORMS								   = 0x90CD;
		static const Uint32 MAX_FRAGMENT_IMAGE_UNIFORMS								   = 0x90CE;
		static const Uint32 MAX_COMBINED_IMAGE_UNIFORMS								   = 0x90CF;
		static const Uint32 UNPACK_COMPRESSED_BLOCK_WIDTH							   = 0x9127;
		static const Uint32 UNPACK_COMPRESSED_BLOCK_HEIGHT							   = 0x9128;
		static const Uint32 UNPACK_COMPRESSED_BLOCK_DEPTH							   = 0x9129;
		static const Uint32 UNPACK_COMPRESSED_BLOCK_SIZE							   = 0x912A;
		static const Uint32 PACK_COMPRESSED_BLOCK_WIDTH								   = 0x912B;
		static const Uint32 PACK_COMPRESSED_BLOCK_HEIGHT							   = 0x912C;
		static const Uint32 PACK_COMPRESSED_BLOCK_DEPTH								   = 0x912D;
		static const Uint32 PACK_COMPRESSED_BLOCK_SIZE								   = 0x912E;
		static const Uint32 TEXTURE_IMMUTABLE_FORMAT								   = 0x912F;
		static const Uint32 ATOMIC_COUNTER_BUFFER									   = 0x92C0;
		static const Uint32 ATOMIC_COUNTER_BUFFER_BINDING							   = 0x92C1;
		static const Uint32 ATOMIC_COUNTER_BUFFER_START								   = 0x92C2;
		static const Uint32 ATOMIC_COUNTER_BUFFER_SIZE								   = 0x92C3;
		static const Uint32 ATOMIC_COUNTER_BUFFER_DATA_SIZE							   = 0x92C4;
		static const Uint32 ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS			   = 0x92C5;
		static const Uint32 ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES		   = 0x92C6;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER		   = 0x92C7;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER	   = 0x92C8;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x92C9;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER		   = 0x92CA;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER		   = 0x92CB;
		static const Uint32 MAX_VERTEX_ATOMIC_COUNTER_BUFFERS						   = 0x92CC;
		static const Uint32 MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS					   = 0x92CD;
		static const Uint32 MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS				   = 0x92CE;
		static const Uint32 MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS						   = 0x92CF;
		static const Uint32 MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS						   = 0x92D0;
		static const Uint32 MAX_COMBINED_ATOMIC_COUNTER_BUFFERS						   = 0x92D1;
		static const Uint32 MAX_VERTEX_ATOMIC_COUNTERS								   = 0x92D2;
		static const Uint32 MAX_TESS_CONTROL_ATOMIC_COUNTERS						   = 0x92D3;
		static const Uint32 MAX_TESS_EVALUATION_ATOMIC_COUNTERS						   = 0x92D4;
		static const Uint32 MAX_GEOMETRY_ATOMIC_COUNTERS							   = 0x92D5;
		static const Uint32 MAX_FRAGMENT_ATOMIC_COUNTERS							   = 0x92D6;
		static const Uint32 MAX_COMBINED_ATOMIC_COUNTERS							   = 0x92D7;
		static const Uint32 MAX_ATOMIC_COUNTER_BUFFER_SIZE							   = 0x92D8;
		static const Uint32 ACTIVE_ATOMIC_COUNTER_BUFFERS							   = 0x92D9;
		static const Uint32 UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX						   = 0x92DA;
		static const Uint32 UNSIGNED_INT_ATOMIC_COUNTER								   = 0x92DB;
		static const Uint32 MAX_ATOMIC_COUNTER_BUFFER_BINDINGS						   = 0x92DC;
		static const Uint32 NUM_SAMPLE_COUNTS										   = 0x9380;

		static BindImageTexture bindImageTexture;
		static DrawArraysInstancedBaseInstance drawArraysInstancedBaseInstance;
		static DrawElementsInstancedBaseInstance drawElementsInstancedBaseInstance;
		static DrawElementsInstancedBaseVertexBaseInstance drawElementsInstancedBaseVertexBaseInstance;
		static DrawTransformFeedbackInstanced drawTransformFeedbackInstanced;
		static DrawTransformFeedbackStreamInstanced drawTransformFeedbackStreamInstanced;
		static GetActiveAtomicCounterBufferIV getActiveAtomicCounterBufferiv;
		static GetInternalformatIV getInternalformativ;
		static MemoryBarrier memoryBarrier;
		static TexStorage1D texStorage1D;
		static TexStorage2D texStorage2D;
		static TexStorage3D texStorage3D;

		// Version 4.3

		static const Uint32 CONTEXT_FLAG_DEBUG_BIT							   = 0x00000002;
		static const Uint32 COMPUTE_SHADER_BIT								   = 0x00000020;
		static const Uint32 SHADER_STORAGE_BARRIER_BIT						   = 0x00002000;
		static const Uint32 DEBUG_OUTPUT_SYNCHRONOUS						   = 0x8242;
		static const Uint32 DEBUG_NEXT_LOGGED_MESSAGE_LENGTH				   = 0x8243;
		static const Uint32 DEBUG_CALLBACK_FUNCTION							   = 0x8244;
		static const Uint32 DEBUG_CALLBACK_USER_PARAM						   = 0x8245;
		static const Uint32 DEBUG_SOURCE_API								   = 0x8246;
		static const Uint32 DEBUG_SOURCE_WINDOW_SYSTEM						   = 0x8247;
		static const Uint32 DEBUG_SOURCE_SHADER_COMPILER					   = 0x8248;
		static const Uint32 DEBUG_SOURCE_THIRD_PARTY						   = 0x8249;
		static const Uint32 DEBUG_SOURCE_APPLICATION						   = 0x824A;
		static const Uint32 DEBUG_SOURCE_OTHER								   = 0x824B;
		static const Uint32 DEBUG_TYPE_ERROR								   = 0x824C;
		static const Uint32 DEBUG_TYPE_DEPRECATED_BEHAVIOR					   = 0x824D;
		static const Uint32 DEBUG_TYPE_UNDEFINED_BEHAVIOR					   = 0x824E;
		static const Uint32 DEBUG_TYPE_PORTABILITY							   = 0x824F;
		static const Uint32 DEBUG_TYPE_PERFORMANCE							   = 0x8250;
		static const Uint32 DEBUG_TYPE_OTHER								   = 0x8251;
		static const Uint32 MAX_COMPUTE_SHARED_MEMORY_SIZE					   = 0x8262;
		static const Uint32 MAX_COMPUTE_UNIFORM_COMPONENTS					   = 0x8263;
		static const Uint32 MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS				   = 0x8264;
		static const Uint32 MAX_COMPUTE_ATOMIC_COUNTERS						   = 0x8265;
		static const Uint32 MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS			   = 0x8266;
		static const Uint32 COMPUTE_WORK_GROUP_SIZE							   = 0x8267;
		static const Uint32 DEBUG_TYPE_MARKER								   = 0x8268;
		static const Uint32 DEBUG_TYPE_PUSH_GROUP							   = 0x8269;
		static const Uint32 DEBUG_TYPE_POP_GROUP							   = 0x826A;
		static const Uint32 DEBUG_SEVERITY_NOTIFICATION						   = 0x826B;
		static const Uint32 MAX_DEBUG_GROUP_STACK_DEPTH						   = 0x826C;
		static const Uint32 DEBUG_GROUP_STACK_DEPTH							   = 0x826D;
		static const Uint32 MAX_UNIFORM_LOCATIONS							   = 0x826E;
		static const Uint32 INTERNALFORMAT_SUPPORTED						   = 0x826F;
		static const Uint32 INTERNALFORMAT_PREFERRED						   = 0x8270;
		static const Uint32 INTERNALFORMAT_RED_SIZE							   = 0x8271;
		static const Uint32 INTERNALFORMAT_GREEN_SIZE						   = 0x8272;
		static const Uint32 INTERNALFORMAT_BLUE_SIZE						   = 0x8273;
		static const Uint32 INTERNALFORMAT_ALPHA_SIZE						   = 0x8274;
		static const Uint32 INTERNALFORMAT_DEPTH_SIZE						   = 0x8275;
		static const Uint32 INTERNALFORMAT_STENCIL_SIZE						   = 0x8276;
		static const Uint32 INTERNALFORMAT_SHARED_SIZE						   = 0x8277;
		static const Uint32 INTERNALFORMAT_RED_TYPE							   = 0x8278;
		static const Uint32 INTERNALFORMAT_GREEN_TYPE						   = 0x8279;
		static const Uint32 INTERNALFORMAT_BLUE_TYPE						   = 0x827A;
		static const Uint32 INTERNALFORMAT_ALPHA_TYPE						   = 0x827B;
		static const Uint32 INTERNALFORMAT_DEPTH_TYPE						   = 0x827C;
		static const Uint32 INTERNALFORMAT_STENCIL_TYPE						   = 0x827D;
		static const Uint32 MAX_WIDTH										   = 0x827E;
		static const Uint32 MAX_HEIGHT										   = 0x827F;
		static const Uint32 MAX_DEPTH										   = 0x8280;
		static const Uint32 MAX_LAYERS										   = 0x8281;
		static const Uint32 MAX_COMBINED_DIMENSIONS							   = 0x8282;
		static const Uint32 COLOR_COMPONENTS								   = 0x8283;
		static const Uint32 DEPTH_COMPONENTS								   = 0x8284;
		static const Uint32 STENCIL_COMPONENTS								   = 0x8285;
		static const Uint32 COLOR_RENDERABLE								   = 0x8286;
		static const Uint32 DEPTH_RENDERABLE								   = 0x8287;
		static const Uint32 STENCIL_RENDERABLE								   = 0x8288;
		static const Uint32 FRAMEBUFFER_RENDERABLE							   = 0x8289;
		static const Uint32 FRAMEBUFFER_RENDERABLE_LAYERED					   = 0x828A;
		static const Uint32 FRAMEBUFFER_BLEND								   = 0x828B;
		static const Uint32 READ_PIXELS										   = 0x828C;
		static const Uint32 READ_PIXELS_FORMAT								   = 0x828D;
		static const Uint32 READ_PIXELS_TYPE								   = 0x828E;
		static const Uint32 TEXTURE_IMAGE_FORMAT							   = 0x828F;
		static const Uint32 TEXTURE_IMAGE_TYPE								   = 0x8290;
		static const Uint32 GET_TEXTURE_IMAGE_FORMAT						   = 0x8291;
		static const Uint32 GET_TEXTURE_IMAGE_TYPE							   = 0x8292;
		static const Uint32 MIPMAP											   = 0x8293;
		static const Uint32 MANUAL_GENERATE_MIPMAP							   = 0x8294;
		static const Uint32 AUTO_GENERATE_MIPMAP							   = 0x8295;
		static const Uint32 COLOR_ENCODING									   = 0x8296;
		static const Uint32 SRGB_READ										   = 0x8297;
		static const Uint32 SRGB_WRITE										   = 0x8298;
		static const Uint32 FILTER											   = 0x829A;
		static const Uint32 VERTEX_TEXTURE									   = 0x829B;
		static const Uint32 TESS_CONTROL_TEXTURE							   = 0x829C;
		static const Uint32 TESS_EVALUATION_TEXTURE							   = 0x829D;
		static const Uint32 GEOMETRY_TEXTURE								   = 0x829E;
		static const Uint32 FRAGMENT_TEXTURE								   = 0x829F;
		static const Uint32 COMPUTE_TEXTURE									   = 0x82A0;
		static const Uint32 TEXTURE_SHADOW									   = 0x82A1;
		static const Uint32 TEXTURE_GATHER									   = 0x82A2;
		static const Uint32 TEXTURE_GATHER_SHADOW							   = 0x82A3;
		static const Uint32 SHADER_IMAGE_LOAD								   = 0x82A4;
		static const Uint32 SHADER_IMAGE_STORE								   = 0x82A5;
		static const Uint32 SHADER_IMAGE_ATOMIC								   = 0x82A6;
		static const Uint32 IMAGE_TEXEL_SIZE								   = 0x82A7;
		static const Uint32 IMAGE_COMPATIBILITY_CLASS						   = 0x82A8;
		static const Uint32 IMAGE_PIXEL_FORMAT								   = 0x82A9;
		static const Uint32 IMAGE_PIXEL_TYPE								   = 0x82AA;
		static const Uint32 SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST				   = 0x82AC;
		static const Uint32 SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST			   = 0x82AD;
		static const Uint32 SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE			   = 0x82AE;
		static const Uint32 SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE			   = 0x82AF;
		static const Uint32 TEXTURE_COMPRESSED_BLOCK_WIDTH					   = 0x82B1;
		static const Uint32 TEXTURE_COMPRESSED_BLOCK_HEIGHT					   = 0x82B2;
		static const Uint32 TEXTURE_COMPRESSED_BLOCK_SIZE					   = 0x82B3;
		static const Uint32 CLEAR_BUFFER									   = 0x82B4;
		static const Uint32 TEXTURE_VIEW									   = 0x82B5;
		static const Uint32 VIEW_COMPATIBILITY_CLASS						   = 0x82B6;
		static const Uint32 FULL_SUPPORT									   = 0x82B7;
		static const Uint32 CAVEAT_SUPPORT									   = 0x82B8;
		static const Uint32 IMAGE_CLASS_4_X_32								   = 0x82B9;
		static const Uint32 IMAGE_CLASS_2_X_32								   = 0x82BA;
		static const Uint32 IMAGE_CLASS_1_X_32								   = 0x82BB;
		static const Uint32 IMAGE_CLASS_4_X_16								   = 0x82BC;
		static const Uint32 IMAGE_CLASS_2_X_16								   = 0x82BD;
		static const Uint32 IMAGE_CLASS_1_X_16								   = 0x82BE;
		static const Uint32 IMAGE_CLASS_4_X_8								   = 0x82BF;
		static const Uint32 IMAGE_CLASS_2_X_8								   = 0x82C0;
		static const Uint32 IMAGE_CLASS_1_X_8								   = 0x82C1;
		static const Uint32 IMAGE_CLASS_11_11_10							   = 0x82C2;
		static const Uint32 IMAGE_CLASS_10_10_10_2							   = 0x82C3;
		static const Uint32 VIEW_CLASS_128_BITS								   = 0x82C4;
		static const Uint32 VIEW_CLASS_96_BITS								   = 0x82C5;
		static const Uint32 VIEW_CLASS_64_BITS								   = 0x82C6;
		static const Uint32 VIEW_CLASS_48_BITS								   = 0x82C7;
		static const Uint32 VIEW_CLASS_32_BITS								   = 0x82C8;
		static const Uint32 VIEW_CLASS_24_BITS								   = 0x82C9;
		static const Uint32 VIEW_CLASS_16_BITS								   = 0x82CA;
		static const Uint32 VIEW_CLASS_8_BITS								   = 0x82CB;
		static const Uint32 VIEW_CLASS_S3TC_DXT1_RGB						   = 0x82CC;
		static const Uint32 VIEW_CLASS_S3TC_DXT1_RGBA						   = 0x82CD;
		static const Uint32 VIEW_CLASS_S3TC_DXT3_RGBA						   = 0x82CE;
		static const Uint32 VIEW_CLASS_S3TC_DXT5_RGBA						   = 0x82CF;
		static const Uint32 VIEW_CLASS_RGTC1_RED							   = 0x82D0;
		static const Uint32 VIEW_CLASS_RGTC2_RG								   = 0x82D1;
		static const Uint32 VIEW_CLASS_BPTC_UNORM							   = 0x82D2;
		static const Uint32 VIEW_CLASS_BPTC_FLOAT							   = 0x82D3;
		static const Uint32 VERTEX_ATTRIB_BINDING							   = 0x82D4;
		static const Uint32 VERTEX_ATTRIB_RELATIVE_OFFSET					   = 0x82D5;
		static const Uint32 VERTEX_BINDING_DIVISOR							   = 0x82D6;
		static const Uint32 VERTEX_BINDING_OFFSET							   = 0x82D7;
		static const Uint32 VERTEX_BINDING_STRIDE							   = 0x82D8;
		static const Uint32 MAX_VERTEX_ATTRIB_RELATIVE_OFFSET				   = 0x82D9;
		static const Uint32 MAX_VERTEX_ATTRIB_BINDINGS						   = 0x82DA;
		static const Uint32 TEXTURE_VIEW_MIN_LEVEL							   = 0x82DB;
		static const Uint32 TEXTURE_VIEW_NUM_LEVELS							   = 0x82DC;
		static const Uint32 TEXTURE_VIEW_MIN_LAYER							   = 0x82DD;
		static const Uint32 TEXTURE_VIEW_NUM_LAYERS							   = 0x82DE;
		static const Uint32 TEXTURE_IMMUTABLE_LEVELS						   = 0x82DF;
		static const Uint32 BUFFER											   = 0x82E0;
		static const Uint32 SHADER											   = 0x82E1;
		static const Uint32 PROGRAM											   = 0x82E2;
		static const Uint32 QUERY											   = 0x82E3;
		static const Uint32 PROGRAM_PIPELINE								   = 0x82E4;
		static const Uint32 SAMPLER											   = 0x82E6;
		static const Uint32 MAX_LABEL_LENGTH								   = 0x82E8;
		static const Uint32 NUM_SHADING_LANGUAGE_VERSIONS					   = 0x82E9;
		static const Uint32 VERTEX_ATTRIB_ARRAY_LONG						   = 0x874E;
		static const Uint32 PRIMITIVE_RESTART_FIXED_INDEX					   = 0x8D69;
		static const Uint32 ANY_SAMPLES_PASSED_CONSERVATIVE					   = 0x8D6A;
		static const Uint32 MAX_ELEMENT_INDEX								   = 0x8D6B;
		static const Uint32 MAX_COMBINED_SHADER_OUTPUT_RESOURCES			   = 0x8F39;
		static const Uint32 VERTEX_BINDING_BUFFER							   = 0x8F4F;
		static const Uint32 SHADER_STORAGE_BUFFER							   = 0x90D2;
		static const Uint32 SHADER_STORAGE_BUFFER_BINDING					   = 0x90D3;
		static const Uint32 SHADER_STORAGE_BUFFER_START						   = 0x90D4;
		static const Uint32 SHADER_STORAGE_BUFFER_SIZE						   = 0x90D5;
		static const Uint32 MAX_VERTEX_SHADER_STORAGE_BLOCKS				   = 0x90D6;
		static const Uint32 MAX_GEOMETRY_SHADER_STORAGE_BLOCKS				   = 0x90D7;
		static const Uint32 MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS			   = 0x90D8;
		static const Uint32 MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS		   = 0x90D9;
		static const Uint32 MAX_FRAGMENT_SHADER_STORAGE_BLOCKS				   = 0x90DA;
		static const Uint32 MAX_COMPUTE_SHADER_STORAGE_BLOCKS				   = 0x90DB;
		static const Uint32 MAX_COMBINED_SHADER_STORAGE_BLOCKS				   = 0x90DC;
		static const Uint32 MAX_SHADER_STORAGE_BUFFER_BINDINGS				   = 0x90DD;
		static const Uint32 MAX_SHADER_STORAGE_BLOCK_SIZE					   = 0x90DE;
		static const Uint32 SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT			   = 0x90DF;
		static const Uint32 DEPTH_STENCIL_TEXTURE_MODE						   = 0x90EA;
		static const Uint32 MAX_COMPUTE_WORK_GROUP_INVOCATIONS				   = 0x90EB;
		static const Uint32 UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER		   = 0x90EC;
		static const Uint32 ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = 0x90ED;
		static const Uint32 DISPATCH_INDIRECT_BUFFER						   = 0x90EE;
		static const Uint32 DISPATCH_INDIRECT_BUFFER_BINDING				   = 0x90EF;
		static const Uint32 MAX_DEBUG_MESSAGE_LENGTH						   = 0x9143;
		static const Uint32 MAX_DEBUG_LOGGED_MESSAGES						   = 0x9144;
		static const Uint32 DEBUG_LOGGED_MESSAGES							   = 0x9145;
		static const Uint32 DEBUG_SEVERITY_HIGH								   = 0x9146;
		static const Uint32 DEBUG_SEVERITY_MEDIUM							   = 0x9147;
		static const Uint32 DEBUG_SEVERITY_LOW								   = 0x9148;
		static const Uint32 TEXTURE_BUFFER_OFFSET							   = 0x919D;
		static const Uint32 TEXTURE_BUFFER_SIZE								   = 0x919E;
		static const Uint32 TEXTURE_BUFFER_OFFSET_ALIGNMENT					   = 0x919F;
		static const Uint32 COMPUTE_SHADER									   = 0x91B9;
		static const Uint32 MAX_COMPUTE_UNIFORM_BLOCKS						   = 0x91BB;
		static const Uint32 MAX_COMPUTE_TEXTURE_IMAGE_UNITS					   = 0x91BC;
		static const Uint32 MAX_COMPUTE_IMAGE_UNIFORMS						   = 0x91BD;
		static const Uint32 MAX_COMPUTE_WORK_GROUP_COUNT					   = 0x91BE;
		static const Uint32 MAX_COMPUTE_WORK_GROUP_SIZE						   = 0x91BF;
		static const Uint32 COMPRESSED_R11_EAC								   = 0x9270;
		static const Uint32 COMPRESSED_SIGNED_R11_EAC						   = 0x9271;
		static const Uint32 COMPRESSED_RG11_EAC								   = 0x9272;
		static const Uint32 COMPRESSED_SIGNED_RG11_EAC						   = 0x9273;
		static const Uint32 COMPRESSED_RGB8_ETC2							   = 0x9274;
		static const Uint32 COMPRESSED_SRGB8_ETC2							   = 0x9275;
		static const Uint32 COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2		   = 0x9276;
		static const Uint32 COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2		   = 0x9277;
		static const Uint32 COMPRESSED_RGBA8_ETC2_EAC						   = 0x9278;
		static const Uint32 COMPRESSED_SRGB8_ALPHA8_ETC2_EAC				   = 0x9279;
		static const Uint32 DEBUG_OUTPUT									   = 0x92E0;
		static const Uint32 UNIFORM											   = 0x92E1;
		static const Uint32 UNIFORM_BLOCK									   = 0x92E2;
		static const Uint32 PROGRAM_INPUT									   = 0x92E3;
		static const Uint32 PROGRAM_OUTPUT									   = 0x92E4;
		static const Uint32 BUFFER_VARIABLE									   = 0x92E5;
		static const Uint32 SHADER_STORAGE_BLOCK							   = 0x92E6;
		static const Uint32 IS_PER_PATCH									   = 0x92E7;
		static const Uint32 VERTEX_SUBROUTINE								   = 0x92E8;
		static const Uint32 TESS_CONTROL_SUBROUTINE							   = 0x92E9;
		static const Uint32 TESS_EVALUATION_SUBROUTINE						   = 0x92EA;
		static const Uint32 GEOMETRY_SUBROUTINE								   = 0x92EB;
		static const Uint32 FRAGMENT_SUBROUTINE								   = 0x92EC;
		static const Uint32 COMPUTE_SUBROUTINE								   = 0x92ED;
		static const Uint32 VERTEX_SUBROUTINE_UNIFORM						   = 0x92EE;
		static const Uint32 TESS_CONTROL_SUBROUTINE_UNIFORM					   = 0x92EF;
		static const Uint32 TESS_EVALUATION_SUBROUTINE_UNIFORM				   = 0x92F0;
		static const Uint32 GEOMETRY_SUBROUTINE_UNIFORM						   = 0x92F1;
		static const Uint32 FRAGMENT_SUBROUTINE_UNIFORM						   = 0x92F2;
		static const Uint32 COMPUTE_SUBROUTINE_UNIFORM						   = 0x92F3;
		static const Uint32 TRANSFORM_FEEDBACK_VARYING						   = 0x92F4;
		static const Uint32 ACTIVE_RESOURCES								   = 0x92F5;
		static const Uint32 MAX_NAME_LENGTH									   = 0x92F6;
		static const Uint32 MAX_NUM_ACTIVE_VARIABLES						   = 0x92F7;
		static const Uint32 MAX_NUM_COMPATIBLE_SUBROUTINES					   = 0x92F8;
		static const Uint32 NAME_LENGTH										   = 0x92F9;
		static const Uint32 TYPE											   = 0x92FA;
		static const Uint32 ARRAY_SIZE										   = 0x92FB;
		static const Uint32 OFFSET											   = 0x92FC;
		static const Uint32 BLOCK_INDEX										   = 0x92FD;
		static const Uint32 ARRAY_STRIDE									   = 0x92FE;
		static const Uint32 MATRIX_STRIDE									   = 0x92FF;
		static const Uint32 IS_ROW_MAJOR									   = 0x9300;
		static const Uint32 ATOMIC_COUNTER_BUFFER_INDEX						   = 0x9301;
		static const Uint32 BUFFER_BINDING									   = 0x9302;
		static const Uint32 BUFFER_DATA_SIZE								   = 0x9303;
		static const Uint32 NUM_ACTIVE_VARIABLES							   = 0x9304;
		static const Uint32 ACTIVE_VARIABLES								   = 0x9305;
		static const Uint32 REFERENCED_BY_VERTEX_SHADER						   = 0x9306;
		static const Uint32 REFERENCED_BY_TESS_CONTROL_SHADER				   = 0x9307;
		static const Uint32 REFERENCED_BY_TESS_EVALUATION_SHADER			   = 0x9308;
		static const Uint32 REFERENCED_BY_GEOMETRY_SHADER					   = 0x9309;
		static const Uint32 REFERENCED_BY_FRAGMENT_SHADER					   = 0x930A;
		static const Uint32 REFERENCED_BY_COMPUTE_SHADER					   = 0x930B;
		static const Uint32 TOP_LEVEL_ARRAY_SIZE							   = 0x930C;
		static const Uint32 TOP_LEVEL_ARRAY_STRIDE							   = 0x930D;
		static const Uint32 LOCATION										   = 0x930E;
		static const Uint32 LOCATION_INDEX									   = 0x930F;
		static const Uint32 FRAMEBUFFER_DEFAULT_WIDTH						   = 0x9310;
		static const Uint32 FRAMEBUFFER_DEFAULT_HEIGHT						   = 0x9311;
		static const Uint32 FRAMEBUFFER_DEFAULT_LAYERS						   = 0x9312;
		static const Uint32 FRAMEBUFFER_DEFAULT_SAMPLES						   = 0x9313;
		static const Uint32 FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS		   = 0x9314;
		static const Uint32 MAX_FRAMEBUFFER_WIDTH							   = 0x9315;
		static const Uint32 MAX_FRAMEBUFFER_HEIGHT							   = 0x9316;
		static const Uint32 MAX_FRAMEBUFFER_LAYERS							   = 0x9317;
		static const Uint32 MAX_FRAMEBUFFER_SAMPLES							   = 0x9318;

		static BindVertexBuffer bindVertexBuffer;
		static ClearBufferData clearBufferData;
		static ClearBufferSubData clearBufferSubData;
		static CopyImageSubData copyImageSubData;
		static DispatchCompute dispatchCompute;
		static DispatchComputeIndirect dispatchComputeIndirect;
		static DebugMessageCallback debugMessageCallback;
		static DebugMessageControl debugMessageControl;
		static DebugMessageInsert debugMessageInsert;
		static FramebufferParameterI framebufferParameteri;
		static GetDebugMessageLog getDebugMessageLog;
		static GetFramebufferParameterIV getFramebufferParameteriv;
		static GetInternalformatI64V getInternalformati64v;
		static GetObjectLabel getObjectLabel;
		static GetObjectPtrLabel getObjectPtrLabel;
		static GetProgramInterfaceIV getProgramInterfaceiv;
		static GetProgramResourceIndex getProgramResourceIndex;
		static GetProgramResourceIV getProgramResourceiv;
		static GetProgramResourceLocation getProgramResourceLocation;
		static GetProgramResourceLocationIndex getProgramResourceLocationIndex;
		static GetProgramResourceName getProgramResourceName;
		static InvalidateBufferData invalidateBufferData;
		static InvalidateBufferSubData invalidateBufferSubData;
		static InvalidateFramebuffer invalidateFramebuffer;
		static InvalidateSubFramebuffer invalidateSubFramebuffer;
		static InvalidateTexImage invalidateTexImage;
		static InvalidateTexSubImage invalidateTexSubImage;
		static MultiDrawArraysIndirect multiDrawArraysIndirect;
		static MultiDrawElementsIndirect multiDrawElementsIndirect;
		static ObjectLabel objectLabel;
		static ObjectPtrLabel objectPtrLabel;
		static PopDebugGroup popDebugGroup;
		static PushDebugGroup pushDebugGroup;
		static ShaderStorageBlockBinding shaderStorageBlockBinding;
		static TexBufferRange texBufferRange;
		static TexStorage2DMultisample texStorage2DMultisample;
		static TexStorage3DMultisample texStorage3DMultisample;
		static TextureView textureView;
		static VertexAttribBinding vertexAttribBinding;
		static VertexAttribFormat vertexAttribFormat;
		static VertexAttribIFormat vertexAttribIFormat;
		static VertexAttribLFormat vertexAttribLFormat;
		static VertexBindingDivisor vertexBindingDivisor;

		// Version 4.4

		static const Uint32 MAP_PERSISTENT_BIT						= 0x0040;
		static const Uint32 MAP_COHERENT_BIT						= 0x0080;
		static const Uint32 DYNAMIC_STORAGE_BIT						= 0x0100;
		static const Uint32 CLIENT_STORAGE_BIT						= 0x0200;
		static const Uint32 CLIENT_MAPPED_BUFFER_BARRIER_BIT		= 0x00004000;
		static const Uint32 QUERY_BUFFER_BARRIER_BIT				= 0x00008000;
		static const Uint32 BUFFER_IMMUTABLE_STORAGE				= 0x821F;
		static const Uint32 BUFFER_STORAGE_FLAGS					= 0x8220;
		static const Uint32 PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED = 0x8221;
		static const Uint32 MAX_VERTEX_ATTRIB_STRIDE				= 0x82E5;
		static const Uint32 MIRROR_CLAMP_TO_EDGE					= 0x8743;
		static const Uint32 TEXTURE_BUFFER_BINDING					= 0x8C2A;
		static const Uint32 QUERY_BUFFER							= 0x9192;
		static const Uint32 QUERY_BUFFER_BINDING					= 0x9193;
		static const Uint32 QUERY_RESULT_NO_WAIT					= 0x9194;
		static const Uint32 LOCATION_COMPONENT						= 0x934A;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_INDEX			= 0x934B;
		static const Uint32 TRANSFORM_FEEDBACK_BUFFER_STRIDE		= 0x934C;
		static const Uint32 CLEAR_TEXTURE							= 0x9365;

		static BindBuffersBase bindBuffersBase;
		static BindBuffersRange bindBuffersRange;
		static BindImageTextures bindImageTextures;
		static BindSamplers bindSamplers;
		static BindTextures bindTextures;
		static BindVertexBuffers bindVertexBuffers;
		static BufferStorage bufferStorage;
		static ClearTexImage clearTexImage;
		static ClearTexSubImage clearTexSubImage;

		// Version 4.5

		static const Uint32 CONTEXT_FLAG_ROBUST_ACCESS_BIT		 = 0x0004;
		static const Uint32 CONTEXT_LOST						 = 0x0507;
		static const Uint32 TEXTURE_TARGET						 = 0x1006;
		static const Uint32 LOSE_CONTEXT_ON_RESET				 = 0x8252;
		static const Uint32 GUILTY_CONTEXT_RESET				 = 0x8253;
		static const Uint32 INNOCENT_CONTEXT_RESET				 = 0x8254;
		static const Uint32 UNKNOWN_CONTEXT_RESET				 = 0x8255;
		static const Uint32 RESET_NOTIFICATION_STRATEGY			 = 0x8256;
		static const Uint32 NO_RESET_NOTIFICATION				 = 0x8261;
		static const Uint32 QUERY_TARGET						 = 0x82EA;
		static const Uint32 MAX_CULL_DISTANCES					 = 0x82F9;
		static const Uint32 MAX_COMBINED_CLIP_AND_CULL_DISTANCES = 0x82FA;
		static const Uint32 CONTEXT_RELEASE_BEHAVIOR			 = 0x82FB;
		static const Uint32 CONTEXT_RELEASE_BEHAVIOR_FLUSH		 = 0x82FC;
		static const Uint32 QUERY_WAIT_INVERTED					 = 0x8E17;
		static const Uint32 QUERY_NO_WAIT_INVERTED				 = 0x8E18;
		static const Uint32 QUERY_BY_REGION_WAIT_INVERTED		 = 0x8E19;
		static const Uint32 QUERY_BY_REGION_NO_WAIT_INVERTED	 = 0x8E1A;
		static const Uint32 CLIP_ORIGIN							 = 0x935C;
		static const Uint32 CLIP_DEPTH_MODE						 = 0x935D;
		static const Uint32 NEGATIVE_ONE_TO_ONE					 = 0x935E;
		static const Uint32 ZERO_TO_ONE							 = 0x935F;

		static BindTextureUnit bindTextureUnit;
		static BlitNamedFramebuffer blitNamedFramebuffer;
		static CheckNamedFramebufferStatus checkNamedFramebufferStatus;
		static ClearNamedBufferData clearNamedBufferData;
		static ClearNamedBufferSubData clearNamedBufferSubData;
		static ClearNamedFramebufferFI clearNamedFramebufferfi;
		static ClearNamedFramebufferFV clearNamedFramebufferfv;
		static ClearNamedFramebufferIV clearNamedFramebufferiv;
		static ClearNamedFramebufferUIV clearNamedFramebufferuiv;
		static ClipControl clipControl;
		static CompressedTextureSubImage1D compressedTextureSubImage1D;
		static CompressedTextureSubImage2D compressedTextureSubImage2D;
		static CompressedTextureSubImage3D compressedTextureSubImage3D;
		static CopyNamedBufferSubData copyNamedBufferSubData;
		static CopyTextureSubImage1D copyTextureSubImage1D;
		static CopyTextureSubImage2D copyTextureSubImage2D;
		static CopyTextureSubImage3D copyTextureSubImage3D;
		static CreateBuffers createBuffers;
		static CreateFramebuffers createFramebuffers;
		static CreateProgramPipelines createProgramPipelines;
		static CreateQueries createQueries;
		static CreateRenderbuffers createRenderbuffers;
		static CreateSamplers createSamplers;
		static CreateTextures createTextures;
		static CreateTransformFeedbacks createTransformFeedbacks;
		static CreateVertexArrays createVertexArrays;
		static DisableVertexArrayAttrib disableVertexArrayAttrib;
		static EnableVertexArrayAttrib enableVertexArrayAttrib;
		static FlushMappedNamedBufferRange flushMappedNamedBufferRange;
		static GenerateTextureMipmap generateTextureMipmap;
		static GetCompressedTextureImage getCompressedTextureImage;
		static GetCompressedTextureSubImage getCompressedTextureSubImage;
		static GetGraphicsResetStatus getGraphicsResetStatus;
		static GetNamedBufferParameterI64V getNamedBufferParameteri64v;
		static GetNamedBufferParameterIV getNamedBufferParameteriv;
		static GetNamedBufferPointerV getNamedBufferPointerv;
		static GetNamedBufferSubData getNamedBufferSubData;
		static GetNamedFramebufferAttachmentParameterIV getNamedFramebufferAttachmentParameteriv;
		static GetNamedFramebufferParameterIV getNamedFramebufferParameteriv;
		static GetNamedRenderbufferParameterIV getNamedRenderbufferParameteriv;
		static GetnCompressedTexImage getnCompressedTexImage;
		static GetnTexImage getnTexImage;
		static GetnUniformDV getnUniformdv;
		static GetnUniformFV getnUniformfv;
		static GetnUniformIV getnUniformiv;
		static GetnUniformUIV getnUniformuiv;
		static GetQueryBufferObjectI64V getQueryBufferObjecti64v;
		static GetQueryBufferObjectIV getQueryBufferObjectiv;
		static GetQueryBufferObjectUI64V getQueryBufferObjectui64v;
		static GetQueryBufferObjectUIV getQueryBufferObjectuiv;
		static GetTextureImage getTextureImage;
		static GetTextureLevelParameterFV getTextureLevelParameterfv;
		static GetTextureLevelParameterIV getTextureLevelParameteriv;
		static GetTextureParameterFV getTextureParameterfv;
		static GetTextureParameterIIV getTextureParameterIiv;
		static GetTextureParameterIV getTextureParameteriv;
		static GetTextureParameterIUIV getTextureParameterIuiv;
		static GetTextureSubImage getTextureSubImage;
		static GetTransformFeedbackI64_V getTransformFeedbacki64_v;
		static GetTransformFeedbackIV getTransformFeedbackiv;
		static GetTransformFeedbackI_V getTransformFeedbacki_v;
		static GetVertexArrayIndexed64IV getVertexArrayIndexed64iv;
		static GetVertexArrayIndexedIV getVertexArrayIndexediv;
		static GetVertexArrayIV getVertexArrayiv;
		static InvalidateNamedFramebufferData invalidateNamedFramebufferData;
		static InvalidateNamedFramebufferSubData invalidateNamedFramebufferSubData;
		static MapNamedBuffer mapNamedBuffer;
		static MapNamedBufferRange mapNamedBufferRange;
		static MemoryBarrierByRegion memoryBarrierByRegion;
		static NamedBufferData namedBufferData;
		static NamedBufferStorage namedBufferStorage;
		static NamedBufferSubData namedBufferSubData;
		static NamedFramebufferDrawBuffer namedFramebufferDrawBuffer;
		static NamedFramebufferDrawBuffers namedFramebufferDrawBuffers;
		static NamedFramebufferParameterI namedFramebufferParameteri;
		static NamedFramebufferReadBuffer namedFramebufferReadBuffer;
		static NamedFramebufferRenderbuffer namedFramebufferRenderbuffer;
		static NamedFramebufferTexture namedFramebufferTexture;
		static NamedFramebufferTextureLayer namedFramebufferTextureLayer;
		static NamedRenderbufferStorage namedRenderbufferStorage;
		static NamedRenderbufferStorageMultisample namedRenderbufferStorageMultisample;
		static ReadnPixels readnPixels;
		static TransformFeedbackBufferBase transformFeedbackBufferBase;
		static TransformFeedbackBufferRange transformFeedbackBufferRange;
		static TextureBarrier textureBarrier;
		static TextureBuffer textureBuffer;
		static TextureBufferRange textureBufferRange;
		static TextureParameterF textureParameterf;
		static TextureParameterFV textureParameterfv;
		static TextureParameterI textureParameteri;
		static TextureParameterIIV textureParameterIiv;
		static TextureParameterIUIV textureParameterIuiv;
		static TextureParameterIV textureParameteriv;
		static TextureStorage1D textureStorage1D;
		static TextureStorage2D textureStorage2D;
		static TextureStorage2DMultisample textureStorage2DMultisample;
		static TextureStorage3D textureStorage3D;
		static TextureStorage3DMultisample textureStorage3DMultisample;
		static TextureSubImage1D textureSubImage1D;
		static TextureSubImage2D textureSubImage2D;
		static TextureSubImage3D textureSubImage3D;
		static UnmapNamedBuffer unmapNamedBuffer;
		static VertexArrayAttribBinding vertexArrayAttribBinding;
		static VertexArrayAttribFormat vertexArrayAttribFormat;
		static VertexArrayAttribIFormat vertexArrayAttribIFormat;
		static VertexArrayAttribLFormat vertexArrayAttribLFormat;
		static VertexArrayBindingDivisor vertexArrayBindingDivisor;
		static VertexArrayElementBuffer vertexArrayElementBuffer;
		static VertexArrayVertexBuffer vertexArrayVertexBuffer;
		static VertexArrayVertexBuffers vertexArrayVertexBuffers;

		// Custom

		static Int32 getInteger(const Uint32 name);

		OpenGL();

		OpenGL(const OpenGL& openGL) = delete;
		OpenGL(OpenGL&& openGL) = delete;

		~OpenGL() = default;

		OpenGL& operator =(const OpenGL& openGL) = delete;
		OpenGL& operator =(OpenGL&& openGL) = delete;

		static void checkForErrors(const Char8* file, const Uint32 line, const Char8* function);

	private:

		static void initialiseVersion();
		static void checkSupport();
		static void getStandardFunctions();
		static void logInfo();
		static Graphics::ExtensionNameList getExtensionNames();
	};
}

#undef DE_CALL_OPENGL
