cmake_minimum_required(VERSION 2.8)
project(devengine)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(COMMON_C_FLAGS "-m32 -Wall")
set(COMMON_CXX_FLAGS "-fno-exceptions -m32 -std=c++11 -stdlib=libc++ -Wall")

# TODO: add -gmodules -fstandalone-debug?
set(CMAKE_C_FLAGS_DEBUG "${COMMON_C_FLAGS} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_C_FLAGS} -g -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_CXX_FLAGS} -g -O0 -DDE_BUILD_CONFIG_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_CXX_FLAGS} -g -O2 -DDE_BUILD_CONFIG_RELEASE")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")

# external
add_subdirectory(external/libpng)
add_subdirectory(external/zlib)

# framework
add_subdirectory(content)
add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(platform)
