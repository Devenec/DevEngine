#
# core/makefile
#

# Target settings

TARGET_LANGUAGE	   = c++
TARGET_NAME		   = core
TARGET_OUTPUT_TYPE = static


# Includes and sources

INCLUDE_DIRECTORIES = \
	include \
	../platform/include

SOURCE_DIRECTORIES = \
	source \
	source/debug \
	source/maths \
	source/memory

SOURCE_FILES = \
	Application.cpp \
	Bitset.cpp \
	Error.cpp \
	FileSystem.cpp \
	Log.cpp \
	LogBuffer.cpp \
	LogManager.cpp \
	Memory.cpp \
	Rectangle.cpp \
	String.cpp \
	Tokeniser.cpp \
	Types.cpp \
	debug/AllocationTracker.cpp \
	debug/Assert.cpp \
	maths/Angle.cpp \
	maths/Matrix4.cpp \
	maths/Vector2.cpp \
	maths/Vector3.cpp \
	maths/Vector4.cpp \
	memory/AllocationPolicy.cpp \
	memory/AllocationPolicyBase.cpp


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk
include $(MAKE_DIRECTORY)/linux-build.mk
