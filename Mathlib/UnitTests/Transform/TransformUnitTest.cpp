#include <gtest/gtest.h>

#include <Collections/Mathlib.hpp>

using namespace Mathlib;

/**
*	\brief Unit test for constructors
*/
TEST(TransformUnitTest, Constructor)
{
	Vec3 position(12.6f, 8.3f, -4.1f);
	Vec3 rotation(90.0f, 120.f, -90.f);
	Quat rotation_quat = Quat::FromEuler(rotation);
	Vec3 scale(1.f, 1.f, 1.f);

	Transform transform_vec(rotation, position, scale);

	EXPECT_EQ(transform_vec.position, position);
	EXPECT_EQ(transform_vec.rotation, rotation_quat);
	EXPECT_EQ(transform_vec.scale, scale);

	Transform transform_quat(rotation_quat, position, scale);
	EXPECT_EQ(transform_quat.position, position);
	EXPECT_EQ(transform_quat.rotation, rotation_quat);
	EXPECT_EQ(transform_quat.scale, scale);

	Transform transform_pos(position);
	EXPECT_EQ(transform_pos.position, position);
	EXPECT_EQ(transform_pos.rotation, Quat::Identity);
	EXPECT_EQ(transform_pos.scale, Vec3::One);

	Transform transform_rot(rotation_quat);
	EXPECT_EQ(transform_rot.position, Vec3::Zero);
	EXPECT_EQ(transform_rot.rotation, rotation_quat);
	EXPECT_EQ(transform_rot.scale, Vec3::One);

	Transform transform_copy(transform_rot);
	EXPECT_EQ(transform_copy.position, Vec3::Zero);
	EXPECT_EQ(transform_copy.rotation, rotation_quat);
	EXPECT_EQ(transform_copy.scale, Vec3::One);
}

TEST(TransformUnitTest, Lerp)
{
	Vec3 position_1(12.6f, 8.3f, -4.1f);
	Vec3 rotation_1(90.0f, 120.f, -90.f);
	Quat rotation_quat_1 = Quat::FromEuler(rotation_1);
	Vec3 scale_1(1.f, 1.f, 1.f);

	Transform transform_1(rotation_1, position_1, scale_1);

	Vec3 position_2(14.1f, 6.5f, 8.4f);
	Vec3 rotation_2(90.0f, 0.f, 0.f);
	Quat rotation_quat_2 = Quat::FromEuler(rotation_2);
	Vec3 scale_2(2.f, 2.f, 1.5f);

	Transform transform_2(rotation_2, position_2, scale_2);

	Transform transform_3 = Transform::Lerp(transform_1, transform_2, 0.5f);
	Quat rotation_quat_3 = Quat::Lerp(rotation_quat_1, rotation_quat_2, 0.5f);

	EXPECT_EQ(transform_3.position, Vec3(13.35f, 7.4f, 2.15f));
	EXPECT_EQ(transform_3.rotation, rotation_quat_3);
	EXPECT_EQ(transform_3.scale, Vec3(1.5f, 1.5f, 1.25f));
}

TEST(TransformUnitTest, Equality)
{
	Vec3 position_1(12.6f, 8.3f, -4.1f);
	Vec3 rotation_1(90.0f, 120.f, -90.f);
	Quat rotation_quat_1 = Quat::FromEuler(rotation_1);
	Vec3 scale_1(1.f, 1.f, 1.f);

	Transform transform_1(rotation_1, position_1, scale_1);

	Vec3 position_2(14.1f, 6.5f, 8.4f);
	Vec3 rotation_2(90.0f, 0.f, 0.f);
	Quat rotation_quat_2 = Quat::FromEuler(rotation_2);
	Vec3 scale_2(2.f, 2.f, 1.5f);

	Transform transform_2(rotation_2, position_2, scale_2);

	// Equals
	EXPECT_FALSE(transform_1.Equals(transform_2));
	EXPECT_TRUE(transform_2.Equals(transform_2));

	//== operator
	EXPECT_FALSE(transform_1 == transform_2);
	EXPECT_TRUE(transform_2 == transform_2);

	// != operator
	EXPECT_TRUE(transform_1 != transform_2);
	EXPECT_FALSE(transform_2 != transform_2);
}

TEST(TransformUnitTest, Transform_Matrix)
{
	Vec3 position_1(12.6f, 8.3f, -4.1f);
	Vec3 rotation_1(90.0f, 120.f, -90.f);
	Vec3 scale_1(2.f, 2.f, 2.f);

	Transform transform_1(rotation_1, position_1, scale_1);

	Mat4 transform_matrix = Mat4(0.f, 0.f, -2.f, 12.6f,
								1.f, -1.73205113f, 0.f, 8.3f,
								-1.73205090f, -1.f, 0.f, -4.1f,
								0.f, 0.f, 0.f, 1.f);
	Mat4 transform_matrix_no_scale = Mat4(0.f, 0.f, -1.f, 12.6f,
										0.5f, -0.866025567f, 0.f, 8.3f,
										-0.866025448f, -0.5f, 0.f, -4.1f,
										0.f, 0.f, 0.f, 1.f);
	
	EXPECT_TRUE(transform_matrix.Equals(transform_1.ToMatrixWithScale(), 0.000001f));
	EXPECT_TRUE(transform_matrix_no_scale.Equals(transform_1.ToMatrixNoScale(), 0.000001f));

	Mat4 inverted_transform_matrix = Mat4(0.f, 0.25f, -0.433012635f, -3.85035229f,
									0.f, -0.433012575f, -0.25f, 2.56900406f,
									-0.5f, 0.f, 0.f, 6.3f,
									0.f, 0.f, 0.f, 1.f);
	Mat4 inverted_transform_matrix_no_scale = Mat4(0.f, 0.5f, -0.866025269f, -7.70070457f,
											0.f, -0.866025150f, -0.5f, 5.13800812f,
											-1.f, 0.f, 0.f, 12.6f,
											0.f, 0.f, 0.f, 1.f);

	EXPECT_TRUE(inverted_transform_matrix.Equals(transform_1.ToInverseMatrixWithScale(), 0.000001f));
	EXPECT_TRUE(inverted_transform_matrix_no_scale.Equals(transform_1.ToInverseMatrixNoScale(), 0.000001f));
}

TEST(TransformUnitTest, world_transform)
{
	Vec3 position_1(12.6f, 8.3f, -4.1f);
	Vec3 rotation_1(90.0f, 120.f, -90.f);
	Vec3 scale_1(1.f, 1.f, 1.f);

	Transform transform_1(rotation_1, position_1, scale_1);

	Vec3 position_2(14.1f, 6.5f, 8.4f);
	Vec3 rotation_2(90.0f, 0.f, 0.f);
	Vec3 scale_2(2.f, 2.f, 1.5f);

	Transform transform_2(rotation_2, position_2, scale_2);

	Vec3 position_3(4.2f, 9.72083664f, -19.5609608f);
	Quat rotation_3(0.707106769f, 0.707106769f, 0.f, 0.f);
	Vec3 scale_3(2.f, 2.f, 1.5f);
	Transform transform_3(rotation_3, position_3, scale_3);

	Transform world_transform = Transform::GetWorldTransfrom(transform_1, transform_2);

	EXPECT_TRUE(world_transform.Equals(transform_3, 0.00001f));

}