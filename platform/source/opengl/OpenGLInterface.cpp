/**
 * @file platform/opengl/OpenGLInterface.cpp
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

#include <platform/opengl/OpenGLInterface.h>

using namespace Platform;

// Public

OpenGL::OpenGL()
{
	getFunctions();
}

// Private

const Char8* OpenGL::COMPONENT_TAG = "[Platform::OpenGL]";

void OpenGL::getFunctions()
{
	// Version 1.0

	blendFunc = glBlendFunc;
	clear = glClear;
	clearColor = glClearColor;
	clearDepth = glClearDepth;
	clearStencil = glClearStencil;
	colorMask = glColorMask;
	cullFace = glCullFace;
	depthFunc = glDepthFunc;
	depthMask = glDepthMask;
	depthRange = glDepthRange;
	disable = glDisable;
	drawBuffer = glDrawBuffer;
	enable = glEnable;
	finish = glFinish;
	flush = glFlush;
	frontFace = glFrontFace;
	getBooleanv = glGetBooleanv;
	getDoublev = glGetDoublev;
	getError = glGetError;
	getFloatv = glGetFloatv;
	getIntegerv = glGetIntegerv;
	getString = glGetString;
	getTexImage = glGetTexImage;
	getTexLevelParameterfv = glGetTexLevelParameterfv;
	getTexLevelParameteriv = glGetTexLevelParameteriv;
	getTexParameterfv = glGetTexParameterfv;
	getTexParameteriv = glGetTexParameteriv;
	hint = glHint;
	isEnabled = glIsEnabled;
	lineWidth = glLineWidth;
	logicOp = glLogicOp;
	pixelStoref = glPixelStoref;
	pixelStorei = glPixelStorei;
	pointSize = glPointSize;
	polygonMode = glPolygonMode;
	readBuffer = glReadBuffer;
	readPixels = glReadPixels;
	scissor = glScissor;
	stencilFunc = glStencilFunc;
	stencilMask = glStencilMask;
	stencilOp = glStencilOp;
	texImage1D = glTexImage1D;
	texImage2D = glTexImage2D;
	texParameterf = glTexParameterf;
	texParameterfv = glTexParameterfv;
	texParameteri = glTexParameteri;
	texParameteriv = glTexParameteriv;
	viewport = glViewport;


	// Version 1.1

	bindTexture = glBindTexture;
	copyTexImage1D = glCopyTexImage1D;
	copyTexImage2D = glCopyTexImage2D;
	copyTexSubImage1D = glCopyTexSubImage1D;
	copyTexSubImage2D = glCopyTexSubImage2D;
	deleteTextures = glDeleteTextures;
	drawArrays = glDrawArrays;
	drawElements = glDrawElements;
	genTextures = glGenTextures;
	getPointerv = glGetPointerv;
	isTexture = glIsTexture;
	polygonOffset = glPolygonOffset;
	texSubImage1D = glTexSubImage1D;
	texSubImage2D = glTexSubImage2D;


	// Version 1.2

	copyTexSubImage3D = getFunction<GLCopyTexSubImage3D>("glCopyTexSubImage3D");
	drawRangeElements = getFunction<GLDrawRangeElements>("glDrawRangeElements");
	texImage3D = getFunction<GLTexImage3D>("glTexImage3D");
	texSubImage3D = getFunction<GLTexSubImage3D>("glTexSubImage3D");
	  
	  
	// Version 1.3
	  
	activeTexture = getFunction<GLActiveTexture>("glActiveTexture");
	compressedTexImage1D = getFunction<GLCompressedTexImage1D>("glCompressedTexImage1D");
	compressedTexImage2D = getFunction<GLCompressedTexImage2D>("glCompressedTexImage2D");
	compressedTexImage3D = getFunction<GLCompressedTexImage3D>("glCompressedTexImage3D");
	compressedTexSubImage1D = getFunction<GLCompressedTexSubImage1D>("glCompressedTexSubImage1D");
	compressedTexSubImage2D = getFunction<GLCompressedTexSubImage2D>("glCompressedTexSubImage2D");
	compressedTexSubImage3D = getFunction<GLCompressedTexSubImage3D>("glCompressedTexSubImage3D");
	getCompressedTexImage = getFunction<GLGetCompressedTexImage>("glGetCompressedTexImage");
	sampleCoverage = getFunction<GLSampleCoverage>("glSampleCoverage");
	  
	  
	// Version 1.4
	  
	blendColor = getFunction<GLBlendColor>("glBlendColor");
	blendEquation = getFunction<GLBlendEquation>("glBlendEquation");
	blendFuncSeparate = getFunction<GLBlendFuncSeparate>("glBlendFuncSeparate");
	multiDrawArrays = getFunction<GLMultiDrawArrays>("glMultiDrawArrays");
	multiDrawElements = getFunction<GLMultiDrawElements>("glMultiDrawElements");
	pointParameterf = getFunction<GLPointParameterF>("glPointParameterf");
	pointParameterfv = getFunction<GLPointParameterFV>("glPointParameterfv");
	pointParameteri = getFunction<GLPointParameterI>("glPointParameteri");
	pointParameteriv = getFunction<GLPointParameterIV>("glPointParameteriv");
	  
	  
	// Version 1.5
	  
	beginQuery = getFunction<GLBeginQuery>("glBeginQuery");
	bindBuffer = getFunction<GLBindBuffer>("glBindBuffer");
	bufferData = getFunction<GLBufferData>("glBufferData");
	bufferSubData = getFunction<GLBufferSubData>("glBufferSubData");
	deleteBuffers = getFunction<GLDeleteBuffers>("glDeleteBuffers");
	deleteQueries = getFunction<GLDeleteQueries>("glDeleteQueries");
	endQuery = getFunction<GLEndQuery>("glEndQuery");
	genBuffers = getFunction<GLGenBuffers>("glGenBuffers");
	genQueries = getFunction<GLGenQueries>("glGenQueries");
	getBufferParameteriv = getFunction<GLGetBufferParameterIV>("glGetBufferParameteriv");
	getBufferPointerv = getFunction<GLGetBufferPointerV>("glGetBufferPointerv");
	getBufferSubData = getFunction<GLGetBufferSubData>("glGetBufferSubData");
	getQueryiv = getFunction<GLGetQueryIV>("glGetQueryiv");
	getQueryObjectiv = getFunction<GLGetQueryObjectIV>("glGetQueryObjectiv");
	getQueryObjectuiv = getFunction<GLGetQueryObjectUIV>("glGetQueryObjectuiv");
	isBuffer = getFunction<GLIsBuffer>("glIsBuffer");
	isQuery = getFunction<GLIsQuery>("glIsQuery");
	mapBuffer = getFunction<GLMapBuffer>("glMapBuffer");
	unmapBuffer = getFunction<GLUnmapBuffer>("glUnmapBuffer");
	  
	  
	// Version 2.0
	  
	attachShader = getFunction<GLAttachShader>("glAttachShader");
	bindAttribLocation = getFunction<GLBindAttribLocation>("glBindAttribLocation");
	blendEquationSeparate = getFunction<GLBlendEquationSeparate>("glBlendEquationSeparate");
	compileShader = getFunction<GLCompileShader>("glCompileShader");
	createProgram = getFunction<GLCreateProgram>("glCreateProgram");
	createShader = getFunction<GLCreateShader>("glCreateShader");
	deleteProgram = getFunction<GLDeleteProgram>("glDeleteProgram");
	deleteShader = getFunction<GLDeleteShader>("glDeleteShader");
	detachShader = getFunction<GLDetachShader>("glDetachShader");
	disableVertexAttribArray = getFunction<GLDisableVertexAttribArray>("glDisableVertexAttribArray");
	drawBuffers = getFunction<GLDrawBuffers>("glDrawBuffers");
	enableVertexAttribArray = getFunction<GLEnableVertexAttribArray>("glEnableVertexAttribArray");
	getActiveAttrib = getFunction<GLGetActiveAttrib>("glGetActiveAttrib");
	getActiveUniform = getFunction<GLGetActiveUniform>("glGetActiveUniform");
	getAttachedShaders = getFunction<GLGetAttachedShaders>("glGetAttachedShaders");
	getAttribLocation = getFunction<GLGetAttribLocation>("glGetAttribLocation");
	getProgramInfoLog = getFunction<GLGetProgramInfoLog>("glGetProgramInfoLog");
	getProgramiv = getFunction<GLGetProgramIV>("glGetProgramiv");
	getShaderInfoLog = getFunction<GLGetShaderInfoLog>("glGetShaderInfoLog");
	getShaderiv = getFunction<GLGetShaderIV>("glGetShaderiv");
	getShaderSource = getFunction<GLGetShaderSource>("glGetShaderSource");
	getUniformfv = getFunction<GLGetUniformFV>("glGetUniformfv");
	getUniformiv = getFunction<GLGetUniformIV>("glGetUniformiv");
	getUniformLocation = getFunction<GLGetUniformLocation>("glGetUniformLocation");
	getVertexAttribdv = getFunction<GLGetVertexAttribDV>("glGetVertexAttribdv");
	getVertexAttribfv = getFunction<GLGetVertexAttribFV>("glGetVertexAttribfv");
	getVertexAttribiv = getFunction<GLGetVertexAttribIV>("glGetVertexAttribiv");
	getVertexAttribPointerv = getFunction<GLGetVertexAttribPointerV>("glGetVertexAttribPointerv");
	isProgram = getFunction<GLIsProgram>("glIsProgram");
	isShader = getFunction<GLIsShader>("glIsShader");
	linkProgram = getFunction<GLLinkProgram>("glLinkProgram");
	shaderSource = getFunction<GLShaderSource>("glShaderSource");
	stencilFuncSeparate = getFunction<GLStencilFuncSeparate>("glStencilFuncSeparate");
	stencilMaskSeparate = getFunction<GLStencilMaskSeparate>("glStencilMaskSeparate");
	stencilOpSeparate = getFunction<GLStencilOpSeparate>("glStencilOpSeparate");
	uniform1f = getFunction<GLUniform1F>("glUniform1f");
	uniform1fv = getFunction<GLUniform1FV>("glUniform1fv");
	uniform1i = getFunction<GLUniform1I>("glUniform1i");
	uniform1iv = getFunction<GLUniform1IV>("glUniform1iv");
	uniform2f = getFunction<GLUniform2F>("glUniform2f");
	uniform2fv = getFunction<GLUniform2FV>("glUniform2fv");
	uniform2i = getFunction<GLUniform2I>("glUniform2i");
	uniform2iv = getFunction<GLUniform2IV>("glUniform2iv");
	uniform3f = getFunction<GLUniform3F>("glUniform3f");
	uniform3fv = getFunction<GLUniform3FV>("glUniform3fv");
	uniform3i = getFunction<GLUniform3I>("glUniform3i");
	uniform3iv = getFunction<GLUniform3IV>("glUniform3iv");
	uniform4f = getFunction<GLUniform4F>("glUniform4f");
	uniform4fv = getFunction<GLUniform4FV>("glUniform4fv");
	uniform4i = getFunction<GLUniform4I>("glUniform4i");
	uniform4iv = getFunction<GLUniform4IV>("glUniform4iv");
	uniformMatrix2fv = getFunction<GLUniformMatrix2FV>("glUniformMatrix2fv");
	uniformMatrix3fv = getFunction<GLUniformMatrix3FV>("glUniformMatrix3fv");
	uniformMatrix4fv = getFunction<GLUniformMatrix4FV>("glUniformMatrix4fv");
	useProgram = getFunction<GLUseProgram>("glUseProgram");
	validateProgram = getFunction<GLValidateProgram>("glValidateProgram");
	vertexAttrib1d = getFunction<GLVertexAttrib1D>("glVertexAttrib1d");
	vertexAttrib1dv = getFunction<GLVertexAttrib1DV>("glVertexAttrib1dv");
	vertexAttrib1f = getFunction<GLVertexAttrib1F>("glVertexAttrib1f");
	vertexAttrib1fv = getFunction<GLVertexAttrib1FV>("glVertexAttrib1fv");
	vertexAttrib1s = getFunction<GLVertexAttrib1S>("glVertexAttrib1s");
	vertexAttrib1sv = getFunction<GLVertexAttrib1SV>("glVertexAttrib1sv");
	vertexAttrib2d = getFunction<GLVertexAttrib2D>("glVertexAttrib2d");
	vertexAttrib2dv = getFunction<GLVertexAttrib2DV>("glVertexAttrib2dv");
	vertexAttrib2f = getFunction<GLVertexAttrib2F>("glVertexAttrib2f");
	vertexAttrib2fv = getFunction<GLVertexAttrib2FV>("glVertexAttrib2fv");
	vertexAttrib2s = getFunction<GLVertexAttrib2S>("glVertexAttrib2s");
	vertexAttrib2sv = getFunction<GLVertexAttrib2SV>("glVertexAttrib2sv");
	vertexAttrib3d = getFunction<GLVertexAttrib3D>("glVertexAttrib3d");
	vertexAttrib3dv = getFunction<GLVertexAttrib3DV>("glVertexAttrib3dv");
	vertexAttrib3f = getFunction<GLVertexAttrib3F>("glVertexAttrib3f");
	vertexAttrib3fv = getFunction<GLVertexAttrib3FV>("glVertexAttrib3fv");
	vertexAttrib3s = getFunction<GLVertexAttrib3S>("glVertexAttrib3s");
	vertexAttrib3sv = getFunction<GLVertexAttrib3SV>("glVertexAttrib3sv");
	vertexAttrib4bv = getFunction<GLVertexAttrib4BV>("glVertexAttrib4bv");
	vertexAttrib4d = getFunction<GLVertexAttrib4D>("glVertexAttrib4d");
	vertexAttrib4dv = getFunction<GLVertexAttrib4DV>("glVertexAttrib4dv");
	vertexAttrib4f = getFunction<GLVertexAttrib4F>("glVertexAttrib4f");
	vertexAttrib4fv = getFunction<GLVertexAttrib4FV>("glVertexAttrib4fv");
	vertexAttrib4iv = getFunction<GLVertexAttrib4IV>("glVertexAttrib4iv");
	vertexAttrib4Nbv = getFunction<GLVertexAttrib4NBV>("glVertexAttrib4Nbv");
	vertexAttrib4Niv = getFunction<GLVertexAttrib4NIV>("glVertexAttrib4Niv");
	vertexAttrib4Nsv = getFunction<GLVertexAttrib4NSV>("glVertexAttrib4Nsv");
	vertexAttrib4Nub = getFunction<GLVertexAttrib4NUB>("glVertexAttrib4Nub");
	vertexAttrib4Nubv = getFunction<GLVertexAttrib4NUBV>("glVertexAttrib4Nubv");
	vertexAttrib4Nuiv = getFunction<GLVertexAttrib4NUIV>("glVertexAttrib4Nuiv");
	vertexAttrib4Nusv = getFunction<GLVertexAttrib4NUSV>("glVertexAttrib4Nusv");
	vertexAttrib4s = getFunction<GLVertexAttrib4S>("glVertexAttrib4s");
	vertexAttrib4sv = getFunction<GLVertexAttrib4SV>("glVertexAttrib4sv");
	vertexAttrib4ubv = getFunction<GLVertexAttrib4UBV>("glVertexAttrib4ubv");
	vertexAttrib4uiv = getFunction<GLVertexAttrib4UIV>("glVertexAttrib4uiv");
	vertexAttrib4usv = getFunction<GLVertexAttrib4USV>("glVertexAttrib4usv");
	vertexAttribPointer = getFunction<GLVertexAttribPointer>("glVertexAttribPointer");
	  
	  
	// Version 2.1
	  
	uniformMatrix2x3fv = getFunction<GLUniformMatrix2X3FV>("glUniformMatrix2x3fv");
	uniformMatrix2x4fv = getFunction<GLUniformMatrix2X4FV>("glUniformMatrix2x4fv");
	uniformMatrix3x2fv = getFunction<GLUniformMatrix3X2FV>("glUniformMatrix3x2fv");
	uniformMatrix3x4fv = getFunction<GLUniformMatrix3X4FV>("glUniformMatrix3x4fv");
	uniformMatrix4x2fv = getFunction<GLUniformMatrix4X2FV>("glUniformMatrix4x2fv");
	uniformMatrix4x3fv = getFunction<GLUniformMatrix4X3FV>("glUniformMatrix4x3fv");
	  
	  
	// Version 3.0
	  
	beginConditionalRender = getFunction<GLBeginConditionalRender>("glBeginConditionalRender");
	beginTransformFeedback = getFunction<GLBeginTransformFeedback>("glBeginTransformFeedback");
	bindBufferBase = getFunction<GLBindBufferBase>("glBindBufferBase");
	bindBufferRange = getFunction<GLBindBufferRange>("glBindBufferRange");
	bindFragDataLocation = getFunction<GLBindFragDataLocation>("glBindFragDataLocation");
	bindFramebuffer = getFunction<GLBindFramebuffer>("glBindFramebuffer");
	bindRenderbuffer = getFunction<GLBindRenderbuffer>("glBindRenderbuffer");
	bindVertexArray = getFunction<GLBindVertexArray>("glBindVertexArray");
	blitFramebuffer = getFunction<GLBlitFramebuffer>("glBlitFramebuffer");
	checkFramebufferStatus = getFunction<GLCheckFramebufferStatus>("glCheckFramebufferStatus");
	clampColor = getFunction<GLClampColor>("glClampColor");
	clearBufferfi = getFunction<GLClearBufferFI>("glClearBufferfi");
	clearBufferfv = getFunction<GLClearBufferFV>("glClearBufferfv");
	clearBufferiv = getFunction<GLClearBufferIV>("glClearBufferiv");
	clearBufferuiv = getFunction<GLClearBufferUIV>("glClearBufferuiv");
	colorMaski = getFunction<GLColorMaskI>("glColorMaski");
	deleteFramebuffers = getFunction<GLDeleteFramebuffers>("glDeleteFramebuffers");
	deleteRenderbuffers = getFunction<GLDeleteRenderbuffers>("glDeleteRenderbuffers");
	deleteVertexArrays = getFunction<GLDeleteVertexArrays>("glDeleteVertexArrays");
	disablei = getFunction<GLDisableI>("glDisablei");
	enablei = getFunction<GLEnableI>("glEnablei");
	endConditionalRender = getFunction<GLEndConditionalRender>("glEndConditionalRender");
	endTransformFeedback = getFunction<GLEndTransformFeedback>("glEndTransformFeedback");
	flushMappedBufferRange = getFunction<GLFlushMappedBufferRange>("glFlushMappedBufferRange");
	framebufferRenderbuffer = getFunction<GLFramebufferRenderbuffer>("glFramebufferRenderbuffer");
	framebufferTexture1D = getFunction<GLFramebufferTexture1D>("glFramebufferTexture1D");
	framebufferTexture2D = getFunction<GLFramebufferTexture2D>("glFramebufferTexture2D");
	framebufferTexture3D = getFunction<GLFramebufferTexture3D>("glFramebufferTexture3D");
	framebufferTextureLayer = getFunction<GLFramebufferTextureLayer>("glFramebufferTextureLayer");
	generateMipmap = getFunction<GLGenerateMipmap>("glGenerateMipmap");
	genFramebuffers = getFunction<GLGenFramebuffers>("glGenFramebuffers");
	genRenderbuffers = getFunction<GLGenRenderbuffers>("glGenRenderbuffers");
	genVertexArrays = getFunction<GLGenVertexArrays>("glGenVertexArrays");
	getBooleani_v = getFunction<GLGetBooleanI_V>("glGetBooleani_v");
	getFragDataLocation = getFunction<GLGetFragDataLocation>("glGetFragDataLocation");

	getFramebufferAttachmentParameteriv = getFunction<GLGetFramebufferAttachmentParameterIV>(
		"glGetFramebufferAttachmentParameteriv");

	getIntegeri_v = getFunction<GLGetIntegerI_V>("glGetIntegeri_v");
	getRenderbufferParameteriv = getFunction<GLGetRenderbufferParameterIV>("glGetRenderbufferParameteriv");
	getStringi = getFunction<GLGetStringI>("glGetStringi");
	getTexParameterIiv = getFunction<GLGetTexParameterIIV>("glGetTexParameterIiv");
	getTexParameterIuiv = getFunction<GLGetTexParameterIUIV>("glGetTexParameterIuiv");
	getTransformFeedbackVarying = getFunction<GLGetTransformFeedbackVarying>("glGetTransformFeedbackVarying");
	getUniformuiv = getFunction<GLGetUniformUIV>("glGetUniformuiv");
	getVertexAttribIiv = getFunction<GLGetVertexAttribIIV>("glGetVertexAttribIiv");
	getVertexAttribIuiv = getFunction<GLGetVertexAttribIUIV>("glGetVertexAttribIuiv");
	isEnabledi = getFunction<GLIsEnabledI>("glIsEnabledi");
	isFramebuffer = getFunction<GLIsFramebuffer>("glIsFramebuffer");
	isRenderbuffer = getFunction<GLIsRenderbuffer>("glIsRenderbuffer");
	isVertexArray = getFunction<GLIsVertexArray>("glIsVertexArray");
	mapBufferRange = getFunction<GLMapBufferRange>("glMapBufferRange");
	renderbufferStorage = getFunction<GLRenderbufferStorage>("glRenderbufferStorage");

	renderbufferStorageMultisample = getFunction<GLRenderbufferStorageMultisample>(
		"glRenderbufferStorageMultisample");

	texParameterIiv = getFunction<GLTexParameterIIV>("glTexParameterIiv");
	texParameterIuiv = getFunction<GLTexParameterIUIV>("glTexParameterIuiv");
	transformFeedbackVaryings = getFunction<GLTransformFeedbackVaryings>("glTransformFeedbackVaryings");
	uniform1ui = getFunction<GLUniform1UI>("glUniform1ui");
	uniform1uiv = getFunction<GLUniform1UIV>("glUniform1uiv");
	uniform2ui = getFunction<GLUniform2UI>("glUniform2ui");
	uniform2uiv = getFunction<GLUniform2UIV>("glUniform2uiv");
	uniform3ui = getFunction<GLUniform3UI>("glUniform3ui");
	uniform3uiv = getFunction<GLUniform3UIV>("glUniform3uiv");
	uniform4ui = getFunction<GLUniform4UI>("glUniform4ui");
	uniform4uiv = getFunction<GLUniform4UIV>("glUniform4uiv");
	vertexAttribI1i = getFunction<GLVertexAttribI1I>("glVertexAttribI1i");
	vertexAttribI1iv = getFunction<GLVertexAttribI1IV>("glVertexAttribI1iv");
	vertexAttribI1ui = getFunction<GLVertexAttribI1UI>("glVertexAttribI1ui");
	vertexAttribI1uiv = getFunction<GLVertexAttribI1UIV>("glVertexAttribI1uiv");
	vertexAttribI2i = getFunction<GLVertexAttribI2I>("glVertexAttribI2i");
	vertexAttribI2iv = getFunction<GLVertexAttribI2IV>("glVertexAttribI2iv");
	vertexAttribI2ui = getFunction<GLVertexAttribI2UI>("glVertexAttribI2ui");
	vertexAttribI2uiv = getFunction<GLVertexAttribI2UIV>("glVertexAttribI2uiv");
	vertexAttribI3i = getFunction<GLVertexAttribI3I>("glVertexAttribI3i");
	vertexAttribI3iv = getFunction<GLVertexAttribI3IV>("glVertexAttribI3iv");
	vertexAttribI3ui = getFunction<GLVertexAttribI3UI>("glVertexAttribI3ui");
	vertexAttribI3uiv = getFunction<GLVertexAttribI3UIV>("glVertexAttribI3uiv");
	vertexAttribI4bv = getFunction<GLVertexAttribI4BV>("glVertexAttribI4bv");
	vertexAttribI4i = getFunction<GLVertexAttribI4I>("glVertexAttribI4i");
	vertexAttribI4iv = getFunction<GLVertexAttribI4IV>("glVertexAttribI4iv");
	vertexAttribI4sv = getFunction<GLVertexAttribI4SV>("glVertexAttribI4sv");
	vertexAttribI4ubv = getFunction<GLVertexAttribI4UBV>("glVertexAttribI4ubv");
	vertexAttribI4ui = getFunction<GLVertexAttribI4UI>("glVertexAttribI4ui");
	vertexAttribI4uiv = getFunction<GLVertexAttribI4UIV>("glVertexAttribI4uiv");
	vertexAttribI4usv = getFunction<GLVertexAttribI4USV>("glVertexAttribI4usv");
	vertexAttribIPointer = getFunction<GLVertexAttribIPointer>("glVertexAttribIPointer");
	  
	  
	// Version 3.1
	  
	copyBufferSubData = getFunction<GLCopyBufferSubData>("glCopyBufferSubData");
	drawArraysInstanced = getFunction<GLDrawArraysInstanced>("glDrawArraysInstanced");
	drawElementsInstanced = getFunction<GLDrawElementsInstanced>("glDrawElementsInstanced");
	getActiveUniformBlockiv = getFunction<GLGetActiveUniformBlockIV>("glGetActiveUniformBlockiv");
	getActiveUniformBlockName = getFunction<GLGetActiveUniformBlockName>("glGetActiveUniformBlockName");
	getActiveUniformName = getFunction<GLGetActiveUniformName>("glGetActiveUniformName");
	getActiveUniformsiv = getFunction<GLGetActiveUniformsIV>("glGetActiveUniformsiv");
	getUniformBlockIndex = getFunction<GLGetUniformBlockIndex>("glGetUniformBlockIndex");
	getUniformIndices = getFunction<GLGetUniformIndices>("glGetUniformIndices");
	primitiveRestartIndex = getFunction<GLPrimitiveRestartIndex>("glPrimitiveRestartIndex");
	texBuffer = getFunction<GLTexBuffer>("glTexBuffer");
	uniformBlockBinding = getFunction<GLUniformBlockBinding>("glUniformBlockBinding");
	  
	  
	// Version 3.2
	  
	clientWaitSync = getFunction<GLClientWaitSync>("glClientWaitSync");
	deleteSync = getFunction<GLDeleteSync>("glDeleteSync");
	drawElementsBaseVertex = getFunction<GLDrawElementsBaseVertex>("glDrawElementsBaseVertex");

	drawElementsInstancedBaseVertex = getFunction<GLDrawElementsInstancedBaseVertex>(
		"glDrawElementsInstancedBaseVertex");

	drawRangeElementsBaseVertex = getFunction<GLDrawRangeElementsBaseVertex>("glDrawRangeElementsBaseVertex");
	fenceSync = getFunction<GLFenceSync>("glFenceSync");
	framebufferTexture = getFunction<GLFramebufferTexture>("glFramebufferTexture");
	getBufferParameteri64v = getFunction<GLGetBufferParameterI64V>("glGetBufferParameteri64v");
	getInteger64i_v = getFunction<GLGetInteger64I_V>("glGetInteger64i_v");
	getInteger64v = getFunction<GLGetInteger64V>("glGetInteger64v");
	getMultisamplefv = getFunction<GLGetMultisampleFV>("glGetMultisamplefv");
	getSynciv = getFunction<GLGetSyncIV>("glGetSynciv");
	isSync = getFunction<GLIsSync>("glIsSync");
	multiDrawElementsBaseVertex = getFunction<GLMultiDrawElementsBaseVertex>("glMultiDrawElementsBaseVertex");
	provokingVertex = getFunction<GLProvokingVertex>("glProvokingVertex");
	sampleMaski = getFunction<GLSampleMaskI>("glSampleMaski");
	texImage2DMultisample = getFunction<GLTexImage2DMultisample>("glTexImage2DMultisample");
	texImage3DMultisample = getFunction<GLTexImage3DMultisample>("glTexImage3DMultisample");
	waitSync = getFunction<GLWaitSync>("glWaitSync");
	  
	  
	// Version 3.3
	  
	bindFragDataLocationIndexed = getFunction<GLBindFragDataLocationIndexed>("glBindFragDataLocationIndexed");
	bindSampler = getFunction<GLBindSampler>("glBindSampler");
	deleteSamplers = getFunction<GLDeleteSamplers>("glDeleteSamplers");
	genSamplers = getFunction<GLGenSamplers>("glGenSamplers");
	getFragDataIndex = getFunction<GLGetFragDataIndex>("glGetFragDataIndex");
	getQueryObjecti64v = getFunction<GLGetQueryObjectI64V>("glGetQueryObjecti64v");
	getQueryObjectui64v = getFunction<GLGetQueryObjectUI64V>("glGetQueryObjectui64v");
	getSamplerParameterfv = getFunction<GLGetSamplerParameterFV>("glGetSamplerParameterfv");
	getSamplerParameterIiv = getFunction<GLGetSamplerParameterIIV>("glGetSamplerParameterIiv");
	getSamplerParameterIuiv = getFunction<GLGetSamplerParameterIUIV>("glGetSamplerParameterIuiv");
	getSamplerParameteriv = getFunction<GLGetSamplerParameterIV>("glGetSamplerParameteriv");
	isSampler = getFunction<GLIsSampler>("glIsSampler");
	queryCounter = getFunction<GLQueryCounter>("glQueryCounter");
	samplerParameterf = getFunction<GLSamplerParameterF>("glSamplerParameterf");
	samplerParameterfv = getFunction<GLSamplerParameterFV>("glSamplerParameterfv");
	samplerParameteri = getFunction<GLSamplerParameterI>("glSamplerParameteri");
	samplerParameteriv = getFunction<GLSamplerParameterIV>("glSamplerParameteriv");
	samplerParameterIiv = getFunction<GLSamplerParameterIIV>("glSamplerParameterIiv");
	samplerParameterIuiv = getFunction<GLSamplerParameterIUIV>("glSamplerParameterIuiv");
	vertexAttribDivisor = getFunction<GLVertexAttribDivisor>("glVertexAttribDivisor");
	vertexAttribP1ui = getFunction<GLVertexAttribP1UI>("glVertexAttribP1ui");
	vertexAttribP1uiv = getFunction<GLVertexAttribP1UIV>("glVertexAttribP1uiv");
	vertexAttribP2ui = getFunction<GLVertexAttribP2UI>("glVertexAttribP2ui");
	vertexAttribP2uiv = getFunction<GLVertexAttribP2UIV>("glVertexAttribP2uiv");
	vertexAttribP3ui = getFunction<GLVertexAttribP3UI>("glVertexAttribP3ui");
	vertexAttribP3uiv = getFunction<GLVertexAttribP3UIV>("glVertexAttribP3uiv");
	vertexAttribP4ui = getFunction<GLVertexAttribP4UI>("glVertexAttribP4ui");
	vertexAttribP4uiv = getFunction<GLVertexAttribP4UIV>("glVertexAttribP4uiv");
	  
	  
	// Version 4.0
	  
	beginQueryIndexed = getFunction<GLBeginQueryIndexed>("glBeginQueryIndexed");
	bindTransformFeedback = getFunction<GLBindTransformFeedback>("glBindTransformFeedback");
	blendEquationi = getFunction<GLBlendEquationI>("glBlendEquationi");
	blendEquationSeparatei = getFunction<GLBlendEquationSeparateI>("glBlendEquationSeparatei");
	blendFunci = getFunction<GLBlendFuncI>("glBlendFunci");
	blendFuncSeparatei = getFunction<GLBlendFuncSeparateI>("glBlendFuncSeparatei");
	deleteTransformFeedbacks = getFunction<GLDeleteTransformFeedbacks>("glDeleteTransformFeedbacks");
	drawArraysIndirect = getFunction<GLDrawArraysIndirect>("glDrawArraysIndirect");
	drawElementsIndirect = getFunction<GLDrawElementsIndirect>("glDrawElementsIndirect");
	drawTransformFeedback = getFunction<GLDrawTransformFeedback>("glDrawTransformFeedback");
	drawTransformFeedbackStream = getFunction<GLDrawTransformFeedbackStream>("glDrawTransformFeedbackStream");
	endQueryIndexed = getFunction<GLEndQueryIndexed>("glEndQueryIndexed");
	genTransformFeedbacks = getFunction<GLGenTransformFeedbacks>("glGenTransformFeedbacks");
	getActiveSubroutineName = getFunction<GLGetActiveSubroutineName>("glGetActiveSubroutineName");
	getActiveSubroutineUniformiv = getFunction<GLGetActiveSubroutineUniformIV>("glGetActiveSubroutineUniformiv");

	getActiveSubroutineUniformName = getFunction<GLGetActiveSubroutineUniformName>(
		"glGetActiveSubroutineUniformName");

	getProgramStageiv = getFunction<GLGetProgramStageIV>("glGetProgramStageiv");
	getQueryIndexediv = getFunction<GLGetQueryIndexedIV>("glGetQueryIndexediv");
	getSubroutineIndex = getFunction<GLGetSubroutineIndex>("glGetSubroutineIndex");
	getSubroutineUniformLocation = getFunction<GLGetSubroutineUniformLocation>("glGetSubroutineUniformLocation");
	getUniformdv = getFunction<GLGetUniformDV>("glGetUniformdv");
	getUniformSubroutineuiv = getFunction<GLGetUniformSubroutineUIV>("glGetUniformSubroutineuiv");
	isTransformFeedback = getFunction<GLIsTransformFeedback>("glIsTransformFeedback");
	minSampleShading = getFunction<GLMinSampleShading>("glMinSampleShading");
	patchParameterfv = getFunction<GLPatchParameterFV>("glPatchParameterfv");
	patchParameteri = getFunction<GLPatchParameterI>("glPatchParameteri");
	pauseTransformFeedback = getFunction<GLPauseTransformFeedback>("glPauseTransformFeedback");
	resumeTransformFeedback = getFunction<GLResumeTransformFeedback>("glResumeTransformFeedback");
	uniform1d = getFunction<GLUniform1D>("glUniform1d");
	uniform1dv = getFunction<GLUniform1DV>("glUniform1dv");
	uniform2d = getFunction<GLUniform2D>("glUniform2d");
	uniform2dv = getFunction<GLUniform2DV>("glUniform2dv");
	uniform3d = getFunction<GLUniform3D>("glUniform3d");
	uniform3dv = getFunction<GLUniform3DV>("glUniform3dv");
	uniform4d = getFunction<GLUniform4D>("glUniform4d");
	uniform4dv = getFunction<GLUniform4DV>("glUniform4dv");
	uniformMatrix2dv = getFunction<GLUniformMatrix2DV>("glUniformMatrix2dv");
	uniformMatrix2x3dv = getFunction<GLUniformMatrix2X3DV>("glUniformMatrix2x3dv");
	uniformMatrix2x4dv = getFunction<GLUniformMatrix2X4DV>("glUniformMatrix2x4dv");
	uniformMatrix3dv = getFunction<GLUniformMatrix3DV>("glUniformMatrix3dv");
	uniformMatrix3x2dv = getFunction<GLUniformMatrix3X2DV>("glUniformMatrix3x2dv");
	uniformMatrix3x4dv = getFunction<GLUniformMatrix3X4DV>("glUniformMatrix3x4dv");
	uniformMatrix4dv = getFunction<GLUniformMatrix4DV>("glUniformMatrix4dv");
	uniformMatrix4x2dv = getFunction<GLUniformMatrix4X2DV>("glUniformMatrix4x2dv");
	uniformMatrix4x3dv = getFunction<GLUniformMatrix4X3DV>("glUniformMatrix4x3dv");
	uniformSubroutinesuiv = getFunction<GLUniformSubroutineSUIV>("glUniformSubroutinesuiv");
	  
	  
	// Version 4.1
	  
	activeShaderProgram = getFunction<GLActiveShaderProgram>("glActiveShaderProgram");
	bindProgramPipeline = getFunction<GLBindProgramPipeline>("glBindProgramPipeline");
	clearDepthf = getFunction<GLClearDepthF>("glClearDepthf");
	createShaderProgramv = getFunction<GLCreateShaderProgramV>("glCreateShaderProgramv");
	deleteProgramPipelines = getFunction<GLDeleteProgramPipelines>("glDeleteProgramPipelines");
	depthRangeArrayv = getFunction<GLDepthRangeArrayV>("glDepthRangeArrayv");
	depthRangef = getFunction<GLDepthRangeF>("glDepthRangef");
	depthRangeIndexed = getFunction<GLDepthRangeIndexed>("glDepthRangeIndexed");
	genProgramPipelines = getFunction<GLGenProgramPipelines>("glGenProgramPipelines");
	getDoublei_v = getFunction<GLGetDoubleI_V>("glGetDoublei_v");
	getFloati_v = getFunction<GLGetFloatI_V>("glGetFloati_v");
	getProgramBinary = getFunction<GLGetProgramBinary>("glGetProgramBinary");
	getProgramPipelineInfoLog = getFunction<GLGetProgramPipelineInfoLog>("glGetProgramPipelineInfoLog");
	getProgramPipelineiv = getFunction<GLGetProgramPipelineIV>("glGetProgramPipelineiv");
	getShaderPrecisionFormat = getFunction<GLGetShaderPrecisionFormat>("glGetShaderPrecisionFormat");
	getVertexAttribLdv = getFunction<GLGetVertexAttribLDV>("glGetVertexAttribLdv");
	isProgramPipeline = getFunction<GLIsProgramPipeline>("glIsProgramPipeline");
	programBinary = getFunction<GLProgramBinary>("glProgramBinary");
	programParameteri = getFunction<GLProgramParameterI>("glProgramParameteri");
	programUniform1d = getFunction<GLProgramUniform1D>("glProgramUniform1d");
	programUniform1dv = getFunction<GLProgramUniform1DV>("glProgramUniform1dv");
	programUniform1f = getFunction<GLProgramUniform1F>("glProgramUniform1f");
	programUniform1fv = getFunction<GLProgramUniform1FV>("glProgramUniform1fv");
	programUniform1i = getFunction<GLProgramUniform1I>("glProgramUniform1i");
	programUniform1iv = getFunction<GLProgramUniform1IV>("glProgramUniform1iv");
	programUniform1ui = getFunction<GLProgramUniform1UI>("glProgramUniform1ui");
	programUniform1uiv = getFunction<GLProgramUniform1UIV>("glProgramUniform1uiv");
	programUniform2d = getFunction<GLProgramUniform2D>("glProgramUniform2d");
	programUniform2dv = getFunction<GLProgramUniform2DV>("glProgramUniform2dv");
	programUniform2f = getFunction<GLProgramUniform2F>("glProgramUniform2f");
	programUniform2fv = getFunction<GLProgramUniform2FV>("glProgramUniform2fv");
	programUniform2i = getFunction<GLProgramUniform2I>("glProgramUniform2i");
	programUniform2iv = getFunction<GLProgramUniform2IV>("glProgramUniform2iv");
	programUniform2ui = getFunction<GLProgramUniform2UI>("glProgramUniform2ui");
	programUniform2uiv = getFunction<GLProgramUniform2UIV>("glProgramUniform2uiv");
	programUniform3d = getFunction<GLProgramUniform3D>("glProgramUniform3d");
	programUniform3dv = getFunction<GLProgramUniform3DV>("glProgramUniform3dv");
	programUniform3f = getFunction<GLProgramUniform3F>("glProgramUniform3f");
	programUniform3fv = getFunction<GLProgramUniform3FV>("glProgramUniform3fv");
	programUniform3i = getFunction<GLProgramUniform3I>("glProgramUniform3i");
	programUniform3iv = getFunction<GLProgramUniform3IV>("glProgramUniform3iv");
	programUniform3ui = getFunction<GLProgramUniform3UI>("glProgramUniform3ui");
	programUniform3uiv = getFunction<GLProgramUniform3UIV>("glProgramUniform3uiv");
	programUniform4d = getFunction<GLProgramUniform4D>("glProgramUniform4d");
	programUniform4dv = getFunction<GLProgramUniform4DV>("glProgramUniform4dv");
	programUniform4f = getFunction<GLProgramUniform4F>("glProgramUniform4f");
	programUniform4fv = getFunction<GLProgramUniform4FV>("glProgramUniform4fv");
	programUniform4i = getFunction<GLProgramUniform4I>("glProgramUniform4i");
	programUniform4iv = getFunction<GLProgramUniform4IV>("glProgramUniform4iv");
	programUniform4ui = getFunction<GLProgramUniform4UI>("glProgramUniform4ui");
	programUniform4uiv = getFunction<GLProgramUniform4UIV>("glProgramUniform4uiv");
	programUniformMatrix2dv = getFunction<GLProgramUniformMatrix2DV>("glProgramUniformMatrix2dv");
	programUniformMatrix2fv = getFunction<GLProgramUniformMatrix2FV>("glProgramUniformMatrix2fv");
	programUniformMatrix2x3dv = getFunction<GLProgramUniformMatrix2X3DV>("glProgramUniformMatrix2x3dv");
	programUniformMatrix2x3fv = getFunction<GLProgramUniformMatrix2X3FV>("glProgramUniformMatrix2x3fv");
	programUniformMatrix2x4dv = getFunction<GLProgramUniformMatrix2X4DV>("glProgramUniformMatrix2x4dv");
	programUniformMatrix2x4fv = getFunction<GLProgramUniformMatrix2X4FV>("glProgramUniformMatrix2x4fv");
	programUniformMatrix3dv = getFunction<GLProgramUniformMatrix3DV>("glProgramUniformMatrix3dv");
	programUniformMatrix3fv = getFunction<GLProgramUniformMatrix3FV>("glProgramUniformMatrix3fv");
	programUniformMatrix3x2dv = getFunction<GLProgramUniformMatrix3X2DV>("glProgramUniformMatrix3x2dv");
	programUniformMatrix3x2fv = getFunction<GLProgramUniformMatrix3X2FV>("glProgramUniformMatrix3x2fv");
	programUniformMatrix3x4dv = getFunction<GLProgramUniformMatrix3X4DV>("glProgramUniformMatrix3x4dv");
	programUniformMatrix3x4fv = getFunction<GLProgramUniformMatrix3X4FV>("glProgramUniformMatrix3x4fv");
	programUniformMatrix4dv = getFunction<GLProgramUniformMatrix4DV>("glProgramUniformMatrix4dv");
	programUniformMatrix4fv = getFunction<GLProgramUniformMatrix4FV>("glProgramUniformMatrix4fv");
	programUniformMatrix4x2dv = getFunction<GLProgramUniformMatrix4X2DV>("glProgramUniformMatrix4x2dv");
	programUniformMatrix4x2fv = getFunction<GLProgramUniformMatrix4X2FV>("glProgramUniformMatrix4x2fv");
	programUniformMatrix4x3dv = getFunction<GLProgramUniformMatrix4X3DV>("glProgramUniformMatrix4x3dv");
	programUniformMatrix4x3fv = getFunction<GLProgramUniformMatrix4X3FV>("glProgramUniformMatrix4x3fv");
	releaseShaderCompiler = getFunction<GLReleaseShaderCompiler>("glReleaseShaderCompiler");
	shaderBinary = getFunction<GLShaderBinary>("glShaderBinary");
	scissorArrayv = getFunction<GLScissorArrayV>("glScissorArrayv");
	scissorIndexed = getFunction<GLScissorIndexed>("glScissorIndexed");
	scissorIndexedv = getFunction<GLScissorIndexedV>("glScissorIndexedv");
	useProgramStages = getFunction<GLUseProgramStages>("glUseProgramStages");
	validateProgramPipeline = getFunction<GLValidateProgramPipeline>("glValidateProgramPipeline");
	vertexAttribL1d = getFunction<GLVertexAttribL1D>("glVertexAttribL1d");
	vertexAttribL1dv = getFunction<GLVertexAttribL1DV>("glVertexAttribL1dv");
	vertexAttribL2d = getFunction<GLVertexAttribL2D>("glVertexAttribL2d");
	vertexAttribL2dv = getFunction<GLVertexAttribL2DV>("glVertexAttribL2dv");
	vertexAttribL3d = getFunction<GLVertexAttribL3D>("glVertexAttribL3d");
	vertexAttribL3dv = getFunction<GLVertexAttribL3DV>("glVertexAttribL3dv");
	vertexAttribL4d = getFunction<GLVertexAttribL4D>("glVertexAttribL4d");
	vertexAttribL4dv = getFunction<GLVertexAttribL4DV>("glVertexAttribL4dv");
	vertexAttribLPointer = getFunction<GLVertexAttribLPointer>("glVertexAttribLPointer");
	viewportArrayv = getFunction<GLViewportArrayV>("glViewportArrayv");
	viewportIndexedf = getFunction<GLViewportIndexedF>("glViewportIndexedf");
	viewportIndexedfv = getFunction<GLViewportIndexedFV>("glViewportIndexedfv");
	  
	  
	// Version 4.2
	  
	bindImageTexture = getFunction<GLBindImageTexture>("glBindImageTexture");

	drawArraysInstancedBaseInstance = getFunction<GLDrawArraysInstancedBaseInstance>(
		"glDrawArraysInstancedBaseInstance");

	drawElementsInstancedBaseInstance = getFunction<GLDrawElementsInstancedBaseInstance>(
		"glDrawElementsInstancedBaseInstance");

	drawElementsInstancedBaseVertexBaseInstance = getFunction<GLDrawElementsInstancedBaseVertexBaseInstance>(
		"glDrawElementsInstancedBaseVertexBaseInstance");

	drawTransformFeedbackInstanced = getFunction<GLDrawTransformFeedbackInstanced>(
		"glDrawTransformFeedbackInstanced");

	drawTransformFeedbackStreamInstanced = getFunction<GLDrawTransformFeedbackStreamInstanced>(
		"glDrawTransformFeedbackStreamInstanced");

	getActiveAtomicCounterBufferiv = getFunction<GLGetActiveAtomicCounterBufferIV>(
		"glGetActiveAtomicCounterBufferiv");

	getInternalformativ = getFunction<GLGetInternalformatIV>("glGetInternalformativ");
	memoryBarrier = getFunction<GLMemoryBarrier>("glMemoryBarrier");
	texStorage1D = getFunction<GLTexStorage1D>("glTexStorage1D");
	texStorage2D = getFunction<GLTexStorage2D>("glTexStorage2D");
	texStorage3D = getFunction<GLTexStorage3D>("glTexStorage3D");
	  
	  
	// Version 4.3
	  
	bindVertexBuffer = getFunction<GLBindVertexBuffer>("glBindVertexBuffer");
	clearBufferData = getFunction<GLClearBufferData>("glClearBufferData");
	clearBufferSubData = getFunction<GLClearBufferSubData>("glClearBufferSubData");
	copyImageSubData = getFunction<GLCopyImageSubData>("glCopyImageSubData");
	dispatchCompute = getFunction<GLDispatchCompute>("glDispatchCompute");
	dispatchComputeIndirect = getFunction<GLDispatchComputeIndirect>("glDispatchComputeIndirect");
	debugMessageCallback = getFunction<GLDebugMessageCallback>("glDebugMessageCallback");
	debugMessageControl = getFunction<GLDebugMessageControl>("glDebugMessageControl");
	debugMessageInsert = getFunction<GLDebugMessageInsert>("glDebugMessageInsert");
	framebufferParameteri = getFunction<GLFramebufferParameterI>("glFramebufferParameteri");
	getDebugMessageLog = getFunction<GLGetDebugMessageLog>("glGetDebugMessageLog");
	getFramebufferParameteriv = getFunction<GLGetFramebufferParameterIV>("glGetFramebufferParameteriv");
	getInternalformati64v = getFunction<GLGetInternalformatI64V>("glGetInternalformati64v");
	getObjectLabel = getFunction<GLGetObjectLabel>("glGetObjectLabel");
	getObjectPtrLabel = getFunction<GLGetObjectPtrLabel>("glGetObjectPtrLabel");
	getProgramInterfaceiv = getFunction<GLGetProgramInterfaceIV>("glGetProgramInterfaceiv");
	getProgramResourceIndex = getFunction<GLGetProgramResourceIndex>("glGetProgramResourceIndex");
	getProgramResourceiv = getFunction<GLGetProgramResourceIV>("glGetProgramResourceiv");
	getProgramResourceLocation = getFunction<GLGetProgramResourceLocation>("glGetProgramResourceLocation");

	getProgramResourceLocationIndex = getFunction<GLGetProgramResourceLocationIndex>(
		"glGetProgramResourceLocationIndex");

	getProgramResourceName = getFunction<GLGetProgramResourceName>("glGetProgramResourceName");
	invalidateBufferData = getFunction<GLInvalidateBufferData>("glInvalidateBufferData");
	invalidateBufferSubData = getFunction<GLInvalidateBufferSubData>("glInvalidateBufferSubData");
	invalidateFramebuffer = getFunction<GLInvalidateFramebuffer>("glInvalidateFramebuffer");
	invalidateSubFramebuffer = getFunction<GLInvalidateSubFramebuffer>("glInvalidateSubFramebuffer");
	invalidateTexImage = getFunction<GLInvalidateTexImage>("glInvalidateTexImage");
	invalidateTexSubImage = getFunction<GLInvalidateTexSubImage>("glInvalidateTexSubImage");
	multiDrawArraysIndirect = getFunction<GLMultiDrawArraysIndirect>("glMultiDrawArraysIndirect");
	multiDrawElementsIndirect = getFunction<GLMultiDrawElementsIndirect>("glMultiDrawElementsIndirect");
	objectLabel = getFunction<GLObjectLabel>("glObjectLabel");
	objectPtrLabel = getFunction<GLObjectPtrLabel>("glObjectPtrLabel");
	popDebugGroup = getFunction<GLPopDebugGroup>("glPopDebugGroup");
	pushDebugGroup = getFunction<GLPushDebugGroup>("glPushDebugGroup");
	shaderStorageBlockBinding = getFunction<GLShaderStorageBlockBinding>("glShaderStorageBlockBinding");
	texBufferRange = getFunction<GLTexBufferRange>("glTexBufferRange");
	texStorage2DMultisample = getFunction<GLTexStorage2DMultisample>("glTexStorage2DMultisample");
	texStorage3DMultisample = getFunction<GLTexStorage3DMultisample>("glTexStorage3DMultisample");
	textureView = getFunction<GLTextureView>("glTextureView");
	vertexAttribBinding = getFunction<GLVertexAttribBinding>("glVertexAttribBinding");
	vertexAttribFormat = getFunction<GLVertexAttribFormat>("glVertexAttribFormat");
	vertexAttribIFormat = getFunction<GLVertexAttribIFormat>("glVertexAttribIFormat");
	vertexAttribLFormat = getFunction<GLVertexAttribLFormat>("glVertexAttribLFormat");
	vertexBindingDivisor = getFunction<GLVertexBindingDivisor>("glVertexBindingDivisor");
	  
	  
	// Version 4.4
	  
	bindBuffersBase = getFunction<GLBindBuffersBase>("glBindBuffersBase");
	bindBuffersRange = getFunction<GLBindBuffersRange>("glBindBuffersRange");
	bindImageTextures = getFunction<GLBindImageTextures>("glBindImageTextures");
	bindSamplers = getFunction<GLBindSamplers>("glBindSamplers");
	bindTextures = getFunction<GLBindTextures>("glBindTextures");
	bindVertexBuffers = getFunction<GLBindVertexBuffers>("glBindVertexBuffers");
	bufferStorage = getFunction<GLBufferStorage>("glBufferStorage");
	clearTexImage = getFunction<GLClearTexImage>("glClearTexImage");
	clearTexSubImage = getFunction<GLClearTexSubImage>("glClearTexSubImage");
	  
	  
	// Version 4.5
	  
	bindTextureUnit = getFunction<GLBindTextureUnit>("glBindTextureUnit");
	blitNamedFramebuffer = getFunction<GLBlitNamedFramebuffer>("glBlitNamedFramebuffer");
	checkNamedFramebufferStatus = getFunction<GLCheckNamedFramebufferStatus>("glCheckNamedFramebufferStatus");
	clearNamedBufferData = getFunction<GLClearNamedBufferData>("glClearNamedBufferData");
	clearNamedBufferSubData = getFunction<GLClearNamedBufferSubData>("glClearNamedBufferSubData");
	clearNamedFramebufferfi = getFunction<GLClearNamedFramebufferFI>("glClearNamedFramebufferfi");
	clearNamedFramebufferfv = getFunction<GLClearNamedFramebufferFV>("glClearNamedFramebufferfv");
	clearNamedFramebufferiv = getFunction<GLClearNamedFramebufferIV>("glClearNamedFramebufferiv");
	clearNamedFramebufferuiv = getFunction<GLClearNamedFramebufferUIV>("glClearNamedFramebufferuiv");
	clipControl = getFunction<GLClipControl>("glClipControl");
	compressedTextureSubImage1D = getFunction<GLCompressedTextureSubImage1D>("glCompressedTextureSubImage1D");
	compressedTextureSubImage2D = getFunction<GLCompressedTextureSubImage2D>("glCompressedTextureSubImage2D");
	compressedTextureSubImage3D = getFunction<GLCompressedTextureSubImage3D>("glCompressedTextureSubImage3D");
	copyNamedBufferSubData = getFunction<GLCopyNamedBufferSubData>("glCopyNamedBufferSubData");
	copyTextureSubImage1D = getFunction<GLCopyTextureSubImage1D>("glCopyTextureSubImage1D");
	copyTextureSubImage2D = getFunction<GLCopyTextureSubImage2D>("glCopyTextureSubImage2D");
	copyTextureSubImage3D = getFunction<GLCopyTextureSubImage3D>("glCopyTextureSubImage3D");
	createBuffers = getFunction<GLCreateBuffers>("glCreateBuffers");
	createFramebuffers = getFunction<GLCreateFramebuffers>("glCreateFramebuffers");
	createProgramPipelines = getFunction<GLCreateProgramPipelines>("glCreateProgramPipelines");
	createQueries = getFunction<GLCreateQueries>("glCreateQueries");
	createRenderbuffers = getFunction<GLCreateRenderbuffers>("glCreateRenderbuffers");
	createSamplers = getFunction<GLCreateSamplers>("glCreateSamplers");
	createTextures = getFunction<GLCreateTextures>("glCreateTextures");
	createTransformFeedbacks = getFunction<GLCreateTransformFeedbacks>("glCreateTransformFeedbacks");
	createVertexArrays = getFunction<GLCreateVertexArrays>("glCreateVertexArrays");
	disableVertexArrayAttrib = getFunction<GLDisableVertexArrayAttrib>("glDisableVertexArrayAttrib");
	enableVertexArrayAttrib = getFunction<GLEnableVertexArrayAttrib>("glEnableVertexArrayAttrib");
	flushMappedNamedBufferRange = getFunction<GLFlushMappedNamedBufferRange>("glFlushMappedNamedBufferRange");
	generateTextureMipmap = getFunction<GLGenerateTextureMipmap>("glGenerateTextureMipmap");
	getCompressedTextureImage = getFunction<GLGetCompressedTextureImage>("glGetCompressedTextureImage");
	getCompressedTextureSubImage = getFunction<GLGetCompressedTextureSubImage>("glGetCompressedTextureSubImage");
	getGraphicsResetStatus = getFunction<GLGetGraphicsResetStatus>("glGetGraphicsResetStatus");
	getNamedBufferParameteri64v = getFunction<GLGetNamedBufferParameterI64V>("glGetNamedBufferParameteri64v");
	getNamedBufferParameteriv = getFunction<GLGetNamedBufferParameterIV>("glGetNamedBufferParameteriv");
	getNamedBufferPointerv = getFunction<GLGetNamedBufferPointerV>("glGetNamedBufferPointerv");
	getNamedBufferSubData = getFunction<GLGetNamedBufferSubData>("glGetNamedBufferSubData");

	getNamedFramebufferAttachmentParameteriv = getFunction<GLGetNamedFramebufferAttachmentParameterIV>(
		"glGetNamedFramebufferAttachmentParameteriv");

	getNamedFramebufferParameteriv = getFunction<GLGetNamedFramebufferParameterIV>(
		"glGetNamedFramebufferParameteriv");

	getNamedRenderbufferParameteriv = getFunction<GLGetNamedRenderbufferParameterIV>(
		"glGetNamedRenderbufferParameteriv");

	getnCompressedTexImage = getFunction<GLGetnCompressedTexImage>("glGetnCompressedTexImage");
	getnTexImage = getFunction<GLGetnTexImage>("glGetnTexImage");
	getnUniformdv = getFunction<GLGetnUniformDV>("glGetnUniformdv");
	getnUniformfv = getFunction<GLGetnUniformFV>("glGetnUniformfv");
	getnUniformiv = getFunction<GLGetnUniformIV>("glGetnUniformiv");
	getnUniformuiv = getFunction<GLGetnUniformUIV>("glGetnUniformuiv");
	getQueryBufferObjecti64v = getFunction<GLGetQueryBufferObjectI64V>("glGetQueryBufferObjecti64v");
	getQueryBufferObjectiv = getFunction<GLGetQueryBufferObjectIV>("glGetQueryBufferObjectiv");
	getQueryBufferObjectui64v = getFunction<GLGetQueryBufferObjectUI64V>("glGetQueryBufferObjectui64v");
	getQueryBufferObjectuiv = getFunction<GLGetQueryBufferObjectUIV>("glGetQueryBufferObjectuiv");
	getTextureImage = getFunction<GLGetTextureImage>("glGetTextureImage");
	getTextureLevelParameterfv = getFunction<GLGetTextureLevelParameterFV>("glGetTextureLevelParameterfv");
	getTextureLevelParameteriv = getFunction<GLGetTextureLevelParameterIV>("glGetTextureLevelParameteriv");
	getTextureParameterfv = getFunction<GLGetTextureParameterFV>("glGetTextureParameterfv");
	getTextureParameterIiv = getFunction<GLGetTextureParameterIIV>("glGetTextureParameterIiv");
	getTextureParameteriv = getFunction<GLGetTextureParameterIV>("glGetTextureParameteriv");
	getTextureParameterIuiv = getFunction<GLGetTextureParameterIUIV>("glGetTextureParameterIuiv");
	getTextureSubImage = getFunction<GLGetTextureSubImage>("glGetTextureSubImage");
	getTransformFeedbacki64_v = getFunction<GLGetTransformFeedbackI64_V>("glGetTransformFeedbacki64_v");
	getTransformFeedbackiv = getFunction<GLGetTransformFeedbackIV>("glGetTransformFeedbackiv");
	getTransformFeedbacki_v = getFunction<GLGetTransformFeedbackI_V>("glGetTransformFeedbacki_v");
	getVertexArrayIndexed64iv = getFunction<GLGetVertexArrayIndexed64IV>("glGetVertexArrayIndexed64iv");
	getVertexArrayIndexediv = getFunction<GLGetVertexArrayIndexedIV>("glGetVertexArrayIndexediv");
	getVertexArrayiv = getFunction<GLGetVertexArrayIV>("glGetVertexArrayiv");

	invalidateNamedFramebufferData = getFunction<GLInvalidateNamedFramebufferData>(
		"glInvalidateNamedFramebufferData");

	invalidateNamedFramebufferSubData = getFunction<GLInvalidateNamedFramebufferSubData>(
		"glInvalidateNamedFramebufferSubData");

	mapNamedBuffer = getFunction<GLMapNamedBuffer>("glMapNamedBuffer");
	mapNamedBufferRange = getFunction<GLMapNamedBufferRange>("glMapNamedBufferRange");
	memoryBarrierByRegion = getFunction<GLMemoryBarrierByRegion>("glMemoryBarrierByRegion");
	namedBufferData = getFunction<GLNamedBufferData>("glNamedBufferData");
	namedBufferStorage = getFunction<GLNamedBufferStorage>("glNamedBufferStorage");
	namedBufferSubData = getFunction<GLNamedBufferSubData>("glNamedBufferSubData");
	namedFramebufferDrawBuffer = getFunction<GLNamedFramebufferDrawBuffer>("glNamedFramebufferDrawBuffer");
	namedFramebufferDrawBuffers = getFunction<GLNamedFramebufferDrawBuffers>("glNamedFramebufferDrawBuffers");
	namedFramebufferParameteri = getFunction<GLNamedFramebufferParameterI>("glNamedFramebufferParameteri");
	namedFramebufferReadBuffer = getFunction<GLNamedFramebufferReadBuffer>("glNamedFramebufferReadBuffer");
	namedFramebufferRenderbuffer = getFunction<GLNamedFramebufferRenderbuffer>("glNamedFramebufferRenderbuffer");
	namedFramebufferTexture = getFunction<GLNamedFramebufferTexture>("glNamedFramebufferTexture");
	namedFramebufferTextureLayer = getFunction<GLNamedFramebufferTextureLayer>("glNamedFramebufferTextureLayer");
	namedRenderbufferStorage = getFunction<GLNamedRenderbufferStorage>("glNamedRenderbufferStorage");

	namedRenderbufferStorageMultisample = getFunction<GLNamedRenderbufferStorageMultisample>(
		"glNamedRenderbufferStorageMultisample");

	readnPixels = getFunction<GLReadnPixels>("glReadnPixels");
	transformFeedbackBufferBase = getFunction<GLTransformFeedbackBufferBase>("glTransformFeedbackBufferBase");
	transformFeedbackBufferRange = getFunction<GLTransformFeedbackBufferRange>("glTransformFeedbackBufferRange");
	textureBarrier = getFunction<GLTextureBarrier>("glTextureBarrier");
	textureBuffer = getFunction<GLTextureBuffer>("glTextureBuffer");
	textureBufferRange = getFunction<GLTextureBufferRange>("glTextureBufferRange");
	textureParameterf = getFunction<GLTextureParameterF>("glTextureParameterf");
	textureParameterfv = getFunction<GLTextureParameterFV>("glTextureParameterfv");
	textureParameteri = getFunction<GLTextureParameterI>("glTextureParameteri");
	textureParameterIiv = getFunction<GLTextureParameterIIV>("glTextureParameterIiv");
	textureParameterIuiv = getFunction<GLTextureParameterIUIV>("glTextureParameterIuiv");
	textureParameteriv = getFunction<GLTextureParameterIV>("glTextureParameteriv");
	textureStorage1D = getFunction<GLTextureStorage1D>("glTextureStorage1D");
	textureStorage2D = getFunction<GLTextureStorage2D>("glTextureStorage2D");
	textureStorage2DMultisample = getFunction<GLTextureStorage2DMultisample>("glTextureStorage2DMultisample");
	textureStorage3D = getFunction<GLTextureStorage3D>("glTextureStorage3D");
	textureStorage3DMultisample = getFunction<GLTextureStorage3DMultisample>("glTextureStorage3DMultisample");
	textureSubImage1D = getFunction<GLTextureSubImage1D>("glTextureSubImage1D");
	textureSubImage2D = getFunction<GLTextureSubImage2D>("glTextureSubImage2D");
	textureSubImage3D = getFunction<GLTextureSubImage3D>("glTextureSubImage3D");
	unmapNamedBuffer = getFunction<GLUnmapNamedBuffer>("glUnmapNamedBuffer");
	vertexArrayAttribBinding = getFunction<GLVertexArrayAttribBinding>("glVertexArrayAttribBinding");
	vertexArrayAttribFormat = getFunction<GLVertexArrayAttribFormat>("glVertexArrayAttribFormat");
	vertexArrayAttribIFormat = getFunction<GLVertexArrayAttribIFormat>("glVertexArrayAttribIFormat");
	vertexArrayAttribLFormat = getFunction<GLVertexArrayAttribLFormat>("glVertexArrayAttribLFormat");
	vertexArrayBindingDivisor = getFunction<GLVertexArrayBindingDivisor>("glVertexArrayBindingDivisor");
	vertexArrayElementBuffer = getFunction<GLVertexArrayElementBuffer>("glVertexArrayElementBuffer");
	vertexArrayVertexBuffer = getFunction<GLVertexArrayVertexBuffer>("glVertexArrayVertexBuffer");
	vertexArrayVertexBuffers = getFunction<GLVertexArrayVertexBuffers>("glVertexArrayVertexBuffers");
}
