/**
 * @file platform/opengl/OpenGLInterface.h
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

#pragma once

#include <core/Array.h>
#include <core/Error.h>
#include <core/Log.h>
#include <core/Platform.h>
#include <core/Types.h>
#include <core/UtilityMacros.h>
#include <platform/GraphicsExtensionManager.h>
#include <platform/opengl/OpenGL.h>

#if DE_BUILD == DE_BUILD_PRODUCTION
	#define DE_CHECK_ERROR_OPENGL(instance) \
		DE_NO_OPERATION
#else
	#define DE_CHECK_ERROR_OPENGL(instance) \
		instance.checkForErrors(DE_FILE, DE_LINE, DE_FUNCTION)
#endif

namespace Platform
{
	class OpenGL final
	{
	public:

		// Version 1.0

		GLBlendFunc blendFunc = nullptr;
		GLClear clear = nullptr;
		GLClearColor clearColor = nullptr;
		GLClearDepth clearDepth = nullptr;
		GLClearStencil clearStencil = nullptr;
		GLColorMask colorMask = nullptr;
		GLCullFace cullFace = nullptr;
		GLDepthFunc depthFunc = nullptr;
		GLDepthMask depthMask = nullptr;
		GLDepthRange depthRange = nullptr;
		GLDisable disable = nullptr;
		GLDrawBuffer drawBuffer = nullptr;
		GLEnable enable = nullptr;
		GLFinish finish = nullptr;
		GLFlush flush = nullptr;
		GLFrontFace frontFace = nullptr;
		GLGetBooleanV getBooleanv = nullptr;
		GLGetDoubleV getDoublev = nullptr;
		GLGetError getError = nullptr;
		GLGetFloatV getFloatv = nullptr;
		GLGetIntegerV getIntegerv = nullptr;
		GLGetString getString = nullptr;
		GLGetTexImage getTexImage = nullptr;
		GLGetTexLevelParameterFV getTexLevelParameterfv = nullptr;
		GLGetTexLevelParameterIV getTexLevelParameteriv = nullptr;
		GLGetTexParameterFV getTexParameterfv = nullptr;
		GLGetTexParameterIV getTexParameteriv = nullptr;
		GLHint hint = nullptr;
		GLIsEnabled isEnabled = nullptr;
		GLLineWidth lineWidth = nullptr;
		GLLogicOp logicOp = nullptr;
		GLPixelStoreF pixelStoref = nullptr;
		GLPixelStoreI pixelStorei = nullptr;
		GLPointSize pointSize = nullptr;
		GLPolygonMode polygonMode = nullptr;
		GLReadBuffer readBuffer = nullptr;
		GLReadPixels readPixels = nullptr;
		GLScissor scissor = nullptr;
		GLStencilFunc stencilFunc = nullptr;
		GLStencilMask stencilMask = nullptr;
		GLStencilOp stencilOp = nullptr;
		GLTexImage1D texImage1D = nullptr;
		GLTexImage2D texImage2D = nullptr;
		GLTexParameterF texParameterf = nullptr;
		GLTexParameterFV texParameterfv = nullptr;
		GLTexParameterI texParameteri = nullptr;
		GLTexParameterIV texParameteriv = nullptr;
		GLViewport viewport = nullptr;


		// Version 1.1

		GLBindTexture bindTexture = nullptr;
		GLCopyTexImage1D copyTexImage1D = nullptr;
		GLCopyTexImage2D copyTexImage2D = nullptr;
		GLCopyTexSubImage1D copyTexSubImage1D = nullptr;
		GLCopyTexSubImage2D copyTexSubImage2D = nullptr;
		GLDeleteTextures deleteTextures = nullptr;
		GLDrawArrays drawArrays = nullptr;
		GLDrawElements drawElements = nullptr;
		GLGenTextures genTextures = nullptr;
		GLGetPointerV getPointerv = nullptr;
		GLIsTexture isTexture = nullptr;
		GLPolygonOffset polygonOffset = nullptr;
		GLTexSubImage1D texSubImage1D = nullptr;
		GLTexSubImage2D texSubImage2D = nullptr;


		// Version 1.2

		GLCopyTexSubImage3D copyTexSubImage3D = nullptr;
		GLDrawRangeElements drawRangeElements = nullptr;
		GLTexImage3D texImage3D = nullptr;
		GLTexSubImage3D texSubImage3D = nullptr;


		// Version 1.3

		GLActiveTexture activeTexture = nullptr;
		GLCompressedTexImage1D compressedTexImage1D = nullptr;
		GLCompressedTexImage2D compressedTexImage2D = nullptr;
		GLCompressedTexImage3D compressedTexImage3D = nullptr;
		GLCompressedTexSubImage1D compressedTexSubImage1D = nullptr;
		GLCompressedTexSubImage2D compressedTexSubImage2D = nullptr;
		GLCompressedTexSubImage3D compressedTexSubImage3D = nullptr;
		GLGetCompressedTexImage getCompressedTexImage = nullptr;
		GLSampleCoverage sampleCoverage = nullptr;


		// Version 1.4

		GLBlendColor blendColor = nullptr;
		GLBlendEquation blendEquation = nullptr;
		GLBlendFuncSeparate blendFuncSeparate = nullptr;
		GLMultiDrawArrays multiDrawArrays = nullptr;
		GLMultiDrawElements multiDrawElements = nullptr;
		GLPointParameterF pointParameterf = nullptr;
		GLPointParameterFV pointParameterfv = nullptr;
		GLPointParameterI pointParameteri = nullptr;
		GLPointParameterIV pointParameteriv = nullptr;


		// Version 1.5

		GLBeginQuery beginQuery = nullptr;
		GLBindBuffer bindBuffer = nullptr;
		GLBufferData bufferData = nullptr;
		GLBufferSubData bufferSubData = nullptr;
		GLDeleteBuffers deleteBuffers = nullptr;
		GLDeleteQueries deleteQueries = nullptr;
		GLEndQuery endQuery = nullptr;
		GLGenBuffers genBuffers = nullptr;
		GLGenQueries genQueries = nullptr;
		GLGetBufferParameterIV getBufferParameteriv = nullptr;
		GLGetBufferPointerV getBufferPointerv = nullptr;
		GLGetBufferSubData getBufferSubData = nullptr;
		GLGetQueryIV getQueryiv = nullptr;
		GLGetQueryObjectIV getQueryObjectiv = nullptr;
		GLGetQueryObjectUIV getQueryObjectuiv = nullptr;
		GLIsBuffer isBuffer = nullptr;
		GLIsQuery isQuery = nullptr;
		GLMapBuffer mapBuffer = nullptr;
		GLUnmapBuffer unmapBuffer = nullptr;


		// Version 2.0

		GLAttachShader attachShader = nullptr;
		GLBindAttribLocation bindAttribLocation = nullptr;
		GLBlendEquationSeparate blendEquationSeparate = nullptr;
		GLCompileShader compileShader = nullptr;
		GLCreateProgram createProgram = nullptr;
		GLCreateShader createShader = nullptr;
		GLDeleteProgram deleteProgram = nullptr;
		GLDeleteShader deleteShader = nullptr;
		GLDetachShader detachShader = nullptr;
		GLDisableVertexAttribArray disableVertexAttribArray = nullptr;
		GLDrawBuffers drawBuffers = nullptr;
		GLEnableVertexAttribArray enableVertexAttribArray = nullptr;
		GLGetActiveAttrib getActiveAttrib = nullptr;
		GLGetActiveUniform getActiveUniform = nullptr;
		GLGetAttachedShaders getAttachedShaders = nullptr;
		GLGetAttribLocation getAttribLocation = nullptr;
		GLGetProgramInfoLog getProgramInfoLog = nullptr;
		GLGetProgramIV getProgramiv = nullptr;
		GLGetShaderInfoLog getShaderInfoLog = nullptr;
		GLGetShaderIV getShaderiv = nullptr;
		GLGetShaderSource getShaderSource = nullptr;
		GLGetUniformFV getUniformfv = nullptr;
		GLGetUniformIV getUniformiv = nullptr;
		GLGetUniformLocation getUniformLocation = nullptr;
		GLGetVertexAttribDV getVertexAttribdv = nullptr;
		GLGetVertexAttribFV getVertexAttribfv = nullptr;
		GLGetVertexAttribIV getVertexAttribiv = nullptr;
		GLGetVertexAttribPointerV getVertexAttribPointerv = nullptr;
		GLIsProgram isProgram = nullptr;
		GLIsShader isShader = nullptr;
		GLLinkProgram linkProgram = nullptr;
		GLShaderSource shaderSource = nullptr;
		GLStencilFuncSeparate stencilFuncSeparate = nullptr;
		GLStencilMaskSeparate stencilMaskSeparate = nullptr;
		GLStencilOpSeparate stencilOpSeparate = nullptr;
		GLUniform1F uniform1f = nullptr;
		GLUniform1FV uniform1fv = nullptr;
		GLUniform1I uniform1i = nullptr;
		GLUniform1IV uniform1iv = nullptr;
		GLUniform2F uniform2f = nullptr;
		GLUniform2FV uniform2fv = nullptr;
		GLUniform2I uniform2i = nullptr;
		GLUniform2IV uniform2iv = nullptr;
		GLUniform3F uniform3f = nullptr;
		GLUniform3FV uniform3fv = nullptr;
		GLUniform3I uniform3i = nullptr;
		GLUniform3IV uniform3iv = nullptr;
		GLUniform4F uniform4f = nullptr;
		GLUniform4FV uniform4fv = nullptr;
		GLUniform4I uniform4i = nullptr;
		GLUniform4IV uniform4iv = nullptr;
		GLUniformMatrix2FV uniformMatrix2fv = nullptr;
		GLUniformMatrix3FV uniformMatrix3fv = nullptr;
		GLUniformMatrix4FV uniformMatrix4fv = nullptr;
		GLUseProgram useProgram = nullptr;
		GLValidateProgram validateProgram = nullptr;
		GLVertexAttrib1D vertexAttrib1d = nullptr;
		GLVertexAttrib1DV vertexAttrib1dv = nullptr;
		GLVertexAttrib1F vertexAttrib1f = nullptr;
		GLVertexAttrib1FV vertexAttrib1fv = nullptr;
		GLVertexAttrib1S vertexAttrib1s = nullptr;
		GLVertexAttrib1SV vertexAttrib1sv = nullptr;
		GLVertexAttrib2D vertexAttrib2d = nullptr;
		GLVertexAttrib2DV vertexAttrib2dv = nullptr;
		GLVertexAttrib2F vertexAttrib2f = nullptr;
		GLVertexAttrib2FV vertexAttrib2fv = nullptr;
		GLVertexAttrib2S vertexAttrib2s = nullptr;
		GLVertexAttrib2SV vertexAttrib2sv = nullptr;
		GLVertexAttrib3D vertexAttrib3d = nullptr;
		GLVertexAttrib3DV vertexAttrib3dv = nullptr;
		GLVertexAttrib3F vertexAttrib3f = nullptr;
		GLVertexAttrib3FV vertexAttrib3fv = nullptr;
		GLVertexAttrib3S vertexAttrib3s = nullptr;
		GLVertexAttrib3SV vertexAttrib3sv = nullptr;
		GLVertexAttrib4BV vertexAttrib4bv = nullptr;
		GLVertexAttrib4D vertexAttrib4d = nullptr;
		GLVertexAttrib4DV vertexAttrib4dv = nullptr;
		GLVertexAttrib4F vertexAttrib4f = nullptr;
		GLVertexAttrib4FV vertexAttrib4fv = nullptr;
		GLVertexAttrib4IV vertexAttrib4iv = nullptr;
		GLVertexAttrib4NBV vertexAttrib4Nbv = nullptr;
		GLVertexAttrib4NIV vertexAttrib4Niv = nullptr;
		GLVertexAttrib4NSV vertexAttrib4Nsv = nullptr;
		GLVertexAttrib4NUB vertexAttrib4Nub = nullptr;
		GLVertexAttrib4NUBV vertexAttrib4Nubv = nullptr;
		GLVertexAttrib4NUIV vertexAttrib4Nuiv = nullptr;
		GLVertexAttrib4NUSV vertexAttrib4Nusv = nullptr;
		GLVertexAttrib4S vertexAttrib4s = nullptr;
		GLVertexAttrib4SV vertexAttrib4sv = nullptr;
		GLVertexAttrib4UBV vertexAttrib4ubv = nullptr;
		GLVertexAttrib4UIV vertexAttrib4uiv = nullptr;
		GLVertexAttrib4USV vertexAttrib4usv = nullptr;
		GLVertexAttribPointer vertexAttribPointer = nullptr;


		// Version 2.1

		GLUniformMatrix2X3FV uniformMatrix2x3fv = nullptr;
		GLUniformMatrix2X4FV uniformMatrix2x4fv = nullptr;
		GLUniformMatrix3X2FV uniformMatrix3x2fv = nullptr;
		GLUniformMatrix3X4FV uniformMatrix3x4fv = nullptr;
		GLUniformMatrix4X2FV uniformMatrix4x2fv = nullptr;
		GLUniformMatrix4X3FV uniformMatrix4x3fv = nullptr;


		// Version 3.0

		GLBeginConditionalRender beginConditionalRender = nullptr;
		GLBeginTransformFeedback beginTransformFeedback = nullptr;
		GLBindBufferBase bindBufferBase = nullptr;
		GLBindBufferRange bindBufferRange = nullptr;
		GLBindFragDataLocation bindFragDataLocation = nullptr;
		GLBindFramebuffer bindFramebuffer = nullptr;
		GLBindRenderbuffer bindRenderbuffer = nullptr;
		GLBindVertexArray bindVertexArray = nullptr;
		GLBlitFramebuffer blitFramebuffer = nullptr;
		GLCheckFramebufferStatus checkFramebufferStatus = nullptr;
		GLClampColor clampColor = nullptr;
		GLClearBufferFI clearBufferfi = nullptr;
		GLClearBufferFV clearBufferfv = nullptr;
		GLClearBufferIV clearBufferiv = nullptr;
		GLClearBufferUIV clearBufferuiv = nullptr;
		GLColorMaskI colorMaski = nullptr;
		GLDeleteFramebuffers deleteFramebuffers = nullptr;
		GLDeleteRenderbuffers deleteRenderbuffers = nullptr;
		GLDeleteVertexArrays deleteVertexArrays = nullptr;
		GLDisableI disablei = nullptr;
		GLEnableI enablei = nullptr;
		GLEndConditionalRender endConditionalRender = nullptr;
		GLEndTransformFeedback endTransformFeedback = nullptr;
		GLFlushMappedBufferRange flushMappedBufferRange = nullptr;
		GLFramebufferRenderbuffer framebufferRenderbuffer = nullptr;
		GLFramebufferTexture1D framebufferTexture1D = nullptr;
		GLFramebufferTexture2D framebufferTexture2D = nullptr;
		GLFramebufferTexture3D framebufferTexture3D = nullptr;
		GLFramebufferTextureLayer framebufferTextureLayer = nullptr;
		GLGenerateMipmap generateMipmap = nullptr;
		GLGenFramebuffers genFramebuffers = nullptr;
		GLGenRenderbuffers genRenderbuffers = nullptr;
		GLGenVertexArrays genVertexArrays = nullptr;
		GLGetBooleanI_V getBooleani_v = nullptr;
		GLGetFragDataLocation getFragDataLocation = nullptr;
		GLGetFramebufferAttachmentParameterIV getFramebufferAttachmentParameteriv = nullptr;
		GLGetIntegerI_V getIntegeri_v = nullptr;
		GLGetRenderbufferParameterIV getRenderbufferParameteriv = nullptr;
		GLGetStringI getStringi = nullptr;
		GLGetTexParameterIIV getTexParameterIiv = nullptr;
		GLGetTexParameterIUIV getTexParameterIuiv = nullptr;
		GLGetTransformFeedbackVarying getTransformFeedbackVarying = nullptr;
		GLGetUniformUIV getUniformuiv = nullptr;
		GLGetVertexAttribIIV getVertexAttribIiv = nullptr;
		GLGetVertexAttribIUIV getVertexAttribIuiv = nullptr;
		GLIsEnabledI isEnabledi = nullptr;
		GLIsFramebuffer isFramebuffer = nullptr;
		GLIsRenderbuffer isRenderbuffer = nullptr;
		GLIsVertexArray isVertexArray = nullptr;
		GLMapBufferRange mapBufferRange = nullptr;
		GLRenderbufferStorage renderbufferStorage = nullptr;
		GLRenderbufferStorageMultisample renderbufferStorageMultisample = nullptr;
		GLTexParameterIIV texParameterIiv = nullptr;
		GLTexParameterIUIV texParameterIuiv = nullptr;
		GLTransformFeedbackVaryings transformFeedbackVaryings = nullptr;
		GLUniform1UI uniform1ui = nullptr;
		GLUniform1UIV uniform1uiv = nullptr;
		GLUniform2UI uniform2ui = nullptr;
		GLUniform2UIV uniform2uiv = nullptr;
		GLUniform3UI uniform3ui = nullptr;
		GLUniform3UIV uniform3uiv = nullptr;
		GLUniform4UI uniform4ui = nullptr;
		GLUniform4UIV uniform4uiv = nullptr;
		GLVertexAttribI1I vertexAttribI1i = nullptr;
		GLVertexAttribI1IV vertexAttribI1iv = nullptr;
		GLVertexAttribI1UI vertexAttribI1ui = nullptr;
		GLVertexAttribI1UIV vertexAttribI1uiv = nullptr;
		GLVertexAttribI2I vertexAttribI2i = nullptr;
		GLVertexAttribI2IV vertexAttribI2iv = nullptr;
		GLVertexAttribI2UI vertexAttribI2ui = nullptr;
		GLVertexAttribI2UIV vertexAttribI2uiv = nullptr;
		GLVertexAttribI3I vertexAttribI3i = nullptr;
		GLVertexAttribI3IV vertexAttribI3iv = nullptr;
		GLVertexAttribI3UI vertexAttribI3ui = nullptr;
		GLVertexAttribI3UIV vertexAttribI3uiv = nullptr;
		GLVertexAttribI4BV vertexAttribI4bv = nullptr;
		GLVertexAttribI4I vertexAttribI4i = nullptr;
		GLVertexAttribI4IV vertexAttribI4iv = nullptr;
		GLVertexAttribI4SV vertexAttribI4sv = nullptr;
		GLVertexAttribI4UBV vertexAttribI4ubv = nullptr;
		GLVertexAttribI4UI vertexAttribI4ui = nullptr;
		GLVertexAttribI4UIV vertexAttribI4uiv = nullptr;
		GLVertexAttribI4USV vertexAttribI4usv = nullptr;
		GLVertexAttribIPointer vertexAttribIPointer = nullptr;


		// Version 3.1

		GLCopyBufferSubData copyBufferSubData = nullptr;
		GLDrawArraysInstanced drawArraysInstanced = nullptr;
		GLDrawElementsInstanced drawElementsInstanced = nullptr;
		GLGetActiveUniformBlockIV getActiveUniformBlockiv = nullptr;
		GLGetActiveUniformBlockName getActiveUniformBlockName = nullptr;
		GLGetActiveUniformName getActiveUniformName = nullptr;
		GLGetActiveUniformsIV getActiveUniformsiv = nullptr;
		GLGetUniformBlockIndex getUniformBlockIndex = nullptr;
		GLGetUniformIndices getUniformIndices = nullptr;
		GLPrimitiveRestartIndex primitiveRestartIndex = nullptr;
		GLTexBuffer texBuffer = nullptr;
		GLUniformBlockBinding uniformBlockBinding = nullptr;


		// Version 3.2

		GLClientWaitSync clientWaitSync = nullptr;
		GLDeleteSync deleteSync = nullptr;
		GLDrawElementsBaseVertex drawElementsBaseVertex = nullptr;
		GLDrawElementsInstancedBaseVertex drawElementsInstancedBaseVertex = nullptr;
		GLDrawRangeElementsBaseVertex drawRangeElementsBaseVertex = nullptr;
		GLFenceSync fenceSync = nullptr;
		GLFramebufferTexture framebufferTexture = nullptr;
		GLGetBufferParameterI64V getBufferParameteri64v = nullptr;
		GLGetInteger64I_V getInteger64i_v = nullptr;
		GLGetInteger64V getInteger64v = nullptr;
		GLGetMultisampleFV getMultisamplefv = nullptr;
		GLGetSyncIV getSynciv = nullptr;
		GLIsSync isSync = nullptr;
		GLMultiDrawElementsBaseVertex multiDrawElementsBaseVertex = nullptr;
		GLProvokingVertex provokingVertex = nullptr;
		GLSampleMaskI sampleMaski = nullptr;
		GLTexImage2DMultisample texImage2DMultisample = nullptr;
		GLTexImage3DMultisample texImage3DMultisample = nullptr;
		GLWaitSync waitSync = nullptr;


		// Version 3.3

		GLBindFragDataLocationIndexed bindFragDataLocationIndexed = nullptr;
		GLBindSampler bindSampler = nullptr;
		GLDeleteSamplers deleteSamplers = nullptr;
		GLGenSamplers genSamplers = nullptr;
		GLGetFragDataIndex getFragDataIndex = nullptr;
		GLGetQueryObjectI64V getQueryObjecti64v = nullptr;
		GLGetQueryObjectUI64V getQueryObjectui64v = nullptr;
		GLGetSamplerParameterFV getSamplerParameterfv = nullptr;
		GLGetSamplerParameterIIV getSamplerParameterIiv = nullptr;
		GLGetSamplerParameterIUIV getSamplerParameterIuiv = nullptr;
		GLGetSamplerParameterIV getSamplerParameteriv = nullptr;
		GLIsSampler isSampler = nullptr;
		GLQueryCounter queryCounter = nullptr;
		GLSamplerParameterF samplerParameterf = nullptr;
		GLSamplerParameterFV samplerParameterfv = nullptr;
		GLSamplerParameterI samplerParameteri = nullptr;
		GLSamplerParameterIV samplerParameteriv = nullptr;
		GLSamplerParameterIIV samplerParameterIiv = nullptr;
		GLSamplerParameterIUIV samplerParameterIuiv = nullptr;
		GLVertexAttribDivisor vertexAttribDivisor = nullptr;
		GLVertexAttribP1UI vertexAttribP1ui = nullptr;
		GLVertexAttribP1UIV vertexAttribP1uiv = nullptr;
		GLVertexAttribP2UI vertexAttribP2ui = nullptr;
		GLVertexAttribP2UIV vertexAttribP2uiv = nullptr;
		GLVertexAttribP3UI vertexAttribP3ui = nullptr;
		GLVertexAttribP3UIV vertexAttribP3uiv = nullptr;
		GLVertexAttribP4UI vertexAttribP4ui = nullptr;
		GLVertexAttribP4UIV vertexAttribP4uiv = nullptr;


		// Version 4.0

		GLBeginQueryIndexed beginQueryIndexed = nullptr;
		GLBindTransformFeedback bindTransformFeedback = nullptr;
		GLBlendEquationI blendEquationi = nullptr;
		GLBlendEquationSeparateI blendEquationSeparatei = nullptr;
		GLBlendFuncI blendFunci = nullptr;
		GLBlendFuncSeparateI blendFuncSeparatei = nullptr;
		GLDeleteTransformFeedbacks deleteTransformFeedbacks = nullptr;
		GLDrawArraysIndirect drawArraysIndirect = nullptr;
		GLDrawElementsIndirect drawElementsIndirect = nullptr;
		GLDrawTransformFeedback drawTransformFeedback = nullptr;
		GLDrawTransformFeedbackStream drawTransformFeedbackStream = nullptr;
		GLEndQueryIndexed endQueryIndexed = nullptr;
		GLGenTransformFeedbacks genTransformFeedbacks = nullptr;
		GLGetActiveSubroutineName getActiveSubroutineName = nullptr;
		GLGetActiveSubroutineUniformIV getActiveSubroutineUniformiv = nullptr;
		GLGetActiveSubroutineUniformName getActiveSubroutineUniformName = nullptr;
		GLGetProgramStageIV getProgramStageiv = nullptr;
		GLGetQueryIndexedIV getQueryIndexediv = nullptr;
		GLGetSubroutineIndex getSubroutineIndex = nullptr;
		GLGetSubroutineUniformLocation getSubroutineUniformLocation = nullptr;
		GLGetUniformDV getUniformdv = nullptr;
		GLGetUniformSubroutineUIV getUniformSubroutineuiv = nullptr;
		GLIsTransformFeedback isTransformFeedback = nullptr;
		GLMinSampleShading minSampleShading = nullptr;
		GLPatchParameterFV patchParameterfv = nullptr;
		GLPatchParameterI patchParameteri = nullptr;
		GLPauseTransformFeedback pauseTransformFeedback = nullptr;
		GLResumeTransformFeedback resumeTransformFeedback = nullptr;
		GLUniform1D uniform1d = nullptr;
		GLUniform1DV uniform1dv = nullptr;
		GLUniform2D uniform2d = nullptr;
		GLUniform2DV uniform2dv = nullptr;
		GLUniform3D uniform3d = nullptr;
		GLUniform3DV uniform3dv = nullptr;
		GLUniform4D uniform4d = nullptr;
		GLUniform4DV uniform4dv = nullptr;
		GLUniformMatrix2DV uniformMatrix2dv = nullptr;
		GLUniformMatrix2X3DV uniformMatrix2x3dv = nullptr;
		GLUniformMatrix2X4DV uniformMatrix2x4dv = nullptr;
		GLUniformMatrix3DV uniformMatrix3dv = nullptr;
		GLUniformMatrix3X2DV uniformMatrix3x2dv = nullptr;
		GLUniformMatrix3X4DV uniformMatrix3x4dv = nullptr;
		GLUniformMatrix4DV uniformMatrix4dv = nullptr;
		GLUniformMatrix4X2DV uniformMatrix4x2dv = nullptr;
		GLUniformMatrix4X3DV uniformMatrix4x3dv = nullptr;
		GLUniformSubroutineSUIV uniformSubroutinesuiv = nullptr;


		// Version 4.1

		GLActiveShaderProgram activeShaderProgram = nullptr;
		GLBindProgramPipeline bindProgramPipeline = nullptr;
		GLClearDepthF clearDepthf = nullptr;
		GLCreateShaderProgramV createShaderProgramv = nullptr;
		GLDeleteProgramPipelines deleteProgramPipelines = nullptr;
		GLDepthRangeArrayV depthRangeArrayv = nullptr;
		GLDepthRangeF depthRangef = nullptr;
		GLDepthRangeIndexed depthRangeIndexed = nullptr;
		GLGenProgramPipelines genProgramPipelines = nullptr;
		GLGetDoubleI_V getDoublei_v = nullptr;
		GLGetFloatI_V getFloati_v = nullptr;
		GLGetProgramBinary getProgramBinary = nullptr;
		GLGetProgramPipelineInfoLog getProgramPipelineInfoLog = nullptr;
		GLGetProgramPipelineIV getProgramPipelineiv = nullptr;
		GLGetShaderPrecisionFormat getShaderPrecisionFormat = nullptr;
		GLGetVertexAttribLDV getVertexAttribLdv = nullptr;
		GLIsProgramPipeline isProgramPipeline = nullptr;
		GLProgramBinary programBinary = nullptr;
		GLProgramParameterI programParameteri = nullptr;
		GLProgramUniform1D programUniform1d = nullptr;
		GLProgramUniform1DV programUniform1dv = nullptr;
		GLProgramUniform1F programUniform1f = nullptr;
		GLProgramUniform1FV programUniform1fv = nullptr;
		GLProgramUniform1I programUniform1i = nullptr;
		GLProgramUniform1IV programUniform1iv = nullptr;
		GLProgramUniform1UI programUniform1ui = nullptr;
		GLProgramUniform1UIV programUniform1uiv = nullptr;
		GLProgramUniform2D programUniform2d = nullptr;
		GLProgramUniform2DV programUniform2dv = nullptr;
		GLProgramUniform2F programUniform2f = nullptr;
		GLProgramUniform2FV programUniform2fv = nullptr;
		GLProgramUniform2I programUniform2i = nullptr;
		GLProgramUniform2IV programUniform2iv = nullptr;
		GLProgramUniform2UI programUniform2ui = nullptr;
		GLProgramUniform2UIV programUniform2uiv = nullptr;
		GLProgramUniform3D programUniform3d = nullptr;
		GLProgramUniform3DV programUniform3dv = nullptr;
		GLProgramUniform3F programUniform3f = nullptr;
		GLProgramUniform3FV programUniform3fv = nullptr;
		GLProgramUniform3I programUniform3i = nullptr;
		GLProgramUniform3IV programUniform3iv = nullptr;
		GLProgramUniform3UI programUniform3ui = nullptr;
		GLProgramUniform3UIV programUniform3uiv = nullptr;
		GLProgramUniform4D programUniform4d = nullptr;
		GLProgramUniform4DV programUniform4dv = nullptr;
		GLProgramUniform4F programUniform4f = nullptr;
		GLProgramUniform4FV programUniform4fv = nullptr;
		GLProgramUniform4I programUniform4i = nullptr;
		GLProgramUniform4IV programUniform4iv = nullptr;
		GLProgramUniform4UI programUniform4ui = nullptr;
		GLProgramUniform4UIV programUniform4uiv = nullptr;
		GLProgramUniformMatrix2DV programUniformMatrix2dv = nullptr;
		GLProgramUniformMatrix2FV programUniformMatrix2fv = nullptr;
		GLProgramUniformMatrix2X3DV programUniformMatrix2x3dv = nullptr;
		GLProgramUniformMatrix2X3FV programUniformMatrix2x3fv = nullptr;
		GLProgramUniformMatrix2X4DV programUniformMatrix2x4dv = nullptr;
		GLProgramUniformMatrix2X4FV programUniformMatrix2x4fv = nullptr;
		GLProgramUniformMatrix3DV programUniformMatrix3dv = nullptr;
		GLProgramUniformMatrix3FV programUniformMatrix3fv = nullptr;
		GLProgramUniformMatrix3X2DV programUniformMatrix3x2dv = nullptr;
		GLProgramUniformMatrix3X2FV programUniformMatrix3x2fv = nullptr;
		GLProgramUniformMatrix3X4DV programUniformMatrix3x4dv = nullptr;
		GLProgramUniformMatrix3X4FV programUniformMatrix3x4fv = nullptr;
		GLProgramUniformMatrix4DV programUniformMatrix4dv = nullptr;
		GLProgramUniformMatrix4FV programUniformMatrix4fv = nullptr;
		GLProgramUniformMatrix4X2DV programUniformMatrix4x2dv = nullptr;
		GLProgramUniformMatrix4X2FV programUniformMatrix4x2fv = nullptr;
		GLProgramUniformMatrix4X3DV programUniformMatrix4x3dv = nullptr;
		GLProgramUniformMatrix4X3FV programUniformMatrix4x3fv = nullptr;
		GLReleaseShaderCompiler releaseShaderCompiler = nullptr;
		GLShaderBinary shaderBinary = nullptr;
		GLScissorArrayV scissorArrayv = nullptr;
		GLScissorIndexed scissorIndexed = nullptr;
		GLScissorIndexedV scissorIndexedv = nullptr;
		GLUseProgramStages useProgramStages = nullptr;
		GLValidateProgramPipeline validateProgramPipeline = nullptr;
		GLVertexAttribL1D vertexAttribL1d = nullptr;
		GLVertexAttribL1DV vertexAttribL1dv = nullptr;
		GLVertexAttribL2D vertexAttribL2d = nullptr;
		GLVertexAttribL2DV vertexAttribL2dv = nullptr;
		GLVertexAttribL3D vertexAttribL3d = nullptr;
		GLVertexAttribL3DV vertexAttribL3dv = nullptr;
		GLVertexAttribL4D vertexAttribL4d = nullptr;
		GLVertexAttribL4DV vertexAttribL4dv = nullptr;
		GLVertexAttribLPointer vertexAttribLPointer = nullptr;
		GLViewportArrayV viewportArrayv = nullptr;
		GLViewportIndexedF viewportIndexedf = nullptr;
		GLViewportIndexedFV viewportIndexedfv = nullptr;


		// Version 4.2

		GLBindImageTexture bindImageTexture = nullptr;
		GLDrawArraysInstancedBaseInstance drawArraysInstancedBaseInstance = nullptr;
		GLDrawElementsInstancedBaseInstance drawElementsInstancedBaseInstance = nullptr;
		GLDrawElementsInstancedBaseVertexBaseInstance drawElementsInstancedBaseVertexBaseInstance = nullptr;
		GLDrawTransformFeedbackInstanced drawTransformFeedbackInstanced = nullptr;
		GLDrawTransformFeedbackStreamInstanced drawTransformFeedbackStreamInstanced = nullptr;
		GLGetActiveAtomicCounterBufferIV getActiveAtomicCounterBufferiv = nullptr;
		GLGetInternalformatIV getInternalformativ = nullptr;
		GLMemoryBarrier memoryBarrier = nullptr;
		GLTexStorage1D texStorage1D = nullptr;
		GLTexStorage2D texStorage2D = nullptr;
		GLTexStorage3D texStorage3D = nullptr;


		// Version 4.3

		GLBindVertexBuffer bindVertexBuffer = nullptr;
		GLClearBufferData clearBufferData = nullptr;
		GLClearBufferSubData clearBufferSubData = nullptr;
		GLCopyImageSubData copyImageSubData = nullptr;
		GLDispatchCompute dispatchCompute = nullptr;
		GLDispatchComputeIndirect dispatchComputeIndirect = nullptr;
		GLDebugMessageCallback debugMessageCallback = nullptr;
		GLDebugMessageControl debugMessageControl = nullptr;
		GLDebugMessageInsert debugMessageInsert = nullptr;
		GLFramebufferParameterI framebufferParameteri = nullptr;
		GLGetDebugMessageLog getDebugMessageLog = nullptr;
		GLGetFramebufferParameterIV getFramebufferParameteriv = nullptr;
		GLGetInternalformatI64V getInternalformati64v = nullptr;
		GLGetObjectLabel getObjectLabel = nullptr;
		GLGetObjectPtrLabel getObjectPtrLabel = nullptr;
		GLGetProgramInterfaceIV getProgramInterfaceiv = nullptr;
		GLGetProgramResourceIndex getProgramResourceIndex = nullptr;
		GLGetProgramResourceIV getProgramResourceiv = nullptr;
		GLGetProgramResourceLocation getProgramResourceLocation = nullptr;
		GLGetProgramResourceLocationIndex getProgramResourceLocationIndex = nullptr;
		GLGetProgramResourceName getProgramResourceName = nullptr;
		GLInvalidateBufferData invalidateBufferData = nullptr;
		GLInvalidateBufferSubData invalidateBufferSubData = nullptr;
		GLInvalidateFramebuffer invalidateFramebuffer = nullptr;
		GLInvalidateSubFramebuffer invalidateSubFramebuffer = nullptr;
		GLInvalidateTexImage invalidateTexImage = nullptr;
		GLInvalidateTexSubImage invalidateTexSubImage = nullptr;
		GLMultiDrawArraysIndirect multiDrawArraysIndirect = nullptr;
		GLMultiDrawElementsIndirect multiDrawElementsIndirect = nullptr;
		GLObjectLabel objectLabel = nullptr;
		GLObjectPtrLabel objectPtrLabel = nullptr;
		GLPopDebugGroup popDebugGroup = nullptr;
		GLPushDebugGroup pushDebugGroup = nullptr;
		GLShaderStorageBlockBinding shaderStorageBlockBinding = nullptr;
		GLTexBufferRange texBufferRange = nullptr;
		GLTexStorage2DMultisample texStorage2DMultisample = nullptr;
		GLTexStorage3DMultisample texStorage3DMultisample = nullptr;
		GLTextureView textureView = nullptr;
		GLVertexAttribBinding vertexAttribBinding = nullptr;
		GLVertexAttribFormat vertexAttribFormat = nullptr;
		GLVertexAttribIFormat vertexAttribIFormat = nullptr;
		GLVertexAttribLFormat vertexAttribLFormat = nullptr;
		GLVertexBindingDivisor vertexBindingDivisor = nullptr;


		// Version 4.4

		GLBindBuffersBase bindBuffersBase = nullptr;
		GLBindBuffersRange bindBuffersRange = nullptr;
		GLBindImageTextures bindImageTextures = nullptr;
		GLBindSamplers bindSamplers = nullptr;
		GLBindTextures bindTextures = nullptr;
		GLBindVertexBuffers bindVertexBuffers = nullptr;
		GLBufferStorage bufferStorage = nullptr;
		GLClearTexImage clearTexImage = nullptr;
		GLClearTexSubImage clearTexSubImage = nullptr;


		// Version 4.5

		GLBindTextureUnit bindTextureUnit = nullptr;
		GLBlitNamedFramebuffer blitNamedFramebuffer = nullptr;
		GLCheckNamedFramebufferStatus checkNamedFramebufferStatus = nullptr;
		GLClearNamedBufferData clearNamedBufferData = nullptr;
		GLClearNamedBufferSubData clearNamedBufferSubData = nullptr;
		GLClearNamedFramebufferFI clearNamedFramebufferfi = nullptr;
		GLClearNamedFramebufferFV clearNamedFramebufferfv = nullptr;
		GLClearNamedFramebufferIV clearNamedFramebufferiv = nullptr;
		GLClearNamedFramebufferUIV clearNamedFramebufferuiv = nullptr;
		GLClipControl clipControl = nullptr;
		GLCompressedTextureSubImage1D compressedTextureSubImage1D = nullptr;
		GLCompressedTextureSubImage2D compressedTextureSubImage2D = nullptr;
		GLCompressedTextureSubImage3D compressedTextureSubImage3D = nullptr;
		GLCopyNamedBufferSubData copyNamedBufferSubData = nullptr;
		GLCopyTextureSubImage1D copyTextureSubImage1D = nullptr;
		GLCopyTextureSubImage2D copyTextureSubImage2D = nullptr;
		GLCopyTextureSubImage3D copyTextureSubImage3D = nullptr;
		GLCreateBuffers createBuffers = nullptr;
		GLCreateFramebuffers createFramebuffers = nullptr;
		GLCreateProgramPipelines createProgramPipelines = nullptr;
		GLCreateQueries createQueries = nullptr;
		GLCreateRenderbuffers createRenderbuffers = nullptr;
		GLCreateSamplers createSamplers = nullptr;
		GLCreateTextures createTextures = nullptr;
		GLCreateTransformFeedbacks createTransformFeedbacks = nullptr;
		GLCreateVertexArrays createVertexArrays = nullptr;
		GLDisableVertexArrayAttrib disableVertexArrayAttrib = nullptr;
		GLEnableVertexArrayAttrib enableVertexArrayAttrib = nullptr;
		GLFlushMappedNamedBufferRange flushMappedNamedBufferRange = nullptr;
		GLGenerateTextureMipmap generateTextureMipmap = nullptr;
		GLGetCompressedTextureImage getCompressedTextureImage = nullptr;
		GLGetCompressedTextureSubImage getCompressedTextureSubImage = nullptr;
		GLGetGraphicsResetStatus getGraphicsResetStatus = nullptr;
		GLGetNamedBufferParameterI64V getNamedBufferParameteri64v = nullptr;
		GLGetNamedBufferParameterIV getNamedBufferParameteriv = nullptr;
		GLGetNamedBufferPointerV getNamedBufferPointerv = nullptr;
		GLGetNamedBufferSubData getNamedBufferSubData = nullptr;
		GLGetNamedFramebufferAttachmentParameterIV getNamedFramebufferAttachmentParameteriv = nullptr;
		GLGetNamedFramebufferParameterIV getNamedFramebufferParameteriv = nullptr;
		GLGetNamedRenderbufferParameterIV getNamedRenderbufferParameteriv = nullptr;
		GLGetnCompressedTexImage getnCompressedTexImage = nullptr;
		GLGetnTexImage getnTexImage = nullptr;
		GLGetnUniformDV getnUniformdv = nullptr;
		GLGetnUniformFV getnUniformfv = nullptr;
		GLGetnUniformIV getnUniformiv = nullptr;
		GLGetnUniformUIV getnUniformuiv = nullptr;
		GLGetQueryBufferObjectI64V getQueryBufferObjecti64v = nullptr;
		GLGetQueryBufferObjectIV getQueryBufferObjectiv = nullptr;
		GLGetQueryBufferObjectUI64V getQueryBufferObjectui64v = nullptr;
		GLGetQueryBufferObjectUIV getQueryBufferObjectuiv = nullptr;
		GLGetTextureImage getTextureImage = nullptr;
		GLGetTextureLevelParameterFV getTextureLevelParameterfv = nullptr;
		GLGetTextureLevelParameterIV getTextureLevelParameteriv = nullptr;
		GLGetTextureParameterFV getTextureParameterfv = nullptr;
		GLGetTextureParameterIIV getTextureParameterIiv = nullptr;
		GLGetTextureParameterIV getTextureParameteriv = nullptr;
		GLGetTextureParameterIUIV getTextureParameterIuiv = nullptr;
		GLGetTextureSubImage getTextureSubImage = nullptr;
		GLGetTransformFeedbackI64_V getTransformFeedbacki64_v = nullptr;
		GLGetTransformFeedbackIV getTransformFeedbackiv = nullptr;
		GLGetTransformFeedbackI_V getTransformFeedbacki_v = nullptr;
		GLGetVertexArrayIndexed64IV getVertexArrayIndexed64iv = nullptr;
		GLGetVertexArrayIndexedIV getVertexArrayIndexediv = nullptr;
		GLGetVertexArrayIV getVertexArrayiv = nullptr;
		GLInvalidateNamedFramebufferData invalidateNamedFramebufferData = nullptr;
		GLInvalidateNamedFramebufferSubData invalidateNamedFramebufferSubData = nullptr;
		GLMapNamedBuffer mapNamedBuffer = nullptr;
		GLMapNamedBufferRange mapNamedBufferRange = nullptr;
		GLMemoryBarrierByRegion memoryBarrierByRegion = nullptr;
		GLNamedBufferData namedBufferData = nullptr;
		GLNamedBufferStorage namedBufferStorage = nullptr;
		GLNamedBufferSubData namedBufferSubData = nullptr;
		GLNamedFramebufferDrawBuffer namedFramebufferDrawBuffer = nullptr;
		GLNamedFramebufferDrawBuffers namedFramebufferDrawBuffers = nullptr;
		GLNamedFramebufferParameterI namedFramebufferParameteri = nullptr;
		GLNamedFramebufferReadBuffer namedFramebufferReadBuffer = nullptr;
		GLNamedFramebufferRenderbuffer namedFramebufferRenderbuffer = nullptr;
		GLNamedFramebufferTexture namedFramebufferTexture = nullptr;
		GLNamedFramebufferTextureLayer namedFramebufferTextureLayer = nullptr;
		GLNamedRenderbufferStorage namedRenderbufferStorage = nullptr;
		GLNamedRenderbufferStorageMultisample namedRenderbufferStorageMultisample = nullptr;
		GLReadnPixels readnPixels = nullptr;
		GLTransformFeedbackBufferBase transformFeedbackBufferBase = nullptr;
		GLTransformFeedbackBufferRange transformFeedbackBufferRange = nullptr;
		GLTextureBarrier textureBarrier = nullptr;
		GLTextureBuffer textureBuffer = nullptr;
		GLTextureBufferRange textureBufferRange = nullptr;
		GLTextureParameterF textureParameterf = nullptr;
		GLTextureParameterFV textureParameterfv = nullptr;
		GLTextureParameterI textureParameteri = nullptr;
		GLTextureParameterIIV textureParameterIiv = nullptr;
		GLTextureParameterIUIV textureParameterIuiv = nullptr;
		GLTextureParameterIV textureParameteriv = nullptr;
		GLTextureStorage1D textureStorage1D = nullptr;
		GLTextureStorage2D textureStorage2D = nullptr;
		GLTextureStorage2DMultisample textureStorage2DMultisample = nullptr;
		GLTextureStorage3D textureStorage3D = nullptr;
		GLTextureStorage3DMultisample textureStorage3DMultisample = nullptr;
		GLTextureSubImage1D textureSubImage1D = nullptr;
		GLTextureSubImage2D textureSubImage2D = nullptr;
		GLTextureSubImage3D textureSubImage3D = nullptr;
		GLUnmapNamedBuffer unmapNamedBuffer = nullptr;
		GLVertexArrayAttribBinding vertexArrayAttribBinding = nullptr;
		GLVertexArrayAttribFormat vertexArrayAttribFormat = nullptr;
		GLVertexArrayAttribIFormat vertexArrayAttribIFormat = nullptr;
		GLVertexArrayAttribLFormat vertexArrayAttribLFormat = nullptr;
		GLVertexArrayBindingDivisor vertexArrayBindingDivisor = nullptr;
		GLVertexArrayElementBuffer vertexArrayElementBuffer = nullptr;
		GLVertexArrayVertexBuffer vertexArrayVertexBuffer = nullptr;
		GLVertexArrayVertexBuffers vertexArrayVertexBuffers = nullptr;

		OpenGL();

		OpenGL(const OpenGL& openGl) = delete;
		OpenGL(OpenGL&& openGl) = delete;

		~OpenGL() = default;

		OpenGL& operator =(const OpenGL& openGl) = delete;
		OpenGL& operator =(OpenGL&& openGl) = delete;

		void checkForErrors(const Char8* file, const Uint32 line, const Char8* function) const;

	private:

		static const Char8* COMPONENT_TAG;
		static const Core::Array<Char8*, 6u> DEBUG_MESSAGE_SOURCE_NAMES;
		static const Core::Array<Char8*, 9u> DEBUG_MESSAGE_TYPE_NAMES;

		void getFunctions();
		void initialiseDebugMessaging() const;
		void reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function) const;

		static void DE_CALL_OPENGL processDebugMessage(const Uint32 messageSource, const Uint32 messageType,
			const Uint32 messageId, const Uint32 messageSeverity, const Int32 messageLength, const Char8* message,
			const Void* userData);

		static Core::LogLevel getDebugMessageLogLevel(const Uint32 messageSeverity);
		static const Char8* getDebugMessageTypeName(const Uint32 messageType);
		static const Char8* getDebugMessageSourceName(const Uint32 messageSource);

		template<typename T>
		static T getFunction(const Char8* functionName);
	};

#include "inline/OpenGLInterface.inl"
}
