cmake_minimum_required(VERSION 3.28.0)
project(conway)

add_executable(conway main.cpp)

find_package(raylib 5.0 QUIET)
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(conway raylib)

target_include_directories(conway PUBLIC "${raylib_SOURCE_DIR}/src")