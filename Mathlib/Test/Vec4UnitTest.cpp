#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Generate a random Vec4
*/
Vec4 GenerateVec4()
{
	float vec_x = static_cast<float>(Math::Random(-100, 100));
	float vec_y = static_cast<float>(Math::Random(-100, 100));
	float vec_z = static_cast<float>(Math::Random(-100, 100));
	float vec_w = static_cast<float>(Math::Random(-100, 100));
	return Vec4(vec_x, vec_y, vec_z, vec_w);
}

/**
*	\brief Unit test for constants values
*/
TEST(Vec4UnitTest, Constant)
{
	Math::InitializeRandom();

	EXPECT_EQ(Vec4::Zero, Vec4(0.f, 0.f, 0.f, 0.f));
	EXPECT_EQ(Vec4::One, Vec4(1.f, 1.f, 1.f, 0.f));
	EXPECT_EQ(Vec4::Right, Vec4(1.f, 0.f, 0.f, 0.f));
	EXPECT_EQ(Vec4::Left, Vec4(-1.f, 0.f, 0.f, 0.f));
	EXPECT_EQ(Vec4::Up, Vec4(0.f, 1.f, 0.f, 0.f));
	EXPECT_EQ(Vec4::Down, Vec4(0.f, -1.f, 0.f, 0.f));
	EXPECT_EQ(Vec4::Forward, Vec4(0.f, 0.f, 1.f, 0.f));
	EXPECT_EQ(Vec4::Backward, Vec4(0.f, 0.f, -1.f, 0.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Vec4UnitTest, Constructor)
{
	Vec4 vec_1;
	EXPECT_EQ(vec_1, Vec4(0.f, 0.f, 0.f, 0.f));

	float vec_2_x = static_cast<float>(Math::Random(-100, 100));
	float vec_2_y = static_cast<float>(Math::Random(-100, 100));
	float vec_2_z = static_cast<float>(Math::Random(-100, 100));
	float vec_2_w = static_cast<float>(Math::Random(-100, 100));
	Vec4 vec_2 = Vec4(vec_2_x, vec_2_y, vec_2_z, vec_2_w);

	EXPECT_FLOAT_EQ(vec_2.X, vec_2_x);
	EXPECT_FLOAT_EQ(vec_2.Y, vec_2_y);
	EXPECT_FLOAT_EQ(vec_2.Z, vec_2_z);
	EXPECT_FLOAT_EQ(vec_2.W, vec_2_w);

	float vec_3_xyzw = static_cast<float>(Math::Random(-100, 100));
	Vec4 vec_3 = Vec4(vec_3_xyzw);

	EXPECT_FLOAT_EQ(vec_3.X, vec_3_xyzw);
	EXPECT_FLOAT_EQ(vec_3.Y, vec_3_xyzw);
	EXPECT_FLOAT_EQ(vec_3.Z, vec_3_xyzw);

	Vec4 vec_4 = Vec4(vec_2);

	EXPECT_EQ(vec_4, vec_2);

	Vec2 vec_5 = Vec2(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));
	float vec_5_z = static_cast<float>(Math::Random(-100, 100));
	float vec_5_w = static_cast<float>(Math::Random(-100, 100));

	EXPECT_EQ(Vec4(vec_5, vec_5_z, vec_5_w), Vec4(vec_5.X, vec_5.Y, vec_5_z, vec_5_w));

	Vec3 vec_6 = Vec3(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));
	float vec_6_z = static_cast<float>(Math::Random(-100, 100));
	EXPECT_EQ(Vec4(vec_6, vec_6_z), Vec4(vec_6.X, vec_6.Y, vec_6.Z, vec_6_z));
}

/**
*	\brief Unit test for equality and comparison between Vec4
*/
TEST(Vec4UnitTest, Equality)
{
	Vec4 vec_1 = Vec4::Zero;
	float vec_2_x = static_cast<float>(Math::Random(1, 100));
	float vec_2_y = static_cast<float>(Math::Random(1, 100));
	float vec_2_z = static_cast<float>(Math::Random(1, 100));
	float vec_2_w = static_cast<float>(Math::Random(1, 100));
	Vec4 vec_2 = Vec4(vec_2_x, vec_2_y, vec_2_z, vec_2_w);

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
*	\brief Unit test for Vec4 accessors fuction
*/
TEST(Vec4UnitTest, Accessors)
{
	Vec4 vec_1 = GenerateVec4();

	const float* vec_1_data = vec_1.Data();

	EXPECT_EQ(vec_1_data[0], vec_1.X);
	EXPECT_EQ(vec_1_data[1], vec_1.Y);
	EXPECT_EQ(vec_1_data[2], vec_1.Z);
	EXPECT_EQ(vec_1_data[3], vec_1.W);

	Vec4 vec_2 = GenerateVec4();
	const float* vec_2_data = vec_2.Data();

	EXPECT_EQ(vec_2_data[0], vec_2.X);
	EXPECT_EQ(vec_2_data[1], vec_2.Y);
	EXPECT_EQ(vec_2_data[2], vec_2.Z);
	EXPECT_EQ(vec_2_data[3], vec_2.W);
}

/**
*	\brief Unit test length computation of Vec4
*/
TEST(Vec4UnitTest, Length)
{
	Vec4 vec_1 = GenerateVec4();
	Vec4 vec_2 = Vec4::Backward;

	float sqrLen = vec_1.X * vec_1.X + vec_1.Y * vec_1.Y + vec_1.Z * vec_1.Z + vec_1.W * vec_1.W;
	float len = Math::Sqrt(sqrLen);

	EXPECT_FLOAT_EQ(vec_1.Length(), len);
	EXPECT_FLOAT_EQ(vec_2.Length(), 1.f);

	EXPECT_FLOAT_EQ(vec_1.SquaredLength(), sqrLen);
	EXPECT_FLOAT_EQ(vec_2.SquaredLength(), 1.f);

	EXPECT_EQ(vec_2.IsNormalized(), true);

	EXPECT_EQ(vec_1.GetNormalized(), Vec4(vec_1.X / len, vec_1.Y / len, vec_1.Z / len, vec_1.W / len));
	EXPECT_EQ(vec_2.GetNormalized(), vec_2);

	EXPECT_EQ(vec_1.Normalize(), Vec4(vec_1.X / len, vec_1.Y / len, vec_1.Z / len, vec_1.W / len));
	EXPECT_EQ(vec_2.Normalize(), vec_2);

	EXPECT_EQ(vec_1.IsNormalized(), true);
}

/**
*	\brief Unit test for distance and squared distance between two vec4 fuctions
*/
TEST(Vec4UnitTest, Distance)
{
	Vec4 vec_1 = GenerateVec4();
	Vec4 vec_2 = GenerateVec4();

	Vec4 vec_3 = vec_2 - vec_1;

	float sqrLen = vec_3.X * vec_3.X + vec_3.Y * vec_3.Y + vec_3.Z * vec_3.Z;
	float len = Math::Sqrt(sqrLen);

	EXPECT_FLOAT_EQ(Vec3::Distance(vec_1, vec_2), len);
	EXPECT_FLOAT_EQ(Vec3::SqrDistance(vec_1, vec_2), sqrLen);
}

/**
*	\brief Unit test for lerp fuction
*/
TEST(Vec4UnitTest, Lerp)
{
	Vec4 vec_1 = GenerateVec4();
	Vec4 vec_2 = GenerateVec4();

	float alpha = float(Math::Random(0, 10)) / 10.f;

	Vec4 vec_3 = vec_1 + (vec_2 - vec_1) * alpha;

	EXPECT_EQ(Vec3::Lerp(vec_1, vec_2, alpha), vec_3);
}

/**
 * \brief Unit test for Vec4 operators
*/
TEST(Vec4UnitTest, Operator)
{
	// operator- (invert vector)
	Vec4 vec_1 = GenerateVec4();
	Vec4 vec_2 = GenerateVec4();

	EXPECT_EQ(-vec_1, Vec4(-vec_1.X, -vec_1.Y, -vec_1.Z, -vec_1.W));
	EXPECT_EQ(-vec_2, Vec4(-vec_2.X, -vec_2.Y, -vec_2.Z, -vec_2.W));

	// operator+(Vec4)
	EXPECT_EQ(vec_1 + vec_2, Vec4(vec_1.X + vec_2.X, vec_1.Y + vec_2.Y, vec_1.Z + vec_2.Z, vec_1.W + vec_2.W));

	// operator-(Vec4)
	EXPECT_EQ(vec_1 - vec_2, Vec4(vec_1.X - vec_2.X, vec_1.Y - vec_2.Y, vec_1.Z - vec_2.Z, vec_1.W - vec_2.W));

	// operator*(Vec4)
	EXPECT_EQ(vec_1 * vec_2, Vec4(vec_1.X * vec_2.X, vec_1.Y * vec_2.Y, vec_1.Z * vec_2.Z, vec_1.W * vec_2.W));

	Vec4 test_result_1 = vec_1 / vec_2;
	Vec4 test_result_2 = Vec4(vec_1.X / vec_2.X, vec_1.Y / vec_2.Y, vec_1.Z / vec_2.Z, vec_1.W / vec_2.W);

	bool test_compare = test_result_1 == test_result_2;

	// operator/(Vec4)
	EXPECT_EQ(vec_1 / vec_2, Vec4(vec_1.X / vec_2.X, vec_1.Y / vec_2.Y, vec_1.Z / vec_2.Z, vec_1.W / vec_2.W));

	// operator+=(Vec4)

	vec_1 = GenerateVec4();
	vec_2 = GenerateVec4();
	Vec4 vec_3 = vec_1;
	vec_1 += vec_2;

	EXPECT_EQ(vec_1, vec_3 + vec_2);

	Vec4 vec_4 = GenerateVec4();
	Vec4 vec_5 = GenerateVec4();
	Vec4 vec_6 = vec_4;
	vec_4 += vec_5;

	EXPECT_EQ(vec_4, vec_5 + vec_6);


	// operator-=(Vec4)

	vec_1 = GenerateVec4();
	vec_2 = GenerateVec4();
	vec_3 = vec_1;
	vec_1 -= vec_2;

	EXPECT_EQ(vec_1, vec_3 - vec_2);

	vec_4 = GenerateVec4();
	vec_5 = GenerateVec4();
	vec_6 = vec_4;
	vec_4 -= vec_5;

	EXPECT_EQ(vec_4, vec_6 - vec_5);


	// operator*=(Vec4)

	vec_1 = GenerateVec4();
	vec_2 = GenerateVec4();
	vec_3 = vec_1;
	vec_1 *= vec_2;

	EXPECT_EQ(vec_1, vec_3 * vec_2);

	vec_4 = GenerateVec4();
	vec_5 = GenerateVec4();
	vec_6 = vec_4;
	vec_4 *= vec_5;

	EXPECT_EQ(vec_4, vec_5 * vec_6);

	// operator/=(Vec4)
	vec_1 = GenerateVec4();
	vec_2 = GenerateVec4();
	vec_3 = vec_1;
	vec_1 /= vec_2;

	EXPECT_EQ(vec_1, vec_3 / vec_2);

	vec_4 = GenerateVec4();
	vec_5 = GenerateVec4();
	vec_6 = vec_4;
	vec_4 /= vec_5;

	EXPECT_EQ(vec_4, vec_6 / vec_5);

	vec_1 = GenerateVec4();
	float scale = static_cast<float>(Math::Random(1, 100));

	// operator+(float)
	EXPECT_EQ(vec_1 + scale, Vec4(vec_1.X + scale, vec_1.Y + scale, vec_1.Z + scale, vec_1.W + scale));
	
	// operator-(float)
	EXPECT_EQ(vec_1 - scale, Vec4(vec_1.X - scale, vec_1.Y - scale, vec_1.Z - scale, vec_1.W - scale));

	// operator*(float)
	EXPECT_EQ(vec_1 * scale, Vec4(vec_1.X * scale, vec_1.Y * scale, vec_1.Z * scale, vec_1.W * scale));

	// operator/(float)
	EXPECT_EQ(vec_1 / scale, Vec4(vec_1.X / scale, vec_1.Y / scale, vec_1.Z / scale, vec_1.W / scale));

	// operator+=(float)
	vec_1 = GenerateVec4();
	vec_2 = vec_1;
	vec_1 += scale;

	EXPECT_EQ(vec_1, vec_2 + scale);

	// operator-=(float)
	vec_1 = GenerateVec4();
	vec_2 = vec_1;
	vec_1 -= scale;

	EXPECT_EQ(vec_1, vec_2 - scale);
	
	// operator*=(float)
	vec_1 = GenerateVec4();
	vec_2 = vec_1;
	vec_1 *= scale;

	EXPECT_EQ(vec_1, vec_2 * scale);

	// operator/=(float)
	vec_1 = GenerateVec4();
	vec_2 = vec_1;
	vec_1 /= scale;

	EXPECT_EQ(vec_1, vec_2 / scale);
}