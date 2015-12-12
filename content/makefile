#
# content/makefile
#

# Target settings

TARGET_LANGUAGE		 = c++
TARGET_NAME			 = content
TARGET_OUTPUT_TYPE	 = static


include $(MAKE_DIRECTORY)/linux-$(TARGET_CONFIGURATION).mk


# Include directories and source files

INCLUDE_DIRECTORIES = \
	include \
	../core/include \
	../platform/include

SOURCE_DIRECTORIES = \
	source

SOURCE_FILES = \
	ContentManager.cpp


include $(MAKE_DIRECTORY)/linux-build.mk
