# CMakeList.txt : CMake project for Mathlib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCES "Source/*")

add_library (Mathlib SHARED ${SOURCES})
target_compile_definitions(Mathlib PRIVATE MATHLIB_EXPORTS)
target_include_directories(Mathlib PUBLIC Include)

#google test
enable_testing()

file(GLOB_RECURSE UT_SOURCES "Test/*")

add_executable(GlobalUnitTest ${UT_SOURCES})
target_link_libraries(GlobalUnitTest gtest_main)
target_link_libraries(GlobalUnitTest Mathlib)

add_executable(MathUnitTest Test/Misc/MathUnitTest.cpp)
target_link_libraries(MathUnitTest gtest_main)
target_link_libraries(MathUnitTest Mathlib)

add_executable(Vector2UnitTest Test/Space/Vec2UnitTest.cpp)
target_link_libraries(Vector2UnitTest gtest_main)
target_link_libraries(Vector2UnitTest Mathlib)

add_executable(Vector3UnitTest Test/Space/Vec3UnitTest.cpp)
target_link_libraries(Vector3UnitTest gtest_main)
target_link_libraries(Vector3UnitTest Mathlib)

add_executable(Vector4UnitTest Test/Space/Vec4UnitTest.cpp)
target_link_libraries(Vector4UnitTest gtest_main)
target_link_libraries(Vector4UnitTest Mathlib)

add_executable(QuaternionUnitTest Test/Space/QuaternionUnitTest.cpp)
target_link_libraries(QuaternionUnitTest gtest_main)
target_link_libraries(QuaternionUnitTest Mathlib)

add_executable(Mat2UnitTest Test/Matrix/Mat2UnitTest.cpp)
target_link_libraries(Mat2UnitTest gtest_main)
target_link_libraries(Mat2UnitTest Mathlib)

add_executable(Mat3UnitTest Test/Matrix/Mat3UnitTest.cpp)
target_link_libraries(Mat3UnitTest gtest_main)
target_link_libraries(Mat3UnitTest Mathlib)

add_executable(Mat4UnitTest Test/Matrix/Mat4UnitTest.cpp)
target_link_libraries(Mat4UnitTest gtest_main)
target_link_libraries(Mat4UnitTest Mathlib)

add_executable(TransformUnitTest Test/Transform/TransformUnitTest.cpp)
target_link_libraries(TransformUnitTest gtest_main)
target_link_libraries(TransformUnitTest Mathlib)

include(GoogleTest)
gtest_discover_tests(Vector3UnitTest)
