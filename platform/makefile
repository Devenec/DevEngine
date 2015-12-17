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
	../core/include \
	../graphics/include

SOURCE_DIRECTORIES = \
	source \
	source/glx \
	source/null \
	source/posix \
	source/std \
	source/x

SOURCE_FILES = \
	Utility.cpp \
	glx/GLX.cpp \
	glx/GLXGraphicsConfigChooser.cpp \
	null/NullLogManager.cpp \
	posix/POSIXFileStream.cpp \
	std/STDLog.cpp \
	std/STDMain.cpp \
	x/X.cpp \
	x/XGraphicsAdapter.cpp \
	x/XGraphicsAdapterManager.cpp \
	x/XGraphicsDeviceManager.cpp


include $(MAKE_DIRECTORY)/linux-build.mk
