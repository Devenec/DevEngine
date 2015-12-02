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
	content
	graphics
	core
	platform
	graphics
	core
	platform
	X11
	Xrandr
)

include_directories(${INCLUDE_DIRECTORIES})
add_executable(sample ${SOURCE_FILES})
target_link_libraries(sample ${LIBRARIES})
