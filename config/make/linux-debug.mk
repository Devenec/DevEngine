#
# config/make/linux-debug.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

COMPILER_C_FLAGS				+= -g -O0
COMPILER_C++_FLAGS				+= -g -O0
COMPILER_C++_PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_DEBUG
