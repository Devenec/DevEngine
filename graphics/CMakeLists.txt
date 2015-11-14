cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/Colour.cpp
	source/DisplayMode.cpp
	source/GraphicsAdapterManager.cpp
	source/GraphicsContextManager.cpp
	source/GraphicsDevice.cpp
	source/Image.cpp
	source/ImageLoader.cpp
	source/IndexBuffer.cpp
	source/PngReader.cpp
	source/Viewport.cpp
)

include_directories(include ../content/include ../core/include ../external/libpng/include ../platform/include)
add_library(graphics STATIC ${SOURCE_FILES})
