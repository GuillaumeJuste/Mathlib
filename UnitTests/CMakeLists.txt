#google test
enable_testing()

file(GLOB_RECURSE UT_SOURCES "*")

add_executable(GlobalUnitTest ${UT_SOURCES})
target_link_libraries(GlobalUnitTest gtest_main)
target_link_libraries(GlobalUnitTest Mathlib)

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