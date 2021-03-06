#include <gtest/gtest.h>

#include <Collections/Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Unit test for constants values
*/
TEST(Vec2UnitTest, Constant)
{
	Math::InitializeRandom();
	EXPECT_EQ(Vec2::Zero, Vec2(0.f, 0.f));
	EXPECT_EQ(Vec2::One, Vec2(1.f, 1.f));
	EXPECT_EQ(Vec2::Right, Vec2(1.f, 0.f));
	EXPECT_EQ(Vec2::Left, Vec2(-1.f, 0.f));
	EXPECT_EQ(Vec2::Up, Vec2(0.f, 1.f));
	EXPECT_EQ(Vec2::Down, Vec2(0.f, -1.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Vec2UnitTest, Constructor)
{
	Vec2 vec_1;
	EXPECT_EQ(vec_1, Vec2(0.f, 0.f));

	float vec_2_x = static_cast<float>(Math::Random(-100, 100));
	float vec_2_y = static_cast<float>(Math::Random(-100, 100));
	Vec2 vec_2 = Vec2(vec_2_x, vec_2_y);

	EXPECT_FLOAT_EQ(vec_2.X, vec_2_x);
	EXPECT_FLOAT_EQ(vec_2.Y, vec_2_y);

	float vec_3_xy = static_cast<float>(Math::Random(-100, 100));
	Vec2 vec_3 = Vec2(vec_3_xy);

	EXPECT_FLOAT_EQ(vec_3.X, vec_3_xy);
	EXPECT_FLOAT_EQ(vec_3.Y, vec_3_xy);

	Vec2 vec_4 = Vec2(vec_2);

	EXPECT_EQ(vec_4, vec_2);

	Vec3 vec_5 = Vec3(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));

	EXPECT_EQ(Vec2(vec_5), Vec2(vec_5.X, vec_5.Y));

	Vec4 vec_6 = Vec4(static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)), static_cast<float>(Math::Random(-100, 100)));

	EXPECT_EQ(Vec2(vec_6), Vec2(vec_6.X, vec_6.Y));
}

/**
*	\brief Unit test for equality and comparison between Vec2
*/
TEST(Vec2UnitTest, Equality)
{
	Vec2 vec_1 = Vec2::Zero;
	float vec_2_x = static_cast<float>(Math::Random(1, 100));
	float vec_2_y = static_cast<float>(Math::Random(1, 100));
	Vec2 vec_2 = Vec2(vec_2_x, vec_2_y);

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
*	\brief Unit test for equality and comparison between Vec2
*/
TEST(Vec2UnitTest, Length)
{
	Vec2 vec_1 = Vec2(3.8f, -5.2f);
	Vec2 vec_2 = Vec2::Right;

	float sqrLen = 41.48f;
	float len = 6.440496f;

	Vec2 vec_1_normalized = vec_1 / len;

	EXPECT_FLOAT_EQ(vec_1.Length(), len);
	EXPECT_FLOAT_EQ(vec_2.Length(), 1.f);

	EXPECT_FLOAT_EQ(vec_1.SquaredLength(), sqrLen);
	EXPECT_FLOAT_EQ(vec_2.SquaredLength(), 1.f);

	EXPECT_EQ(vec_2.IsNormalized(), true);

	EXPECT_TRUE(vec_1_normalized.Equals(vec_1.GetNormalized(), 0.000001f));
	EXPECT_EQ(vec_2.GetNormalized(), vec_2);

	EXPECT_TRUE(vec_1_normalized.Equals(vec_1.Normalize(), 0.000001f));
	EXPECT_EQ(vec_2.Normalize(), vec_2);

	EXPECT_EQ(vec_1.IsNormalized(), true);
}

/**
*	\brief Unit test for projection fuction
*/
TEST(Vec2UnitTest, Projection)
{
	Vec2 vec_1 = Vec2(7.9f, 5.2f);
	Vec2 vec_2 = Vec3(1.f, 0.f, 0.f);

	EXPECT_EQ(vec_1.ProjectOn(vec_2), Vec2(7.9f, 0.f));
}

/**
*	\brief Unit test for dot product fuction
*/
TEST(Vec2UnitTest, DotProduct)
{
	Vec2 vec_1 = Vec2(15.7f, -4.3f);
	Vec2 vec_2 = Vec2(-3.3f, 7.5f);

	float dot_result = -84.06f;

	EXPECT_EQ(Vec3::DotProduct(vec_1, vec_2), dot_result);
}

/**
*	\brief Unit test for cross product fuction
*/
TEST(Vec2UnitTest, CrossProduct)
{
	Vec2 vec_1 = Vec2(12.1f, -7.8f);
	Vec2 vec_2 = Vec2(-22.5f, 6.5f);

	float cross_result = -96.85f;

	EXPECT_EQ(Vec2::CrossProduct(vec_1, vec_2), cross_result);
}

/**
*	\brief Unit test for cross angle fuction
*/
TEST(Vec2UnitTest, Angle)
{
	Vec2 vec_1 = Vec2(1.0f, 1.0f);
	Vec2 vec_2 = Vec2(-1.f, 1.f);
	EXPECT_FLOAT_EQ(Vec3::Angle(vec_1, vec_2), 90.f * static_cast<float>(Math::DegToRad));
}

/**
*	\brief Unit test for distance and squared distance between two Vec2 fuctions
*/
TEST(Vec2UnitTest, Distance)
{
	Vec2 vec_1 = Vec2(6.4f, 8.7f);
	Vec2 vec_2 = Vec2(-8.3f, 7.5f);

	Vec2 vec_3 = vec_2 - vec_1;

	float sqrLen = vec_3.X * vec_3.X + vec_3.Y * vec_3.Y;
	float len = Math::Sqrt(sqrLen);

	EXPECT_FLOAT_EQ(Vec2::Distance(vec_1, vec_2), len);
	EXPECT_FLOAT_EQ(Vec2::SqrDistance(vec_1, vec_2), sqrLen);
}

/**
*	\brief Unit test for lerp fuction
*/
TEST(Vec2UnitTest, Lerp)
{
	Vec2 vec_1 = Vec2(3.7f, 9.2f);
	Vec2 vec_2 = Vec2(-8.7f, -5.6f);

	float alpha = 0.7f;

	Vec2 vec_3 = vec_1 + (vec_2 - vec_1) * alpha;

	EXPECT_EQ(Vec3::Lerp(vec_1, vec_2, alpha), vec_3);
}

/**
*	\brief Unit test for slerp fuction
*/
TEST(Vec2UnitTest, SLerp)
{
	Vec2 vec_1 = Vec3(1.0f, 1.0f, 0.f);
	Vec2 vec_2 = Vec3(-1.f, 1.f, 0.f);
	Vec2 vec_3 = Vec3(0.f, vec_1.Length(), 0.f);

	EXPECT_EQ(Vec3::SLerp(vec_1, vec_2, 0.5f), vec_3);
}

/**
*	\brief Unit test for Vec2 accessors fuction
*/
TEST(Vec2UnitTest, Accessors)
{
	Vec2 vec_1 = Vec2(-8.6f, 4.8f);

	const float* vec_1_data = vec_1.Data();

	EXPECT_EQ(vec_1_data[0], vec_1.X);
	EXPECT_EQ(vec_1_data[1], vec_1.Y);

	Vec2 vec_2 = Vec2(2.8f, -6.8f);
	const float* vec_2_data = vec_2.Data();

	EXPECT_EQ(vec_2_data[0], vec_2.X);
	EXPECT_EQ(vec_2_data[1], vec_2.Y);
}

/**
 * \brief Unit test for Vec2 & Vec2 operators
*/
TEST(Vec2UnitTest, Operator_Vec2)
{
	// operator- (invert vector)
	Vec2 vec_1 = Vec2(-26.7f, 5.8f);
	Vec2 vec_2 = Vec2(5.1f, 18.6f);

	EXPECT_EQ(-vec_1, Vec2(26.7f, -5.8f));
	EXPECT_EQ(-vec_2, Vec2(-5.1f, -18.6f));

	// operator+(Vec2)
	EXPECT_EQ(vec_1 + vec_2, Vec2(vec_1.X + vec_2.X, vec_1.Y + vec_2.Y));

	// operator-(Vec2)
	EXPECT_EQ(vec_1 - vec_2, Vec2(vec_1.X - vec_2.X, vec_1.Y - vec_2.Y));

	// operator*(Vec2)
	EXPECT_EQ(vec_1 * vec_2, Vec2(vec_1.X * vec_2.X, vec_1.Y * vec_2.Y));

	// operator/(Vec2)
	EXPECT_EQ(vec_1 / vec_2, Vec2(vec_1.X / vec_2.X, vec_1.Y / vec_2.Y));

	// operator+=(Vec2)
	vec_1 = Vec2(15.7f, -4.3f);
	vec_2 = Vec2(8.1f, 15.f);
	Vec2 vec_3 = vec_1;
	vec_1 += vec_2;

	EXPECT_EQ(vec_1, vec_3 + vec_2);

	Vec2 vec_4 = Vec2(10.2f, -4.3f);
	Vec2 vec_5 = Vec2(-3.3f, 7.5f);
	Vec2 vec_6 = vec_4;
	vec_4 += vec_5;

	EXPECT_EQ(vec_4, vec_5 + vec_6);


	// operator-=(Vec2)

	vec_1 = Vec2(15.7f, -4.3f);
	vec_2 = Vec2(8.1f, 15.f);
	vec_3 = vec_1;
	vec_1 -= vec_2;

	EXPECT_EQ(vec_1, vec_3 - vec_2);

	vec_4 = Vec2(10.2f, -4.3f);
	vec_5 = Vec2(-3.3f, 7.5f);
	vec_6 = vec_4;
	vec_4 -= vec_5;

	EXPECT_EQ(vec_4, vec_6 - vec_5);


	// operator*=(Vec2)

	vec_1 = Vec2(15.7f, -4.3f);
	vec_2 = Vec2(8.1f, 15.f);
	vec_3 = vec_1;
	vec_1 *= vec_2;

	EXPECT_EQ(vec_1, vec_3 * vec_2);

	vec_4 = Vec2(10.2f, -4.3f);
	vec_5 = Vec2(-3.3f, 7.5f);
	vec_6 = vec_4;
	vec_4 *= vec_5;

	EXPECT_EQ(vec_4, vec_5 * vec_6);

	// operator/=(Vec2)

	vec_1 = Vec2(15.7f, -4.3f);
	vec_2 = Vec2(8.1f, 15.f);
	vec_3 = vec_1;
	vec_1 /= vec_2;

	EXPECT_EQ(vec_1, vec_3 / vec_2);

	vec_4 = Vec2(10.2f, -4.3f);
	vec_5 = Vec2(-3.3f, 7.5f);
	vec_6 = vec_4;
	vec_4 /= vec_5;

	EXPECT_EQ(vec_4, vec_6 / vec_5);
}

/**
 * \brief Unit test for Vec2 & float operators
*/
TEST(Vec2UnitTest, Operator_float)
{
	// operator+(float)
	Vec2 vec_1 = Vec2(5.3f, 19.2f);
	float scale = static_cast<float>(Math::Random(1, 100));

	EXPECT_EQ(vec_1 + scale, Vec2(vec_1.X + scale, vec_1.Y + scale));

	// operator-(float)
	EXPECT_EQ(vec_1 - scale, Vec2(vec_1.X - scale, vec_1.Y - scale));

	// operator*(float)
	EXPECT_EQ(vec_1 * scale, Vec2(vec_1.X * scale, vec_1.Y * scale));

	// operator/(float)
	EXPECT_EQ(vec_1 / scale, Vec2(vec_1.X / scale, vec_1.Y / scale));

	// operator+=(float)
	vec_1 = Vec2(-20.6f, 18.6f);
	Vec2 vec_2 = vec_1;
	vec_1 += scale;

	EXPECT_EQ(vec_1, vec_2 + scale);

	// operator-=(float)
	vec_1 = Vec2(23.7f, 15.4f);
	vec_2 = vec_1;
	vec_1 -= scale;

	EXPECT_EQ(vec_1, vec_2 - scale);

	// operator*=(float)
	vec_1 = Vec2(26.4f, -8.3f);
	vec_2 = vec_1;
	vec_1 *= scale;

	EXPECT_EQ(vec_1, vec_2 * scale);

	// operator/=(float)
	vec_1 = Vec2(8.4f, 10.48f);
	vec_2 = vec_1;
	vec_1 /= scale;

	EXPECT_EQ(vec_1, vec_2 / scale);
}