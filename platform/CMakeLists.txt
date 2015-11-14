cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/GraphicsExtensionLoader.cpp
	source/opengl/OpenGL.cpp
	source/opengl/OpenGLEffect.cpp
	source/opengl/OpenGLGraphicsBuffer.cpp
	source/opengl/OpenGLGraphicsDevice.cpp
	source/opengl/OpenGLShader.cpp
	source/opengl/OpenGLUniformBuffer.cpp
	source/opengl/OpenGLVertexBufferState.cpp
)

include_directories(include ../core/include ../graphics/include)
add_library(platform STATIC ${SOURCE_FILES})
