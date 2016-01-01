#
# external/libpng/makefile
#

# Target settings

TARGET_LANGUAGE		 = c
TARGET_NAME			 = png
TARGET_OUTPUT_TYPE	 = static


# Build directories

BUILD_OUTPUT_DIRECTORY = ../../build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


# Include directories and source files

INCLUDE_DIRECTORIES = \
	include \
	../zlib/include

SOURCE_DIRECTORIES = \
	source

SOURCE_FILES = \
	png.c \
	pngerror.c \
	pngget.c \
	pngmem.c \
	pngpread.c \
	pngread.c \
	pngrio.c \
	pngrtran.c \
	pngrutil.c \
	pngset.c \
	pngtrans.c \
	pngwio.c \
	pngwrite.c \
	pngwtran.c \
	pngwutil.c


include $(MAKE_DIRECTORY)/linux-build.mk
