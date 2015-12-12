#
# config/make/linux-common.mk
#

ifndef TARGET_NAME
$(error The target name is not defined.)
endif


# Default build directories

ifndef BUILD_OUTPUT_DIRECTORY
	BUILD_OUTPUT_DIRECTORY = ../build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)
endif

ifndef BUILD_INTERMEDIATE_DIRECTORY
	BUILD_INTERMEDIATE_DIRECTORY = $(BUILD_OUTPUT_DIRECTORY)/obj/$(TARGET_NAME)
endif


ifeq ($(TARGET_ARCHITECTURE), x86)
	BUILD_ARCHITECTURE_FLAG = -m32
else ifeq ($(TARGET_ARCHITECTURE), x64)
	BUILD_ARCHITECTURE_FLAG = -m64
else
$(error The target architecture is invalid ($(TARGET_ARCHITECTURE)).)
endif


# Default compiler settings

C_COMPILER_FLAGS   += $(BUILD_ARCHITECTURE_FLAG) -Wall
C++_COMPILER_FLAGS += -fno-exceptions $(BUILD_ARCHITECTURE_FLAG) -std=c++11 -stdlib=libc++ -Wall


# Default archiver settings

ARCHIVER	   += ar
ARCHIVER_FLAGS += -crs


# Default linker settings

C_LINKER_FLAGS		+= $(BUILD_ARCHITECTURE_FLAG) -L$(BUILD_OUTPUT_DIRECTORY)
C++_LINKER_FLAGS	+= $(BUILD_ARCHITECTURE_FLAG) -stdlib=libc++ -L$(BUILD_OUTPUT_DIRECTORY)
LINKER_SHARED_FLAGS += -fPIC -shared
