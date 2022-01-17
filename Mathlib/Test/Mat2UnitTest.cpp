#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Generate a random Mat2
*/
Mat2 GenerateMat2()
{
	float mat_m00 = static_cast<float>(Math::Random(-100, 100));
	float mat_m01 = static_cast<float>(Math::Random(-100, 100));
	float mat_m10 = static_cast<float>(Math::Random(-100, 100));
	float mat_m11 = static_cast<float>(Math::Random(-100, 100));
	return Mat2(mat_m00, mat_m01, mat_m10, mat_m11);
}

/**
*	\brief Unit test for constants values
*/
TEST(Mat2UnitTest, Constant)
{
	Math::InitializeRandom();
	EXPECT_EQ(Mat2::Zero, Mat2(0.f, 0.f, 0.f, 0.f));
	EXPECT_EQ(Mat2::Identity, Mat2(1.f, 0.f, 0.f, 1.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Mat2UnitTest, Constructor)
{
	Mat2 mat_1 = Mat2();

	EXPECT_EQ(mat_1, Mat2(0.f, 0.f, 0.f, 0.f));

	EXPECT_EQ(Mat2(-10.f), Mat2(-10.f, -10.f, -10.f, -10.f));
	
	EXPECT_EQ(Mat2(Vec2(5.f, 48.f), Vec2(12.f, 7.f)), Mat2(5.f, 48.f, 12.f, 7.f));
}

/**
*	\brief Unit test for rotation matrix constructors
*/
TEST(Mat2UnitTest, Rotation_matrix)
{
	Mat2 mat_1 = Mat2::RotationMatrix(Math::Pi / 2.f);

	EXPECT_TRUE(mat_1.Equals(Mat2(0.f, -1.f, 1.f, 0.f)));
}

/**
*	\brief Unit test for Scale matrix constructors
*/
TEST(Mat2UnitTest, Scale_matrix)
{
	Mat2 mat_1 = Mat2::ScaleMatrix(5.f);

	EXPECT_TRUE(mat_1.Equals(Mat2(5.f, 0.f, 0.f, 5.f)));
}

/**
*	\brief Unit test for Mat2 accessors fuction
*/
TEST(Mat2UnitTest, Accessors)
{
	Mat2 mat_1 = GenerateMat2();

	const float* mat_1_data = mat_1.Data();

	EXPECT_FLOAT_EQ(mat_1_data[0], mat_1.e00);
	EXPECT_FLOAT_EQ(mat_1_data[1], mat_1.e01);
	EXPECT_FLOAT_EQ(mat_1_data[2], mat_1.e10);
	EXPECT_FLOAT_EQ(mat_1_data[3], mat_1.e11);

	Mat2 mat_2 = GenerateMat2();
	const float* mat_2_data = mat_2.Data();

	EXPECT_FLOAT_EQ(mat_2_data[0], mat_2[0]);
	EXPECT_FLOAT_EQ(mat_2_data[1], mat_2[1]);
	EXPECT_FLOAT_EQ(mat_2_data[2], mat_2[2]);
	EXPECT_FLOAT_EQ(mat_2_data[3], mat_2[3]);
}

/**
*	\brief Unit test for equality and comparison between Vec2
*/
TEST(Mat2UnitTest, Equality)
{
	Mat2 mat_1 = Mat2::Zero;
	float mat_2_m00 = static_cast<float>(Math::Random(1, 100));
	float mat_2_m01 = static_cast<float>(Math::Random(1, 100));
	float mat_2_m10 = static_cast<float>(Math::Random(1, 100));
	float mat_2_m11 = static_cast<float>(Math::Random(1, 100));
	Mat2 mat_2 = Mat2(mat_2_m00, mat_2_m01, mat_2_m10, mat_2_m11);
	Mat2 mat_3 = Mat2::Identity;

	// isZero()
	EXPECT_TRUE(mat_1.IsZero());
	EXPECT_FALSE(mat_2.IsZero());
	EXPECT_FALSE(mat_1.Equals(mat_2));
	EXPECT_TRUE(mat_2.Equals(mat_2));
	EXPECT_FALSE(mat_1 == mat_2);
	EXPECT_TRUE(mat_2 == mat_2);
	EXPECT_TRUE(mat_1 != mat_2);
	EXPECT_FALSE(mat_2 != mat_2);
	EXPECT_FALSE(mat_1.IsIdentity());
	EXPECT_TRUE(mat_3.IsIdentity());
}

/**
*	\brief Unit test matrix transposition functions
*/
TEST(Mat2UnitTest, Transpose)
{
	Mat2 mat_1 = GenerateMat2();
	Mat2 mat_1_transposed = Mat2(mat_1[0], mat_1[2], mat_1[1], mat_1[3]);
	
	EXPECT_EQ(mat_1.GetTranspose(), mat_1_transposed);

	mat_1.Transpose();

	EXPECT_EQ(mat_1, mat_1_transposed);
}

/**
*	\brief Unit test matrix determinant computation function
*/
TEST(Mat2UnitTest, Determinant)
{
	Mat2 mat_1 = Mat2(-8.f, 5.f, 3.f, -5.f);
	EXPECT_FLOAT_EQ(mat_1.Determinant(), mat_1[0] * mat_1[3] - mat_1[1] * mat_1[2]);

	Mat2 mat_2 = GenerateMat2();
	EXPECT_FLOAT_EQ(mat_2.Determinant(), mat_2[0] * mat_2[3] - mat_2[1] * mat_2[2]);
}

/**
*	\brief Unit test matrix inverse computation function
*/
TEST(Mat2UnitTest, Inverse)
{
	EXPECT_EQ(Mat2::Identity, Mat2::Identity.GetInverse());
	
	Mat2 mat_1 = Mat2(-8.f, 5.f, 3.f, -5.f);

	EXPECT_TRUE(Mat2::Identity.Equals(mat_1 * mat_1.GetInverse()));

	Mat2 tmp = mat_1;
	mat_1.Inverse();
	float inverted_determinant = 1.f / tmp.Determinant();

	EXPECT_TRUE(Mat2::Identity.Equals(mat_1 * tmp));
}

/**
*	\brief Unit test matrix mat2 & scalar operators
*/
TEST(Mat2UnitTest, scalar_operator)
{
	Mat2 mat_1 = GenerateMat2();
	Mat2 mat_2 = GenerateMat2();
	float scalar = Math::Random(1.f, 100.f);

	//operator+(scalar)
	EXPECT_EQ(mat_1 + scalar, Mat2(mat_1[0] + scalar, mat_1[1] + scalar, mat_1[2] + scalar, mat_1[3] + scalar));
	EXPECT_EQ(mat_2 + scalar, Mat2(mat_2[0] + scalar, mat_2[1] + scalar, mat_2[2] + scalar , mat_2[3] + scalar));

	//operator-(scalar)
	EXPECT_EQ(mat_1 - scalar, Mat2(mat_1[0] - scalar, mat_1[1] - scalar, mat_1[2] - scalar, mat_1[3] - scalar));
	EXPECT_EQ(mat_2 - scalar, Mat2(mat_2[0] - scalar, mat_2[1] - scalar, mat_2[2] - scalar, mat_2[3] - scalar));

	//operator*(scalar)
	EXPECT_EQ(mat_1 * scalar, Mat2(mat_1[0] * scalar, mat_1[1] * scalar, mat_1[2] * scalar, mat_1[3] * scalar));
	EXPECT_EQ(mat_2 * scalar, Mat2(mat_2[0] * scalar, mat_2[1] * scalar, mat_2[2] * scalar, mat_2[3] * scalar));

	//operator/(scalar)
	EXPECT_EQ(mat_1 / scalar, Mat2(mat_1[0] / scalar, mat_1[1] / scalar, mat_1[2] / scalar, mat_1[3] / scalar));
	EXPECT_EQ(mat_2 / scalar, Mat2(mat_2[0] / scalar, mat_2[1] / scalar, mat_2[2] / scalar, mat_2[3] / scalar));


	//operator+=(scalar)
	mat_1 = GenerateMat2();
	mat_2 = mat_1;
	mat_1 += scalar;

	EXPECT_EQ(mat_1, mat_2 + scalar);

	//operator-=(scalar)
	mat_1 = GenerateMat2();
	mat_2 = mat_1;
	mat_1 -= scalar;

	EXPECT_EQ(mat_1, mat_2 - scalar);

	//operator*=(scalar)
	mat_1 = GenerateMat2();
	mat_2 = mat_1;
	mat_1 *= scalar;

	EXPECT_EQ(mat_1, mat_2 * scalar);

	//operator/=(scalar)
	mat_1 = GenerateMat2();
	mat_2 = mat_1;
	mat_1 /= scalar;

	EXPECT_EQ(mat_1, mat_2 / scalar);
}

/**
*	\brief Unit test mat2 & vec2 operators
*/
TEST(Mat2UnitTest, vec2_operator)
{
	Mat2 mat_1 = GenerateMat2();
	Vec2 vec_1 = Vec2(Math::Random(1.f, 100.f), Math::Random(1.f, 100.f));
	
	EXPECT_EQ(mat_1 * vec_1 ,Vec2(mat_1[0] * vec_1.X + mat_1[1] * vec_1.Y, mat_1[2] * vec_1.X + mat_1[3] * vec_1.Y));
}

/**
*	\brief Unit test mat2 & mat2 operators
*/
TEST(Mat2UnitTest, mat2_operator)
{
	Mat2 mat_1 = Mat2(-8.f, 5.f, 3.f, -5.f);;
	Mat2 mat_2 = Mat2::Identity;

	EXPECT_EQ(mat_1 + mat_2, Mat2(-7.f, 5.f, 3.f, -4.f));

	EXPECT_EQ(mat_1 - mat_2, Mat2(-9.f, 5.f, 3.f, -6.f));

	EXPECT_EQ(mat_1 * mat_2, mat_1);

	mat_1 += mat_2;

	EXPECT_EQ(mat_1, Mat2(-7.f, 5.f, 3.f, -4.f));

	mat_1 -= mat_2;

	EXPECT_EQ(mat_1, Mat2(-8.f, 5.f, 3.f, -5.f));

	mat_1 *= mat_2;

	EXPECT_EQ(mat_1, Mat2(-8.f, 5.f, 3.f, -5.f));
}