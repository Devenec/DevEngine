#
# platform/makefile
#

# Target settings

TARGET_LANGUAGE		 = c++
TARGET_NAME			 = platform
TARGET_OUTPUT_TYPE	 = static


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


# Include directories and source files

INCLUDE_DIRECTORIES = \
	include \
	../content/include \
	../core/include \
	../graphics/include

SOURCE_DIRECTORIES = \
	source \
	source/glx \
	source/linux \
	source/null \
	source/opengl \
	source/posix \
	source/std \
	source/x

SOURCE_FILES = \
	GraphicsFunctionUtility.cpp \
	Utility.cpp \
	glx/GLX.cpp \
	glx/GLXGraphicsConfigChooser.cpp \
	glx/GLXGraphicsContext.cpp \
	glx/GLXGraphicsFunctionUtility.cpp \
	linux/LinuxThread.cpp \
	null/NullLogManager.cpp \
	opengl/OpenGL.cpp \
	opengl/OpenGLEffect.cpp \
	opengl/OpenGLEffectSourceCodeReader.cpp \
	opengl/OpenGLGraphicsBuffer.cpp \
	opengl/OpenGLGraphicsDevice.cpp \
	opengl/OpenGLShader.cpp \
	opengl/OpenGLVertexBufferState.cpp \
	posix/POSIX.cpp \
	posix/POSIXFileStream.cpp \
	posix/POSIXFileSystem.cpp \
	posix/POSIXThread.cpp \
	std/STDLog.cpp \
	std/STDMain.cpp \
	x/X.cpp \
	x/XGraphicsAdapter.cpp \
	x/XGraphicsAdapterManager.cpp \
	x/XGraphicsDeviceManager.cpp \
	x/XWindow.cpp


include $(MAKE_DIRECTORY)/linux-build.mk
