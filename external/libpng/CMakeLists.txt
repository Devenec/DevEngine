cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/png.c
	source/pngerror.c
	source/pngget.c
	source/pngmem.c
	source/pngpread.c
	source/pngread.c
	source/pngrio.c
	source/pngrtran.c
	source/pngrutil.c
	source/pngset.c
	source/pngtrans.c
	source/pngwio.c
	source/pngwrite.c
	source/pngwtran.c
	source/pngwutil.c
)

include_directories(include ../zlib/include)
add_library(libpng STATIC ${SOURCE_FILES})
