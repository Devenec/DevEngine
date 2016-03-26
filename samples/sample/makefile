#
# samples/sample/makefile
#

# Target settings

TARGET_LANGUAGE		   = c++
TARGET_NAME			   = sample
TARGET_OUTPUT_TYPE	   = executable

BUILD_OUTPUT_DIRECTORY = ../../build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)


# Includes and sources

INCLUDE_DIRECTORIES = \
	include \
	../../content/include \
	../../core/include \
	../../graphics/include \
	../../platform/include

SOURCE_DIRECTORIES = \
	source

SOURCE_FILES = \
	Main.cpp


# Libraries

STATIC_LIBRARIES = \
	content \
	graphics \
	core \
	platform \
	graphics \
	core \
	platform \
	png \
	z \
	dl \
	pthread \
	X11 \
	Xrandr

LIBRARY_PREREQUISITES = \
	content \
	core \
	graphics \
	platform \
	png \
	z


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk
include $(MAKE_DIRECTORY)/linux-build.mk
