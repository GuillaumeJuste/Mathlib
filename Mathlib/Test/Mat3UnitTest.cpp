#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Unit test for constants values
*/
TEST(Mat3UnitTest, Constant)
{
	Math::InitializeRandom();
	EXPECT_EQ(Mat3::Zero, Mat3());
	EXPECT_EQ(Mat3::Identity, Mat3(1.f, 0.f, 0.f, 
								0.f, 1.f, 0.f,
								0.f, 0.f, 1.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Mat3UnitTest, Constructor)
{
	Mat3 mat_1 = Mat3();

	EXPECT_EQ(mat_1, Mat3(0.f, 0.f, 0.f, 
						0.f, 0.f, 0.f,
						0.f, 0.f, 0.f));

	EXPECT_EQ(Mat3(-10.f), Mat3(-10.f, -10.f, -10.f,
		-10.f, -10.f, -10.f,
		-10.f, -10.f, -10.f));

	EXPECT_EQ(Mat3(Vec3(5.f, 48.f, 65.2f), Vec3(12.f, 7.f, 34.9f), Vec3(85.2f, 97.54f, 98.9f)), 
		Mat3(5.f, 48.f, 65.2f,
			12.f, 7.f, 34.9f,
			85.2f, 97.54f, 98.9));

	EXPECT_EQ(Mat3(Mat2::Identity), Mat3::Identity);
	EXPECT_EQ(Mat3(Mat4::Identity), Mat3::Identity);
}

/**
*	\brief Unit test for rotation matrix constructor
*/
TEST(Mat3UnitTest, Rotation_matrix)
{
	Mat3 mat_1 = Mat3::RotationMatrix(Math::Pi, Math::Pi/2.f, 3* Math::Pi / 2.f);

	Mat3 result = Mat3(0.f, -1.f, 0.f,
						0.f, 0.f, 1.f,
						-1.f, 0.f, 0.f);

	EXPECT_TRUE(result.Equals(mat_1));

	Mat3 mat_2 = Mat3::RotationMatrix(Vec3(Math::Pi, Math::Pi / 2.f, 3 * Math::Pi / 2.f));

	EXPECT_TRUE(result.Equals(mat_2));
}

/**
*	\brief Unit test for scale matrix constructor
*/
TEST(Mat3UnitTest, Scale_matrix)
{
	Mat3 mat_1 = Mat3::ScaleMatrix(5.f);

	EXPECT_TRUE(mat_1.Equals(Mat3(5.f, 0.f, 0.f, 
								0.f, 5.f, 0.f,
								0.f, 0.f, 1.f)));

	Mat3 mat_2 = Mat3::ScaleMatrix(Vec2(7.4f, 8.6f));
	EXPECT_TRUE(mat_2.Equals(Mat3(7.4f, 0.f, 0.f,
		0.f, 8.6f, 0.f,
		0.f, 0.f, 1.f)));
}

/**
*	\brief Unit test for transform matrix constructor
*/
TEST(Mat3UnitTest, Transform_matrix)
{
	Mat3 mat_1 = Mat3::TransformMatrix2D(Math::Pi / 2.f, Vec2(2.4f, 3.6f), Vec2(5.f, 1.f));

	Mat3 result = Mat3(0.f, -5.f, 2.4f,
						1.f, 0.f, 3.6f,
						0.f, 0.f,1.f);
}

/**
*	\brief Unit test for scale matrix constructor
*/
TEST(Mat3UnitTest, Translation_matrix)
{
	Mat3 mat_1 = Mat3::TranslationMatrix(Vec2(12.5f, 3.8f));

	EXPECT_TRUE(mat_1.Equals(Mat3(1.f, 0.f, 12.5f,
		0.f, 1.f, 3.8f,
		0.f, 0.f, 1.f)));
}

/**
*	\brief Unit test for Mat3 accessors fuction
*/
TEST(Mat3UnitTest, Accessors)
{
	Mat3 mat_1 = Mat3(3.2f, 8.4f, -1.8f, 
					6.8f, 5.3f, 4.7f,
					-4.6f, 7.4f, 6.8f);

	const float* mat_1_data = mat_1.Data();

	EXPECT_FLOAT_EQ(mat_1_data[0], mat_1.e00);
	EXPECT_FLOAT_EQ(mat_1_data[1], mat_1.e01);
	EXPECT_FLOAT_EQ(mat_1_data[2], mat_1.e02);
	EXPECT_FLOAT_EQ(mat_1_data[3], mat_1.e10);
	EXPECT_FLOAT_EQ(mat_1_data[4], mat_1.e11);
	EXPECT_FLOAT_EQ(mat_1_data[5], mat_1.e12);
	EXPECT_FLOAT_EQ(mat_1_data[6], mat_1.e20);
	EXPECT_FLOAT_EQ(mat_1_data[7], mat_1.e21);
	EXPECT_FLOAT_EQ(mat_1_data[8], mat_1.e22);

	Mat3 mat_2 = Mat3(5.9f, 7.6f, -5.8f, 
					-3.4f, 8.4f, -9.6f,
					7.6f, 5.2f, -7.6f);
	const float* mat_2_data = mat_2.Data();

	EXPECT_FLOAT_EQ(mat_2_data[0], mat_2[0]);
	EXPECT_FLOAT_EQ(mat_2_data[1], mat_2[1]);
	EXPECT_FLOAT_EQ(mat_2_data[2], mat_2[2]);
	EXPECT_FLOAT_EQ(mat_2_data[3], mat_2[3]);
	EXPECT_FLOAT_EQ(mat_2_data[4], mat_2[4]);
	EXPECT_FLOAT_EQ(mat_2_data[5], mat_2[5]);
	EXPECT_FLOAT_EQ(mat_2_data[6], mat_2[6]);
	EXPECT_FLOAT_EQ(mat_2_data[7], mat_2[7]);
	EXPECT_FLOAT_EQ(mat_2_data[8], mat_2[8]);
}

/**
*	\brief Unit test for equality and comparison between Mat3
*/
TEST(Mat3UnitTest, Equality)
{
	Mat3 mat_1 = Mat3::Zero;
	Mat3 mat_2 = Mat3(5.9f, 7.6f, -5.8f, 
				-3.4f, 4.8f, 5.2f,
				-7.6f, -8.4f, 8.2f);
	Mat3 mat_3 = Mat3::Identity;

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
TEST(Mat3UnitTest, Transpose)
{
	Mat3 mat_1 = Mat3(3.2f, 8.4f, -1.8f,
		6.8f, 5.3f, 4.7f,
		-4.6f, 7.4f, 6.8f);
	Mat3 mat_1_transposed = Mat3(mat_1[0], mat_1[3], mat_1[6], 
							mat_1[1], mat_1[4], mat_1[7], 
							mat_1[2], mat_1[5], mat_1[8]);

	EXPECT_EQ(mat_1.GetTranspose(), mat_1_transposed);

	mat_1.Transpose();

	EXPECT_EQ(mat_1, mat_1_transposed);
}

/**
*	\brief Unit test matrix determinant computation function
*/
TEST(Mat3UnitTest, Determinant)
{
	Mat3 mat_1 = Mat3(6.f, 1.f, 1.f,
					4.f, -2.f, 5.f,
					2.f,8.f, 7.f);

	EXPECT_EQ(mat_1.Determinant(), -306.f);
}

/**
*	\brief Unit test matrix inverse computation function
*/
TEST(Mat3UnitTest, Inverse)
{
	EXPECT_EQ(Mat3::Identity, Mat3::Identity.GetInverse());

	Mat3 mat_1 = Mat3(-8.75f, 5.36f, 3.12f, 
					-5.92f, 3.96f, 8.92f,
					8.74f, 9.41f, 35.81f);

	EXPECT_TRUE(Mat3::Identity.Equals(mat_1 * mat_1.GetInverse(), 0.0001f));

	Mat3 tmp = mat_1;
	mat_1.Inverse();
	float inverted_determinant = 1.f / tmp.Determinant();

	EXPECT_TRUE(Mat3::Identity.Equals(mat_1 * tmp, 0.0001f));
}

/**
*	\brief Unit test matrix mat3 & scalar operators
*/
TEST(Mat3UnitTest, scalar_operator)
{
	Mat3 mat_1 = Mat3(3.2f, 8.4f, -1.8f,
		6.8f, 5.3f, 4.7f,
		-4.6f, 7.4f, 6.8f);;
	Mat3 mat_2 = Mat3(5.9f, 7.6f, -5.8f,
		-3.4f, 4.8f, 5.2f,
		-7.6f, -8.4f, 8.2f);;
	float scalar = Math::Random(1.f, 100.f);

	//operator+(scalar)
	EXPECT_EQ(mat_1 + scalar, Mat3(mat_1[0] + scalar, mat_1[1] + scalar, mat_1[2] + scalar, 
		mat_1[3] + scalar, mat_1[4] + scalar, mat_1[5] + scalar, 
		mat_1[6] + scalar, mat_1[7] + scalar, mat_1[8] + scalar));
	EXPECT_EQ(mat_2 + scalar, Mat3(mat_2[0] + scalar, mat_2[1] + scalar, mat_2[2] + scalar, 
		mat_2[3] + scalar, mat_2[4] + scalar, mat_2[5] + scalar, 
		mat_2[6] + scalar, mat_2[7] + scalar, mat_2[8] + scalar));

	//operator-(scalar)
	EXPECT_EQ(mat_1 - scalar, Mat3(mat_1[0] - scalar, mat_1[1] - scalar, mat_1[2] - scalar, 
		mat_1[3] - scalar, mat_1[4] - scalar, mat_1[5] - scalar,
		mat_1[6] - scalar, mat_1[7] - scalar, mat_1[8] - scalar));
	EXPECT_EQ(mat_2 - scalar, Mat3(mat_2[0] - scalar, mat_2[1] - scalar, mat_2[2] - scalar,
		mat_2[3] - scalar, mat_2[4] - scalar, mat_2[5] - scalar,
		mat_2[6] - scalar, mat_2[7] - scalar, mat_2[8] - scalar));

	//operator*(scalar)
	EXPECT_EQ(mat_1 * scalar, Mat3(mat_1[0] * scalar, mat_1[1] * scalar, mat_1[2] * scalar, 
		mat_1[3] * scalar, mat_1[4] * scalar, mat_1[5] * scalar,
		mat_1[6] * scalar, mat_1[7] * scalar, mat_1[8] * scalar));

	EXPECT_EQ(mat_2 * scalar, Mat3(mat_2[0] * scalar, mat_2[1] * scalar, mat_2[2] * scalar, 
		mat_2[3] * scalar, mat_2[4] * scalar, mat_2[5] * scalar,
		mat_2[6] * scalar, mat_2[7] * scalar, mat_2[8] * scalar));
	//operator/(scalar)
	EXPECT_EQ(mat_1 / scalar, Mat3(mat_1[0] / scalar, mat_1[1] / scalar, mat_1[2] / scalar,
		mat_1[3] / scalar, mat_1[4] / scalar, mat_1[5] / scalar,
		mat_1[6] / scalar, mat_1[7] / scalar, mat_1[8] / scalar));

	EXPECT_EQ(mat_2 / scalar, Mat3(mat_2[0] / scalar, mat_2[1] / scalar, mat_2[2] / scalar, 
		mat_2[3] / scalar, mat_2[4] / scalar, mat_2[5] / scalar,
		mat_2[6] / scalar, mat_2[7] / scalar, mat_2[8] / scalar));

	//operator+=(scalar)
	mat_1 = Mat3(8.7f, -11.5f, 6.4f, 
		8.3f, 5.6f, 7.9f,
		2.5f, 12.8f, -7.6f);
	mat_2 = mat_1;
	mat_1 += scalar;

	EXPECT_EQ(mat_1, mat_2 + scalar);

	//operator-=(scalar)
	mat_1 = Mat3(8.7f, -11.5f, 6.4f,
		8.3f, 5.6f, 7.9f,
		2.5f, 12.8f, -7.6f);
	mat_2 = mat_1;
	mat_1 -= scalar;

	EXPECT_EQ(mat_1, mat_2 - scalar);

	//operator*=(scalar)
	mat_1 = Mat3(5.9f, 7.6f, -5.8f,
		-3.4f, 8.4f, -9.6f,
		7.6f, 5.2f, -7.6f);
	mat_2 = mat_1;
	mat_1 *= scalar;

	EXPECT_EQ(mat_1, mat_2 * scalar);

	//operator/=(scalar)
	mat_1 = Mat3(5.9f, 7.6f, -5.8f,
		-3.4f, 8.4f, -9.6f,
		7.6f, 5.2f, -7.6f);
	mat_2 = mat_1;
	mat_1 /= scalar;

	EXPECT_EQ(mat_1, mat_2 / scalar);
}

/**
*	\brief Unit test mat3 & vec3 operators
*/
TEST(Mat3UnitTest, vec3_operator)
{
	Mat3 mat_1 = Mat3(3.2f, 8.4f, -1.8f,
		6.8f, 5.3f, 4.7f,
		-4.6f, 7.4f, 6.8f);
	Vec3 vec_1 = Vec3(Math::Random(1.f, 100.f), Math::Random(1.f, 100.f), Math::Random(1.f, 100.f));

	Vec3 result = Vec3(mat_1.e00 * vec_1.X + mat_1.e01 * vec_1.Y + mat_1.e02 * vec_1.Z, 
		mat_1.e10 * vec_1.X + mat_1.e11 * vec_1.Y + mat_1.e12 * vec_1.Z, 
		mat_1.e20 * vec_1.X + mat_1.e21 * vec_1.Y + mat_1.e22 * vec_1.Z);

	EXPECT_EQ(mat_1 * vec_1, result);
}

/**
*	\brief Unit test mat3 & mat3 operators
*/
TEST(Mat3UnitTest, mat3_operator)
{
	Mat3 mat_1 = Mat3(-8.f, 5.f, 3.f,
					-5.f, 6.2f, 7.7f,
					-9.2f, 6.4f, 12.8f);
	Mat3 mat_2 = Mat3::Identity;

	EXPECT_EQ(mat_1 + mat_2, Mat3(-7.f, 5.f, 3.f,
								-5.f, 7.2f, 7.7f,
								-9.2f, 6.4f, 13.8f));

	EXPECT_EQ(mat_1 - mat_2, Mat3(-9.f, 5.f, 3.f,
								-5.f, 5.2f, 7.7f,
								-9.2f, 6.4f, 11.8f));

	EXPECT_EQ(mat_1 * mat_2, mat_1);

	mat_1 += mat_2;

	EXPECT_EQ(mat_1, Mat3(-7.f, 5.f, 3.f,
						-5.f, 7.2f, 7.7f,
						-9.2f, 6.4f, 13.8f));

	mat_1 -= mat_2;

	EXPECT_EQ(mat_1, Mat3(-8.f, 5.f, 3.f,
						-5.f, 6.2f, 7.7f,
						-9.2f, 6.4f, 12.8f));

	mat_1 *= mat_2;

	EXPECT_EQ(mat_1, Mat3(-8.f, 5.f, 3.f,
						-5.f, 6.2f, 7.7f,
						-9.2f, 6.4f, 12.8f));
}