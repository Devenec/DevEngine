/**
 * @file platform/opengl/OpenGL.cpp
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
 * along with this program. If not, see <http:  //www.gnu.org/licenses/>.
 */

#include <core/Log.h>
#include <core/StringStream.h>
#include <core/debug/Assert.h>
#include <platform/opengl/OpenGL.h>

using namespace Core;
using namespace Platform;

// External

using Bitfield = Uint32;
using Boolean  = Uint8;
using Enum	   = Uint32;
using Sizei	   = Int32;

extern "C"
{
	// Version 1.0

	void DE_CALL_OPENGL glBlendFunc(Enum sfactor, Enum dfactor);
	void DE_CALL_OPENGL glClear(Bitfield mask);
	void DE_CALL_OPENGL glClearColor(Float32 red, Float32 green, Float32 blue, Float32 alpha);
	void DE_CALL_OPENGL glClearDepth(Float64 depth);
	void DE_CALL_OPENGL glClearStencil(Int32 s);
	void DE_CALL_OPENGL glColorMask(Boolean red, Boolean green, Boolean blue, Boolean alpha);
	void DE_CALL_OPENGL glCullFace(Enum mode);
	void DE_CALL_OPENGL glDepthFunc(Enum func);
	void DE_CALL_OPENGL glDepthMask(Boolean flag);
	void DE_CALL_OPENGL glDepthRange(Float64 near, Float64 far);
	void DE_CALL_OPENGL glDisable(Enum cap);
	void DE_CALL_OPENGL glDrawBuffer(Enum buf);
	void DE_CALL_OPENGL glEnable(Enum cap);
	void DE_CALL_OPENGL glFinish();
	void DE_CALL_OPENGL glFlush();
	void DE_CALL_OPENGL glFrontFace(Enum mode);
	void DE_CALL_OPENGL glGetBooleanv(Enum pname, Boolean* data);
	void DE_CALL_OPENGL glGetDoublev(Enum pname, Float64* data);
	Enum DE_CALL_OPENGL glGetError();
	void DE_CALL_OPENGL glGetFloatv(Enum pname, Float32* data);
	void DE_CALL_OPENGL glGetIntegerv(Enum pname, Int32* data);
	const Uint8* DE_CALL_OPENGL glGetString(Enum name);
	void DE_CALL_OPENGL glGetTexImage(Enum target, Int32 level, Enum format, Enum type, Void* pixels);
	void DE_CALL_OPENGL glGetTexLevelParameterfv(Enum target, Int32 level, Enum pname, Float32* params);
	void DE_CALL_OPENGL glGetTexLevelParameteriv(Enum target, Int32 level, Enum pname, Int32* params);
	void DE_CALL_OPENGL glGetTexParameterfv(Enum target, Enum pname, Float32* params);
	void DE_CALL_OPENGL glGetTexParameteriv(Enum target, Enum pname, Int32* params);
	void DE_CALL_OPENGL glHint(Enum target, Enum mode);
	Boolean DE_CALL_OPENGL glIsEnabled(Enum cap);
	void DE_CALL_OPENGL glLineWidth(Float32 width);
	void DE_CALL_OPENGL glLogicOp(Enum opcode);
	void DE_CALL_OPENGL glPixelStoref(Enum pname, Float32 param);
	void DE_CALL_OPENGL glPixelStorei(Enum pname, Int32 param);
	void DE_CALL_OPENGL glPointSize(Float32 size);
	void DE_CALL_OPENGL glPolygonMode(Enum face, Enum mode);
	void DE_CALL_OPENGL glReadBuffer(Enum src);

	void DE_CALL_OPENGL glReadPixels(Int32 x, Int32 y, Sizei width, Sizei height, Enum format, Enum type,
		Void* pixels);

	void DE_CALL_OPENGL glScissor(Int32 x, Int32 y, Sizei width, Sizei height);
	void DE_CALL_OPENGL glStencilFunc(Enum func, Int32 ref, Uint32 mask);
	void DE_CALL_OPENGL glStencilMask(Uint32 mask);
	void DE_CALL_OPENGL glStencilOp(Enum fail, Enum zfail, Enum zpass);

	void DE_CALL_OPENGL glTexImage1D(Enum target, Int32 level, Int32 internalformat, Sizei width, Int32 border,
		Enum format, Enum type, const Void* pixels);

	void DE_CALL_OPENGL glTexImage2D(Enum target, Int32 level, Int32 internalformat, Sizei width, Sizei height,
		Int32 border, Enum format, Enum type, const Void* pixels);

	void DE_CALL_OPENGL glTexParameterf(Enum target, Enum pname, Float32 param);
	void DE_CALL_OPENGL glTexParameterfv(Enum target, Enum pname, const Float32* params);
	void DE_CALL_OPENGL glTexParameteri(Enum target, Enum pname, Int32 param);
	void DE_CALL_OPENGL glTexParameteriv(Enum target, Enum pname, const Int32* params);
	void DE_CALL_OPENGL glViewport(Int32 x, Int32 y, Sizei width, Sizei height);

	// Version 1.1

	void DE_CALL_OPENGL glBindTexture(Enum target, Uint32 texture);

	void DE_CALL_OPENGL glCopyTexImage1D(Enum target, Int32 level, Enum internalformat, Int32 x, Int32 y, Sizei width,
		Int32 border);

	void DE_CALL_OPENGL glCopyTexImage2D(Enum target, Int32 level, Enum internalformat, Int32 x, Int32 y, Sizei width,
		Sizei height, Int32 border);

	void DE_CALL_OPENGL glCopyTexSubImage1D(Enum target, Int32 level, Int32 xoffset, Int32 x, Int32 y, Sizei width);

	void DE_CALL_OPENGL glCopyTexSubImage2D(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Int32 x, Int32 y,
		Sizei width, Sizei height);

	void DE_CALL_OPENGL glDeleteTextures(Sizei n, const Uint32* textures);
	void DE_CALL_OPENGL glDrawArrays(Enum mode, Int32 first, Sizei count);
	void DE_CALL_OPENGL glDrawElements(Enum mode, Sizei count, Enum type, const Void* indices);
	void DE_CALL_OPENGL glGenTextures(Sizei n, Uint32* textures);
	void DE_CALL_OPENGL glGetPointerv(Enum pname, Void** params);
	Boolean DE_CALL_OPENGL glIsTexture(Uint32 texture);
	void DE_CALL_OPENGL glPolygonOffset(Float32 factor, Float32 units);

	void DE_CALL_OPENGL glTexSubImage1D(Enum target, Int32 level, Int32 xoffset, Sizei width, Enum format, Enum type,
		const Void* pixels);

	void DE_CALL_OPENGL glTexSubImage2D(Enum target, Int32 level, Int32 xoffset, Int32 yoffset, Sizei width,
		Sizei height, Enum format, Enum type, const Void* pixels);
}


// Public

// Version 1.0

OpenGL::BlendFunc OpenGL::blendFunc = glBlendFunc;
OpenGL::Clear OpenGL::clear = glClear;
OpenGL::ClearColor OpenGL::clearColor = glClearColor;
OpenGL::ClearDepth OpenGL::clearDepth = glClearDepth;
OpenGL::ClearStencil OpenGL::clearStencil = glClearStencil;
OpenGL::ColorMask OpenGL::colorMask = glColorMask;
OpenGL::CullFace OpenGL::cullFace = glCullFace;
OpenGL::DepthFunc OpenGL::depthFunc = glDepthFunc;
OpenGL::DepthMask OpenGL::depthMask = glDepthMask;
OpenGL::DepthRange OpenGL::depthRange = glDepthRange;
OpenGL::Disable OpenGL::disable = glDisable;
OpenGL::DrawBuffer OpenGL::drawBuffer = glDrawBuffer;
OpenGL::Enable OpenGL::enable = glEnable;
OpenGL::Finish OpenGL::finish = glFinish;
OpenGL::Flush OpenGL::flush = glFlush;
OpenGL::FrontFace OpenGL::frontFace = glFrontFace;
OpenGL::GetBooleanV OpenGL::getBooleanv = glGetBooleanv;
OpenGL::GetDoubleV OpenGL::getDoublev = glGetDoublev;
OpenGL::GetError OpenGL::getError = glGetError;
OpenGL::GetFloatV OpenGL::getFloatv = glGetFloatv;
OpenGL::GetIntegerV OpenGL::getIntegerv = glGetIntegerv;
OpenGL::GetString OpenGL::getString = glGetString;
OpenGL::GetTexImage OpenGL::getTexImage = glGetTexImage;
OpenGL::GetTexLevelParameterFV OpenGL::getTexLevelParameterfv = glGetTexLevelParameterfv;
OpenGL::GetTexLevelParameterIV OpenGL::getTexLevelParameteriv = glGetTexLevelParameteriv;
OpenGL::GetTexParameterFV OpenGL::getTexParameterfv = glGetTexParameterfv;
OpenGL::GetTexParameterIV OpenGL::getTexParameteriv = glGetTexParameteriv;
OpenGL::Hint OpenGL::hint = glHint;
OpenGL::IsEnabled OpenGL::isEnabled = glIsEnabled;
OpenGL::LineWidth OpenGL::lineWidth = glLineWidth;
OpenGL::LogicOp OpenGL::logicOp = glLogicOp;
OpenGL::PixelStoreF OpenGL::pixelStoref = glPixelStoref;
OpenGL::PixelStoreI OpenGL::pixelStorei = glPixelStorei;
OpenGL::PointSize OpenGL::pointSize = glPointSize;
OpenGL::PolygonMode OpenGL::polygonMode = glPolygonMode;
OpenGL::ReadBuffer OpenGL::readBuffer = glReadBuffer;
OpenGL::ReadPixels OpenGL::readPixels = glReadPixels;
OpenGL::Scissor OpenGL::scissor = glScissor;
OpenGL::StencilFunc OpenGL::stencilFunc = glStencilFunc;
OpenGL::StencilMask OpenGL::stencilMask = glStencilMask;
OpenGL::StencilOp OpenGL::stencilOp = glStencilOp;
OpenGL::TexImage1D OpenGL::texImage1D = glTexImage1D;
OpenGL::TexImage2D OpenGL::texImage2D = glTexImage2D;
OpenGL::TexParameterF OpenGL::texParameterf = glTexParameterf;
OpenGL::TexParameterFV OpenGL::texParameterfv = glTexParameterfv;
OpenGL::TexParameterI OpenGL::texParameteri = glTexParameteri;
OpenGL::TexParameterIV OpenGL::texParameteriv = glTexParameteriv;
OpenGL::Viewport OpenGL::viewport = glViewport;

// Version 1.1

OpenGL::BindTexture OpenGL::bindTexture = glBindTexture;
OpenGL::CopyTexImage1D OpenGL::copyTexImage1D = glCopyTexImage1D;
OpenGL::CopyTexImage2D OpenGL::copyTexImage2D = glCopyTexImage2D;
OpenGL::CopyTexSubImage1D OpenGL::copyTexSubImage1D = glCopyTexSubImage1D;
OpenGL::CopyTexSubImage2D OpenGL::copyTexSubImage2D = glCopyTexSubImage2D;
OpenGL::DeleteTextures OpenGL::deleteTextures = glDeleteTextures;
OpenGL::DrawArrays OpenGL::drawArrays = glDrawArrays;
OpenGL::DrawElements OpenGL::drawElements = glDrawElements;
OpenGL::GenTextures OpenGL::genTextures = glGenTextures;
OpenGL::GetPointerV OpenGL::getPointerv = glGetPointerv;
OpenGL::IsTexture OpenGL::isTexture = glIsTexture;
OpenGL::PolygonOffset OpenGL::polygonOffset = glPolygonOffset;
OpenGL::TexSubImage1D OpenGL::texSubImage1D = glTexSubImage1D;
OpenGL::TexSubImage2D OpenGL::texSubImage2D = glTexSubImage2D;

// Version 1.2

OpenGL::CopyTexSubImage3D OpenGL::copyTexSubImage3D = nullptr;
OpenGL::DrawRangeElements OpenGL::drawRangeElements = nullptr;
OpenGL::TexImage3D OpenGL::texImage3D = nullptr;
OpenGL::TexSubImage3D OpenGL::texSubImage3D = nullptr;

// Version 1.3

OpenGL::ActiveTexture OpenGL::activeTexture = nullptr;
OpenGL::CompressedTexImage1D OpenGL::compressedTexImage1D = nullptr;
OpenGL::CompressedTexImage2D OpenGL::compressedTexImage2D = nullptr;
OpenGL::CompressedTexImage3D OpenGL::compressedTexImage3D = nullptr;
OpenGL::CompressedTexSubImage1D OpenGL::compressedTexSubImage1D = nullptr;
OpenGL::CompressedTexSubImage2D OpenGL::compressedTexSubImage2D = nullptr;
OpenGL::CompressedTexSubImage3D OpenGL::compressedTexSubImage3D = nullptr;
OpenGL::GetCompressedTexImage OpenGL::getCompressedTexImage = nullptr;
OpenGL::SampleCoverage OpenGL::sampleCoverage = nullptr;

// Version 1.4

OpenGL::BlendColor OpenGL::blendColor = nullptr;
OpenGL::BlendEquation OpenGL::blendEquation = nullptr;
OpenGL::BlendFuncSeparate OpenGL::blendFuncSeparate = nullptr;
OpenGL::MultiDrawArrays OpenGL::multiDrawArrays = nullptr;
OpenGL::MultiDrawElements OpenGL::multiDrawElements = nullptr;
OpenGL::PointParameterF OpenGL::pointParameterf = nullptr;
OpenGL::PointParameterFV OpenGL::pointParameterfv = nullptr;
OpenGL::PointParameterI OpenGL::pointParameteri = nullptr;
OpenGL::PointParameterIV OpenGL::pointParameteriv = nullptr;

// Version 1.5

OpenGL::BeginQuery OpenGL::beginQuery = nullptr;
OpenGL::BindBuffer OpenGL::bindBuffer = nullptr;
OpenGL::BufferData OpenGL::bufferData = nullptr;
OpenGL::BufferSubData OpenGL::bufferSubData = nullptr;
OpenGL::DeleteBuffers OpenGL::deleteBuffers = nullptr;
OpenGL::DeleteQueries OpenGL::deleteQueries = nullptr;
OpenGL::EndQuery OpenGL::endQuery = nullptr;
OpenGL::GenBuffers OpenGL::genBuffers = nullptr;
OpenGL::GenQueries OpenGL::genQueries = nullptr;
OpenGL::GetBufferParameterIV OpenGL::getBufferParameteriv = nullptr;
OpenGL::GetBufferPointerV OpenGL::getBufferPointerv = nullptr;
OpenGL::GetBufferSubData OpenGL::getBufferSubData = nullptr;
OpenGL::GetQueryIV OpenGL::getQueryiv = nullptr;
OpenGL::GetQueryObjectIV OpenGL::getQueryObjectiv = nullptr;
OpenGL::GetQueryObjectUIV OpenGL::getQueryObjectuiv = nullptr;
OpenGL::IsBuffer OpenGL::isBuffer = nullptr;
OpenGL::IsQuery OpenGL::isQuery = nullptr;
OpenGL::MapBuffer OpenGL::mapBuffer = nullptr;
OpenGL::UnmapBuffer OpenGL::unmapBuffer = nullptr;

// Version 2.0

OpenGL::AttachShader OpenGL::attachShader = nullptr;
OpenGL::BindAttribLocation OpenGL::bindAttribLocation = nullptr;
OpenGL::BlendEquationSeparate OpenGL::blendEquationSeparate = nullptr;
OpenGL::CompileShader OpenGL::compileShader = nullptr;
OpenGL::CreateProgram OpenGL::createProgram = nullptr;
OpenGL::CreateShader OpenGL::createShader = nullptr;
OpenGL::DeleteProgram OpenGL::deleteProgram = nullptr;
OpenGL::DeleteShader OpenGL::deleteShader = nullptr;
OpenGL::DetachShader OpenGL::detachShader = nullptr;
OpenGL::DisableVertexAttribArray OpenGL::disableVertexAttribArray = nullptr;
OpenGL::DrawBuffers OpenGL::drawBuffers = nullptr;
OpenGL::EnableVertexAttribArray OpenGL::enableVertexAttribArray = nullptr;
OpenGL::GetActiveAttrib OpenGL::getActiveAttrib = nullptr;
OpenGL::GetActiveUniform OpenGL::getActiveUniform = nullptr;
OpenGL::GetAttachedShaders OpenGL::getAttachedShaders = nullptr;
OpenGL::GetAttribLocation OpenGL::getAttribLocation = nullptr;
OpenGL::GetProgramInfoLog OpenGL::getProgramInfoLog = nullptr;
OpenGL::GetProgramIV OpenGL::getProgramiv = nullptr;
OpenGL::GetShaderInfoLog OpenGL::getShaderInfoLog = nullptr;
OpenGL::GetShaderIV OpenGL::getShaderiv = nullptr;
OpenGL::GetShaderSource OpenGL::getShaderSource = nullptr;
OpenGL::GetUniformFV OpenGL::getUniformfv = nullptr;
OpenGL::GetUniformIV OpenGL::getUniformiv = nullptr;
OpenGL::GetUniformLocation OpenGL::getUniformLocation = nullptr;
OpenGL::GetVertexAttribDV OpenGL::getVertexAttribdv = nullptr;
OpenGL::GetVertexAttribFV OpenGL::getVertexAttribfv = nullptr;
OpenGL::GetVertexAttribIV OpenGL::getVertexAttribiv = nullptr;
OpenGL::GetVertexAttribPointerV OpenGL::getVertexAttribPointerv = nullptr;
OpenGL::IsProgram OpenGL::isProgram = nullptr;
OpenGL::IsShader OpenGL::isShader = nullptr;
OpenGL::LinkProgram OpenGL::linkProgram = nullptr;
OpenGL::ShaderSource OpenGL::shaderSource = nullptr;
OpenGL::StencilFuncSeparate OpenGL::stencilFuncSeparate = nullptr;
OpenGL::StencilMaskSeparate OpenGL::stencilMaskSeparate = nullptr;
OpenGL::StencilOpSeparate OpenGL::stencilOpSeparate = nullptr;
OpenGL::Uniform1F OpenGL::uniform1f = nullptr;
OpenGL::Uniform1FV OpenGL::uniform1fv = nullptr;
OpenGL::Uniform1I OpenGL::uniform1i = nullptr;
OpenGL::Uniform1IV OpenGL::uniform1iv = nullptr;
OpenGL::Uniform2F OpenGL::uniform2f = nullptr;
OpenGL::Uniform2FV OpenGL::uniform2fv = nullptr;
OpenGL::Uniform2I OpenGL::uniform2i = nullptr;
OpenGL::Uniform2IV OpenGL::uniform2iv = nullptr;
OpenGL::Uniform3F OpenGL::uniform3f = nullptr;
OpenGL::Uniform3FV OpenGL::uniform3fv = nullptr;
OpenGL::Uniform3I OpenGL::uniform3i = nullptr;
OpenGL::Uniform3IV OpenGL::uniform3iv = nullptr;
OpenGL::Uniform4F OpenGL::uniform4f = nullptr;
OpenGL::Uniform4FV OpenGL::uniform4fv = nullptr;
OpenGL::Uniform4I OpenGL::uniform4i = nullptr;
OpenGL::Uniform4IV OpenGL::uniform4iv = nullptr;
OpenGL::UniformMatrix2FV OpenGL::uniformMatrix2fv = nullptr;
OpenGL::UniformMatrix3FV OpenGL::uniformMatrix3fv = nullptr;
OpenGL::UniformMatrix4FV OpenGL::uniformMatrix4fv = nullptr;
OpenGL::UseProgram OpenGL::useProgram = nullptr;
OpenGL::ValidateProgram OpenGL::validateProgram = nullptr;
OpenGL::VertexAttrib1D OpenGL::vertexAttrib1d = nullptr;
OpenGL::VertexAttrib1DV OpenGL::vertexAttrib1dv = nullptr;
OpenGL::VertexAttrib1F OpenGL::vertexAttrib1f = nullptr;
OpenGL::VertexAttrib1FV OpenGL::vertexAttrib1fv = nullptr;
OpenGL::VertexAttrib1S OpenGL::vertexAttrib1s = nullptr;
OpenGL::VertexAttrib1SV OpenGL::vertexAttrib1sv = nullptr;
OpenGL::VertexAttrib2D OpenGL::vertexAttrib2d = nullptr;
OpenGL::VertexAttrib2DV OpenGL::vertexAttrib2dv = nullptr;
OpenGL::VertexAttrib2F OpenGL::vertexAttrib2f = nullptr;
OpenGL::VertexAttrib2FV OpenGL::vertexAttrib2fv = nullptr;
OpenGL::VertexAttrib2S OpenGL::vertexAttrib2s = nullptr;
OpenGL::VertexAttrib2SV OpenGL::vertexAttrib2sv = nullptr;
OpenGL::VertexAttrib3D OpenGL::vertexAttrib3d = nullptr;
OpenGL::VertexAttrib3DV OpenGL::vertexAttrib3dv = nullptr;
OpenGL::VertexAttrib3F OpenGL::vertexAttrib3f = nullptr;
OpenGL::VertexAttrib3FV OpenGL::vertexAttrib3fv = nullptr;
OpenGL::VertexAttrib3S OpenGL::vertexAttrib3s = nullptr;
OpenGL::VertexAttrib3SV OpenGL::vertexAttrib3sv = nullptr;
OpenGL::VertexAttrib4BV OpenGL::vertexAttrib4bv = nullptr;
OpenGL::VertexAttrib4D OpenGL::vertexAttrib4d = nullptr;
OpenGL::VertexAttrib4DV OpenGL::vertexAttrib4dv = nullptr;
OpenGL::VertexAttrib4F OpenGL::vertexAttrib4f = nullptr;
OpenGL::VertexAttrib4FV OpenGL::vertexAttrib4fv = nullptr;
OpenGL::VertexAttrib4IV OpenGL::vertexAttrib4iv = nullptr;
OpenGL::VertexAttrib4NBV OpenGL::vertexAttrib4Nbv = nullptr;
OpenGL::VertexAttrib4NIV OpenGL::vertexAttrib4Niv = nullptr;
OpenGL::VertexAttrib4NSV OpenGL::vertexAttrib4Nsv = nullptr;
OpenGL::VertexAttrib4NUB OpenGL::vertexAttrib4Nub = nullptr;
OpenGL::VertexAttrib4NUBV OpenGL::vertexAttrib4Nubv = nullptr;
OpenGL::VertexAttrib4NUIV OpenGL::vertexAttrib4Nuiv = nullptr;
OpenGL::VertexAttrib4NUSV OpenGL::vertexAttrib4Nusv = nullptr;
OpenGL::VertexAttrib4S OpenGL::vertexAttrib4s = nullptr;
OpenGL::VertexAttrib4SV OpenGL::vertexAttrib4sv = nullptr;
OpenGL::VertexAttrib4UBV OpenGL::vertexAttrib4ubv = nullptr;
OpenGL::VertexAttrib4UIV OpenGL::vertexAttrib4uiv = nullptr;
OpenGL::VertexAttrib4USV OpenGL::vertexAttrib4usv = nullptr;
OpenGL::VertexAttribPointer OpenGL::vertexAttribPointer = nullptr;

// Version 2.1

OpenGL::UniformMatrix2X3FV OpenGL::uniformMatrix2x3fv = nullptr;
OpenGL::UniformMatrix2X4FV OpenGL::uniformMatrix2x4fv = nullptr;
OpenGL::UniformMatrix3X2FV OpenGL::uniformMatrix3x2fv = nullptr;
OpenGL::UniformMatrix3X4FV OpenGL::uniformMatrix3x4fv = nullptr;
OpenGL::UniformMatrix4X2FV OpenGL::uniformMatrix4x2fv = nullptr;
OpenGL::UniformMatrix4X3FV OpenGL::uniformMatrix4x3fv = nullptr;

// Version 3.0

OpenGL::BeginConditionalRender OpenGL::beginConditionalRender = nullptr;
OpenGL::BeginTransformFeedback OpenGL::beginTransformFeedback = nullptr;
OpenGL::BindBufferBase OpenGL::bindBufferBase = nullptr;
OpenGL::BindBufferRange OpenGL::bindBufferRange = nullptr;
OpenGL::BindFragDataLocation OpenGL::bindFragDataLocation = nullptr;
OpenGL::BindFramebuffer OpenGL::bindFramebuffer = nullptr;
OpenGL::BindRenderbuffer OpenGL::bindRenderbuffer = nullptr;
OpenGL::BindVertexArray OpenGL::bindVertexArray = nullptr;
OpenGL::BlitFramebuffer OpenGL::blitFramebuffer = nullptr;
OpenGL::CheckFramebufferStatus OpenGL::checkFramebufferStatus = nullptr;
OpenGL::ClampColor OpenGL::clampColor = nullptr;
OpenGL::ClearBufferFI OpenGL::clearBufferfi = nullptr;
OpenGL::ClearBufferFV OpenGL::clearBufferfv = nullptr;
OpenGL::ClearBufferIV OpenGL::clearBufferiv = nullptr;
OpenGL::ClearBufferUIV OpenGL::clearBufferuiv = nullptr;
OpenGL::ColorMaskI OpenGL::colorMaski = nullptr;
OpenGL::DeleteFramebuffers OpenGL::deleteFramebuffers = nullptr;
OpenGL::DeleteRenderbuffers OpenGL::deleteRenderbuffers = nullptr;
OpenGL::DeleteVertexArrays OpenGL::deleteVertexArrays = nullptr;
OpenGL::DisableI OpenGL::disablei = nullptr;
OpenGL::EnableI OpenGL::enablei = nullptr;
OpenGL::EndConditionalRender OpenGL::endConditionalRender = nullptr;
OpenGL::EndTransformFeedback OpenGL::endTransformFeedback = nullptr;
OpenGL::FlushMappedBufferRange OpenGL::flushMappedBufferRange = nullptr;
OpenGL::FramebufferRenderbuffer OpenGL::framebufferRenderbuffer = nullptr;
OpenGL::FramebufferTexture1D OpenGL::framebufferTexture1D = nullptr;
OpenGL::FramebufferTexture2D OpenGL::framebufferTexture2D = nullptr;
OpenGL::FramebufferTexture3D OpenGL::framebufferTexture3D = nullptr;
OpenGL::FramebufferTextureLayer OpenGL::framebufferTextureLayer = nullptr;
OpenGL::GenerateMipmap OpenGL::generateMipmap = nullptr;
OpenGL::GenFramebuffers OpenGL::genFramebuffers = nullptr;
OpenGL::GenRenderbuffers OpenGL::genRenderbuffers = nullptr;
OpenGL::GenVertexArrays OpenGL::genVertexArrays = nullptr;
OpenGL::GetBooleanI_V OpenGL::getBooleani_v = nullptr;
OpenGL::GetFragDataLocation OpenGL::getFragDataLocation = nullptr;
OpenGL::GetFramebufferAttachmentParameterIV OpenGL::getFramebufferAttachmentParameteriv = nullptr;
OpenGL::GetIntegerI_V OpenGL::getIntegeri_v = nullptr;
OpenGL::GetRenderbufferParameterIV OpenGL::getRenderbufferParameteriv = nullptr;
OpenGL::GetStringI OpenGL::getStringi = nullptr;
OpenGL::GetTexParameterIIV OpenGL::getTexParameterIiv = nullptr;
OpenGL::GetTexParameterIUIV OpenGL::getTexParameterIuiv = nullptr;
OpenGL::GetTransformFeedbackVarying OpenGL::getTransformFeedbackVarying = nullptr;
OpenGL::GetUniformUIV OpenGL::getUniformuiv = nullptr;
OpenGL::GetVertexAttribIIV OpenGL::getVertexAttribIiv = nullptr;
OpenGL::GetVertexAttribIUIV OpenGL::getVertexAttribIuiv = nullptr;
OpenGL::IsEnabledI OpenGL::isEnabledi = nullptr;
OpenGL::IsFramebuffer OpenGL::isFramebuffer = nullptr;
OpenGL::IsRenderbuffer OpenGL::isRenderbuffer = nullptr;
OpenGL::IsVertexArray OpenGL::isVertexArray = nullptr;
OpenGL::MapBufferRange OpenGL::mapBufferRange = nullptr;
OpenGL::RenderbufferStorage OpenGL::renderbufferStorage = nullptr;
OpenGL::RenderbufferStorageMultisample OpenGL::renderbufferStorageMultisample = nullptr;
OpenGL::TexParameterIIV OpenGL::texParameterIiv = nullptr;
OpenGL::TexParameterIUIV OpenGL::texParameterIuiv = nullptr;
OpenGL::TransformFeedbackVaryings OpenGL::transformFeedbackVaryings = nullptr;
OpenGL::Uniform1UI OpenGL::uniform1ui = nullptr;
OpenGL::Uniform1UIV OpenGL::uniform1uiv = nullptr;
OpenGL::Uniform2UI OpenGL::uniform2ui = nullptr;
OpenGL::Uniform2UIV OpenGL::uniform2uiv = nullptr;
OpenGL::Uniform3UI OpenGL::uniform3ui = nullptr;
OpenGL::Uniform3UIV OpenGL::uniform3uiv = nullptr;
OpenGL::Uniform4UI OpenGL::uniform4ui = nullptr;
OpenGL::Uniform4UIV OpenGL::uniform4uiv = nullptr;
OpenGL::VertexAttribI1I OpenGL::vertexAttribI1i = nullptr;
OpenGL::VertexAttribI1IV OpenGL::vertexAttribI1iv = nullptr;
OpenGL::VertexAttribI1UI OpenGL::vertexAttribI1ui = nullptr;
OpenGL::VertexAttribI1UIV OpenGL::vertexAttribI1uiv = nullptr;
OpenGL::VertexAttribI2I OpenGL::vertexAttribI2i = nullptr;
OpenGL::VertexAttribI2IV OpenGL::vertexAttribI2iv = nullptr;
OpenGL::VertexAttribI2UI OpenGL::vertexAttribI2ui = nullptr;
OpenGL::VertexAttribI2UIV OpenGL::vertexAttribI2uiv = nullptr;
OpenGL::VertexAttribI3I OpenGL::vertexAttribI3i = nullptr;
OpenGL::VertexAttribI3IV OpenGL::vertexAttribI3iv = nullptr;
OpenGL::VertexAttribI3UI OpenGL::vertexAttribI3ui = nullptr;
OpenGL::VertexAttribI3UIV OpenGL::vertexAttribI3uiv = nullptr;
OpenGL::VertexAttribI4BV OpenGL::vertexAttribI4bv = nullptr;
OpenGL::VertexAttribI4I OpenGL::vertexAttribI4i = nullptr;
OpenGL::VertexAttribI4IV OpenGL::vertexAttribI4iv = nullptr;
OpenGL::VertexAttribI4SV OpenGL::vertexAttribI4sv = nullptr;
OpenGL::VertexAttribI4UBV OpenGL::vertexAttribI4ubv = nullptr;
OpenGL::VertexAttribI4UI OpenGL::vertexAttribI4ui = nullptr;
OpenGL::VertexAttribI4UIV OpenGL::vertexAttribI4uiv = nullptr;
OpenGL::VertexAttribI4USV OpenGL::vertexAttribI4usv = nullptr;
OpenGL::VertexAttribIPointer OpenGL::vertexAttribIPointer = nullptr;

// Version 3.1

OpenGL::CopyBufferSubData OpenGL::copyBufferSubData = nullptr;
OpenGL::DrawArraysInstanced OpenGL::drawArraysInstanced = nullptr;
OpenGL::DrawElementsInstanced OpenGL::drawElementsInstanced = nullptr;
OpenGL::GetActiveUniformBlockIV OpenGL::getActiveUniformBlockiv = nullptr;
OpenGL::GetActiveUniformBlockName OpenGL::getActiveUniformBlockName = nullptr;
OpenGL::GetActiveUniformName OpenGL::getActiveUniformName = nullptr;
OpenGL::GetActiveUniformsIV OpenGL::getActiveUniformsiv = nullptr;
OpenGL::GetUniformBlockIndex OpenGL::getUniformBlockIndex = nullptr;
OpenGL::GetUniformIndices OpenGL::getUniformIndices = nullptr;
OpenGL::PrimitiveRestartIndex OpenGL::primitiveRestartIndex = nullptr;
OpenGL::TexBuffer OpenGL::texBuffer = nullptr;
OpenGL::UniformBlockBinding OpenGL::uniformBlockBinding = nullptr;

// Version 3.2

OpenGL::ClientWaitSync OpenGL::clientWaitSync = nullptr;
OpenGL::DeleteSync OpenGL::deleteSync = nullptr;
OpenGL::DrawElementsBaseVertex OpenGL::drawElementsBaseVertex = nullptr;
OpenGL::DrawElementsInstancedBaseVertex OpenGL::drawElementsInstancedBaseVertex = nullptr;
OpenGL::DrawRangeElementsBaseVertex OpenGL::drawRangeElementsBaseVertex = nullptr;
OpenGL::FenceSync OpenGL::fenceSync = nullptr;
OpenGL::FramebufferTexture OpenGL::framebufferTexture = nullptr;
OpenGL::GetBufferParameterI64V OpenGL::getBufferParameteri64v = nullptr;
OpenGL::GetInteger64I_V OpenGL::getInteger64i_v = nullptr;
OpenGL::GetInteger64V OpenGL::getInteger64v = nullptr;
OpenGL::GetMultisampleFV OpenGL::getMultisamplefv = nullptr;
OpenGL::GetSyncIV OpenGL::getSynciv = nullptr;
OpenGL::IsSync OpenGL::isSync = nullptr;
OpenGL::MultiDrawElementsBaseVertex OpenGL::multiDrawElementsBaseVertex = nullptr;
OpenGL::ProvokingVertex OpenGL::provokingVertex = nullptr;
OpenGL::SampleMaskI OpenGL::sampleMaski = nullptr;
OpenGL::TexImage2DMultisample OpenGL::texImage2DMultisample = nullptr;
OpenGL::TexImage3DMultisample OpenGL::texImage3DMultisample = nullptr;
OpenGL::WaitSync OpenGL::waitSync = nullptr;

// Version 3.3

OpenGL::BindFragDataLocationIndexed OpenGL::bindFragDataLocationIndexed = nullptr;
OpenGL::BindSampler OpenGL::bindSampler = nullptr;
OpenGL::DeleteSamplers OpenGL::deleteSamplers = nullptr;
OpenGL::GenSamplers OpenGL::genSamplers = nullptr;
OpenGL::GetFragDataIndex OpenGL::getFragDataIndex = nullptr;
OpenGL::GetQueryObjectI64V OpenGL::getQueryObjecti64v = nullptr;
OpenGL::GetQueryObjectUI64V OpenGL::getQueryObjectui64v = nullptr;
OpenGL::GetSamplerParameterFV OpenGL::getSamplerParameterfv = nullptr;
OpenGL::GetSamplerParameterIIV OpenGL::getSamplerParameterIiv = nullptr;
OpenGL::GetSamplerParameterIUIV OpenGL::getSamplerParameterIuiv = nullptr;
OpenGL::GetSamplerParameterIV OpenGL::getSamplerParameteriv = nullptr;
OpenGL::IsSampler OpenGL::isSampler = nullptr;
OpenGL::QueryCounter OpenGL::queryCounter = nullptr;
OpenGL::SamplerParameterF OpenGL::samplerParameterf = nullptr;
OpenGL::SamplerParameterFV OpenGL::samplerParameterfv = nullptr;
OpenGL::SamplerParameterI OpenGL::samplerParameteri = nullptr;
OpenGL::SamplerParameterIV OpenGL::samplerParameteriv = nullptr;
OpenGL::SamplerParameterIIV OpenGL::samplerParameterIiv = nullptr;
OpenGL::SamplerParameterIUIV OpenGL::samplerParameterIuiv = nullptr;
OpenGL::VertexAttribDivisor OpenGL::vertexAttribDivisor = nullptr;
OpenGL::VertexAttribP1UI OpenGL::vertexAttribP1ui = nullptr;
OpenGL::VertexAttribP1UIV OpenGL::vertexAttribP1uiv = nullptr;
OpenGL::VertexAttribP2UI OpenGL::vertexAttribP2ui = nullptr;
OpenGL::VertexAttribP2UIV OpenGL::vertexAttribP2uiv = nullptr;
OpenGL::VertexAttribP3UI OpenGL::vertexAttribP3ui = nullptr;
OpenGL::VertexAttribP3UIV OpenGL::vertexAttribP3uiv = nullptr;
OpenGL::VertexAttribP4UI OpenGL::vertexAttribP4ui = nullptr;
OpenGL::VertexAttribP4UIV OpenGL::vertexAttribP4uiv = nullptr;

// Version 4.0

OpenGL::BeginQueryIndexed OpenGL::beginQueryIndexed = nullptr;
OpenGL::BindTransformFeedback OpenGL::bindTransformFeedback = nullptr;
OpenGL::BlendEquationI OpenGL::blendEquationi = nullptr;
OpenGL::BlendEquationSeparateI OpenGL::blendEquationSeparatei = nullptr;
OpenGL::BlendFuncI OpenGL::blendFunci = nullptr;
OpenGL::BlendFuncSeparateI OpenGL::blendFuncSeparatei = nullptr;
OpenGL::DeleteTransformFeedbacks OpenGL::deleteTransformFeedbacks = nullptr;
OpenGL::DrawArraysIndirect OpenGL::drawArraysIndirect = nullptr;
OpenGL::DrawElementsIndirect OpenGL::drawElementsIndirect = nullptr;
OpenGL::DrawTransformFeedback OpenGL::drawTransformFeedback = nullptr;
OpenGL::DrawTransformFeedbackStream OpenGL::drawTransformFeedbackStream = nullptr;
OpenGL::EndQueryIndexed OpenGL::endQueryIndexed = nullptr;
OpenGL::GenTransformFeedbacks OpenGL::genTransformFeedbacks = nullptr;
OpenGL::GetActiveSubroutineName OpenGL::getActiveSubroutineName = nullptr;
OpenGL::GetActiveSubroutineUniformIV OpenGL::getActiveSubroutineUniformiv = nullptr;
OpenGL::GetActiveSubroutineUniformName OpenGL::getActiveSubroutineUniformName = nullptr;
OpenGL::GetProgramStageIV OpenGL::getProgramStageiv = nullptr;
OpenGL::GetQueryIndexedIV OpenGL::getQueryIndexediv = nullptr;
OpenGL::GetSubroutineIndex OpenGL::getSubroutineIndex = nullptr;
OpenGL::GetSubroutineUniformLocation OpenGL::getSubroutineUniformLocation = nullptr;
OpenGL::GetUniformDV OpenGL::getUniformdv = nullptr;
OpenGL::GetUniformSubroutineUIV OpenGL::getUniformSubroutineuiv = nullptr;
OpenGL::IsTransformFeedback OpenGL::isTransformFeedback = nullptr;
OpenGL::MinSampleShading OpenGL::minSampleShading = nullptr;
OpenGL::PatchParameterFV OpenGL::patchParameterfv = nullptr;
OpenGL::PatchParameterI OpenGL::patchParameteri = nullptr;
OpenGL::PauseTransformFeedback OpenGL::pauseTransformFeedback = nullptr;
OpenGL::ResumeTransformFeedback OpenGL::resumeTransformFeedback = nullptr;
OpenGL::Uniform1D OpenGL::uniform1d = nullptr;
OpenGL::Uniform1DV OpenGL::uniform1dv = nullptr;
OpenGL::Uniform2D OpenGL::uniform2d = nullptr;
OpenGL::Uniform2DV OpenGL::uniform2dv = nullptr;
OpenGL::Uniform3D OpenGL::uniform3d = nullptr;
OpenGL::Uniform3DV OpenGL::uniform3dv = nullptr;
OpenGL::Uniform4D OpenGL::uniform4d = nullptr;
OpenGL::Uniform4DV OpenGL::uniform4dv = nullptr;
OpenGL::UniformMatrix2DV OpenGL::uniformMatrix2dv = nullptr;
OpenGL::UniformMatrix2X3DV OpenGL::uniformMatrix2x3dv = nullptr;
OpenGL::UniformMatrix2X4DV OpenGL::uniformMatrix2x4dv = nullptr;
OpenGL::UniformMatrix3DV OpenGL::uniformMatrix3dv = nullptr;
OpenGL::UniformMatrix3X2DV OpenGL::uniformMatrix3x2dv = nullptr;
OpenGL::UniformMatrix3X4DV OpenGL::uniformMatrix3x4dv = nullptr;
OpenGL::UniformMatrix4DV OpenGL::uniformMatrix4dv = nullptr;
OpenGL::UniformMatrix4X2DV OpenGL::uniformMatrix4x2dv = nullptr;
OpenGL::UniformMatrix4X3DV OpenGL::uniformMatrix4x3dv = nullptr;
OpenGL::UniformSubroutineSUIV OpenGL::uniformSubroutinesuiv = nullptr;

// Version 4.1

OpenGL::ActiveShaderProgram OpenGL::activeShaderProgram = nullptr;
OpenGL::BindProgramPipeline OpenGL::bindProgramPipeline = nullptr;
OpenGL::ClearDepthF OpenGL::clearDepthf = nullptr;
OpenGL::CreateShaderProgramV OpenGL::createShaderProgramv = nullptr;
OpenGL::DeleteProgramPipelines OpenGL::deleteProgramPipelines = nullptr;
OpenGL::DepthRangeArrayV OpenGL::depthRangeArrayv = nullptr;
OpenGL::DepthRangeF OpenGL::depthRangef = nullptr;
OpenGL::DepthRangeIndexed OpenGL::depthRangeIndexed = nullptr;
OpenGL::GenProgramPipelines OpenGL::genProgramPipelines = nullptr;
OpenGL::GetDoubleI_V OpenGL::getDoublei_v = nullptr;
OpenGL::GetFloatI_V OpenGL::getFloati_v = nullptr;
OpenGL::GetProgramBinary OpenGL::getProgramBinary = nullptr;
OpenGL::GetProgramPipelineInfoLog OpenGL::getProgramPipelineInfoLog = nullptr;
OpenGL::GetProgramPipelineIV OpenGL::getProgramPipelineiv = nullptr;
OpenGL::GetShaderPrecisionFormat OpenGL::getShaderPrecisionFormat = nullptr;
OpenGL::GetVertexAttribLDV OpenGL::getVertexAttribLdv = nullptr;
OpenGL::IsProgramPipeline OpenGL::isProgramPipeline = nullptr;
OpenGL::ProgramBinary OpenGL::programBinary = nullptr;
OpenGL::ProgramParameterI OpenGL::programParameteri = nullptr;
OpenGL::ProgramUniform1D OpenGL::programUniform1d = nullptr;
OpenGL::ProgramUniform1DV OpenGL::programUniform1dv = nullptr;
OpenGL::ProgramUniform1F OpenGL::programUniform1f = nullptr;
OpenGL::ProgramUniform1FV OpenGL::programUniform1fv = nullptr;
OpenGL::ProgramUniform1I OpenGL::programUniform1i = nullptr;
OpenGL::ProgramUniform1IV OpenGL::programUniform1iv = nullptr;
OpenGL::ProgramUniform1UI OpenGL::programUniform1ui = nullptr;
OpenGL::ProgramUniform1UIV OpenGL::programUniform1uiv = nullptr;
OpenGL::ProgramUniform2D OpenGL::programUniform2d = nullptr;
OpenGL::ProgramUniform2DV OpenGL::programUniform2dv = nullptr;
OpenGL::ProgramUniform2F OpenGL::programUniform2f = nullptr;
OpenGL::ProgramUniform2FV OpenGL::programUniform2fv = nullptr;
OpenGL::ProgramUniform2I OpenGL::programUniform2i = nullptr;
OpenGL::ProgramUniform2IV OpenGL::programUniform2iv = nullptr;
OpenGL::ProgramUniform2UI OpenGL::programUniform2ui = nullptr;
OpenGL::ProgramUniform2UIV OpenGL::programUniform2uiv = nullptr;
OpenGL::ProgramUniform3D OpenGL::programUniform3d = nullptr;
OpenGL::ProgramUniform3DV OpenGL::programUniform3dv = nullptr;
OpenGL::ProgramUniform3F OpenGL::programUniform3f = nullptr;
OpenGL::ProgramUniform3FV OpenGL::programUniform3fv = nullptr;
OpenGL::ProgramUniform3I OpenGL::programUniform3i = nullptr;
OpenGL::ProgramUniform3IV OpenGL::programUniform3iv = nullptr;
OpenGL::ProgramUniform3UI OpenGL::programUniform3ui = nullptr;
OpenGL::ProgramUniform3UIV OpenGL::programUniform3uiv = nullptr;
OpenGL::ProgramUniform4D OpenGL::programUniform4d = nullptr;
OpenGL::ProgramUniform4DV OpenGL::programUniform4dv = nullptr;
OpenGL::ProgramUniform4F OpenGL::programUniform4f = nullptr;
OpenGL::ProgramUniform4FV OpenGL::programUniform4fv = nullptr;
OpenGL::ProgramUniform4I OpenGL::programUniform4i = nullptr;
OpenGL::ProgramUniform4IV OpenGL::programUniform4iv = nullptr;
OpenGL::ProgramUniform4UI OpenGL::programUniform4ui = nullptr;
OpenGL::ProgramUniform4UIV OpenGL::programUniform4uiv = nullptr;
OpenGL::ProgramUniformMatrix2DV OpenGL::programUniformMatrix2dv = nullptr;
OpenGL::ProgramUniformMatrix2FV OpenGL::programUniformMatrix2fv = nullptr;
OpenGL::ProgramUniformMatrix2X3DV OpenGL::programUniformMatrix2x3dv = nullptr;
OpenGL::ProgramUniformMatrix2X3FV OpenGL::programUniformMatrix2x3fv = nullptr;
OpenGL::ProgramUniformMatrix2X4DV OpenGL::programUniformMatrix2x4dv = nullptr;
OpenGL::ProgramUniformMatrix2X4FV OpenGL::programUniformMatrix2x4fv = nullptr;
OpenGL::ProgramUniformMatrix3DV OpenGL::programUniformMatrix3dv = nullptr;
OpenGL::ProgramUniformMatrix3FV OpenGL::programUniformMatrix3fv = nullptr;
OpenGL::ProgramUniformMatrix3X2DV OpenGL::programUniformMatrix3x2dv = nullptr;
OpenGL::ProgramUniformMatrix3X2FV OpenGL::programUniformMatrix3x2fv = nullptr;
OpenGL::ProgramUniformMatrix3X4DV OpenGL::programUniformMatrix3x4dv = nullptr;
OpenGL::ProgramUniformMatrix3X4FV OpenGL::programUniformMatrix3x4fv = nullptr;
OpenGL::ProgramUniformMatrix4DV OpenGL::programUniformMatrix4dv = nullptr;
OpenGL::ProgramUniformMatrix4FV OpenGL::programUniformMatrix4fv = nullptr;
OpenGL::ProgramUniformMatrix4X2DV OpenGL::programUniformMatrix4x2dv = nullptr;
OpenGL::ProgramUniformMatrix4X2FV OpenGL::programUniformMatrix4x2fv = nullptr;
OpenGL::ProgramUniformMatrix4X3DV OpenGL::programUniformMatrix4x3dv = nullptr;
OpenGL::ProgramUniformMatrix4X3FV OpenGL::programUniformMatrix4x3fv = nullptr;
OpenGL::ReleaseShaderCompiler OpenGL::releaseShaderCompiler = nullptr;
OpenGL::ShaderBinary OpenGL::shaderBinary = nullptr;
OpenGL::ScissorArrayV OpenGL::scissorArrayv = nullptr;
OpenGL::ScissorIndexed OpenGL::scissorIndexed = nullptr;
OpenGL::ScissorIndexedV OpenGL::scissorIndexedv = nullptr;
OpenGL::UseProgramStages OpenGL::useProgramStages = nullptr;
OpenGL::ValidateProgramPipeline OpenGL::validateProgramPipeline = nullptr;
OpenGL::VertexAttribL1D OpenGL::vertexAttribL1d = nullptr;
OpenGL::VertexAttribL1DV OpenGL::vertexAttribL1dv = nullptr;
OpenGL::VertexAttribL2D OpenGL::vertexAttribL2d = nullptr;
OpenGL::VertexAttribL2DV OpenGL::vertexAttribL2dv = nullptr;
OpenGL::VertexAttribL3D OpenGL::vertexAttribL3d = nullptr;
OpenGL::VertexAttribL3DV OpenGL::vertexAttribL3dv = nullptr;
OpenGL::VertexAttribL4D OpenGL::vertexAttribL4d = nullptr;
OpenGL::VertexAttribL4DV OpenGL::vertexAttribL4dv = nullptr;
OpenGL::VertexAttribLPointer OpenGL::vertexAttribLPointer = nullptr;
OpenGL::ViewportArrayV OpenGL::viewportArrayv = nullptr;
OpenGL::ViewportIndexedF OpenGL::viewportIndexedf = nullptr;
OpenGL::ViewportIndexedFV OpenGL::viewportIndexedfv = nullptr;

// Version 4.2

OpenGL::BindImageTexture OpenGL::bindImageTexture = nullptr;
OpenGL::DrawArraysInstancedBaseInstance OpenGL::drawArraysInstancedBaseInstance = nullptr;
OpenGL::DrawElementsInstancedBaseInstance OpenGL::drawElementsInstancedBaseInstance = nullptr;
OpenGL::DrawElementsInstancedBaseVertexBaseInstance OpenGL::drawElementsInstancedBaseVertexBaseInstance = nullptr;
OpenGL::DrawTransformFeedbackInstanced OpenGL::drawTransformFeedbackInstanced = nullptr;
OpenGL::DrawTransformFeedbackStreamInstanced OpenGL::drawTransformFeedbackStreamInstanced = nullptr;
OpenGL::GetActiveAtomicCounterBufferIV OpenGL::getActiveAtomicCounterBufferiv = nullptr;
OpenGL::GetInternalformatIV OpenGL::getInternalformativ = nullptr;
OpenGL::MemoryBarrier OpenGL::memoryBarrier = nullptr;
OpenGL::TexStorage1D OpenGL::texStorage1D = nullptr;
OpenGL::TexStorage2D OpenGL::texStorage2D = nullptr;
OpenGL::TexStorage3D OpenGL::texStorage3D = nullptr;

// Version 4.3

OpenGL::BindVertexBuffer OpenGL::bindVertexBuffer = nullptr;
OpenGL::ClearBufferData OpenGL::clearBufferData = nullptr;
OpenGL::ClearBufferSubData OpenGL::clearBufferSubData = nullptr;
OpenGL::CopyImageSubData OpenGL::copyImageSubData = nullptr;
OpenGL::DispatchCompute OpenGL::dispatchCompute = nullptr;
OpenGL::DispatchComputeIndirect OpenGL::dispatchComputeIndirect = nullptr;
OpenGL::DebugMessageCallback OpenGL::debugMessageCallback = nullptr;
OpenGL::DebugMessageControl OpenGL::debugMessageControl = nullptr;
OpenGL::DebugMessageInsert OpenGL::debugMessageInsert = nullptr;
OpenGL::FramebufferParameterI OpenGL::framebufferParameteri = nullptr;
OpenGL::GetDebugMessageLog OpenGL::getDebugMessageLog = nullptr;
OpenGL::GetFramebufferParameterIV OpenGL::getFramebufferParameteriv = nullptr;
OpenGL::GetInternalformatI64V OpenGL::getInternalformati64v = nullptr;
OpenGL::GetObjectLabel OpenGL::getObjectLabel = nullptr;
OpenGL::GetObjectPtrLabel OpenGL::getObjectPtrLabel = nullptr;
OpenGL::GetProgramInterfaceIV OpenGL::getProgramInterfaceiv = nullptr;
OpenGL::GetProgramResourceIndex OpenGL::getProgramResourceIndex = nullptr;
OpenGL::GetProgramResourceIV OpenGL::getProgramResourceiv = nullptr;
OpenGL::GetProgramResourceLocation OpenGL::getProgramResourceLocation = nullptr;
OpenGL::GetProgramResourceLocationIndex OpenGL::getProgramResourceLocationIndex = nullptr;
OpenGL::GetProgramResourceName OpenGL::getProgramResourceName = nullptr;
OpenGL::InvalidateBufferData OpenGL::invalidateBufferData = nullptr;
OpenGL::InvalidateBufferSubData OpenGL::invalidateBufferSubData = nullptr;
OpenGL::InvalidateFramebuffer OpenGL::invalidateFramebuffer = nullptr;
OpenGL::InvalidateSubFramebuffer OpenGL::invalidateSubFramebuffer = nullptr;
OpenGL::InvalidateTexImage OpenGL::invalidateTexImage = nullptr;
OpenGL::InvalidateTexSubImage OpenGL::invalidateTexSubImage = nullptr;
OpenGL::MultiDrawArraysIndirect OpenGL::multiDrawArraysIndirect = nullptr;
OpenGL::MultiDrawElementsIndirect OpenGL::multiDrawElementsIndirect = nullptr;
OpenGL::ObjectLabel OpenGL::objectLabel = nullptr;
OpenGL::ObjectPtrLabel OpenGL::objectPtrLabel = nullptr;
OpenGL::PopDebugGroup OpenGL::popDebugGroup = nullptr;
OpenGL::PushDebugGroup OpenGL::pushDebugGroup = nullptr;
OpenGL::ShaderStorageBlockBinding OpenGL::shaderStorageBlockBinding = nullptr;
OpenGL::TexBufferRange OpenGL::texBufferRange = nullptr;
OpenGL::TexStorage2DMultisample OpenGL::texStorage2DMultisample = nullptr;
OpenGL::TexStorage3DMultisample OpenGL::texStorage3DMultisample = nullptr;
OpenGL::TextureView OpenGL::textureView = nullptr;
OpenGL::VertexAttribBinding OpenGL::vertexAttribBinding = nullptr;
OpenGL::VertexAttribFormat OpenGL::vertexAttribFormat = nullptr;
OpenGL::VertexAttribIFormat OpenGL::vertexAttribIFormat = nullptr;
OpenGL::VertexAttribLFormat OpenGL::vertexAttribLFormat = nullptr;
OpenGL::VertexBindingDivisor OpenGL::vertexBindingDivisor = nullptr;

// Version 4.4

OpenGL::BindBuffersBase OpenGL::bindBuffersBase = nullptr;
OpenGL::BindBuffersRange OpenGL::bindBuffersRange = nullptr;
OpenGL::BindImageTextures OpenGL::bindImageTextures = nullptr;
OpenGL::BindSamplers OpenGL::bindSamplers = nullptr;
OpenGL::BindTextures OpenGL::bindTextures = nullptr;
OpenGL::BindVertexBuffers OpenGL::bindVertexBuffers = nullptr;
OpenGL::BufferStorage OpenGL::bufferStorage = nullptr;
OpenGL::ClearTexImage OpenGL::clearTexImage = nullptr;
OpenGL::ClearTexSubImage OpenGL::clearTexSubImage = nullptr;

// Version 4.5

OpenGL::BindTextureUnit OpenGL::bindTextureUnit = nullptr;
OpenGL::BlitNamedFramebuffer OpenGL::blitNamedFramebuffer = nullptr;
OpenGL::CheckNamedFramebufferStatus OpenGL::checkNamedFramebufferStatus = nullptr;
OpenGL::ClearNamedBufferData OpenGL::clearNamedBufferData = nullptr;
OpenGL::ClearNamedBufferSubData OpenGL::clearNamedBufferSubData = nullptr;
OpenGL::ClearNamedFramebufferFI OpenGL::clearNamedFramebufferfi = nullptr;
OpenGL::ClearNamedFramebufferFV OpenGL::clearNamedFramebufferfv = nullptr;
OpenGL::ClearNamedFramebufferIV OpenGL::clearNamedFramebufferiv = nullptr;
OpenGL::ClearNamedFramebufferUIV OpenGL::clearNamedFramebufferuiv = nullptr;
OpenGL::ClipControl OpenGL::clipControl = nullptr;
OpenGL::CompressedTextureSubImage1D OpenGL::compressedTextureSubImage1D = nullptr;
OpenGL::CompressedTextureSubImage2D OpenGL::compressedTextureSubImage2D = nullptr;
OpenGL::CompressedTextureSubImage3D OpenGL::compressedTextureSubImage3D = nullptr;
OpenGL::CopyNamedBufferSubData OpenGL::copyNamedBufferSubData = nullptr;
OpenGL::CopyTextureSubImage1D OpenGL::copyTextureSubImage1D = nullptr;
OpenGL::CopyTextureSubImage2D OpenGL::copyTextureSubImage2D = nullptr;
OpenGL::CopyTextureSubImage3D OpenGL::copyTextureSubImage3D = nullptr;
OpenGL::CreateBuffers OpenGL::createBuffers = nullptr;
OpenGL::CreateFramebuffers OpenGL::createFramebuffers = nullptr;
OpenGL::CreateProgramPipelines OpenGL::createProgramPipelines = nullptr;
OpenGL::CreateQueries OpenGL::createQueries = nullptr;
OpenGL::CreateRenderbuffers OpenGL::createRenderbuffers = nullptr;
OpenGL::CreateSamplers OpenGL::createSamplers = nullptr;
OpenGL::CreateTextures OpenGL::createTextures = nullptr;
OpenGL::CreateTransformFeedbacks OpenGL::createTransformFeedbacks = nullptr;
OpenGL::CreateVertexArrays OpenGL::createVertexArrays = nullptr;
OpenGL::DisableVertexArrayAttrib OpenGL::disableVertexArrayAttrib = nullptr;
OpenGL::EnableVertexArrayAttrib OpenGL::enableVertexArrayAttrib = nullptr;
OpenGL::FlushMappedNamedBufferRange OpenGL::flushMappedNamedBufferRange = nullptr;
OpenGL::GenerateTextureMipmap OpenGL::generateTextureMipmap = nullptr;
OpenGL::GetCompressedTextureImage OpenGL::getCompressedTextureImage = nullptr;
OpenGL::GetCompressedTextureSubImage OpenGL::getCompressedTextureSubImage = nullptr;
OpenGL::GetGraphicsResetStatus OpenGL::getGraphicsResetStatus = nullptr;
OpenGL::GetNamedBufferParameterI64V OpenGL::getNamedBufferParameteri64v = nullptr;
OpenGL::GetNamedBufferParameterIV OpenGL::getNamedBufferParameteriv = nullptr;
OpenGL::GetNamedBufferPointerV OpenGL::getNamedBufferPointerv = nullptr;
OpenGL::GetNamedBufferSubData OpenGL::getNamedBufferSubData = nullptr;
OpenGL::GetNamedFramebufferAttachmentParameterIV OpenGL::getNamedFramebufferAttachmentParameteriv = nullptr;
OpenGL::GetNamedFramebufferParameterIV OpenGL::getNamedFramebufferParameteriv = nullptr;
OpenGL::GetNamedRenderbufferParameterIV OpenGL::getNamedRenderbufferParameteriv = nullptr;
OpenGL::GetnCompressedTexImage OpenGL::getnCompressedTexImage = nullptr;
OpenGL::GetnTexImage OpenGL::getnTexImage = nullptr;
OpenGL::GetnUniformDV OpenGL::getnUniformdv = nullptr;
OpenGL::GetnUniformFV OpenGL::getnUniformfv = nullptr;
OpenGL::GetnUniformIV OpenGL::getnUniformiv = nullptr;
OpenGL::GetnUniformUIV OpenGL::getnUniformuiv = nullptr;
OpenGL::GetQueryBufferObjectI64V OpenGL::getQueryBufferObjecti64v = nullptr;
OpenGL::GetQueryBufferObjectIV OpenGL::getQueryBufferObjectiv = nullptr;
OpenGL::GetQueryBufferObjectUI64V OpenGL::getQueryBufferObjectui64v = nullptr;
OpenGL::GetQueryBufferObjectUIV OpenGL::getQueryBufferObjectuiv = nullptr;
OpenGL::GetTextureImage OpenGL::getTextureImage = nullptr;
OpenGL::GetTextureLevelParameterFV OpenGL::getTextureLevelParameterfv = nullptr;
OpenGL::GetTextureLevelParameterIV OpenGL::getTextureLevelParameteriv = nullptr;
OpenGL::GetTextureParameterFV OpenGL::getTextureParameterfv = nullptr;
OpenGL::GetTextureParameterIIV OpenGL::getTextureParameterIiv = nullptr;
OpenGL::GetTextureParameterIV OpenGL::getTextureParameteriv = nullptr;
OpenGL::GetTextureParameterIUIV OpenGL::getTextureParameterIuiv = nullptr;
OpenGL::GetTextureSubImage OpenGL::getTextureSubImage = nullptr;
OpenGL::GetTransformFeedbackI64_V OpenGL::getTransformFeedbacki64_v = nullptr;
OpenGL::GetTransformFeedbackIV OpenGL::getTransformFeedbackiv = nullptr;
OpenGL::GetTransformFeedbackI_V OpenGL::getTransformFeedbacki_v = nullptr;
OpenGL::GetVertexArrayIndexed64IV OpenGL::getVertexArrayIndexed64iv = nullptr;
OpenGL::GetVertexArrayIndexedIV OpenGL::getVertexArrayIndexediv = nullptr;
OpenGL::GetVertexArrayIV OpenGL::getVertexArrayiv = nullptr;
OpenGL::InvalidateNamedFramebufferData OpenGL::invalidateNamedFramebufferData = nullptr;
OpenGL::InvalidateNamedFramebufferSubData OpenGL::invalidateNamedFramebufferSubData = nullptr;
OpenGL::MapNamedBuffer OpenGL::mapNamedBuffer = nullptr;
OpenGL::MapNamedBufferRange OpenGL::mapNamedBufferRange = nullptr;
OpenGL::MemoryBarrierByRegion OpenGL::memoryBarrierByRegion = nullptr;
OpenGL::NamedBufferData OpenGL::namedBufferData = nullptr;
OpenGL::NamedBufferStorage OpenGL::namedBufferStorage = nullptr;
OpenGL::NamedBufferSubData OpenGL::namedBufferSubData = nullptr;
OpenGL::NamedFramebufferDrawBuffer OpenGL::namedFramebufferDrawBuffer = nullptr;
OpenGL::NamedFramebufferDrawBuffers OpenGL::namedFramebufferDrawBuffers = nullptr;
OpenGL::NamedFramebufferParameterI OpenGL::namedFramebufferParameteri = nullptr;
OpenGL::NamedFramebufferReadBuffer OpenGL::namedFramebufferReadBuffer = nullptr;
OpenGL::NamedFramebufferRenderbuffer OpenGL::namedFramebufferRenderbuffer = nullptr;
OpenGL::NamedFramebufferTexture OpenGL::namedFramebufferTexture = nullptr;
OpenGL::NamedFramebufferTextureLayer OpenGL::namedFramebufferTextureLayer = nullptr;
OpenGL::NamedRenderbufferStorage OpenGL::namedRenderbufferStorage = nullptr;
OpenGL::NamedRenderbufferStorageMultisample OpenGL::namedRenderbufferStorageMultisample = nullptr;
OpenGL::ReadnPixels OpenGL::readnPixels = nullptr;
OpenGL::TransformFeedbackBufferBase OpenGL::transformFeedbackBufferBase = nullptr;
OpenGL::TransformFeedbackBufferRange OpenGL::transformFeedbackBufferRange = nullptr;
OpenGL::TextureBarrier OpenGL::textureBarrier = nullptr;
OpenGL::TextureBuffer OpenGL::textureBuffer = nullptr;
OpenGL::TextureBufferRange OpenGL::textureBufferRange = nullptr;
OpenGL::TextureParameterF OpenGL::textureParameterf = nullptr;
OpenGL::TextureParameterFV OpenGL::textureParameterfv = nullptr;
OpenGL::TextureParameterI OpenGL::textureParameteri = nullptr;
OpenGL::TextureParameterIIV OpenGL::textureParameterIiv = nullptr;
OpenGL::TextureParameterIUIV OpenGL::textureParameterIuiv = nullptr;
OpenGL::TextureParameterIV OpenGL::textureParameteriv = nullptr;
OpenGL::TextureStorage1D OpenGL::textureStorage1D = nullptr;
OpenGL::TextureStorage2D OpenGL::textureStorage2D = nullptr;
OpenGL::TextureStorage2DMultisample OpenGL::textureStorage2DMultisample = nullptr;
OpenGL::TextureStorage3D OpenGL::textureStorage3D = nullptr;
OpenGL::TextureStorage3DMultisample OpenGL::textureStorage3DMultisample = nullptr;
OpenGL::TextureSubImage1D OpenGL::textureSubImage1D = nullptr;
OpenGL::TextureSubImage2D OpenGL::textureSubImage2D = nullptr;
OpenGL::TextureSubImage3D OpenGL::textureSubImage3D = nullptr;
OpenGL::UnmapNamedBuffer OpenGL::unmapNamedBuffer = nullptr;
OpenGL::VertexArrayAttribBinding OpenGL::vertexArrayAttribBinding = nullptr;
OpenGL::VertexArrayAttribFormat OpenGL::vertexArrayAttribFormat = nullptr;
OpenGL::VertexArrayAttribIFormat OpenGL::vertexArrayAttribIFormat = nullptr;
OpenGL::VertexArrayAttribLFormat OpenGL::vertexArrayAttribLFormat = nullptr;
OpenGL::VertexArrayBindingDivisor OpenGL::vertexArrayBindingDivisor = nullptr;
OpenGL::VertexArrayElementBuffer OpenGL::vertexArrayElementBuffer = nullptr;
OpenGL::VertexArrayVertexBuffer OpenGL::vertexArrayVertexBuffer = nullptr;
OpenGL::VertexArrayVertexBuffers OpenGL::vertexArrayVertexBuffers = nullptr;

// Static

void OpenGL::checkForErrors(const Char8* file, const Uint32 line, const Char8* function)
{
	Uint32 errorCode;

	while((errorCode = getError()) != NO_ERROR)
		reportError(errorCode, file, line, function);
}

void OpenGL::initialise()
{
	enable(DEBUG_OUTPUT_SYNCHRONOUS);
	DE_CHECK_ERROR_OPENGL();
	debugMessageControl(DONT_CARE, DONT_CARE, DONT_CARE, 0, nullptr, TRUE);
	DE_CHECK_ERROR_OPENGL();
	debugMessageCallback(processDebugMessage, nullptr);
}

// Private

const Char8* OpenGL::COMPONENT_TAG = "[Platform::OpenGL]";

const Array<Char8*, 6u> OpenGL::DEBUG_MESSAGE_SOURCE_NAMES
{{
	"OpenGL",
	"window system",
	"shader compiler",
	"third party",
	"application",
	"other source"
}};

const Array<Char8*, 9u> OpenGL::DEBUG_MESSAGE_TYPE_NAMES
{{
	"Deprecated behaviour",
	"Error",
	"Group pop",
	"Group push"
	"Marker",
	"Other",
	"Performance",
	"Portability",
	"Undefined behaviour"
}};

// Static

void OpenGL::reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function)
{
	StringStream8 stringStream;
	stringStream << "Error caught at " << file << " on line " << line << " in function " << function << '.';
	
	// TODO: check GL_MAX_DEBUG_MESSAGE_LENGTH
	debugMessageInsert(DEBUG_SOURCE_APPLICATION, DEBUG_TYPE_ERROR, errorCode, DEBUG_SEVERITY_HIGH, -1,
		stringStream.str().c_str());

	//DE_CHECK_ERROR_OPENGL(); // TODO: causes a stack overflow if debugMessageInsert generates an error
}

void OpenGL::processDebugMessage(const Uint32 messageSource, const Uint32 messageType, const Uint32 messageId,
	const Uint32 messageSeverity, const Int32 messageLength, const Char8* message, const Void* userData)
{
	static_cast<Void>(messageLength);
	static_cast<Void>(userData);
	
	const Char8* messageSourceName = DEBUG_MESSAGE_SOURCE_NAMES[messageSource - DEBUG_SOURCE_API];

	defaultLog << getDebugMessageLogLevel(messageSeverity) << COMPONENT_TAG << ' ' <<
		getDebugMessageTypeName(messageType) << " message (" << StreamFormat::Hexadecimal << messageId <<
		StreamFormat::Decimal << ") from " << messageSourceName << ": '" << message << '\'' << Log::Flush();
}

LogLevel OpenGL::getDebugMessageLogLevel(const Uint32 messageSeverity)
{
	switch(messageSeverity)
	{
		case DEBUG_SEVERITY_HIGH:
			return LogLevel::Error;

		case DEBUG_SEVERITY_MEDIUM:
		case DEBUG_SEVERITY_LOW:
			return LogLevel::Warning;

		case DEBUG_SEVERITY_NOTIFICATION:
			return LogLevel::Info;

		default:
			DE_ASSERT(false);
			return LogLevel();
	}
}

const Char8* OpenGL::getDebugMessageTypeName(const Uint32 messageType)
{
	switch(messageType)
	{
		case DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return DEBUG_MESSAGE_TYPE_NAMES[0];

		case DEBUG_TYPE_ERROR:
			return DEBUG_MESSAGE_TYPE_NAMES[1];

		case DEBUG_TYPE_MARKER:
			return DEBUG_MESSAGE_TYPE_NAMES[4];

		case DEBUG_TYPE_OTHER:
			return DEBUG_MESSAGE_TYPE_NAMES[5];

		case DEBUG_TYPE_PERFORMANCE:
			return DEBUG_MESSAGE_TYPE_NAMES[6];

		case DEBUG_TYPE_POP_GROUP:
			return DEBUG_MESSAGE_TYPE_NAMES[2];

		case DEBUG_TYPE_PORTABILITY:
			return DEBUG_MESSAGE_TYPE_NAMES[7];

		case DEBUG_TYPE_PUSH_GROUP:
			return DEBUG_MESSAGE_TYPE_NAMES[3];

		case DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return DEBUG_MESSAGE_TYPE_NAMES[8];

		default:
			DE_ASSERT(false);
			return DEBUG_MESSAGE_TYPE_NAMES[0];
	}
}
