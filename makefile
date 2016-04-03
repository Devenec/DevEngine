#
# makefile
#

# Global settings

# Supported values are clang and gcc
COMPILER								  = gcc

export COMPILER_C++_ENABLE_EXTRA_WARNINGS = false

ifeq ($(COMPILER), clang)
	# Supported values are libc++ and libstdc++
	STANDARD_LIBRARY				 = libstdc++

	export COMPILER_C				 = clang
	export COMPILER_C_FLAGS			 = -Wall -Wextra -Wpedantic -Wshorten-64-to-32
	export COMPILER_C++				 = clang++

	export COMPILER_C++_FLAGS		 = -fno-exceptions -std=c++11 -stdlib=$(STANDARD_LIBRARY) -Wall -Wextra \
		-Wcast-align -Wformat=2 -Wnon-virtual-dtor -Wpedantic -Wredundant-decls -Wshorten-64-to-32 \
		-Wsign-promo -Wundef -Wunused -Werror=return-type

	export COMPILER_C++_LINKER_FLAGS = -stdlib=$(STANDARD_LIBRARY)
else ifeq ($(COMPILER), gcc)
	export COMPILER_C				 = gcc
	export COMPILER_C_FLAGS			 = -Wall -Wextra -Wpedantic
	export COMPILER_C++				 = g++

	export COMPILER_C++_FLAGS		 = -fno-exceptions -std=c++11 -Wall -Wextra -Wcast-align -Wformat=2 \
		-Wformat-signedness -Wlogical-op -Wnon-virtual-dtor -Wpedantic -Wredundant-decls -Wsign-promo \
		-Wundef -Wunused -Werror=return-type
else
$(error The compiler is invalid ($(COMPILER)).)
endif

ifeq ($(COMPILER_C++_ENABLE_EXTRA_WARNINGS), true)
	COMPILER_C++_FLAGS += -Wconversion -Wctor-dtor-privacy -Wdate-time -Wfloat-equal -Wold-style-cast \
		-Woverloaded-virtual -Wpadded -Wshadow -Wsign-conversion -Wstrict-null-sentinel -Wstrict-overflow=5 \
		-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wuseless-cast \
		-Wzero-as-null-pointer-constant
endif

# Supported values are x86 and x64
export TARGET_ARCHITECTURE	 = x64

# Supported values are debug, release and production
export TARGET_CONFIGURATION	 = debug

# Supported value is linux
export TARGET_PLATFORM		 = linux

export MAKE_DIRECTORY		:= $(CURDIR)/config/make


# Rules

all:
	$(MAKE) -C external/libpng; \
	$(MAKE) -C external/zlib; \
	$(MAKE) -C content; \
	$(MAKE) -C core; \
	$(MAKE) -C graphics; \
	$(MAKE) -C platform; \
	$(MAKE) -C samples/sample

.PHONY: clean
clean:
	$(MAKE) -C external/libpng clean; \
	$(MAKE) -C external/zlib clean; \
	$(MAKE) -C content clean; \
	$(MAKE) -C core clean; \
	$(MAKE) -C graphics clean; \
	$(MAKE) -C platform clean; \
	$(MAKE) -C samples/sample clean
