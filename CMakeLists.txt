# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

# Project
project ("Mathlib")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)    # .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .dll / .so / .dylib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .exe

set (CMAKE_CXX_STANDARD 17)

# Input
file(GLOB_RECURSE SOURCES "Source/*")

# Dynamic library.
add_library (Mathlib SHARED ${SOURCES})
target_compile_definitions(Mathlib PRIVATE MATHLIB_EXPORTS)
set_target_properties(Mathlib PROPERTIES LINKER_LANGUAGE CXX)

# Include directories
target_include_directories(Mathlib PUBLIC Include)

# Entrypoints
add_subdirectory(UnitTests)

# Enable tests
include(CTest)