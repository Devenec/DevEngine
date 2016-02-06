#
# graphics/makefile
#

# Target settings

TARGET_LANGUAGE		 = c++
TARGET_NAME			 = graphics
TARGET_OUTPUT_TYPE	 = static


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


# Include directories and source files

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
	IndexBuffer.cpp \
	LogUtility.cpp \
	PNGReader.cpp \
	Viewport.cpp


include $(MAKE_DIRECTORY)/linux-build.mk
