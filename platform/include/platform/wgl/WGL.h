/**
 * @file platform/wgl/WGL.h
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

#include <core/Platform.h>
#include <core/Types.h>
#include <graphics/LogUtility.h>
#include <platform/windows/WindowsGraphics.h>

#define DE_CALL_WGL DE_INTERNAL_CALL_STDCALL

namespace Platform
{
	class GraphicsContextBase;

	class WGL final
	{
	public:

		// Standard

		using Function = Int32 (DE_CALL_WGL*)();

		using CreateContext = HGLRC (DE_CALL_WGL*)(HDC hdc);
		using DeleteContext = Int32 (DE_CALL_WGL*)(HGLRC hglrc);
		using GetCurrentContext = HGLRC (DE_CALL_WGL*)();
		using GetProcAddress = Function (DE_CALL_WGL*)(const Char8* lpszProc);
		using MakeCurrent = Int32 (DE_CALL_WGL*)(HDC hdc, HGLRC hglrc);

		// WGL_ARB_create_context

		using CreateContextAttribsARB =
			HGLRC (DE_CALL_WGL*)(HDC hdc, HGLRC hShareContext, const Int32* attribList);

		// WGL_ARB_extensions_string

		using GetExtensionsStringARB = const Char8* (DE_CALL_WGL*)(HDC hdc);

		// WGL_ARB_pixel_format

		using ChoosePixelFormatARB =
			Int32 (DE_CALL_WGL*)(HDC hdc, const Int32* piAttribIList, const Float32* pfAttribFList,
				Uint32 nMaxFormats, Int32* piFormats, Uint32* nNumFormats);

		using GetPixelFormatAttribFVARB =
			Int32 (DE_CALL_WGL*)(HDC hdc, Int32 iPixelFormat, Int32 iLayerPlane, Uint32 nAttributes,
				const Int32* piAttributes, Float32* piValues);

		using GetPixelFormatAttribIVARB =
			Int32 (DE_CALL_WGL*)(HDC hdc, Int32 piValues, Int32 iLayerPlane, Uint32 nAttributes,
				const Int32* piAttributes, Int32* attributeValues);


		// Standard

		static CreateContext createContext;
		static DeleteContext deleteContext;
		static GetCurrentContext getCurrentContext;
		static GetProcAddress getProcAddress;
		static MakeCurrent makeCurrent;

		// WGL_ARB_create_context

		static const Int32 CONTEXT_DEBUG_BIT_ARB			  = 0x0001;
		static const Int32 CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x0002;
		static const Int32 CONTEXT_MAJOR_VERSION_ARB		  = 0x2091;
		static const Int32 CONTEXT_MINOR_VERSION_ARB		  = 0x2092;
		static const Int32 CONTEXT_LAYER_PLANE_ARB			  = 0x2093;
		static const Int32 CONTEXT_FLAGS_ARB				  = 0x2094;
		static const Int32 ERROR_INVALID_VERSION_ARB		  = 0x2095;

		static CreateContextAttribsARB createContextAttribsARB;

		// WGL_ARB_extensions_string

		static GetExtensionsStringARB getExtensionsStringARB;

		// WGL_ARB_create_context_profile

		static const Int32 CONTEXT_CORE_PROFILE_BIT_ARB			 = 0x0001;
		static const Int32 CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x0002;
		static const Int32 ERROR_INVALID_PROFILE_ARB			 = 0x2096;
		static const Int32 CONTEXT_PROFILE_MASK_ARB				 = 0x9126;

		// WGL_ARB_multisample

		static const Int32 SAMPLE_BUFFERS_ARB = 0x2041;
		static const Int32 SAMPLES_ARB		  = 0x2042;

		// WGL_ARB_pixel_format

		static const Int32 NUMBER_PIXEL_FORMATS_ARB	   = 0x2000;
		static const Int32 DRAW_TO_WINDOW_ARB		   = 0x2001;
		static const Int32 DRAW_TO_BITMAP_ARB		   = 0x2002;
		static const Int32 ACCELERATION_ARB			   = 0x2003;
		static const Int32 NEED_PALETTE_ARB			   = 0x2004;
		static const Int32 NEED_SYSTEM_PALETTE_ARB	   = 0x2005;
		static const Int32 SWAP_LAYER_BUFFERS_ARB	   = 0x2006;
		static const Int32 SWAP_METHOD_ARB			   = 0x2007;
		static const Int32 NUMBER_OVERLAYS_ARB		   = 0x2008;
		static const Int32 NUMBER_UNDERLAYS_ARB		   = 0x2009;
		static const Int32 TRANSPARENT_ARB			   = 0x200A;
		static const Int32 SHARE_DEPTH_ARB			   = 0x200C;
		static const Int32 SHARE_STENCIL_ARB		   = 0x200D;
		static const Int32 SHARE_ACCUM_ARB			   = 0x200E;
		static const Int32 SUPPORT_GDI_ARB			   = 0x200F;
		static const Int32 SUPPORT_OPENGL_ARB		   = 0x2010;
		static const Int32 DOUBLE_BUFFER_ARB		   = 0x2011;
		static const Int32 STEREO_ARB				   = 0x2012;
		static const Int32 PIXEL_TYPE_ARB			   = 0x2013;
		static const Int32 COLOR_BITS_ARB			   = 0x2014;
		static const Int32 RED_BITS_ARB				   = 0x2015;
		static const Int32 RED_SHIFT_ARB			   = 0x2016;
		static const Int32 GREEN_BITS_ARB			   = 0x2017;
		static const Int32 GREEN_SHIFT_ARB			   = 0x2018;
		static const Int32 BLUE_BITS_ARB			   = 0x2019;
		static const Int32 BLUE_SHIFT_ARB			   = 0x201A;
		static const Int32 ALPHA_BITS_ARB			   = 0x201B;
		static const Int32 ALPHA_SHIFT_ARB			   = 0x201C;
		static const Int32 ACCUM_BITS_ARB			   = 0x201D;
		static const Int32 ACCUM_RED_BITS_ARB		   = 0x201E;
		static const Int32 ACCUM_GREEN_BITS_ARB		   = 0x201F;
		static const Int32 ACCUM_BLUE_BITS_ARB		   = 0x2020;
		static const Int32 ACCUM_ALPHA_BITS_ARB		   = 0x2021;
		static const Int32 DEPTH_BITS_ARB			   = 0x2022;
		static const Int32 STENCIL_BITS_ARB			   = 0x2023;
		static const Int32 AUX_BUFFERS_ARB			   = 0x2024;
		static const Int32 NO_ACCELERATION_ARB		   = 0x2025;
		static const Int32 GENERIC_ACCELERATION_ARB	   = 0x2026;
		static const Int32 FULL_ACCELERATION_ARB	   = 0x2027;
		static const Int32 SWAP_EXCHANGE_ARB		   = 0x2028;
		static const Int32 SWAP_COPY_ARB			   = 0x2029;
		static const Int32 SWAP_UNDEFINED_ARB		   = 0x202A;
		static const Int32 TYPE_RGBA_ARB			   = 0x202B;
		static const Int32 TYPE_COLORINDEX_ARB		   = 0x202C;
		static const Int32 TRANSPARENT_RED_VALUE_ARB   = 0x2037;
		static const Int32 TRANSPARENT_GREEN_VALUE_ARB = 0x2038;
		static const Int32 TRANSPARENT_BLUE_VALUE_ARB  = 0x2039;
		static const Int32 TRANSPARENT_ALPHA_VALUE_ARB = 0x203A;
		static const Int32 TRANSPARENT_INDEX_VALUE_ARB = 0x203B;

		static ChoosePixelFormatARB choosePixelFormatARB;
		static GetPixelFormatAttribFVARB getPixelFormatAttribfvARB;
		static GetPixelFormatAttribIVARB getPixelFormatAttribivARB;


		WGL() = delete;

		WGL(const WGL& wGL) = delete;
		WGL(WGL&& wGL) = delete;

		~WGL() = delete;

		WGL& operator =(const WGL& wGL) = delete;
		WGL& operator =(WGL&& wGL) = delete;

		static void initialise(const GraphicsContextBase& graphicsContext);

	private:

		static void getExtensionFunctions();
		static Graphics::ExtensionNameList getExtensionNames(const GraphicsContextBase& graphicsContext);
		static void checkExtensionSupport(const Graphics::ExtensionNameList& extensionNames);
	};
}

#undef DE_CALL_WGL
