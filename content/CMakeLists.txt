cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/ContentManager.cpp
)

include_directories(include ../core/include ../platform/include)
add_library(content STATIC ${SOURCE_FILES})
