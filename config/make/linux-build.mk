#
# config/make/linux-build.mk
#

ifeq ($(TARGET_LANGUAGE), c)
	COMPILER					 = $(COMPILER_C)
	COMPILER_FLAGS				 = $(COMPILER_C_FLAGS)
	COMPILER_LINKER_FLAGS		 = $(COMPILER_C_LINKER_FLAGS)
	COMPILER_LINKER_SHARED_FLAGS = $(COMPILER_C_LINKER_SHARED_FLAGS)
	COMPILER_PREPROCESSOR_FLAGS	 = $(COMPILER_C_PREPROCESSOR_FLAGS)
	SOURCE_FILE_EXTENSION		 = .c
else ifeq ($(TARGET_LANGUAGE), c++)
	COMPILER					 = $(COMPILER_C++)
	COMPILER_FLAGS				 = $(COMPILER_C++_FLAGS)
	COMPILER_LINKER_FLAGS		 = $(COMPILER_C++_LINKER_FLAGS)
	COMPILER_LINKER_SHARED_FLAGS = $(COMPILER_C++_LINKER_SHARED_FLAGS)
	COMPILER_PREPROCESSOR_FLAGS	 = $(COMPILER_C++_PREPROCESSOR_FLAGS)
	SOURCE_FILE_EXTENSION		 = .cpp
else
$(error The target language is invalid ($(TARGET_LANGUAGE)).)
endif

INTERNAL_STATIC_LIBRARIES		= $(addprefix -l, $(STATIC_LIBRARIES))
INTERNAL_INCLUDE_DIRECTORIES	= $(addprefix -I, $(INCLUDE_DIRECTORIES))
DEPENDENCIES_DIRECTORY			= $(BUILD_INTERMEDIATE_DIRECTORY)/dependencies
BUILD_DIRECTORIES				= $(DEPENDENCIES_DIRECTORY) $(BUILD_OUTPUT_DIRECTORY)
COMPILER_DEPENDENCY_FLAGS		= -MMD -MP -MF $(DEPENDENCIES_DIRECTORY)/$*.d
SOURCE_OBJECT_FILES				= $(SOURCE_FILES:.c=.o)
SOURCE_OBJECT_FILES			   += $(SOURCE_FILES:.cpp=.o)

OBJECT_FILES					= \
	$(addprefix $(BUILD_INTERMEDIATE_DIRECTORY)/, $(filter %.o, $(notdir $(SOURCE_OBJECT_FILES))))

INTERNAL_LIBRARY_PREREQUISITES	= \
	$(addprefix $(BUILD_OUTPUT_DIRECTORY)/lib, $(addsuffix .a, $(LIBRARY_PREREQUISITES)))

VPATH							= $(SOURCE_DIRECTORIES)

ifeq ($(TARGET_OUTPUT_TYPE), static)
	BUILD_OUTPUT_FILE_PREFIX	= lib
	BUILD_OUTPUT_FILE_EXTENSION = .a
	LINKER_COMMAND				= $(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^
else ifeq ($(TARGET_OUTPUT_TYPE), shared)
	BUILD_OUTPUT_FILE_PREFIX	= lib
	BUILD_OUTPUT_FILE_EXTENSION = .so

	LINKER_COMMAND				= \
		$(COMPILER) $(COMPILER_LINKER_FLAGS) $(COMPILER_LINKER_SHARED_FLAGS) $^ $(INTERNAL_STATIC_LIBRARIES) \
			-o $@
else ifeq ($(TARGET_OUTPUT_TYPE), executable)
	LINKER_COMMAND				= $(COMPILER) $(COMPILER_LINKER_FLAGS) $^ $(INTERNAL_STATIC_LIBRARIES) -o $@
else
$(error The target output type is invalid ($(TARGET_OUTPUT_TYPE)).)
endif

BUILD_OUTPUT_FILE = \
	$(BUILD_OUTPUT_DIRECTORY)/$(BUILD_OUTPUT_FILE_PREFIX)$(TARGET_NAME)$(BUILD_OUTPUT_FILE_EXTENSION)


# Rules

all: $(BUILD_OUTPUT_FILE)
	$(POST_BUILD_COMMAND)

$(BUILD_OUTPUT_FILE): $(OBJECT_FILES) $(INTERNAL_LIBRARY_PREREQUISITES)
	$(LINKER_COMMAND)

$(OBJECT_FILES): $(BUILD_INTERMEDIATE_DIRECTORY)/%.o: %$(SOURCE_FILE_EXTENSION) | $(BUILD_DIRECTORIES)
	$(COMPILER) $(COMPILER_FLAGS) $(COMPILER_PREPROCESSOR_FLAGS) $(INTERNAL_INCLUDE_DIRECTORIES) \
		$(COMPILER_DEPENDENCY_FLAGS) -c $< -o $@

-include $(DEPENDENCIES_DIRECTORY)/*.d

$(BUILD_DIRECTORIES):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f -- $(BUILD_OUTPUT_FILE) $(OBJECT_FILES) $(DEPENDENCIES_DIRECTORY)/*.d;
	$(CUSTOM_CLEAN_COMMAND)
