/**
 * @file platform/wgl/WGLGraphicsExtensionLoader.cpp
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
 */

#include <core/Error.h>
#include <core/Log.h>
#include <core/Types.h>
#include <platform/GraphicsExtensionLoader.h>
#include <platform/opengl/OpenGL.h>
#include <platform/wgl/WGL.h>
#include <platform/wgl/WGLGraphicsContextBase.h>

using namespace Core;
using namespace Platform;

// Implementation

class GraphicsExtensionLoader::Impl final
{
public:

	Impl() = delete;

	Impl(const Impl& impl) = delete;
	Impl(Impl&& impl) = delete;

	~Impl() = delete;

	Impl& operator =(const Impl& impl) = delete;
	Impl& operator =(Impl&& impl) = delete;

	static void loadContextExtensions(const GraphicsContextBase& graphicsContext)
	{
		validateContextState();
		loadWGLExtensions();
		logSupportedWGLExtensions(graphicsContext);
	}

	static void loadInterfaceExtensions()
	{
		validateContextState();
		loadOpenGLStandards();
	}

private:

	static void validateContextState()
	{
		if(WGL::getCurrentContext() == nullptr)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " No current context exists." << Log::Flush();
			DE_ERROR(0x0);
		}
	}

	static void loadWGLExtensions()
	{
		// WGL_ARB_create_context

		WGL::createContextAttribsARB = getFunction<WGL::CreateContextAttribsARB>("wglCreateContextAttribsARB");

		// WGL_ARB_extensions_string

		WGL::getExtensionsStringARB = getFunction<WGL::GetExtensionsStringARB>("wglGetExtensionsStringARB");

		// WGL_ARB_pixel_format

		WGL::choosePixelFormatARB = getFunction<WGL::ChoosePixelFormatARB>("wglChoosePixelFormatARB");
		WGL::getPixelFormatAttribfvARB = getFunction<WGL::GetPixelFormatAttribFVARB>("wglGetPixelFormatAttribfvARB");
		WGL::getPixelFormatAttribivARB = getFunction<WGL::GetPixelFormatAttribIVARB>("wglGetPixelFormatAttribivARB");

		// WGL_EXT_swap_control

		WGL::getSwapIntervalEXT = getFunction<WGL::GetSwapIntervalEXT>("wglGetSwapIntervalEXT");
		WGL::swapIntervalEXT = getFunction<WGL::SwapIntervalEXT>("wglSwapIntervalEXT");
	}

	static void logSupportedWGLExtensions(const GraphicsContextBase& graphicsContext)
	{
		defaultLog << LogLevel::Info << COMPONENT_TAG;

		if(WGL::getExtensionsStringARB == nullptr)
		{
			defaultLog << " No WGL extensions are supported.";
		}
		else
		{
			defaultLog << " Supported WGL extensions: " <<
				WGL::getExtensionsStringARB(graphicsContext.deviceContextHandle());
		}

		defaultLog << Log::Flush();
	}

	static void loadOpenGLStandards()
	{
		// Version 1.2

		OpenGL::copyTexSubImage3D = getFunction<OpenGL::CopyTexSubImage3D>("glCopyTexSubImage3D");
		OpenGL::drawRangeElements = getFunction<OpenGL::DrawRangeElements>("glDrawRangeElements");
		OpenGL::texImage3D = getFunction<OpenGL::TexImage3D>("glTexImage3D");
		OpenGL::texSubImage3D = getFunction<OpenGL::TexSubImage3D>("glTexSubImage3D");

		// Version 1.3

		OpenGL::activeTexture = getFunction<OpenGL::ActiveTexture>("glActiveTexture");
		OpenGL::compressedTexImage1D = getFunction<OpenGL::CompressedTexImage1D>("glCompressedTexImage1D");
		OpenGL::compressedTexImage2D = getFunction<OpenGL::CompressedTexImage2D>("glCompressedTexImage2D");
		OpenGL::compressedTexImage3D = getFunction<OpenGL::CompressedTexImage3D>("glCompressedTexImage3D");
		OpenGL::compressedTexSubImage1D = getFunction<OpenGL::CompressedTexSubImage1D>("glCompressedTexSubImage1D");
		OpenGL::compressedTexSubImage2D = getFunction<OpenGL::CompressedTexSubImage2D>("glCompressedTexSubImage2D");
		OpenGL::compressedTexSubImage3D = getFunction<OpenGL::CompressedTexSubImage3D>("glCompressedTexSubImage3D");
		OpenGL::getCompressedTexImage = getFunction<OpenGL::GetCompressedTexImage>("glGetCompressedTexImage");
		OpenGL::sampleCoverage = getFunction<OpenGL::SampleCoverage>("glSampleCoverage");

		// Version 1.4

		OpenGL::blendColor = getFunction<OpenGL::BlendColor>("glBlendColor");
		OpenGL::blendEquation = getFunction<OpenGL::BlendEquation>("glBlendEquation");
		OpenGL::blendFuncSeparate = getFunction<OpenGL::BlendFuncSeparate>("glBlendFuncSeparate");
		OpenGL::multiDrawArrays = getFunction<OpenGL::MultiDrawArrays>("glMultiDrawArrays");
		OpenGL::multiDrawElements = getFunction<OpenGL::MultiDrawElements>("glMultiDrawElements");
		OpenGL::pointParameterf = getFunction<OpenGL::PointParameterF>("glPointParameterf");
		OpenGL::pointParameterfv = getFunction<OpenGL::PointParameterFV>("glPointParameterfv");
		OpenGL::pointParameteri = getFunction<OpenGL::PointParameterI>("glPointParameteri");
		OpenGL::pointParameteriv = getFunction<OpenGL::PointParameterIV>("glPointParameteriv");

		// Version 1.5

		OpenGL::beginQuery = getFunction<OpenGL::BeginQuery>("glBeginQuery");
		OpenGL::bindBuffer = getFunction<OpenGL::BindBuffer>("glBindBuffer");
		OpenGL::bufferData = getFunction<OpenGL::BufferData>("glBufferData");
		OpenGL::bufferSubData = getFunction<OpenGL::BufferSubData>("glBufferSubData");
		OpenGL::deleteBuffers = getFunction<OpenGL::DeleteBuffers>("glDeleteBuffers");
		OpenGL::deleteQueries = getFunction<OpenGL::DeleteQueries>("glDeleteQueries");
		OpenGL::endQuery = getFunction<OpenGL::EndQuery>("glEndQuery");
		OpenGL::genBuffers = getFunction<OpenGL::GenBuffers>("glGenBuffers");
		OpenGL::genQueries = getFunction<OpenGL::GenQueries>("glGenQueries");
		OpenGL::getBufferParameteriv = getFunction<OpenGL::GetBufferParameterIV>("glGetBufferParameteriv");
		OpenGL::getBufferPointerv = getFunction<OpenGL::GetBufferPointerV>("glGetBufferPointerv");
		OpenGL::getBufferSubData = getFunction<OpenGL::GetBufferSubData>("glGetBufferSubData");
		OpenGL::getQueryiv = getFunction<OpenGL::GetQueryIV>("glGetQueryiv");
		OpenGL::getQueryObjectiv = getFunction<OpenGL::GetQueryObjectIV>("glGetQueryObjectiv");
		OpenGL::getQueryObjectuiv = getFunction<OpenGL::GetQueryObjectUIV>("glGetQueryObjectuiv");
		OpenGL::isBuffer = getFunction<OpenGL::IsBuffer>("glIsBuffer");
		OpenGL::isQuery = getFunction<OpenGL::IsQuery>("glIsQuery");
		OpenGL::mapBuffer = getFunction<OpenGL::MapBuffer>("glMapBuffer");
		OpenGL::unmapBuffer = getFunction<OpenGL::UnmapBuffer>("glUnmapBuffer");

		// Version 2.0

		OpenGL::attachShader = getFunction<OpenGL::AttachShader>("glAttachShader");
		OpenGL::bindAttribLocation = getFunction<OpenGL::BindAttribLocation>("glBindAttribLocation");
		OpenGL::blendEquationSeparate = getFunction<OpenGL::BlendEquationSeparate>("glBlendEquationSeparate");
		OpenGL::compileShader = getFunction<OpenGL::CompileShader>("glCompileShader");
		OpenGL::createProgram = getFunction<OpenGL::CreateProgram>("glCreateProgram");
		OpenGL::createShader = getFunction<OpenGL::CreateShader>("glCreateShader");
		OpenGL::deleteProgram = getFunction<OpenGL::DeleteProgram>("glDeleteProgram");
		OpenGL::deleteShader = getFunction<OpenGL::DeleteShader>("glDeleteShader");
		OpenGL::detachShader = getFunction<OpenGL::DetachShader>("glDetachShader");
		OpenGL::disableVertexAttribArray = getFunction<OpenGL::DisableVertexAttribArray>("glDisableVertexAttribArray");
		OpenGL::drawBuffers = getFunction<OpenGL::DrawBuffers>("glDrawBuffers");
		OpenGL::enableVertexAttribArray = getFunction<OpenGL::EnableVertexAttribArray>("glEnableVertexAttribArray");
		OpenGL::getActiveAttrib = getFunction<OpenGL::GetActiveAttrib>("glGetActiveAttrib");
		OpenGL::getActiveUniform = getFunction<OpenGL::GetActiveUniform>("glGetActiveUniform");
		OpenGL::getAttachedShaders = getFunction<OpenGL::GetAttachedShaders>("glGetAttachedShaders");
		OpenGL::getAttribLocation = getFunction<OpenGL::GetAttribLocation>("glGetAttribLocation");
		OpenGL::getProgramInfoLog = getFunction<OpenGL::GetProgramInfoLog>("glGetProgramInfoLog");
		OpenGL::getProgramiv = getFunction<OpenGL::GetProgramIV>("glGetProgramiv");
		OpenGL::getShaderInfoLog = getFunction<OpenGL::GetShaderInfoLog>("glGetShaderInfoLog");
		OpenGL::getShaderiv = getFunction<OpenGL::GetShaderIV>("glGetShaderiv");
		OpenGL::getShaderSource = getFunction<OpenGL::GetShaderSource>("glGetShaderSource");
		OpenGL::getUniformfv = getFunction<OpenGL::GetUniformFV>("glGetUniformfv");
		OpenGL::getUniformiv = getFunction<OpenGL::GetUniformIV>("glGetUniformiv");
		OpenGL::getUniformLocation = getFunction<OpenGL::GetUniformLocation>("glGetUniformLocation");
		OpenGL::getVertexAttribdv = getFunction<OpenGL::GetVertexAttribDV>("glGetVertexAttribdv");
		OpenGL::getVertexAttribfv = getFunction<OpenGL::GetVertexAttribFV>("glGetVertexAttribfv");
		OpenGL::getVertexAttribiv = getFunction<OpenGL::GetVertexAttribIV>("glGetVertexAttribiv");
		OpenGL::getVertexAttribPointerv = getFunction<OpenGL::GetVertexAttribPointerV>("glGetVertexAttribPointerv");
		OpenGL::isProgram = getFunction<OpenGL::IsProgram>("glIsProgram");
		OpenGL::isShader = getFunction<OpenGL::IsShader>("glIsShader");
		OpenGL::linkProgram = getFunction<OpenGL::LinkProgram>("glLinkProgram");
		OpenGL::shaderSource = getFunction<OpenGL::ShaderSource>("glShaderSource");
		OpenGL::stencilFuncSeparate = getFunction<OpenGL::StencilFuncSeparate>("glStencilFuncSeparate");
		OpenGL::stencilMaskSeparate = getFunction<OpenGL::StencilMaskSeparate>("glStencilMaskSeparate");
		OpenGL::stencilOpSeparate = getFunction<OpenGL::StencilOpSeparate>("glStencilOpSeparate");
		OpenGL::uniform1f = getFunction<OpenGL::Uniform1F>("glUniform1f");
		OpenGL::uniform1fv = getFunction<OpenGL::Uniform1FV>("glUniform1fv");
		OpenGL::uniform1i = getFunction<OpenGL::Uniform1I>("glUniform1i");
		OpenGL::uniform1iv = getFunction<OpenGL::Uniform1IV>("glUniform1iv");
		OpenGL::uniform2f = getFunction<OpenGL::Uniform2F>("glUniform2f");
		OpenGL::uniform2fv = getFunction<OpenGL::Uniform2FV>("glUniform2fv");
		OpenGL::uniform2i = getFunction<OpenGL::Uniform2I>("glUniform2i");
		OpenGL::uniform2iv = getFunction<OpenGL::Uniform2IV>("glUniform2iv");
		OpenGL::uniform3f = getFunction<OpenGL::Uniform3F>("glUniform3f");
		OpenGL::uniform3fv = getFunction<OpenGL::Uniform3FV>("glUniform3fv");
		OpenGL::uniform3i = getFunction<OpenGL::Uniform3I>("glUniform3i");
		OpenGL::uniform3iv = getFunction<OpenGL::Uniform3IV>("glUniform3iv");
		OpenGL::uniform4f = getFunction<OpenGL::Uniform4F>("glUniform4f");
		OpenGL::uniform4fv = getFunction<OpenGL::Uniform4FV>("glUniform4fv");
		OpenGL::uniform4i = getFunction<OpenGL::Uniform4I>("glUniform4i");
		OpenGL::uniform4iv = getFunction<OpenGL::Uniform4IV>("glUniform4iv");
		OpenGL::uniformMatrix2fv = getFunction<OpenGL::UniformMatrix2FV>("glUniformMatrix2fv");
		OpenGL::uniformMatrix3fv = getFunction<OpenGL::UniformMatrix3FV>("glUniformMatrix3fv");
		OpenGL::uniformMatrix4fv = getFunction<OpenGL::UniformMatrix4FV>("glUniformMatrix4fv");
		OpenGL::useProgram = getFunction<OpenGL::UseProgram>("glUseProgram");
		OpenGL::validateProgram = getFunction<OpenGL::ValidateProgram>("glValidateProgram");
		OpenGL::vertexAttrib1d = getFunction<OpenGL::VertexAttrib1D>("glVertexAttrib1d");
		OpenGL::vertexAttrib1dv = getFunction<OpenGL::VertexAttrib1DV>("glVertexAttrib1dv");
		OpenGL::vertexAttrib1f = getFunction<OpenGL::VertexAttrib1F>("glVertexAttrib1f");
		OpenGL::vertexAttrib1fv = getFunction<OpenGL::VertexAttrib1FV>("glVertexAttrib1fv");
		OpenGL::vertexAttrib1s = getFunction<OpenGL::VertexAttrib1S>("glVertexAttrib1s");
		OpenGL::vertexAttrib1sv = getFunction<OpenGL::VertexAttrib1SV>("glVertexAttrib1sv");
		OpenGL::vertexAttrib2d = getFunction<OpenGL::VertexAttrib2D>("glVertexAttrib2d");
		OpenGL::vertexAttrib2dv = getFunction<OpenGL::VertexAttrib2DV>("glVertexAttrib2dv");
		OpenGL::vertexAttrib2f = getFunction<OpenGL::VertexAttrib2F>("glVertexAttrib2f");
		OpenGL::vertexAttrib2fv = getFunction<OpenGL::VertexAttrib2FV>("glVertexAttrib2fv");
		OpenGL::vertexAttrib2s = getFunction<OpenGL::VertexAttrib2S>("glVertexAttrib2s");
		OpenGL::vertexAttrib2sv = getFunction<OpenGL::VertexAttrib2SV>("glVertexAttrib2sv");
		OpenGL::vertexAttrib3d = getFunction<OpenGL::VertexAttrib3D>("glVertexAttrib3d");
		OpenGL::vertexAttrib3dv = getFunction<OpenGL::VertexAttrib3DV>("glVertexAttrib3dv");
		OpenGL::vertexAttrib3f = getFunction<OpenGL::VertexAttrib3F>("glVertexAttrib3f");
		OpenGL::vertexAttrib3fv = getFunction<OpenGL::VertexAttrib3FV>("glVertexAttrib3fv");
		OpenGL::vertexAttrib3s = getFunction<OpenGL::VertexAttrib3S>("glVertexAttrib3s");
		OpenGL::vertexAttrib3sv = getFunction<OpenGL::VertexAttrib3SV>("glVertexAttrib3sv");
		OpenGL::vertexAttrib4bv = getFunction<OpenGL::VertexAttrib4BV>("glVertexAttrib4bv");
		OpenGL::vertexAttrib4d = getFunction<OpenGL::VertexAttrib4D>("glVertexAttrib4d");
		OpenGL::vertexAttrib4dv = getFunction<OpenGL::VertexAttrib4DV>("glVertexAttrib4dv");
		OpenGL::vertexAttrib4f = getFunction<OpenGL::VertexAttrib4F>("glVertexAttrib4f");
		OpenGL::vertexAttrib4fv = getFunction<OpenGL::VertexAttrib4FV>("glVertexAttrib4fv");
		OpenGL::vertexAttrib4iv = getFunction<OpenGL::VertexAttrib4IV>("glVertexAttrib4iv");
		OpenGL::vertexAttrib4Nbv = getFunction<OpenGL::VertexAttrib4NBV>("glVertexAttrib4Nbv");
		OpenGL::vertexAttrib4Niv = getFunction<OpenGL::VertexAttrib4NIV>("glVertexAttrib4Niv");
		OpenGL::vertexAttrib4Nsv = getFunction<OpenGL::VertexAttrib4NSV>("glVertexAttrib4Nsv");
		OpenGL::vertexAttrib4Nub = getFunction<OpenGL::VertexAttrib4NUB>("glVertexAttrib4Nub");
		OpenGL::vertexAttrib4Nubv = getFunction<OpenGL::VertexAttrib4NUBV>("glVertexAttrib4Nubv");
		OpenGL::vertexAttrib4Nuiv = getFunction<OpenGL::VertexAttrib4NUIV>("glVertexAttrib4Nuiv");
		OpenGL::vertexAttrib4Nusv = getFunction<OpenGL::VertexAttrib4NUSV>("glVertexAttrib4Nusv");
		OpenGL::vertexAttrib4s = getFunction<OpenGL::VertexAttrib4S>("glVertexAttrib4s");
		OpenGL::vertexAttrib4sv = getFunction<OpenGL::VertexAttrib4SV>("glVertexAttrib4sv");
		OpenGL::vertexAttrib4ubv = getFunction<OpenGL::VertexAttrib4UBV>("glVertexAttrib4ubv");
		OpenGL::vertexAttrib4uiv = getFunction<OpenGL::VertexAttrib4UIV>("glVertexAttrib4uiv");
		OpenGL::vertexAttrib4usv = getFunction<OpenGL::VertexAttrib4USV>("glVertexAttrib4usv");
		OpenGL::vertexAttribPointer = getFunction<OpenGL::VertexAttribPointer>("glVertexAttribPointer");

		// Version 2.1

		OpenGL::uniformMatrix2x3fv = getFunction<OpenGL::UniformMatrix2X3FV>("glUniformMatrix2x3fv");
		OpenGL::uniformMatrix2x4fv = getFunction<OpenGL::UniformMatrix2X4FV>("glUniformMatrix2x4fv");
		OpenGL::uniformMatrix3x2fv = getFunction<OpenGL::UniformMatrix3X2FV>("glUniformMatrix3x2fv");
		OpenGL::uniformMatrix3x4fv = getFunction<OpenGL::UniformMatrix3X4FV>("glUniformMatrix3x4fv");
		OpenGL::uniformMatrix4x2fv = getFunction<OpenGL::UniformMatrix4X2FV>("glUniformMatrix4x2fv");
		OpenGL::uniformMatrix4x3fv = getFunction<OpenGL::UniformMatrix4X3FV>("glUniformMatrix4x3fv");

		// Version 3.0

		OpenGL::beginConditionalRender = getFunction<OpenGL::BeginConditionalRender>("glBeginConditionalRender");
		OpenGL::beginTransformFeedback = getFunction<OpenGL::BeginTransformFeedback>("glBeginTransformFeedback");
		OpenGL::bindBufferBase = getFunction<OpenGL::BindBufferBase>("glBindBufferBase");
		OpenGL::bindBufferRange = getFunction<OpenGL::BindBufferRange>("glBindBufferRange");
		OpenGL::bindFragDataLocation = getFunction<OpenGL::BindFragDataLocation>("glBindFragDataLocation");
		OpenGL::bindFramebuffer = getFunction<OpenGL::BindFramebuffer>("glBindFramebuffer");
		OpenGL::bindRenderbuffer = getFunction<OpenGL::BindRenderbuffer>("glBindRenderbuffer");
		OpenGL::bindVertexArray = getFunction<OpenGL::BindVertexArray>("glBindVertexArray");
		OpenGL::blitFramebuffer = getFunction<OpenGL::BlitFramebuffer>("glBlitFramebuffer");
		OpenGL::checkFramebufferStatus = getFunction<OpenGL::CheckFramebufferStatus>("glCheckFramebufferStatus");
		OpenGL::clampColor = getFunction<OpenGL::ClampColor>("glClampColor");
		OpenGL::clearBufferfi = getFunction<OpenGL::ClearBufferFI>("glClearBufferfi");
		OpenGL::clearBufferfv = getFunction<OpenGL::ClearBufferFV>("glClearBufferfv");
		OpenGL::clearBufferiv = getFunction<OpenGL::ClearBufferIV>("glClearBufferiv");
		OpenGL::clearBufferuiv = getFunction<OpenGL::ClearBufferUIV>("glClearBufferuiv");
		OpenGL::colorMaski = getFunction<OpenGL::ColorMaskI>("glColorMaski");
		OpenGL::deleteFramebuffers = getFunction<OpenGL::DeleteFramebuffers>("glDeleteFramebuffers");
		OpenGL::deleteRenderbuffers = getFunction<OpenGL::DeleteRenderbuffers>("glDeleteRenderbuffers");
		OpenGL::deleteVertexArrays = getFunction<OpenGL::DeleteVertexArrays>("glDeleteVertexArrays");
		OpenGL::disablei = getFunction<OpenGL::DisableI>("glDisablei");
		OpenGL::enablei = getFunction<OpenGL::EnableI>("glEnablei");
		OpenGL::endConditionalRender = getFunction<OpenGL::EndConditionalRender>("glEndConditionalRender");
		OpenGL::endTransformFeedback = getFunction<OpenGL::EndTransformFeedback>("glEndTransformFeedback");
		OpenGL::flushMappedBufferRange = getFunction<OpenGL::FlushMappedBufferRange>("glFlushMappedBufferRange");
		OpenGL::framebufferRenderbuffer = getFunction<OpenGL::FramebufferRenderbuffer>("glFramebufferRenderbuffer");
		OpenGL::framebufferTexture1D = getFunction<OpenGL::FramebufferTexture1D>("glFramebufferTexture1D");
		OpenGL::framebufferTexture2D = getFunction<OpenGL::FramebufferTexture2D>("glFramebufferTexture2D");
		OpenGL::framebufferTexture3D = getFunction<OpenGL::FramebufferTexture3D>("glFramebufferTexture3D");
		OpenGL::framebufferTextureLayer = getFunction<OpenGL::FramebufferTextureLayer>("glFramebufferTextureLayer");
		OpenGL::generateMipmap = getFunction<OpenGL::GenerateMipmap>("glGenerateMipmap");
		OpenGL::genFramebuffers = getFunction<OpenGL::GenFramebuffers>("glGenFramebuffers");
		OpenGL::genRenderbuffers = getFunction<OpenGL::GenRenderbuffers>("glGenRenderbuffers");
		OpenGL::genVertexArrays = getFunction<OpenGL::GenVertexArrays>("glGenVertexArrays");
		OpenGL::getBooleani_v = getFunction<OpenGL::GetBooleanI_V>("glGetBooleani_v");
		OpenGL::getFragDataLocation = getFunction<OpenGL::GetFragDataLocation>("glGetFragDataLocation");

		OpenGL::getFramebufferAttachmentParameteriv = getFunction<OpenGL::GetFramebufferAttachmentParameterIV>(
			"glGetFramebufferAttachmentParameteriv");

		OpenGL::getIntegeri_v = getFunction<OpenGL::GetIntegerI_V>("glGetIntegeri_v");

		OpenGL::getRenderbufferParameteriv = getFunction<OpenGL::GetRenderbufferParameterIV>(
			"glGetRenderbufferParameteriv");

		OpenGL::getStringi = getFunction<OpenGL::GetStringI>("glGetStringi");
		OpenGL::getTexParameterIiv = getFunction<OpenGL::GetTexParameterIIV>("glGetTexParameterIiv");
		OpenGL::getTexParameterIuiv = getFunction<OpenGL::GetTexParameterIUIV>("glGetTexParameterIuiv");

		OpenGL::getTransformFeedbackVarying = getFunction<OpenGL::GetTransformFeedbackVarying>(
			"glGetTransformFeedbackVarying");

		OpenGL::getUniformuiv = getFunction<OpenGL::GetUniformUIV>("glGetUniformuiv");
		OpenGL::getVertexAttribIiv = getFunction<OpenGL::GetVertexAttribIIV>("glGetVertexAttribIiv");
		OpenGL::getVertexAttribIuiv = getFunction<OpenGL::GetVertexAttribIUIV>("glGetVertexAttribIuiv");
		OpenGL::isEnabledi = getFunction<OpenGL::IsEnabledI>("glIsEnabledi");
		OpenGL::isFramebuffer = getFunction<OpenGL::IsFramebuffer>("glIsFramebuffer");
		OpenGL::isRenderbuffer = getFunction<OpenGL::IsRenderbuffer>("glIsRenderbuffer");
		OpenGL::isVertexArray = getFunction<OpenGL::IsVertexArray>("glIsVertexArray");
		OpenGL::mapBufferRange = getFunction<OpenGL::MapBufferRange>("glMapBufferRange");
		OpenGL::renderbufferStorage = getFunction<OpenGL::RenderbufferStorage>("glRenderbufferStorage");

		OpenGL::renderbufferStorageMultisample = getFunction<OpenGL::RenderbufferStorageMultisample>(
			"glRenderbufferStorageMultisample");

		OpenGL::texParameterIiv = getFunction<OpenGL::TexParameterIIV>("glTexParameterIiv");
		OpenGL::texParameterIuiv = getFunction<OpenGL::TexParameterIUIV>("glTexParameterIuiv");

		OpenGL::transformFeedbackVaryings = getFunction<OpenGL::TransformFeedbackVaryings>(
			"glTransformFeedbackVaryings");

		OpenGL::uniform1ui = getFunction<OpenGL::Uniform1UI>("glUniform1ui");
		OpenGL::uniform1uiv = getFunction<OpenGL::Uniform1UIV>("glUniform1uiv");
		OpenGL::uniform2ui = getFunction<OpenGL::Uniform2UI>("glUniform2ui");
		OpenGL::uniform2uiv = getFunction<OpenGL::Uniform2UIV>("glUniform2uiv");
		OpenGL::uniform3ui = getFunction<OpenGL::Uniform3UI>("glUniform3ui");
		OpenGL::uniform3uiv = getFunction<OpenGL::Uniform3UIV>("glUniform3uiv");
		OpenGL::uniform4ui = getFunction<OpenGL::Uniform4UI>("glUniform4ui");
		OpenGL::uniform4uiv = getFunction<OpenGL::Uniform4UIV>("glUniform4uiv");
		OpenGL::vertexAttribI1i = getFunction<OpenGL::VertexAttribI1I>("glVertexAttribI1i");
		OpenGL::vertexAttribI1iv = getFunction<OpenGL::VertexAttribI1IV>("glVertexAttribI1iv");
		OpenGL::vertexAttribI1ui = getFunction<OpenGL::VertexAttribI1UI>("glVertexAttribI1ui");
		OpenGL::vertexAttribI1uiv = getFunction<OpenGL::VertexAttribI1UIV>("glVertexAttribI1uiv");
		OpenGL::vertexAttribI2i = getFunction<OpenGL::VertexAttribI2I>("glVertexAttribI2i");
		OpenGL::vertexAttribI2iv = getFunction<OpenGL::VertexAttribI2IV>("glVertexAttribI2iv");
		OpenGL::vertexAttribI2ui = getFunction<OpenGL::VertexAttribI2UI>("glVertexAttribI2ui");
		OpenGL::vertexAttribI2uiv = getFunction<OpenGL::VertexAttribI2UIV>("glVertexAttribI2uiv");
		OpenGL::vertexAttribI3i = getFunction<OpenGL::VertexAttribI3I>("glVertexAttribI3i");
		OpenGL::vertexAttribI3iv = getFunction<OpenGL::VertexAttribI3IV>("glVertexAttribI3iv");
		OpenGL::vertexAttribI3ui = getFunction<OpenGL::VertexAttribI3UI>("glVertexAttribI3ui");
		OpenGL::vertexAttribI3uiv = getFunction<OpenGL::VertexAttribI3UIV>("glVertexAttribI3uiv");
		OpenGL::vertexAttribI4bv = getFunction<OpenGL::VertexAttribI4BV>("glVertexAttribI4bv");
		OpenGL::vertexAttribI4i = getFunction<OpenGL::VertexAttribI4I>("glVertexAttribI4i");
		OpenGL::vertexAttribI4iv = getFunction<OpenGL::VertexAttribI4IV>("glVertexAttribI4iv");
		OpenGL::vertexAttribI4sv = getFunction<OpenGL::VertexAttribI4SV>("glVertexAttribI4sv");
		OpenGL::vertexAttribI4ubv = getFunction<OpenGL::VertexAttribI4UBV>("glVertexAttribI4ubv");
		OpenGL::vertexAttribI4ui = getFunction<OpenGL::VertexAttribI4UI>("glVertexAttribI4ui");
		OpenGL::vertexAttribI4uiv = getFunction<OpenGL::VertexAttribI4UIV>("glVertexAttribI4uiv");
		OpenGL::vertexAttribI4usv = getFunction<OpenGL::VertexAttribI4USV>("glVertexAttribI4usv");
		OpenGL::vertexAttribIPointer = getFunction<OpenGL::VertexAttribIPointer>("glVertexAttribIPointer");

		// Version 3.1

		OpenGL::copyBufferSubData = getFunction<OpenGL::CopyBufferSubData>("glCopyBufferSubData");
		OpenGL::drawArraysInstanced = getFunction<OpenGL::DrawArraysInstanced>("glDrawArraysInstanced");
		OpenGL::drawElementsInstanced = getFunction<OpenGL::DrawElementsInstanced>("glDrawElementsInstanced");
		OpenGL::getActiveUniformBlockiv = getFunction<OpenGL::GetActiveUniformBlockIV>("glGetActiveUniformBlockiv");

		OpenGL::getActiveUniformBlockName = getFunction<OpenGL::GetActiveUniformBlockName>(
			"glGetActiveUniformBlockName");

		OpenGL::getActiveUniformName = getFunction<OpenGL::GetActiveUniformName>("glGetActiveUniformName");
		OpenGL::getActiveUniformsiv = getFunction<OpenGL::GetActiveUniformsIV>("glGetActiveUniformsiv");
		OpenGL::getUniformBlockIndex = getFunction<OpenGL::GetUniformBlockIndex>("glGetUniformBlockIndex");
		OpenGL::getUniformIndices = getFunction<OpenGL::GetUniformIndices>("glGetUniformIndices");
		OpenGL::primitiveRestartIndex = getFunction<OpenGL::PrimitiveRestartIndex>("glPrimitiveRestartIndex");
		OpenGL::texBuffer = getFunction<OpenGL::TexBuffer>("glTexBuffer");
		OpenGL::uniformBlockBinding = getFunction<OpenGL::UniformBlockBinding>("glUniformBlockBinding");

		// Version 3.2

		OpenGL::clientWaitSync = getFunction<OpenGL::ClientWaitSync>("glClientWaitSync");
		OpenGL::deleteSync = getFunction<OpenGL::DeleteSync>("glDeleteSync");
		OpenGL::drawElementsBaseVertex = getFunction<OpenGL::DrawElementsBaseVertex>("glDrawElementsBaseVertex");

		OpenGL::drawElementsInstancedBaseVertex = getFunction<OpenGL::DrawElementsInstancedBaseVertex>(
			"glDrawElementsInstancedBaseVertex");

		OpenGL::drawRangeElementsBaseVertex = getFunction<OpenGL::DrawRangeElementsBaseVertex>(
			"glDrawRangeElementsBaseVertex");

		OpenGL::fenceSync = getFunction<OpenGL::FenceSync>("glFenceSync");
		OpenGL::framebufferTexture = getFunction<OpenGL::FramebufferTexture>("glFramebufferTexture");
		OpenGL::getBufferParameteri64v = getFunction<OpenGL::GetBufferParameterI64V>("glGetBufferParameteri64v");
		OpenGL::getInteger64i_v = getFunction<OpenGL::GetInteger64I_V>("glGetInteger64i_v");
		OpenGL::getInteger64v = getFunction<OpenGL::GetInteger64V>("glGetInteger64v");
		OpenGL::getMultisamplefv = getFunction<OpenGL::GetMultisampleFV>("glGetMultisamplefv");
		OpenGL::getSynciv = getFunction<OpenGL::GetSyncIV>("glGetSynciv");
		OpenGL::isSync = getFunction<OpenGL::IsSync>("glIsSync");

		OpenGL::multiDrawElementsBaseVertex = getFunction<OpenGL::MultiDrawElementsBaseVertex>(
			"glMultiDrawElementsBaseVertex");

		OpenGL::provokingVertex = getFunction<OpenGL::ProvokingVertex>("glProvokingVertex");
		OpenGL::sampleMaski = getFunction<OpenGL::SampleMaskI>("glSampleMaski");
		OpenGL::texImage2DMultisample = getFunction<OpenGL::TexImage2DMultisample>("glTexImage2DMultisample");
		OpenGL::texImage3DMultisample = getFunction<OpenGL::TexImage3DMultisample>("glTexImage3DMultisample");
		OpenGL::waitSync = getFunction<OpenGL::WaitSync>("glWaitSync");

		// Version 3.3

		OpenGL::bindFragDataLocationIndexed = getFunction<OpenGL::BindFragDataLocationIndexed>(
			"glBindFragDataLocationIndexed");

		OpenGL::bindSampler = getFunction<OpenGL::BindSampler>("glBindSampler");
		OpenGL::deleteSamplers = getFunction<OpenGL::DeleteSamplers>("glDeleteSamplers");
		OpenGL::genSamplers = getFunction<OpenGL::GenSamplers>("glGenSamplers");
		OpenGL::getFragDataIndex = getFunction<OpenGL::GetFragDataIndex>("glGetFragDataIndex");
		OpenGL::getQueryObjecti64v = getFunction<OpenGL::GetQueryObjectI64V>("glGetQueryObjecti64v");
		OpenGL::getQueryObjectui64v = getFunction<OpenGL::GetQueryObjectUI64V>("glGetQueryObjectui64v");
		OpenGL::getSamplerParameterfv = getFunction<OpenGL::GetSamplerParameterFV>("glGetSamplerParameterfv");
		OpenGL::getSamplerParameterIiv = getFunction<OpenGL::GetSamplerParameterIIV>("glGetSamplerParameterIiv");
		OpenGL::getSamplerParameterIuiv = getFunction<OpenGL::GetSamplerParameterIUIV>("glGetSamplerParameterIuiv");
		OpenGL::getSamplerParameteriv = getFunction<OpenGL::GetSamplerParameterIV>("glGetSamplerParameteriv");
		OpenGL::isSampler = getFunction<OpenGL::IsSampler>("glIsSampler");
		OpenGL::queryCounter = getFunction<OpenGL::QueryCounter>("glQueryCounter");
		OpenGL::samplerParameterf = getFunction<OpenGL::SamplerParameterF>("glSamplerParameterf");
		OpenGL::samplerParameterfv = getFunction<OpenGL::SamplerParameterFV>("glSamplerParameterfv");
		OpenGL::samplerParameteri = getFunction<OpenGL::SamplerParameterI>("glSamplerParameteri");
		OpenGL::samplerParameteriv = getFunction<OpenGL::SamplerParameterIV>("glSamplerParameteriv");
		OpenGL::samplerParameterIiv = getFunction<OpenGL::SamplerParameterIIV>("glSamplerParameterIiv");
		OpenGL::samplerParameterIuiv = getFunction<OpenGL::SamplerParameterIUIV>("glSamplerParameterIuiv");
		OpenGL::vertexAttribDivisor = getFunction<OpenGL::VertexAttribDivisor>("glVertexAttribDivisor");
		OpenGL::vertexAttribP1ui = getFunction<OpenGL::VertexAttribP1UI>("glVertexAttribP1ui");
		OpenGL::vertexAttribP1uiv = getFunction<OpenGL::VertexAttribP1UIV>("glVertexAttribP1uiv");
		OpenGL::vertexAttribP2ui = getFunction<OpenGL::VertexAttribP2UI>("glVertexAttribP2ui");
		OpenGL::vertexAttribP2uiv = getFunction<OpenGL::VertexAttribP2UIV>("glVertexAttribP2uiv");
		OpenGL::vertexAttribP3ui = getFunction<OpenGL::VertexAttribP3UI>("glVertexAttribP3ui");
		OpenGL::vertexAttribP3uiv = getFunction<OpenGL::VertexAttribP3UIV>("glVertexAttribP3uiv");
		OpenGL::vertexAttribP4ui = getFunction<OpenGL::VertexAttribP4UI>("glVertexAttribP4ui");
		OpenGL::vertexAttribP4uiv = getFunction<OpenGL::VertexAttribP4UIV>("glVertexAttribP4uiv");

		// Version 4.0

		OpenGL::beginQueryIndexed = getFunction<OpenGL::BeginQueryIndexed>("glBeginQueryIndexed");
		OpenGL::bindTransformFeedback = getFunction<OpenGL::BindTransformFeedback>("glBindTransformFeedback");
		OpenGL::blendEquationi = getFunction<OpenGL::BlendEquationI>("glBlendEquationi");
		OpenGL::blendEquationSeparatei = getFunction<OpenGL::BlendEquationSeparateI>("glBlendEquationSeparatei");
		OpenGL::blendFunci = getFunction<OpenGL::BlendFuncI>("glBlendFunci");
		OpenGL::blendFuncSeparatei = getFunction<OpenGL::BlendFuncSeparateI>("glBlendFuncSeparatei");
		OpenGL::deleteTransformFeedbacks = getFunction<OpenGL::DeleteTransformFeedbacks>("glDeleteTransformFeedbacks");
		OpenGL::drawArraysIndirect = getFunction<OpenGL::DrawArraysIndirect>("glDrawArraysIndirect");
		OpenGL::drawElementsIndirect = getFunction<OpenGL::DrawElementsIndirect>("glDrawElementsIndirect");
		OpenGL::drawTransformFeedback = getFunction<OpenGL::DrawTransformFeedback>("glDrawTransformFeedback");

		OpenGL::drawTransformFeedbackStream = getFunction<OpenGL::DrawTransformFeedbackStream>(
			"glDrawTransformFeedbackStream");

		OpenGL::endQueryIndexed = getFunction<OpenGL::EndQueryIndexed>("glEndQueryIndexed");
		OpenGL::genTransformFeedbacks = getFunction<OpenGL::GenTransformFeedbacks>("glGenTransformFeedbacks");
		OpenGL::getActiveSubroutineName = getFunction<OpenGL::GetActiveSubroutineName>("glGetActiveSubroutineName");

		OpenGL::getActiveSubroutineUniformiv = getFunction<OpenGL::GetActiveSubroutineUniformIV>(
			"glGetActiveSubroutineUniformiv");

		OpenGL::getActiveSubroutineUniformName = getFunction<OpenGL::GetActiveSubroutineUniformName>(
			"glGetActiveSubroutineUniformName");

		OpenGL::getProgramStageiv = getFunction<OpenGL::GetProgramStageIV>("glGetProgramStageiv");
		OpenGL::getQueryIndexediv = getFunction<OpenGL::GetQueryIndexedIV>("glGetQueryIndexediv");
		OpenGL::getSubroutineIndex = getFunction<OpenGL::GetSubroutineIndex>("glGetSubroutineIndex");

		OpenGL::getSubroutineUniformLocation = getFunction<OpenGL::GetSubroutineUniformLocation>(
			"glGetSubroutineUniformLocation");

		OpenGL::getUniformdv = getFunction<OpenGL::GetUniformDV>("glGetUniformdv");
		OpenGL::getUniformSubroutineuiv = getFunction<OpenGL::GetUniformSubroutineUIV>("glGetUniformSubroutineuiv");
		OpenGL::isTransformFeedback = getFunction<OpenGL::IsTransformFeedback>("glIsTransformFeedback");
		OpenGL::minSampleShading = getFunction<OpenGL::MinSampleShading>("glMinSampleShading");
		OpenGL::patchParameterfv = getFunction<OpenGL::PatchParameterFV>("glPatchParameterfv");
		OpenGL::patchParameteri = getFunction<OpenGL::PatchParameterI>("glPatchParameteri");
		OpenGL::pauseTransformFeedback = getFunction<OpenGL::PauseTransformFeedback>("glPauseTransformFeedback");
		OpenGL::resumeTransformFeedback = getFunction<OpenGL::ResumeTransformFeedback>("glResumeTransformFeedback");
		OpenGL::uniform1d = getFunction<OpenGL::Uniform1D>("glUniform1d");
		OpenGL::uniform1dv = getFunction<OpenGL::Uniform1DV>("glUniform1dv");
		OpenGL::uniform2d = getFunction<OpenGL::Uniform2D>("glUniform2d");
		OpenGL::uniform2dv = getFunction<OpenGL::Uniform2DV>("glUniform2dv");
		OpenGL::uniform3d = getFunction<OpenGL::Uniform3D>("glUniform3d");
		OpenGL::uniform3dv = getFunction<OpenGL::Uniform3DV>("glUniform3dv");
		OpenGL::uniform4d = getFunction<OpenGL::Uniform4D>("glUniform4d");
		OpenGL::uniform4dv = getFunction<OpenGL::Uniform4DV>("glUniform4dv");
		OpenGL::uniformMatrix2dv = getFunction<OpenGL::UniformMatrix2DV>("glUniformMatrix2dv");
		OpenGL::uniformMatrix2x3dv = getFunction<OpenGL::UniformMatrix2X3DV>("glUniformMatrix2x3dv");
		OpenGL::uniformMatrix2x4dv = getFunction<OpenGL::UniformMatrix2X4DV>("glUniformMatrix2x4dv");
		OpenGL::uniformMatrix3dv = getFunction<OpenGL::UniformMatrix3DV>("glUniformMatrix3dv");
		OpenGL::uniformMatrix3x2dv = getFunction<OpenGL::UniformMatrix3X2DV>("glUniformMatrix3x2dv");
		OpenGL::uniformMatrix3x4dv = getFunction<OpenGL::UniformMatrix3X4DV>("glUniformMatrix3x4dv");
		OpenGL::uniformMatrix4dv = getFunction<OpenGL::UniformMatrix4DV>("glUniformMatrix4dv");
		OpenGL::uniformMatrix4x2dv = getFunction<OpenGL::UniformMatrix4X2DV>("glUniformMatrix4x2dv");
		OpenGL::uniformMatrix4x3dv = getFunction<OpenGL::UniformMatrix4X3DV>("glUniformMatrix4x3dv");
		OpenGL::uniformSubroutinesuiv = getFunction<OpenGL::UniformSubroutineSUIV>("glUniformSubroutinesuiv");

		// Version 4.1

		OpenGL::activeShaderProgram = getFunction<OpenGL::ActiveShaderProgram>("glActiveShaderProgram");
		OpenGL::bindProgramPipeline = getFunction<OpenGL::BindProgramPipeline>("glBindProgramPipeline");
		OpenGL::clearDepthf = getFunction<OpenGL::ClearDepthF>("glClearDepthf");
		OpenGL::createShaderProgramv = getFunction<OpenGL::CreateShaderProgramV>("glCreateShaderProgramv");
		OpenGL::deleteProgramPipelines = getFunction<OpenGL::DeleteProgramPipelines>("glDeleteProgramPipelines");
		OpenGL::depthRangeArrayv = getFunction<OpenGL::DepthRangeArrayV>("glDepthRangeArrayv");
		OpenGL::depthRangef = getFunction<OpenGL::DepthRangeF>("glDepthRangef");
		OpenGL::depthRangeIndexed = getFunction<OpenGL::DepthRangeIndexed>("glDepthRangeIndexed");
		OpenGL::genProgramPipelines = getFunction<OpenGL::GenProgramPipelines>("glGenProgramPipelines");
		OpenGL::getDoublei_v = getFunction<OpenGL::GetDoubleI_V>("glGetDoublei_v");
		OpenGL::getFloati_v = getFunction<OpenGL::GetFloatI_V>("glGetFloati_v");
		OpenGL::getProgramBinary = getFunction<OpenGL::GetProgramBinary>("glGetProgramBinary");

		OpenGL::getProgramPipelineInfoLog = getFunction<OpenGL::GetProgramPipelineInfoLog>(
			"glGetProgramPipelineInfoLog");

		OpenGL::getProgramPipelineiv = getFunction<OpenGL::GetProgramPipelineIV>("glGetProgramPipelineiv");
		OpenGL::getShaderPrecisionFormat = getFunction<OpenGL::GetShaderPrecisionFormat>("glGetShaderPrecisionFormat");
		OpenGL::getVertexAttribLdv = getFunction<OpenGL::GetVertexAttribLDV>("glGetVertexAttribLdv");
		OpenGL::isProgramPipeline = getFunction<OpenGL::IsProgramPipeline>("glIsProgramPipeline");
		OpenGL::programBinary = getFunction<OpenGL::ProgramBinary>("glProgramBinary");
		OpenGL::programParameteri = getFunction<OpenGL::ProgramParameterI>("glProgramParameteri");
		OpenGL::programUniform1d = getFunction<OpenGL::ProgramUniform1D>("glProgramUniform1d");
		OpenGL::programUniform1dv = getFunction<OpenGL::ProgramUniform1DV>("glProgramUniform1dv");
		OpenGL::programUniform1f = getFunction<OpenGL::ProgramUniform1F>("glProgramUniform1f");
		OpenGL::programUniform1fv = getFunction<OpenGL::ProgramUniform1FV>("glProgramUniform1fv");
		OpenGL::programUniform1i = getFunction<OpenGL::ProgramUniform1I>("glProgramUniform1i");
		OpenGL::programUniform1iv = getFunction<OpenGL::ProgramUniform1IV>("glProgramUniform1iv");
		OpenGL::programUniform1ui = getFunction<OpenGL::ProgramUniform1UI>("glProgramUniform1ui");
		OpenGL::programUniform1uiv = getFunction<OpenGL::ProgramUniform1UIV>("glProgramUniform1uiv");
		OpenGL::programUniform2d = getFunction<OpenGL::ProgramUniform2D>("glProgramUniform2d");
		OpenGL::programUniform2dv = getFunction<OpenGL::ProgramUniform2DV>("glProgramUniform2dv");
		OpenGL::programUniform2f = getFunction<OpenGL::ProgramUniform2F>("glProgramUniform2f");
		OpenGL::programUniform2fv = getFunction<OpenGL::ProgramUniform2FV>("glProgramUniform2fv");
		OpenGL::programUniform2i = getFunction<OpenGL::ProgramUniform2I>("glProgramUniform2i");
		OpenGL::programUniform2iv = getFunction<OpenGL::ProgramUniform2IV>("glProgramUniform2iv");
		OpenGL::programUniform2ui = getFunction<OpenGL::ProgramUniform2UI>("glProgramUniform2ui");
		OpenGL::programUniform2uiv = getFunction<OpenGL::ProgramUniform2UIV>("glProgramUniform2uiv");
		OpenGL::programUniform3d = getFunction<OpenGL::ProgramUniform3D>("glProgramUniform3d");
		OpenGL::programUniform3dv = getFunction<OpenGL::ProgramUniform3DV>("glProgramUniform3dv");
		OpenGL::programUniform3f = getFunction<OpenGL::ProgramUniform3F>("glProgramUniform3f");
		OpenGL::programUniform3fv = getFunction<OpenGL::ProgramUniform3FV>("glProgramUniform3fv");
		OpenGL::programUniform3i = getFunction<OpenGL::ProgramUniform3I>("glProgramUniform3i");
		OpenGL::programUniform3iv = getFunction<OpenGL::ProgramUniform3IV>("glProgramUniform3iv");
		OpenGL::programUniform3ui = getFunction<OpenGL::ProgramUniform3UI>("glProgramUniform3ui");
		OpenGL::programUniform3uiv = getFunction<OpenGL::ProgramUniform3UIV>("glProgramUniform3uiv");
		OpenGL::programUniform4d = getFunction<OpenGL::ProgramUniform4D>("glProgramUniform4d");
		OpenGL::programUniform4dv = getFunction<OpenGL::ProgramUniform4DV>("glProgramUniform4dv");
		OpenGL::programUniform4f = getFunction<OpenGL::ProgramUniform4F>("glProgramUniform4f");
		OpenGL::programUniform4fv = getFunction<OpenGL::ProgramUniform4FV>("glProgramUniform4fv");
		OpenGL::programUniform4i = getFunction<OpenGL::ProgramUniform4I>("glProgramUniform4i");
		OpenGL::programUniform4iv = getFunction<OpenGL::ProgramUniform4IV>("glProgramUniform4iv");
		OpenGL::programUniform4ui = getFunction<OpenGL::ProgramUniform4UI>("glProgramUniform4ui");
		OpenGL::programUniform4uiv = getFunction<OpenGL::ProgramUniform4UIV>("glProgramUniform4uiv");
		OpenGL::programUniformMatrix2dv = getFunction<OpenGL::ProgramUniformMatrix2DV>("glProgramUniformMatrix2dv");
		OpenGL::programUniformMatrix2fv = getFunction<OpenGL::ProgramUniformMatrix2FV>("glProgramUniformMatrix2fv");

		OpenGL::programUniformMatrix2x3dv = getFunction<OpenGL::ProgramUniformMatrix2X3DV>(
			"glProgramUniformMatrix2x3dv");

		OpenGL::programUniformMatrix2x3fv = getFunction<OpenGL::ProgramUniformMatrix2X3FV>(
			"glProgramUniformMatrix2x3fv");

		OpenGL::programUniformMatrix2x4dv = getFunction<OpenGL::ProgramUniformMatrix2X4DV>(
			"glProgramUniformMatrix2x4dv");

		OpenGL::programUniformMatrix2x4fv = getFunction<OpenGL::ProgramUniformMatrix2X4FV>(
			"glProgramUniformMatrix2x4fv");

		OpenGL::programUniformMatrix3dv = getFunction<OpenGL::ProgramUniformMatrix3DV>("glProgramUniformMatrix3dv");
		OpenGL::programUniformMatrix3fv = getFunction<OpenGL::ProgramUniformMatrix3FV>("glProgramUniformMatrix3fv");

		OpenGL::programUniformMatrix3x2dv = getFunction<OpenGL::ProgramUniformMatrix3X2DV>(
			"glProgramUniformMatrix3x2dv");

		OpenGL::programUniformMatrix3x2fv = getFunction<OpenGL::ProgramUniformMatrix3X2FV>(
			"glProgramUniformMatrix3x2fv");

		OpenGL::programUniformMatrix3x4dv = getFunction<OpenGL::ProgramUniformMatrix3X4DV>(
			"glProgramUniformMatrix3x4dv");

		OpenGL::programUniformMatrix3x4fv = getFunction<OpenGL::ProgramUniformMatrix3X4FV>(
			"glProgramUniformMatrix3x4fv");

		OpenGL::programUniformMatrix4dv = getFunction<OpenGL::ProgramUniformMatrix4DV>("glProgramUniformMatrix4dv");
		OpenGL::programUniformMatrix4fv = getFunction<OpenGL::ProgramUniformMatrix4FV>("glProgramUniformMatrix4fv");

		OpenGL::programUniformMatrix4x2dv = getFunction<OpenGL::ProgramUniformMatrix4X2DV>(
			"glProgramUniformMatrix4x2dv");

		OpenGL::programUniformMatrix4x2fv = getFunction<OpenGL::ProgramUniformMatrix4X2FV>(
			"glProgramUniformMatrix4x2fv");

		OpenGL::programUniformMatrix4x3dv = getFunction<OpenGL::ProgramUniformMatrix4X3DV>(
			"glProgramUniformMatrix4x3dv");

		OpenGL::programUniformMatrix4x3fv = getFunction<OpenGL::ProgramUniformMatrix4X3FV>(
			"glProgramUniformMatrix4x3fv");

		OpenGL::releaseShaderCompiler = getFunction<OpenGL::ReleaseShaderCompiler>("glReleaseShaderCompiler");
		OpenGL::shaderBinary = getFunction<OpenGL::ShaderBinary>("glShaderBinary");
		OpenGL::scissorArrayv = getFunction<OpenGL::ScissorArrayV>("glScissorArrayv");
		OpenGL::scissorIndexed = getFunction<OpenGL::ScissorIndexed>("glScissorIndexed");
		OpenGL::scissorIndexedv = getFunction<OpenGL::ScissorIndexedV>("glScissorIndexedv");
		OpenGL::useProgramStages = getFunction<OpenGL::UseProgramStages>("glUseProgramStages");
		OpenGL::validateProgramPipeline = getFunction<OpenGL::ValidateProgramPipeline>("glValidateProgramPipeline");
		OpenGL::vertexAttribL1d = getFunction<OpenGL::VertexAttribL1D>("glVertexAttribL1d");
		OpenGL::vertexAttribL1dv = getFunction<OpenGL::VertexAttribL1DV>("glVertexAttribL1dv");
		OpenGL::vertexAttribL2d = getFunction<OpenGL::VertexAttribL2D>("glVertexAttribL2d");
		OpenGL::vertexAttribL2dv = getFunction<OpenGL::VertexAttribL2DV>("glVertexAttribL2dv");
		OpenGL::vertexAttribL3d = getFunction<OpenGL::VertexAttribL3D>("glVertexAttribL3d");
		OpenGL::vertexAttribL3dv = getFunction<OpenGL::VertexAttribL3DV>("glVertexAttribL3dv");
		OpenGL::vertexAttribL4d = getFunction<OpenGL::VertexAttribL4D>("glVertexAttribL4d");
		OpenGL::vertexAttribL4dv = getFunction<OpenGL::VertexAttribL4DV>("glVertexAttribL4dv");
		OpenGL::vertexAttribLPointer = getFunction<OpenGL::VertexAttribLPointer>("glVertexAttribLPointer");
		OpenGL::viewportArrayv = getFunction<OpenGL::ViewportArrayV>("glViewportArrayv");
		OpenGL::viewportIndexedf = getFunction<OpenGL::ViewportIndexedF>("glViewportIndexedf");
		OpenGL::viewportIndexedfv = getFunction<OpenGL::ViewportIndexedFV>("glViewportIndexedfv");

		// Version 4.2

		OpenGL::bindImageTexture = getFunction<OpenGL::BindImageTexture>("glBindImageTexture");

		OpenGL::drawArraysInstancedBaseInstance = getFunction<OpenGL::DrawArraysInstancedBaseInstance>(
			"glDrawArraysInstancedBaseInstance");

		OpenGL::drawElementsInstancedBaseInstance = getFunction<OpenGL::DrawElementsInstancedBaseInstance>(
			"glDrawElementsInstancedBaseInstance");

		OpenGL::drawElementsInstancedBaseVertexBaseInstance =
			getFunction<OpenGL::DrawElementsInstancedBaseVertexBaseInstance>(
			"glDrawElementsInstancedBaseVertexBaseInstance");

		OpenGL::drawTransformFeedbackInstanced = getFunction<OpenGL::DrawTransformFeedbackInstanced>(
			"glDrawTransformFeedbackInstanced");

		OpenGL::drawTransformFeedbackStreamInstanced = getFunction<OpenGL::DrawTransformFeedbackStreamInstanced>(
			"glDrawTransformFeedbackStreamInstanced");

		OpenGL::getActiveAtomicCounterBufferiv = getFunction<OpenGL::GetActiveAtomicCounterBufferIV>(
			"glGetActiveAtomicCounterBufferiv");

		OpenGL::getInternalformativ = getFunction<OpenGL::GetInternalformatIV>("glGetInternalformativ");
		OpenGL::memoryBarrier = getFunction<OpenGL::MemoryBarrier>("glMemoryBarrier");
		OpenGL::texStorage1D = getFunction<OpenGL::TexStorage1D>("glTexStorage1D");
		OpenGL::texStorage2D = getFunction<OpenGL::TexStorage2D>("glTexStorage2D");
		OpenGL::texStorage3D = getFunction<OpenGL::TexStorage3D>("glTexStorage3D");

		// Version 4.3

		OpenGL::bindVertexBuffer = getFunction<OpenGL::BindVertexBuffer>("glBindVertexBuffer");
		OpenGL::clearBufferData = getFunction<OpenGL::ClearBufferData>("glClearBufferData");
		OpenGL::clearBufferSubData = getFunction<OpenGL::ClearBufferSubData>("glClearBufferSubData");
		OpenGL::copyImageSubData = getFunction<OpenGL::CopyImageSubData>("glCopyImageSubData");
		OpenGL::dispatchCompute = getFunction<OpenGL::DispatchCompute>("glDispatchCompute");
		OpenGL::dispatchComputeIndirect = getFunction<OpenGL::DispatchComputeIndirect>("glDispatchComputeIndirect");
		OpenGL::debugMessageCallback = getFunction<OpenGL::DebugMessageCallback>("glDebugMessageCallback");
		OpenGL::debugMessageControl = getFunction<OpenGL::DebugMessageControl>("glDebugMessageControl");
		OpenGL::debugMessageInsert = getFunction<OpenGL::DebugMessageInsert>("glDebugMessageInsert");
		OpenGL::framebufferParameteri = getFunction<OpenGL::FramebufferParameterI>("glFramebufferParameteri");
		OpenGL::getDebugMessageLog = getFunction<OpenGL::GetDebugMessageLog>("glGetDebugMessageLog");

		OpenGL::getFramebufferParameteriv = getFunction<OpenGL::GetFramebufferParameterIV>(
			"glGetFramebufferParameteriv");

		OpenGL::getInternalformati64v = getFunction<OpenGL::GetInternalformatI64V>("glGetInternalformati64v");
		OpenGL::getObjectLabel = getFunction<OpenGL::GetObjectLabel>("glGetObjectLabel");
		OpenGL::getObjectPtrLabel = getFunction<OpenGL::GetObjectPtrLabel>("glGetObjectPtrLabel");
		OpenGL::getProgramInterfaceiv = getFunction<OpenGL::GetProgramInterfaceIV>("glGetProgramInterfaceiv");
		OpenGL::getProgramResourceIndex = getFunction<OpenGL::GetProgramResourceIndex>("glGetProgramResourceIndex");
		OpenGL::getProgramResourceiv = getFunction<OpenGL::GetProgramResourceIV>("glGetProgramResourceiv");

		OpenGL::getProgramResourceLocation = getFunction<OpenGL::GetProgramResourceLocation>(
			"glGetProgramResourceLocation");

		OpenGL::getProgramResourceLocationIndex = getFunction<OpenGL::GetProgramResourceLocationIndex>(
			"glGetProgramResourceLocationIndex");

		OpenGL::getProgramResourceName = getFunction<OpenGL::GetProgramResourceName>("glGetProgramResourceName");
		OpenGL::invalidateBufferData = getFunction<OpenGL::InvalidateBufferData>("glInvalidateBufferData");
		OpenGL::invalidateBufferSubData = getFunction<OpenGL::InvalidateBufferSubData>("glInvalidateBufferSubData");
		OpenGL::invalidateFramebuffer = getFunction<OpenGL::InvalidateFramebuffer>("glInvalidateFramebuffer");
		OpenGL::invalidateSubFramebuffer = getFunction<OpenGL::InvalidateSubFramebuffer>("glInvalidateSubFramebuffer");
		OpenGL::invalidateTexImage = getFunction<OpenGL::InvalidateTexImage>("glInvalidateTexImage");
		OpenGL::invalidateTexSubImage = getFunction<OpenGL::InvalidateTexSubImage>("glInvalidateTexSubImage");
		OpenGL::multiDrawArraysIndirect = getFunction<OpenGL::MultiDrawArraysIndirect>("glMultiDrawArraysIndirect");

		OpenGL::multiDrawElementsIndirect = getFunction<OpenGL::MultiDrawElementsIndirect>(
			"glMultiDrawElementsIndirect");

		OpenGL::objectLabel = getFunction<OpenGL::ObjectLabel>("glObjectLabel");
		OpenGL::objectPtrLabel = getFunction<OpenGL::ObjectPtrLabel>("glObjectPtrLabel");
		OpenGL::popDebugGroup = getFunction<OpenGL::PopDebugGroup>("glPopDebugGroup");
		OpenGL::pushDebugGroup = getFunction<OpenGL::PushDebugGroup>("glPushDebugGroup");

		OpenGL::shaderStorageBlockBinding = getFunction<OpenGL::ShaderStorageBlockBinding>(
			"glShaderStorageBlockBinding");

		OpenGL::texBufferRange = getFunction<OpenGL::TexBufferRange>("glTexBufferRange");
		OpenGL::texStorage2DMultisample = getFunction<OpenGL::TexStorage2DMultisample>("glTexStorage2DMultisample");
		OpenGL::texStorage3DMultisample = getFunction<OpenGL::TexStorage3DMultisample>("glTexStorage3DMultisample");
		OpenGL::textureView = getFunction<OpenGL::TextureView>("glTextureView");
		OpenGL::vertexAttribBinding = getFunction<OpenGL::VertexAttribBinding>("glVertexAttribBinding");
		OpenGL::vertexAttribFormat = getFunction<OpenGL::VertexAttribFormat>("glVertexAttribFormat");
		OpenGL::vertexAttribIFormat = getFunction<OpenGL::VertexAttribIFormat>("glVertexAttribIFormat");
		OpenGL::vertexAttribLFormat = getFunction<OpenGL::VertexAttribLFormat>("glVertexAttribLFormat");
		OpenGL::vertexBindingDivisor = getFunction<OpenGL::VertexBindingDivisor>("glVertexBindingDivisor");

		// Version 4.4

		OpenGL::bindBuffersBase = getFunction<OpenGL::BindBuffersBase>("glBindBuffersBase");
		OpenGL::bindBuffersRange = getFunction<OpenGL::BindBuffersRange>("glBindBuffersRange");
		OpenGL::bindImageTextures = getFunction<OpenGL::BindImageTextures>("glBindImageTextures");
		OpenGL::bindSamplers = getFunction<OpenGL::BindSamplers>("glBindSamplers");
		OpenGL::bindTextures = getFunction<OpenGL::BindTextures>("glBindTextures");
		OpenGL::bindVertexBuffers = getFunction<OpenGL::BindVertexBuffers>("glBindVertexBuffers");
		OpenGL::bufferStorage = getFunction<OpenGL::BufferStorage>("glBufferStorage");
		OpenGL::clearTexImage = getFunction<OpenGL::ClearTexImage>("glClearTexImage");
		OpenGL::clearTexSubImage = getFunction<OpenGL::ClearTexSubImage>("glClearTexSubImage");

		// Version 4.5

		OpenGL::bindTextureUnit = getFunction<OpenGL::BindTextureUnit>("glBindTextureUnit");
		OpenGL::blitNamedFramebuffer = getFunction<OpenGL::BlitNamedFramebuffer>("glBlitNamedFramebuffer");

		OpenGL::checkNamedFramebufferStatus = getFunction<OpenGL::CheckNamedFramebufferStatus>(
			"glCheckNamedFramebufferStatus");

		OpenGL::clearNamedBufferData = getFunction<OpenGL::ClearNamedBufferData>("glClearNamedBufferData");
		OpenGL::clearNamedBufferSubData = getFunction<OpenGL::ClearNamedBufferSubData>("glClearNamedBufferSubData");
		OpenGL::clearNamedFramebufferfi = getFunction<OpenGL::ClearNamedFramebufferFI>("glClearNamedFramebufferfi");
		OpenGL::clearNamedFramebufferfv = getFunction<OpenGL::ClearNamedFramebufferFV>("glClearNamedFramebufferfv");
		OpenGL::clearNamedFramebufferiv = getFunction<OpenGL::ClearNamedFramebufferIV>("glClearNamedFramebufferiv");
		OpenGL::clearNamedFramebufferuiv = getFunction<OpenGL::ClearNamedFramebufferUIV>("glClearNamedFramebufferuiv");
		OpenGL::clipControl = getFunction<OpenGL::ClipControl>("glClipControl");

		OpenGL::compressedTextureSubImage1D = getFunction<OpenGL::CompressedTextureSubImage1D>(
			"glCompressedTextureSubImage1D");

		OpenGL::compressedTextureSubImage2D = getFunction<OpenGL::CompressedTextureSubImage2D>(
			"glCompressedTextureSubImage2D");

		OpenGL::compressedTextureSubImage3D = getFunction<OpenGL::CompressedTextureSubImage3D>(
			"glCompressedTextureSubImage3D");

		OpenGL::copyNamedBufferSubData = getFunction<OpenGL::CopyNamedBufferSubData>("glCopyNamedBufferSubData");
		OpenGL::copyTextureSubImage1D = getFunction<OpenGL::CopyTextureSubImage1D>("glCopyTextureSubImage1D");
		OpenGL::copyTextureSubImage2D = getFunction<OpenGL::CopyTextureSubImage2D>("glCopyTextureSubImage2D");
		OpenGL::copyTextureSubImage3D = getFunction<OpenGL::CopyTextureSubImage3D>("glCopyTextureSubImage3D");
		OpenGL::createBuffers = getFunction<OpenGL::CreateBuffers>("glCreateBuffers");
		OpenGL::createFramebuffers = getFunction<OpenGL::CreateFramebuffers>("glCreateFramebuffers");
		OpenGL::createProgramPipelines = getFunction<OpenGL::CreateProgramPipelines>("glCreateProgramPipelines");
		OpenGL::createQueries = getFunction<OpenGL::CreateQueries>("glCreateQueries");
		OpenGL::createRenderbuffers = getFunction<OpenGL::CreateRenderbuffers>("glCreateRenderbuffers");
		OpenGL::createSamplers = getFunction<OpenGL::CreateSamplers>("glCreateSamplers");
		OpenGL::createTextures = getFunction<OpenGL::CreateTextures>("glCreateTextures");
		OpenGL::createTransformFeedbacks = getFunction<OpenGL::CreateTransformFeedbacks>("glCreateTransformFeedbacks");
		OpenGL::createVertexArrays = getFunction<OpenGL::CreateVertexArrays>("glCreateVertexArrays");
		OpenGL::disableVertexArrayAttrib = getFunction<OpenGL::DisableVertexArrayAttrib>("glDisableVertexArrayAttrib");
		OpenGL::enableVertexArrayAttrib = getFunction<OpenGL::EnableVertexArrayAttrib>("glEnableVertexArrayAttrib");

		OpenGL::flushMappedNamedBufferRange = getFunction<OpenGL::FlushMappedNamedBufferRange>(
			"glFlushMappedNamedBufferRange");

		OpenGL::generateTextureMipmap = getFunction<OpenGL::GenerateTextureMipmap>("glGenerateTextureMipmap");

		OpenGL::getCompressedTextureImage = getFunction<OpenGL::GetCompressedTextureImage>(
			"glGetCompressedTextureImage");

		OpenGL::getCompressedTextureSubImage = getFunction<OpenGL::GetCompressedTextureSubImage>(
			"glGetCompressedTextureSubImage");

		OpenGL::getGraphicsResetStatus = getFunction<OpenGL::GetGraphicsResetStatus>("glGetGraphicsResetStatus");

		OpenGL::getNamedBufferParameteri64v = getFunction<OpenGL::GetNamedBufferParameterI64V>(
			"glGetNamedBufferParameteri64v");

		OpenGL::getNamedBufferParameteriv = getFunction<OpenGL::GetNamedBufferParameterIV>(
			"glGetNamedBufferParameteriv");

		OpenGL::getNamedBufferPointerv = getFunction<OpenGL::GetNamedBufferPointerV>("glGetNamedBufferPointerv");
		OpenGL::getNamedBufferSubData = getFunction<OpenGL::GetNamedBufferSubData>("glGetNamedBufferSubData");

		OpenGL::getNamedFramebufferAttachmentParameteriv =
			getFunction<OpenGL::GetNamedFramebufferAttachmentParameterIV>(
			"glGetNamedFramebufferAttachmentParameteriv");

		OpenGL::getNamedFramebufferParameteriv = getFunction<OpenGL::GetNamedFramebufferParameterIV>(
			"glGetNamedFramebufferParameteriv");

		OpenGL::getNamedRenderbufferParameteriv = getFunction<OpenGL::GetNamedRenderbufferParameterIV>(
			"glGetNamedRenderbufferParameteriv");

		OpenGL::getnCompressedTexImage = getFunction<OpenGL::GetnCompressedTexImage>("glGetnCompressedTexImage");
		OpenGL::getnTexImage = getFunction<OpenGL::GetnTexImage>("glGetnTexImage");
		OpenGL::getnUniformdv = getFunction<OpenGL::GetnUniformDV>("glGetnUniformdv");
		OpenGL::getnUniformfv = getFunction<OpenGL::GetnUniformFV>("glGetnUniformfv");
		OpenGL::getnUniformiv = getFunction<OpenGL::GetnUniformIV>("glGetnUniformiv");
		OpenGL::getnUniformuiv = getFunction<OpenGL::GetnUniformUIV>("glGetnUniformuiv");
		OpenGL::getQueryBufferObjecti64v = getFunction<OpenGL::GetQueryBufferObjectI64V>("glGetQueryBufferObjecti64v");
		OpenGL::getQueryBufferObjectiv = getFunction<OpenGL::GetQueryBufferObjectIV>("glGetQueryBufferObjectiv");

		OpenGL::getQueryBufferObjectui64v = getFunction<OpenGL::GetQueryBufferObjectUI64V>(
			"glGetQueryBufferObjectui64v");

		OpenGL::getQueryBufferObjectuiv = getFunction<OpenGL::GetQueryBufferObjectUIV>("glGetQueryBufferObjectuiv");
		OpenGL::getTextureImage = getFunction<OpenGL::GetTextureImage>("glGetTextureImage");

		OpenGL::getTextureLevelParameterfv = getFunction<OpenGL::GetTextureLevelParameterFV>(
			"glGetTextureLevelParameterfv");

		OpenGL::getTextureLevelParameteriv = getFunction<OpenGL::GetTextureLevelParameterIV>(
			"glGetTextureLevelParameteriv");

		OpenGL::getTextureParameterfv = getFunction<OpenGL::GetTextureParameterFV>("glGetTextureParameterfv");
		OpenGL::getTextureParameterIiv = getFunction<OpenGL::GetTextureParameterIIV>("glGetTextureParameterIiv");
		OpenGL::getTextureParameteriv = getFunction<OpenGL::GetTextureParameterIV>("glGetTextureParameteriv");
		OpenGL::getTextureParameterIuiv = getFunction<OpenGL::GetTextureParameterIUIV>("glGetTextureParameterIuiv");
		OpenGL::getTextureSubImage = getFunction<OpenGL::GetTextureSubImage>("glGetTextureSubImage");

		OpenGL::getTransformFeedbacki64_v = getFunction<OpenGL::GetTransformFeedbackI64_V>(
			"glGetTransformFeedbacki64_v");

		OpenGL::getTransformFeedbackiv = getFunction<OpenGL::GetTransformFeedbackIV>("glGetTransformFeedbackiv");
		OpenGL::getTransformFeedbacki_v = getFunction<OpenGL::GetTransformFeedbackI_V>("glGetTransformFeedbacki_v");

		OpenGL::getVertexArrayIndexed64iv = getFunction<OpenGL::GetVertexArrayIndexed64IV>(
			"glGetVertexArrayIndexed64iv");

		OpenGL::getVertexArrayIndexediv = getFunction<OpenGL::GetVertexArrayIndexedIV>("glGetVertexArrayIndexediv");
		OpenGL::getVertexArrayiv = getFunction<OpenGL::GetVertexArrayIV>("glGetVertexArrayiv");

		OpenGL::invalidateNamedFramebufferData = getFunction<OpenGL::InvalidateNamedFramebufferData>(
			"glInvalidateNamedFramebufferData");

		OpenGL::invalidateNamedFramebufferSubData = getFunction<OpenGL::InvalidateNamedFramebufferSubData>(
			"glInvalidateNamedFramebufferSubData");

		OpenGL::mapNamedBuffer = getFunction<OpenGL::MapNamedBuffer>("glMapNamedBuffer");
		OpenGL::mapNamedBufferRange = getFunction<OpenGL::MapNamedBufferRange>("glMapNamedBufferRange");
		OpenGL::memoryBarrierByRegion = getFunction<OpenGL::MemoryBarrierByRegion>("glMemoryBarrierByRegion");
		OpenGL::namedBufferData = getFunction<OpenGL::NamedBufferData>("glNamedBufferData");
		OpenGL::namedBufferStorage = getFunction<OpenGL::NamedBufferStorage>("glNamedBufferStorage");
		OpenGL::namedBufferSubData = getFunction<OpenGL::NamedBufferSubData>("glNamedBufferSubData");

		OpenGL::namedFramebufferDrawBuffer = getFunction<OpenGL::NamedFramebufferDrawBuffer>(
			"glNamedFramebufferDrawBuffer");

		OpenGL::namedFramebufferDrawBuffers = getFunction<OpenGL::NamedFramebufferDrawBuffers>(
			"glNamedFramebufferDrawBuffers");

		OpenGL::namedFramebufferParameteri = getFunction<OpenGL::NamedFramebufferParameterI>(
			"glNamedFramebufferParameteri");

		OpenGL::namedFramebufferReadBuffer = getFunction<OpenGL::NamedFramebufferReadBuffer>(
			"glNamedFramebufferReadBuffer");

		OpenGL::namedFramebufferRenderbuffer = getFunction<OpenGL::NamedFramebufferRenderbuffer>(
			"glNamedFramebufferRenderbuffer");

		OpenGL::namedFramebufferTexture = getFunction<OpenGL::NamedFramebufferTexture>("glNamedFramebufferTexture");

		OpenGL::namedFramebufferTextureLayer = getFunction<OpenGL::NamedFramebufferTextureLayer>(
			"glNamedFramebufferTextureLayer");

		OpenGL::namedRenderbufferStorage = getFunction<OpenGL::NamedRenderbufferStorage>("glNamedRenderbufferStorage");

		OpenGL::namedRenderbufferStorageMultisample = getFunction<OpenGL::NamedRenderbufferStorageMultisample>(
			"glNamedRenderbufferStorageMultisample");

		OpenGL::readnPixels = getFunction<OpenGL::ReadnPixels>("glReadnPixels");

		OpenGL::transformFeedbackBufferBase = getFunction<OpenGL::TransformFeedbackBufferBase>(
			"glTransformFeedbackBufferBase");

		OpenGL::transformFeedbackBufferRange = getFunction<OpenGL::TransformFeedbackBufferRange>(
			"glTransformFeedbackBufferRange");

		OpenGL::textureBarrier = getFunction<OpenGL::TextureBarrier>("glTextureBarrier");
		OpenGL::textureBuffer = getFunction<OpenGL::TextureBuffer>("glTextureBuffer");
		OpenGL::textureBufferRange = getFunction<OpenGL::TextureBufferRange>("glTextureBufferRange");
		OpenGL::textureParameterf = getFunction<OpenGL::TextureParameterF>("glTextureParameterf");
		OpenGL::textureParameterfv = getFunction<OpenGL::TextureParameterFV>("glTextureParameterfv");
		OpenGL::textureParameteri = getFunction<OpenGL::TextureParameterI>("glTextureParameteri");
		OpenGL::textureParameterIiv = getFunction<OpenGL::TextureParameterIIV>("glTextureParameterIiv");
		OpenGL::textureParameterIuiv = getFunction<OpenGL::TextureParameterIUIV>("glTextureParameterIuiv");
		OpenGL::textureParameteriv = getFunction<OpenGL::TextureParameterIV>("glTextureParameteriv");
		OpenGL::textureStorage1D = getFunction<OpenGL::TextureStorage1D>("glTextureStorage1D");
		OpenGL::textureStorage2D = getFunction<OpenGL::TextureStorage2D>("glTextureStorage2D");

		OpenGL::textureStorage2DMultisample = getFunction<OpenGL::TextureStorage2DMultisample>(
			"glTextureStorage2DMultisample");

		OpenGL::textureStorage3D = getFunction<OpenGL::TextureStorage3D>("glTextureStorage3D");

		OpenGL::textureStorage3DMultisample = getFunction<OpenGL::TextureStorage3DMultisample>(
			"glTextureStorage3DMultisample");

		OpenGL::textureSubImage1D = getFunction<OpenGL::TextureSubImage1D>("glTextureSubImage1D");
		OpenGL::textureSubImage2D = getFunction<OpenGL::TextureSubImage2D>("glTextureSubImage2D");
		OpenGL::textureSubImage3D = getFunction<OpenGL::TextureSubImage3D>("glTextureSubImage3D");
		OpenGL::unmapNamedBuffer = getFunction<OpenGL::UnmapNamedBuffer>("glUnmapNamedBuffer");
		OpenGL::vertexArrayAttribBinding = getFunction<OpenGL::VertexArrayAttribBinding>("glVertexArrayAttribBinding");
		OpenGL::vertexArrayAttribFormat = getFunction<OpenGL::VertexArrayAttribFormat>("glVertexArrayAttribFormat");
		OpenGL::vertexArrayAttribIFormat = getFunction<OpenGL::VertexArrayAttribIFormat>("glVertexArrayAttribIFormat");
		OpenGL::vertexArrayAttribLFormat = getFunction<OpenGL::VertexArrayAttribLFormat>("glVertexArrayAttribLFormat");

		OpenGL::vertexArrayBindingDivisor = getFunction<OpenGL::VertexArrayBindingDivisor>(
			"glVertexArrayBindingDivisor");

		OpenGL::vertexArrayElementBuffer = getFunction<OpenGL::VertexArrayElementBuffer>("glVertexArrayElementBuffer");
		OpenGL::vertexArrayVertexBuffer = getFunction<OpenGL::VertexArrayVertexBuffer>("glVertexArrayVertexBuffer");
		OpenGL::vertexArrayVertexBuffers = getFunction<OpenGL::VertexArrayVertexBuffers>("glVertexArrayVertexBuffers");
	}

	template<typename T>
	static T getFunction(const Char8* name)
	{
		T function = reinterpret_cast<T>(WGL::getProcAddress(name));

		if(function == nullptr)
		{
			defaultLog << LogLevel::Error << COMPONENT_TAG << " Failed to get the function '" << name << "'." <<
				Log::Flush();

			DE_ERROR(0x0);
		}

		return function;
	}

private:

	static const Char8* COMPONENT_TAG;
};

const Char8* GraphicsExtensionLoader::Impl::COMPONENT_TAG = "[Platform::GraphicsExtensionLoader - WGL]";


// Public

// Static

void GraphicsExtensionLoader::loadContextExtensions(const GraphicsContextBase& graphicsContext)
{
	Impl::loadContextExtensions(graphicsContext);
}

void GraphicsExtensionLoader::loadInterfaceExtensions()
{
	Impl::loadInterfaceExtensions();
}
