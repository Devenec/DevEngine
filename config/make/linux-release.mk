#
# config/make/linux-release.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

# Compiler settings

C_COMPILER_FLAGS   += -g -O2
C++_COMPILER_FLAGS += -g -O2
PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_RELEASE
