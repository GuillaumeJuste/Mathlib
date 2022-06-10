#include <gtest/gtest.h>

#include <Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Unit test for constants values
*/
TEST(Mat4UnitTest, Constant)
{
	Math::InitializeRandom();
	EXPECT_EQ(Mat4::Zero, Mat4());
	EXPECT_EQ(Mat4::Identity, Mat4(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f));
}

/**
*	\brief Unit test for constructors
*/
TEST(Mat4UnitTest, Constructor)
{
	Mat4 mat_1 = Mat4();

	EXPECT_EQ(mat_1, Mat4(0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f));

	EXPECT_EQ(Mat4(-10.f), Mat4(-10.f, -10.f, -10.f, -10.f,
		-10.f, -10.f, -10.f, -10.f,
		-10.f, -10.f, -10.f, -10.f,
		-10.f, -10.f, -10.f, -10.f));

	EXPECT_EQ(Mat4(Vec4(5.f, 48.f, 65.2f, 988.f), 
				Vec4(12.f, 7.f, 34.9f, 5.5f), 
				Vec4(85.2f, 97.54f, 98.9f, 85.f),
				Vec4(54.32f, 32.f, 88.f, 67.f)),
		Mat4(5.f, 48.f, 65.2f, 988.f,
			12.f, 7.f, 34.9f, 5.5f,
			85.2f, 97.54f, 98.9f, 85.f,
			54.32f, 32.f, 88.f, 67.f));

	EXPECT_EQ(Mat4(Mat2::Identity), Mat4::Identity);
	EXPECT_EQ(Mat4(Mat3::Identity), Mat4::Identity);
}

/**
*	\brief Unit test for rotation matrix constructors
*/
TEST(Mat4UnitTest, Rotation_matrix)
{
	Mat4 mat = Mat4::RotationMatrix(Math::Pi, Math::Pi / 2.f, 3 * Math::Pi / 2.f);

	Mat4 result = Mat4(0.f, -1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f, 
		-1.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	EXPECT_TRUE(result.Equals(mat));

	Mat4 mat_2 = Mat4::RotationMatrix(Vec3(Math::Pi, Math::Pi / 2.f, 3 * Math::Pi / 2.f));

	EXPECT_TRUE(result.Equals(mat_2));
}

/**
*	\brief Unit test for scale matrix constructor
*/
TEST(Mat4UnitTest, Scale_matrix)
{
	Mat4 mat_1 = Mat4::ScaleMatrix(5.f);

	EXPECT_TRUE(mat_1.Equals(Mat4(5.f, 0.f, 0.f, 0.f,
		0.f, 5.f, 0.f, 0.f,
		0.f, 0.f, 5.f, 0.f,
		0.f, 0.f, 0.f, 1.f)));

	Mat4 mat_2 = Mat4::ScaleMatrix(Vec3(7.4f, 8.6f, 5.9f));
	EXPECT_TRUE(mat_2.Equals(Mat4(7.4f, 0.f, 0.f, 0.f,
		0.f, 8.6f, 0.f, 0.f,
		0.f, 0.f, 5.9f, 0.f,
		0.f, 0.f, 0.f, 1.f)));
}

/**
*	\brief Unit test for view matrix computation function
*/
TEST(Mat4UnitTest, View_matrix)
{
	Mat4 mat_1 = Mat4::ViewMatrix(COORDINATE_SYSTEM::LEFT_HAND, Vec3(0.f, 0.f, -1.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));

	Mat4 result_1 = Mat4(1.f, 0.f, 0.f, 0.f,
		0.f, -1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 1.f, 1.f);

	EXPECT_TRUE(mat_1.Equals(result_1, 0.01f));

	Mat4 mat_2 = Mat4::ViewMatrix(COORDINATE_SYSTEM::RIGHT_HAND, Vec3(0.f, 0.f, -1.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, -1.f, 0.f));

	Mat4 result_2 = Mat4(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, -1.f, 0.f,
		0.f, 0.f, 1.f, 1.f);

	EXPECT_TRUE(mat_2.Equals(result_2, 0.01f));
}

/**
*	\brief Unit test for perspective matrix computation function
*/
TEST(Mat4UnitTest, Perspective_matrix)
{
	Mat4 mat_1 = Mat4::PerspectiveMatrix(COORDINATE_SYSTEM::LEFT_HAND, Math::Radians(45.0f), 4.f / 3.f, 0.1f, 100.0f);

	Mat4 result_1 = Mat4(1.81066012f, 0.f, 0.f, 0.f,
		0.f, 2.41421342f, 0.f, 0.f,
		0.f, 0.f, 1.002002f, 0.2002002f,
		0.f, 0.f, 1.f, 0.f);

	EXPECT_TRUE(mat_1.Equals(result_1, Math::FloatEpsilon));

	Mat4 mat_2 = Mat4::PerspectiveMatrix(COORDINATE_SYSTEM::RIGHT_HAND, Math::Radians(45.0f), 4.f / 3.f, 0.1f, 100.0f);

	Mat4 result_2 = Mat4(1.81066012f, 0.f, 0.f, 0.f,
		0.f, 2.41421342f, 0.f, 0.f,
		0.f, 0.f, -1.002002f, -0.2002002f,
		0.f, 0.f, -1.f, 0.f);

	EXPECT_TRUE(mat_2.Equals(result_2, 0.01f));
}

/**
*	\brief Unit test for Mat4 accessors fuction
*/
TEST(Mat4UnitTest, Accessors)
{
	Mat4 mat_1 = Mat4(3.2f, 8.4f, -1.8f, 2.1f,
		6.8f, 5.3f, 4.7f, -4.5f,
		-4.6f, 7.4f, 6.8f, 8.6f,
		-11.3f, 8.6f, 1.2f, 6.4f);

	const float* mat_1_data = mat_1.Data();

	EXPECT_FLOAT_EQ(mat_1_data[0], mat_1.e00);
	EXPECT_FLOAT_EQ(mat_1_data[1], mat_1.e01);
	EXPECT_FLOAT_EQ(mat_1_data[2], mat_1.e02);
	EXPECT_FLOAT_EQ(mat_1_data[3], mat_1.e03);
	EXPECT_FLOAT_EQ(mat_1_data[4], mat_1.e10);
	EXPECT_FLOAT_EQ(mat_1_data[5], mat_1.e11);
	EXPECT_FLOAT_EQ(mat_1_data[6], mat_1.e12);
	EXPECT_FLOAT_EQ(mat_1_data[7], mat_1.e13);
	EXPECT_FLOAT_EQ(mat_1_data[8], mat_1.e20);
	EXPECT_FLOAT_EQ(mat_1_data[9], mat_1.e21);
	EXPECT_FLOAT_EQ(mat_1_data[10], mat_1.e22);
	EXPECT_FLOAT_EQ(mat_1_data[11], mat_1.e23);
	EXPECT_FLOAT_EQ(mat_1_data[12], mat_1.e30);
	EXPECT_FLOAT_EQ(mat_1_data[13], mat_1.e31);
	EXPECT_FLOAT_EQ(mat_1_data[14], mat_1.e32);
	EXPECT_FLOAT_EQ(mat_1_data[15], mat_1.e33);

	Mat4 mat_2 = Mat4(5.9f, 7.6f, -5.8f, 8.2f,
		-3.4f, 8.4f, -9.6f, 7.6f,
		7.6f, 5.2f, -7.6f, 1.5f,
		-9.8f, -4.2f, 7.4f, 8.3f);
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
	EXPECT_FLOAT_EQ(mat_2_data[9], mat_2[9]);
	EXPECT_FLOAT_EQ(mat_2_data[10], mat_2[10]);
	EXPECT_FLOAT_EQ(mat_2_data[11], mat_2[11]);
	EXPECT_FLOAT_EQ(mat_2_data[12], mat_2[12]);
	EXPECT_FLOAT_EQ(mat_2_data[13], mat_2[13]);
	EXPECT_FLOAT_EQ(mat_2_data[14], mat_2[14]);
	EXPECT_FLOAT_EQ(mat_2_data[15], mat_2[15]);
}

/**
*	\brief Unit test for equality and comparison between Mat4
*/
TEST(Mat4UnitTest, Equality)
{
	Mat4 mat_1 = Mat4::Zero;
	Mat4 mat_2 = Mat3(5.9f, 7.6f, -5.8f,
		-3.4f, 4.8f, 5.2f,
		-7.6f, -8.4f, 8.2f);
	Mat4 mat_3 = Mat4::Identity;

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
TEST(Mat4UnitTest, Transpose)
{
	Mat4 mat_1 = Mat4(5.9f, 7.6f, -5.8f, 4.6f,
		-3.4f, 4.8f, 5.2f, 3.5f, 
		-7.6f, -8.4f, 8.2f, 6.8f,
		-4.8f, 7.3f, -8.2f, 1.3f);
	Mat4 mat_1_transposed = Mat4(mat_1[0], mat_1[4], mat_1[8], mat_1[12],
		mat_1[1], mat_1[5], mat_1[9], mat_1[13],
		mat_1[2], mat_1[6], mat_1[10], mat_1[14],
		mat_1[3], mat_1[7], mat_1[11], mat_1[15]);


	EXPECT_EQ(mat_1.GetTranspose(), mat_1_transposed);

	mat_1.Transpose();

	EXPECT_EQ(mat_1, mat_1_transposed);
}

/**
*	\brief Unit test matrix determinant computation function
*/
TEST(Mat4UnitTest, Determinant)
{
	Mat4 mat_1 = Mat4(6.f, 1.f, 1.f, 5.8f,
		4.f, -2.f, 5.f, 5.2f,
		2.f, 8.f, 7.f, 9.3f,
		9.4f, 3.5f, 8.2f, 6.7f);

	EXPECT_FLOAT_EQ(mat_1.Determinant(), 2186.2f);
}

/**
*	\brief Unit test matrix inverse computation function
*/
TEST(Mat4UnitTest, Inverse)
{
	EXPECT_EQ(Mat4::Identity, Mat4::Identity.GetInverse());

	Mat4 mat_1 = Mat4(6.f, 1.f, 1.f, 5.8f,
		4.f, -2.f, 5.f, 5.2f,
		2.f, 8.f, 7.f, 9.3f,
		9.4f, 3.5f, 8.2f, 6.7f);

	Mat4 inverse = Mat4(0.0764751f, -0.085980f, -0.079663f, 0.111106f,
		0.001930f, -0.177778f, 0.052657f, 0.063214f,
		-0.191418f, 0.089305f, 0.010392f, 0.081968f,
		0.125972f, 0.104199f, 0.071539f, -0.139968f);

	Mat4 result = mat_1.Inverse();

	EXPECT_TRUE(inverse.Equals(result, 0.000001f));

	Mat4 tmp = mat_1;
	mat_1.Inverse();
	float inverted_determinant = 1.f / tmp.Determinant();

	EXPECT_TRUE(Mat4::Identity.Equals(mat_1 * tmp, 0.0001f));
}

/**
*	\brief Unit test matrix mat4 & scalar operators
*/
TEST(Mat4UnitTest, scalar_operator)
{
	Mat4 mat_1 = Mat4(5.9f, 7.6f, -5.8f, 8.2f,
		-3.4f, 8.4f, -9.6f, 7.6f,
		7.6f, 5.2f, -7.6f, 1.5f,
		-9.8f, -4.2f, 7.4f, 8.3f);
	Mat4 mat_2 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	float scalar = (float)Math::Random(1, 100);

	//operator+(scalar)
	EXPECT_EQ(mat_1 + scalar, Mat4(mat_1[0] + scalar, mat_1[1] + scalar, mat_1[2] + scalar, mat_1[3] + scalar,
		mat_1[4] + scalar, mat_1[5] + scalar, mat_1[6] + scalar, mat_1[7] + scalar,
		mat_1[8] + scalar, mat_1[9] + scalar, mat_1[10] + scalar, mat_1[11] + scalar, 
		mat_1[12] + scalar, mat_1[13] + scalar, mat_1[14] + scalar, mat_1[15] + scalar));

	EXPECT_EQ(mat_2 + scalar, Mat4(mat_2[0] + scalar, mat_2[1] + scalar, mat_2[2] + scalar, mat_2[3] + scalar,
		mat_2[4] + scalar, mat_2[5] + scalar, mat_2[6] + scalar, mat_2[7] + scalar,
		mat_2[8] + scalar, mat_2[9] + scalar, mat_2[10] + scalar, mat_2[11] + scalar,
		mat_2[12] + scalar, mat_2[13] + scalar, mat_2[14] + scalar, mat_2[15] + scalar));

	//operator-(scalar)
	EXPECT_EQ(mat_1 - scalar, Mat4(mat_1[0] - scalar, mat_1[1] - scalar, mat_1[2] - scalar, mat_1[3] - scalar,
		mat_1[4] - scalar, mat_1[5] - scalar, mat_1[6] - scalar, mat_1[7] - scalar,
		mat_1[8] - scalar, mat_1[9] - scalar, mat_1[10] - scalar, mat_1[11] - scalar,
		mat_1[12] - scalar, mat_1[13] - scalar, mat_1[14] - scalar, mat_1[15] - scalar));

	EXPECT_EQ(mat_2 - scalar, Mat4(mat_2[0] - scalar, mat_2[1] - scalar, mat_2[2] - scalar, mat_2[3] - scalar,
		mat_2[4] - scalar, mat_2[5] - scalar, mat_2[6] - scalar, mat_2[7] - scalar,
		mat_2[8] - scalar, mat_2[9] - scalar, mat_2[10] - scalar, mat_2[11] - scalar,
		mat_2[12] - scalar, mat_2[13] - scalar, mat_2[14] - scalar, mat_2[15] - scalar));

	//operator*(scalar)
	EXPECT_EQ(mat_1 * scalar, Mat4(mat_1[0] * scalar, mat_1[1] * scalar, mat_1[2] * scalar, mat_1[3] * scalar,
		mat_1[4] * scalar, mat_1[5] * scalar, mat_1[6] * scalar, mat_1[7] * scalar,
		mat_1[8] * scalar, mat_1[9] * scalar, mat_1[10] * scalar, mat_1[11] * scalar,
		mat_1[12] * scalar, mat_1[13] * scalar, mat_1[14] * scalar, mat_1[15] * scalar));

	EXPECT_EQ(mat_2 * scalar, Mat4(mat_2[0] * scalar, mat_2[1] * scalar, mat_2[2] * scalar, mat_2[3] * scalar,
		mat_2[4] * scalar, mat_2[5] * scalar, mat_2[6] * scalar, mat_2[7] * scalar,
		mat_2[8] * scalar, mat_2[9] * scalar, mat_2[10] * scalar, mat_2[11] * scalar,
		mat_2[12] * scalar, mat_2[13] * scalar, mat_2[14] * scalar, mat_2[15] * scalar));
	//operator/(scalar)
	EXPECT_EQ(mat_1 / scalar, Mat4(mat_1[0] / scalar, mat_1[1] / scalar, mat_1[2] / scalar, mat_1[3] / scalar,
		mat_1[4] / scalar, mat_1[5] / scalar, mat_1[6] / scalar, mat_1[7] / scalar,
		mat_1[8] / scalar, mat_1[9] / scalar, mat_1[10] / scalar, mat_1[11] / scalar,
		mat_1[12] / scalar, mat_1[13] / scalar, mat_1[14] / scalar, mat_1[15] / scalar));

	EXPECT_EQ(mat_2 / scalar, Mat4(mat_2[0] / scalar, mat_2[1] / scalar, mat_2[2] / scalar, mat_2[3] / scalar,
		mat_2[4] / scalar, mat_2[5] / scalar, mat_2[6] / scalar, mat_2[7] / scalar,
		mat_2[8] / scalar, mat_2[9] / scalar, mat_2[10] / scalar, mat_2[11] / scalar,
		mat_2[12] / scalar, mat_2[13] / scalar, mat_2[14] / scalar, mat_2[15] / scalar));

	//operator+=(scalar)
	mat_1 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	mat_2 = mat_1;
	mat_1 += scalar;

	EXPECT_EQ(mat_1, mat_2 + scalar);

	//operator-=(scalar)
	mat_1 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	mat_2 = mat_1;
	mat_1 -= scalar;

	EXPECT_EQ(mat_1, mat_2 - scalar);

	//operator*=(scalar)
	mat_1 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	mat_2 = mat_1;
	mat_1 *= scalar;

	EXPECT_EQ(mat_1, mat_2 * scalar);

	//operator/=(scalar)
	mat_1 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	mat_2 = mat_1;
	mat_1 /= scalar;

	EXPECT_EQ(mat_1, mat_2 / scalar);
}

/**
*	\brief Unit test mat4 & vec4 operators
*/
TEST(Mat4UnitTest, vec4_operator)
{
	Mat4 mat_1 = Mat4(3.2f, 8.4f, -1.8f, 3.4f,
		6.8f, 5.3f, 4.7f, 7.1f,
		-4.6f, 7.4f, 6.8f, -2.5f,
		5.2f, 8.6f, -4.7f, 6.8f);
	Vec4 vec_1 = Vec3((float)Math::Random(1, 100), (float)Math::Random(1, 100), (float)Math::Random(1, 100));

	Vec4 result = Vec4(mat_1.e00 * vec_1.X + mat_1.e01 * vec_1.Y + mat_1.e02 * vec_1.Z + mat_1.e03 * vec_1.W,
		mat_1.e10 * vec_1.X + mat_1.e11 * vec_1.Y + mat_1.e12 * vec_1.Z + mat_1.e13 * vec_1.W,
		mat_1.e20 * vec_1.X + mat_1.e21 * vec_1.Y + mat_1.e22 * vec_1.Z + mat_1.e23 * vec_1.W,
		mat_1.e30 * vec_1.X + mat_1.e31 * vec_1.Y + mat_1.e32 * vec_1.Z + mat_1.e33 * vec_1.W);

	EXPECT_EQ(mat_1 * vec_1, result);
}

/**
*	\brief Unit test mat4 & mat4 operators
*/
TEST(Mat4UnitTest, mat4_operator)
{
	Mat4 mat_1 = Mat4(-8.f, 5.f, 3.f, 4.2f,
		-5.f, 6.2f, 7.7f, 5.7f,
		-9.2f, 6.4f, 12.8f, 5.7f,
		-7.9f, 1.2f, 5.2f, 8.5f);
	Mat4 mat_2 = Mat4(5.9f, 7.6f, -5.8f, 8.2f,
		-3.4f, 8.4f, -9.6f, 7.6f,
		6.6f, 5.2f, -7.2f, 1.5f,
		-9.8f, -4.2f, 7.4f, 8.3f);

	Mat4 addition_result = Mat4(-2.1f, 12.6f, -2.8f, 12.4f,
		-8.4f, 14.6f, -1.9f, 13.3f,
		-2.6f, 11.6f, 5.6f, 7.2f,
		-17.7f, -3.f, 12.6f, 16.8f);

	Mat4 substraction_result = Mat4(-13.9f, -2.6f, 8.8f, - 4.f,
		-1.6f, -2.2f, 17.3f, - 1.9f,
		-15.8f, 1.2f, 20.f, 4.2f,
		1.9f, 5.4f, -2.2f, 0.2f);

	Mat4 multiplication_result = Mat4(-85.56f, -20.84f, 7.88f, 11.76f,
		-55.62f, 30.18f, -43.78f, 64.98f,
		-47.42f, 26.46f, -58.06f, 39.71f,
		-99.67f, -58.62f, 59.76f, 22.69f);

	EXPECT_TRUE(addition_result.Equals(mat_1 + mat_2, 0.001f));

	EXPECT_TRUE(substraction_result.Equals(mat_1 - mat_2, 0.001f));

	EXPECT_TRUE(multiplication_result.Equals(mat_1 * mat_2, 0.001f));

	Mat4 tmp = mat_1;
	tmp += mat_2;

	EXPECT_TRUE(tmp.Equals(addition_result, 0.001f));

	tmp = mat_1;
	tmp -= mat_2;

	EXPECT_TRUE(tmp.Equals(substraction_result, 0.001f));

	tmp = mat_1;
	tmp *= mat_2;

	EXPECT_TRUE(tmp.Equals(multiplication_result, 0.001f));
}