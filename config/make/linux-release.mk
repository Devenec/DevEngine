#
# config/make/linux-release.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

# Default compiler settings

COMPILER_C_FLAGS				+= -g -O2
COMPILER_C++_FLAGS				+= -g -O2
COMPILER_C++_PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_RELEASE
