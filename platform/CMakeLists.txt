cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/null/NullLogManager.cpp
	source/opengl/OpenGL.cpp
	source/opengl/OpenGLEffect.cpp
	source/opengl/OpenGLGraphicsBuffer.cpp
	source/opengl/OpenGLGraphicsDevice.cpp
	source/opengl/OpenGLShader.cpp
	source/opengl/OpenGLVertexBufferState.cpp
	source/posix/POSIXFileStream.cpp
	source/std/STDLog.cpp
	source/std/STDMain.cpp
)

set(INCLUDE_DIRECTORIES
	include
	../core/include
	../graphics/include
)

include_directories(${INCLUDE_DIRECTORIES})
add_library(platform STATIC ${SOURCE_FILES})
