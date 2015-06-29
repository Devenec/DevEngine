/**
 * @file platform/wgl/WGL.h
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
 *
 *
 * Copyright (c) 2013-2014 The Khronos Group Inc.
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

#include <core/Types.h>
#include <platform/windows/Windows.h>

// WGL_ARB_create_context

#define WGL_CONTEXT_DEBUG_BIT_ARB			   0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_MAJOR_VERSION_ARB		   0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB		   0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB			   0x2093
#define WGL_CONTEXT_FLAGS_ARB				   0x2094
#define ERROR_INVALID_VERSION_ARB			   0x2095

using WGLCreateContextAttribsARB = HGLRC (WINAPI *)(HDC deviceContextHandle, HGLRC shareGraphicsContextHandle,
	const Int32* attributes);


// WGL_ARB_create_context_profile

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB		  0x0001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x0002
#define ERROR_INVALID_PROFILE_ARB				  0x2096
#define WGL_CONTEXT_PROFILE_MASK_ARB			  0x9126


// WGL_ARB_extensions_string

using WGLGetExtensionsStringARB = const Char8* (WINAPI *)(HDC deviceContextHandle);


// WGL_ARB_multisample

#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB		   0x2042


// WGL_ARB_pixel_format

#define WGL_NUMBER_PIXEL_FORMATS_ARB	0x2000
#define WGL_DRAW_TO_WINDOW_ARB			0x2001
#define WGL_DRAW_TO_BITMAP_ARB			0x2002
#define WGL_ACCELERATION_ARB			0x2003
#define WGL_NEED_PALETTE_ARB			0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB		0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB		0x2006
#define WGL_SWAP_METHOD_ARB				0x2007
#define WGL_NUMBER_OVERLAYS_ARB			0x2008
#define WGL_NUMBER_UNDERLAYS_ARB		0x2009
#define WGL_TRANSPARENT_ARB				0x200A
#define WGL_SHARE_DEPTH_ARB				0x200C
#define WGL_SHARE_STENCIL_ARB			0x200D
#define WGL_SHARE_ACCUM_ARB				0x200E
#define WGL_SUPPORT_GDI_ARB				0x200F
#define WGL_SUPPORT_OPENGL_ARB			0x2010
#define WGL_DOUBLE_BUFFER_ARB			0x2011
#define WGL_STEREO_ARB					0x2012
#define WGL_PIXEL_TYPE_ARB				0x2013
#define WGL_COLOR_BITS_ARB				0x2014
#define WGL_RED_BITS_ARB				0x2015
#define WGL_RED_SHIFT_ARB				0x2016
#define WGL_GREEN_BITS_ARB				0x2017
#define WGL_GREEN_SHIFT_ARB				0x2018
#define WGL_BLUE_BITS_ARB				0x2019
#define WGL_BLUE_SHIFT_ARB				0x201A
#define WGL_ALPHA_BITS_ARB				0x201B
#define WGL_ALPHA_SHIFT_ARB				0x201C
#define WGL_ACCUM_BITS_ARB				0x201D
#define WGL_ACCUM_RED_BITS_ARB			0x201E
#define WGL_ACCUM_GREEN_BITS_ARB		0x201F
#define WGL_ACCUM_BLUE_BITS_ARB			0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB		0x2021
#define WGL_DEPTH_BITS_ARB				0x2022
#define WGL_STENCIL_BITS_ARB			0x2023
#define WGL_AUX_BUFFERS_ARB				0x2024
#define WGL_NO_ACCELERATION_ARB			0x2025
#define WGL_GENERIC_ACCELERATION_ARB	0x2026
#define WGL_FULL_ACCELERATION_ARB		0x2027
#define WGL_SWAP_EXCHANGE_ARB			0x2028
#define WGL_SWAP_COPY_ARB				0x2029
#define WGL_SWAP_UNDEFINED_ARB			0x202A
#define WGL_TYPE_RGBA_ARB				0x202B
#define WGL_TYPE_COLORINDEX_ARB			0x202C
#define WGL_TRANSPARENT_RED_VALUE_ARB	0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB 0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB	0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB 0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB 0x203B

using WGLChoosePixelFormatARB = Int32 (WINAPI *)(HDC deviceContextHandle, const Int32* attributes,
	const Float32* floatAttributes, Uint32 maxPixelFormatCount, Int32* pixelFormats, Uint32* pixelFormatCount);

using WGLGetPixelFormatAttribFVARB = Int32 (WINAPI *)(HDC deviceContextHandle, Int32 pixelFormatIndex,
	Int32 planeIndex, Uint32 attributeCount, const Int32* attributeIds, Float32* attributeValues);

using WGLGetPixelFormatAttribIVARB = Int32 (WINAPI *)(HDC deviceContextHandle, Int32 pixelFormatIndex,
	Int32 planeIndex, Uint32 attributeCount, const Int32* attributeIds, Int32* attributeValues);


// WGL_EXT_swap_control

using WGLGetSwapIntervalEXT = Int32 (WINAPI *)(void);
using WGLSwapIntervalEXT = Int32 (WINAPI *)(Int32 interval);


// Function declarations

extern WGLChoosePixelFormatARB wglChoosePixelFormatARB;
extern WGLCreateContextAttribsARB wglCreateContextAttribsARB;
extern WGLGetExtensionsStringARB wglGetExtensionsStringARB;
extern WGLGetPixelFormatAttribFVARB wglGetPixelFormatAttribfvARB;
extern WGLGetPixelFormatAttribIVARB wglGetPixelFormatAttribivARB;
extern WGLGetSwapIntervalEXT wglGetSwapIntervalEXT;
extern WGLSwapIntervalEXT wglSwapIntervalEXT;
