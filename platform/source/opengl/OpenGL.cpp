/**
 * @file platform/opengl/OpenGL.cpp
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
 */

#include <cstdlib>
#include <core/Array.h>
#include <core/Error.h>
#include <core/Log.h>
#include <core/debug/Assert.h>
#include <graphics/LogUtility.h>
#include <platform/GraphicsFunctionUtility.h>
#include <platform/Utility.h>
#include <platform/opengl/OpenGL.h>

using namespace Core;
using namespace Graphics;
using namespace Platform;

// External

static const Char8* COMPONENT_TAG = "[Platform::OpenGL]";

static const Array<const Char8*, 6u> DEBUG_MESSAGE_SOURCE_NAMES
{{
	"OpenGL",
	"window system",
	"shader compiler",
	"third party",
	"application",
	"other source"
}};

static const Array<const Char8*, 10u> DEBUG_MESSAGE_TYPE_NAMES
{{
	"Deprecated behaviour",
	"Error",
	"Group pop",
	"Group push",
	"Marker",
	"Other",
	"Performance",
	"Portability",
	"Undefined behaviour",
	"Unknown"
}};

static const Array<const Char8*, 7u> ERROR_NAMES
{{
	"Invalid enumeration",
	"Invalid value",
	"Invalid operation",
	"Stack overflow",
	"Stack underflow",
	"Out of memory",
	"Invalid framebuffer operation"
}};

static const Uint32 MIN_SUPPORTED_VERSION_MAJOR = 3u;
static const Uint32 MIN_SUPPORTED_VERSION_MINOR = 3u;

static Uint32 versionMajor = 0u;
static Uint32 versionMinor = 0u;

static LogLevel getDebugMessageLogLevel(const Uint32 messageSeverity);
static const Char8* getDebugMessageTypeName(const Uint32 messageType);
static void initialiseMajorVersion(const String8& versionString);
static void initialiseMinorVersion(const String8& versionString);

static void DE_CALL_OPENGL processDebugMessage(const Uint32 messageSource, const Uint32 messageType,
	const Uint32 messageId, const Uint32 messageSeverity, const Int32 messageLength, const Char8* message,
	const Void* userData);

static void reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function);


// Public

OpenGL::OpenGL()
{
	// TODO: check current context state?
	checkSupport();
	getStandardFunctions();

	if(debugMessageCallback != nullptr)
		initialiseDebugMessaging();
}

void OpenGL::checkForErrors(const Char8* file, const Uint32 line, const Char8* function) const
{
	Uint32 errorCode;

	while((errorCode = getError()) != NO_ERROR)
		::reportError(errorCode, file, line, function);
}

void OpenGL::logInfo() const
{
	defaultLog << LogLevel::Info << "Initialised OpenGL rendering.\n\nVersion: " << ::versionMajor << '.' <<
		::versionMinor << '\n';

	logGraphicsExtensions("graphics interface", getExtensionNames());
}

// Private

void OpenGL::checkSupport()
{
	GraphicsFunctionUtility functionUtility;
	getString = functionUtility.getStandardFunction<GetString>("glGetString");
	const String8 versionString(reinterpret_cast<const Char8*>(getString(VERSION)));
	::initialiseMajorVersion(versionString);
	::initialiseMinorVersion(versionString);

	if(isVersionLess(::versionMajor, ::versionMinor, ::MIN_SUPPORTED_VERSION_MAJOR, ::MIN_SUPPORTED_VERSION_MINOR))
	{
		defaultLog << LogLevel::Error << ::COMPONENT_TAG << " OpenGL version " << ::versionMajor << '.' <<
			::versionMinor << " is not supported. The minimum supported version is " << ::MIN_SUPPORTED_VERSION_MAJOR <<
			'.' << ::MIN_SUPPORTED_VERSION_MINOR << '.' << Log::Flush();

		DE_ERROR(0x0);
	}
}

void OpenGL::getStandardFunctions()
{
	GraphicsFunctionUtility functionUtility;

	// Version 1.0

	blendFunc = functionUtility.getStandardFunction<BlendFunc>("glBlendFunc");
	clear = functionUtility.getStandardFunction<Clear>("glClear");
	clearColor = functionUtility.getStandardFunction<ClearColor>("glClearColor");
	clearDepth = functionUtility.getStandardFunction<ClearDepth>("glClearDepth");
	clearStencil = functionUtility.getStandardFunction<ClearStencil>("glClearStencil");
	colorMask = functionUtility.getStandardFunction<ColorMask>("glColorMask");
	cullFace = functionUtility.getStandardFunction<CullFace>("glCullFace");
	depthFunc = functionUtility.getStandardFunction<DepthFunc>("glDepthFunc");
	depthMask = functionUtility.getStandardFunction<DepthMask>("glDepthMask");
	depthRange = functionUtility.getStandardFunction<DepthRange>("glDepthRange");
	disable = functionUtility.getStandardFunction<Disable>("glDisable");
	drawBuffer = functionUtility.getStandardFunction<DrawBuffer>("glDrawBuffer");
	enable = functionUtility.getStandardFunction<Enable>("glEnable");
	finish = functionUtility.getStandardFunction<Finish>("glFinish");
	flush = functionUtility.getStandardFunction<Flush>("glFlush");
	frontFace = functionUtility.getStandardFunction<FrontFace>("glFrontFace");
	getBooleanv = functionUtility.getStandardFunction<GetBooleanV>("glGetBooleanv");
	getDoublev = functionUtility.getStandardFunction<GetDoubleV>("glGetDoublev");
	getError = functionUtility.getStandardFunction<GetError>("glGetError");
	getFloatv = functionUtility.getStandardFunction<GetFloatV>("glGetFloatv");
	getIntegerv = functionUtility.getStandardFunction<GetIntegerV>("glGetIntegerv");
	// getString is initialised in OpenGL::checkSupport()
	getTexImage = functionUtility.getStandardFunction<GetTexImage>("glGetTexImage");

	getTexLevelParameterfv =
		functionUtility.getStandardFunction<GetTexLevelParameterFV>("glGetTexLevelParameterfv");

	getTexLevelParameteriv =
		functionUtility.getStandardFunction<GetTexLevelParameterIV>("glGetTexLevelParameteriv");

	getTexParameterfv = functionUtility.getStandardFunction<GetTexParameterFV>("glGetTexParameterfv");
	getTexParameteriv = functionUtility.getStandardFunction<GetTexParameterIV>("glGetTexParameteriv");
	hint = functionUtility.getStandardFunction<Hint>("glHint");
	isEnabled = functionUtility.getStandardFunction<IsEnabled>("glIsEnabled");
	lineWidth = functionUtility.getStandardFunction<LineWidth>("glLineWidth");
	logicOp = functionUtility.getStandardFunction<LogicOp>("glLogicOp");
	pixelStoref = functionUtility.getStandardFunction<PixelStoreF>("glPixelStoref");
	pixelStorei = functionUtility.getStandardFunction<PixelStoreI>("glPixelStorei");
	pointSize = functionUtility.getStandardFunction<PointSize>("glPointSize");
	polygonMode = functionUtility.getStandardFunction<PolygonMode>("glPolygonMode");
	readBuffer = functionUtility.getStandardFunction<ReadBuffer>("glReadBuffer");
	readPixels = functionUtility.getStandardFunction<ReadPixels>("glReadPixels");
	scissor = functionUtility.getStandardFunction<Scissor>("glScissor");
	stencilFunc = functionUtility.getStandardFunction<StencilFunc>("glStencilFunc");
	stencilMask = functionUtility.getStandardFunction<StencilMask>("glStencilMask");
	stencilOp = functionUtility.getStandardFunction<StencilOp>("glStencilOp");
	texImage1D = functionUtility.getStandardFunction<TexImage1D>("glTexImage1D");
	texImage2D = functionUtility.getStandardFunction<TexImage2D>("glTexImage2D");
	texParameterf = functionUtility.getStandardFunction<TexParameterF>("glTexParameterf");
	texParameterfv = functionUtility.getStandardFunction<TexParameterFV>("glTexParameterfv");
	texParameteri = functionUtility.getStandardFunction<TexParameterI>("glTexParameteri");
	texParameteriv = functionUtility.getStandardFunction<TexParameterIV>("glTexParameteriv");
	viewport = functionUtility.getStandardFunction<Viewport>("glViewport");

	// Version 1.1

	bindTexture = functionUtility.getStandardFunction<BindTexture>("glBindTexture");
	copyTexImage1D = functionUtility.getStandardFunction<CopyTexImage1D>("glCopyTexImage1D");
	copyTexImage2D = functionUtility.getStandardFunction<CopyTexImage2D>("glCopyTexImage2D");
	copyTexSubImage1D = functionUtility.getStandardFunction<CopyTexSubImage1D>("glCopyTexSubImage1D");
	copyTexSubImage2D = functionUtility.getStandardFunction<CopyTexSubImage2D>("glCopyTexSubImage2D");
	deleteTextures = functionUtility.getStandardFunction<DeleteTextures>("glDeleteTextures");
	drawArrays = functionUtility.getStandardFunction<DrawArrays>("glDrawArrays");
	drawElements = functionUtility.getStandardFunction<DrawElements>("glDrawElements");
	genTextures = functionUtility.getStandardFunction<GenTextures>("glGenTextures");
	getPointerv = functionUtility.getStandardFunction<GetPointerV>("glGetPointerv");
	isTexture = functionUtility.getStandardFunction<IsTexture>("glIsTexture");
	polygonOffset = functionUtility.getStandardFunction<PolygonOffset>("glPolygonOffset");
	texSubImage1D = functionUtility.getStandardFunction<TexSubImage1D>("glTexSubImage1D");
	texSubImage2D = functionUtility.getStandardFunction<TexSubImage2D>("glTexSubImage2D");

	// Version 1.2

	copyTexSubImage3D = functionUtility.getExtensionFunction<CopyTexSubImage3D>("glCopyTexSubImage3D");
	drawRangeElements = functionUtility.getExtensionFunction<DrawRangeElements>("glDrawRangeElements");
	texImage3D = functionUtility.getExtensionFunction<TexImage3D>("glTexImage3D");
	texSubImage3D = functionUtility.getExtensionFunction<TexSubImage3D>("glTexSubImage3D");

	// Version 1.3

	activeTexture = functionUtility.getExtensionFunction<ActiveTexture>("glActiveTexture");

	compressedTexImage1D =
		functionUtility.getExtensionFunction<CompressedTexImage1D>("glCompressedTexImage1D");

	compressedTexImage2D =
		functionUtility.getExtensionFunction<CompressedTexImage2D>("glCompressedTexImage2D");

	compressedTexImage3D =
		functionUtility.getExtensionFunction<CompressedTexImage3D>("glCompressedTexImage3D");

	compressedTexSubImage1D =
		functionUtility.getExtensionFunction<CompressedTexSubImage1D>("glCompressedTexSubImage1D");

	compressedTexSubImage2D =
		functionUtility.getExtensionFunction<CompressedTexSubImage2D>("glCompressedTexSubImage2D");

	compressedTexSubImage3D =
		functionUtility.getExtensionFunction<CompressedTexSubImage3D>("glCompressedTexSubImage3D");

	getCompressedTexImage =
		functionUtility.getExtensionFunction<GetCompressedTexImage>("glGetCompressedTexImage");

	sampleCoverage = functionUtility.getExtensionFunction<SampleCoverage>("glSampleCoverage");

	// Version 1.4

	blendColor = functionUtility.getExtensionFunction<BlendColor>("glBlendColor");
	blendEquation = functionUtility.getExtensionFunction<BlendEquation>("glBlendEquation");
	blendFuncSeparate = functionUtility.getExtensionFunction<BlendFuncSeparate>("glBlendFuncSeparate");
	multiDrawArrays = functionUtility.getExtensionFunction<MultiDrawArrays>("glMultiDrawArrays");
	multiDrawElements = functionUtility.getExtensionFunction<MultiDrawElements>("glMultiDrawElements");
	pointParameterf = functionUtility.getExtensionFunction<PointParameterF>("glPointParameterf");
	pointParameterfv = functionUtility.getExtensionFunction<PointParameterFV>("glPointParameterfv");
	pointParameteri = functionUtility.getExtensionFunction<PointParameterI>("glPointParameteri");
	pointParameteriv = functionUtility.getExtensionFunction<PointParameterIV>("glPointParameteriv");

	// Version 1.5

	beginQuery = functionUtility.getExtensionFunction<BeginQuery>("glBeginQuery");
	bindBuffer = functionUtility.getExtensionFunction<BindBuffer>("glBindBuffer");
	bufferData = functionUtility.getExtensionFunction<BufferData>("glBufferData");
	bufferSubData = functionUtility.getExtensionFunction<BufferSubData>("glBufferSubData");
	deleteBuffers = functionUtility.getExtensionFunction<DeleteBuffers>("glDeleteBuffers");
	deleteQueries = functionUtility.getExtensionFunction<DeleteQueries>("glDeleteQueries");
	endQuery = functionUtility.getExtensionFunction<EndQuery>("glEndQuery");
	genBuffers = functionUtility.getExtensionFunction<GenBuffers>("glGenBuffers");
	genQueries = functionUtility.getExtensionFunction<GenQueries>("glGenQueries");

	getBufferParameteriv =
		functionUtility.getExtensionFunction<GetBufferParameterIV>("glGetBufferParameteriv");

	getBufferPointerv = functionUtility.getExtensionFunction<GetBufferPointerV>("glGetBufferPointerv");
	getBufferSubData = functionUtility.getExtensionFunction<GetBufferSubData>("glGetBufferSubData");
	getQueryiv = functionUtility.getExtensionFunction<GetQueryIV>("glGetQueryiv");
	getQueryObjectiv = functionUtility.getExtensionFunction<GetQueryObjectIV>("glGetQueryObjectiv");
	getQueryObjectuiv = functionUtility.getExtensionFunction<GetQueryObjectUIV>("glGetQueryObjectuiv");
	isBuffer = functionUtility.getExtensionFunction<IsBuffer>("glIsBuffer");
	isQuery = functionUtility.getExtensionFunction<IsQuery>("glIsQuery");
	mapBuffer = functionUtility.getExtensionFunction<MapBuffer>("glMapBuffer");
	unmapBuffer = functionUtility.getExtensionFunction<UnmapBuffer>("glUnmapBuffer");

	// Version 2.0

	attachShader = functionUtility.getExtensionFunction<AttachShader>("glAttachShader");
	bindAttribLocation = functionUtility.getExtensionFunction<BindAttribLocation>("glBindAttribLocation");

	blendEquationSeparate =
		functionUtility.getExtensionFunction<BlendEquationSeparate>("glBlendEquationSeparate");

	compileShader = functionUtility.getExtensionFunction<CompileShader>("glCompileShader");
	createProgram = functionUtility.getExtensionFunction<CreateProgram>("glCreateProgram");
	createShader = functionUtility.getExtensionFunction<CreateShader>("glCreateShader");
	deleteProgram = functionUtility.getExtensionFunction<DeleteProgram>("glDeleteProgram");
	deleteShader = functionUtility.getExtensionFunction<DeleteShader>("glDeleteShader");
	detachShader = functionUtility.getExtensionFunction<DetachShader>("glDetachShader");

	disableVertexAttribArray =
		functionUtility.getExtensionFunction<DisableVertexAttribArray>("glDisableVertexAttribArray");

	drawBuffers = functionUtility.getExtensionFunction<DrawBuffers>("glDrawBuffers");

	enableVertexAttribArray =
		functionUtility.getExtensionFunction<EnableVertexAttribArray>("glEnableVertexAttribArray");

	getActiveAttrib = functionUtility.getExtensionFunction<GetActiveAttrib>("glGetActiveAttrib");
	getActiveUniform = functionUtility.getExtensionFunction<GetActiveUniform>("glGetActiveUniform");
	getAttachedShaders = functionUtility.getExtensionFunction<GetAttachedShaders>("glGetAttachedShaders");
	getAttribLocation = functionUtility.getExtensionFunction<GetAttribLocation>("glGetAttribLocation");
	getProgramInfoLog = functionUtility.getExtensionFunction<GetProgramInfoLog>("glGetProgramInfoLog");
	getProgramiv = functionUtility.getExtensionFunction<GetProgramIV>("glGetProgramiv");
	getShaderInfoLog = functionUtility.getExtensionFunction<GetShaderInfoLog>("glGetShaderInfoLog");
	getShaderiv = functionUtility.getExtensionFunction<GetShaderIV>("glGetShaderiv");
	getShaderSource = functionUtility.getExtensionFunction<GetShaderSource>("glGetShaderSource");
	getUniformfv = functionUtility.getExtensionFunction<GetUniformFV>("glGetUniformfv");
	getUniformiv = functionUtility.getExtensionFunction<GetUniformIV>("glGetUniformiv");
	getUniformLocation = functionUtility.getExtensionFunction<GetUniformLocation>("glGetUniformLocation");
	getVertexAttribdv = functionUtility.getExtensionFunction<GetVertexAttribDV>("glGetVertexAttribdv");
	getVertexAttribfv = functionUtility.getExtensionFunction<GetVertexAttribFV>("glGetVertexAttribfv");
	getVertexAttribiv = functionUtility.getExtensionFunction<GetVertexAttribIV>("glGetVertexAttribiv");

	getVertexAttribPointerv =
		functionUtility.getExtensionFunction<GetVertexAttribPointerV>("glGetVertexAttribPointerv");

	isProgram = functionUtility.getExtensionFunction<IsProgram>("glIsProgram");
	isShader = functionUtility.getExtensionFunction<IsShader>("glIsShader");
	linkProgram = functionUtility.getExtensionFunction<LinkProgram>("glLinkProgram");
	shaderSource = functionUtility.getExtensionFunction<ShaderSource>("glShaderSource");
	stencilFuncSeparate = functionUtility.getExtensionFunction<StencilFuncSeparate>("glStencilFuncSeparate");
	stencilMaskSeparate = functionUtility.getExtensionFunction<StencilMaskSeparate>("glStencilMaskSeparate");
	stencilOpSeparate = functionUtility.getExtensionFunction<StencilOpSeparate>("glStencilOpSeparate");
	uniform1f = functionUtility.getExtensionFunction<Uniform1F>("glUniform1f");
	uniform1fv = functionUtility.getExtensionFunction<Uniform1FV>("glUniform1fv");
	uniform1i = functionUtility.getExtensionFunction<Uniform1I>("glUniform1i");
	uniform1iv = functionUtility.getExtensionFunction<Uniform1IV>("glUniform1iv");
	uniform2f = functionUtility.getExtensionFunction<Uniform2F>("glUniform2f");
	uniform2fv = functionUtility.getExtensionFunction<Uniform2FV>("glUniform2fv");
	uniform2i = functionUtility.getExtensionFunction<Uniform2I>("glUniform2i");
	uniform2iv = functionUtility.getExtensionFunction<Uniform2IV>("glUniform2iv");
	uniform3f = functionUtility.getExtensionFunction<Uniform3F>("glUniform3f");
	uniform3fv = functionUtility.getExtensionFunction<Uniform3FV>("glUniform3fv");
	uniform3i = functionUtility.getExtensionFunction<Uniform3I>("glUniform3i");
	uniform3iv = functionUtility.getExtensionFunction<Uniform3IV>("glUniform3iv");
	uniform4f = functionUtility.getExtensionFunction<Uniform4F>("glUniform4f");
	uniform4fv = functionUtility.getExtensionFunction<Uniform4FV>("glUniform4fv");
	uniform4i = functionUtility.getExtensionFunction<Uniform4I>("glUniform4i");
	uniform4iv = functionUtility.getExtensionFunction<Uniform4IV>("glUniform4iv");
	uniformMatrix2fv = functionUtility.getExtensionFunction<UniformMatrix2FV>("glUniformMatrix2fv");
	uniformMatrix3fv = functionUtility.getExtensionFunction<UniformMatrix3FV>("glUniformMatrix3fv");
	uniformMatrix4fv = functionUtility.getExtensionFunction<UniformMatrix4FV>("glUniformMatrix4fv");
	useProgram = functionUtility.getExtensionFunction<UseProgram>("glUseProgram");
	validateProgram = functionUtility.getExtensionFunction<ValidateProgram>("glValidateProgram");
	vertexAttrib1d = functionUtility.getExtensionFunction<VertexAttrib1D>("glVertexAttrib1d");
	vertexAttrib1dv = functionUtility.getExtensionFunction<VertexAttrib1DV>("glVertexAttrib1dv");
	vertexAttrib1f = functionUtility.getExtensionFunction<VertexAttrib1F>("glVertexAttrib1f");
	vertexAttrib1fv = functionUtility.getExtensionFunction<VertexAttrib1FV>("glVertexAttrib1fv");
	vertexAttrib1s = functionUtility.getExtensionFunction<VertexAttrib1S>("glVertexAttrib1s");
	vertexAttrib1sv = functionUtility.getExtensionFunction<VertexAttrib1SV>("glVertexAttrib1sv");
	vertexAttrib2d = functionUtility.getExtensionFunction<VertexAttrib2D>("glVertexAttrib2d");
	vertexAttrib2dv = functionUtility.getExtensionFunction<VertexAttrib2DV>("glVertexAttrib2dv");
	vertexAttrib2f = functionUtility.getExtensionFunction<VertexAttrib2F>("glVertexAttrib2f");
	vertexAttrib2fv = functionUtility.getExtensionFunction<VertexAttrib2FV>("glVertexAttrib2fv");
	vertexAttrib2s = functionUtility.getExtensionFunction<VertexAttrib2S>("glVertexAttrib2s");
	vertexAttrib2sv = functionUtility.getExtensionFunction<VertexAttrib2SV>("glVertexAttrib2sv");
	vertexAttrib3d = functionUtility.getExtensionFunction<VertexAttrib3D>("glVertexAttrib3d");
	vertexAttrib3dv = functionUtility.getExtensionFunction<VertexAttrib3DV>("glVertexAttrib3dv");
	vertexAttrib3f = functionUtility.getExtensionFunction<VertexAttrib3F>("glVertexAttrib3f");
	vertexAttrib3fv = functionUtility.getExtensionFunction<VertexAttrib3FV>("glVertexAttrib3fv");
	vertexAttrib3s = functionUtility.getExtensionFunction<VertexAttrib3S>("glVertexAttrib3s");
	vertexAttrib3sv = functionUtility.getExtensionFunction<VertexAttrib3SV>("glVertexAttrib3sv");
	vertexAttrib4bv = functionUtility.getExtensionFunction<VertexAttrib4BV>("glVertexAttrib4bv");
	vertexAttrib4d = functionUtility.getExtensionFunction<VertexAttrib4D>("glVertexAttrib4d");
	vertexAttrib4dv = functionUtility.getExtensionFunction<VertexAttrib4DV>("glVertexAttrib4dv");
	vertexAttrib4f = functionUtility.getExtensionFunction<VertexAttrib4F>("glVertexAttrib4f");
	vertexAttrib4fv = functionUtility.getExtensionFunction<VertexAttrib4FV>("glVertexAttrib4fv");
	vertexAttrib4iv = functionUtility.getExtensionFunction<VertexAttrib4IV>("glVertexAttrib4iv");
	vertexAttrib4Nbv = functionUtility.getExtensionFunction<VertexAttrib4NBV>("glVertexAttrib4Nbv");
	vertexAttrib4Niv = functionUtility.getExtensionFunction<VertexAttrib4NIV>("glVertexAttrib4Niv");
	vertexAttrib4Nsv = functionUtility.getExtensionFunction<VertexAttrib4NSV>("glVertexAttrib4Nsv");
	vertexAttrib4Nub = functionUtility.getExtensionFunction<VertexAttrib4NUB>("glVertexAttrib4Nub");
	vertexAttrib4Nubv = functionUtility.getExtensionFunction<VertexAttrib4NUBV>("glVertexAttrib4Nubv");
	vertexAttrib4Nuiv = functionUtility.getExtensionFunction<VertexAttrib4NUIV>("glVertexAttrib4Nuiv");
	vertexAttrib4Nusv = functionUtility.getExtensionFunction<VertexAttrib4NUSV>("glVertexAttrib4Nusv");
	vertexAttrib4s = functionUtility.getExtensionFunction<VertexAttrib4S>("glVertexAttrib4s");
	vertexAttrib4sv = functionUtility.getExtensionFunction<VertexAttrib4SV>("glVertexAttrib4sv");
	vertexAttrib4ubv = functionUtility.getExtensionFunction<VertexAttrib4UBV>("glVertexAttrib4ubv");
	vertexAttrib4uiv = functionUtility.getExtensionFunction<VertexAttrib4UIV>("glVertexAttrib4uiv");
	vertexAttrib4usv = functionUtility.getExtensionFunction<VertexAttrib4USV>("glVertexAttrib4usv");
	vertexAttribPointer = functionUtility.getExtensionFunction<VertexAttribPointer>("glVertexAttribPointer");

	// Version 2.1

	uniformMatrix2x3fv = functionUtility.getExtensionFunction<UniformMatrix2X3FV>("glUniformMatrix2x3fv");
	uniformMatrix2x4fv = functionUtility.getExtensionFunction<UniformMatrix2X4FV>("glUniformMatrix2x4fv");
	uniformMatrix3x2fv = functionUtility.getExtensionFunction<UniformMatrix3X2FV>("glUniformMatrix3x2fv");
	uniformMatrix3x4fv = functionUtility.getExtensionFunction<UniformMatrix3X4FV>("glUniformMatrix3x4fv");
	uniformMatrix4x2fv = functionUtility.getExtensionFunction<UniformMatrix4X2FV>("glUniformMatrix4x2fv");
	uniformMatrix4x3fv = functionUtility.getExtensionFunction<UniformMatrix4X3FV>("glUniformMatrix4x3fv");

	// Version 3.0

	beginConditionalRender =
		functionUtility.getExtensionFunction<BeginConditionalRender>("glBeginConditionalRender");

	beginTransformFeedback =
		functionUtility.getExtensionFunction<BeginTransformFeedback>("glBeginTransformFeedback");

	bindBufferBase = functionUtility.getExtensionFunction<BindBufferBase>("glBindBufferBase");
	bindBufferRange = functionUtility.getExtensionFunction<BindBufferRange>("glBindBufferRange");

	bindFragDataLocation =
		functionUtility.getExtensionFunction<BindFragDataLocation>("glBindFragDataLocation");

	bindFramebuffer = functionUtility.getExtensionFunction<BindFramebuffer>("glBindFramebuffer");
	bindRenderbuffer = functionUtility.getExtensionFunction<BindRenderbuffer>("glBindRenderbuffer");
	bindVertexArray = functionUtility.getExtensionFunction<BindVertexArray>("glBindVertexArray");
	blitFramebuffer = functionUtility.getExtensionFunction<BlitFramebuffer>("glBlitFramebuffer");

	checkFramebufferStatus =
		functionUtility.getExtensionFunction<CheckFramebufferStatus>("glCheckFramebufferStatus");

	clampColor = functionUtility.getExtensionFunction<ClampColor>("glClampColor");
	clearBufferfi = functionUtility.getExtensionFunction<ClearBufferFI>("glClearBufferfi");
	clearBufferfv = functionUtility.getExtensionFunction<ClearBufferFV>("glClearBufferfv");
	clearBufferiv = functionUtility.getExtensionFunction<ClearBufferIV>("glClearBufferiv");
	clearBufferuiv = functionUtility.getExtensionFunction<ClearBufferUIV>("glClearBufferuiv");
	colorMaski = functionUtility.getExtensionFunction<ColorMaskI>("glColorMaski");
	deleteFramebuffers = functionUtility.getExtensionFunction<DeleteFramebuffers>("glDeleteFramebuffers");
	deleteRenderbuffers = functionUtility.getExtensionFunction<DeleteRenderbuffers>("glDeleteRenderbuffers");
	deleteVertexArrays = functionUtility.getExtensionFunction<DeleteVertexArrays>("glDeleteVertexArrays");
	disablei = functionUtility.getExtensionFunction<DisableI>("glDisablei");
	enablei = functionUtility.getExtensionFunction<EnableI>("glEnablei");

	endConditionalRender =
		functionUtility.getExtensionFunction<EndConditionalRender>("glEndConditionalRender");

	endTransformFeedback =
		functionUtility.getExtensionFunction<EndTransformFeedback>("glEndTransformFeedback");

	flushMappedBufferRange =
		functionUtility.getExtensionFunction<FlushMappedBufferRange>("glFlushMappedBufferRange");

	framebufferRenderbuffer =
		functionUtility.getExtensionFunction<FramebufferRenderbuffer>("glFramebufferRenderbuffer");

	framebufferTexture1D =
		functionUtility.getExtensionFunction<FramebufferTexture1D>("glFramebufferTexture1D");

	framebufferTexture2D =
		functionUtility.getExtensionFunction<FramebufferTexture2D>("glFramebufferTexture2D");

	framebufferTexture3D =
		functionUtility.getExtensionFunction<FramebufferTexture3D>("glFramebufferTexture3D");

	framebufferTextureLayer =
		functionUtility.getExtensionFunction<FramebufferTextureLayer>("glFramebufferTextureLayer");

	generateMipmap = functionUtility.getExtensionFunction<GenerateMipmap>("glGenerateMipmap");
	genFramebuffers = functionUtility.getExtensionFunction<GenFramebuffers>("glGenFramebuffers");
	genRenderbuffers = functionUtility.getExtensionFunction<GenRenderbuffers>("glGenRenderbuffers");
	genVertexArrays = functionUtility.getExtensionFunction<GenVertexArrays>("glGenVertexArrays");
	getBooleani_v = functionUtility.getExtensionFunction<GetBooleanI_V>("glGetBooleani_v");
	getFragDataLocation = functionUtility.getExtensionFunction<GetFragDataLocation>("glGetFragDataLocation");

	getFramebufferAttachmentParameteriv =
		functionUtility.getExtensionFunction<GetFramebufferAttachmentParameterIV>(
			"glGetFramebufferAttachmentParameteriv");

	getIntegeri_v = functionUtility.getExtensionFunction<GetIntegerI_V>("glGetIntegeri_v");

	getRenderbufferParameteriv =
		functionUtility.getExtensionFunction<GetRenderbufferParameterIV>("glGetRenderbufferParameteriv");

	getStringi = functionUtility.getExtensionFunction<GetStringI>("glGetStringi");
	getTexParameterIiv = functionUtility.getExtensionFunction<GetTexParameterIIV>("glGetTexParameterIiv");
	getTexParameterIuiv = functionUtility.getExtensionFunction<GetTexParameterIUIV>("glGetTexParameterIuiv");

	getTransformFeedbackVarying =
		functionUtility.getExtensionFunction<GetTransformFeedbackVarying>("glGetTransformFeedbackVarying");

	getUniformuiv = functionUtility.getExtensionFunction<GetUniformUIV>("glGetUniformuiv");
	getVertexAttribIiv = functionUtility.getExtensionFunction<GetVertexAttribIIV>("glGetVertexAttribIiv");
	getVertexAttribIuiv = functionUtility.getExtensionFunction<GetVertexAttribIUIV>("glGetVertexAttribIuiv");
	isEnabledi = functionUtility.getExtensionFunction<IsEnabledI>("glIsEnabledi");
	isFramebuffer = functionUtility.getExtensionFunction<IsFramebuffer>("glIsFramebuffer");
	isRenderbuffer = functionUtility.getExtensionFunction<IsRenderbuffer>("glIsRenderbuffer");
	isVertexArray = functionUtility.getExtensionFunction<IsVertexArray>("glIsVertexArray");
	mapBufferRange = functionUtility.getExtensionFunction<MapBufferRange>("glMapBufferRange");
	renderbufferStorage = functionUtility.getExtensionFunction<RenderbufferStorage>("glRenderbufferStorage");

	renderbufferStorageMultisample =
		functionUtility.getExtensionFunction<RenderbufferStorageMultisample>(
			"glRenderbufferStorageMultisample");

	texParameterIiv = functionUtility.getExtensionFunction<TexParameterIIV>("glTexParameterIiv");
	texParameterIuiv = functionUtility.getExtensionFunction<TexParameterIUIV>("glTexParameterIuiv");

	transformFeedbackVaryings =
		functionUtility.getExtensionFunction<TransformFeedbackVaryings>("glTransformFeedbackVaryings");

	uniform1ui = functionUtility.getExtensionFunction<Uniform1UI>("glUniform1ui");
	uniform1uiv = functionUtility.getExtensionFunction<Uniform1UIV>("glUniform1uiv");
	uniform2ui = functionUtility.getExtensionFunction<Uniform2UI>("glUniform2ui");
	uniform2uiv = functionUtility.getExtensionFunction<Uniform2UIV>("glUniform2uiv");
	uniform3ui = functionUtility.getExtensionFunction<Uniform3UI>("glUniform3ui");
	uniform3uiv = functionUtility.getExtensionFunction<Uniform3UIV>("glUniform3uiv");
	uniform4ui = functionUtility.getExtensionFunction<Uniform4UI>("glUniform4ui");
	uniform4uiv = functionUtility.getExtensionFunction<Uniform4UIV>("glUniform4uiv");
	vertexAttribI1i = functionUtility.getExtensionFunction<VertexAttribI1I>("glVertexAttribI1i");
	vertexAttribI1iv = functionUtility.getExtensionFunction<VertexAttribI1IV>("glVertexAttribI1iv");
	vertexAttribI1ui = functionUtility.getExtensionFunction<VertexAttribI1UI>("glVertexAttribI1ui");
	vertexAttribI1uiv = functionUtility.getExtensionFunction<VertexAttribI1UIV>("glVertexAttribI1uiv");
	vertexAttribI2i = functionUtility.getExtensionFunction<VertexAttribI2I>("glVertexAttribI2i");
	vertexAttribI2iv = functionUtility.getExtensionFunction<VertexAttribI2IV>("glVertexAttribI2iv");
	vertexAttribI2ui = functionUtility.getExtensionFunction<VertexAttribI2UI>("glVertexAttribI2ui");
	vertexAttribI2uiv = functionUtility.getExtensionFunction<VertexAttribI2UIV>("glVertexAttribI2uiv");
	vertexAttribI3i = functionUtility.getExtensionFunction<VertexAttribI3I>("glVertexAttribI3i");
	vertexAttribI3iv = functionUtility.getExtensionFunction<VertexAttribI3IV>("glVertexAttribI3iv");
	vertexAttribI3ui = functionUtility.getExtensionFunction<VertexAttribI3UI>("glVertexAttribI3ui");
	vertexAttribI3uiv = functionUtility.getExtensionFunction<VertexAttribI3UIV>("glVertexAttribI3uiv");
	vertexAttribI4bv = functionUtility.getExtensionFunction<VertexAttribI4BV>("glVertexAttribI4bv");
	vertexAttribI4i = functionUtility.getExtensionFunction<VertexAttribI4I>("glVertexAttribI4i");
	vertexAttribI4iv = functionUtility.getExtensionFunction<VertexAttribI4IV>("glVertexAttribI4iv");
	vertexAttribI4sv = functionUtility.getExtensionFunction<VertexAttribI4SV>("glVertexAttribI4sv");
	vertexAttribI4ubv = functionUtility.getExtensionFunction<VertexAttribI4UBV>("glVertexAttribI4ubv");
	vertexAttribI4ui = functionUtility.getExtensionFunction<VertexAttribI4UI>("glVertexAttribI4ui");
	vertexAttribI4uiv = functionUtility.getExtensionFunction<VertexAttribI4UIV>("glVertexAttribI4uiv");
	vertexAttribI4usv = functionUtility.getExtensionFunction<VertexAttribI4USV>("glVertexAttribI4usv");

	vertexAttribIPointer =
		functionUtility.getExtensionFunction<VertexAttribIPointer>("glVertexAttribIPointer");

	// Version 3.1

	copyBufferSubData = functionUtility.getExtensionFunction<CopyBufferSubData>("glCopyBufferSubData");
	drawArraysInstanced = functionUtility.getExtensionFunction<DrawArraysInstanced>("glDrawArraysInstanced");

	drawElementsInstanced =
		functionUtility.getExtensionFunction<DrawElementsInstanced>("glDrawElementsInstanced");

	getActiveUniformBlockiv =
		functionUtility.getExtensionFunction<GetActiveUniformBlockIV>("glGetActiveUniformBlockiv");

	getActiveUniformBlockName =
		functionUtility.getExtensionFunction<GetActiveUniformBlockName>("glGetActiveUniformBlockName");

	getActiveUniformName =
		functionUtility.getExtensionFunction<GetActiveUniformName>("glGetActiveUniformName");

	getActiveUniformsiv = functionUtility.getExtensionFunction<GetActiveUniformsIV>("glGetActiveUniformsiv");

	getUniformBlockIndex =
		functionUtility.getExtensionFunction<GetUniformBlockIndex>("glGetUniformBlockIndex");

	getUniformIndices = functionUtility.getExtensionFunction<GetUniformIndices>("glGetUniformIndices");

	primitiveRestartIndex =
		functionUtility.getExtensionFunction<PrimitiveRestartIndex>("glPrimitiveRestartIndex");

	texBuffer = functionUtility.getExtensionFunction<TexBuffer>("glTexBuffer");
	uniformBlockBinding = functionUtility.getExtensionFunction<UniformBlockBinding>("glUniformBlockBinding");

	// Version 3.2

	clientWaitSync = functionUtility.getExtensionFunction<ClientWaitSync>("glClientWaitSync");
	deleteSync = functionUtility.getExtensionFunction<DeleteSync>("glDeleteSync");

	drawElementsBaseVertex =
		functionUtility.getExtensionFunction<DrawElementsBaseVertex>("glDrawElementsBaseVertex");

	drawElementsInstancedBaseVertex =
		functionUtility.getExtensionFunction<DrawElementsInstancedBaseVertex>(
			"glDrawElementsInstancedBaseVertex");

	drawRangeElementsBaseVertex =
		functionUtility.getExtensionFunction<DrawRangeElementsBaseVertex>("glDrawRangeElementsBaseVertex");

	fenceSync = functionUtility.getExtensionFunction<FenceSync>("glFenceSync");
	framebufferTexture = functionUtility.getExtensionFunction<FramebufferTexture>("glFramebufferTexture");

	getBufferParameteri64v =
		functionUtility.getExtensionFunction<GetBufferParameterI64V>("glGetBufferParameteri64v");

	getInteger64i_v = functionUtility.getExtensionFunction<GetInteger64I_V>("glGetInteger64i_v");
	getInteger64v = functionUtility.getExtensionFunction<GetInteger64V>("glGetInteger64v");
	getMultisamplefv = functionUtility.getExtensionFunction<GetMultisampleFV>("glGetMultisamplefv");
	getSynciv = functionUtility.getExtensionFunction<GetSyncIV>("glGetSynciv");
	isSync = functionUtility.getExtensionFunction<IsSync>("glIsSync");

	multiDrawElementsBaseVertex =
		functionUtility.getExtensionFunction<MultiDrawElementsBaseVertex>("glMultiDrawElementsBaseVertex");

	provokingVertex = functionUtility.getExtensionFunction<ProvokingVertex>("glProvokingVertex");
	sampleMaski = functionUtility.getExtensionFunction<SampleMaskI>("glSampleMaski");

	texImage2DMultisample =
		functionUtility.getExtensionFunction<TexImage2DMultisample>("glTexImage2DMultisample");

	texImage3DMultisample =
		functionUtility.getExtensionFunction<TexImage3DMultisample>("glTexImage3DMultisample");

	waitSync = functionUtility.getExtensionFunction<WaitSync>("glWaitSync");

	// Version 3.3

	bindFragDataLocationIndexed =
		functionUtility.getExtensionFunction<BindFragDataLocationIndexed>("glBindFragDataLocationIndexed");

	bindSampler = functionUtility.getExtensionFunction<BindSampler>("glBindSampler");
	deleteSamplers = functionUtility.getExtensionFunction<DeleteSamplers>("glDeleteSamplers");
	genSamplers = functionUtility.getExtensionFunction<GenSamplers>("glGenSamplers");
	getFragDataIndex = functionUtility.getExtensionFunction<GetFragDataIndex>("glGetFragDataIndex");
	getQueryObjecti64v = functionUtility.getExtensionFunction<GetQueryObjectI64V>("glGetQueryObjecti64v");
	getQueryObjectui64v = functionUtility.getExtensionFunction<GetQueryObjectUI64V>("glGetQueryObjectui64v");

	getSamplerParameterfv =
		functionUtility.getExtensionFunction<GetSamplerParameterFV>("glGetSamplerParameterfv");

	getSamplerParameterIiv =
		functionUtility.getExtensionFunction<GetSamplerParameterIIV>("glGetSamplerParameterIiv");

	getSamplerParameterIuiv =
		functionUtility.getExtensionFunction<GetSamplerParameterIUIV>("glGetSamplerParameterIuiv");

	getSamplerParameteriv =
		functionUtility.getExtensionFunction<GetSamplerParameterIV>("glGetSamplerParameteriv");

	isSampler = functionUtility.getExtensionFunction<IsSampler>("glIsSampler");
	queryCounter = functionUtility.getExtensionFunction<QueryCounter>("glQueryCounter");
	samplerParameterf = functionUtility.getExtensionFunction<SamplerParameterF>("glSamplerParameterf");
	samplerParameterfv = functionUtility.getExtensionFunction<SamplerParameterFV>("glSamplerParameterfv");
	samplerParameteri = functionUtility.getExtensionFunction<SamplerParameterI>("glSamplerParameteri");
	samplerParameteriv = functionUtility.getExtensionFunction<SamplerParameterIV>("glSamplerParameteriv");
	samplerParameterIiv = functionUtility.getExtensionFunction<SamplerParameterIIV>("glSamplerParameterIiv");

	samplerParameterIuiv =
		functionUtility.getExtensionFunction<SamplerParameterIUIV>("glSamplerParameterIuiv");

	vertexAttribDivisor = functionUtility.getExtensionFunction<VertexAttribDivisor>("glVertexAttribDivisor");
	vertexAttribP1ui = functionUtility.getExtensionFunction<VertexAttribP1UI>("glVertexAttribP1ui");
	vertexAttribP1uiv = functionUtility.getExtensionFunction<VertexAttribP1UIV>("glVertexAttribP1uiv");
	vertexAttribP2ui = functionUtility.getExtensionFunction<VertexAttribP2UI>("glVertexAttribP2ui");
	vertexAttribP2uiv = functionUtility.getExtensionFunction<VertexAttribP2UIV>("glVertexAttribP2uiv");
	vertexAttribP3ui = functionUtility.getExtensionFunction<VertexAttribP3UI>("glVertexAttribP3ui");
	vertexAttribP3uiv = functionUtility.getExtensionFunction<VertexAttribP3UIV>("glVertexAttribP3uiv");
	vertexAttribP4ui = functionUtility.getExtensionFunction<VertexAttribP4UI>("glVertexAttribP4ui");
	vertexAttribP4uiv = functionUtility.getExtensionFunction<VertexAttribP4UIV>("glVertexAttribP4uiv");

	if(::versionMajor >= 4u)
	{
		// Version 4.0

		beginQueryIndexed = functionUtility.getExtensionFunction<BeginQueryIndexed>("glBeginQueryIndexed");

		bindTransformFeedback =
			functionUtility.getExtensionFunction<BindTransformFeedback>("glBindTransformFeedback");

		blendEquationi = functionUtility.getExtensionFunction<BlendEquationI>("glBlendEquationi");

		blendEquationSeparatei =
			functionUtility.getExtensionFunction<BlendEquationSeparateI>("glBlendEquationSeparatei");

		blendFunci = functionUtility.getExtensionFunction<BlendFuncI>("glBlendFunci");
		blendFuncSeparatei = functionUtility.getExtensionFunction<BlendFuncSeparateI>("glBlendFuncSeparatei");

		deleteTransformFeedbacks =
			functionUtility.getExtensionFunction<DeleteTransformFeedbacks>("glDeleteTransformFeedbacks");

		drawArraysIndirect = functionUtility.getExtensionFunction<DrawArraysIndirect>("glDrawArraysIndirect");

		drawElementsIndirect =
			functionUtility.getExtensionFunction<DrawElementsIndirect>("glDrawElementsIndirect");

		drawTransformFeedback =
			functionUtility.getExtensionFunction<DrawTransformFeedback>("glDrawTransformFeedback");

		drawTransformFeedbackStream =
			functionUtility.getExtensionFunction<DrawTransformFeedbackStream>(
				"glDrawTransformFeedbackStream");

		endQueryIndexed = functionUtility.getExtensionFunction<EndQueryIndexed>("glEndQueryIndexed");

		genTransformFeedbacks =
			functionUtility.getExtensionFunction<GenTransformFeedbacks>("glGenTransformFeedbacks");

		getActiveSubroutineName =
			functionUtility.getExtensionFunction<GetActiveSubroutineName>("glGetActiveSubroutineName");

		getActiveSubroutineUniformiv =
			functionUtility.getExtensionFunction<GetActiveSubroutineUniformIV>(
				"glGetActiveSubroutineUniformiv");

		getActiveSubroutineUniformName =
			functionUtility.getExtensionFunction<GetActiveSubroutineUniformName>(
				"glGetActiveSubroutineUniformName");

		getProgramStageiv = functionUtility.getExtensionFunction<GetProgramStageIV>("glGetProgramStageiv");
		getQueryIndexediv = functionUtility.getExtensionFunction<GetQueryIndexedIV>("glGetQueryIndexediv");
		getSubroutineIndex = functionUtility.getExtensionFunction<GetSubroutineIndex>("glGetSubroutineIndex");

		getSubroutineUniformLocation =
			functionUtility.getExtensionFunction<GetSubroutineUniformLocation>(
				"glGetSubroutineUniformLocation");

		getUniformdv = functionUtility.getExtensionFunction<GetUniformDV>("glGetUniformdv");

		getUniformSubroutineuiv =
			functionUtility.getExtensionFunction<GetUniformSubroutineUIV>("glGetUniformSubroutineuiv");

		isTransformFeedback =
			functionUtility.getExtensionFunction<IsTransformFeedback>("glIsTransformFeedback");

		minSampleShading = functionUtility.getExtensionFunction<MinSampleShading>("glMinSampleShading");
		patchParameterfv = functionUtility.getExtensionFunction<PatchParameterFV>("glPatchParameterfv");
		patchParameteri = functionUtility.getExtensionFunction<PatchParameterI>("glPatchParameteri");

		pauseTransformFeedback =
			functionUtility.getExtensionFunction<PauseTransformFeedback>("glPauseTransformFeedback");

		resumeTransformFeedback =
			functionUtility.getExtensionFunction<ResumeTransformFeedback>("glResumeTransformFeedback");

		uniform1d = functionUtility.getExtensionFunction<Uniform1D>("glUniform1d");
		uniform1dv = functionUtility.getExtensionFunction<Uniform1DV>("glUniform1dv");
		uniform2d = functionUtility.getExtensionFunction<Uniform2D>("glUniform2d");
		uniform2dv = functionUtility.getExtensionFunction<Uniform2DV>("glUniform2dv");
		uniform3d = functionUtility.getExtensionFunction<Uniform3D>("glUniform3d");
		uniform3dv = functionUtility.getExtensionFunction<Uniform3DV>("glUniform3dv");
		uniform4d = functionUtility.getExtensionFunction<Uniform4D>("glUniform4d");
		uniform4dv = functionUtility.getExtensionFunction<Uniform4DV>("glUniform4dv");
		uniformMatrix2dv = functionUtility.getExtensionFunction<UniformMatrix2DV>("glUniformMatrix2dv");
		uniformMatrix2x3dv = functionUtility.getExtensionFunction<UniformMatrix2X3DV>("glUniformMatrix2x3dv");
		uniformMatrix2x4dv = functionUtility.getExtensionFunction<UniformMatrix2X4DV>("glUniformMatrix2x4dv");
		uniformMatrix3dv = functionUtility.getExtensionFunction<UniformMatrix3DV>("glUniformMatrix3dv");
		uniformMatrix3x2dv = functionUtility.getExtensionFunction<UniformMatrix3X2DV>("glUniformMatrix3x2dv");
		uniformMatrix3x4dv = functionUtility.getExtensionFunction<UniformMatrix3X4DV>("glUniformMatrix3x4dv");
		uniformMatrix4dv = functionUtility.getExtensionFunction<UniformMatrix4DV>("glUniformMatrix4dv");
		uniformMatrix4x2dv = functionUtility.getExtensionFunction<UniformMatrix4X2DV>("glUniformMatrix4x2dv");
		uniformMatrix4x3dv = functionUtility.getExtensionFunction<UniformMatrix4X3DV>("glUniformMatrix4x3dv");

		uniformSubroutinesuiv =
			functionUtility.getExtensionFunction<UniformSubroutineSUIV>("glUniformSubroutinesuiv");

		if(::versionMinor >= 1u)
		{
			// Version 4.1

			activeShaderProgram =
				functionUtility.getExtensionFunction<ActiveShaderProgram>("glActiveShaderProgram");

			bindProgramPipeline =
				functionUtility.getExtensionFunction<BindProgramPipeline>("glBindProgramPipeline");

			clearDepthf = functionUtility.getExtensionFunction<ClearDepthF>("glClearDepthf");

			createShaderProgramv =
				functionUtility.getExtensionFunction<CreateShaderProgramV>("glCreateShaderProgramv");

			deleteProgramPipelines =
				functionUtility.getExtensionFunction<DeleteProgramPipelines>("glDeleteProgramPipelines");

			depthRangeArrayv = functionUtility.getExtensionFunction<DepthRangeArrayV>("glDepthRangeArrayv");
			depthRangef = functionUtility.getExtensionFunction<DepthRangeF>("glDepthRangef");

			depthRangeIndexed =
				functionUtility.getExtensionFunction<DepthRangeIndexed>("glDepthRangeIndexed");

			genProgramPipelines =
				functionUtility.getExtensionFunction<GenProgramPipelines>("glGenProgramPipelines");

			getDoublei_v = functionUtility.getExtensionFunction<GetDoubleI_V>("glGetDoublei_v");
			getFloati_v = functionUtility.getExtensionFunction<GetFloatI_V>("glGetFloati_v");
			getProgramBinary = functionUtility.getExtensionFunction<GetProgramBinary>("glGetProgramBinary");

			getProgramPipelineInfoLog =
				functionUtility.getExtensionFunction<GetProgramPipelineInfoLog>(
					"glGetProgramPipelineInfoLog");

			getProgramPipelineiv =
				functionUtility.getExtensionFunction<GetProgramPipelineIV>("glGetProgramPipelineiv");

			getShaderPrecisionFormat =
				functionUtility.getExtensionFunction<GetShaderPrecisionFormat>("glGetShaderPrecisionFormat");

			getVertexAttribLdv =
				functionUtility.getExtensionFunction<GetVertexAttribLDV>("glGetVertexAttribLdv");

			isProgramPipeline =
				functionUtility.getExtensionFunction<IsProgramPipeline>("glIsProgramPipeline");

			programBinary = functionUtility.getExtensionFunction<ProgramBinary>("glProgramBinary");

			programParameteri =
				functionUtility.getExtensionFunction<ProgramParameterI>("glProgramParameteri");

			programUniform1d = functionUtility.getExtensionFunction<ProgramUniform1D>("glProgramUniform1d");

			programUniform1dv =
				functionUtility.getExtensionFunction<ProgramUniform1DV>("glProgramUniform1dv");

			programUniform1f = functionUtility.getExtensionFunction<ProgramUniform1F>("glProgramUniform1f");

			programUniform1fv =
				functionUtility.getExtensionFunction<ProgramUniform1FV>("glProgramUniform1fv");

			programUniform1i = functionUtility.getExtensionFunction<ProgramUniform1I>("glProgramUniform1i");

			programUniform1iv =
				functionUtility.getExtensionFunction<ProgramUniform1IV>("glProgramUniform1iv");

			programUniform1ui =
				functionUtility.getExtensionFunction<ProgramUniform1UI>("glProgramUniform1ui");

			programUniform1uiv =
				functionUtility.getExtensionFunction<ProgramUniform1UIV>("glProgramUniform1uiv");

			programUniform2d = functionUtility.getExtensionFunction<ProgramUniform2D>("glProgramUniform2d");

			programUniform2dv =
				functionUtility.getExtensionFunction<ProgramUniform2DV>("glProgramUniform2dv");

			programUniform2f = functionUtility.getExtensionFunction<ProgramUniform2F>("glProgramUniform2f");

			programUniform2fv =
				functionUtility.getExtensionFunction<ProgramUniform2FV>("glProgramUniform2fv");

			programUniform2i = functionUtility.getExtensionFunction<ProgramUniform2I>("glProgramUniform2i");

			programUniform2iv =
				functionUtility.getExtensionFunction<ProgramUniform2IV>("glProgramUniform2iv");

			programUniform2ui =
				functionUtility.getExtensionFunction<ProgramUniform2UI>("glProgramUniform2ui");

			programUniform2uiv =
				functionUtility.getExtensionFunction<ProgramUniform2UIV>("glProgramUniform2uiv");

			programUniform3d = functionUtility.getExtensionFunction<ProgramUniform3D>("glProgramUniform3d");

			programUniform3dv =
				functionUtility.getExtensionFunction<ProgramUniform3DV>("glProgramUniform3dv");

			programUniform3f = functionUtility.getExtensionFunction<ProgramUniform3F>("glProgramUniform3f");

			programUniform3fv =
				functionUtility.getExtensionFunction<ProgramUniform3FV>("glProgramUniform3fv");

			programUniform3i = functionUtility.getExtensionFunction<ProgramUniform3I>("glProgramUniform3i");

			programUniform3iv =
				functionUtility.getExtensionFunction<ProgramUniform3IV>("glProgramUniform3iv");

			programUniform3ui =
				functionUtility.getExtensionFunction<ProgramUniform3UI>("glProgramUniform3ui");

			programUniform3uiv =
				functionUtility.getExtensionFunction<ProgramUniform3UIV>("glProgramUniform3uiv");

			programUniform4d = functionUtility.getExtensionFunction<ProgramUniform4D>("glProgramUniform4d");

			programUniform4dv =
				functionUtility.getExtensionFunction<ProgramUniform4DV>("glProgramUniform4dv");

			programUniform4f = functionUtility.getExtensionFunction<ProgramUniform4F>("glProgramUniform4f");

			programUniform4fv =
				functionUtility.getExtensionFunction<ProgramUniform4FV>("glProgramUniform4fv");

			programUniform4i = functionUtility.getExtensionFunction<ProgramUniform4I>("glProgramUniform4i");

			programUniform4iv =
				functionUtility.getExtensionFunction<ProgramUniform4IV>("glProgramUniform4iv");

			programUniform4ui =
				functionUtility.getExtensionFunction<ProgramUniform4UI>("glProgramUniform4ui");

			programUniform4uiv =
				functionUtility.getExtensionFunction<ProgramUniform4UIV>("glProgramUniform4uiv");

			programUniformMatrix2dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2DV>("glProgramUniformMatrix2dv");

			programUniformMatrix2fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2FV>("glProgramUniformMatrix2fv");

			programUniformMatrix2x3dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2X3DV>(
					"glProgramUniformMatrix2x3dv");

			programUniformMatrix2x3fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2X3FV>(
					"glProgramUniformMatrix2x3fv");

			programUniformMatrix2x4dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2X4DV>(
					"glProgramUniformMatrix2x4dv");

			programUniformMatrix2x4fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix2X4FV>(
					"glProgramUniformMatrix2x4fv");

			programUniformMatrix3dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3DV>("glProgramUniformMatrix3dv");

			programUniformMatrix3fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3FV>("glProgramUniformMatrix3fv");

			programUniformMatrix3x2dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3X2DV>(
					"glProgramUniformMatrix3x2dv");

			programUniformMatrix3x2fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3X2FV>(
					"glProgramUniformMatrix3x2fv");

			programUniformMatrix3x4dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3X4DV>(
					"glProgramUniformMatrix3x4dv");

			programUniformMatrix3x4fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix3X4FV>(
					"glProgramUniformMatrix3x4fv");

			programUniformMatrix4dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4DV>("glProgramUniformMatrix4dv");

			programUniformMatrix4fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4FV>("glProgramUniformMatrix4fv");

			programUniformMatrix4x2dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4X2DV>(
					"glProgramUniformMatrix4x2dv");

			programUniformMatrix4x2fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4X2FV>(
					"glProgramUniformMatrix4x2fv");

			programUniformMatrix4x3dv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4X3DV>(
					"glProgramUniformMatrix4x3dv");

			programUniformMatrix4x3fv =
				functionUtility.getExtensionFunction<ProgramUniformMatrix4X3FV>(
					"glProgramUniformMatrix4x3fv");

			releaseShaderCompiler =
				functionUtility.getExtensionFunction<ReleaseShaderCompiler>("glReleaseShaderCompiler");

			shaderBinary = functionUtility.getExtensionFunction<ShaderBinary>("glShaderBinary");
			scissorArrayv = functionUtility.getExtensionFunction<ScissorArrayV>("glScissorArrayv");
			scissorIndexed = functionUtility.getExtensionFunction<ScissorIndexed>("glScissorIndexed");
			scissorIndexedv = functionUtility.getExtensionFunction<ScissorIndexedV>("glScissorIndexedv");
			useProgramStages = functionUtility.getExtensionFunction<UseProgramStages>("glUseProgramStages");

			validateProgramPipeline =
				functionUtility.getExtensionFunction<ValidateProgramPipeline>("glValidateProgramPipeline");

			vertexAttribL1d = functionUtility.getExtensionFunction<VertexAttribL1D>("glVertexAttribL1d");
			vertexAttribL1dv = functionUtility.getExtensionFunction<VertexAttribL1DV>("glVertexAttribL1dv");
			vertexAttribL2d = functionUtility.getExtensionFunction<VertexAttribL2D>("glVertexAttribL2d");
			vertexAttribL2dv = functionUtility.getExtensionFunction<VertexAttribL2DV>("glVertexAttribL2dv");
			vertexAttribL3d = functionUtility.getExtensionFunction<VertexAttribL3D>("glVertexAttribL3d");
			vertexAttribL3dv = functionUtility.getExtensionFunction<VertexAttribL3DV>("glVertexAttribL3dv");
			vertexAttribL4d = functionUtility.getExtensionFunction<VertexAttribL4D>("glVertexAttribL4d");
			vertexAttribL4dv = functionUtility.getExtensionFunction<VertexAttribL4DV>("glVertexAttribL4dv");

			vertexAttribLPointer =
				functionUtility.getExtensionFunction<VertexAttribLPointer>("glVertexAttribLPointer");

			viewportArrayv = functionUtility.getExtensionFunction<ViewportArrayV>("glViewportArrayv");
			viewportIndexedf = functionUtility.getExtensionFunction<ViewportIndexedF>("glViewportIndexedf");

			viewportIndexedfv =
				functionUtility.getExtensionFunction<ViewportIndexedFV>("glViewportIndexedfv");
		}

		if(::versionMinor >= 2u)
		{
			// Version 4.2

			bindImageTexture = functionUtility.getExtensionFunction<BindImageTexture>("glBindImageTexture");

			drawArraysInstancedBaseInstance =
				functionUtility.getExtensionFunction<DrawArraysInstancedBaseInstance>(
					"glDrawArraysInstancedBaseInstance");

			drawElementsInstancedBaseInstance =
				functionUtility.getExtensionFunction<DrawElementsInstancedBaseInstance>(
					"glDrawElementsInstancedBaseInstance");

			drawElementsInstancedBaseVertexBaseInstance =
				functionUtility.getExtensionFunction<DrawElementsInstancedBaseVertexBaseInstance>(
					"glDrawElementsInstancedBaseVertexBaseInstance");

			drawTransformFeedbackInstanced =
				functionUtility.getExtensionFunction<DrawTransformFeedbackInstanced>(
					"glDrawTransformFeedbackInstanced");

			drawTransformFeedbackStreamInstanced =
				functionUtility.getExtensionFunction<DrawTransformFeedbackStreamInstanced>(
					"glDrawTransformFeedbackStreamInstanced");

			getActiveAtomicCounterBufferiv =
				functionUtility.getExtensionFunction<GetActiveAtomicCounterBufferIV>(
					"glGetActiveAtomicCounterBufferiv");

			getInternalformativ =
				functionUtility.getExtensionFunction<GetInternalformatIV>("glGetInternalformativ");

			memoryBarrier = functionUtility.getExtensionFunction<MemoryBarrier>("glMemoryBarrier");
			texStorage1D = functionUtility.getExtensionFunction<TexStorage1D>("glTexStorage1D");
			texStorage2D = functionUtility.getExtensionFunction<TexStorage2D>("glTexStorage2D");
			texStorage3D = functionUtility.getExtensionFunction<TexStorage3D>("glTexStorage3D");
		}

		if(::versionMinor >= 3u)
		{
			// Version 4.3

			bindVertexBuffer = functionUtility.getExtensionFunction<BindVertexBuffer>("glBindVertexBuffer");
			clearBufferData = functionUtility.getExtensionFunction<ClearBufferData>("glClearBufferData");

			clearBufferSubData =
				functionUtility.getExtensionFunction<ClearBufferSubData>("glClearBufferSubData");

			copyImageSubData = functionUtility.getExtensionFunction<CopyImageSubData>("glCopyImageSubData");
			dispatchCompute = functionUtility.getExtensionFunction<DispatchCompute>("glDispatchCompute");

			dispatchComputeIndirect =
				functionUtility.getExtensionFunction<DispatchComputeIndirect>("glDispatchComputeIndirect");

			debugMessageCallback =
				functionUtility.getExtensionFunction<DebugMessageCallback>("glDebugMessageCallback");

			debugMessageControl =
				functionUtility.getExtensionFunction<DebugMessageControl>("glDebugMessageControl");

			debugMessageInsert =
				functionUtility.getExtensionFunction<DebugMessageInsert>("glDebugMessageInsert");

			framebufferParameteri =
				functionUtility.getExtensionFunction<FramebufferParameterI>("glFramebufferParameteri");

			getDebugMessageLog =
				functionUtility.getExtensionFunction<GetDebugMessageLog>("glGetDebugMessageLog");

			getFramebufferParameteriv =
				functionUtility.getExtensionFunction<GetFramebufferParameterIV>(
					"glGetFramebufferParameteriv");

			getInternalformati64v =
				functionUtility.getExtensionFunction<GetInternalformatI64V>("glGetInternalformati64v");

			getObjectLabel = functionUtility.getExtensionFunction<GetObjectLabel>("glGetObjectLabel");

			getObjectPtrLabel =
				functionUtility.getExtensionFunction<GetObjectPtrLabel>("glGetObjectPtrLabel");

			getProgramInterfaceiv =
				functionUtility.getExtensionFunction<GetProgramInterfaceIV>("glGetProgramInterfaceiv");

			getProgramResourceIndex =
				functionUtility.getExtensionFunction<GetProgramResourceIndex>("glGetProgramResourceIndex");

			getProgramResourceiv =
				functionUtility.getExtensionFunction<GetProgramResourceIV>("glGetProgramResourceiv");

			getProgramResourceLocation =
				functionUtility.getExtensionFunction<GetProgramResourceLocation>(
					"glGetProgramResourceLocation");

			getProgramResourceLocationIndex =
				functionUtility.getExtensionFunction<GetProgramResourceLocationIndex>(
					"glGetProgramResourceLocationIndex");

			getProgramResourceName =
				functionUtility.getExtensionFunction<GetProgramResourceName>("glGetProgramResourceName");

			invalidateBufferData =
				functionUtility.getExtensionFunction<InvalidateBufferData>("glInvalidateBufferData");

			invalidateBufferSubData =
				functionUtility.getExtensionFunction<InvalidateBufferSubData>("glInvalidateBufferSubData");

			invalidateFramebuffer =
				functionUtility.getExtensionFunction<InvalidateFramebuffer>("glInvalidateFramebuffer");

			invalidateSubFramebuffer =
				functionUtility.getExtensionFunction<InvalidateSubFramebuffer>("glInvalidateSubFramebuffer");

			invalidateTexImage =
				functionUtility.getExtensionFunction<InvalidateTexImage>("glInvalidateTexImage");

			invalidateTexSubImage =
				functionUtility.getExtensionFunction<InvalidateTexSubImage>("glInvalidateTexSubImage");

			multiDrawArraysIndirect =
				functionUtility.getExtensionFunction<MultiDrawArraysIndirect>("glMultiDrawArraysIndirect");

			multiDrawElementsIndirect =
				functionUtility.getExtensionFunction<MultiDrawElementsIndirect>(
					"glMultiDrawElementsIndirect");

			objectLabel = functionUtility.getExtensionFunction<ObjectLabel>("glObjectLabel");
			objectPtrLabel = functionUtility.getExtensionFunction<ObjectPtrLabel>("glObjectPtrLabel");
			popDebugGroup = functionUtility.getExtensionFunction<PopDebugGroup>("glPopDebugGroup");
			pushDebugGroup = functionUtility.getExtensionFunction<PushDebugGroup>("glPushDebugGroup");

			shaderStorageBlockBinding =
				functionUtility.getExtensionFunction<ShaderStorageBlockBinding>(
					"glShaderStorageBlockBinding");

			texBufferRange = functionUtility.getExtensionFunction<TexBufferRange>("glTexBufferRange");

			texStorage2DMultisample =
				functionUtility.getExtensionFunction<TexStorage2DMultisample>("glTexStorage2DMultisample");

			texStorage3DMultisample =
				functionUtility.getExtensionFunction<TexStorage3DMultisample>("glTexStorage3DMultisample");

			textureView = functionUtility.getExtensionFunction<TextureView>("glTextureView");

			vertexAttribBinding =
				functionUtility.getExtensionFunction<VertexAttribBinding>("glVertexAttribBinding");

			vertexAttribFormat =
				functionUtility.getExtensionFunction<VertexAttribFormat>("glVertexAttribFormat");

			vertexAttribIFormat =
				functionUtility.getExtensionFunction<VertexAttribIFormat>("glVertexAttribIFormat");

			vertexAttribLFormat =
				functionUtility.getExtensionFunction<VertexAttribLFormat>("glVertexAttribLFormat");

			vertexBindingDivisor =
				functionUtility.getExtensionFunction<VertexBindingDivisor>("glVertexBindingDivisor");
		}

		if(::versionMinor >= 4u)
		{
			// Version 4.4

			bindBuffersBase = functionUtility.getExtensionFunction<BindBuffersBase>("glBindBuffersBase");
			bindBuffersRange = functionUtility.getExtensionFunction<BindBuffersRange>("glBindBuffersRange");

			bindImageTextures =
				functionUtility.getExtensionFunction<BindImageTextures>("glBindImageTextures");

			bindSamplers = functionUtility.getExtensionFunction<BindSamplers>("glBindSamplers");
			bindTextures = functionUtility.getExtensionFunction<BindTextures>("glBindTextures");

			bindVertexBuffers =
				functionUtility.getExtensionFunction<BindVertexBuffers>("glBindVertexBuffers");

			bufferStorage = functionUtility.getExtensionFunction<BufferStorage>("glBufferStorage");
			clearTexImage = functionUtility.getExtensionFunction<ClearTexImage>("glClearTexImage");
			clearTexSubImage = functionUtility.getExtensionFunction<ClearTexSubImage>("glClearTexSubImage");
		}

		if(::versionMinor >= 5u)
		{
			// Version 4.5

			bindTextureUnit = functionUtility.getExtensionFunction<BindTextureUnit>("glBindTextureUnit");

			blitNamedFramebuffer =
				functionUtility.getExtensionFunction<BlitNamedFramebuffer>("glBlitNamedFramebuffer");

			checkNamedFramebufferStatus =
				functionUtility.getExtensionFunction<CheckNamedFramebufferStatus>(
					"glCheckNamedFramebufferStatus");

			clearNamedBufferData =
				functionUtility.getExtensionFunction<ClearNamedBufferData>("glClearNamedBufferData");

			clearNamedBufferSubData =
				functionUtility.getExtensionFunction<ClearNamedBufferSubData>("glClearNamedBufferSubData");

			clearNamedFramebufferfi =
				functionUtility.getExtensionFunction<ClearNamedFramebufferFI>("glClearNamedFramebufferfi");

			clearNamedFramebufferfv =
				functionUtility.getExtensionFunction<ClearNamedFramebufferFV>("glClearNamedFramebufferfv");

			clearNamedFramebufferiv =
				functionUtility.getExtensionFunction<ClearNamedFramebufferIV>("glClearNamedFramebufferiv");

			clearNamedFramebufferuiv =
				functionUtility.getExtensionFunction<ClearNamedFramebufferUIV>("glClearNamedFramebufferuiv");

			clipControl = functionUtility.getExtensionFunction<ClipControl>("glClipControl");

			compressedTextureSubImage1D =
				functionUtility.getExtensionFunction<CompressedTextureSubImage1D>(
					"glCompressedTextureSubImage1D");

			compressedTextureSubImage2D =
				functionUtility.getExtensionFunction<CompressedTextureSubImage2D>(
					"glCompressedTextureSubImage2D");

			compressedTextureSubImage3D =
				functionUtility.getExtensionFunction<CompressedTextureSubImage3D>(
					"glCompressedTextureSubImage3D");

			copyNamedBufferSubData =
				functionUtility.getExtensionFunction<CopyNamedBufferSubData>("glCopyNamedBufferSubData");

			copyTextureSubImage1D =
				functionUtility.getExtensionFunction<CopyTextureSubImage1D>("glCopyTextureSubImage1D");

			copyTextureSubImage2D =
				functionUtility.getExtensionFunction<CopyTextureSubImage2D>("glCopyTextureSubImage2D");

			copyTextureSubImage3D =
				functionUtility.getExtensionFunction<CopyTextureSubImage3D>("glCopyTextureSubImage3D");

			createBuffers = functionUtility.getExtensionFunction<CreateBuffers>("glCreateBuffers");

			createFramebuffers =
				functionUtility.getExtensionFunction<CreateFramebuffers>("glCreateFramebuffers");

			createProgramPipelines =
				functionUtility.getExtensionFunction<CreateProgramPipelines>("glCreateProgramPipelines");

			createQueries = functionUtility.getExtensionFunction<CreateQueries>("glCreateQueries");

			createRenderbuffers =
				functionUtility.getExtensionFunction<CreateRenderbuffers>("glCreateRenderbuffers");

			createSamplers = functionUtility.getExtensionFunction<CreateSamplers>("glCreateSamplers");
			createTextures = functionUtility.getExtensionFunction<CreateTextures>("glCreateTextures");

			createTransformFeedbacks =
				functionUtility.getExtensionFunction<CreateTransformFeedbacks>("glCreateTransformFeedbacks");

			createVertexArrays =
				functionUtility.getExtensionFunction<CreateVertexArrays>("glCreateVertexArrays");

			disableVertexArrayAttrib =
				functionUtility.getExtensionFunction<DisableVertexArrayAttrib>("glDisableVertexArrayAttrib");

			enableVertexArrayAttrib =
				functionUtility.getExtensionFunction<EnableVertexArrayAttrib>("glEnableVertexArrayAttrib");

			flushMappedNamedBufferRange =
				functionUtility.getExtensionFunction<FlushMappedNamedBufferRange>(
					"glFlushMappedNamedBufferRange");

			generateTextureMipmap =
				functionUtility.getExtensionFunction<GenerateTextureMipmap>("glGenerateTextureMipmap");

			getCompressedTextureImage =
				functionUtility.getExtensionFunction<GetCompressedTextureImage>(
					"glGetCompressedTextureImage");

			getCompressedTextureSubImage =
				functionUtility.getExtensionFunction<GetCompressedTextureSubImage>(
					"glGetCompressedTextureSubImage");

			getGraphicsResetStatus =
				functionUtility.getExtensionFunction<GetGraphicsResetStatus>("glGetGraphicsResetStatus");

			getNamedBufferParameteri64v =
				functionUtility.getExtensionFunction<GetNamedBufferParameterI64V>(
					"glGetNamedBufferParameteri64v");

			getNamedBufferParameteriv =
				functionUtility.getExtensionFunction<GetNamedBufferParameterIV>(
					"glGetNamedBufferParameteriv");

			getNamedBufferPointerv =
				functionUtility.getExtensionFunction<GetNamedBufferPointerV>("glGetNamedBufferPointerv");

			getNamedBufferSubData =
				functionUtility.getExtensionFunction<GetNamedBufferSubData>("glGetNamedBufferSubData");

			getNamedFramebufferAttachmentParameteriv =
				functionUtility.getExtensionFunction<GetNamedFramebufferAttachmentParameterIV>(
					"glGetNamedFramebufferAttachmentParameteriv");

			getNamedFramebufferParameteriv =
				functionUtility.getExtensionFunction<GetNamedFramebufferParameterIV>(
					"glGetNamedFramebufferParameteriv");

			getNamedRenderbufferParameteriv =
				functionUtility.getExtensionFunction<GetNamedRenderbufferParameterIV>(
					"glGetNamedRenderbufferParameteriv");

			getnCompressedTexImage =
				functionUtility.getExtensionFunction<GetnCompressedTexImage>("glGetnCompressedTexImage");

			getnTexImage = functionUtility.getExtensionFunction<GetnTexImage>("glGetnTexImage");
			getnUniformdv = functionUtility.getExtensionFunction<GetnUniformDV>("glGetnUniformdv");
			getnUniformfv = functionUtility.getExtensionFunction<GetnUniformFV>("glGetnUniformfv");
			getnUniformiv = functionUtility.getExtensionFunction<GetnUniformIV>("glGetnUniformiv");
			getnUniformuiv = functionUtility.getExtensionFunction<GetnUniformUIV>("glGetnUniformuiv");

			getQueryBufferObjecti64v =
				functionUtility.getExtensionFunction<GetQueryBufferObjectI64V>("glGetQueryBufferObjecti64v");

			getQueryBufferObjectiv =
				functionUtility.getExtensionFunction<GetQueryBufferObjectIV>("glGetQueryBufferObjectiv");

			getQueryBufferObjectui64v =
				functionUtility.getExtensionFunction<GetQueryBufferObjectUI64V>(
					"glGetQueryBufferObjectui64v");

			getQueryBufferObjectuiv =
				functionUtility.getExtensionFunction<GetQueryBufferObjectUIV>("glGetQueryBufferObjectuiv");

			getTextureImage = functionUtility.getExtensionFunction<GetTextureImage>("glGetTextureImage");

			getTextureLevelParameterfv =
				functionUtility.getExtensionFunction<GetTextureLevelParameterFV>(
					"glGetTextureLevelParameterfv");

			getTextureLevelParameteriv =
				functionUtility.getExtensionFunction<GetTextureLevelParameterIV>(
					"glGetTextureLevelParameteriv");

			getTextureParameterfv =
				functionUtility.getExtensionFunction<GetTextureParameterFV>("glGetTextureParameterfv");

			getTextureParameterIiv =
				functionUtility.getExtensionFunction<GetTextureParameterIIV>("glGetTextureParameterIiv");

			getTextureParameteriv =
				functionUtility.getExtensionFunction<GetTextureParameterIV>("glGetTextureParameteriv");

			getTextureParameterIuiv =
				functionUtility.getExtensionFunction<GetTextureParameterIUIV>("glGetTextureParameterIuiv");

			getTextureSubImage =
				functionUtility.getExtensionFunction<GetTextureSubImage>("glGetTextureSubImage");

			getTransformFeedbacki64_v =
				functionUtility.getExtensionFunction<GetTransformFeedbackI64_V>(
					"glGetTransformFeedbacki64_v");

			getTransformFeedbackiv =
				functionUtility.getExtensionFunction<GetTransformFeedbackIV>("glGetTransformFeedbackiv");

			getTransformFeedbacki_v =
				functionUtility.getExtensionFunction<GetTransformFeedbackI_V>("glGetTransformFeedbacki_v");

			getVertexArrayIndexed64iv =
				functionUtility.getExtensionFunction<GetVertexArrayIndexed64IV>(
					"glGetVertexArrayIndexed64iv");

			getVertexArrayIndexediv =
				functionUtility.getExtensionFunction<GetVertexArrayIndexedIV>("glGetVertexArrayIndexediv");

			getVertexArrayiv = functionUtility.getExtensionFunction<GetVertexArrayIV>("glGetVertexArrayiv");

			invalidateNamedFramebufferData =
				functionUtility.getExtensionFunction<InvalidateNamedFramebufferData>(
					"glInvalidateNamedFramebufferData");

			invalidateNamedFramebufferSubData =
				functionUtility.getExtensionFunction<InvalidateNamedFramebufferSubData>(
					"glInvalidateNamedFramebufferSubData");

			mapNamedBuffer = functionUtility.getExtensionFunction<MapNamedBuffer>("glMapNamedBuffer");

			mapNamedBufferRange =
				functionUtility.getExtensionFunction<MapNamedBufferRange>("glMapNamedBufferRange");

			memoryBarrierByRegion =
				functionUtility.getExtensionFunction<MemoryBarrierByRegion>("glMemoryBarrierByRegion");

			namedBufferData = functionUtility.getExtensionFunction<NamedBufferData>("glNamedBufferData");

			namedBufferStorage =
				functionUtility.getExtensionFunction<NamedBufferStorage>("glNamedBufferStorage");

			namedBufferSubData =
				functionUtility.getExtensionFunction<NamedBufferSubData>("glNamedBufferSubData");

			namedFramebufferDrawBuffer =
				functionUtility.getExtensionFunction<NamedFramebufferDrawBuffer>(
					"glNamedFramebufferDrawBuffer");

			namedFramebufferDrawBuffers =
				functionUtility.getExtensionFunction<NamedFramebufferDrawBuffers>(
					"glNamedFramebufferDrawBuffers");

			namedFramebufferParameteri =
				functionUtility.getExtensionFunction<NamedFramebufferParameterI>(
					"glNamedFramebufferParameteri");

			namedFramebufferReadBuffer =
				functionUtility.getExtensionFunction<NamedFramebufferReadBuffer>(
					"glNamedFramebufferReadBuffer");

			namedFramebufferRenderbuffer =
				functionUtility.getExtensionFunction<NamedFramebufferRenderbuffer>(
					"glNamedFramebufferRenderbuffer");

			namedFramebufferTexture =
				functionUtility.getExtensionFunction<NamedFramebufferTexture>("glNamedFramebufferTexture");

			namedFramebufferTextureLayer =
				functionUtility.getExtensionFunction<NamedFramebufferTextureLayer>(
					"glNamedFramebufferTextureLayer");

			namedRenderbufferStorage =
				functionUtility.getExtensionFunction<NamedRenderbufferStorage>("glNamedRenderbufferStorage");

			namedRenderbufferStorageMultisample =
				functionUtility.getExtensionFunction<NamedRenderbufferStorageMultisample>(
					"glNamedRenderbufferStorageMultisample");

			readnPixels = functionUtility.getExtensionFunction<ReadnPixels>("glReadnPixels");

			transformFeedbackBufferBase =
				functionUtility.getExtensionFunction<TransformFeedbackBufferBase>(
					"glTransformFeedbackBufferBase");

			transformFeedbackBufferRange =
				functionUtility.getExtensionFunction<TransformFeedbackBufferRange>(
					"glTransformFeedbackBufferRange");

			textureBarrier = functionUtility.getExtensionFunction<TextureBarrier>("glTextureBarrier");
			textureBuffer = functionUtility.getExtensionFunction<TextureBuffer>("glTextureBuffer");

			textureBufferRange =
				functionUtility.getExtensionFunction<TextureBufferRange>("glTextureBufferRange");

			textureParameterf =
				functionUtility.getExtensionFunction<TextureParameterF>("glTextureParameterf");

			textureParameterfv =
				functionUtility.getExtensionFunction<TextureParameterFV>("glTextureParameterfv");

			textureParameteri =
				functionUtility.getExtensionFunction<TextureParameterI>("glTextureParameteri");

			textureParameterIiv =
				functionUtility.getExtensionFunction<TextureParameterIIV>("glTextureParameterIiv");

			textureParameterIuiv =
				functionUtility.getExtensionFunction<TextureParameterIUIV>("glTextureParameterIuiv");

			textureParameteriv =
				functionUtility.getExtensionFunction<TextureParameterIV>("glTextureParameteriv");

			textureStorage1D = functionUtility.getExtensionFunction<TextureStorage1D>("glTextureStorage1D");
			textureStorage2D = functionUtility.getExtensionFunction<TextureStorage2D>("glTextureStorage2D");

			textureStorage2DMultisample =
				functionUtility.getExtensionFunction<TextureStorage2DMultisample>(
					"glTextureStorage2DMultisample");

			textureStorage3D = functionUtility.getExtensionFunction<TextureStorage3D>("glTextureStorage3D");

			textureStorage3DMultisample =
				functionUtility.getExtensionFunction<TextureStorage3DMultisample>(
					"glTextureStorage3DMultisample");

			textureSubImage1D =
				functionUtility.getExtensionFunction<TextureSubImage1D>("glTextureSubImage1D");

			textureSubImage2D =
				functionUtility.getExtensionFunction<TextureSubImage2D>("glTextureSubImage2D");

			textureSubImage3D =
				functionUtility.getExtensionFunction<TextureSubImage3D>("glTextureSubImage3D");

			unmapNamedBuffer = functionUtility.getExtensionFunction<UnmapNamedBuffer>("glUnmapNamedBuffer");

			vertexArrayAttribBinding =
				functionUtility.getExtensionFunction<VertexArrayAttribBinding>("glVertexArrayAttribBinding");

			vertexArrayAttribFormat =
				functionUtility.getExtensionFunction<VertexArrayAttribFormat>("glVertexArrayAttribFormat");

			vertexArrayAttribIFormat =
				functionUtility.getExtensionFunction<VertexArrayAttribIFormat>("glVertexArrayAttribIFormat");

			vertexArrayAttribLFormat =
				functionUtility.getExtensionFunction<VertexArrayAttribLFormat>("glVertexArrayAttribLFormat");

			vertexArrayBindingDivisor =
				functionUtility.getExtensionFunction<VertexArrayBindingDivisor>(
					"glVertexArrayBindingDivisor");

			vertexArrayElementBuffer =
				functionUtility.getExtensionFunction<VertexArrayElementBuffer>("glVertexArrayElementBuffer");

			vertexArrayVertexBuffer =
				functionUtility.getExtensionFunction<VertexArrayVertexBuffer>("glVertexArrayVertexBuffer");

			vertexArrayVertexBuffers =
				functionUtility.getExtensionFunction<VertexArrayVertexBuffers>("glVertexArrayVertexBuffers");
		}
	}
}

void OpenGL::initialiseDebugMessaging() const
{
	enable(DEBUG_OUTPUT_SYNCHRONOUS);
	DE_CHECK_ERROR_OPENGL(this);
	debugMessageControl(DONT_CARE, DEBUG_TYPE_OTHER, DONT_CARE, 0, nullptr, FALSE);
	DE_CHECK_ERROR_OPENGL(this);
	debugMessageCallback(::processDebugMessage, nullptr);
}

ExtensionNameList OpenGL::getExtensionNames() const
{
	Int32 extensionCount = 0u;
	getIntegerv(OpenGL::NUM_EXTENSIONS, &extensionCount);
	DE_CHECK_ERROR_OPENGL(this);
	ExtensionNameList extensionNames;

	for(Int32 i = 0; i < extensionCount; ++i)
	{
		const Char8* extensionName = reinterpret_cast<const Char8*>(getStringi(OpenGL::EXTENSIONS, i));
		DE_CHECK_ERROR_OPENGL(this);
		extensionNames.push_back(extensionName);
	}

	return extensionNames;
}


// External

static LogLevel getDebugMessageLogLevel(const Uint32 messageSeverity)
{
	switch(messageSeverity)
	{
		case OpenGL::DEBUG_SEVERITY_NOTIFICATION:
			return LogLevel::Info;

		case OpenGL::DEBUG_SEVERITY_HIGH:
			return LogLevel::Error;

		case OpenGL::DEBUG_SEVERITY_MEDIUM:
		case OpenGL::DEBUG_SEVERITY_LOW:
			return LogLevel::Warning;

		default:
			return LogLevel::Debug;
	}
}

static const Char8* getDebugMessageTypeName(const Uint32 messageType)
{
	switch(messageType)
	{
		case OpenGL::DEBUG_TYPE_ERROR:
			return ::DEBUG_MESSAGE_TYPE_NAMES[1];

		case OpenGL::DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return ::DEBUG_MESSAGE_TYPE_NAMES[0];

		case OpenGL::DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return ::DEBUG_MESSAGE_TYPE_NAMES[8];

		case OpenGL::DEBUG_TYPE_PORTABILITY:
			return ::DEBUG_MESSAGE_TYPE_NAMES[7];

		case OpenGL::DEBUG_TYPE_PERFORMANCE:
			return ::DEBUG_MESSAGE_TYPE_NAMES[6];

		case OpenGL::DEBUG_TYPE_OTHER:
			return ::DEBUG_MESSAGE_TYPE_NAMES[5];

		case OpenGL::DEBUG_TYPE_MARKER:
			return ::DEBUG_MESSAGE_TYPE_NAMES[4];

		case OpenGL::DEBUG_TYPE_PUSH_GROUP:
			return ::DEBUG_MESSAGE_TYPE_NAMES[3];

		case OpenGL::DEBUG_TYPE_POP_GROUP:
			return ::DEBUG_MESSAGE_TYPE_NAMES[2];

		default:
			return ::DEBUG_MESSAGE_TYPE_NAMES[9];
	}
}

static void initialiseMajorVersion(const String8& versionString)
{
	const Uint32 delimiterPosition = versionString.find('.');
	::versionMajor = std::strtol(versionString.substr(0u, delimiterPosition).c_str(), nullptr, 10);
}

static void initialiseMinorVersion(const String8& versionString)
{
	const Uint32 minorPosition = versionString.find('.') + 1u;
	const Uint32 secondDelimiterPosition = versionString.find('.', minorPosition);
	Uint32 versionEndPosition = versionString.find(' ', minorPosition);

	if(secondDelimiterPosition < versionEndPosition)
		versionEndPosition = secondDelimiterPosition;

	const String8 minorString = versionString.substr(minorPosition, versionEndPosition - minorPosition);
	::versionMinor = std::strtol(minorString.c_str(), nullptr, 10);
}

static void DE_CALL_OPENGL processDebugMessage(const Uint32 messageSource, const Uint32 messageType,
	const Uint32 messageId, const Uint32 messageSeverity, const Int32 messageLength, const Char8* message,
	const Void* userData)
{
	static_cast<Void>(messageLength);
	static_cast<Void>(userData);

	const Char8* messageSourceName = ::DEBUG_MESSAGE_SOURCE_NAMES[messageSource - OpenGL::DEBUG_SOURCE_API];

	defaultLog << ::getDebugMessageLogLevel(messageSeverity) << ::COMPONENT_TAG << ' ' <<
		::getDebugMessageTypeName(messageType) << " message (" << StreamFormat::Hexadecimal << messageId <<
		StreamFormat::Decimal << ") from " << messageSourceName << ": '" << message << '\'' << Log::Flush();
}

static void reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function)
{
	defaultLog << LogLevel::Warning << "OpenGL error occurred, " << ::ERROR_NAMES[OpenGL::INVALID_ENUM - errorCode] <<
		" (" << StreamFormat::Hexadecimal << errorCode << StreamFormat::Decimal << ") at " << file << ", on line " <<
		line << ", in function " << function << '.' << Log::Flush();
}
