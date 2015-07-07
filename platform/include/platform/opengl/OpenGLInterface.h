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
	#define DE_CHECK_ERROR_OPENGL() \
		DE_NO_OPERATION
#else
	#define DE_CHECK_ERROR_OPENGL() \
		Platform::OpenGL::checkForErrors(DE_FILE, DE_LINE, DE_FUNCTION)
#endif

namespace Platform
{
	class OpenGL final
	{
	public:

		// Version 1.0

		static GLBlendFunc blendFunc;
		static GLClear clear;
		static GLClearColor clearColor;
		static GLClearDepth clearDepth;
		static GLClearStencil clearStencil;
		static GLColorMask colorMask;
		static GLCullFace cullFace;
		static GLDepthFunc depthFunc;
		static GLDepthMask depthMask;
		static GLDepthRange depthRange;
		static GLDisable disable;
		static GLDrawBuffer drawBuffer;
		static GLEnable enable;
		static GLFinish finish;
		static GLFlush flush;
		static GLFrontFace frontFace;
		static GLGetBooleanV getBooleanv;
		static GLGetDoubleV getDoublev;
		static GLGetError getError;
		static GLGetFloatV getFloatv;
		static GLGetIntegerV getIntegerv;
		static GLGetString getString;
		static GLGetTexImage getTexImage;
		static GLGetTexLevelParameterFV getTexLevelParameterfv;
		static GLGetTexLevelParameterIV getTexLevelParameteriv;
		static GLGetTexParameterFV getTexParameterfv;
		static GLGetTexParameterIV getTexParameteriv;
		static GLHint hint;
		static GLIsEnabled isEnabled;
		static GLLineWidth lineWidth;
		static GLLogicOp logicOp;
		static GLPixelStoreF pixelStoref;
		static GLPixelStoreI pixelStorei;
		static GLPointSize pointSize;
		static GLPolygonMode polygonMode;
		static GLReadBuffer readBuffer;
		static GLReadPixels readPixels;
		static GLScissor scissor;
		static GLStencilFunc stencilFunc;
		static GLStencilMask stencilMask;
		static GLStencilOp stencilOp;
		static GLTexImage1D texImage1D;
		static GLTexImage2D texImage2D;
		static GLTexParameterF texParameterf;
		static GLTexParameterFV texParameterfv;
		static GLTexParameterI texParameteri;
		static GLTexParameterIV texParameteriv;
		static GLViewport viewport;

		// Version 1.1

		static GLBindTexture bindTexture;
		static GLCopyTexImage1D copyTexImage1D;
		static GLCopyTexImage2D copyTexImage2D;
		static GLCopyTexSubImage1D copyTexSubImage1D;
		static GLCopyTexSubImage2D copyTexSubImage2D;
		static GLDeleteTextures deleteTextures;
		static GLDrawArrays drawArrays;
		static GLDrawElements drawElements;
		static GLGenTextures genTextures;
		static GLGetPointerV getPointerv;
		static GLIsTexture isTexture;
		static GLPolygonOffset polygonOffset;
		static GLTexSubImage1D texSubImage1D;
		static GLTexSubImage2D texSubImage2D;

		// Version 1.2

		static GLCopyTexSubImage3D copyTexSubImage3D;
		static GLDrawRangeElements drawRangeElements;
		static GLTexImage3D texImage3D;
		static GLTexSubImage3D texSubImage3D;

		// Version 1.3

		static GLActiveTexture activeTexture;
		static GLCompressedTexImage1D compressedTexImage1D;
		static GLCompressedTexImage2D compressedTexImage2D;
		static GLCompressedTexImage3D compressedTexImage3D;
		static GLCompressedTexSubImage1D compressedTexSubImage1D;
		static GLCompressedTexSubImage2D compressedTexSubImage2D;
		static GLCompressedTexSubImage3D compressedTexSubImage3D;
		static GLGetCompressedTexImage getCompressedTexImage;
		static GLSampleCoverage sampleCoverage;

		// Version 1.4

		static GLBlendColor blendColor;
		static GLBlendEquation blendEquation;
		static GLBlendFuncSeparate blendFuncSeparate;
		static GLMultiDrawArrays multiDrawArrays;
		static GLMultiDrawElements multiDrawElements;
		static GLPointParameterF pointParameterf;
		static GLPointParameterFV pointParameterfv;
		static GLPointParameterI pointParameteri;
		static GLPointParameterIV pointParameteriv;

		// Version 1.5

		static GLBeginQuery beginQuery;
		static GLBindBuffer bindBuffer;
		static GLBufferData bufferData;
		static GLBufferSubData bufferSubData;
		static GLDeleteBuffers deleteBuffers;
		static GLDeleteQueries deleteQueries;
		static GLEndQuery endQuery;
		static GLGenBuffers genBuffers;
		static GLGenQueries genQueries;
		static GLGetBufferParameterIV getBufferParameteriv;
		static GLGetBufferPointerV getBufferPointerv;
		static GLGetBufferSubData getBufferSubData;
		static GLGetQueryIV getQueryiv;
		static GLGetQueryObjectIV getQueryObjectiv;
		static GLGetQueryObjectUIV getQueryObjectuiv;
		static GLIsBuffer isBuffer;
		static GLIsQuery isQuery;
		static GLMapBuffer mapBuffer;
		static GLUnmapBuffer unmapBuffer;

		// Version 2.0

		static GLAttachShader attachShader;
		static GLBindAttribLocation bindAttribLocation;
		static GLBlendEquationSeparate blendEquationSeparate;
		static GLCompileShader compileShader;
		static GLCreateProgram createProgram;
		static GLCreateShader createShader;
		static GLDeleteProgram deleteProgram;
		static GLDeleteShader deleteShader;
		static GLDetachShader detachShader;
		static GLDisableVertexAttribArray disableVertexAttribArray;
		static GLDrawBuffers drawBuffers;
		static GLEnableVertexAttribArray enableVertexAttribArray;
		static GLGetActiveAttrib getActiveAttrib;
		static GLGetActiveUniform getActiveUniform;
		static GLGetAttachedShaders getAttachedShaders;
		static GLGetAttribLocation getAttribLocation;
		static GLGetProgramInfoLog getProgramInfoLog;
		static GLGetProgramIV getProgramiv;
		static GLGetShaderInfoLog getShaderInfoLog;
		static GLGetShaderIV getShaderiv;
		static GLGetShaderSource getShaderSource;
		static GLGetUniformFV getUniformfv;
		static GLGetUniformIV getUniformiv;
		static GLGetUniformLocation getUniformLocation;
		static GLGetVertexAttribDV getVertexAttribdv;
		static GLGetVertexAttribFV getVertexAttribfv;
		static GLGetVertexAttribIV getVertexAttribiv;
		static GLGetVertexAttribPointerV getVertexAttribPointerv;
		static GLIsProgram isProgram;
		static GLIsShader isShader;
		static GLLinkProgram linkProgram;
		static GLShaderSource shaderSource;
		static GLStencilFuncSeparate stencilFuncSeparate;
		static GLStencilMaskSeparate stencilMaskSeparate;
		static GLStencilOpSeparate stencilOpSeparate;
		static GLUniform1F uniform1f;
		static GLUniform1FV uniform1fv;
		static GLUniform1I uniform1i;
		static GLUniform1IV uniform1iv;
		static GLUniform2F uniform2f;
		static GLUniform2FV uniform2fv;
		static GLUniform2I uniform2i;
		static GLUniform2IV uniform2iv;
		static GLUniform3F uniform3f;
		static GLUniform3FV uniform3fv;
		static GLUniform3I uniform3i;
		static GLUniform3IV uniform3iv;
		static GLUniform4F uniform4f;
		static GLUniform4FV uniform4fv;
		static GLUniform4I uniform4i;
		static GLUniform4IV uniform4iv;
		static GLUniformMatrix2FV uniformMatrix2fv;
		static GLUniformMatrix3FV uniformMatrix3fv;
		static GLUniformMatrix4FV uniformMatrix4fv;
		static GLUseProgram useProgram;
		static GLValidateProgram validateProgram;
		static GLVertexAttrib1D vertexAttrib1d;
		static GLVertexAttrib1DV vertexAttrib1dv;
		static GLVertexAttrib1F vertexAttrib1f;
		static GLVertexAttrib1FV vertexAttrib1fv;
		static GLVertexAttrib1S vertexAttrib1s;
		static GLVertexAttrib1SV vertexAttrib1sv;
		static GLVertexAttrib2D vertexAttrib2d;
		static GLVertexAttrib2DV vertexAttrib2dv;
		static GLVertexAttrib2F vertexAttrib2f;
		static GLVertexAttrib2FV vertexAttrib2fv;
		static GLVertexAttrib2S vertexAttrib2s;
		static GLVertexAttrib2SV vertexAttrib2sv;
		static GLVertexAttrib3D vertexAttrib3d;
		static GLVertexAttrib3DV vertexAttrib3dv;
		static GLVertexAttrib3F vertexAttrib3f;
		static GLVertexAttrib3FV vertexAttrib3fv;
		static GLVertexAttrib3S vertexAttrib3s;
		static GLVertexAttrib3SV vertexAttrib3sv;
		static GLVertexAttrib4BV vertexAttrib4bv;
		static GLVertexAttrib4D vertexAttrib4d;
		static GLVertexAttrib4DV vertexAttrib4dv;
		static GLVertexAttrib4F vertexAttrib4f;
		static GLVertexAttrib4FV vertexAttrib4fv;
		static GLVertexAttrib4IV vertexAttrib4iv;
		static GLVertexAttrib4NBV vertexAttrib4Nbv;
		static GLVertexAttrib4NIV vertexAttrib4Niv;
		static GLVertexAttrib4NSV vertexAttrib4Nsv;
		static GLVertexAttrib4NUB vertexAttrib4Nub;
		static GLVertexAttrib4NUBV vertexAttrib4Nubv;
		static GLVertexAttrib4NUIV vertexAttrib4Nuiv;
		static GLVertexAttrib4NUSV vertexAttrib4Nusv;
		static GLVertexAttrib4S vertexAttrib4s;
		static GLVertexAttrib4SV vertexAttrib4sv;
		static GLVertexAttrib4UBV vertexAttrib4ubv;
		static GLVertexAttrib4UIV vertexAttrib4uiv;
		static GLVertexAttrib4USV vertexAttrib4usv;
		static GLVertexAttribPointer vertexAttribPointer;

		// Version 2.1

		static GLUniformMatrix2X3FV uniformMatrix2x3fv;
		static GLUniformMatrix2X4FV uniformMatrix2x4fv;
		static GLUniformMatrix3X2FV uniformMatrix3x2fv;
		static GLUniformMatrix3X4FV uniformMatrix3x4fv;
		static GLUniformMatrix4X2FV uniformMatrix4x2fv;
		static GLUniformMatrix4X3FV uniformMatrix4x3fv;

		// Version 3.0

		static GLBeginConditionalRender beginConditionalRender;
		static GLBeginTransformFeedback beginTransformFeedback;
		static GLBindBufferBase bindBufferBase;
		static GLBindBufferRange bindBufferRange;
		static GLBindFragDataLocation bindFragDataLocation;
		static GLBindFramebuffer bindFramebuffer;
		static GLBindRenderbuffer bindRenderbuffer;
		static GLBindVertexArray bindVertexArray;
		static GLBlitFramebuffer blitFramebuffer;
		static GLCheckFramebufferStatus checkFramebufferStatus;
		static GLClampColor clampColor;
		static GLClearBufferFI clearBufferfi;
		static GLClearBufferFV clearBufferfv;
		static GLClearBufferIV clearBufferiv;
		static GLClearBufferUIV clearBufferuiv;
		static GLColorMaskI colorMaski;
		static GLDeleteFramebuffers deleteFramebuffers;
		static GLDeleteRenderbuffers deleteRenderbuffers;
		static GLDeleteVertexArrays deleteVertexArrays;
		static GLDisableI disablei;
		static GLEnableI enablei;
		static GLEndConditionalRender endConditionalRender;
		static GLEndTransformFeedback endTransformFeedback;
		static GLFlushMappedBufferRange flushMappedBufferRange;
		static GLFramebufferRenderbuffer framebufferRenderbuffer;
		static GLFramebufferTexture1D framebufferTexture1D;
		static GLFramebufferTexture2D framebufferTexture2D;
		static GLFramebufferTexture3D framebufferTexture3D;
		static GLFramebufferTextureLayer framebufferTextureLayer;
		static GLGenerateMipmap generateMipmap;
		static GLGenFramebuffers genFramebuffers;
		static GLGenRenderbuffers genRenderbuffers;
		static GLGenVertexArrays genVertexArrays;
		static GLGetBooleanI_V getBooleani_v;
		static GLGetFragDataLocation getFragDataLocation;
		static GLGetFramebufferAttachmentParameterIV getFramebufferAttachmentParameteriv;
		static GLGetIntegerI_V getIntegeri_v;
		static GLGetRenderbufferParameterIV getRenderbufferParameteriv;
		static GLGetStringI getStringi;
		static GLGetTexParameterIIV getTexParameterIiv;
		static GLGetTexParameterIUIV getTexParameterIuiv;
		static GLGetTransformFeedbackVarying getTransformFeedbackVarying;
		static GLGetUniformUIV getUniformuiv;
		static GLGetVertexAttribIIV getVertexAttribIiv;
		static GLGetVertexAttribIUIV getVertexAttribIuiv;
		static GLIsEnabledI isEnabledi;
		static GLIsFramebuffer isFramebuffer;
		static GLIsRenderbuffer isRenderbuffer;
		static GLIsVertexArray isVertexArray;
		static GLMapBufferRange mapBufferRange;
		static GLRenderbufferStorage renderbufferStorage;
		static GLRenderbufferStorageMultisample renderbufferStorageMultisample;
		static GLTexParameterIIV texParameterIiv;
		static GLTexParameterIUIV texParameterIuiv;
		static GLTransformFeedbackVaryings transformFeedbackVaryings;
		static GLUniform1UI uniform1ui;
		static GLUniform1UIV uniform1uiv;
		static GLUniform2UI uniform2ui;
		static GLUniform2UIV uniform2uiv;
		static GLUniform3UI uniform3ui;
		static GLUniform3UIV uniform3uiv;
		static GLUniform4UI uniform4ui;
		static GLUniform4UIV uniform4uiv;
		static GLVertexAttribI1I vertexAttribI1i;
		static GLVertexAttribI1IV vertexAttribI1iv;
		static GLVertexAttribI1UI vertexAttribI1ui;
		static GLVertexAttribI1UIV vertexAttribI1uiv;
		static GLVertexAttribI2I vertexAttribI2i;
		static GLVertexAttribI2IV vertexAttribI2iv;
		static GLVertexAttribI2UI vertexAttribI2ui;
		static GLVertexAttribI2UIV vertexAttribI2uiv;
		static GLVertexAttribI3I vertexAttribI3i;
		static GLVertexAttribI3IV vertexAttribI3iv;
		static GLVertexAttribI3UI vertexAttribI3ui;
		static GLVertexAttribI3UIV vertexAttribI3uiv;
		static GLVertexAttribI4BV vertexAttribI4bv;
		static GLVertexAttribI4I vertexAttribI4i;
		static GLVertexAttribI4IV vertexAttribI4iv;
		static GLVertexAttribI4SV vertexAttribI4sv;
		static GLVertexAttribI4UBV vertexAttribI4ubv;
		static GLVertexAttribI4UI vertexAttribI4ui;
		static GLVertexAttribI4UIV vertexAttribI4uiv;
		static GLVertexAttribI4USV vertexAttribI4usv;
		static GLVertexAttribIPointer vertexAttribIPointer;

		// Version 3.1

		static GLCopyBufferSubData copyBufferSubData;
		static GLDrawArraysInstanced drawArraysInstanced;
		static GLDrawElementsInstanced drawElementsInstanced;
		static GLGetActiveUniformBlockIV getActiveUniformBlockiv;
		static GLGetActiveUniformBlockName getActiveUniformBlockName;
		static GLGetActiveUniformName getActiveUniformName;
		static GLGetActiveUniformsIV getActiveUniformsiv;
		static GLGetUniformBlockIndex getUniformBlockIndex;
		static GLGetUniformIndices getUniformIndices;
		static GLPrimitiveRestartIndex primitiveRestartIndex;
		static GLTexBuffer texBuffer;
		static GLUniformBlockBinding uniformBlockBinding;

		// Version 3.2

		static GLClientWaitSync clientWaitSync;
		static GLDeleteSync deleteSync;
		static GLDrawElementsBaseVertex drawElementsBaseVertex;
		static GLDrawElementsInstancedBaseVertex drawElementsInstancedBaseVertex;
		static GLDrawRangeElementsBaseVertex drawRangeElementsBaseVertex;
		static GLFenceSync fenceSync;
		static GLFramebufferTexture framebufferTexture;
		static GLGetBufferParameterI64V getBufferParameteri64v;
		static GLGetInteger64I_V getInteger64i_v;
		static GLGetInteger64V getInteger64v;
		static GLGetMultisampleFV getMultisamplefv;
		static GLGetSyncIV getSynciv;
		static GLIsSync isSync;
		static GLMultiDrawElementsBaseVertex multiDrawElementsBaseVertex;
		static GLProvokingVertex provokingVertex;
		static GLSampleMaskI sampleMaski;
		static GLTexImage2DMultisample texImage2DMultisample;
		static GLTexImage3DMultisample texImage3DMultisample;
		static GLWaitSync waitSync;

		// Version 3.3

		static GLBindFragDataLocationIndexed bindFragDataLocationIndexed;
		static GLBindSampler bindSampler;
		static GLDeleteSamplers deleteSamplers;
		static GLGenSamplers genSamplers;
		static GLGetFragDataIndex getFragDataIndex;
		static GLGetQueryObjectI64V getQueryObjecti64v;
		static GLGetQueryObjectUI64V getQueryObjectui64v;
		static GLGetSamplerParameterFV getSamplerParameterfv;
		static GLGetSamplerParameterIIV getSamplerParameterIiv;
		static GLGetSamplerParameterIUIV getSamplerParameterIuiv;
		static GLGetSamplerParameterIV getSamplerParameteriv;
		static GLIsSampler isSampler;
		static GLQueryCounter queryCounter;
		static GLSamplerParameterF samplerParameterf;
		static GLSamplerParameterFV samplerParameterfv;
		static GLSamplerParameterI samplerParameteri;
		static GLSamplerParameterIV samplerParameteriv;
		static GLSamplerParameterIIV samplerParameterIiv;
		static GLSamplerParameterIUIV samplerParameterIuiv;
		static GLVertexAttribDivisor vertexAttribDivisor;
		static GLVertexAttribP1UI vertexAttribP1ui;
		static GLVertexAttribP1UIV vertexAttribP1uiv;
		static GLVertexAttribP2UI vertexAttribP2ui;
		static GLVertexAttribP2UIV vertexAttribP2uiv;
		static GLVertexAttribP3UI vertexAttribP3ui;
		static GLVertexAttribP3UIV vertexAttribP3uiv;
		static GLVertexAttribP4UI vertexAttribP4ui;
		static GLVertexAttribP4UIV vertexAttribP4uiv;

		// Version 4.0

		static GLBeginQueryIndexed beginQueryIndexed;
		static GLBindTransformFeedback bindTransformFeedback;
		static GLBlendEquationI blendEquationi;
		static GLBlendEquationSeparateI blendEquationSeparatei;
		static GLBlendFuncI blendFunci;
		static GLBlendFuncSeparateI blendFuncSeparatei;
		static GLDeleteTransformFeedbacks deleteTransformFeedbacks;
		static GLDrawArraysIndirect drawArraysIndirect;
		static GLDrawElementsIndirect drawElementsIndirect;
		static GLDrawTransformFeedback drawTransformFeedback;
		static GLDrawTransformFeedbackStream drawTransformFeedbackStream;
		static GLEndQueryIndexed endQueryIndexed;
		static GLGenTransformFeedbacks genTransformFeedbacks;
		static GLGetActiveSubroutineName getActiveSubroutineName;
		static GLGetActiveSubroutineUniformIV getActiveSubroutineUniformiv;
		static GLGetActiveSubroutineUniformName getActiveSubroutineUniformName;
		static GLGetProgramStageIV getProgramStageiv;
		static GLGetQueryIndexedIV getQueryIndexediv;
		static GLGetSubroutineIndex getSubroutineIndex;
		static GLGetSubroutineUniformLocation getSubroutineUniformLocation;
		static GLGetUniformDV getUniformdv;
		static GLGetUniformSubroutineUIV getUniformSubroutineuiv;
		static GLIsTransformFeedback isTransformFeedback;
		static GLMinSampleShading minSampleShading;
		static GLPatchParameterFV patchParameterfv;
		static GLPatchParameterI patchParameteri;
		static GLPauseTransformFeedback pauseTransformFeedback;
		static GLResumeTransformFeedback resumeTransformFeedback;
		static GLUniform1D uniform1d;
		static GLUniform1DV uniform1dv;
		static GLUniform2D uniform2d;
		static GLUniform2DV uniform2dv;
		static GLUniform3D uniform3d;
		static GLUniform3DV uniform3dv;
		static GLUniform4D uniform4d;
		static GLUniform4DV uniform4dv;
		static GLUniformMatrix2DV uniformMatrix2dv;
		static GLUniformMatrix2X3DV uniformMatrix2x3dv;
		static GLUniformMatrix2X4DV uniformMatrix2x4dv;
		static GLUniformMatrix3DV uniformMatrix3dv;
		static GLUniformMatrix3X2DV uniformMatrix3x2dv;
		static GLUniformMatrix3X4DV uniformMatrix3x4dv;
		static GLUniformMatrix4DV uniformMatrix4dv;
		static GLUniformMatrix4X2DV uniformMatrix4x2dv;
		static GLUniformMatrix4X3DV uniformMatrix4x3dv;
		static GLUniformSubroutineSUIV uniformSubroutinesuiv;

		// Version 4.1

		static GLActiveShaderProgram activeShaderProgram;
		static GLBindProgramPipeline bindProgramPipeline;
		static GLClearDepthF clearDepthf;
		static GLCreateShaderProgramV createShaderProgramv;
		static GLDeleteProgramPipelines deleteProgramPipelines;
		static GLDepthRangeArrayV depthRangeArrayv;
		static GLDepthRangeF depthRangef;
		static GLDepthRangeIndexed depthRangeIndexed;
		static GLGenProgramPipelines genProgramPipelines;
		static GLGetDoubleI_V getDoublei_v;
		static GLGetFloatI_V getFloati_v;
		static GLGetProgramBinary getProgramBinary;
		static GLGetProgramPipelineInfoLog getProgramPipelineInfoLog;
		static GLGetProgramPipelineIV getProgramPipelineiv;
		static GLGetShaderPrecisionFormat getShaderPrecisionFormat;
		static GLGetVertexAttribLDV getVertexAttribLdv;
		static GLIsProgramPipeline isProgramPipeline;
		static GLProgramBinary programBinary;
		static GLProgramParameterI programParameteri;
		static GLProgramUniform1D programUniform1d;
		static GLProgramUniform1DV programUniform1dv;
		static GLProgramUniform1F programUniform1f;
		static GLProgramUniform1FV programUniform1fv;
		static GLProgramUniform1I programUniform1i;
		static GLProgramUniform1IV programUniform1iv;
		static GLProgramUniform1UI programUniform1ui;
		static GLProgramUniform1UIV programUniform1uiv;
		static GLProgramUniform2D programUniform2d;
		static GLProgramUniform2DV programUniform2dv;
		static GLProgramUniform2F programUniform2f;
		static GLProgramUniform2FV programUniform2fv;
		static GLProgramUniform2I programUniform2i;
		static GLProgramUniform2IV programUniform2iv;
		static GLProgramUniform2UI programUniform2ui;
		static GLProgramUniform2UIV programUniform2uiv;
		static GLProgramUniform3D programUniform3d;
		static GLProgramUniform3DV programUniform3dv;
		static GLProgramUniform3F programUniform3f;
		static GLProgramUniform3FV programUniform3fv;
		static GLProgramUniform3I programUniform3i;
		static GLProgramUniform3IV programUniform3iv;
		static GLProgramUniform3UI programUniform3ui;
		static GLProgramUniform3UIV programUniform3uiv;
		static GLProgramUniform4D programUniform4d;
		static GLProgramUniform4DV programUniform4dv;
		static GLProgramUniform4F programUniform4f;
		static GLProgramUniform4FV programUniform4fv;
		static GLProgramUniform4I programUniform4i;
		static GLProgramUniform4IV programUniform4iv;
		static GLProgramUniform4UI programUniform4ui;
		static GLProgramUniform4UIV programUniform4uiv;
		static GLProgramUniformMatrix2DV programUniformMatrix2dv;
		static GLProgramUniformMatrix2FV programUniformMatrix2fv;
		static GLProgramUniformMatrix2X3DV programUniformMatrix2x3dv;
		static GLProgramUniformMatrix2X3FV programUniformMatrix2x3fv;
		static GLProgramUniformMatrix2X4DV programUniformMatrix2x4dv;
		static GLProgramUniformMatrix2X4FV programUniformMatrix2x4fv;
		static GLProgramUniformMatrix3DV programUniformMatrix3dv;
		static GLProgramUniformMatrix3FV programUniformMatrix3fv;
		static GLProgramUniformMatrix3X2DV programUniformMatrix3x2dv;
		static GLProgramUniformMatrix3X2FV programUniformMatrix3x2fv;
		static GLProgramUniformMatrix3X4DV programUniformMatrix3x4dv;
		static GLProgramUniformMatrix3X4FV programUniformMatrix3x4fv;
		static GLProgramUniformMatrix4DV programUniformMatrix4dv;
		static GLProgramUniformMatrix4FV programUniformMatrix4fv;
		static GLProgramUniformMatrix4X2DV programUniformMatrix4x2dv;
		static GLProgramUniformMatrix4X2FV programUniformMatrix4x2fv;
		static GLProgramUniformMatrix4X3DV programUniformMatrix4x3dv;
		static GLProgramUniformMatrix4X3FV programUniformMatrix4x3fv;
		static GLReleaseShaderCompiler releaseShaderCompiler;
		static GLShaderBinary shaderBinary;
		static GLScissorArrayV scissorArrayv;
		static GLScissorIndexed scissorIndexed;
		static GLScissorIndexedV scissorIndexedv;
		static GLUseProgramStages useProgramStages;
		static GLValidateProgramPipeline validateProgramPipeline;
		static GLVertexAttribL1D vertexAttribL1d;
		static GLVertexAttribL1DV vertexAttribL1dv;
		static GLVertexAttribL2D vertexAttribL2d;
		static GLVertexAttribL2DV vertexAttribL2dv;
		static GLVertexAttribL3D vertexAttribL3d;
		static GLVertexAttribL3DV vertexAttribL3dv;
		static GLVertexAttribL4D vertexAttribL4d;
		static GLVertexAttribL4DV vertexAttribL4dv;
		static GLVertexAttribLPointer vertexAttribLPointer;
		static GLViewportArrayV viewportArrayv;
		static GLViewportIndexedF viewportIndexedf;
		static GLViewportIndexedFV viewportIndexedfv;

		// Version 4.2

		static GLBindImageTexture bindImageTexture;
		static GLDrawArraysInstancedBaseInstance drawArraysInstancedBaseInstance;
		static GLDrawElementsInstancedBaseInstance drawElementsInstancedBaseInstance;
		static GLDrawElementsInstancedBaseVertexBaseInstance drawElementsInstancedBaseVertexBaseInstance;
		static GLDrawTransformFeedbackInstanced drawTransformFeedbackInstanced;
		static GLDrawTransformFeedbackStreamInstanced drawTransformFeedbackStreamInstanced;
		static GLGetActiveAtomicCounterBufferIV getActiveAtomicCounterBufferiv;
		static GLGetInternalformatIV getInternalformativ;
		static GLMemoryBarrier memoryBarrier;
		static GLTexStorage1D texStorage1D;
		static GLTexStorage2D texStorage2D;
		static GLTexStorage3D texStorage3D;

		// Version 4.3

		static GLBindVertexBuffer bindVertexBuffer;
		static GLClearBufferData clearBufferData;
		static GLClearBufferSubData clearBufferSubData;
		static GLCopyImageSubData copyImageSubData;
		static GLDispatchCompute dispatchCompute;
		static GLDispatchComputeIndirect dispatchComputeIndirect;
		static GLDebugMessageCallback debugMessageCallback;
		static GLDebugMessageControl debugMessageControl;
		static GLDebugMessageInsert debugMessageInsert;
		static GLFramebufferParameterI framebufferParameteri;
		static GLGetDebugMessageLog getDebugMessageLog;
		static GLGetFramebufferParameterIV getFramebufferParameteriv;
		static GLGetInternalformatI64V getInternalformati64v;
		static GLGetObjectLabel getObjectLabel;
		static GLGetObjectPtrLabel getObjectPtrLabel;
		static GLGetProgramInterfaceIV getProgramInterfaceiv;
		static GLGetProgramResourceIndex getProgramResourceIndex;
		static GLGetProgramResourceIV getProgramResourceiv;
		static GLGetProgramResourceLocation getProgramResourceLocation;
		static GLGetProgramResourceLocationIndex getProgramResourceLocationIndex;
		static GLGetProgramResourceName getProgramResourceName;
		static GLInvalidateBufferData invalidateBufferData;
		static GLInvalidateBufferSubData invalidateBufferSubData;
		static GLInvalidateFramebuffer invalidateFramebuffer;
		static GLInvalidateSubFramebuffer invalidateSubFramebuffer;
		static GLInvalidateTexImage invalidateTexImage;
		static GLInvalidateTexSubImage invalidateTexSubImage;
		static GLMultiDrawArraysIndirect multiDrawArraysIndirect;
		static GLMultiDrawElementsIndirect multiDrawElementsIndirect;
		static GLObjectLabel objectLabel;
		static GLObjectPtrLabel objectPtrLabel;
		static GLPopDebugGroup popDebugGroup;
		static GLPushDebugGroup pushDebugGroup;
		static GLShaderStorageBlockBinding shaderStorageBlockBinding;
		static GLTexBufferRange texBufferRange;
		static GLTexStorage2DMultisample texStorage2DMultisample;
		static GLTexStorage3DMultisample texStorage3DMultisample;
		static GLTextureView textureView;
		static GLVertexAttribBinding vertexAttribBinding;
		static GLVertexAttribFormat vertexAttribFormat;
		static GLVertexAttribIFormat vertexAttribIFormat;
		static GLVertexAttribLFormat vertexAttribLFormat;
		static GLVertexBindingDivisor vertexBindingDivisor;

		// Version 4.4

		static GLBindBuffersBase bindBuffersBase;
		static GLBindBuffersRange bindBuffersRange;
		static GLBindImageTextures bindImageTextures;
		static GLBindSamplers bindSamplers;
		static GLBindTextures bindTextures;
		static GLBindVertexBuffers bindVertexBuffers;
		static GLBufferStorage bufferStorage;
		static GLClearTexImage clearTexImage;
		static GLClearTexSubImage clearTexSubImage;

		// Version 4.5

		static GLBindTextureUnit bindTextureUnit;
		static GLBlitNamedFramebuffer blitNamedFramebuffer;
		static GLCheckNamedFramebufferStatus checkNamedFramebufferStatus;
		static GLClearNamedBufferData clearNamedBufferData;
		static GLClearNamedBufferSubData clearNamedBufferSubData;
		static GLClearNamedFramebufferFI clearNamedFramebufferfi;
		static GLClearNamedFramebufferFV clearNamedFramebufferfv;
		static GLClearNamedFramebufferIV clearNamedFramebufferiv;
		static GLClearNamedFramebufferUIV clearNamedFramebufferuiv;
		static GLClipControl clipControl;
		static GLCompressedTextureSubImage1D compressedTextureSubImage1D;
		static GLCompressedTextureSubImage2D compressedTextureSubImage2D;
		static GLCompressedTextureSubImage3D compressedTextureSubImage3D;
		static GLCopyNamedBufferSubData copyNamedBufferSubData;
		static GLCopyTextureSubImage1D copyTextureSubImage1D;
		static GLCopyTextureSubImage2D copyTextureSubImage2D;
		static GLCopyTextureSubImage3D copyTextureSubImage3D;
		static GLCreateBuffers createBuffers;
		static GLCreateFramebuffers createFramebuffers;
		static GLCreateProgramPipelines createProgramPipelines;
		static GLCreateQueries createQueries;
		static GLCreateRenderbuffers createRenderbuffers;
		static GLCreateSamplers createSamplers;
		static GLCreateTextures createTextures;
		static GLCreateTransformFeedbacks createTransformFeedbacks;
		static GLCreateVertexArrays createVertexArrays;
		static GLDisableVertexArrayAttrib disableVertexArrayAttrib;
		static GLEnableVertexArrayAttrib enableVertexArrayAttrib;
		static GLFlushMappedNamedBufferRange flushMappedNamedBufferRange;
		static GLGenerateTextureMipmap generateTextureMipmap;
		static GLGetCompressedTextureImage getCompressedTextureImage;
		static GLGetCompressedTextureSubImage getCompressedTextureSubImage;
		static GLGetGraphicsResetStatus getGraphicsResetStatus;
		static GLGetNamedBufferParameterI64V getNamedBufferParameteri64v;
		static GLGetNamedBufferParameterIV getNamedBufferParameteriv;
		static GLGetNamedBufferPointerV getNamedBufferPointerv;
		static GLGetNamedBufferSubData getNamedBufferSubData;
		static GLGetNamedFramebufferAttachmentParameterIV getNamedFramebufferAttachmentParameteriv;
		static GLGetNamedFramebufferParameterIV getNamedFramebufferParameteriv;
		static GLGetNamedRenderbufferParameterIV getNamedRenderbufferParameteriv;
		static GLGetnCompressedTexImage getnCompressedTexImage;
		static GLGetnTexImage getnTexImage;
		static GLGetnUniformDV getnUniformdv;
		static GLGetnUniformFV getnUniformfv;
		static GLGetnUniformIV getnUniformiv;
		static GLGetnUniformUIV getnUniformuiv;
		static GLGetQueryBufferObjectI64V getQueryBufferObjecti64v;
		static GLGetQueryBufferObjectIV getQueryBufferObjectiv;
		static GLGetQueryBufferObjectUI64V getQueryBufferObjectui64v;
		static GLGetQueryBufferObjectUIV getQueryBufferObjectuiv;
		static GLGetTextureImage getTextureImage;
		static GLGetTextureLevelParameterFV getTextureLevelParameterfv;
		static GLGetTextureLevelParameterIV getTextureLevelParameteriv;
		static GLGetTextureParameterFV getTextureParameterfv;
		static GLGetTextureParameterIIV getTextureParameterIiv;
		static GLGetTextureParameterIV getTextureParameteriv;
		static GLGetTextureParameterIUIV getTextureParameterIuiv;
		static GLGetTextureSubImage getTextureSubImage;
		static GLGetTransformFeedbackI64_V getTransformFeedbacki64_v;
		static GLGetTransformFeedbackIV getTransformFeedbackiv;
		static GLGetTransformFeedbackI_V getTransformFeedbacki_v;
		static GLGetVertexArrayIndexed64IV getVertexArrayIndexed64iv;
		static GLGetVertexArrayIndexedIV getVertexArrayIndexediv;
		static GLGetVertexArrayIV getVertexArrayiv;
		static GLInvalidateNamedFramebufferData invalidateNamedFramebufferData;
		static GLInvalidateNamedFramebufferSubData invalidateNamedFramebufferSubData;
		static GLMapNamedBuffer mapNamedBuffer;
		static GLMapNamedBufferRange mapNamedBufferRange;
		static GLMemoryBarrierByRegion memoryBarrierByRegion;
		static GLNamedBufferData namedBufferData;
		static GLNamedBufferStorage namedBufferStorage;
		static GLNamedBufferSubData namedBufferSubData;
		static GLNamedFramebufferDrawBuffer namedFramebufferDrawBuffer;
		static GLNamedFramebufferDrawBuffers namedFramebufferDrawBuffers;
		static GLNamedFramebufferParameterI namedFramebufferParameteri;
		static GLNamedFramebufferReadBuffer namedFramebufferReadBuffer;
		static GLNamedFramebufferRenderbuffer namedFramebufferRenderbuffer;
		static GLNamedFramebufferTexture namedFramebufferTexture;
		static GLNamedFramebufferTextureLayer namedFramebufferTextureLayer;
		static GLNamedRenderbufferStorage namedRenderbufferStorage;
		static GLNamedRenderbufferStorageMultisample namedRenderbufferStorageMultisample;
		static GLReadnPixels readnPixels;
		static GLTransformFeedbackBufferBase transformFeedbackBufferBase;
		static GLTransformFeedbackBufferRange transformFeedbackBufferRange;
		static GLTextureBarrier textureBarrier;
		static GLTextureBuffer textureBuffer;
		static GLTextureBufferRange textureBufferRange;
		static GLTextureParameterF textureParameterf;
		static GLTextureParameterFV textureParameterfv;
		static GLTextureParameterI textureParameteri;
		static GLTextureParameterIIV textureParameterIiv;
		static GLTextureParameterIUIV textureParameterIuiv;
		static GLTextureParameterIV textureParameteriv;
		static GLTextureStorage1D textureStorage1D;
		static GLTextureStorage2D textureStorage2D;
		static GLTextureStorage2DMultisample textureStorage2DMultisample;
		static GLTextureStorage3D textureStorage3D;
		static GLTextureStorage3DMultisample textureStorage3DMultisample;
		static GLTextureSubImage1D textureSubImage1D;
		static GLTextureSubImage2D textureSubImage2D;
		static GLTextureSubImage3D textureSubImage3D;
		static GLUnmapNamedBuffer unmapNamedBuffer;
		static GLVertexArrayAttribBinding vertexArrayAttribBinding;
		static GLVertexArrayAttribFormat vertexArrayAttribFormat;
		static GLVertexArrayAttribIFormat vertexArrayAttribIFormat;
		static GLVertexArrayAttribLFormat vertexArrayAttribLFormat;
		static GLVertexArrayBindingDivisor vertexArrayBindingDivisor;
		static GLVertexArrayElementBuffer vertexArrayElementBuffer;
		static GLVertexArrayVertexBuffer vertexArrayVertexBuffer;
		static GLVertexArrayVertexBuffers vertexArrayVertexBuffers;

		OpenGL() = delete;

		OpenGL(const OpenGL& openGl) = delete;
		OpenGL(OpenGL&& openGl) = delete;

		~OpenGL() = delete;

		OpenGL& operator =(const OpenGL& openGl) = delete;
		OpenGL& operator =(OpenGL&& openGl) = delete;

		static void checkForErrors(const Char8* file, const Uint32 line, const Char8* function);

		static void initialise();

	private:

		static const Char8* COMPONENT_TAG;
		static const Core::Array<Char8*, 6u> DEBUG_MESSAGE_SOURCE_NAMES;
		static const Core::Array<Char8*, 9u> DEBUG_MESSAGE_TYPE_NAMES;

		static void reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function);
		static void getFunctions();
		static void initialiseDebugMessaging();

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
