#
# makefile
#

# Global settings

# Supported values are clang and gcc
COMPILER		 = clang

# Supported values are libc++ and libstdc++ (used with Clang only)
STANDARD_LIBRARY = libc++

ifeq ($(COMPILER), clang)
	export COMPILER_C				 = clang
	export COMPILER_C_FLAGS			 = -Wall -Wshorten-64-to-32
	export COMPILER_C++				 = clang++

	export COMPILER_C++_FLAGS		 = -fno-exceptions -std=c++11 -stdlib=$(STANDARD_LIBRARY) -Wall \
		-Wshorten-64-to-32

	export COMPILER_C++_LINKER_FLAGS = -stdlib=$(STANDARD_LIBRARY)
else ifeq ($(COMPILER), gcc)
	export COMPILER_C				 = gcc
	export COMPILER_C_FLAGS			 = -Wall
	export COMPILER_C++				 = g++
	export COMPILER_C++_FLAGS		 = -fno-exceptions -std=c++11 -Wall
else
$(error The compiler is invalid ($(COMPILER)).)
endif

# Supported values are x86 and x64
export TARGET_ARCHITECTURE	 = x64

# Supported values are debug, release and production
export TARGET_CONFIGURATION	 = debug

# Supported values are linux
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
	$(MAKE) -C samples/sample \

	# Temporary solution to have assets in correct location
	cp -arv samples/sample/assets/ build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)/

.PHONY: clean
clean:
	$(MAKE) -C external/libpng clean; \
	$(MAKE) -C external/zlib clean; \
	$(MAKE) -C content clean; \
	$(MAKE) -C core clean; \
	$(MAKE) -C graphics clean; \
	$(MAKE) -C platform clean; \
	$(MAKE) -C samples/sample clean \

	# Temporary solution, see above
	rm -fr build/$(TARGET_PLATFORM)/$(TARGET_ARCHITECTURE)/$(TARGET_CONFIGURATION)/assets/
