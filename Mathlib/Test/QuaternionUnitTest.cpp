#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Unit test for constants values
*/
TEST(QuaternionUnitTest, Constant)
{
	Math::InitializeRandom();
	EXPECT_EQ(Quat::Zero, Quat(0.f, 0.f, 0.f, 0.f));
	EXPECT_EQ(Quat::Identity, Quat(1.f, 0.f, 0.f, 0.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(QuaternionUnitTest, Constructor)
{
	EXPECT_EQ(Quat(), Quat(0.f, 0.f, 0.f, 0.f));

	float quat_x = 19.2f;
	float quat_y = -8.4f;
	float quat_z = 7.5f;
	float quat_w = 12.6f;
	Quat quat = Quat(quat_w, quat_x, quat_y, quat_z);

	EXPECT_FLOAT_EQ(quat.X, quat_x);
	EXPECT_FLOAT_EQ(quat.Y, quat_y);
	EXPECT_FLOAT_EQ(quat.Z, quat_z);
	EXPECT_FLOAT_EQ(quat.W, quat_w);

	Vec3 axis = Vec3(quat_x, quat_y, quat_z);
	Quat quat_2 = Quat(quat_w, axis);

	EXPECT_FLOAT_EQ(quat_2.X, 0.094655044f);
	EXPECT_FLOAT_EQ(quat_2.Y, -0.041411579f);
	EXPECT_FLOAT_EQ(quat_2.Z, 0.036974624f);
	EXPECT_FLOAT_EQ(quat_2.W, 0.993960950f);
}

TEST(QuaternionUnitTest, Equality)
{
	Quat quat_1 = Quat::Zero;
	float quat_2_x = 19.2f;
	float quat_2_y = -8.4f;
	float quat_2_z = 7.5f;
	float quat_2_w = 12.6f;
	Quat quat_2 = Quat(quat_2_w, quat_2_x, quat_2_y, quat_2_z);

	// isZero
	EXPECT_TRUE(quat_1.IsZero());
	EXPECT_FALSE(quat_2.IsZero());

	// Equals
	EXPECT_FALSE(quat_1.Equals(quat_2));
	EXPECT_TRUE(quat_2.Equals(quat_2));

	//== operator
	EXPECT_FALSE(quat_1 == quat_2);
	EXPECT_TRUE(quat_2 == quat_2);

	// != operator
	EXPECT_TRUE(quat_1 != quat_2);
	EXPECT_FALSE(quat_2 != quat_2);
}

/**
*	\brief Unit test for Quat accessors fuction
*/
TEST(QuaternionUnitTest, Accessors)
{

	Quat quat = Quat(2.8f, -6.8f, 4.5f, 8.4f);
	const float* quat_data = quat.Data();

	EXPECT_FLOAT_EQ(quat_data[0], quat.W);
	EXPECT_FLOAT_EQ(quat_data[1], quat.X);
	EXPECT_FLOAT_EQ(quat_data[2], quat.Y);
	EXPECT_FLOAT_EQ(quat_data[3], quat.Z);
}

/**
*	\brief Unit test length computation of Quat
*/
TEST(QuaternionUnitTest, Length)
{
	Quat quat_1 = Quat(3.8f, -5.2f, 7.2f, 5.2f);
	Quat quat_2 = Quat::Identity;

	float sqrLen = 120.36;
	float len = 10.9708705f;

	Quat quat_1_normalized = quat_1 / len;

	EXPECT_FLOAT_EQ(quat_1.Length(), len);
	EXPECT_FLOAT_EQ(quat_2.Length(), 1.f);

	EXPECT_FLOAT_EQ(quat_1.SquaredLength(), sqrLen);
	EXPECT_FLOAT_EQ(quat_2.SquaredLength(), 1.f);

	EXPECT_EQ(quat_2.IsNormalized(), true);

	EXPECT_TRUE(quat_1_normalized.Equals(quat_1.GetNormalized(), 0.000001f));
	EXPECT_EQ(quat_2.GetNormalized(), quat_2);

	EXPECT_TRUE(quat_1_normalized.Equals(quat_1.Normalize(), 0.000001f));
	EXPECT_EQ(quat_2.Normalize(), quat_2);

	EXPECT_EQ(quat_2.IsNormalized(), true);
}

TEST(QuaternionUnitTest, Euler)
{
	Quat left_quat = Quat::FromEuler(Vec3::Left);
	Vec3 left_quat_euler = left_quat.Euler();

	EXPECT_FLOAT_EQ(left_quat_euler.X, -1.f);
	EXPECT_FLOAT_EQ(left_quat_euler.Y, 0.f);
	EXPECT_FLOAT_EQ(left_quat_euler.Z, 0.f);

	Quat one_quat = Quat::FromEuler(Vec3::One);
	Vec3 one_quat_euler = one_quat.Euler();

	EXPECT_FLOAT_EQ(one_quat_euler.X, 1.f);
	EXPECT_FLOAT_EQ(one_quat_euler.Y, 1.f);
	EXPECT_FLOAT_EQ(one_quat_euler.Z, 1.f);
}

TEST(QuaternionUnitTest, From_Euler)
{
	Quat left_quat = Quat::FromEuler(Vec3::Left);

	EXPECT_FLOAT_EQ(left_quat.W, 0.999961923f);
	EXPECT_FLOAT_EQ(left_quat.X, -0.008726539f);
	EXPECT_FLOAT_EQ(left_quat.Y, 0.f);
	EXPECT_FLOAT_EQ(left_quat.Z, 0.f);

	Quat one_quat = Quat::FromEuler(Vec3::One);

	EXPECT_FLOAT_EQ(one_quat.W, 0.999886437f);
	EXPECT_FLOAT_EQ(one_quat.X, 0.008649725f);
	EXPECT_FLOAT_EQ(one_quat.Y, 0.008802024f);
	EXPECT_FLOAT_EQ(one_quat.Z, 0.008649725f);

}

TEST(QuaternionUnitTest, Inverse)
{
	Quat quat_1 = Quat(2.8f, -6.8f, 4.5f, 8.4f);

	Quat quat_1_inversed = quat_1.GetInverse();

	EXPECT_FLOAT_EQ(quat_1_inversed.W, 0.019325f);
	EXPECT_FLOAT_EQ(quat_1_inversed.X, 0.046932161f);
	EXPECT_FLOAT_EQ(quat_1_inversed.Y, -0.031058047f);
	EXPECT_FLOAT_EQ(quat_1_inversed.Z, -0.05797502f);

	Quat quat_1_inverse = quat_1.Inverse();

	EXPECT_FLOAT_EQ(quat_1_inverse.W, 0.019325f);
	EXPECT_FLOAT_EQ(quat_1_inverse.X, 0.046932161f);
	EXPECT_FLOAT_EQ(quat_1_inverse.Y, -0.031058047f);
	EXPECT_FLOAT_EQ(quat_1_inverse.Z, -0.05797502f);

	Quat quat_2 = Quat(3.8f, -5.2f, 7.2f, 5.2f);

	Quat quat_2_inversed = quat_2.GetInverse();

	EXPECT_FLOAT_EQ(quat_2_inversed.W, 0.031571954f);
	EXPECT_FLOAT_EQ(quat_2_inversed.X, 0.043203726f);
	EXPECT_FLOAT_EQ(quat_2_inversed.Y, -0.059820544f);
	EXPECT_FLOAT_EQ(quat_2_inversed.Z, -0.043203726f);

	Quat quat_2_inverse = quat_2.Inverse();

	EXPECT_FLOAT_EQ(quat_2_inverse.W, 0.031571954f);
	EXPECT_FLOAT_EQ(quat_2_inverse.X, 0.043203726f);
	EXPECT_FLOAT_EQ(quat_2_inverse.Y, -0.059820544f);
	EXPECT_FLOAT_EQ(quat_2_inverse.Z, -0.043203726f);
}