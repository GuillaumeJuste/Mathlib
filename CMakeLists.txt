cmake_minimum_required (VERSION 3.20)

# Project
project (Mathlib)

# Set output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)    # .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .dll / .so / .dylib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .exe

# Set default C++ Version
set (CMAKE_CXX_STANDARD 17)

## Add SA_Maths's tests to build tree.
option(MATHLIB_BUILD_TESTS_OPT "Should build MATHLIB tests" OFF)

# Enable tests
include(CTest)

# Entrypoints
add_subdirectory(Mathlib)