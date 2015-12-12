#
# config/make/linux-debug.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

# Compiler settings

C_COMPILER_FLAGS   += -g -O0
C++_COMPILER_FLAGS += -g -O0
PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_DEBUG
