project(MathlibUnitTests)

#load googletest
include(FetchContent)
FetchContent_Declare(
			googletest
			GIT_REPOSITORY https://github.com/google/googletest.git
			GIT_TAG        release-1.11.0
			SOURCE_DIR		${CMAKE_SOURCE_DIR}/ThirdParty/googletest
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#google test
enable_testing()

file(GLOB_RECURSE UT_SOURCES "*")

set(GlobalUnitTest MathlibUnitTests)
add_executable(${GlobalUnitTest} ${UT_SOURCES})
target_link_libraries(${GlobalUnitTest} gtest_main)
target_link_libraries(${GlobalUnitTest} Mathlib)
add_test(NAME ${GlobalUnitTest} COMMAND ${GlobalUnitTest})
target_compile_options(${GlobalUnitTest}
    PUBLIC
        "-O0"
        "-fprofile-arcs"
        "-ftest-coverage"
    )


add_executable(MathUnitTest Misc/MathUnitTest.cpp)
target_link_libraries(MathUnitTest gtest_main)
target_link_libraries(MathUnitTest Mathlib)

add_executable(Vector2UnitTest Space/Vec2UnitTest.cpp)
target_link_libraries(Vector2UnitTest gtest_main)
target_link_libraries(Vector2UnitTest Mathlib)

add_executable(Vector3UnitTest Space/Vec3UnitTest.cpp)
target_link_libraries(Vector3UnitTest gtest_main)
target_link_libraries(Vector3UnitTest Mathlib)

add_executable(Vector4UnitTest Space/Vec4UnitTest.cpp)
target_link_libraries(Vector4UnitTest gtest_main)
target_link_libraries(Vector4UnitTest Mathlib)

add_executable(QuaternionUnitTest Space/QuaternionUnitTest.cpp)
target_link_libraries(QuaternionUnitTest gtest_main)
target_link_libraries(QuaternionUnitTest Mathlib)

add_executable(Mat2UnitTest Matrix/Mat2UnitTest.cpp)
target_link_libraries(Mat2UnitTest gtest_main)
target_link_libraries(Mat2UnitTest Mathlib)

add_executable(Mat3UnitTest Matrix/Mat3UnitTest.cpp)
target_link_libraries(Mat3UnitTest gtest_main)
target_link_libraries(Mat3UnitTest Mathlib)

add_executable(Mat4UnitTest Matrix/Mat4UnitTest.cpp)
target_link_libraries(Mat4UnitTest gtest_main)
target_link_libraries(Mat4UnitTest Mathlib)

add_executable(TransformUnitTest Transform/TransformUnitTest.cpp)
target_link_libraries(TransformUnitTest gtest_main)
target_link_libraries(TransformUnitTest Mathlib)