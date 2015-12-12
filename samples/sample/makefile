#
# samples/sample/makefile
#

# Target settings

TARGET_LANGUAGE		 = c++
TARGET_NAME			 = sample
TARGET_OUTPUT_TYPE	 = executable


# Build directories

BUILD_OUTPUT_DIRECTORY = ../../build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


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

LIBRARY_PREREQUISITES = \
	content \
	core \
	graphics \
	platform

STATIC_LIBRARIES = \
	content \
	graphics \
	core \
	platform \
	graphics \
	core \
	platform \
	X11 \
	Xrandr


include $(MAKE_DIRECTORY)/linux-build.mk
