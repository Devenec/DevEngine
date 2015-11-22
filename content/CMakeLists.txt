cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/ContentManager.cpp
)

set(INCLUDE_DIRECTORIES
	include
	../core/include
	../platform/include
)

include_directories(${INCLUDE_DIRECTORIES})
add_library(content STATIC ${SOURCE_FILES})
