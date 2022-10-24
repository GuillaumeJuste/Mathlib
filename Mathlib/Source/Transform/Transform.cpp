#include <Transform/Transform.hpp>
#include <Matrix/Mat4.hpp>

using namespace Mathlib;

//Constructor

Transform::Transform(const Quat& _rotation, const Vec3& _position, const Vec3& _scale) noexcept :
	rotation{ _rotation }, position{ _position }, scale { _scale }
{

}

Transform::Transform(const Vec3& _rotation, const Vec3& _position, const Vec3& _scale) noexcept :
	position{ _position }, scale{ _scale }
{
	rotation = Quat::FromEuler(_rotation);
}

Transform::Transform(const Quat& _rotation) noexcept :
	rotation{ _rotation }, position{ Vec3::Zero }, scale{ Vec3::One }
{

}

Transform::Transform(const Vec3& _position) noexcept :
	rotation{ Quat::Identity }, position{ _position }, scale{ Vec3::One }
{

}

//Lerp

Transform Transform::Lerp(const Transform& _start, const Transform& _end, float _alpha)
{
	Transform result;
	result.rotation = Quat::Lerp(_start.rotation, _end.rotation, _alpha);
	result.position = Vec3::Lerp(_start.position, _end.position, _alpha);
	result.scale = Vec3::Lerp(_start.scale, _end.scale,_alpha);

	return result;
}

//Equality

bool Transform::Equals(const Transform& _other, float _epsilon) const noexcept
{
	return rotation.Equals(_other.rotation, _epsilon) &&
		position.Equals(_other.position, _epsilon) &&
		scale.Equals(_other.scale, _epsilon);
}

bool Transform::operator==(const Transform& _rhs) const noexcept
{
	return rotation == _rhs.rotation &&
		position == _rhs.position &&
		scale == _rhs.scale;
}

bool Transform::operator!=(const Transform& _rhs) const noexcept
{
	return !(rotation == _rhs.rotation &&
		position == _rhs.position &&
		scale == _rhs.scale);
}

//ToMatrix

Mat4 Transform::ToMatrixWithScale() const
{
	Mat4 transform = Mat4::RotationMatrix(rotation);
	
	transform.e00 *= scale.X;
	transform.e01 *= scale.X;
	transform.e02 *= scale.X;

	transform.e10 *= scale.Y;
	transform.e11 *= scale.Y;
	transform.e12 *= scale.Y;

	transform.e20 *= scale.Z;
	transform.e21 *= scale.Z;
	transform.e22 *= scale.Z;

	transform.e03 = position.X;
	transform.e13 = position.Y;
	transform.e23 = position.Z;

	return transform;
}

Mat4 Transform::ToInverseMatrixWithScale() const
{
	return ToMatrixWithScale().Inverse();
}

Mat4 Transform::ToMatrixNoScale() const
{
	Mat4 transform = Mat4::RotationMatrix(rotation);

	transform.e03 = position.X;
	transform.e13 = position.Y;
	transform.e23 = position.Z;

	return transform;
}

Mat4 Transform::ToInverseMatrixNoScale() const
{
	return ToMatrixNoScale().Inverse();
}

Transform Transform::GetWorldTransfrom(const Transform& _parent) const
{
	Transform result;
	result.rotation = rotation;
	result.position = _parent.rotation.Rotate(position) + _parent.position;
	result.scale = _parent.scale * scale;

	return result;
}

Vec3 Transform::GetForwardVector() const
{
	return rotation.GetForwardVector();
}

Vec3 Transform::GetRightVector() const
{
	return rotation.GetRightVector();
}

Vec3 Transform::GetUpVector() const
{
	return rotation.GetUpVector();
}