#
# config/make/linux-production.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

# Default compiler settings

COMPILER_C_FLAGS				+= -O2
COMPILER_C++_FLAGS				+= -O2
COMPILER_C++_PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_PRODUCTION
