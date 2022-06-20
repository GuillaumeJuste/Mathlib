cmake_minimum_required (VERSION 3.20)

# Project
project ("Mathlib")

# Set output folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)    # .lib / .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .dll / .so / .dylib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)    # .exe

# Set default C++ Version
set (CMAKE_CXX_STANDARD 17)

# Entrypoints
add_subdirectory(Mathlib)

# Enable tests
include(CTest)