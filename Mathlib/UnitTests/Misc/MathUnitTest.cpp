#include <gtest/gtest.h>

#include <Collections/Mathlib.hpp>


using namespace Mathlib;

/**
*	\brief Unit test for constants value
*/
TEST(MathUnitTest, Constants)
{
	EXPECT_FLOAT_EQ(Math::Pi, 3.1415926535897932384f);
	EXPECT_FLOAT_EQ(Math::DegToRad, 3.1415926535897932384f / 180.0f);
	EXPECT_FLOAT_EQ(Math::RadToDeg, 180.0f / 3.1415926535897932384f);
}

/**
*	\brief Unit test Absolute value functions
*/
TEST(MathUnitTest, Abs)
{
	EXPECT_EQ(Math::Abs(10), 10);
	EXPECT_EQ(Math::Abs(-64750), 64750);
}

/**
*	\brief Unit test for value sign getter functions
*/
TEST(MathUnitTest, Sign)
{
	EXPECT_EQ(Math::Sign(10), 1);
	EXPECT_EQ(Math::Sign(-64750), -1);

	EXPECT_EQ(Math::Sign(84565.65454f), 1);
	EXPECT_EQ(Math::Sign(-561.5646f), -1);
}

/**
*	\brief Unit test for Min, Max and Clamp functions
*/
TEST(MathUnitTest, Min_Max_Clamp)
{
	//Min
	EXPECT_EQ(Math::Min(54, 86), 54);
	EXPECT_EQ(Math::Min(584, -5423), -5423);

	EXPECT_FLOAT_EQ(Math::Min(647.554f, 0.152f), 0.152f);
	EXPECT_FLOAT_EQ(Math::Min(4584.843f, 84165.844f), 4584.843f);

	//Max
	EXPECT_EQ(Math::Max(54, 86), 86);
	EXPECT_EQ(Math::Max(584, -5423), 584);

	EXPECT_FLOAT_EQ(Math::Max(647.554f, 0.152f), 647.554f);
	EXPECT_FLOAT_EQ(Math::Max(4584.843f, 84165.844f), 84165.844f);

	//Clamp
	EXPECT_EQ(Math::Clamp(54, 12, 73), 54);
	EXPECT_EQ(Math::Clamp(-3, 0, 86), 0);
	EXPECT_EQ(Math::Clamp(100, 0, 86), 86);

	EXPECT_FLOAT_EQ(Math::Clamp(4.98f, 1.89f, 7.874f), 4.98f);
	EXPECT_FLOAT_EQ(Math::Clamp(-3.8974f, 2.841f, 15.695f), 2.841f);
	EXPECT_FLOAT_EQ(Math::Clamp(99.84f, 45.95f, 86.89848f), 86.89848f);
}

/**
*	\brief Unit test for power and square root functions
*/
TEST(MathUnitTest, Pow_Sqrt)
{
	//Pow
	EXPECT_EQ(Math::Pow(4, 5), 1024);
	EXPECT_EQ(Math::Pow(7, 3), 343);

	EXPECT_FLOAT_EQ(Math::Pow(2.5f, 3.f), 15.625f);
	EXPECT_FLOAT_EQ(Math::Pow(4.9f, 2.f), 24.01f);

	//Sqrt
	EXPECT_EQ(Math::Sqrt(9), 3);
	EXPECT_EQ(Math::Sqrt(1024), 32);

	EXPECT_FLOAT_EQ(Math::Sqrt(6.25f), 2.5f);
	EXPECT_FLOAT_EQ(Math::Sqrt(72.25f), 8.5f);
}

/**
*	\brief Unit test for Trigonometry functions
*/
TEST(MathUnitTest, Trigonometry)
{
	//Cos
	EXPECT_FLOAT_EQ(Math::Cos(Math::Pi), -1.f);
	EXPECT_FLOAT_EQ(Math::Cos(0.f), 1.f);

	//ACos
	EXPECT_TRUE(Math::Equals0(Math::ACos(1.f)));

	//Sin
	EXPECT_TRUE(Math::Equals0(Math::Sin(0.f)));
	EXPECT_FLOAT_EQ(Math::Sin(Math::Pi / 2.f), 1.f);

	//ASin
	EXPECT_TRUE(Math::Equals0(Math::ASin(0.f)));

	//Tan
	EXPECT_TRUE(Math::Equals0(Math::Tan(0.f)));


	EXPECT_TRUE(Math::Equals(Math::Tan(Math::Pi / 3.f), Math::Sqrt(3.f), Math::FloatEpsilon));

	//ATan
	EXPECT_TRUE(Math::Equals0(Math::ATan(0.f)));
	EXPECT_TRUE(Math::Equals(Math::ATan(Math::Sqrt(3.f)), Math::Pi / 3.f, Math::FloatEpsilon));
}

/**
*	\brief Unit test for Lerp function
*/
TEST(MathUnitTest, Lerp)
{
	EXPECT_FLOAT_EQ(Math::Lerp(0.f, 1.f, 0.5f), 0.5f);
	EXPECT_FLOAT_EQ(Math::Lerp(-15.f, 15.f, 0.75f), 7.5f);
}

/**
*	\brief Unit test for random number generating functions
*/
TEST(MathUnitTest, Random)
{
	Math::InitializeRandom();
	EXPECT_EQ(Math::Random() == Math::Random(), false);
}

/**
*	\brief Unit test for radian value computation
*/
TEST(MathUnitTest, Radian)
{
	EXPECT_FLOAT_EQ(Math::Radians(90.f), Math::Pi / 2.f);
	EXPECT_FLOAT_EQ(Math::Radians(180.f) , Math::Pi);
}

/**
*	\brief Unit test for degree value computation
*/
TEST(MathUnitTest, degree)
{
	EXPECT_FLOAT_EQ(Math::Degree(Math::Pi / 2.f), 90.f);
	EXPECT_FLOAT_EQ(Math::Degree(Math::Pi), 180.f);
}