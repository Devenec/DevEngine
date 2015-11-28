cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/Main.cpp
)

set(INCLUDE_DIRECTORIES
	include
	../../content/include
	../../core/include
	../../graphics/include
	../../platform/include
)

set(LIBRARIES
	platform
	core
	platform
	core
	#content
	#graphics
	#libpng
	#zlib
)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(sample ${SOURCE_FILES})
target_link_libraries(sample ${LIBRARIES})
