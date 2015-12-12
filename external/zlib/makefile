#
# external/zlib/makefile
#

# Target settings

TARGET_LANGUAGE		 = c
TARGET_NAME			 = z
TARGET_OUTPUT_TYPE	 = static


# Build directories

BUILD_OUTPUT_DIRECTORY = ../../build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk
C_COMPILER_FLAGS += -Wno-implicit-function-declaration


# Include directories and source files

INCLUDE_DIRECTORIES = \
	include

SOURCE_DIRECTORIES = \
	source

SOURCE_FILES = \
	adler32.c \
	compress.c \
	crc32.c \
	deflate.c \
	gzclose.c \
	gzlib.c \
	gzread.c \
	gzwrite.c \
	infback.c \
	inffast.c \
	inflate.c \
	inftrees.c \
	trees.c \
	uncompr.c \
	zutil.c


include $(MAKE_DIRECTORY)/linux-build.mk
