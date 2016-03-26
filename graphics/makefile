#
# graphics/makefile
#

# Target settings

TARGET_LANGUAGE	   = c++
TARGET_NAME		   = graphics
TARGET_OUTPUT_TYPE = static


# Includes and sources

INCLUDE_DIRECTORIES = \
	include \
	../content/include \
	../core/include \
	../external/libpng/include \
	../platform/include

SOURCE_DIRECTORIES = \
	source

SOURCE_FILES = \
	Colour.cpp \
	DisplayMode.cpp \
	EffectCodeLoader.cpp \
	GraphicsConfig.cpp \
	GraphicsDevice.cpp \
	GraphicsDeviceManager.cpp \
	Image.cpp \
	ImageLoader.cpp \
	LogUtility.cpp \
	PNGReader.cpp \
	Viewport.cpp


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk
include $(MAKE_DIRECTORY)/linux-build.mk
