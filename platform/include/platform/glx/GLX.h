/**
 * @file platform/glx/GLX.h
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

#include <core/Singleton.h>
#include <core/Types.h>
#include <graphics/LogUtility.h>
#include <platform/x/XInclude.h>

namespace Platform
{
	class GLX final : public Core::Singleton<GLX>
	{
	public:

		// Version 1.0

		struct ContextStruct;
		using Context = ContextStruct*;

		using Drawable = XID;

		using DestroyContext = void (*)(Display* dpy, Context ctx);
		using IsDirect = Int32 (*)(Display* dpy, Context ctx);
		using QueryExtension = Int32 (*)(Display* dpy, Int32* errorb, Int32* event);
		using QueryVersion = Int32 (*)(Display* dpy, Int32* maj, Int32* min);
		using SwapBuffers = void (*)(Display* dpy, Drawable drawable);

		// Version 1.1

		using QueryExtensionsString = const Char8* (*)(Display* dpy, Int32 screen);

		// Version 1.3

		struct FBConfigStruct;
		using FBConfig = FBConfigStruct*;

		using ChooseFBConfig = FBConfig* (*)(Display* dpy, Int32 screen, const Int32* attrib_list, Int32* nelements);
		using GetFBConfigAttrib = Int32 (*)(Display* dpy, FBConfig config, Int32 attribute, Int32* value);
		using GetVisualFromFBConfig = XVisualInfo* (*)(Display* dpy, FBConfig config);
		using MakeContextCurrent = Int32 (*)(Display* dpy, Drawable draw, Drawable read, Context ctx);

		// version 1.4

		using Function = void (*)();

		using GetProcAddress = Function (*)(const Uint8* procName);

		// GLX_ARB_create_context

		using CreateContextAttribsARB = Context (*)(Display* dpy, FBConfig config, Context share_context, Int32 direct,
			const Int32* attrib_list);


		// Version 1.0

		static const Int32 USE_GL			= 0x01;
		static const Int32 BUFFER_SIZE		= 0x02;
		static const Int32 LEVEL			= 0x03;
		static const Int32 RGBA				= 0x04;
		static const Int32 DOUBLEBUFFER		= 0x05;
		static const Int32 STEREO			= 0x06;
		static const Int32 AUX_BUFFERS		= 0x07;
		static const Int32 RED_SIZE			= 0x08;
		static const Int32 GREEN_SIZE		= 0x09;
		static const Int32 BLUE_SIZE		= 0x0A;
		static const Int32 ALPHA_SIZE		= 0x0B;
		static const Int32 DEPTH_SIZE		= 0x0C;
		static const Int32 STENCIL_SIZE		= 0x0D;
		static const Int32 ACCUM_RED_SIZE	= 0x0E;
		static const Int32 ACCUM_GREEN_SIZE = 0x0F;
		static const Int32 ACCUM_BLUE_SIZE	= 0x10;
		static const Int32 ACCUM_ALPHA_SIZE = 0x11;

		static DestroyContext destroyContext;
		static IsDirect isDirect;
		static QueryExtension queryExtension;
		static QueryVersion queryVersion;
		static SwapBuffers swapBuffers;

		// Version 1.1

		static QueryExtensionsString queryExtensionsString;

		// Version 1.3

		static const Int32 WINDOW_BIT			   = 0x0001;
		static const Int32 PIXMAP_BIT			   = 0x0002;
		static const Int32 PBUFFER_BIT			   = 0x0004;
		static const Int32 RGBA_BIT				   = 0x0001;
		static const Int32 COLOR_INDEX_BIT		   = 0x0002;
		static const Int32 FRONT_LEFT_BUFFER_BIT   = 0x0001;
		static const Int32 FRONT_RIGHT_BUFFER_BIT  = 0x0002;
		static const Int32 BACK_LEFT_BUFFER_BIT	   = 0x0004;
		static const Int32 BACK_RIGHT_BUFFER_BIT   = 0x0008;
		static const Int32 AUX_BUFFERS_BIT		   = 0x0010;
		static const Int32 DEPTH_BUFFER_BIT		   = 0x0020;
		static const Int32 STENCIL_BUFFER_BIT	   = 0x0040;
		static const Int32 ACCUM_BUFFER_BIT		   = 0x0080;
		static const Int32 CONFIG_CAVEAT		   = 0x0020;
		static const Int32 X_VISUAL_TYPE		   = 0x0022;
		static const Int32 TRANSPARENT_TYPE		   = 0x0023;
		static const Int32 TRANSPARENT_INDEX_VALUE = 0x0024;
		static const Int32 TRANSPARENT_RED_VALUE   = 0x0025;
		static const Int32 TRANSPARENT_GREEN_VALUE = 0x0026;
		static const Int32 TRANSPARENT_BLUE_VALUE  = 0x0027;
		static const Int32 TRANSPARENT_ALPHA_VALUE = 0x0028;
		static const Int32 NONE					   = 0x8000;
		static const Int32 SLOW_CONFIG			   = 0x8001;
		static const Int32 TRUE_COLOR			   = 0x8002;
		static const Int32 DIRECT_COLOR			   = 0x8003;
		static const Int32 PSEUDO_COLOR			   = 0x8004;
		static const Int32 STATIC_COLOR			   = 0x8005;
		static const Int32 GRAY_SCALE			   = 0x8006;
		static const Int32 STATIC_GRAY			   = 0x8007;
		static const Int32 TRANSPARENT_RGB		   = 0x8008;
		static const Int32 TRANSPARENT_INDEX	   = 0x8009;
		static const Int32 VISUAL_ID			   = 0x800B;
		static const Int32 SCREEN				   = 0x800C;
		static const Int32 NON_CONFORMANT_CONFIG   = 0x800D;
		static const Int32 DRAWABLE_TYPE		   = 0x8010;
		static const Int32 RENDER_TYPE			   = 0x8011;
		static const Int32 X_RENDERABLE			   = 0x8012;
		static const Int32 FBCONFIG_ID			   = 0x8013;
		static const Int32 RGBA_TYPE			   = 0x8014;
		static const Int32 COLOR_INDEX_TYPE		   = 0x8015;
		static const Int32 MAX_PBUFFER_WIDTH	   = 0x8016;
		static const Int32 MAX_PBUFFER_HEIGHT	   = 0x8017;
		static const Int32 MAX_PBUFFER_PIXELS	   = 0x8018;
		static const Int32 PRESERVED_CONTENTS	   = 0x801B;
		static const Int32 LARGEST_PBUFFER		   = 0x801C;
		static const Int32 WIDTH				   = 0x801D;
		static const Int32 HEIGHT				   = 0x801E;
		static const Int32 EVENT_MASK			   = 0x801F;
		static const Int32 DAMAGED				   = 0x8020;
		static const Int32 SAVED				   = 0x8021;
		static const Int32 WINDOW				   = 0x8022;
		static const Int32 PBUFFER				   = 0x8023;
		static const Int32 PBUFFER_HEIGHT		   = 0x8040;
		static const Int32 PBUFFER_WIDTH		   = 0x8041;
		static const Int32 PBUFFER_CLOBBER_MASK	   = 0x08000000;
		static const Int32 DONT_CARE			   = 0xFFFFFFFF;

		static ChooseFBConfig chooseFBConfig;
		static GetFBConfigAttrib getFBConfigAttrib;
		static GetVisualFromFBConfig getVisualFromFBConfig;
		static MakeContextCurrent makeContextCurrent;

		// Version 1.4

		static const Int32 SAMPLE_BUFFERS = 0x0186A0;
		static const Int32 SAMPLES		  = 0x0186A1;

		static GetProcAddress getProcAddress;

		// GLX_ARB_create_context

		static const Int32 CONTEXT_DEBUG_BIT_ARB			  = 0x0001;
		static const Int32 CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x0002;
		static const Int32 CONTEXT_MAJOR_VERSION_ARB		  = 0x2091;
		static const Int32 CONTEXT_MINOR_VERSION_ARB		  = 0x2092;
		static const Int32 CONTEXT_FLAGS_ARB				  = 0x2094;

		static CreateContextAttribsARB createContextAttribsARB;

		// GLX_ARB_create_context_profile

		static const Int32 CONTEXT_CORE_PROFILE_BIT_ARB			 = 0x0001;
		static const Int32 CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x0002;
		static const Int32 CONTEXT_PROFILE_MASK_ARB				 = 0x9126;


		GLX();

		GLX(const GLX& glX) = delete;
		GLX(GLX&& glX) = delete;

		~GLX();

		GLX& operator =(const GLX& glX) = delete;
		GLX& operator =(GLX&& glX) = delete;

	private:

		Void* _libraryHandle;

		void loadLibrary();
		void getStandardFunctions() const;
		void checkSupport() const;
		void getExtensionFunctions() const;
		void checkExtensionSupport() const;
		Graphics::ExtensionNameList getExtensionNames() const;
		void clearFunctions() const;
		void unloadLibrary() const;
		Void* getStandardFunctionInternal(const Char8* name) const;

		template<typename T>
		inline T getStandardFunction(const Char8* name) const;
	};

#include "inline/GLX.inl"
}
