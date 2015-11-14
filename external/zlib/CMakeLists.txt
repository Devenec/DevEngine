cmake_minimum_required(VERSION 2.8)

set(SOURCE_FILES
	source/adler32.c
	source/compress.c
	source/crc32.c
	source/deflate.c
	source/gzclose.c
	source/gzlib.c
	source/gzread.c
	source/gzwrite.c
	source/infback.c
	source/inffast.c
	source/inflate.c
	source/inftrees.c
	source/trees.c
	source/uncompr.c
	source/zutil.c
)

include_directories(include)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wno-implicit-function-declaration")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wno-implicit-function-declaration")
add_library(zlib STATIC ${SOURCE_FILES})
