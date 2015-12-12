#
# config/make/linux-production.mk
#

include $(MAKE_DIRECTORY)/linux-common.mk

# Compiler settings

C_COMPILER_FLAGS   += -O2
C++_COMPILER_FLAGS += -O2
PREPROCESSOR_FLAGS += -DDE_BUILD_CONFIG_PRODUCTION
