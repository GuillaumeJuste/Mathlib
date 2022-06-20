set(MathlibTarget Mathlib)

# Input
file(GLOB_RECURSE SOURCES "Source/*")

# Dynamic library.
add_library (${MathlibTarget} SHARED ${SOURCES})
target_compile_definitions(${MathlibTarget} PRIVATE MATHLIB_EXPORTS)
set_target_properties(${MathlibTarget} PROPERTIES LINKER_LANGUAGE CXX)

# Add options to generate coverage file
if (CMAKE_CXX_COMPILER_ID  STREQUAL "GNU")
		target_compile_options(${MathlibTarget} PUBLIC --coverage)
		target_link_options(${MathlibTarget} PUBLIC --coverage)
endif()

# Include directories
target_include_directories(${MathlibTarget} PUBLIC Include)

# Entrypoints
add_subdirectory(UnitTests)