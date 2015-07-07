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

#include <core/StringStream.h>
#include <core/debug/Assert.h>
#include <platform/opengl/OpenGLInterface.h>

using namespace Core;
using namespace Platform;

// Public

// Version 1.0

GLBlendFunc OpenGL::blendFunc = nullptr;
GLClear OpenGL::clear = nullptr;
GLClearColor OpenGL::clearColor = nullptr;
GLClearDepth OpenGL::clearDepth = nullptr;
GLClearStencil OpenGL::clearStencil = nullptr;
GLColorMask OpenGL::colorMask = nullptr;
GLCullFace OpenGL::cullFace = nullptr;
GLDepthFunc OpenGL::depthFunc = nullptr;
GLDepthMask OpenGL::depthMask = nullptr;
GLDepthRange OpenGL::depthRange = nullptr;
GLDisable OpenGL::disable = nullptr;
GLDrawBuffer OpenGL::drawBuffer = nullptr;
GLEnable OpenGL::enable = nullptr;
GLFinish OpenGL::finish = nullptr;
GLFlush OpenGL::flush = nullptr;
GLFrontFace OpenGL::frontFace = nullptr;
GLGetBooleanV OpenGL::getBooleanv = nullptr;
GLGetDoubleV OpenGL::getDoublev = nullptr;
GLGetError OpenGL::getError = nullptr;
GLGetFloatV OpenGL::getFloatv = nullptr;
GLGetIntegerV OpenGL::getIntegerv = nullptr;
GLGetString OpenGL::getString = nullptr;
GLGetTexImage OpenGL::getTexImage = nullptr;
GLGetTexLevelParameterFV OpenGL::getTexLevelParameterfv = nullptr;
GLGetTexLevelParameterIV OpenGL::getTexLevelParameteriv = nullptr;
GLGetTexParameterFV OpenGL::getTexParameterfv = nullptr;
GLGetTexParameterIV OpenGL::getTexParameteriv = nullptr;
GLHint OpenGL::hint = nullptr;
GLIsEnabled OpenGL::isEnabled = nullptr;
GLLineWidth OpenGL::lineWidth = nullptr;
GLLogicOp OpenGL::logicOp = nullptr;
GLPixelStoreF OpenGL::pixelStoref = nullptr;
GLPixelStoreI OpenGL::pixelStorei = nullptr;
GLPointSize OpenGL::pointSize = nullptr;
GLPolygonMode OpenGL::polygonMode = nullptr;
GLReadBuffer OpenGL::readBuffer = nullptr;
GLReadPixels OpenGL::readPixels = nullptr;
GLScissor OpenGL::scissor = nullptr;
GLStencilFunc OpenGL::stencilFunc = nullptr;
GLStencilMask OpenGL::stencilMask = nullptr;
GLStencilOp OpenGL::stencilOp = nullptr;
GLTexImage1D OpenGL::texImage1D = nullptr;
GLTexImage2D OpenGL::texImage2D = nullptr;
GLTexParameterF OpenGL::texParameterf = nullptr;
GLTexParameterFV OpenGL::texParameterfv = nullptr;
GLTexParameterI OpenGL::texParameteri = nullptr;
GLTexParameterIV OpenGL::texParameteriv = nullptr;
GLViewport OpenGL::viewport = nullptr;

// Version 1.1

GLBindTexture OpenGL::bindTexture = nullptr;
GLCopyTexImage1D OpenGL::copyTexImage1D = nullptr;
GLCopyTexImage2D OpenGL::copyTexImage2D = nullptr;
GLCopyTexSubImage1D OpenGL::copyTexSubImage1D = nullptr;
GLCopyTexSubImage2D OpenGL::copyTexSubImage2D = nullptr;
GLDeleteTextures OpenGL::deleteTextures = nullptr;
GLDrawArrays OpenGL::drawArrays = nullptr;
GLDrawElements OpenGL::drawElements = nullptr;
GLGenTextures OpenGL::genTextures = nullptr;
GLGetPointerV OpenGL::getPointerv = nullptr;
GLIsTexture OpenGL::isTexture = nullptr;
GLPolygonOffset OpenGL::polygonOffset = nullptr;
GLTexSubImage1D OpenGL::texSubImage1D = nullptr;
GLTexSubImage2D OpenGL::texSubImage2D = nullptr;

// Version 1.2

GLCopyTexSubImage3D OpenGL::copyTexSubImage3D = nullptr;
GLDrawRangeElements OpenGL::drawRangeElements = nullptr;
GLTexImage3D OpenGL::texImage3D = nullptr;
GLTexSubImage3D OpenGL::texSubImage3D = nullptr;

// Version 1.3

GLActiveTexture OpenGL::activeTexture = nullptr;
GLCompressedTexImage1D OpenGL::compressedTexImage1D = nullptr;
GLCompressedTexImage2D OpenGL::compressedTexImage2D = nullptr;
GLCompressedTexImage3D OpenGL::compressedTexImage3D = nullptr;
GLCompressedTexSubImage1D OpenGL::compressedTexSubImage1D = nullptr;
GLCompressedTexSubImage2D OpenGL::compressedTexSubImage2D = nullptr;
GLCompressedTexSubImage3D OpenGL::compressedTexSubImage3D = nullptr;
GLGetCompressedTexImage OpenGL::getCompressedTexImage = nullptr;
GLSampleCoverage OpenGL::sampleCoverage = nullptr;

// Version 1.4

GLBlendColor OpenGL::blendColor = nullptr;
GLBlendEquation OpenGL::blendEquation = nullptr;
GLBlendFuncSeparate OpenGL::blendFuncSeparate = nullptr;
GLMultiDrawArrays OpenGL::multiDrawArrays = nullptr;
GLMultiDrawElements OpenGL::multiDrawElements = nullptr;
GLPointParameterF OpenGL::pointParameterf = nullptr;
GLPointParameterFV OpenGL::pointParameterfv = nullptr;
GLPointParameterI OpenGL::pointParameteri = nullptr;
GLPointParameterIV OpenGL::pointParameteriv = nullptr;

// Version 1.5

GLBeginQuery OpenGL::beginQuery = nullptr;
GLBindBuffer OpenGL::bindBuffer = nullptr;
GLBufferData OpenGL::bufferData = nullptr;
GLBufferSubData OpenGL::bufferSubData = nullptr;
GLDeleteBuffers OpenGL::deleteBuffers = nullptr;
GLDeleteQueries OpenGL::deleteQueries = nullptr;
GLEndQuery OpenGL::endQuery = nullptr;
GLGenBuffers OpenGL::genBuffers = nullptr;
GLGenQueries OpenGL::genQueries = nullptr;
GLGetBufferParameterIV OpenGL::getBufferParameteriv = nullptr;
GLGetBufferPointerV OpenGL::getBufferPointerv = nullptr;
GLGetBufferSubData OpenGL::getBufferSubData = nullptr;
GLGetQueryIV OpenGL::getQueryiv = nullptr;
GLGetQueryObjectIV OpenGL::getQueryObjectiv = nullptr;
GLGetQueryObjectUIV OpenGL::getQueryObjectuiv = nullptr;
GLIsBuffer OpenGL::isBuffer = nullptr;
GLIsQuery OpenGL::isQuery = nullptr;
GLMapBuffer OpenGL::mapBuffer = nullptr;
GLUnmapBuffer OpenGL::unmapBuffer = nullptr;

// Version 2.0

GLAttachShader OpenGL::attachShader = nullptr;
GLBindAttribLocation OpenGL::bindAttribLocation = nullptr;
GLBlendEquationSeparate OpenGL::blendEquationSeparate = nullptr;
GLCompileShader OpenGL::compileShader = nullptr;
GLCreateProgram OpenGL::createProgram = nullptr;
GLCreateShader OpenGL::createShader = nullptr;
GLDeleteProgram OpenGL::deleteProgram = nullptr;
GLDeleteShader OpenGL::deleteShader = nullptr;
GLDetachShader OpenGL::detachShader = nullptr;
GLDisableVertexAttribArray OpenGL::disableVertexAttribArray = nullptr;
GLDrawBuffers OpenGL::drawBuffers = nullptr;
GLEnableVertexAttribArray OpenGL::enableVertexAttribArray = nullptr;
GLGetActiveAttrib OpenGL::getActiveAttrib = nullptr;
GLGetActiveUniform OpenGL::getActiveUniform = nullptr;
GLGetAttachedShaders OpenGL::getAttachedShaders = nullptr;
GLGetAttribLocation OpenGL::getAttribLocation = nullptr;
GLGetProgramInfoLog OpenGL::getProgramInfoLog = nullptr;
GLGetProgramIV OpenGL::getProgramiv = nullptr;
GLGetShaderInfoLog OpenGL::getShaderInfoLog = nullptr;
GLGetShaderIV OpenGL::getShaderiv = nullptr;
GLGetShaderSource OpenGL::getShaderSource = nullptr;
GLGetUniformFV OpenGL::getUniformfv = nullptr;
GLGetUniformIV OpenGL::getUniformiv = nullptr;
GLGetUniformLocation OpenGL::getUniformLocation = nullptr;
GLGetVertexAttribDV OpenGL::getVertexAttribdv = nullptr;
GLGetVertexAttribFV OpenGL::getVertexAttribfv = nullptr;
GLGetVertexAttribIV OpenGL::getVertexAttribiv = nullptr;
GLGetVertexAttribPointerV OpenGL::getVertexAttribPointerv = nullptr;
GLIsProgram OpenGL::isProgram = nullptr;
GLIsShader OpenGL::isShader = nullptr;
GLLinkProgram OpenGL::linkProgram = nullptr;
GLShaderSource OpenGL::shaderSource = nullptr;
GLStencilFuncSeparate OpenGL::stencilFuncSeparate = nullptr;
GLStencilMaskSeparate OpenGL::stencilMaskSeparate = nullptr;
GLStencilOpSeparate OpenGL::stencilOpSeparate = nullptr;
GLUniform1F OpenGL::uniform1f = nullptr;
GLUniform1FV OpenGL::uniform1fv = nullptr;
GLUniform1I OpenGL::uniform1i = nullptr;
GLUniform1IV OpenGL::uniform1iv = nullptr;
GLUniform2F OpenGL::uniform2f = nullptr;
GLUniform2FV OpenGL::uniform2fv = nullptr;
GLUniform2I OpenGL::uniform2i = nullptr;
GLUniform2IV OpenGL::uniform2iv = nullptr;
GLUniform3F OpenGL::uniform3f = nullptr;
GLUniform3FV OpenGL::uniform3fv = nullptr;
GLUniform3I OpenGL::uniform3i = nullptr;
GLUniform3IV OpenGL::uniform3iv = nullptr;
GLUniform4F OpenGL::uniform4f = nullptr;
GLUniform4FV OpenGL::uniform4fv = nullptr;
GLUniform4I OpenGL::uniform4i = nullptr;
GLUniform4IV OpenGL::uniform4iv = nullptr;
GLUniformMatrix2FV OpenGL::uniformMatrix2fv = nullptr;
GLUniformMatrix3FV OpenGL::uniformMatrix3fv = nullptr;
GLUniformMatrix4FV OpenGL::uniformMatrix4fv = nullptr;
GLUseProgram OpenGL::useProgram = nullptr;
GLValidateProgram OpenGL::validateProgram = nullptr;
GLVertexAttrib1D OpenGL::vertexAttrib1d = nullptr;
GLVertexAttrib1DV OpenGL::vertexAttrib1dv = nullptr;
GLVertexAttrib1F OpenGL::vertexAttrib1f = nullptr;
GLVertexAttrib1FV OpenGL::vertexAttrib1fv = nullptr;
GLVertexAttrib1S OpenGL::vertexAttrib1s = nullptr;
GLVertexAttrib1SV OpenGL::vertexAttrib1sv = nullptr;
GLVertexAttrib2D OpenGL::vertexAttrib2d = nullptr;
GLVertexAttrib2DV OpenGL::vertexAttrib2dv = nullptr;
GLVertexAttrib2F OpenGL::vertexAttrib2f = nullptr;
GLVertexAttrib2FV OpenGL::vertexAttrib2fv = nullptr;
GLVertexAttrib2S OpenGL::vertexAttrib2s = nullptr;
GLVertexAttrib2SV OpenGL::vertexAttrib2sv = nullptr;
GLVertexAttrib3D OpenGL::vertexAttrib3d = nullptr;
GLVertexAttrib3DV OpenGL::vertexAttrib3dv = nullptr;
GLVertexAttrib3F OpenGL::vertexAttrib3f = nullptr;
GLVertexAttrib3FV OpenGL::vertexAttrib3fv = nullptr;
GLVertexAttrib3S OpenGL::vertexAttrib3s = nullptr;
GLVertexAttrib3SV OpenGL::vertexAttrib3sv = nullptr;
GLVertexAttrib4BV OpenGL::vertexAttrib4bv = nullptr;
GLVertexAttrib4D OpenGL::vertexAttrib4d = nullptr;
GLVertexAttrib4DV OpenGL::vertexAttrib4dv = nullptr;
GLVertexAttrib4F OpenGL::vertexAttrib4f = nullptr;
GLVertexAttrib4FV OpenGL::vertexAttrib4fv = nullptr;
GLVertexAttrib4IV OpenGL::vertexAttrib4iv = nullptr;
GLVertexAttrib4NBV OpenGL::vertexAttrib4Nbv = nullptr;
GLVertexAttrib4NIV OpenGL::vertexAttrib4Niv = nullptr;
GLVertexAttrib4NSV OpenGL::vertexAttrib4Nsv = nullptr;
GLVertexAttrib4NUB OpenGL::vertexAttrib4Nub = nullptr;
GLVertexAttrib4NUBV OpenGL::vertexAttrib4Nubv = nullptr;
GLVertexAttrib4NUIV OpenGL::vertexAttrib4Nuiv = nullptr;
GLVertexAttrib4NUSV OpenGL::vertexAttrib4Nusv = nullptr;
GLVertexAttrib4S OpenGL::vertexAttrib4s = nullptr;
GLVertexAttrib4SV OpenGL::vertexAttrib4sv = nullptr;
GLVertexAttrib4UBV OpenGL::vertexAttrib4ubv = nullptr;
GLVertexAttrib4UIV OpenGL::vertexAttrib4uiv = nullptr;
GLVertexAttrib4USV OpenGL::vertexAttrib4usv = nullptr;
GLVertexAttribPointer OpenGL::vertexAttribPointer = nullptr;

// Version 2.1

GLUniformMatrix2X3FV OpenGL::uniformMatrix2x3fv = nullptr;
GLUniformMatrix2X4FV OpenGL::uniformMatrix2x4fv = nullptr;
GLUniformMatrix3X2FV OpenGL::uniformMatrix3x2fv = nullptr;
GLUniformMatrix3X4FV OpenGL::uniformMatrix3x4fv = nullptr;
GLUniformMatrix4X2FV OpenGL::uniformMatrix4x2fv = nullptr;
GLUniformMatrix4X3FV OpenGL::uniformMatrix4x3fv = nullptr;

// Version 3.0

GLBeginConditionalRender OpenGL::beginConditionalRender = nullptr;
GLBeginTransformFeedback OpenGL::beginTransformFeedback = nullptr;
GLBindBufferBase OpenGL::bindBufferBase = nullptr;
GLBindBufferRange OpenGL::bindBufferRange = nullptr;
GLBindFragDataLocation OpenGL::bindFragDataLocation = nullptr;
GLBindFramebuffer OpenGL::bindFramebuffer = nullptr;
GLBindRenderbuffer OpenGL::bindRenderbuffer = nullptr;
GLBindVertexArray OpenGL::bindVertexArray = nullptr;
GLBlitFramebuffer OpenGL::blitFramebuffer = nullptr;
GLCheckFramebufferStatus OpenGL::checkFramebufferStatus = nullptr;
GLClampColor OpenGL::clampColor = nullptr;
GLClearBufferFI OpenGL::clearBufferfi = nullptr;
GLClearBufferFV OpenGL::clearBufferfv = nullptr;
GLClearBufferIV OpenGL::clearBufferiv = nullptr;
GLClearBufferUIV OpenGL::clearBufferuiv = nullptr;
GLColorMaskI OpenGL::colorMaski = nullptr;
GLDeleteFramebuffers OpenGL::deleteFramebuffers = nullptr;
GLDeleteRenderbuffers OpenGL::deleteRenderbuffers = nullptr;
GLDeleteVertexArrays OpenGL::deleteVertexArrays = nullptr;
GLDisableI OpenGL::disablei = nullptr;
GLEnableI OpenGL::enablei = nullptr;
GLEndConditionalRender OpenGL::endConditionalRender = nullptr;
GLEndTransformFeedback OpenGL::endTransformFeedback = nullptr;
GLFlushMappedBufferRange OpenGL::flushMappedBufferRange = nullptr;
GLFramebufferRenderbuffer OpenGL::framebufferRenderbuffer = nullptr;
GLFramebufferTexture1D OpenGL::framebufferTexture1D = nullptr;
GLFramebufferTexture2D OpenGL::framebufferTexture2D = nullptr;
GLFramebufferTexture3D OpenGL::framebufferTexture3D = nullptr;
GLFramebufferTextureLayer OpenGL::framebufferTextureLayer = nullptr;
GLGenerateMipmap OpenGL::generateMipmap = nullptr;
GLGenFramebuffers OpenGL::genFramebuffers = nullptr;
GLGenRenderbuffers OpenGL::genRenderbuffers = nullptr;
GLGenVertexArrays OpenGL::genVertexArrays = nullptr;
GLGetBooleanI_V OpenGL::getBooleani_v = nullptr;
GLGetFragDataLocation OpenGL::getFragDataLocation = nullptr;
GLGetFramebufferAttachmentParameterIV OpenGL::getFramebufferAttachmentParameteriv = nullptr;
GLGetIntegerI_V OpenGL::getIntegeri_v = nullptr;
GLGetRenderbufferParameterIV OpenGL::getRenderbufferParameteriv = nullptr;
GLGetStringI OpenGL::getStringi = nullptr;
GLGetTexParameterIIV OpenGL::getTexParameterIiv = nullptr;
GLGetTexParameterIUIV OpenGL::getTexParameterIuiv = nullptr;
GLGetTransformFeedbackVarying OpenGL::getTransformFeedbackVarying = nullptr;
GLGetUniformUIV OpenGL::getUniformuiv = nullptr;
GLGetVertexAttribIIV OpenGL::getVertexAttribIiv = nullptr;
GLGetVertexAttribIUIV OpenGL::getVertexAttribIuiv = nullptr;
GLIsEnabledI OpenGL::isEnabledi = nullptr;
GLIsFramebuffer OpenGL::isFramebuffer = nullptr;
GLIsRenderbuffer OpenGL::isRenderbuffer = nullptr;
GLIsVertexArray OpenGL::isVertexArray = nullptr;
GLMapBufferRange OpenGL::mapBufferRange = nullptr;
GLRenderbufferStorage OpenGL::renderbufferStorage = nullptr;
GLRenderbufferStorageMultisample OpenGL::renderbufferStorageMultisample = nullptr;
GLTexParameterIIV OpenGL::texParameterIiv = nullptr;
GLTexParameterIUIV OpenGL::texParameterIuiv = nullptr;
GLTransformFeedbackVaryings OpenGL::transformFeedbackVaryings = nullptr;
GLUniform1UI OpenGL::uniform1ui = nullptr;
GLUniform1UIV OpenGL::uniform1uiv = nullptr;
GLUniform2UI OpenGL::uniform2ui = nullptr;
GLUniform2UIV OpenGL::uniform2uiv = nullptr;
GLUniform3UI OpenGL::uniform3ui = nullptr;
GLUniform3UIV OpenGL::uniform3uiv = nullptr;
GLUniform4UI OpenGL::uniform4ui = nullptr;
GLUniform4UIV OpenGL::uniform4uiv = nullptr;
GLVertexAttribI1I OpenGL::vertexAttribI1i = nullptr;
GLVertexAttribI1IV OpenGL::vertexAttribI1iv = nullptr;
GLVertexAttribI1UI OpenGL::vertexAttribI1ui = nullptr;
GLVertexAttribI1UIV OpenGL::vertexAttribI1uiv = nullptr;
GLVertexAttribI2I OpenGL::vertexAttribI2i = nullptr;
GLVertexAttribI2IV OpenGL::vertexAttribI2iv = nullptr;
GLVertexAttribI2UI OpenGL::vertexAttribI2ui = nullptr;
GLVertexAttribI2UIV OpenGL::vertexAttribI2uiv = nullptr;
GLVertexAttribI3I OpenGL::vertexAttribI3i = nullptr;
GLVertexAttribI3IV OpenGL::vertexAttribI3iv = nullptr;
GLVertexAttribI3UI OpenGL::vertexAttribI3ui = nullptr;
GLVertexAttribI3UIV OpenGL::vertexAttribI3uiv = nullptr;
GLVertexAttribI4BV OpenGL::vertexAttribI4bv = nullptr;
GLVertexAttribI4I OpenGL::vertexAttribI4i = nullptr;
GLVertexAttribI4IV OpenGL::vertexAttribI4iv = nullptr;
GLVertexAttribI4SV OpenGL::vertexAttribI4sv = nullptr;
GLVertexAttribI4UBV OpenGL::vertexAttribI4ubv = nullptr;
GLVertexAttribI4UI OpenGL::vertexAttribI4ui = nullptr;
GLVertexAttribI4UIV OpenGL::vertexAttribI4uiv = nullptr;
GLVertexAttribI4USV OpenGL::vertexAttribI4usv = nullptr;
GLVertexAttribIPointer OpenGL::vertexAttribIPointer = nullptr;

// Version 3.1

GLCopyBufferSubData OpenGL::copyBufferSubData = nullptr;
GLDrawArraysInstanced OpenGL::drawArraysInstanced = nullptr;
GLDrawElementsInstanced OpenGL::drawElementsInstanced = nullptr;
GLGetActiveUniformBlockIV OpenGL::getActiveUniformBlockiv = nullptr;
GLGetActiveUniformBlockName OpenGL::getActiveUniformBlockName = nullptr;
GLGetActiveUniformName OpenGL::getActiveUniformName = nullptr;
GLGetActiveUniformsIV OpenGL::getActiveUniformsiv = nullptr;
GLGetUniformBlockIndex OpenGL::getUniformBlockIndex = nullptr;
GLGetUniformIndices OpenGL::getUniformIndices = nullptr;
GLPrimitiveRestartIndex OpenGL::primitiveRestartIndex = nullptr;
GLTexBuffer OpenGL::texBuffer = nullptr;
GLUniformBlockBinding OpenGL::uniformBlockBinding = nullptr;

// Version 3.2

GLClientWaitSync OpenGL::clientWaitSync = nullptr;
GLDeleteSync OpenGL::deleteSync = nullptr;
GLDrawElementsBaseVertex OpenGL::drawElementsBaseVertex = nullptr;
GLDrawElementsInstancedBaseVertex OpenGL::drawElementsInstancedBaseVertex = nullptr;
GLDrawRangeElementsBaseVertex OpenGL::drawRangeElementsBaseVertex = nullptr;
GLFenceSync OpenGL::fenceSync = nullptr;
GLFramebufferTexture OpenGL::framebufferTexture = nullptr;
GLGetBufferParameterI64V OpenGL::getBufferParameteri64v = nullptr;
GLGetInteger64I_V OpenGL::getInteger64i_v = nullptr;
GLGetInteger64V OpenGL::getInteger64v = nullptr;
GLGetMultisampleFV OpenGL::getMultisamplefv = nullptr;
GLGetSyncIV OpenGL::getSynciv = nullptr;
GLIsSync OpenGL::isSync = nullptr;
GLMultiDrawElementsBaseVertex OpenGL::multiDrawElementsBaseVertex = nullptr;
GLProvokingVertex OpenGL::provokingVertex = nullptr;
GLSampleMaskI OpenGL::sampleMaski = nullptr;
GLTexImage2DMultisample OpenGL::texImage2DMultisample = nullptr;
GLTexImage3DMultisample OpenGL::texImage3DMultisample = nullptr;
GLWaitSync OpenGL::waitSync = nullptr;

// Version 3.3

GLBindFragDataLocationIndexed OpenGL::bindFragDataLocationIndexed = nullptr;
GLBindSampler OpenGL::bindSampler = nullptr;
GLDeleteSamplers OpenGL::deleteSamplers = nullptr;
GLGenSamplers OpenGL::genSamplers = nullptr;
GLGetFragDataIndex OpenGL::getFragDataIndex = nullptr;
GLGetQueryObjectI64V OpenGL::getQueryObjecti64v = nullptr;
GLGetQueryObjectUI64V OpenGL::getQueryObjectui64v = nullptr;
GLGetSamplerParameterFV OpenGL::getSamplerParameterfv = nullptr;
GLGetSamplerParameterIIV OpenGL::getSamplerParameterIiv = nullptr;
GLGetSamplerParameterIUIV OpenGL::getSamplerParameterIuiv = nullptr;
GLGetSamplerParameterIV OpenGL::getSamplerParameteriv = nullptr;
GLIsSampler OpenGL::isSampler = nullptr;
GLQueryCounter OpenGL::queryCounter = nullptr;
GLSamplerParameterF OpenGL::samplerParameterf = nullptr;
GLSamplerParameterFV OpenGL::samplerParameterfv = nullptr;
GLSamplerParameterI OpenGL::samplerParameteri = nullptr;
GLSamplerParameterIV OpenGL::samplerParameteriv = nullptr;
GLSamplerParameterIIV OpenGL::samplerParameterIiv = nullptr;
GLSamplerParameterIUIV OpenGL::samplerParameterIuiv = nullptr;
GLVertexAttribDivisor OpenGL::vertexAttribDivisor = nullptr;
GLVertexAttribP1UI OpenGL::vertexAttribP1ui = nullptr;
GLVertexAttribP1UIV OpenGL::vertexAttribP1uiv = nullptr;
GLVertexAttribP2UI OpenGL::vertexAttribP2ui = nullptr;
GLVertexAttribP2UIV OpenGL::vertexAttribP2uiv = nullptr;
GLVertexAttribP3UI OpenGL::vertexAttribP3ui = nullptr;
GLVertexAttribP3UIV OpenGL::vertexAttribP3uiv = nullptr;
GLVertexAttribP4UI OpenGL::vertexAttribP4ui = nullptr;
GLVertexAttribP4UIV OpenGL::vertexAttribP4uiv = nullptr;

// Version 4.0

GLBeginQueryIndexed OpenGL::beginQueryIndexed = nullptr;
GLBindTransformFeedback OpenGL::bindTransformFeedback = nullptr;
GLBlendEquationI OpenGL::blendEquationi = nullptr;
GLBlendEquationSeparateI OpenGL::blendEquationSeparatei = nullptr;
GLBlendFuncI OpenGL::blendFunci = nullptr;
GLBlendFuncSeparateI OpenGL::blendFuncSeparatei = nullptr;
GLDeleteTransformFeedbacks OpenGL::deleteTransformFeedbacks = nullptr;
GLDrawArraysIndirect OpenGL::drawArraysIndirect = nullptr;
GLDrawElementsIndirect OpenGL::drawElementsIndirect = nullptr;
GLDrawTransformFeedback OpenGL::drawTransformFeedback = nullptr;
GLDrawTransformFeedbackStream OpenGL::drawTransformFeedbackStream = nullptr;
GLEndQueryIndexed OpenGL::endQueryIndexed = nullptr;
GLGenTransformFeedbacks OpenGL::genTransformFeedbacks = nullptr;
GLGetActiveSubroutineName OpenGL::getActiveSubroutineName = nullptr;
GLGetActiveSubroutineUniformIV OpenGL::getActiveSubroutineUniformiv = nullptr;
GLGetActiveSubroutineUniformName OpenGL::getActiveSubroutineUniformName = nullptr;
GLGetProgramStageIV OpenGL::getProgramStageiv = nullptr;
GLGetQueryIndexedIV OpenGL::getQueryIndexediv = nullptr;
GLGetSubroutineIndex OpenGL::getSubroutineIndex = nullptr;
GLGetSubroutineUniformLocation OpenGL::getSubroutineUniformLocation = nullptr;
GLGetUniformDV OpenGL::getUniformdv = nullptr;
GLGetUniformSubroutineUIV OpenGL::getUniformSubroutineuiv = nullptr;
GLIsTransformFeedback OpenGL::isTransformFeedback = nullptr;
GLMinSampleShading OpenGL::minSampleShading = nullptr;
GLPatchParameterFV OpenGL::patchParameterfv = nullptr;
GLPatchParameterI OpenGL::patchParameteri = nullptr;
GLPauseTransformFeedback OpenGL::pauseTransformFeedback = nullptr;
GLResumeTransformFeedback OpenGL::resumeTransformFeedback = nullptr;
GLUniform1D OpenGL::uniform1d = nullptr;
GLUniform1DV OpenGL::uniform1dv = nullptr;
GLUniform2D OpenGL::uniform2d = nullptr;
GLUniform2DV OpenGL::uniform2dv = nullptr;
GLUniform3D OpenGL::uniform3d = nullptr;
GLUniform3DV OpenGL::uniform3dv = nullptr;
GLUniform4D OpenGL::uniform4d = nullptr;
GLUniform4DV OpenGL::uniform4dv = nullptr;
GLUniformMatrix2DV OpenGL::uniformMatrix2dv = nullptr;
GLUniformMatrix2X3DV OpenGL::uniformMatrix2x3dv = nullptr;
GLUniformMatrix2X4DV OpenGL::uniformMatrix2x4dv = nullptr;
GLUniformMatrix3DV OpenGL::uniformMatrix3dv = nullptr;
GLUniformMatrix3X2DV OpenGL::uniformMatrix3x2dv = nullptr;
GLUniformMatrix3X4DV OpenGL::uniformMatrix3x4dv = nullptr;
GLUniformMatrix4DV OpenGL::uniformMatrix4dv = nullptr;
GLUniformMatrix4X2DV OpenGL::uniformMatrix4x2dv = nullptr;
GLUniformMatrix4X3DV OpenGL::uniformMatrix4x3dv = nullptr;
GLUniformSubroutineSUIV OpenGL::uniformSubroutinesuiv = nullptr;

// Version 4.1

GLActiveShaderProgram OpenGL::activeShaderProgram = nullptr;
GLBindProgramPipeline OpenGL::bindProgramPipeline = nullptr;
GLClearDepthF OpenGL::clearDepthf = nullptr;
GLCreateShaderProgramV OpenGL::createShaderProgramv = nullptr;
GLDeleteProgramPipelines OpenGL::deleteProgramPipelines = nullptr;
GLDepthRangeArrayV OpenGL::depthRangeArrayv = nullptr;
GLDepthRangeF OpenGL::depthRangef = nullptr;
GLDepthRangeIndexed OpenGL::depthRangeIndexed = nullptr;
GLGenProgramPipelines OpenGL::genProgramPipelines = nullptr;
GLGetDoubleI_V OpenGL::getDoublei_v = nullptr;
GLGetFloatI_V OpenGL::getFloati_v = nullptr;
GLGetProgramBinary OpenGL::getProgramBinary = nullptr;
GLGetProgramPipelineInfoLog OpenGL::getProgramPipelineInfoLog = nullptr;
GLGetProgramPipelineIV OpenGL::getProgramPipelineiv = nullptr;
GLGetShaderPrecisionFormat OpenGL::getShaderPrecisionFormat = nullptr;
GLGetVertexAttribLDV OpenGL::getVertexAttribLdv = nullptr;
GLIsProgramPipeline OpenGL::isProgramPipeline = nullptr;
GLProgramBinary OpenGL::programBinary = nullptr;
GLProgramParameterI OpenGL::programParameteri = nullptr;
GLProgramUniform1D OpenGL::programUniform1d = nullptr;
GLProgramUniform1DV OpenGL::programUniform1dv = nullptr;
GLProgramUniform1F OpenGL::programUniform1f = nullptr;
GLProgramUniform1FV OpenGL::programUniform1fv = nullptr;
GLProgramUniform1I OpenGL::programUniform1i = nullptr;
GLProgramUniform1IV OpenGL::programUniform1iv = nullptr;
GLProgramUniform1UI OpenGL::programUniform1ui = nullptr;
GLProgramUniform1UIV OpenGL::programUniform1uiv = nullptr;
GLProgramUniform2D OpenGL::programUniform2d = nullptr;
GLProgramUniform2DV OpenGL::programUniform2dv = nullptr;
GLProgramUniform2F OpenGL::programUniform2f = nullptr;
GLProgramUniform2FV OpenGL::programUniform2fv = nullptr;
GLProgramUniform2I OpenGL::programUniform2i = nullptr;
GLProgramUniform2IV OpenGL::programUniform2iv = nullptr;
GLProgramUniform2UI OpenGL::programUniform2ui = nullptr;
GLProgramUniform2UIV OpenGL::programUniform2uiv = nullptr;
GLProgramUniform3D OpenGL::programUniform3d = nullptr;
GLProgramUniform3DV OpenGL::programUniform3dv = nullptr;
GLProgramUniform3F OpenGL::programUniform3f = nullptr;
GLProgramUniform3FV OpenGL::programUniform3fv = nullptr;
GLProgramUniform3I OpenGL::programUniform3i = nullptr;
GLProgramUniform3IV OpenGL::programUniform3iv = nullptr;
GLProgramUniform3UI OpenGL::programUniform3ui = nullptr;
GLProgramUniform3UIV OpenGL::programUniform3uiv = nullptr;
GLProgramUniform4D OpenGL::programUniform4d = nullptr;
GLProgramUniform4DV OpenGL::programUniform4dv = nullptr;
GLProgramUniform4F OpenGL::programUniform4f = nullptr;
GLProgramUniform4FV OpenGL::programUniform4fv = nullptr;
GLProgramUniform4I OpenGL::programUniform4i = nullptr;
GLProgramUniform4IV OpenGL::programUniform4iv = nullptr;
GLProgramUniform4UI OpenGL::programUniform4ui = nullptr;
GLProgramUniform4UIV OpenGL::programUniform4uiv = nullptr;
GLProgramUniformMatrix2DV OpenGL::programUniformMatrix2dv = nullptr;
GLProgramUniformMatrix2FV OpenGL::programUniformMatrix2fv = nullptr;
GLProgramUniformMatrix2X3DV OpenGL::programUniformMatrix2x3dv = nullptr;
GLProgramUniformMatrix2X3FV OpenGL::programUniformMatrix2x3fv = nullptr;
GLProgramUniformMatrix2X4DV OpenGL::programUniformMatrix2x4dv = nullptr;
GLProgramUniformMatrix2X4FV OpenGL::programUniformMatrix2x4fv = nullptr;
GLProgramUniformMatrix3DV OpenGL::programUniformMatrix3dv = nullptr;
GLProgramUniformMatrix3FV OpenGL::programUniformMatrix3fv = nullptr;
GLProgramUniformMatrix3X2DV OpenGL::programUniformMatrix3x2dv = nullptr;
GLProgramUniformMatrix3X2FV OpenGL::programUniformMatrix3x2fv = nullptr;
GLProgramUniformMatrix3X4DV OpenGL::programUniformMatrix3x4dv = nullptr;
GLProgramUniformMatrix3X4FV OpenGL::programUniformMatrix3x4fv = nullptr;
GLProgramUniformMatrix4DV OpenGL::programUniformMatrix4dv = nullptr;
GLProgramUniformMatrix4FV OpenGL::programUniformMatrix4fv = nullptr;
GLProgramUniformMatrix4X2DV OpenGL::programUniformMatrix4x2dv = nullptr;
GLProgramUniformMatrix4X2FV OpenGL::programUniformMatrix4x2fv = nullptr;
GLProgramUniformMatrix4X3DV OpenGL::programUniformMatrix4x3dv = nullptr;
GLProgramUniformMatrix4X3FV OpenGL::programUniformMatrix4x3fv = nullptr;
GLReleaseShaderCompiler OpenGL::releaseShaderCompiler = nullptr;
GLShaderBinary OpenGL::shaderBinary = nullptr;
GLScissorArrayV OpenGL::scissorArrayv = nullptr;
GLScissorIndexed OpenGL::scissorIndexed = nullptr;
GLScissorIndexedV OpenGL::scissorIndexedv = nullptr;
GLUseProgramStages OpenGL::useProgramStages = nullptr;
GLValidateProgramPipeline OpenGL::validateProgramPipeline = nullptr;
GLVertexAttribL1D OpenGL::vertexAttribL1d = nullptr;
GLVertexAttribL1DV OpenGL::vertexAttribL1dv = nullptr;
GLVertexAttribL2D OpenGL::vertexAttribL2d = nullptr;
GLVertexAttribL2DV OpenGL::vertexAttribL2dv = nullptr;
GLVertexAttribL3D OpenGL::vertexAttribL3d = nullptr;
GLVertexAttribL3DV OpenGL::vertexAttribL3dv = nullptr;
GLVertexAttribL4D OpenGL::vertexAttribL4d = nullptr;
GLVertexAttribL4DV OpenGL::vertexAttribL4dv = nullptr;
GLVertexAttribLPointer OpenGL::vertexAttribLPointer = nullptr;
GLViewportArrayV OpenGL::viewportArrayv = nullptr;
GLViewportIndexedF OpenGL::viewportIndexedf = nullptr;
GLViewportIndexedFV OpenGL::viewportIndexedfv = nullptr;

// Version 4.2

GLBindImageTexture OpenGL::bindImageTexture = nullptr;
GLDrawArraysInstancedBaseInstance OpenGL::drawArraysInstancedBaseInstance = nullptr;
GLDrawElementsInstancedBaseInstance OpenGL::drawElementsInstancedBaseInstance = nullptr;
GLDrawElementsInstancedBaseVertexBaseInstance OpenGL::drawElementsInstancedBaseVertexBaseInstance = nullptr;
GLDrawTransformFeedbackInstanced OpenGL::drawTransformFeedbackInstanced = nullptr;
GLDrawTransformFeedbackStreamInstanced OpenGL::drawTransformFeedbackStreamInstanced = nullptr;
GLGetActiveAtomicCounterBufferIV OpenGL::getActiveAtomicCounterBufferiv = nullptr;
GLGetInternalformatIV OpenGL::getInternalformativ = nullptr;
GLMemoryBarrier OpenGL::memoryBarrier = nullptr;
GLTexStorage1D OpenGL::texStorage1D = nullptr;
GLTexStorage2D OpenGL::texStorage2D = nullptr;
GLTexStorage3D OpenGL::texStorage3D = nullptr;

// Version 4.3

GLBindVertexBuffer OpenGL::bindVertexBuffer = nullptr;
GLClearBufferData OpenGL::clearBufferData = nullptr;
GLClearBufferSubData OpenGL::clearBufferSubData = nullptr;
GLCopyImageSubData OpenGL::copyImageSubData = nullptr;
GLDispatchCompute OpenGL::dispatchCompute = nullptr;
GLDispatchComputeIndirect OpenGL::dispatchComputeIndirect = nullptr;
GLDebugMessageCallback OpenGL::debugMessageCallback = nullptr;
GLDebugMessageControl OpenGL::debugMessageControl = nullptr;
GLDebugMessageInsert OpenGL::debugMessageInsert = nullptr;
GLFramebufferParameterI OpenGL::framebufferParameteri = nullptr;
GLGetDebugMessageLog OpenGL::getDebugMessageLog = nullptr;
GLGetFramebufferParameterIV OpenGL::getFramebufferParameteriv = nullptr;
GLGetInternalformatI64V OpenGL::getInternalformati64v = nullptr;
GLGetObjectLabel OpenGL::getObjectLabel = nullptr;
GLGetObjectPtrLabel OpenGL::getObjectPtrLabel = nullptr;
GLGetProgramInterfaceIV OpenGL::getProgramInterfaceiv = nullptr;
GLGetProgramResourceIndex OpenGL::getProgramResourceIndex = nullptr;
GLGetProgramResourceIV OpenGL::getProgramResourceiv = nullptr;
GLGetProgramResourceLocation OpenGL::getProgramResourceLocation = nullptr;
GLGetProgramResourceLocationIndex OpenGL::getProgramResourceLocationIndex = nullptr;
GLGetProgramResourceName OpenGL::getProgramResourceName = nullptr;
GLInvalidateBufferData OpenGL::invalidateBufferData = nullptr;
GLInvalidateBufferSubData OpenGL::invalidateBufferSubData = nullptr;
GLInvalidateFramebuffer OpenGL::invalidateFramebuffer = nullptr;
GLInvalidateSubFramebuffer OpenGL::invalidateSubFramebuffer = nullptr;
GLInvalidateTexImage OpenGL::invalidateTexImage = nullptr;
GLInvalidateTexSubImage OpenGL::invalidateTexSubImage = nullptr;
GLMultiDrawArraysIndirect OpenGL::multiDrawArraysIndirect = nullptr;
GLMultiDrawElementsIndirect OpenGL::multiDrawElementsIndirect = nullptr;
GLObjectLabel OpenGL::objectLabel = nullptr;
GLObjectPtrLabel OpenGL::objectPtrLabel = nullptr;
GLPopDebugGroup OpenGL::popDebugGroup = nullptr;
GLPushDebugGroup OpenGL::pushDebugGroup = nullptr;
GLShaderStorageBlockBinding OpenGL::shaderStorageBlockBinding = nullptr;
GLTexBufferRange OpenGL::texBufferRange = nullptr;
GLTexStorage2DMultisample OpenGL::texStorage2DMultisample = nullptr;
GLTexStorage3DMultisample OpenGL::texStorage3DMultisample = nullptr;
GLTextureView OpenGL::textureView = nullptr;
GLVertexAttribBinding OpenGL::vertexAttribBinding = nullptr;
GLVertexAttribFormat OpenGL::vertexAttribFormat = nullptr;
GLVertexAttribIFormat OpenGL::vertexAttribIFormat = nullptr;
GLVertexAttribLFormat OpenGL::vertexAttribLFormat = nullptr;
GLVertexBindingDivisor OpenGL::vertexBindingDivisor = nullptr;

// Version 4.4

GLBindBuffersBase OpenGL::bindBuffersBase = nullptr;
GLBindBuffersRange OpenGL::bindBuffersRange = nullptr;
GLBindImageTextures OpenGL::bindImageTextures = nullptr;
GLBindSamplers OpenGL::bindSamplers = nullptr;
GLBindTextures OpenGL::bindTextures = nullptr;
GLBindVertexBuffers OpenGL::bindVertexBuffers = nullptr;
GLBufferStorage OpenGL::bufferStorage = nullptr;
GLClearTexImage OpenGL::clearTexImage = nullptr;
GLClearTexSubImage OpenGL::clearTexSubImage = nullptr;

// Version 4.5

GLBindTextureUnit OpenGL::bindTextureUnit = nullptr;
GLBlitNamedFramebuffer OpenGL::blitNamedFramebuffer = nullptr;
GLCheckNamedFramebufferStatus OpenGL::checkNamedFramebufferStatus = nullptr;
GLClearNamedBufferData OpenGL::clearNamedBufferData = nullptr;
GLClearNamedBufferSubData OpenGL::clearNamedBufferSubData = nullptr;
GLClearNamedFramebufferFI OpenGL::clearNamedFramebufferfi = nullptr;
GLClearNamedFramebufferFV OpenGL::clearNamedFramebufferfv = nullptr;
GLClearNamedFramebufferIV OpenGL::clearNamedFramebufferiv = nullptr;
GLClearNamedFramebufferUIV OpenGL::clearNamedFramebufferuiv = nullptr;
GLClipControl OpenGL::clipControl = nullptr;
GLCompressedTextureSubImage1D OpenGL::compressedTextureSubImage1D = nullptr;
GLCompressedTextureSubImage2D OpenGL::compressedTextureSubImage2D = nullptr;
GLCompressedTextureSubImage3D OpenGL::compressedTextureSubImage3D = nullptr;
GLCopyNamedBufferSubData OpenGL::copyNamedBufferSubData = nullptr;
GLCopyTextureSubImage1D OpenGL::copyTextureSubImage1D = nullptr;
GLCopyTextureSubImage2D OpenGL::copyTextureSubImage2D = nullptr;
GLCopyTextureSubImage3D OpenGL::copyTextureSubImage3D = nullptr;
GLCreateBuffers OpenGL::createBuffers = nullptr;
GLCreateFramebuffers OpenGL::createFramebuffers = nullptr;
GLCreateProgramPipelines OpenGL::createProgramPipelines = nullptr;
GLCreateQueries OpenGL::createQueries = nullptr;
GLCreateRenderbuffers OpenGL::createRenderbuffers = nullptr;
GLCreateSamplers OpenGL::createSamplers = nullptr;
GLCreateTextures OpenGL::createTextures = nullptr;
GLCreateTransformFeedbacks OpenGL::createTransformFeedbacks = nullptr;
GLCreateVertexArrays OpenGL::createVertexArrays = nullptr;
GLDisableVertexArrayAttrib OpenGL::disableVertexArrayAttrib = nullptr;
GLEnableVertexArrayAttrib OpenGL::enableVertexArrayAttrib = nullptr;
GLFlushMappedNamedBufferRange OpenGL::flushMappedNamedBufferRange = nullptr;
GLGenerateTextureMipmap OpenGL::generateTextureMipmap = nullptr;
GLGetCompressedTextureImage OpenGL::getCompressedTextureImage = nullptr;
GLGetCompressedTextureSubImage OpenGL::getCompressedTextureSubImage = nullptr;
GLGetGraphicsResetStatus OpenGL::getGraphicsResetStatus = nullptr;
GLGetNamedBufferParameterI64V OpenGL::getNamedBufferParameteri64v = nullptr;
GLGetNamedBufferParameterIV OpenGL::getNamedBufferParameteriv = nullptr;
GLGetNamedBufferPointerV OpenGL::getNamedBufferPointerv = nullptr;
GLGetNamedBufferSubData OpenGL::getNamedBufferSubData = nullptr;
GLGetNamedFramebufferAttachmentParameterIV OpenGL::getNamedFramebufferAttachmentParameteriv = nullptr;
GLGetNamedFramebufferParameterIV OpenGL::getNamedFramebufferParameteriv = nullptr;
GLGetNamedRenderbufferParameterIV OpenGL::getNamedRenderbufferParameteriv = nullptr;
GLGetnCompressedTexImage OpenGL::getnCompressedTexImage = nullptr;
GLGetnTexImage OpenGL::getnTexImage = nullptr;
GLGetnUniformDV OpenGL::getnUniformdv = nullptr;
GLGetnUniformFV OpenGL::getnUniformfv = nullptr;
GLGetnUniformIV OpenGL::getnUniformiv = nullptr;
GLGetnUniformUIV OpenGL::getnUniformuiv = nullptr;
GLGetQueryBufferObjectI64V OpenGL::getQueryBufferObjecti64v = nullptr;
GLGetQueryBufferObjectIV OpenGL::getQueryBufferObjectiv = nullptr;
GLGetQueryBufferObjectUI64V OpenGL::getQueryBufferObjectui64v = nullptr;
GLGetQueryBufferObjectUIV OpenGL::getQueryBufferObjectuiv = nullptr;
GLGetTextureImage OpenGL::getTextureImage = nullptr;
GLGetTextureLevelParameterFV OpenGL::getTextureLevelParameterfv = nullptr;
GLGetTextureLevelParameterIV OpenGL::getTextureLevelParameteriv = nullptr;
GLGetTextureParameterFV OpenGL::getTextureParameterfv = nullptr;
GLGetTextureParameterIIV OpenGL::getTextureParameterIiv = nullptr;
GLGetTextureParameterIV OpenGL::getTextureParameteriv = nullptr;
GLGetTextureParameterIUIV OpenGL::getTextureParameterIuiv = nullptr;
GLGetTextureSubImage OpenGL::getTextureSubImage = nullptr;
GLGetTransformFeedbackI64_V OpenGL::getTransformFeedbacki64_v = nullptr;
GLGetTransformFeedbackIV OpenGL::getTransformFeedbackiv = nullptr;
GLGetTransformFeedbackI_V OpenGL::getTransformFeedbacki_v = nullptr;
GLGetVertexArrayIndexed64IV OpenGL::getVertexArrayIndexed64iv = nullptr;
GLGetVertexArrayIndexedIV OpenGL::getVertexArrayIndexediv = nullptr;
GLGetVertexArrayIV OpenGL::getVertexArrayiv = nullptr;
GLInvalidateNamedFramebufferData OpenGL::invalidateNamedFramebufferData = nullptr;
GLInvalidateNamedFramebufferSubData OpenGL::invalidateNamedFramebufferSubData = nullptr;
GLMapNamedBuffer OpenGL::mapNamedBuffer = nullptr;
GLMapNamedBufferRange OpenGL::mapNamedBufferRange = nullptr;
GLMemoryBarrierByRegion OpenGL::memoryBarrierByRegion = nullptr;
GLNamedBufferData OpenGL::namedBufferData = nullptr;
GLNamedBufferStorage OpenGL::namedBufferStorage = nullptr;
GLNamedBufferSubData OpenGL::namedBufferSubData = nullptr;
GLNamedFramebufferDrawBuffer OpenGL::namedFramebufferDrawBuffer = nullptr;
GLNamedFramebufferDrawBuffers OpenGL::namedFramebufferDrawBuffers = nullptr;
GLNamedFramebufferParameterI OpenGL::namedFramebufferParameteri = nullptr;
GLNamedFramebufferReadBuffer OpenGL::namedFramebufferReadBuffer = nullptr;
GLNamedFramebufferRenderbuffer OpenGL::namedFramebufferRenderbuffer = nullptr;
GLNamedFramebufferTexture OpenGL::namedFramebufferTexture = nullptr;
GLNamedFramebufferTextureLayer OpenGL::namedFramebufferTextureLayer = nullptr;
GLNamedRenderbufferStorage OpenGL::namedRenderbufferStorage = nullptr;
GLNamedRenderbufferStorageMultisample OpenGL::namedRenderbufferStorageMultisample = nullptr;
GLReadnPixels OpenGL::readnPixels = nullptr;
GLTransformFeedbackBufferBase OpenGL::transformFeedbackBufferBase = nullptr;
GLTransformFeedbackBufferRange OpenGL::transformFeedbackBufferRange = nullptr;
GLTextureBarrier OpenGL::textureBarrier = nullptr;
GLTextureBuffer OpenGL::textureBuffer = nullptr;
GLTextureBufferRange OpenGL::textureBufferRange = nullptr;
GLTextureParameterF OpenGL::textureParameterf = nullptr;
GLTextureParameterFV OpenGL::textureParameterfv = nullptr;
GLTextureParameterI OpenGL::textureParameteri = nullptr;
GLTextureParameterIIV OpenGL::textureParameterIiv = nullptr;
GLTextureParameterIUIV OpenGL::textureParameterIuiv = nullptr;
GLTextureParameterIV OpenGL::textureParameteriv = nullptr;
GLTextureStorage1D OpenGL::textureStorage1D = nullptr;
GLTextureStorage2D OpenGL::textureStorage2D = nullptr;
GLTextureStorage2DMultisample OpenGL::textureStorage2DMultisample = nullptr;
GLTextureStorage3D OpenGL::textureStorage3D = nullptr;
GLTextureStorage3DMultisample OpenGL::textureStorage3DMultisample = nullptr;
GLTextureSubImage1D OpenGL::textureSubImage1D = nullptr;
GLTextureSubImage2D OpenGL::textureSubImage2D = nullptr;
GLTextureSubImage3D OpenGL::textureSubImage3D = nullptr;
GLUnmapNamedBuffer OpenGL::unmapNamedBuffer = nullptr;
GLVertexArrayAttribBinding OpenGL::vertexArrayAttribBinding = nullptr;
GLVertexArrayAttribFormat OpenGL::vertexArrayAttribFormat = nullptr;
GLVertexArrayAttribIFormat OpenGL::vertexArrayAttribIFormat = nullptr;
GLVertexArrayAttribLFormat OpenGL::vertexArrayAttribLFormat = nullptr;
GLVertexArrayBindingDivisor OpenGL::vertexArrayBindingDivisor = nullptr;
GLVertexArrayElementBuffer OpenGL::vertexArrayElementBuffer = nullptr;
GLVertexArrayVertexBuffer OpenGL::vertexArrayVertexBuffer = nullptr;
GLVertexArrayVertexBuffers OpenGL::vertexArrayVertexBuffers = nullptr;

// Static

void OpenGL::checkForErrors(const Char8* file, const Uint32 line, const Char8* function)
{
	Uint32 errorCode;

	while((errorCode = getError()) != GL_NO_ERROR)
		reportError(errorCode, file, line, function);
}

void OpenGL::initialise()
{
	getFunctions();
	initialiseDebugMessaging();
}

// Private

const Char8* OpenGL::COMPONENT_TAG = "[Platform::OpenGL]";

const Array<Char8*, 6u> OpenGL::DEBUG_MESSAGE_SOURCE_NAMES
{{
	"application",
	"OpenGL",
	"other source",
	"shader compiler",
	"third party",
	"window system"
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

	debugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, errorCode, GL_DEBUG_SEVERITY_HIGH, -1,
		stringStream.str().c_str());
}

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

void OpenGL::initialiseDebugMessaging()
{
	enable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	debugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	debugMessageCallback(processDebugMessage, nullptr);
}

void OpenGL::processDebugMessage(const Uint32 messageSource, const Uint32 messageType, const Uint32 messageId,
	const Uint32 messageSeverity, const Int32 messageLength, const Char8* message, const Void* userData)
{
	static_cast<Void>(messageLength);
	static_cast<Void>(userData);

	defaultLog << getDebugMessageLogLevel(messageSeverity) << COMPONENT_TAG << ' ' <<
		getDebugMessageTypeName(messageType) << " message (0x" << std::hex << std::uppercase << messageId <<
		std::nouppercase << std::dec << ") from " << getDebugMessageSourceName(messageSource) << ": '" << message <<
		'\'' << Log::Flush();
}

LogLevel OpenGL::getDebugMessageLogLevel(const Uint32 messageSeverity)
{
	switch(messageSeverity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			return LogLevel::Error;

		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			return LogLevel::Warning;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
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
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return DEBUG_MESSAGE_TYPE_NAMES[0];

		case GL_DEBUG_TYPE_ERROR:
			return DEBUG_MESSAGE_TYPE_NAMES[1];

		case GL_DEBUG_TYPE_MARKER:
			return DEBUG_MESSAGE_TYPE_NAMES[4];

		case GL_DEBUG_TYPE_OTHER:
			return DEBUG_MESSAGE_TYPE_NAMES[5];

		case GL_DEBUG_TYPE_PERFORMANCE:
			return DEBUG_MESSAGE_TYPE_NAMES[6];

		case GL_DEBUG_TYPE_POP_GROUP:
			return DEBUG_MESSAGE_TYPE_NAMES[2];

		case GL_DEBUG_TYPE_PORTABILITY:
			return DEBUG_MESSAGE_TYPE_NAMES[7];

		case GL_DEBUG_TYPE_PUSH_GROUP:
			return DEBUG_MESSAGE_TYPE_NAMES[3];

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return DEBUG_MESSAGE_TYPE_NAMES[8];

		default:
			DE_ASSERT(false);
			return DEBUG_MESSAGE_TYPE_NAMES[0];
	}
}

const Char8* OpenGL::getDebugMessageSourceName(const Uint32 messageSource)
{
	switch(messageSource)
	{
		case GL_DEBUG_SOURCE_API:
			return DEBUG_MESSAGE_SOURCE_NAMES[1];

		case GL_DEBUG_SOURCE_APPLICATION:
			return DEBUG_MESSAGE_SOURCE_NAMES[0];

		case GL_DEBUG_SOURCE_OTHER:
			return DEBUG_MESSAGE_SOURCE_NAMES[2];

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return DEBUG_MESSAGE_SOURCE_NAMES[3];

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return DEBUG_MESSAGE_SOURCE_NAMES[4];

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return DEBUG_MESSAGE_SOURCE_NAMES[5];

		default:
			DE_ASSERT(false);
			return DEBUG_MESSAGE_SOURCE_NAMES[0];
	}
}
