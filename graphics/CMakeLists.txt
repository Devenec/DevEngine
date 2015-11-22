cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/Colour.cpp
	source/DisplayMode.cpp
	source/GraphicsConfig.cpp
	source/GraphicsDevice.cpp
	source/Image.cpp
	source/ImageLoader.cpp
	source/IndexBuffer.cpp
	source/LogUtility.cpp
	source/PngReader.cpp
	source/Viewport.cpp
)

set(INCLUDE_DIRECTORIES
	include
	../content/include
	../core/include
	../external/libpng/include
	../platform/include
)

include_directories(${INCLUDE_DIRECTORIES})
add_library(graphics STATIC ${SOURCE_FILES})
