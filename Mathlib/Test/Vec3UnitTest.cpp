#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Generate a random Vec3
*/
Vec3 GenerateVec3()
{
	float vec_x = static_cast<float>(Math::Random(-100, 100));
	float vec_y = static_cast<float>(Math::Random(-100, 100));
	float vec_z = static_cast<float>(Math::Random(-100, 100));
	return Vec3(vec_x, vec_y, vec_z);
}

/**
*	\brief Unit test for constants values
*/
TEST(Vec3UnitTest, Constant)
{
	Math::InitializeRandom();

	EXPECT_EQ(Vec3::Zero, Vec3(0.f, 0.f, 0.f));
	EXPECT_EQ(Vec3::One, Vec3(1.f, 1.f, 1.f));
	EXPECT_EQ(Vec3::Right, Vec3(1.f, 0.f, 0.f));
	EXPECT_EQ(Vec3::Left, Vec3(-1.f, 0.f, 0.f));
	EXPECT_EQ(Vec3::Up, Vec3(0.f, 1.f, 0.f));
	EXPECT_EQ(Vec3::Down, Vec3(0.f, -1.f, 0.f));
	EXPECT_EQ(Vec3::Forward, Vec3(0.f, 0.f, 1.f));
	EXPECT_EQ(Vec3::Backward, Vec3(0.f, 0.f, -1.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Vec3UnitTest, Constructor)
{
	Vec3 vec_1;
	EXPECT_EQ(vec_1, Vec3(0.f, 0.f, 0.f));

	float vec_2_x = static_cast<float>(Math::Random(-100, 100));
	float vec_2_y = static_cast<float>(Math::Random(-100, 100));
	float vec_2_z = static_cast<float>(Math::Random(-100, 100));
	Vec3 vec_2 = Vec3(vec_2_x, vec_2_y, vec_2_z);

	EXPECT_FLOAT_EQ(vec_2.X, vec_2_x);
	EXPECT_FLOAT_EQ(vec_2.Y, vec_2_y);
	EXPECT_FLOAT_EQ(vec_2.Z, vec_2_z);

	float vec_3_xyz = static_cast<float>(Math::Random(-100, 100));
	Vec3 vec_3 = Vec3(vec_3_xyz);

	EXPECT_FLOAT_EQ(vec_3.X, vec_3_xyz);
	EXPECT_FLOAT_EQ(vec_3.Y, vec_3_xyz);
	EXPECT_FLOAT_EQ(vec_3.Z, vec_3_xyz);

	Vec3 vec_4 = Vec3(vec_2);

	EXPECT_EQ(vec_4, vec_2);

	Vec2 vec_5 = Vec2(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));
	float vec_5_z = static_cast<float>(Math::Random(-100, 100));

	EXPECT_EQ(Vec3(vec_5, vec_5_z), Vec3(vec_5.X, vec_5.Y, vec_5_z));

	Vec4 vec_6 = Vec4(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));
	EXPECT_EQ(Vec3(vec_6), Vec3(vec_6.X, vec_6.Y, vec_6.Z));
}

/**
*	\brief Unit test for equality and comparison between Vec3
*/
TEST(Vec3UnitTest, Equality)
{
	Vec3 vec_1 = Vec3::Zero;
	float vec_2_x = static_cast<float>(Math::Random(1, 100));
	float vec_2_y = static_cast<float>(Math::Random(1, 100));
	float vec_2_z = static_cast<float>(Math::Random(1, 100));
	Vec3 vec_2 = Vec3(vec_2_x, vec_2_y, vec_2_z);

	// isZero()
	EXPECT_TRUE(vec_1.IsZero());
	EXPECT_FALSE(vec_2.IsZero());
	EXPECT_FALSE(vec_1.Equals(vec_2));
	EXPECT_TRUE(vec_2.Equals(vec_2));
	EXPECT_FALSE(vec_1 == vec_2);
	EXPECT_TRUE(vec_2 == vec_2);
	EXPECT_TRUE(vec_1 != vec_2);
	EXPECT_FALSE(vec_2 != vec_2);
}

/**
*	\brief Unit test length computation of Vec3
*/
TEST(Vec3UnitTest, Length)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = Vec3::Backward;

	float sqrLen = vec_1.X * vec_1.X + vec_1.Y * vec_1.Y + vec_1.Z * vec_1.Z;
	float len = Math::Sqrt(sqrLen);

	EXPECT_FLOAT_EQ(vec_1.Length(), len);
	EXPECT_FLOAT_EQ(vec_2.Length(), 1.f);

	EXPECT_FLOAT_EQ(vec_1.SquaredLength(), sqrLen);
	EXPECT_FLOAT_EQ(vec_2.SquaredLength(), 1.f);

	EXPECT_EQ(vec_2.IsNormalized(), true);

	EXPECT_EQ(vec_1.GetNormalized(), Vec3(vec_1.X / len, vec_1.Y / len, vec_1.Z / len));
	EXPECT_EQ(vec_2.GetNormalized(), vec_2);

	EXPECT_EQ(vec_1.Normalize(), Vec3(vec_1.X / len, vec_1.Y / len, vec_1.Z / len));
	EXPECT_EQ(vec_2.Normalize(), vec_2);

	EXPECT_EQ(vec_1.IsNormalized(), true);
}

/**
*	\brief Unit test for projection fuction
*/
TEST(Vec3UnitTest, Projection)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = Vec3(1.f, 0.f, 0.f);

	EXPECT_EQ(vec_1.ProjectOn(vec_2), Vec3(vec_1.X, 0.f, 0.f));
}

/**
*	\brief Unit test for dot product fuction
*/
TEST(Vec3UnitTest, DotProduct)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = GenerateVec3();

	float dot_result = vec_1.X * vec_2.X + vec_1.Y * vec_2.Y + vec_1.Z * vec_2.Z;

	EXPECT_EQ(Vec3::DotProduct(vec_1, vec_2), dot_result);
}

/**
*	\brief Unit test for cross product fuction
*/
TEST(Vec3UnitTest, CrossProduct)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = GenerateVec3();

	Vec3 cross_result =  Vec3(vec_1.Y * vec_2.Z - vec_1.Z * vec_2.Y,
		vec_1.Z * vec_2.X - vec_1.X * vec_2.Z,
		vec_1.X * vec_2.Y - vec_1.Y * vec_2.X);

	EXPECT_EQ(Vec3::CrossProduct(vec_1, vec_2), cross_result);
}

/**
*	\brief Unit test for cross angle fuction
*/
TEST(Vec3UnitTest, Angle)
{
	Vec3 vec_1 = Vec3(1.0f, 1.0f, 0.f);
	Vec3 vec_2 = Vec3(-1.f, 1.f, 0.f);
	EXPECT_EQ(Math::Equals(Vec3::Angle(vec_1, vec_2), 90.f * static_cast<float>(Math::DegToRad), 0.001f), true);
}

/**
*	\brief Unit test for distance and squared distance between two Vec3 fuctions
*/
TEST(Vec3UnitTest, Distance)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = GenerateVec3();

	Vec3 vec_3 = vec_2 - vec_1;

	float sqrLen = vec_3.X * vec_3.X + vec_3.Y * vec_3.Y + vec_3.Z * vec_3.Z;
	float len = Math::Sqrt(sqrLen);

	EXPECT_FLOAT_EQ(Vec3::Distance(vec_1, vec_2), len);
	EXPECT_FLOAT_EQ(Vec3::SqrDistance(vec_1, vec_2), sqrLen);
}

/**
*	\brief Unit test for lerp fuction
*/
TEST(Vec3UnitTest, Lerp)
{
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = GenerateVec3();

	float alpha = float(Math::Random(0, 10))/ 10.f;

	Vec3 vec_3 = vec_1 + (vec_2 - vec_1) * alpha;

	EXPECT_EQ(Vec3::Lerp(vec_1, vec_2, alpha), vec_3);
}

/**
*	\brief Unit test for slerp fuction
*/
TEST(Vec3UnitTest, SLerp)
{
	Vec3 vec_1 = Vec3(1.0f, 1.0f, 0.f);
	Vec3 vec_2 = Vec3(-1.f, 1.f, 0.f);
	Vec3 vec_3 = Vec3(0.f, vec_1.Length(), 0.f);

	EXPECT_EQ(Vec3::SLerp(vec_1, vec_2, 0.5f), vec_3);
}

/**
*	\brief Unit test for Vec3 accessors fuction
*/
TEST(Vec3UnitTest, Accessors)
{
	Vec3 vec_1 = GenerateVec3();

	const float* vec_1_data = vec_1.Data();

	EXPECT_EQ(vec_1_data[0], vec_1.X);
	EXPECT_EQ(vec_1_data[1], vec_1.Y);
	EXPECT_EQ(vec_1_data[2], vec_1.Z);

	Vec3 vec_2 = GenerateVec3();
	const float* vec_2_data = vec_2.Data();

	EXPECT_EQ(vec_2_data[0], vec_2.X);
	EXPECT_EQ(vec_2_data[1], vec_2.Y);
	EXPECT_EQ(vec_2_data[2], vec_2.Z);
}

/**
 * \brief Unit test for Vec3 operators
*/
TEST(Vec3UnitTest, Operator)
{
	// operator- (invert vector)
	Vec3 vec_1 = GenerateVec3();
	Vec3 vec_2 = GenerateVec3();

	EXPECT_EQ(-vec_1, Vec3(-vec_1.X, -vec_1.Y, -vec_1.Z));
	EXPECT_EQ(-vec_2, Vec3(-vec_2.X, -vec_2.Y, -vec_2.Z));

	// operator+(Vec3)
	EXPECT_EQ(vec_1 + vec_2, Vec3(vec_1.X + vec_2.X, vec_1.Y + vec_2.Y, vec_1.Z + vec_2.Z));

	// operator-(Vec3)
	EXPECT_EQ(vec_1 - vec_2, Vec3(vec_1.X - vec_2.X, vec_1.Y - vec_2.Y, vec_1.Z - vec_2.Z));

	// operator*(Vec3)
	EXPECT_EQ(vec_1 * vec_2, Vec3(vec_1.X * vec_2.X, vec_1.Y * vec_2.Y, vec_1.Z * vec_2.Z));

	// operator/(Vec3)
	EXPECT_EQ(vec_1 / vec_2, Vec3(vec_1.X / vec_2.X, vec_1.Y / vec_2.Y, vec_1.Z / vec_2.Z));

	// operator+=(Vec3)

	vec_1 = GenerateVec3();
	vec_2 = GenerateVec3();
	Vec3 vec_3 = vec_1;
	vec_1 += vec_2;

	EXPECT_EQ(vec_1, vec_3 + vec_2);

	Vec3 vec_4 = GenerateVec3();
	Vec3 vec_5 = GenerateVec3();
	Vec3 vec_6 = vec_4;
	vec_4 += vec_5;

	EXPECT_EQ(vec_4, vec_5 + vec_6);


	// operator-=(Vec3)

	vec_1 = GenerateVec3();
	vec_2 = GenerateVec3();
	vec_3 = vec_1;
	vec_1 -= vec_2;

	EXPECT_EQ(vec_1, vec_3 - vec_2);

	vec_4 = GenerateVec3();
	vec_5 = GenerateVec3();
	vec_6 = vec_4;
	vec_4 -= vec_5;

	EXPECT_EQ(vec_4, vec_6 - vec_5);


	// operator*=(Vec3)

	vec_1 = GenerateVec3();
	vec_2 = GenerateVec3();
	vec_3 = vec_1;
	vec_1 *= vec_2;

	EXPECT_EQ(vec_1, vec_3 * vec_2);

	vec_4 = GenerateVec3();
	vec_5 = GenerateVec3();
	vec_6 = vec_4;
	vec_4 *= vec_5;

	EXPECT_EQ(vec_4, vec_5 * vec_6);

	// operator/=(Vec3)

	vec_1 = GenerateVec3();
	vec_2 = GenerateVec3();
	vec_3 = vec_1;
	vec_1 /= vec_2;

	EXPECT_EQ(vec_1, vec_3 / vec_2);

	vec_4 = GenerateVec3();
	vec_5 = GenerateVec3();
	vec_6 = vec_4;
	vec_4 /= vec_5;

	EXPECT_EQ(vec_4, vec_6 / vec_5);

	// operator+(float)
	vec_1 = GenerateVec3();
	float scale = static_cast<float>(Math::Random(1, 100));
	
	EXPECT_EQ(vec_1 + scale, Vec3(vec_1.X + scale, vec_1.Y + scale, vec_1.Z + scale));

	// operator-(float)
	EXPECT_EQ(vec_1 - scale, Vec3(vec_1.X - scale, vec_1.Y - scale, vec_1.Z - scale));

	// operator*(float)
	EXPECT_EQ(vec_1 * scale, Vec3(vec_1.X * scale,  vec_1.Y * scale, vec_1.Z * scale));

	// operator/(float)
	EXPECT_EQ(vec_1 / scale, Vec3(vec_1.X / scale, vec_1.Y / scale, vec_1.Z / scale));

	// operator+=(float)
	vec_1 = GenerateVec3();
	vec_2 = vec_1;
	vec_1 += scale;

	EXPECT_EQ(vec_1, vec_2 + scale);

	// operator-=(float)
	vec_1 = GenerateVec3();
	vec_2 = vec_1;
	vec_1 -= scale;

	EXPECT_EQ(vec_1, vec_2 - scale);

	// operator*=(float)
	vec_1 = GenerateVec3();
	vec_2 = vec_1;
	vec_1 *= scale;

	EXPECT_EQ(vec_1, vec_2 * scale);

	// operator/=(float)
	vec_1 = GenerateVec3();
	vec_2 = vec_1;
	vec_1 /= scale;

	EXPECT_EQ(vec_1, vec_2 / scale);
}