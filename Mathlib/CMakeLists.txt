# Input
file(GLOB_RECURSE SOURCES "Source/*")

# Dynamic library.
add_library (Mathlib SHARED ${SOURCES})
target_compile_definitions(Mathlib PRIVATE MATHLIB_EXPORTS)
set_target_properties(Mathlib PROPERTIES LINKER_LANGUAGE CXX)

# Add options to generate coverage file
if (CMAKE_CXX_COMPILER_ID  STREQUAL "GNU")
		target_compile_options(Mathlib PUBLIC --coverage)
		target_link_options(Mathlib PUBLIC --coverage)
endif()

# Include directories
target_include_directories(Mathlib PUBLIC Include)

# Entrypoints
add_subdirectory(UnitTests)