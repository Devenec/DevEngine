/**
 * @file platform/opengl/OpenGL.cpp
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
 * along with DevEngine. If not, see <http:  //www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <core/Array.h>
#include <core/Log.h>
#include <core/debug/Assert.h>
#include <graphics/LogUtility.h>
#include <platform/GraphicsExtensionHelper.h>
#include <platform/opengl/OpenGL.h>

using namespace Core;
using namespace Graphics;
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

static const Array<const Char8*, 9u> DEBUG_MESSAGE_TYPE_NAMES
{{
	"Deprecated behaviour",
	"Error",
	"Group pop",
	"Group push",
	"Marker",
	"Other",
	"Performance",
	"Portability",
	"Undefined behaviour"
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

static Uint32 majorVersion = 1u;
static Uint32 minorVersion = 1u;

static LogLevel getDebugMessageLogLevel(const Uint32 messageSeverity);
static const Char8* getDebugMessageTypeName(const Uint32 messageType);
static void getStandardFunctions(OpenGL& openGL);
static void initialiseDebugMessaging(OpenGL& openGL);
static void initialiseMajorVersion(const String8& versionString);
static void initialiseMinorVersion(const String8& versionString);

static void DE_CALL_OPENGL processDebugMessage(const Uint32 messageSource, const Uint32 messageType,
	const Uint32 messageId, const Uint32 messageSeverity, const Int32 messageLength, const Char8* message,
	const Void* userData);

static void reportError(const Uint32 errorCode, const Char8* file, const Uint32 line, const Char8* function);


// Public

OpenGL::OpenGL()

	  // Version 1.0

	: blendFunc(glBlendFunc),
	  clear(glClear),
	  clearColor(glClearColor),
	  clearDepth(glClearDepth),
	  clearStencil(glClearStencil),
	  colorMask(glColorMask),
	  cullFace(glCullFace),
	  depthFunc(glDepthFunc),
	  depthMask(glDepthMask),
	  depthRange(glDepthRange),
	  disable(glDisable),
	  drawBuffer(glDrawBuffer),
	  enable(glEnable),
	  finish(glFinish),
	  flush(glFlush),
	  frontFace(glFrontFace),
	  getBooleanv(glGetBooleanv),
	  getDoublev(glGetDoublev),
	  getError(glGetError),
	  getFloatv(glGetFloatv),
	  getIntegerv(glGetIntegerv),
	  getString(glGetString),
	  getTexImage(glGetTexImage),
	  getTexLevelParameterfv(glGetTexLevelParameterfv),
	  getTexLevelParameteriv(glGetTexLevelParameteriv),
	  getTexParameterfv(glGetTexParameterfv),
	  getTexParameteriv(glGetTexParameteriv),
	  hint(glHint),
	  isEnabled(glIsEnabled),
	  lineWidth(glLineWidth),
	  logicOp(glLogicOp),
	  pixelStoref(glPixelStoref),
	  pixelStorei(glPixelStorei),
	  pointSize(glPointSize),
	  polygonMode(glPolygonMode),
	  readBuffer(glReadBuffer),
	  readPixels(glReadPixels),
	  scissor(glScissor),
	  stencilFunc(glStencilFunc),
	  stencilMask(glStencilMask),
	  stencilOp(glStencilOp),
	  texImage1D(glTexImage1D),
	  texImage2D(glTexImage2D),
	  texParameterf(glTexParameterf),
	  texParameterfv(glTexParameterfv),
	  texParameteri(glTexParameteri),
	  texParameteriv(glTexParameteriv),
	  viewport(glViewport),

	  // Version 1.1

	  bindTexture(glBindTexture),
	  copyTexImage1D(glCopyTexImage1D),
	  copyTexImage2D(glCopyTexImage2D),
	  copyTexSubImage1D(glCopyTexSubImage1D),
	  copyTexSubImage2D(glCopyTexSubImage2D),
	  deleteTextures(glDeleteTextures),
	  drawArrays(glDrawArrays),
	  drawElements(glDrawElements),
	  genTextures(glGenTextures),
	  getPointerv(glGetPointerv),
	  isTexture(glIsTexture),
	  polygonOffset(glPolygonOffset),
	  texSubImage1D(glTexSubImage1D),
	  texSubImage2D(glTexSubImage2D)
{
	// TODO: check current context state?
	::getStandardFunctions(*this);

	if(debugMessageCallback != nullptr)
		::initialiseDebugMessaging(*this);
}

void OpenGL::checkForErrors(const Char8* file, const Uint32 line, const Char8* function) const
{
	Uint32 errorCode;

	while((errorCode = getError()) != NO_ERROR)
		::reportError(errorCode, file, line, function);
}

void OpenGL::logExtensions() const
{
	logGraphicsExtensions("graphics interface", getExtensionNames());
}

// Static

void OpenGL::initialiseVersion(Uint32& major, Uint32& minor)
{
	const String8 versionString(reinterpret_cast<const Char8*>(glGetString(VERSION)));
	::initialiseMajorVersion(versionString);
	::initialiseMinorVersion(versionString);
	major = ::majorVersion;
	minor = ::minorVersion;
}

// Private

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
			DE_ASSERT(false);
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
			DE_ASSERT(false);
			return ::DEBUG_MESSAGE_TYPE_NAMES[0];
	}
}

static void getStandardFunctions(OpenGL& openGL)
{
	// Version 1.2

	openGL.copyTexSubImage3D = GraphicsExtensionHelper::getFunction<OpenGL::CopyTexSubImage3D>("glCopyTexSubImage3D");
	openGL.drawRangeElements = GraphicsExtensionHelper::getFunction<OpenGL::DrawRangeElements>("glDrawRangeElements");
	openGL.texImage3D = GraphicsExtensionHelper::getFunction<OpenGL::TexImage3D>("glTexImage3D");
	openGL.texSubImage3D = GraphicsExtensionHelper::getFunction<OpenGL::TexSubImage3D>("glTexSubImage3D");

	// Version 1.3

	openGL.activeTexture = GraphicsExtensionHelper::getFunction<OpenGL::ActiveTexture>("glActiveTexture");

	openGL.compressedTexImage1D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexImage1D>("glCompressedTexImage1D");

	openGL.compressedTexImage2D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexImage2D>("glCompressedTexImage2D");

	openGL.compressedTexImage3D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexImage3D>("glCompressedTexImage3D");

	openGL.compressedTexSubImage1D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexSubImage1D>("glCompressedTexSubImage1D");

	openGL.compressedTexSubImage2D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexSubImage2D>("glCompressedTexSubImage2D");

	openGL.compressedTexSubImage3D =
		GraphicsExtensionHelper::getFunction<OpenGL::CompressedTexSubImage3D>("glCompressedTexSubImage3D");

	openGL.getCompressedTexImage =
		GraphicsExtensionHelper::getFunction<OpenGL::GetCompressedTexImage>("glGetCompressedTexImage");

	openGL.sampleCoverage = GraphicsExtensionHelper::getFunction<OpenGL::SampleCoverage>("glSampleCoverage");

	// Version 1.4

	openGL.blendColor = GraphicsExtensionHelper::getFunction<OpenGL::BlendColor>("glBlendColor");
	openGL.blendEquation = GraphicsExtensionHelper::getFunction<OpenGL::BlendEquation>("glBlendEquation");
	openGL.blendFuncSeparate = GraphicsExtensionHelper::getFunction<OpenGL::BlendFuncSeparate>("glBlendFuncSeparate");
	openGL.multiDrawArrays = GraphicsExtensionHelper::getFunction<OpenGL::MultiDrawArrays>("glMultiDrawArrays");
	openGL.multiDrawElements = GraphicsExtensionHelper::getFunction<OpenGL::MultiDrawElements>("glMultiDrawElements");
	openGL.pointParameterf = GraphicsExtensionHelper::getFunction<OpenGL::PointParameterF>("glPointParameterf");
	openGL.pointParameterfv = GraphicsExtensionHelper::getFunction<OpenGL::PointParameterFV>("glPointParameterfv");
	openGL.pointParameteri = GraphicsExtensionHelper::getFunction<OpenGL::PointParameterI>("glPointParameteri");
	openGL.pointParameteriv = GraphicsExtensionHelper::getFunction<OpenGL::PointParameterIV>("glPointParameteriv");

	// Version 1.5

	openGL.beginQuery = GraphicsExtensionHelper::getFunction<OpenGL::BeginQuery>("glBeginQuery");
	openGL.bindBuffer = GraphicsExtensionHelper::getFunction<OpenGL::BindBuffer>("glBindBuffer");
	openGL.bufferData = GraphicsExtensionHelper::getFunction<OpenGL::BufferData>("glBufferData");
	openGL.bufferSubData = GraphicsExtensionHelper::getFunction<OpenGL::BufferSubData>("glBufferSubData");
	openGL.deleteBuffers = GraphicsExtensionHelper::getFunction<OpenGL::DeleteBuffers>("glDeleteBuffers");
	openGL.deleteQueries = GraphicsExtensionHelper::getFunction<OpenGL::DeleteQueries>("glDeleteQueries");
	openGL.endQuery = GraphicsExtensionHelper::getFunction<OpenGL::EndQuery>("glEndQuery");
	openGL.genBuffers = GraphicsExtensionHelper::getFunction<OpenGL::GenBuffers>("glGenBuffers");
	openGL.genQueries = GraphicsExtensionHelper::getFunction<OpenGL::GenQueries>("glGenQueries");

	openGL.getBufferParameteriv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetBufferParameterIV>("glGetBufferParameteriv");

	openGL.getBufferPointerv = GraphicsExtensionHelper::getFunction<OpenGL::GetBufferPointerV>("glGetBufferPointerv");
	openGL.getBufferSubData = GraphicsExtensionHelper::getFunction<OpenGL::GetBufferSubData>("glGetBufferSubData");
	openGL.getQueryiv = GraphicsExtensionHelper::getFunction<OpenGL::GetQueryIV>("glGetQueryiv");
	openGL.getQueryObjectiv = GraphicsExtensionHelper::getFunction<OpenGL::GetQueryObjectIV>("glGetQueryObjectiv");
	openGL.getQueryObjectuiv = GraphicsExtensionHelper::getFunction<OpenGL::GetQueryObjectUIV>("glGetQueryObjectuiv");
	openGL.isBuffer = GraphicsExtensionHelper::getFunction<OpenGL::IsBuffer>("glIsBuffer");
	openGL.isQuery = GraphicsExtensionHelper::getFunction<OpenGL::IsQuery>("glIsQuery");
	openGL.mapBuffer = GraphicsExtensionHelper::getFunction<OpenGL::MapBuffer>("glMapBuffer");
	openGL.unmapBuffer = GraphicsExtensionHelper::getFunction<OpenGL::UnmapBuffer>("glUnmapBuffer");

	// Version 2.0

	openGL.attachShader = GraphicsExtensionHelper::getFunction<OpenGL::AttachShader>("glAttachShader");

	openGL.bindAttribLocation =
		GraphicsExtensionHelper::getFunction<OpenGL::BindAttribLocation>("glBindAttribLocation");

	openGL.blendEquationSeparate =
		GraphicsExtensionHelper::getFunction<OpenGL::BlendEquationSeparate>("glBlendEquationSeparate");

	openGL.compileShader = GraphicsExtensionHelper::getFunction<OpenGL::CompileShader>("glCompileShader");
	openGL.createProgram = GraphicsExtensionHelper::getFunction<OpenGL::CreateProgram>("glCreateProgram");
	openGL.createShader = GraphicsExtensionHelper::getFunction<OpenGL::CreateShader>("glCreateShader");
	openGL.deleteProgram = GraphicsExtensionHelper::getFunction<OpenGL::DeleteProgram>("glDeleteProgram");
	openGL.deleteShader = GraphicsExtensionHelper::getFunction<OpenGL::DeleteShader>("glDeleteShader");
	openGL.detachShader = GraphicsExtensionHelper::getFunction<OpenGL::DetachShader>("glDetachShader");

	openGL.disableVertexAttribArray =	
		GraphicsExtensionHelper::getFunction<OpenGL::DisableVertexAttribArray>("glDisableVertexAttribArray");

	openGL.drawBuffers = GraphicsExtensionHelper::getFunction<OpenGL::DrawBuffers>("glDrawBuffers");

	openGL.enableVertexAttribArray =
		GraphicsExtensionHelper::getFunction<OpenGL::EnableVertexAttribArray>("glEnableVertexAttribArray");

	openGL.getActiveAttrib = GraphicsExtensionHelper::getFunction<OpenGL::GetActiveAttrib>("glGetActiveAttrib");
	openGL.getActiveUniform = GraphicsExtensionHelper::getFunction<OpenGL::GetActiveUniform>("glGetActiveUniform");

	openGL.getAttachedShaders =
		GraphicsExtensionHelper::getFunction<OpenGL::GetAttachedShaders>("glGetAttachedShaders");

	openGL.getAttribLocation = GraphicsExtensionHelper::getFunction<OpenGL::GetAttribLocation>("glGetAttribLocation");
	openGL.getProgramInfoLog = GraphicsExtensionHelper::getFunction<OpenGL::GetProgramInfoLog>("glGetProgramInfoLog");
	openGL.getProgramiv = GraphicsExtensionHelper::getFunction<OpenGL::GetProgramIV>("glGetProgramiv");
	openGL.getShaderInfoLog = GraphicsExtensionHelper::getFunction<OpenGL::GetShaderInfoLog>("glGetShaderInfoLog");
	openGL.getShaderiv = GraphicsExtensionHelper::getFunction<OpenGL::GetShaderIV>("glGetShaderiv");
	openGL.getShaderSource = GraphicsExtensionHelper::getFunction<OpenGL::GetShaderSource>("glGetShaderSource");
	openGL.getUniformfv = GraphicsExtensionHelper::getFunction<OpenGL::GetUniformFV>("glGetUniformfv");
	openGL.getUniformiv = GraphicsExtensionHelper::getFunction<OpenGL::GetUniformIV>("glGetUniformiv");

	openGL.getUniformLocation =
		GraphicsExtensionHelper::getFunction<OpenGL::GetUniformLocation>("glGetUniformLocation");

	openGL.getVertexAttribdv = GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribDV>("glGetVertexAttribdv");
	openGL.getVertexAttribfv = GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribFV>("glGetVertexAttribfv");
	openGL.getVertexAttribiv = GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribIV>("glGetVertexAttribiv");

	openGL.getVertexAttribPointerv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribPointerV>("glGetVertexAttribPointerv");

	openGL.isProgram = GraphicsExtensionHelper::getFunction<OpenGL::IsProgram>("glIsProgram");
	openGL.isShader = GraphicsExtensionHelper::getFunction<OpenGL::IsShader>("glIsShader");
	openGL.linkProgram = GraphicsExtensionHelper::getFunction<OpenGL::LinkProgram>("glLinkProgram");
	openGL.shaderSource = GraphicsExtensionHelper::getFunction<OpenGL::ShaderSource>("glShaderSource");

	openGL.stencilFuncSeparate =
		GraphicsExtensionHelper::getFunction<OpenGL::StencilFuncSeparate>("glStencilFuncSeparate");

	openGL.stencilMaskSeparate =
		GraphicsExtensionHelper::getFunction<OpenGL::StencilMaskSeparate>("glStencilMaskSeparate");

	openGL.stencilOpSeparate = GraphicsExtensionHelper::getFunction<OpenGL::StencilOpSeparate>("glStencilOpSeparate");
	openGL.uniform1f = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1F>("glUniform1f");
	openGL.uniform1fv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1FV>("glUniform1fv");
	openGL.uniform1i = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1I>("glUniform1i");
	openGL.uniform1iv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1IV>("glUniform1iv");
	openGL.uniform2f = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2F>("glUniform2f");
	openGL.uniform2fv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2FV>("glUniform2fv");
	openGL.uniform2i = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2I>("glUniform2i");
	openGL.uniform2iv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2IV>("glUniform2iv");
	openGL.uniform3f = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3F>("glUniform3f");
	openGL.uniform3fv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3FV>("glUniform3fv");
	openGL.uniform3i = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3I>("glUniform3i");
	openGL.uniform3iv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3IV>("glUniform3iv");
	openGL.uniform4f = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4F>("glUniform4f");
	openGL.uniform4fv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4FV>("glUniform4fv");
	openGL.uniform4i = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4I>("glUniform4i");
	openGL.uniform4iv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4IV>("glUniform4iv");
	openGL.uniformMatrix2fv = GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2FV>("glUniformMatrix2fv");
	openGL.uniformMatrix3fv = GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3FV>("glUniformMatrix3fv");
	openGL.uniformMatrix4fv = GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4FV>("glUniformMatrix4fv");
	openGL.useProgram = GraphicsExtensionHelper::getFunction<OpenGL::UseProgram>("glUseProgram");
	openGL.validateProgram = GraphicsExtensionHelper::getFunction<OpenGL::ValidateProgram>("glValidateProgram");
	openGL.vertexAttrib1d = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1D>("glVertexAttrib1d");
	openGL.vertexAttrib1dv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1DV>("glVertexAttrib1dv");
	openGL.vertexAttrib1f = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1F>("glVertexAttrib1f");
	openGL.vertexAttrib1fv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1FV>("glVertexAttrib1fv");
	openGL.vertexAttrib1s = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1S>("glVertexAttrib1s");
	openGL.vertexAttrib1sv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib1SV>("glVertexAttrib1sv");
	openGL.vertexAttrib2d = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2D>("glVertexAttrib2d");
	openGL.vertexAttrib2dv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2DV>("glVertexAttrib2dv");
	openGL.vertexAttrib2f = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2F>("glVertexAttrib2f");
	openGL.vertexAttrib2fv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2FV>("glVertexAttrib2fv");
	openGL.vertexAttrib2s = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2S>("glVertexAttrib2s");
	openGL.vertexAttrib2sv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib2SV>("glVertexAttrib2sv");
	openGL.vertexAttrib3d = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3D>("glVertexAttrib3d");
	openGL.vertexAttrib3dv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3DV>("glVertexAttrib3dv");
	openGL.vertexAttrib3f = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3F>("glVertexAttrib3f");
	openGL.vertexAttrib3fv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3FV>("glVertexAttrib3fv");
	openGL.vertexAttrib3s = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3S>("glVertexAttrib3s");
	openGL.vertexAttrib3sv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib3SV>("glVertexAttrib3sv");
	openGL.vertexAttrib4bv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4BV>("glVertexAttrib4bv");
	openGL.vertexAttrib4d = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4D>("glVertexAttrib4d");
	openGL.vertexAttrib4dv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4DV>("glVertexAttrib4dv");
	openGL.vertexAttrib4f = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4F>("glVertexAttrib4f");
	openGL.vertexAttrib4fv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4FV>("glVertexAttrib4fv");
	openGL.vertexAttrib4iv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4IV>("glVertexAttrib4iv");
	openGL.vertexAttrib4Nbv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NBV>("glVertexAttrib4Nbv");
	openGL.vertexAttrib4Niv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NIV>("glVertexAttrib4Niv");
	openGL.vertexAttrib4Nsv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NSV>("glVertexAttrib4Nsv");
	openGL.vertexAttrib4Nub = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NUB>("glVertexAttrib4Nub");
	openGL.vertexAttrib4Nubv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NUBV>("glVertexAttrib4Nubv");
	openGL.vertexAttrib4Nuiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NUIV>("glVertexAttrib4Nuiv");
	openGL.vertexAttrib4Nusv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4NUSV>("glVertexAttrib4Nusv");
	openGL.vertexAttrib4s = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4S>("glVertexAttrib4s");
	openGL.vertexAttrib4sv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4SV>("glVertexAttrib4sv");
	openGL.vertexAttrib4ubv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4UBV>("glVertexAttrib4ubv");
	openGL.vertexAttrib4uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4UIV>("glVertexAttrib4uiv");
	openGL.vertexAttrib4usv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttrib4USV>("glVertexAttrib4usv");

	openGL.vertexAttribPointer =
		GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribPointer>("glVertexAttribPointer");

	// Version 2.1

	openGL.uniformMatrix2x3fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2X3FV>("glUniformMatrix2x3fv");

	openGL.uniformMatrix2x4fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2X4FV>("glUniformMatrix2x4fv");

	openGL.uniformMatrix3x2fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3X2FV>("glUniformMatrix3x2fv");

	openGL.uniformMatrix3x4fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3X4FV>("glUniformMatrix3x4fv");

	openGL.uniformMatrix4x2fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4X2FV>("glUniformMatrix4x2fv");

	openGL.uniformMatrix4x3fv =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4X3FV>("glUniformMatrix4x3fv");

	// Version 3.0

	openGL.beginConditionalRender =
		GraphicsExtensionHelper::getFunction<OpenGL::BeginConditionalRender>("glBeginConditionalRender");

	openGL.beginTransformFeedback =
		GraphicsExtensionHelper::getFunction<OpenGL::BeginTransformFeedback>("glBeginTransformFeedback");

	openGL.bindBufferBase = GraphicsExtensionHelper::getFunction<OpenGL::BindBufferBase>("glBindBufferBase");
	openGL.bindBufferRange = GraphicsExtensionHelper::getFunction<OpenGL::BindBufferRange>("glBindBufferRange");

	openGL.bindFragDataLocation =
		GraphicsExtensionHelper::getFunction<OpenGL::BindFragDataLocation>("glBindFragDataLocation");

	openGL.bindFramebuffer = GraphicsExtensionHelper::getFunction<OpenGL::BindFramebuffer>("glBindFramebuffer");
	openGL.bindRenderbuffer = GraphicsExtensionHelper::getFunction<OpenGL::BindRenderbuffer>("glBindRenderbuffer");
	openGL.bindVertexArray = GraphicsExtensionHelper::getFunction<OpenGL::BindVertexArray>("glBindVertexArray");
	openGL.blitFramebuffer = GraphicsExtensionHelper::getFunction<OpenGL::BlitFramebuffer>("glBlitFramebuffer");

	openGL.checkFramebufferStatus =
		GraphicsExtensionHelper::getFunction<OpenGL::CheckFramebufferStatus>("glCheckFramebufferStatus");

	openGL.clampColor = GraphicsExtensionHelper::getFunction<OpenGL::ClampColor>("glClampColor");
	openGL.clearBufferfi = GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferFI>("glClearBufferfi");
	openGL.clearBufferfv = GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferFV>("glClearBufferfv");
	openGL.clearBufferiv = GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferIV>("glClearBufferiv");
	openGL.clearBufferuiv = GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferUIV>("glClearBufferuiv");
	openGL.colorMaski = GraphicsExtensionHelper::getFunction<OpenGL::ColorMaskI>("glColorMaski");

	openGL.deleteFramebuffers =
		GraphicsExtensionHelper::getFunction<OpenGL::DeleteFramebuffers>("glDeleteFramebuffers");

	openGL.deleteRenderbuffers =
		GraphicsExtensionHelper::getFunction<OpenGL::DeleteRenderbuffers>("glDeleteRenderbuffers");

	openGL.deleteVertexArrays =
		GraphicsExtensionHelper::getFunction<OpenGL::DeleteVertexArrays>("glDeleteVertexArrays");

	openGL.disablei = GraphicsExtensionHelper::getFunction<OpenGL::DisableI>("glDisablei");
	openGL.enablei = GraphicsExtensionHelper::getFunction<OpenGL::EnableI>("glEnablei");

	openGL.endConditionalRender =
		GraphicsExtensionHelper::getFunction<OpenGL::EndConditionalRender>("glEndConditionalRender");

	openGL.endTransformFeedback =
		GraphicsExtensionHelper::getFunction<OpenGL::EndTransformFeedback>("glEndTransformFeedback");

	openGL.flushMappedBufferRange =
		GraphicsExtensionHelper::getFunction<OpenGL::FlushMappedBufferRange>("glFlushMappedBufferRange");

	openGL.framebufferRenderbuffer =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferRenderbuffer>("glFramebufferRenderbuffer");

	openGL.framebufferTexture1D =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferTexture1D>("glFramebufferTexture1D");

	openGL.framebufferTexture2D =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferTexture2D>("glFramebufferTexture2D");

	openGL.framebufferTexture3D =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferTexture3D>("glFramebufferTexture3D");

	openGL.framebufferTextureLayer =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferTextureLayer>("glFramebufferTextureLayer");

	openGL.generateMipmap = GraphicsExtensionHelper::getFunction<OpenGL::GenerateMipmap>("glGenerateMipmap");
	openGL.genFramebuffers = GraphicsExtensionHelper::getFunction<OpenGL::GenFramebuffers>("glGenFramebuffers");
	openGL.genRenderbuffers = GraphicsExtensionHelper::getFunction<OpenGL::GenRenderbuffers>("glGenRenderbuffers");
	openGL.genVertexArrays = GraphicsExtensionHelper::getFunction<OpenGL::GenVertexArrays>("glGenVertexArrays");
	openGL.getBooleani_v = GraphicsExtensionHelper::getFunction<OpenGL::GetBooleanI_V>("glGetBooleani_v");

	openGL.getFragDataLocation =
		GraphicsExtensionHelper::getFunction<OpenGL::GetFragDataLocation>("glGetFragDataLocation");

	openGL.getFramebufferAttachmentParameteriv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetFramebufferAttachmentParameterIV>(
			"glGetFramebufferAttachmentParameteriv");

	openGL.getIntegeri_v = GraphicsExtensionHelper::getFunction<OpenGL::GetIntegerI_V>("glGetIntegeri_v");

	openGL.getRenderbufferParameteriv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetRenderbufferParameterIV>("glGetRenderbufferParameteriv");

	openGL.getStringi = GraphicsExtensionHelper::getFunction<OpenGL::GetStringI>("glGetStringi");

	openGL.getTexParameterIiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetTexParameterIIV>("glGetTexParameterIiv");

	openGL.getTexParameterIuiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetTexParameterIUIV>("glGetTexParameterIuiv");

	openGL.getTransformFeedbackVarying =
		GraphicsExtensionHelper::getFunction<OpenGL::GetTransformFeedbackVarying>("glGetTransformFeedbackVarying");

	openGL.getUniformuiv = GraphicsExtensionHelper::getFunction<OpenGL::GetUniformUIV>("glGetUniformuiv");

	openGL.getVertexAttribIiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribIIV>("glGetVertexAttribIiv");

	openGL.getVertexAttribIuiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribIUIV>("glGetVertexAttribIuiv");

	openGL.isEnabledi = GraphicsExtensionHelper::getFunction<OpenGL::IsEnabledI>("glIsEnabledi");
	openGL.isFramebuffer = GraphicsExtensionHelper::getFunction<OpenGL::IsFramebuffer>("glIsFramebuffer");
	openGL.isRenderbuffer = GraphicsExtensionHelper::getFunction<OpenGL::IsRenderbuffer>("glIsRenderbuffer");
	openGL.isVertexArray = GraphicsExtensionHelper::getFunction<OpenGL::IsVertexArray>("glIsVertexArray");
	openGL.mapBufferRange = GraphicsExtensionHelper::getFunction<OpenGL::MapBufferRange>("glMapBufferRange");

	openGL.renderbufferStorage =
		GraphicsExtensionHelper::getFunction<OpenGL::RenderbufferStorage>("glRenderbufferStorage");

	openGL.renderbufferStorageMultisample =
		GraphicsExtensionHelper::getFunction<OpenGL::RenderbufferStorageMultisample>(
			"glRenderbufferStorageMultisample");

	openGL.texParameterIiv = GraphicsExtensionHelper::getFunction<OpenGL::TexParameterIIV>("glTexParameterIiv");
	openGL.texParameterIuiv = GraphicsExtensionHelper::getFunction<OpenGL::TexParameterIUIV>("glTexParameterIuiv");

	openGL.transformFeedbackVaryings =
		GraphicsExtensionHelper::getFunction<OpenGL::TransformFeedbackVaryings>("glTransformFeedbackVaryings");

	openGL.uniform1ui = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1UI>("glUniform1ui");
	openGL.uniform1uiv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1UIV>("glUniform1uiv");
	openGL.uniform2ui = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2UI>("glUniform2ui");
	openGL.uniform2uiv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2UIV>("glUniform2uiv");
	openGL.uniform3ui = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3UI>("glUniform3ui");
	openGL.uniform3uiv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3UIV>("glUniform3uiv");
	openGL.uniform4ui = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4UI>("glUniform4ui");
	openGL.uniform4uiv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4UIV>("glUniform4uiv");
	openGL.vertexAttribI1i = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI1I>("glVertexAttribI1i");
	openGL.vertexAttribI1iv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI1IV>("glVertexAttribI1iv");
	openGL.vertexAttribI1ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI1UI>("glVertexAttribI1ui");
	openGL.vertexAttribI1uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI1UIV>("glVertexAttribI1uiv");
	openGL.vertexAttribI2i = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI2I>("glVertexAttribI2i");
	openGL.vertexAttribI2iv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI2IV>("glVertexAttribI2iv");
	openGL.vertexAttribI2ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI2UI>("glVertexAttribI2ui");
	openGL.vertexAttribI2uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI2UIV>("glVertexAttribI2uiv");
	openGL.vertexAttribI3i = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI3I>("glVertexAttribI3i");
	openGL.vertexAttribI3iv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI3IV>("glVertexAttribI3iv");
	openGL.vertexAttribI3ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI3UI>("glVertexAttribI3ui");
	openGL.vertexAttribI3uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI3UIV>("glVertexAttribI3uiv");
	openGL.vertexAttribI4bv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4BV>("glVertexAttribI4bv");
	openGL.vertexAttribI4i = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4I>("glVertexAttribI4i");
	openGL.vertexAttribI4iv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4IV>("glVertexAttribI4iv");
	openGL.vertexAttribI4sv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4SV>("glVertexAttribI4sv");
	openGL.vertexAttribI4ubv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4UBV>("glVertexAttribI4ubv");
	openGL.vertexAttribI4ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4UI>("glVertexAttribI4ui");
	openGL.vertexAttribI4uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4UIV>("glVertexAttribI4uiv");
	openGL.vertexAttribI4usv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribI4USV>("glVertexAttribI4usv");

	openGL.vertexAttribIPointer =
		GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribIPointer>("glVertexAttribIPointer");

	// Version 3.1

	openGL.copyBufferSubData = GraphicsExtensionHelper::getFunction<OpenGL::CopyBufferSubData>("glCopyBufferSubData");

	openGL.drawArraysInstanced =
		GraphicsExtensionHelper::getFunction<OpenGL::DrawArraysInstanced>("glDrawArraysInstanced");

	openGL.drawElementsInstanced =
		GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsInstanced>("glDrawElementsInstanced");

	openGL.getActiveUniformBlockiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetActiveUniformBlockIV>("glGetActiveUniformBlockiv");

	openGL.getActiveUniformBlockName =
		GraphicsExtensionHelper::getFunction<OpenGL::GetActiveUniformBlockName>("glGetActiveUniformBlockName");

	openGL.getActiveUniformName =
		GraphicsExtensionHelper::getFunction<OpenGL::GetActiveUniformName>("glGetActiveUniformName");

	openGL.getActiveUniformsiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetActiveUniformsIV>("glGetActiveUniformsiv");

	openGL.getUniformBlockIndex =
		GraphicsExtensionHelper::getFunction<OpenGL::GetUniformBlockIndex>("glGetUniformBlockIndex");

	openGL.getUniformIndices = GraphicsExtensionHelper::getFunction<OpenGL::GetUniformIndices>("glGetUniformIndices");

	openGL.primitiveRestartIndex =
		GraphicsExtensionHelper::getFunction<OpenGL::PrimitiveRestartIndex>("glPrimitiveRestartIndex");

	openGL.texBuffer = GraphicsExtensionHelper::getFunction<OpenGL::TexBuffer>("glTexBuffer");

	openGL.uniformBlockBinding =
		GraphicsExtensionHelper::getFunction<OpenGL::UniformBlockBinding>("glUniformBlockBinding");

	// Version 3.2

	openGL.clientWaitSync = GraphicsExtensionHelper::getFunction<OpenGL::ClientWaitSync>("glClientWaitSync");
	openGL.deleteSync = GraphicsExtensionHelper::getFunction<OpenGL::DeleteSync>("glDeleteSync");

	openGL.drawElementsBaseVertex =
		GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsBaseVertex>("glDrawElementsBaseVertex");

	openGL.drawElementsInstancedBaseVertex =
		GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsInstancedBaseVertex>(
			"glDrawElementsInstancedBaseVertex");

	openGL.drawRangeElementsBaseVertex =
		GraphicsExtensionHelper::getFunction<OpenGL::DrawRangeElementsBaseVertex>("glDrawRangeElementsBaseVertex");

	openGL.fenceSync = GraphicsExtensionHelper::getFunction<OpenGL::FenceSync>("glFenceSync");

	openGL.framebufferTexture =
		GraphicsExtensionHelper::getFunction<OpenGL::FramebufferTexture>("glFramebufferTexture");

	openGL.getBufferParameteri64v =
		GraphicsExtensionHelper::getFunction<OpenGL::GetBufferParameterI64V>("glGetBufferParameteri64v");

	openGL.getInteger64i_v = GraphicsExtensionHelper::getFunction<OpenGL::GetInteger64I_V>("glGetInteger64i_v");
	openGL.getInteger64v = GraphicsExtensionHelper::getFunction<OpenGL::GetInteger64V>("glGetInteger64v");
	openGL.getMultisamplefv = GraphicsExtensionHelper::getFunction<OpenGL::GetMultisampleFV>("glGetMultisamplefv");
	openGL.getSynciv = GraphicsExtensionHelper::getFunction<OpenGL::GetSyncIV>("glGetSynciv");
	openGL.isSync = GraphicsExtensionHelper::getFunction<OpenGL::IsSync>("glIsSync");

	openGL.multiDrawElementsBaseVertex =
		GraphicsExtensionHelper::getFunction<OpenGL::MultiDrawElementsBaseVertex>("glMultiDrawElementsBaseVertex");

	openGL.provokingVertex = GraphicsExtensionHelper::getFunction<OpenGL::ProvokingVertex>("glProvokingVertex");
	openGL.sampleMaski = GraphicsExtensionHelper::getFunction<OpenGL::SampleMaskI>("glSampleMaski");

	openGL.texImage2DMultisample =
		GraphicsExtensionHelper::getFunction<OpenGL::TexImage2DMultisample>("glTexImage2DMultisample");

	openGL.texImage3DMultisample =
		GraphicsExtensionHelper::getFunction<OpenGL::TexImage3DMultisample>("glTexImage3DMultisample");

	openGL.waitSync = GraphicsExtensionHelper::getFunction<OpenGL::WaitSync>("glWaitSync");

	// Version 3.3

	openGL.bindFragDataLocationIndexed =
		GraphicsExtensionHelper::getFunction<OpenGL::BindFragDataLocationIndexed>("glBindFragDataLocationIndexed");

	openGL.bindSampler = GraphicsExtensionHelper::getFunction<OpenGL::BindSampler>("glBindSampler");
	openGL.deleteSamplers = GraphicsExtensionHelper::getFunction<OpenGL::DeleteSamplers>("glDeleteSamplers");
	openGL.genSamplers = GraphicsExtensionHelper::getFunction<OpenGL::GenSamplers>("glGenSamplers");
	openGL.getFragDataIndex = GraphicsExtensionHelper::getFunction<OpenGL::GetFragDataIndex>("glGetFragDataIndex");

	openGL.getQueryObjecti64v =
		GraphicsExtensionHelper::getFunction<OpenGL::GetQueryObjectI64V>("glGetQueryObjecti64v");

	openGL.getQueryObjectui64v =
		GraphicsExtensionHelper::getFunction<OpenGL::GetQueryObjectUI64V>("glGetQueryObjectui64v");

	openGL.getSamplerParameterfv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetSamplerParameterFV>("glGetSamplerParameterfv");

	openGL.getSamplerParameterIiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetSamplerParameterIIV>("glGetSamplerParameterIiv");

	openGL.getSamplerParameterIuiv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetSamplerParameterIUIV>("glGetSamplerParameterIuiv");

	openGL.getSamplerParameteriv =
		GraphicsExtensionHelper::getFunction<OpenGL::GetSamplerParameterIV>("glGetSamplerParameteriv");

	openGL.isSampler = GraphicsExtensionHelper::getFunction<OpenGL::IsSampler>("glIsSampler");
	openGL.queryCounter = GraphicsExtensionHelper::getFunction<OpenGL::QueryCounter>("glQueryCounter");
	openGL.samplerParameterf = GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterF>("glSamplerParameterf");

	openGL.samplerParameterfv =
		GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterFV>("glSamplerParameterfv");

	openGL.samplerParameteri = GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterI>("glSamplerParameteri");

	openGL.samplerParameteriv =
		GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterIV>("glSamplerParameteriv");

	openGL.samplerParameterIiv =
		GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterIIV>("glSamplerParameterIiv");

	openGL.samplerParameterIuiv =
		GraphicsExtensionHelper::getFunction<OpenGL::SamplerParameterIUIV>("glSamplerParameterIuiv");

	openGL.vertexAttribDivisor =
		GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribDivisor>("glVertexAttribDivisor");

	openGL.vertexAttribP1ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP1UI>("glVertexAttribP1ui");
	openGL.vertexAttribP1uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP1UIV>("glVertexAttribP1uiv");
	openGL.vertexAttribP2ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP2UI>("glVertexAttribP2ui");
	openGL.vertexAttribP2uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP2UIV>("glVertexAttribP2uiv");
	openGL.vertexAttribP3ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP3UI>("glVertexAttribP3ui");
	openGL.vertexAttribP3uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP3UIV>("glVertexAttribP3uiv");
	openGL.vertexAttribP4ui = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP4UI>("glVertexAttribP4ui");
	openGL.vertexAttribP4uiv = GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribP4UIV>("glVertexAttribP4uiv");

	if(::majorVersion >= 4u)
	{
		if(::minorVersion >= 0u)
		{
			// Version 4.0

			openGL.beginQueryIndexed =
				GraphicsExtensionHelper::getFunction<OpenGL::BeginQueryIndexed>("glBeginQueryIndexed");

			openGL.bindTransformFeedback =
				GraphicsExtensionHelper::getFunction<OpenGL::BindTransformFeedback>("glBindTransformFeedback");

			openGL.blendEquationi = GraphicsExtensionHelper::getFunction<OpenGL::BlendEquationI>("glBlendEquationi");

			openGL.blendEquationSeparatei =
				GraphicsExtensionHelper::getFunction<OpenGL::BlendEquationSeparateI>("glBlendEquationSeparatei");

			openGL.blendFunci = GraphicsExtensionHelper::getFunction<OpenGL::BlendFuncI>("glBlendFunci");

			openGL.blendFuncSeparatei =
				GraphicsExtensionHelper::getFunction<OpenGL::BlendFuncSeparateI>("glBlendFuncSeparatei");

			openGL.deleteTransformFeedbacks =
				GraphicsExtensionHelper::getFunction<OpenGL::DeleteTransformFeedbacks>("glDeleteTransformFeedbacks");

			openGL.drawArraysIndirect =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawArraysIndirect>("glDrawArraysIndirect");

			openGL.drawElementsIndirect =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsIndirect>("glDrawElementsIndirect");

			openGL.drawTransformFeedback =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawTransformFeedback>("glDrawTransformFeedback");

			openGL.drawTransformFeedbackStream =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawTransformFeedbackStream>(
					"glDrawTransformFeedbackStream");

			openGL.endQueryIndexed =
				GraphicsExtensionHelper::getFunction<OpenGL::EndQueryIndexed>("glEndQueryIndexed");

			openGL.genTransformFeedbacks =
				GraphicsExtensionHelper::getFunction<OpenGL::GenTransformFeedbacks>("glGenTransformFeedbacks");

			openGL.getActiveSubroutineName =
				GraphicsExtensionHelper::getFunction<OpenGL::GetActiveSubroutineName>("glGetActiveSubroutineName");

			openGL.getActiveSubroutineUniformiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetActiveSubroutineUniformIV>(
					"glGetActiveSubroutineUniformiv");

			openGL.getActiveSubroutineUniformName =
				GraphicsExtensionHelper::getFunction<OpenGL::GetActiveSubroutineUniformName>(
					"glGetActiveSubroutineUniformName");

			openGL.getProgramStageiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramStageIV>("glGetProgramStageiv");

			openGL.getQueryIndexediv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetQueryIndexedIV>("glGetQueryIndexediv");

			openGL.getSubroutineIndex =
				GraphicsExtensionHelper::getFunction<OpenGL::GetSubroutineIndex>("glGetSubroutineIndex");

			openGL.getSubroutineUniformLocation =
				GraphicsExtensionHelper::getFunction<OpenGL::GetSubroutineUniformLocation>(
					"glGetSubroutineUniformLocation");

			openGL.getUniformdv = GraphicsExtensionHelper::getFunction<OpenGL::GetUniformDV>("glGetUniformdv");

			openGL.getUniformSubroutineuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetUniformSubroutineUIV>("glGetUniformSubroutineuiv");

			openGL.isTransformFeedback =
				GraphicsExtensionHelper::getFunction<OpenGL::IsTransformFeedback>("glIsTransformFeedback");

			openGL.minSampleShading =
				GraphicsExtensionHelper::getFunction<OpenGL::MinSampleShading>("glMinSampleShading");

			openGL.patchParameterfv =
				GraphicsExtensionHelper::getFunction<OpenGL::PatchParameterFV>("glPatchParameterfv");

			openGL.patchParameteri =
				GraphicsExtensionHelper::getFunction<OpenGL::PatchParameterI>("glPatchParameteri");

			openGL.pauseTransformFeedback =
				GraphicsExtensionHelper::getFunction<OpenGL::PauseTransformFeedback>("glPauseTransformFeedback");

			openGL.resumeTransformFeedback =
				GraphicsExtensionHelper::getFunction<OpenGL::ResumeTransformFeedback>("glResumeTransformFeedback");

			openGL.uniform1d = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1D>("glUniform1d");
			openGL.uniform1dv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform1DV>("glUniform1dv");
			openGL.uniform2d = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2D>("glUniform2d");
			openGL.uniform2dv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform2DV>("glUniform2dv");
			openGL.uniform3d = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3D>("glUniform3d");
			openGL.uniform3dv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform3DV>("glUniform3dv");
			openGL.uniform4d = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4D>("glUniform4d");
			openGL.uniform4dv = GraphicsExtensionHelper::getFunction<OpenGL::Uniform4DV>("glUniform4dv");

			openGL.uniformMatrix2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2DV>("glUniformMatrix2dv");

			openGL.uniformMatrix2x3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2X3DV>("glUniformMatrix2x3dv");

			openGL.uniformMatrix2x4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix2X4DV>("glUniformMatrix2x4dv");

			openGL.uniformMatrix3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3DV>("glUniformMatrix3dv");

			openGL.uniformMatrix3x2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3X2DV>("glUniformMatrix3x2dv");

			openGL.uniformMatrix3x4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix3X4DV>("glUniformMatrix3x4dv");

			openGL.uniformMatrix4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4DV>("glUniformMatrix4dv");

			openGL.uniformMatrix4x2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4X2DV>("glUniformMatrix4x2dv");

			openGL.uniformMatrix4x3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformMatrix4X3DV>("glUniformMatrix4x3dv");

			openGL.uniformSubroutinesuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::UniformSubroutineSUIV>("glUniformSubroutinesuiv");
		}

		if(::minorVersion >= 1u)
		{
			// Version 4.1

			openGL.activeShaderProgram =
				GraphicsExtensionHelper::getFunction<OpenGL::ActiveShaderProgram>("glActiveShaderProgram");

			openGL.bindProgramPipeline =
				GraphicsExtensionHelper::getFunction<OpenGL::BindProgramPipeline>("glBindProgramPipeline");

			openGL.clearDepthf = GraphicsExtensionHelper::getFunction<OpenGL::ClearDepthF>("glClearDepthf");

			openGL.createShaderProgramv =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateShaderProgramV>("glCreateShaderProgramv");

			openGL.deleteProgramPipelines =
				GraphicsExtensionHelper::getFunction<OpenGL::DeleteProgramPipelines>("glDeleteProgramPipelines");

			openGL.depthRangeArrayv =
				GraphicsExtensionHelper::getFunction<OpenGL::DepthRangeArrayV>("glDepthRangeArrayv");

			openGL.depthRangef = GraphicsExtensionHelper::getFunction<OpenGL::DepthRangeF>("glDepthRangef");

			openGL.depthRangeIndexed =
				GraphicsExtensionHelper::getFunction<OpenGL::DepthRangeIndexed>("glDepthRangeIndexed");

			openGL.genProgramPipelines =
				GraphicsExtensionHelper::getFunction<OpenGL::GenProgramPipelines>("glGenProgramPipelines");

			openGL.getDoublei_v = GraphicsExtensionHelper::getFunction<OpenGL::GetDoubleI_V>("glGetDoublei_v");
			openGL.getFloati_v = GraphicsExtensionHelper::getFunction<OpenGL::GetFloatI_V>("glGetFloati_v");

			openGL.getProgramBinary =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramBinary>("glGetProgramBinary");

			openGL.getProgramPipelineInfoLog =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramPipelineInfoLog>("glGetProgramPipelineInfoLog");

			openGL.getProgramPipelineiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramPipelineIV>("glGetProgramPipelineiv");

			openGL.getShaderPrecisionFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::GetShaderPrecisionFormat>("glGetShaderPrecisionFormat");

			openGL.getVertexAttribLdv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetVertexAttribLDV>("glGetVertexAttribLdv");

			openGL.isProgramPipeline =
				GraphicsExtensionHelper::getFunction<OpenGL::IsProgramPipeline>("glIsProgramPipeline");

			openGL.programBinary =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramBinary>("glProgramBinary");

			openGL.programParameteri =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramParameterI>("glProgramParameteri");

			openGL.programUniform1d =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1D>("glProgramUniform1d");

			openGL.programUniform1dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1DV>("glProgramUniform1dv");

			openGL.programUniform1f =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1F>("glProgramUniform1f");

			openGL.programUniform1fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1FV>("glProgramUniform1fv");

			openGL.programUniform1i =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1I>("glProgramUniform1i");

			openGL.programUniform1iv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1IV>("glProgramUniform1iv");

			openGL.programUniform1ui =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1UI>("glProgramUniform1ui");

			openGL.programUniform1uiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform1UIV>("glProgramUniform1uiv");

			openGL.programUniform2d =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2D>("glProgramUniform2d");

			openGL.programUniform2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2DV>("glProgramUniform2dv");

			openGL.programUniform2f =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2F>("glProgramUniform2f");

			openGL.programUniform2fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2FV>("glProgramUniform2fv");

			openGL.programUniform2i =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2I>("glProgramUniform2i");

			openGL.programUniform2iv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2IV>("glProgramUniform2iv");

			openGL.programUniform2ui =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2UI>("glProgramUniform2ui");

			openGL.programUniform2uiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform2UIV>("glProgramUniform2uiv");

			openGL.programUniform3d =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3D>("glProgramUniform3d");

			openGL.programUniform3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3DV>("glProgramUniform3dv");

			openGL.programUniform3f =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3F>("glProgramUniform3f");

			openGL.programUniform3fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3FV>("glProgramUniform3fv");

			openGL.programUniform3i =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3I>("glProgramUniform3i");

			openGL.programUniform3iv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3IV>("glProgramUniform3iv");

			openGL.programUniform3ui =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3UI>("glProgramUniform3ui");

			openGL.programUniform3uiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform3UIV>("glProgramUniform3uiv");

			openGL.programUniform4d =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4D>("glProgramUniform4d");

			openGL.programUniform4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4DV>("glProgramUniform4dv");

			openGL.programUniform4f =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4F>("glProgramUniform4f");

			openGL.programUniform4fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4FV>("glProgramUniform4fv");

			openGL.programUniform4i =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4I>("glProgramUniform4i");

			openGL.programUniform4iv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4IV>("glProgramUniform4iv");

			openGL.programUniform4ui =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4UI>("glProgramUniform4ui");

			openGL.programUniform4uiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniform4UIV>("glProgramUniform4uiv");

			openGL.programUniformMatrix2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2DV>("glProgramUniformMatrix2dv");

			openGL.programUniformMatrix2fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2FV>("glProgramUniformMatrix2fv");

			openGL.programUniformMatrix2x3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2X3DV>("glProgramUniformMatrix2x3dv");

			openGL.programUniformMatrix2x3fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2X3FV>("glProgramUniformMatrix2x3fv");

			openGL.programUniformMatrix2x4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2X4DV>("glProgramUniformMatrix2x4dv");

			openGL.programUniformMatrix2x4fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix2X4FV>("glProgramUniformMatrix2x4fv");

			openGL.programUniformMatrix3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3DV>("glProgramUniformMatrix3dv");

			openGL.programUniformMatrix3fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3FV>("glProgramUniformMatrix3fv");

			openGL.programUniformMatrix3x2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3X2DV>("glProgramUniformMatrix3x2dv");

			openGL.programUniformMatrix3x2fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3X2FV>("glProgramUniformMatrix3x2fv");

			openGL.programUniformMatrix3x4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3X4DV>("glProgramUniformMatrix3x4dv");

			openGL.programUniformMatrix3x4fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix3X4FV>("glProgramUniformMatrix3x4fv");

			openGL.programUniformMatrix4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4DV>("glProgramUniformMatrix4dv");

			openGL.programUniformMatrix4fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4FV>("glProgramUniformMatrix4fv");

			openGL.programUniformMatrix4x2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4X2DV>("glProgramUniformMatrix4x2dv");

			openGL.programUniformMatrix4x2fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4X2FV>("glProgramUniformMatrix4x2fv");

			openGL.programUniformMatrix4x3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4X3DV>("glProgramUniformMatrix4x3dv");

			openGL.programUniformMatrix4x3fv =
				GraphicsExtensionHelper::getFunction<OpenGL::ProgramUniformMatrix4X3FV>("glProgramUniformMatrix4x3fv");

			openGL.releaseShaderCompiler =
				GraphicsExtensionHelper::getFunction<OpenGL::ReleaseShaderCompiler>("glReleaseShaderCompiler");

			openGL.shaderBinary = GraphicsExtensionHelper::getFunction<OpenGL::ShaderBinary>("glShaderBinary");
			openGL.scissorArrayv = GraphicsExtensionHelper::getFunction<OpenGL::ScissorArrayV>("glScissorArrayv");
			openGL.scissorIndexed = GraphicsExtensionHelper::getFunction<OpenGL::ScissorIndexed>("glScissorIndexed");

			openGL.scissorIndexedv =
				GraphicsExtensionHelper::getFunction<OpenGL::ScissorIndexedV>("glScissorIndexedv");

			openGL.useProgramStages =
				GraphicsExtensionHelper::getFunction<OpenGL::UseProgramStages>("glUseProgramStages");

			openGL.validateProgramPipeline =
				GraphicsExtensionHelper::getFunction<OpenGL::ValidateProgramPipeline>("glValidateProgramPipeline");

			openGL.vertexAttribL1d =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL1D>("glVertexAttribL1d");

			openGL.vertexAttribL1dv =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL1DV>("glVertexAttribL1dv");

			openGL.vertexAttribL2d =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL2D>("glVertexAttribL2d");

			openGL.vertexAttribL2dv =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL2DV>("glVertexAttribL2dv");

			openGL.vertexAttribL3d =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL3D>("glVertexAttribL3d");

			openGL.vertexAttribL3dv =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL3DV>("glVertexAttribL3dv");

			openGL.vertexAttribL4d =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL4D>("glVertexAttribL4d");

			openGL.vertexAttribL4dv =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribL4DV>("glVertexAttribL4dv");

			openGL.vertexAttribLPointer =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribLPointer>("glVertexAttribLPointer");

			openGL.viewportArrayv = GraphicsExtensionHelper::getFunction<OpenGL::ViewportArrayV>("glViewportArrayv");

			openGL.viewportIndexedf =
				GraphicsExtensionHelper::getFunction<OpenGL::ViewportIndexedF>("glViewportIndexedf");

			openGL.viewportIndexedfv =
				GraphicsExtensionHelper::getFunction<OpenGL::ViewportIndexedFV>("glViewportIndexedfv");
		}
		
		if(::minorVersion >= 2u)
		{
			// Version 4.2

			openGL.bindImageTexture =
				GraphicsExtensionHelper::getFunction<OpenGL::BindImageTexture>("glBindImageTexture");

			openGL.drawArraysInstancedBaseInstance =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawArraysInstancedBaseInstance>(
					"glDrawArraysInstancedBaseInstance");

			openGL.drawElementsInstancedBaseInstance =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsInstancedBaseInstance>(
					"glDrawElementsInstancedBaseInstance");

			openGL.drawElementsInstancedBaseVertexBaseInstance =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawElementsInstancedBaseVertexBaseInstance>(
					"glDrawElementsInstancedBaseVertexBaseInstance");

			openGL.drawTransformFeedbackInstanced =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawTransformFeedbackInstanced>(
					"glDrawTransformFeedbackInstanced");

			openGL.drawTransformFeedbackStreamInstanced =
				GraphicsExtensionHelper::getFunction<OpenGL::DrawTransformFeedbackStreamInstanced>(
					"glDrawTransformFeedbackStreamInstanced");

			openGL.getActiveAtomicCounterBufferiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetActiveAtomicCounterBufferIV>(
					"glGetActiveAtomicCounterBufferiv");

			openGL.getInternalformativ =
				GraphicsExtensionHelper::getFunction<OpenGL::GetInternalformatIV>("glGetInternalformativ");

			openGL.memoryBarrier = GraphicsExtensionHelper::getFunction<OpenGL::MemoryBarrier>("glMemoryBarrier");
			openGL.texStorage1D = GraphicsExtensionHelper::getFunction<OpenGL::TexStorage1D>("glTexStorage1D");
			openGL.texStorage2D = GraphicsExtensionHelper::getFunction<OpenGL::TexStorage2D>("glTexStorage2D");
			openGL.texStorage3D = GraphicsExtensionHelper::getFunction<OpenGL::TexStorage3D>("glTexStorage3D");
		}
		
		if(::minorVersion >= 3u)
		{
			// Version 4.3

			openGL.bindVertexBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::BindVertexBuffer>("glBindVertexBuffer");

			openGL.clearBufferData =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferData>("glClearBufferData");

			openGL.clearBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearBufferSubData>("glClearBufferSubData");

			openGL.copyImageSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::CopyImageSubData>("glCopyImageSubData");

			openGL.dispatchCompute =
				GraphicsExtensionHelper::getFunction<OpenGL::DispatchCompute>("glDispatchCompute");

			openGL.dispatchComputeIndirect =
				GraphicsExtensionHelper::getFunction<OpenGL::DispatchComputeIndirect>("glDispatchComputeIndirect");

			openGL.debugMessageCallback =
				GraphicsExtensionHelper::getFunction<OpenGL::DebugMessageCallback>("glDebugMessageCallback");

			openGL.debugMessageControl =
				GraphicsExtensionHelper::getFunction<OpenGL::DebugMessageControl>("glDebugMessageControl");

			openGL.debugMessageInsert =
				GraphicsExtensionHelper::getFunction<OpenGL::DebugMessageInsert>("glDebugMessageInsert");

			openGL.framebufferParameteri =
				GraphicsExtensionHelper::getFunction<OpenGL::FramebufferParameterI>("glFramebufferParameteri");

			openGL.getDebugMessageLog =
				GraphicsExtensionHelper::getFunction<OpenGL::GetDebugMessageLog>("glGetDebugMessageLog");

			openGL.getFramebufferParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetFramebufferParameterIV>("glGetFramebufferParameteriv");

			openGL.getInternalformati64v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetInternalformatI64V>("glGetInternalformati64v");

			openGL.getObjectLabel = GraphicsExtensionHelper::getFunction<OpenGL::GetObjectLabel>("glGetObjectLabel");

			openGL.getObjectPtrLabel =
				GraphicsExtensionHelper::getFunction<OpenGL::GetObjectPtrLabel>("glGetObjectPtrLabel");

			openGL.getProgramInterfaceiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramInterfaceIV>("glGetProgramInterfaceiv");

			openGL.getProgramResourceIndex =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramResourceIndex>("glGetProgramResourceIndex");

			openGL.getProgramResourceiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramResourceIV>("glGetProgramResourceiv");

			openGL.getProgramResourceLocation =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramResourceLocation>(
					"glGetProgramResourceLocation");

			openGL.getProgramResourceLocationIndex =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramResourceLocationIndex>(
					"glGetProgramResourceLocationIndex");

			openGL.getProgramResourceName =
				GraphicsExtensionHelper::getFunction<OpenGL::GetProgramResourceName>("glGetProgramResourceName");

			openGL.invalidateBufferData =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateBufferData>("glInvalidateBufferData");

			openGL.invalidateBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateBufferSubData>("glInvalidateBufferSubData");

			openGL.invalidateFramebuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateFramebuffer>("glInvalidateFramebuffer");

			openGL.invalidateSubFramebuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateSubFramebuffer>("glInvalidateSubFramebuffer");

			openGL.invalidateTexImage =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateTexImage>("glInvalidateTexImage");

			openGL.invalidateTexSubImage =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateTexSubImage>("glInvalidateTexSubImage");

			openGL.multiDrawArraysIndirect =
				GraphicsExtensionHelper::getFunction<OpenGL::MultiDrawArraysIndirect>("glMultiDrawArraysIndirect");

			openGL.multiDrawElementsIndirect =
				GraphicsExtensionHelper::getFunction<OpenGL::MultiDrawElementsIndirect>("glMultiDrawElementsIndirect");

			openGL.objectLabel = GraphicsExtensionHelper::getFunction<OpenGL::ObjectLabel>("glObjectLabel");
			openGL.objectPtrLabel = GraphicsExtensionHelper::getFunction<OpenGL::ObjectPtrLabel>("glObjectPtrLabel");
			openGL.popDebugGroup = GraphicsExtensionHelper::getFunction<OpenGL::PopDebugGroup>("glPopDebugGroup");
			openGL.pushDebugGroup = GraphicsExtensionHelper::getFunction<OpenGL::PushDebugGroup>("glPushDebugGroup");

			openGL.shaderStorageBlockBinding =
				GraphicsExtensionHelper::getFunction<OpenGL::ShaderStorageBlockBinding>("glShaderStorageBlockBinding");

			openGL.texBufferRange = GraphicsExtensionHelper::getFunction<OpenGL::TexBufferRange>("glTexBufferRange");

			openGL.texStorage2DMultisample =
				GraphicsExtensionHelper::getFunction<OpenGL::TexStorage2DMultisample>("glTexStorage2DMultisample");

			openGL.texStorage3DMultisample =
				GraphicsExtensionHelper::getFunction<OpenGL::TexStorage3DMultisample>("glTexStorage3DMultisample");

			openGL.textureView = GraphicsExtensionHelper::getFunction<OpenGL::TextureView>("glTextureView");

			openGL.vertexAttribBinding =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribBinding>("glVertexAttribBinding");

			openGL.vertexAttribFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribFormat>("glVertexAttribFormat");

			openGL.vertexAttribIFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribIFormat>("glVertexAttribIFormat");

			openGL.vertexAttribLFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexAttribLFormat>("glVertexAttribLFormat");

			openGL.vertexBindingDivisor =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexBindingDivisor>("glVertexBindingDivisor");
		}

		if(::minorVersion >= 4u)
		{
			// Version 4.4

			openGL.bindBuffersBase =
				GraphicsExtensionHelper::getFunction<OpenGL::BindBuffersBase>("glBindBuffersBase");

			openGL.bindBuffersRange =
				GraphicsExtensionHelper::getFunction<OpenGL::BindBuffersRange>("glBindBuffersRange");

			openGL.bindImageTextures =
				GraphicsExtensionHelper::getFunction<OpenGL::BindImageTextures>("glBindImageTextures");

			openGL.bindSamplers = GraphicsExtensionHelper::getFunction<OpenGL::BindSamplers>("glBindSamplers");
			openGL.bindTextures = GraphicsExtensionHelper::getFunction<OpenGL::BindTextures>("glBindTextures");

			openGL.bindVertexBuffers =
				GraphicsExtensionHelper::getFunction<OpenGL::BindVertexBuffers>("glBindVertexBuffers");

			openGL.bufferStorage = GraphicsExtensionHelper::getFunction<OpenGL::BufferStorage>("glBufferStorage");
			openGL.clearTexImage = GraphicsExtensionHelper::getFunction<OpenGL::ClearTexImage>("glClearTexImage");

			openGL.clearTexSubImage =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearTexSubImage>("glClearTexSubImage");
		}

		if(::minorVersion >= 5u)
		{
			// Version 4.5

			openGL.bindTextureUnit =
				GraphicsExtensionHelper::getFunction<OpenGL::BindTextureUnit>("glBindTextureUnit");

			openGL.blitNamedFramebuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::BlitNamedFramebuffer>("glBlitNamedFramebuffer");

			openGL.checkNamedFramebufferStatus =
				GraphicsExtensionHelper::getFunction<OpenGL::CheckNamedFramebufferStatus>(
					"glCheckNamedFramebufferStatus");

			openGL.clearNamedBufferData =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedBufferData>("glClearNamedBufferData");

			openGL.clearNamedBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedBufferSubData>("glClearNamedBufferSubData");

			openGL.clearNamedFramebufferfi =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedFramebufferFI>("glClearNamedFramebufferfi");

			openGL.clearNamedFramebufferfv =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedFramebufferFV>("glClearNamedFramebufferfv");

			openGL.clearNamedFramebufferiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedFramebufferIV>("glClearNamedFramebufferiv");

			openGL.clearNamedFramebufferuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::ClearNamedFramebufferUIV>("glClearNamedFramebufferuiv");

			openGL.clipControl = GraphicsExtensionHelper::getFunction<OpenGL::ClipControl>("glClipControl");

			openGL.compressedTextureSubImage1D =
				GraphicsExtensionHelper::getFunction<OpenGL::CompressedTextureSubImage1D>(
					"glCompressedTextureSubImage1D");

			openGL.compressedTextureSubImage2D =
				GraphicsExtensionHelper::getFunction<OpenGL::CompressedTextureSubImage2D>(
					"glCompressedTextureSubImage2D");

			openGL.compressedTextureSubImage3D =
				GraphicsExtensionHelper::getFunction<OpenGL::CompressedTextureSubImage3D>(
					"glCompressedTextureSubImage3D");

			openGL.copyNamedBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::CopyNamedBufferSubData>("glCopyNamedBufferSubData");

			openGL.copyTextureSubImage1D =
				GraphicsExtensionHelper::getFunction<OpenGL::CopyTextureSubImage1D>("glCopyTextureSubImage1D");

			openGL.copyTextureSubImage2D =
				GraphicsExtensionHelper::getFunction<OpenGL::CopyTextureSubImage2D>("glCopyTextureSubImage2D");

			openGL.copyTextureSubImage3D =
				GraphicsExtensionHelper::getFunction<OpenGL::CopyTextureSubImage3D>("glCopyTextureSubImage3D");

			openGL.createBuffers = GraphicsExtensionHelper::getFunction<OpenGL::CreateBuffers>("glCreateBuffers");

			openGL.createFramebuffers =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateFramebuffers>("glCreateFramebuffers");

			openGL.createProgramPipelines =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateProgramPipelines>("glCreateProgramPipelines");

			openGL.createQueries = GraphicsExtensionHelper::getFunction<OpenGL::CreateQueries>("glCreateQueries");

			openGL.createRenderbuffers =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateRenderbuffers>("glCreateRenderbuffers");

			openGL.createSamplers = GraphicsExtensionHelper::getFunction<OpenGL::CreateSamplers>("glCreateSamplers");
			openGL.createTextures = GraphicsExtensionHelper::getFunction<OpenGL::CreateTextures>("glCreateTextures");

			openGL.createTransformFeedbacks =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateTransformFeedbacks>("glCreateTransformFeedbacks");

			openGL.createVertexArrays =
				GraphicsExtensionHelper::getFunction<OpenGL::CreateVertexArrays>("glCreateVertexArrays");

			openGL.disableVertexArrayAttrib =
				GraphicsExtensionHelper::getFunction<OpenGL::DisableVertexArrayAttrib>("glDisableVertexArrayAttrib");

			openGL.enableVertexArrayAttrib =
				GraphicsExtensionHelper::getFunction<OpenGL::EnableVertexArrayAttrib>("glEnableVertexArrayAttrib");

			openGL.flushMappedNamedBufferRange =
				GraphicsExtensionHelper::getFunction<OpenGL::FlushMappedNamedBufferRange>(
					"glFlushMappedNamedBufferRange");

			openGL.generateTextureMipmap =
				GraphicsExtensionHelper::getFunction<OpenGL::GenerateTextureMipmap>("glGenerateTextureMipmap");

			openGL.getCompressedTextureImage =
				GraphicsExtensionHelper::getFunction<OpenGL::GetCompressedTextureImage>("glGetCompressedTextureImage");

			openGL.getCompressedTextureSubImage =
				GraphicsExtensionHelper::getFunction<OpenGL::GetCompressedTextureSubImage>(
					"glGetCompressedTextureSubImage");

			openGL.getGraphicsResetStatus =
				GraphicsExtensionHelper::getFunction<OpenGL::GetGraphicsResetStatus>("glGetGraphicsResetStatus");

			openGL.getNamedBufferParameteri64v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedBufferParameterI64V>(
					"glGetNamedBufferParameteri64v");

			openGL.getNamedBufferParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedBufferParameterIV>("glGetNamedBufferParameteriv");

			openGL.getNamedBufferPointerv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedBufferPointerV>("glGetNamedBufferPointerv");

			openGL.getNamedBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedBufferSubData>("glGetNamedBufferSubData");

			openGL.getNamedFramebufferAttachmentParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedFramebufferAttachmentParameterIV>(
					"glGetNamedFramebufferAttachmentParameteriv");

			openGL.getNamedFramebufferParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedFramebufferParameterIV>(
					"glGetNamedFramebufferParameteriv");

			openGL.getNamedRenderbufferParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetNamedRenderbufferParameterIV>(
					"glGetNamedRenderbufferParameteriv");

			openGL.getnCompressedTexImage =
				GraphicsExtensionHelper::getFunction<OpenGL::GetnCompressedTexImage>("glGetnCompressedTexImage");

			openGL.getnTexImage = GraphicsExtensionHelper::getFunction<OpenGL::GetnTexImage>("glGetnTexImage");
			openGL.getnUniformdv = GraphicsExtensionHelper::getFunction<OpenGL::GetnUniformDV>("glGetnUniformdv");
			openGL.getnUniformfv = GraphicsExtensionHelper::getFunction<OpenGL::GetnUniformFV>("glGetnUniformfv");
			openGL.getnUniformiv = GraphicsExtensionHelper::getFunction<OpenGL::GetnUniformIV>("glGetnUniformiv");
			openGL.getnUniformuiv = GraphicsExtensionHelper::getFunction<OpenGL::GetnUniformUIV>("glGetnUniformuiv");

			openGL.getQueryBufferObjecti64v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetQueryBufferObjectI64V>("glGetQueryBufferObjecti64v");

			openGL.getQueryBufferObjectiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetQueryBufferObjectIV>("glGetQueryBufferObjectiv");

			openGL.getQueryBufferObjectui64v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetQueryBufferObjectUI64V>("glGetQueryBufferObjectui64v");

			openGL.getQueryBufferObjectuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetQueryBufferObjectUIV>("glGetQueryBufferObjectuiv");

			openGL.getTextureImage =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureImage>("glGetTextureImage");

			openGL.getTextureLevelParameterfv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureLevelParameterFV>(
					"glGetTextureLevelParameterfv");

			openGL.getTextureLevelParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureLevelParameterIV>(
					"glGetTextureLevelParameteriv");

			openGL.getTextureParameterfv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureParameterFV>("glGetTextureParameterfv");

			openGL.getTextureParameterIiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureParameterIIV>("glGetTextureParameterIiv");

			openGL.getTextureParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureParameterIV>("glGetTextureParameteriv");

			openGL.getTextureParameterIuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureParameterIUIV>("glGetTextureParameterIuiv");

			openGL.getTextureSubImage =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTextureSubImage>("glGetTextureSubImage");

			openGL.getTransformFeedbacki64_v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTransformFeedbackI64_V>("glGetTransformFeedbacki64_v");

			openGL.getTransformFeedbackiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTransformFeedbackIV>("glGetTransformFeedbackiv");

			openGL.getTransformFeedbacki_v =
				GraphicsExtensionHelper::getFunction<OpenGL::GetTransformFeedbackI_V>("glGetTransformFeedbacki_v");

			openGL.getVertexArrayIndexed64iv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetVertexArrayIndexed64IV>("glGetVertexArrayIndexed64iv");

			openGL.getVertexArrayIndexediv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetVertexArrayIndexedIV>("glGetVertexArrayIndexediv");

			openGL.getVertexArrayiv =
				GraphicsExtensionHelper::getFunction<OpenGL::GetVertexArrayIV>("glGetVertexArrayiv");

			openGL.invalidateNamedFramebufferData =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateNamedFramebufferData>(
					"glInvalidateNamedFramebufferData");

			openGL.invalidateNamedFramebufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::InvalidateNamedFramebufferSubData>(
					"glInvalidateNamedFramebufferSubData");

			openGL.mapNamedBuffer = GraphicsExtensionHelper::getFunction<OpenGL::MapNamedBuffer>("glMapNamedBuffer");

			openGL.mapNamedBufferRange =
				GraphicsExtensionHelper::getFunction<OpenGL::MapNamedBufferRange>("glMapNamedBufferRange");

			openGL.memoryBarrierByRegion =
				GraphicsExtensionHelper::getFunction<OpenGL::MemoryBarrierByRegion>("glMemoryBarrierByRegion");

			openGL.namedBufferData =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedBufferData>("glNamedBufferData");

			openGL.namedBufferStorage =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedBufferStorage>("glNamedBufferStorage");

			openGL.namedBufferSubData =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedBufferSubData>("glNamedBufferSubData");

			openGL.namedFramebufferDrawBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferDrawBuffer>(
					"glNamedFramebufferDrawBuffer");

			openGL.namedFramebufferDrawBuffers =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferDrawBuffers>(
					"glNamedFramebufferDrawBuffers");

			openGL.namedFramebufferParameteri =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferParameterI>(
					"glNamedFramebufferParameteri");

			openGL.namedFramebufferReadBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferReadBuffer>(
					"glNamedFramebufferReadBuffer");

			openGL.namedFramebufferRenderbuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferRenderbuffer>(
					"glNamedFramebufferRenderbuffer");

			openGL.namedFramebufferTexture =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferTexture>("glNamedFramebufferTexture");

			openGL.namedFramebufferTextureLayer =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedFramebufferTextureLayer>(
					"glNamedFramebufferTextureLayer");

			openGL.namedRenderbufferStorage =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedRenderbufferStorage>("glNamedRenderbufferStorage");

			openGL.namedRenderbufferStorageMultisample =
				GraphicsExtensionHelper::getFunction<OpenGL::NamedRenderbufferStorageMultisample>(
					"glNamedRenderbufferStorageMultisample");

			openGL.readnPixels = GraphicsExtensionHelper::getFunction<OpenGL::ReadnPixels>("glReadnPixels");

			openGL.transformFeedbackBufferBase =
				GraphicsExtensionHelper::getFunction<OpenGL::TransformFeedbackBufferBase>(
					"glTransformFeedbackBufferBase");

			openGL.transformFeedbackBufferRange =
				GraphicsExtensionHelper::getFunction<OpenGL::TransformFeedbackBufferRange>(
					"glTransformFeedbackBufferRange");

			openGL.textureBarrier = GraphicsExtensionHelper::getFunction<OpenGL::TextureBarrier>("glTextureBarrier");
			openGL.textureBuffer = GraphicsExtensionHelper::getFunction<OpenGL::TextureBuffer>("glTextureBuffer");

			openGL.textureBufferRange =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureBufferRange>("glTextureBufferRange");

			openGL.textureParameterf =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterF>("glTextureParameterf");

			openGL.textureParameterfv =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterFV>("glTextureParameterfv");

			openGL.textureParameteri =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterI>("glTextureParameteri");

			openGL.textureParameterIiv =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterIIV>("glTextureParameterIiv");

			openGL.textureParameterIuiv =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterIUIV>("glTextureParameterIuiv");

			openGL.textureParameteriv =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureParameterIV>("glTextureParameteriv");

			openGL.textureStorage1D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureStorage1D>("glTextureStorage1D");

			openGL.textureStorage2D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureStorage2D>("glTextureStorage2D");

			openGL.textureStorage2DMultisample =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureStorage2DMultisample>(
					"glTextureStorage2DMultisample");

			openGL.textureStorage3D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureStorage3D>("glTextureStorage3D");

			openGL.textureStorage3DMultisample =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureStorage3DMultisample>(
					"glTextureStorage3DMultisample");

			openGL.textureSubImage1D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureSubImage1D>("glTextureSubImage1D");

			openGL.textureSubImage2D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureSubImage2D>("glTextureSubImage2D");

			openGL.textureSubImage3D =
				GraphicsExtensionHelper::getFunction<OpenGL::TextureSubImage3D>("glTextureSubImage3D");

			openGL.unmapNamedBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::UnmapNamedBuffer>("glUnmapNamedBuffer");

			openGL.vertexArrayAttribBinding =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayAttribBinding>("glVertexArrayAttribBinding");

			openGL.vertexArrayAttribFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayAttribFormat>("glVertexArrayAttribFormat");

			openGL.vertexArrayAttribIFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayAttribIFormat>("glVertexArrayAttribIFormat");

			openGL.vertexArrayAttribLFormat =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayAttribLFormat>("glVertexArrayAttribLFormat");

			openGL.vertexArrayBindingDivisor =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayBindingDivisor>("glVertexArrayBindingDivisor");

			openGL.vertexArrayElementBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayElementBuffer>("glVertexArrayElementBuffer");

			openGL.vertexArrayVertexBuffer =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayVertexBuffer>("glVertexArrayVertexBuffer");

			openGL.vertexArrayVertexBuffers =
				GraphicsExtensionHelper::getFunction<OpenGL::VertexArrayVertexBuffers>("glVertexArrayVertexBuffers");
		}
	}
}

static void initialiseDebugMessaging(OpenGL& openGL)
{
	openGL.enable(OpenGL::DEBUG_OUTPUT_SYNCHRONOUS);
	DE_CHECK_ERROR_OPENGL(&openGL);

	openGL.debugMessageControl(OpenGL::DONT_CARE, OpenGL::DEBUG_TYPE_OTHER, OpenGL::DONT_CARE, 0, nullptr,
		OpenGL::FALSE);

	DE_CHECK_ERROR_OPENGL(&openGL);
	openGL.debugMessageCallback(::processDebugMessage, nullptr);
}

static void initialiseMajorVersion(const String8& versionString)
{
	const Uint32 delimiterPosition = versionString.find('.');
	::majorVersion = std::strtol(versionString.substr(0u, delimiterPosition).c_str(), nullptr, 10);
}

static void initialiseMinorVersion(const String8& versionString)
{
	const Uint32 minorNumberPosition = versionString.find('.') + 1u;
	const Uint32 secondDelimiterPosition = versionString.find('.', minorNumberPosition);
	Uint32 versionEndPosition = versionString.find(' ', minorNumberPosition);

	if(secondDelimiterPosition < versionEndPosition)
		versionEndPosition = secondDelimiterPosition;

	const String8 minorVersionString = versionString.substr(minorNumberPosition,
		versionEndPosition - minorNumberPosition);

	::minorVersion = std::strtol(minorVersionString.c_str(), nullptr, 10);
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
