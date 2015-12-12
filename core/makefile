#
# core/makefile
#

# Target settings

TARGET_LANGUAGE		 = c++
TARGET_NAME			 = core
TARGET_OUTPUT_TYPE	 = static


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


# Include directories and source files

INCLUDE_DIRECTORIES = \
	include \
	../platform/include

SOURCE_DIRECTORIES = \
	source \
	source/debug \
	source/maths \
	source/memory

SOURCE_FILES = \
	debug/AllocationTracker.cpp \
	debug/Assert.cpp \
	maths/Angle.cpp \
	maths/Matrix4.cpp \
	maths/Vector2.cpp \
	maths/Vector3.cpp \
	maths/Vector4.cpp \
	memory/AllocationPolicy.cpp \
	memory/AllocationPolicyBase.cpp \
	Application.cpp \
	Error.cpp \
	Log.cpp \
	LogBuffer.cpp \
	LogManager.cpp \
	Memory.cpp \
	Rectangle.cpp \
	String.cpp \
	Types.cpp


include $(MAKE_DIRECTORY)/linux-build.mk
