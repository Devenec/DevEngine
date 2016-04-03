#
# config/make/linux-release.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

COMPILER_C_FLAGS				+= -g -O2
COMPILER_C++_FLAGS				+= -g -O2
COMPILER_C++_PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_RELEASE

ifeq ($(COMPILER_C++_ENABLE_EXTRA_WARNINGS), true)
	COMPILER_C++_FLAGS += -Wdisabled-optimization -Wunsafe-loop-optimizations -Wvector-operation-performance
endif
