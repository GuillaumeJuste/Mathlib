# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Mathlib")

# Include sub-projects.
add_subdirectory ("Mathlib")

include(FetchContent)
FetchContent_Declare(
			googletest
			GIT_REPOSITORY https://github.com/google/googletest.git
			GIT_TAG        release-1.11.0
			SOURCE_DIR		${CMAKE_SOURCE_DIR}/Mathlib/ThirdParty/googletest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)