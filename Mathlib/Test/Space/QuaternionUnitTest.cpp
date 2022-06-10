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

	float sqrLen = 120.36f;
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

TEST(QuaternionUnitTest, Conjugate)
{
	Quat quat_1 = Quat(2.8f, -6.8f, 4.5f, 8.4f);
	Quat quat_1_conjugate = quat_1.GetConjugate();

	EXPECT_FLOAT_EQ(quat_1_conjugate.W, 2.8f);
	EXPECT_FLOAT_EQ(quat_1_conjugate.X, 6.8f);
	EXPECT_FLOAT_EQ(quat_1_conjugate.Y, -4.5f);
	EXPECT_FLOAT_EQ(quat_1_conjugate.Z, -8.4f);

	Quat quat_2 = Quat(3.8f, -5.2f, 7.2f, 5.2f);
	Quat quat_2_conjugate = quat_2.GetConjugate();

	EXPECT_FLOAT_EQ(quat_2_conjugate.W, 3.8f);
	EXPECT_FLOAT_EQ(quat_2_conjugate.X, 5.2f);
	EXPECT_FLOAT_EQ(quat_2_conjugate.Y, -7.2f);
	EXPECT_FLOAT_EQ(quat_2_conjugate.Z, -5.2f);
}

TEST(QuaternionUnitTest, GetAngle)
{
	Quat quat_1 = Quat(2.8f, -6.8f, 4.5f, 8.4f).Normalize();
	float quat_1_angle = quat_1.GetAngle();

	EXPECT_FLOAT_EQ(quat_1_angle, 2.6720602771680357f);

	Quat quat_2 = Quat(3.8f, -5.2f, 7.2f, 5.2f).Normalize();
	float quat_2_angle = quat_2.GetAngle();

	EXPECT_FLOAT_EQ(quat_2_angle, 2.4341912612720122f);

}

TEST(QuaternionUnitTest, GetAxis)
{
	Quat quat_1 = Quat(2.8f, -6.8f, 4.5f, 8.4f).Normalize();
	Vec3 quat_1_axis = quat_1.GetAxis();

	EXPECT_FLOAT_EQ(quat_1_axis.X, -0.580857221073525f);
	EXPECT_FLOAT_EQ(quat_1_axis.Y, 0.3843908080633621f);
	EXPECT_FLOAT_EQ(quat_1_axis.Z, 0.7175295083849428f);

	Quat quat_2 = Quat(3.8f, -5.2f, 7.2f, 5.2f).Normalize();
	Vec3 quat_2_axis = quat_2.GetAxis();

	EXPECT_FLOAT_EQ(quat_2_axis.X, -0.5052593483187066f);
	EXPECT_FLOAT_EQ(quat_2_axis.Y, 0.6995898669028244f);
	EXPECT_FLOAT_EQ(quat_2_axis.Z, 0.5052593483187066f);
}

TEST(QuaternionUnitTest, Rotate_vector)
{
	Vec3 start = Vec3::Right;
	Quat rotation = Quat::FromEuler(Vec3(0.f, 0.f, 90.f));
	Vec3 end = rotation.Rotate(start);

	EXPECT_TRUE(Math::Equals(end.X, 0.f));
	EXPECT_TRUE(Math::Equals(end.Y, 1.f));
	EXPECT_TRUE(Math::Equals(end.Z, 0.f));

	end = rotation * start;
	EXPECT_TRUE(Math::Equals(end.X, 0.f));
	EXPECT_TRUE(Math::Equals(end.Y, 1.f));
	EXPECT_TRUE(Math::Equals(end.Z, 0.f));

	end = rotation / start;
	EXPECT_TRUE(Math::Equals(end.X, 0.f));
	EXPECT_TRUE(Math::Equals(end.Y, -1.f));
	EXPECT_TRUE(Math::Equals(end.Z, 0.f));

	start = Vec3::Up;
	rotation = Quat::FromEuler(Vec3(90.f, 0.f, 90.f));
	end = rotation.Rotate(start);

	EXPECT_TRUE(Math::Equals(end.X, 0.f));
	EXPECT_TRUE(Math::Equals(end.Y, 0.f));
	EXPECT_TRUE(Math::Equals(end.Z, 1.f));

	end = rotation * start;
	EXPECT_TRUE(Math::Equals(end.X, 0.f));
	EXPECT_TRUE(Math::Equals(end.Y, 0.f));
	EXPECT_TRUE(Math::Equals(end.Z, 1.f));

	end = rotation / start;
	EXPECT_TRUE(Math::Equals(end.X, 1.f));
	EXPECT_TRUE(Math::Equals(end.Y, 0.f));
	EXPECT_TRUE(Math::Equals(end.Z, 0.f));
}

TEST(QuaternionUnitTest, Rotate_quaternion)
{
	Quat quat_1(0.65379899684951437f ,
				0.49198400932684733f ,
				-0.57343602132006610f ,
				-0.040862400050191698f);

	Quat quat_2(0.28456911695921927f,
				0.055287819843885436f,
				-0.16261099422502870f,
				-0.94314438937370981f);

	Quat expected_result(0.027064135033571496f,
							0.71033886691834713f ,
							0.19225567792515003f ,
							-0.67655301421661274f);

	Quat rotation = quat_1.Rotate(quat_2);

	EXPECT_TRUE(Math::Equals(rotation.W, expected_result.W));
	EXPECT_TRUE(Math::Equals(rotation.X, expected_result.X));
	EXPECT_TRUE(Math::Equals(rotation.Y, expected_result.Y));
	EXPECT_TRUE(Math::Equals(rotation.Z, expected_result.Z));
}

TEST(QuaternionUnitTest, Rotation_vectors)
{
	Quat quat_1(0.65379899684951437f,
		0.49198400932684733f,
		-0.57343602132006610f,
		-0.040862400050191698f);

	const Vec3 quat1_right_axis(
		0.33900278742950163f ,
		-0.61767429804632101f,
		0.70961649617805012f );

	EXPECT_TRUE(quat1_right_axis.Equals(quat_1.GetRightVector(), Math::FloatEpsilon));

	/// Precomputed values.
	const Vec3 quat1_up_axis(
		-0.51081111339960539f,
		0.51256399765763738f,
		0.69018124774053136f);

	EXPECT_TRUE(quat1_up_axis.Equals(quat_1.GetUpVector(), Math::FloatEpsilon));

	/// Precomputed values.
	const Vec3 quat1_forward_axis(
		-0.79003108580769366f,
		-0.59645335931504828f,
		-0.14175427196141333f);

	EXPECT_TRUE(quat1_forward_axis.Equals(quat_1.GetForwardVector(), Math::FloatEpsilon));
}

TEST(QuaternionUnitTest, Dot_product)
{
	Quat quat_1(2.8f, -6.8f, 4.5f, 8.4f);
	Quat quat_2(3.7f, 9.1f, -4.1f, -5.6f);

	float dot_product = quat_1.W * quat_2.W + quat_1.X * quat_2.X + quat_1.Y * quat_2.Y + quat_1.Z * quat_2.Z;

	EXPECT_FLOAT_EQ(Quat::DotProduct(quat_1, quat_2), dot_product);
}

TEST(QuaternionUnitTest, Lerp)
{
	Quat quat_1(2.8f, -6.8f, 4.5f, 8.4f);
	Quat quat_2(3.7f, 9.1f, -4.1f, -5.6f);

	Quat lerp_05alpha(3.25f, 1.15f, 0.2f, 1.4f);

	EXPECT_TRUE(lerp_05alpha.Equals(Quat::Lerp(quat_1, quat_2, 0.5f), 0.000001f));
	EXPECT_EQ(Quat::Lerp(quat_1, quat_2, -1.f), quat_1);
}

TEST(QuaternionUnitTest, SLerp)
{
	const Quat quat_1(0.653799f, 0.491984f, -0.573436f, -0.0408624f);
	const Quat quat_2(0.2845691f, 0.05528782f, -0.162611f,  -0.9431444f);
	const Quat slerp_res05alpha(0.5721251f, 0.3336728f, -0.4487695f, -0.5999511f);

	EXPECT_TRUE(slerp_res05alpha.Equals(Quat::SLerp(quat_1, quat_2, 0.5f), 0.000001f));
}

TEST(QuaternionUnitTest, float_operator)
{
	/*multiplication*/

	Quat quat_1(2.8f, -6.8f, 4.5f, 8.4f);
	Quat quat_2 = quat_1 * 2.f;
	
	EXPECT_TRUE(Math::Equals(quat_2.W, 5.6f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_2.X, -13.6f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_2.Y, 9.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_2.Z, 16.8f, 0.001f));

	quat_1 *= 2.f;

	EXPECT_TRUE(Math::Equals(quat_1.W, 5.6f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_1.X, -13.6f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_1.Y, 9.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_1.Z, 16.8f, 0.001f));

	Quat quat_3(3.7f, 9.1f, -4.1f, -5.6f);
	Quat quat_4 = quat_3 * -3.f;

	EXPECT_TRUE(Math::Equals(quat_4.W, -11.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_4.X, -27.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_4.Y, 12.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_4.Z, 16.8f, 0.001f));

	quat_3 *= -3.f;

	EXPECT_TRUE(Math::Equals(quat_3.W, -11.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.X, -27.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Y, 12.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Z, 16.8f, 0.001f));


	/*division*/
	Quat quat_5(5.f, -7.f, 6.f, 8.f);
	Quat quat_6 = quat_5 / 2.f;

	EXPECT_TRUE(Math::Equals(quat_6.W, 2.5f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_6.X, -3.5f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_6.Y, 3.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_6.Z, 4.f, 0.001f));

	quat_5 /= 2.f;

	EXPECT_TRUE(Math::Equals(quat_5.W, 2.5f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_5.X, -3.5f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_5.Y, 3.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_5.Z, 4.f, 0.001f));

	Quat quat_7(6.f, 9.f, -3.f, -12.f);
	Quat quat_8 = quat_7 / -3.f;

	EXPECT_TRUE(Math::Equals(quat_8.W, -2.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_8.X, -3.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_8.Y, 1.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_8.Z, 4.f, 0.001f));

	quat_7 /= -3.f;

	EXPECT_TRUE(Math::Equals(quat_7.W, -2.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_7.X, -3.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_7.Y, 1.f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_7.Z, 4.f, 0.001f));
}

TEST(QuaternionUnitTest, quaternions_operator)
{
	/*operator+*/
	Quat quat_1(5.f, -7.f, 6.f, 8.f);
	Quat quat_2(3.7f, 9.1f, -4.1f, -5.6f);

	Quat quat_3 = quat_1 + quat_2;

	EXPECT_TRUE(Math::Equals(quat_3.W, 8.7f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.X, 2.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Y, 1.9f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Z, 2.4f, 0.001f));

	quat_3 = quat_1;
	quat_3 += quat_2;
	EXPECT_TRUE(Math::Equals(quat_3.W, 8.7f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.X, 2.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Y, 1.9f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Z, 2.4f, 0.001f));

	/*operator-*/

	quat_3 = quat_1 - quat_2;

	EXPECT_TRUE(Math::Equals(quat_3.W, 1.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.X, -16.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Y, 10.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Z, 13.6f, 0.001f));

	quat_3 = quat_1;
	quat_3 -= quat_2;
	EXPECT_TRUE(Math::Equals(quat_3.W, 1.3f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.X, -16.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Y, 10.1f, 0.001f));
	EXPECT_TRUE(Math::Equals(quat_3.Z, 13.6f, 0.001f));

	/*operator**/

	quat_1 = Quat(0.65379899684951437f,
		0.49198400932684733f,
		-0.57343602132006610f,
		-0.040862400050191698f);

	quat_2 = Quat(0.28456911695921927f,
		0.055287819843885436f,
		-0.16261099422502870f,
		-0.94314438937370981f);

	Quat expected_result(0.027064135033571496f,
		0.71033886691834713f,
		0.19225567792515003f,
		-0.67655301421661274f);

	Quat rotation = quat_1 * quat_2;

	EXPECT_TRUE(Math::Equals(rotation.W, expected_result.W));
	EXPECT_TRUE(Math::Equals(rotation.X, expected_result.X));
	EXPECT_TRUE(Math::Equals(rotation.Y, expected_result.Y));
	EXPECT_TRUE(Math::Equals(rotation.Z, expected_result.Z));

	rotation = quat_1;
	rotation *= quat_2;

	EXPECT_TRUE(Math::Equals(rotation.W, expected_result.W));
	EXPECT_TRUE(Math::Equals(rotation.X, expected_result.X));
	EXPECT_TRUE(Math::Equals(rotation.Y, expected_result.Y));
	EXPECT_TRUE(Math::Equals(rotation.Z, expected_result.Z));

	/*operator/*/

	expected_result = Quat(0.34503787137100783f,
		-0.63804462461448919f,
		-0.40488548772720184f,
		-0.55670069709694570f);

	rotation = quat_1 / quat_2;

	EXPECT_TRUE(Math::Equals(rotation.W, expected_result.W));
	EXPECT_TRUE(Math::Equals(rotation.X, expected_result.X));
	EXPECT_TRUE(Math::Equals(rotation.Y, expected_result.Y));
	EXPECT_TRUE(Math::Equals(rotation.Z, expected_result.Z));

	rotation = quat_1;
	rotation /= quat_2;

	EXPECT_TRUE(Math::Equals(rotation.W, expected_result.W));
	EXPECT_TRUE(Math::Equals(rotation.X, expected_result.X));
	EXPECT_TRUE(Math::Equals(rotation.Y, expected_result.Y));
	EXPECT_TRUE(Math::Equals(rotation.Z, expected_result.Z));
}