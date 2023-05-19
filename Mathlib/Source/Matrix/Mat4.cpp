#include <Space/Vec3.hpp>
#include <Space/Vec4.hpp>
#include <Space/Quaternion.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat2.hpp>
#include <Matrix/Mat3.hpp>
#include <Matrix/Mat4.hpp>


using namespace Mathlib;

#define CLASS_NAME "Mat4"

//Constants

const Mat4 Mat4::Zero = Mat4(0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f, 
	0.f, 0.f, 0.f, 0.f,
	0.f, 0.f, 0.f, 0.f);

const Mat4 Mat4::Identity = Mat4(1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f);


//Constructors

Mat4::Mat4(float _e00, float _e01, float _e02, float _e03,
	float _e10, float _e11, float _e12, float _e13,
	float _e20, float _e21, float _e22, float _e23,
	float _e30, float _e31, float _e32, float _e33) noexcept :
	e00{ _e00 }, e01{ _e01 }, e02{ _e02 }, e03{ _e03 },
	e10{ _e10 }, e11{ _e11 }, e12{ _e12 }, e13{ _e13 },
	e20{ _e20 }, e21{ _e21 }, e22{ _e22 }, e23{ _e23 },
	e30{ _e30 }, e31{ _e31 }, e32{ _e32 }, e33{ _e33 }
{
}

Mat4::Mat4(float _value) noexcept :
	e00{ _value }, e01{ _value }, e02{ _value }, e03{ _value },
	e10{ _value }, e11{ _value }, e12{ _value }, e13{ _value },
	e20{ _value }, e21{ _value }, e22{ _value }, e23{ _value },
	e30{ _value }, e31{ _value }, e32{ _value }, e33{ _value }
{
}

Mat4::Mat4(const Vec4& _row0, const Vec4& _row1, const Vec4& _row2, const Vec4& _row3) noexcept :
	e00{ _row0.X }, e01{ _row0.Y }, e02{ _row0.Z }, e03{ _row0.W },
	e10{ _row1.X }, e11{ _row1.Y }, e12{ _row1.Z }, e13{ _row1.W },
	e20{ _row2.X }, e21{ _row2.Y }, e22{ _row2.Z }, e23{ _row2.W },
	e30{ _row3.X }, e31{ _row3.Y }, e32{ _row3.Z }, e33{ _row3.W }
{
}

Mat4::Mat4(const Mat2& _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e02{ 0.f }, e03{ 0.f },
	e10{ _mat.e10 }, e11{ _mat.e11 }, e12{ 0.f }, e13{ 0.f },
	e20{ 0.f }, e21{ 0.f }, e22{ 1.f }, e23{ 0.f },
	e30{ 0.f }, e31{ 0.f }, e32{ 0.f }, e33{ 1.f }
{
}

Mat4::Mat4(const Mat3& _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e02{ _mat.e02 }, e03{ 0.f },
	e10{ _mat.e10 }, e11{ _mat.e11 }, e12{ _mat.e12 }, e13{ 0.f },
	e20{ _mat.e20 }, e21{ _mat.e21 }, e22{ _mat.e22 }, e23{ 0.f },
	e30{ 0.f }, e31{ 0.f }, e32{ 0.f }, e33{ 1.f }
{
}

//static methods

Mat4 Mat4::RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept
{
	float cos_x = Math::Cos(_x_angle);
	float sin_x = Math::Sin(_x_angle);

	float cos_y = Math::Cos(_y_angle);
	float sin_y = Math::Sin(_y_angle);

	float cos_z = Math::Cos(_z_angle);
	float sin_z = Math::Sin(_z_angle);

	return Mat4(cos_z * cos_y, cos_z * sin_y * sin_x - sin_z * cos_x, cos_z * sin_y * cos_x + sin_z * sin_x, 0.f,
		sin_z * cos_y, sin_z * sin_y * sin_x + cos_z * cos_y, sin_z * sin_y * cos_x - cos_z * sin_x, 0.f,
		-sin_y, cos_y * sin_x, cos_y * cos_x, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

Mat4 Mat4::RotationMatrix(const Vec3& _rotation) noexcept
{
	return Mat4::RotationMatrix(_rotation.X, _rotation.Y, _rotation.Z);
}

Mat4 Mat4::RotationMatrix(const Quat& _rotation) noexcept
{
	if (!_rotation.IsNormalized())
		Callback::CallErrorCallback(CLASS_NAME, "ToMatrix", "Quat should be normalized");



	return Mat4(1.f - 2.f * _rotation.Y * _rotation.Y - 2.f * _rotation.Z * _rotation.Z,
		2.f * _rotation.X * _rotation.Y - 2.f * _rotation.Z * _rotation.W,
		2.f * _rotation.X * _rotation.Z + 2.f * _rotation.Y * _rotation.W,
		0.f,

		2.f * _rotation.X * _rotation.Y + 2.f * _rotation.Z * _rotation.W,
		1.f - 2.f * _rotation.X * _rotation.X - 2.f * _rotation.Z * _rotation.Z,
		2.f * _rotation.Y * _rotation.Z - 2.f * _rotation.X * _rotation.W,
		0.f,

		2.f * _rotation.X * _rotation.Z - 2.f * _rotation.Y * _rotation.W,
		2.f * _rotation.Y * _rotation.Z + 2.f * _rotation.X * _rotation.W,
		1.f - 2.f * _rotation.X * _rotation.X - 2.f * _rotation.Y * _rotation.Y,
		0.f,

		0.f,
		0.f,
		0.f,
		1.f
	);
}

Mat4 Mat4::ScaleMatrix(float _scale) noexcept
{
	return Mat4(_scale, 0.f, 0.f, 0.f,
		0.f, _scale, 0.f, 0.f,
		0.f, 0.f, _scale, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

Mat4 Mat4::ScaleMatrix(const Vec3& _scale) noexcept
{
	return Mat4(_scale.X, 0.f, 0.f, 0.f,
		0.f, _scale.Y, 0.f, 0.f,
		0.f, 0.f, _scale.Z, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

Mat4 Mat4::TranslationMatrix(const Vec3& _vec) noexcept
{
	return Mat4(1.f, 0.f, 0.f, _vec.X,
		0.f, 1.f, 0.f, _vec.Y,
		0.f, 0.f, 1.f, _vec.Z,
		0.f, 0.f, 0.f, 1.f);
}

Mat4 Mat4::ViewMatrixLH(const Vec3& _eye, const Vec3& _forward, const Vec3& _up)
{
	Vec3 look = _forward.GetNormalized();
	Vec3 right = Vec3::CrossProduct(_up, look).Normalize();
	Vec3 up = _up.GetNormalized();

	return Mat4(right.X, right.Y, right.Z, -Vec3::DotProduct(right, _eye),
		up.X, up.Y, up.Z, -Vec3::DotProduct(up, _eye),
		look.X, look.Y, look.Z, -Vec3::DotProduct(look, _eye),
		0.f, 0.f, 0.f, 1.f);

}

Mat4 Mat4::ViewMatrixRH(const Vec3& _eye, const Vec3& _forward, const Vec3& _up)
{
	Vec3 look = -_forward.GetNormalized();
	Vec3 right = Vec3::CrossProduct(look, _up).Normalize();
	Vec3 up = _up.GetNormalized();

	return Mat4(right.X, right.Y, right.Z, -Vec3::DotProduct(right, _eye),
		up.X, up.Y, up.Z, -Vec3::DotProduct(up, _eye),
		-look.X, -look.Y, -look.Z, -Vec3::DotProduct(look, _eye),
		0.f, 0.f, 0.f, 1.f);
}

Mat4 Mat4::ViewMatrix(COORDINATE_SYSTEM _coordinate_system, const Vec3& _eye, const Vec3& _center, const Vec3& _up)
{
	if (_coordinate_system == COORDINATE_SYSTEM::LEFT_HAND)
		return ViewMatrixLH(_eye, _center, _up);
	else
		return ViewMatrixRH(_eye, _center, _up);
}

Mat4 Mat4::PerspectiveMatrixLH(float _fovy, float _aspect, float _near, float _far)
{
	if (Math::Equals(_aspect, 0.f))
		Callback::CallErrorCallback(CLASS_NAME, "PerspectiveMatrixLH", "render window aspect is 0");

	float tan_half_fov = Math::Tan(_fovy / 2.f);

	Mat4 result = Mat4::Zero;
	result.e00 = 1.f / (_aspect * tan_half_fov);
	result.e11 = 1.f / (tan_half_fov);
	result.e22 = (_far + _near) / (_far - _near);
	result.e23 = -(2.f * _far * _near) / (_far - _near);
	result.e32 = 1.f;

	return result;
}

Mat4 Mat4::PerspectiveMatrixRH(float _fovy, float _aspect, float _near, float _far)
{
	if (Math::Equals(_aspect, 0.f))
		Callback::CallErrorCallback(CLASS_NAME, "PerspectiveMatrixRH", "render window aspect is 0");

	float tan_half_fov = Math::Tan(_fovy / 2.f);

	Mat4 result = Mat4::Zero;
	result.e00 = 1.f / (_aspect * tan_half_fov);
	result.e11 = 1.f / (tan_half_fov);
	result.e22 = -(_far + _near) / (_far - _near);
	result.e23 = -(2.f * _far * _near) / (_far - _near);
	result.e32 = -1.f;

	return result;
}

Mat4 Mat4::PerspectiveMatrix(COORDINATE_SYSTEM _coordinate_system, float _fovy, float _aspect, float _near, float _far)
{
	if (_coordinate_system == COORDINATE_SYSTEM::LEFT_HAND)
		return PerspectiveMatrixLH(_fovy, _aspect, _near, _far);
	else
		return PerspectiveMatrixRH(_fovy, _aspect, _near, _far);
}

//Accessors

const float* Mat4::Data() const noexcept
{
	return &e00;
}

float& Mat4::operator[](unsigned int _index)
{
	if (_index > 15)
		Callback::CallErrorCallback(CLASS_NAME, "operator[]", "Index out of bound");

	return (&e00)[_index];
}

//Equality

bool Mat4::IsZero() const noexcept
{
	return *this == Mat4::Zero;
}

bool Mat4::IsIdentity() const noexcept
{
	return *this == Mat4::Identity;
}

bool Mat4::Equals(const Mat4& _other, float _epsilon) const noexcept
{
	return Math::Equals(e00, _other.e00, _epsilon) &&
		Math::Equals(e01, _other.e01, _epsilon) &&
		Math::Equals(e02, _other.e02, _epsilon) &&
		Math::Equals(e03, _other.e03, _epsilon) &&
		Math::Equals(e10, _other.e10, _epsilon) &&
		Math::Equals(e11, _other.e11, _epsilon) &&
		Math::Equals(e12, _other.e12, _epsilon) &&
		Math::Equals(e13, _other.e13, _epsilon) &&
		Math::Equals(e20, _other.e20, _epsilon) &&
		Math::Equals(e21, _other.e21, _epsilon) &&
		Math::Equals(e22, _other.e22, _epsilon) &&
		Math::Equals(e23, _other.e23, _epsilon) &&
		Math::Equals(e30, _other.e30, _epsilon) &&
		Math::Equals(e31, _other.e31, _epsilon) &&
		Math::Equals(e32, _other.e32, _epsilon) &&
		Math::Equals(e33, _other.e33, _epsilon);
}

bool Mat4::operator==(const Mat4& _rhs) const noexcept
{
	return e00 == _rhs.e00 &&
		e01 == _rhs.e01 &&
		e02 == _rhs.e02 &&
		e03 == _rhs.e03 &&
		e10 == _rhs.e10 &&
		e11 == _rhs.e11 &&
		e12 == _rhs.e12 &&
		e13 == _rhs.e13 &&
		e20 == _rhs.e20 &&
		e21 == _rhs.e21 &&
		e22 == _rhs.e22 &&
		e23 == _rhs.e23 &&
		e30 == _rhs.e30 &&
		e31 == _rhs.e31 &&
		e32 == _rhs.e32 &&
		e33 == _rhs.e33;

}

bool Mat4::operator!=(const Mat4& _rhs) const noexcept
{
	return !(*this == _rhs);
}

//methods

Mat4 Mat4::Transpose() noexcept
{
	*this = GetTranspose();
	return *this;
}

Mat4 Mat4::GetTranspose()const noexcept
{
	return Mat4(e00, e10, e20, e30,
		e01, e11, e21, e31,
		e02, e12, e22, e32,
		e03, e13, e23, e33);
}

Mat4 Mat4::Inverse() noexcept
{
	*this = GetInverse();
	return *this;
}

Mat4 Mat4::GetInverse() const noexcept
{
	float determinant = Determinant();
	if (determinant != 0.f)
	{
		float _00x11 = e00 * e11;
		float _00x12 = e00 * e12;
		float _00x13 = e00 * e13;

		float _01x10 = e01 * e10;
		float _01x12 = e01 * e12;
		float _01x13 = e01 * e13;

		float _02x10 = e02 * e10;
		float _02x11 = e02 * e11;
		float _02x13 = e02 * e13;

		float _03x10 = e03 * e10;
		float _03x11 = e03 * e11;
		float _03x12 = e03 * e12;
		float _03x32 = e03 * e32;

		float _12x21 = e12 * e21;

		float _13x32 = e13 * e32;

		float _20x31 = e20 * e31;
		float _20x32 = e20 * e32;
		float _20x33 = e20 * e33;

		float _21x30 = e21 * e30;
		float _21x32 = e21 * e32;
		float _21x33 = e21 * e33;

		float _22x30 = e22 * e30;
		float _22x31 = e22 * e31;
		float _22x33 = e22 * e33;

		float _23x30 = e23 * e30;
		float _23x31 = e23 * e31;
		float _23x32 = e23 * e32;

		return  Mat4(
			e11 * _22x33 + e12 * _23x31 + e21 * _13x32 - e13 * _22x31 - e33 * _12x21 - e11 * _23x32,
			-e01 * _22x33 - e02 * _23x31 - e21 * _03x32 + e03 * _22x31 + e02 * _21x33 + e01 * _23x32,
			e33 * _01x12 - e01 * _13x32 - e33 * _02x11 + e11 * _03x32 + e31 * _02x13 - e31 * _03x12,
			e23 * -_01x12 - e21 * _02x13 - e22 * _03x11 + e03 * _12x21 + e23 * _02x11 + e22 * _01x13,

			-e10 * _22x33 + e10 * _23x32 + e12 * _20x33 - e20 * _13x32 - e12 * _23x30 + e13 * _22x30,
			e00 * _22x33 + e02 * _23x30 + e20 * _03x32 - e03 * _22x30 - e02 * _20x33 - e00 * _23x32,
			-e33 * _00x12 - e30 * _02x13 - e10 * _03x32 +  e30 * _03x12 + e33 * _02x10 + e00 * _13x32,
			e23 * _00x12 - e22 * _00x13 - e23 * _02x10 + e22 * _03x10 + e20 * _02x13 - e20 * _03x12,

			e10 * _21x33 + e11 * _23x30 + e13 * _20x31 - e13 * _21x30 - e11 * _20x33 - e10 * _23x31,
			-e00 * _21x33 + e00 * _23x31 + e01 * _20x33 + e03 * _21x30 - e01 * _23x30 - e03 * _20x31,
			e33 * _00x11 + e30 * _01x13 + e31 * _03x10 - e30 * _03x11 - e33 * _01x10 - e31 * _00x13,
			-e23 * _00x11 - e20 * _01x13 - e21 * _03x10 + e20 * _03x11 + e23 * _01x10 + e21 * _00x13,

			-e10 * _21x32 - e11 * _22x30 - e12 * _20x31 + e30 * _12x21 + e11 * _20x32 + e10 * _22x31,
			e00 * _21x32 + e01 * _22x30 + e02 * _20x31 - e02 * _21x30 - e01 * _20x32 - e00 * _22x31,
			- e32 * _00x11 - e30 * _01x12 - e31 * _02x10 + e30 * _02x11 + e32 * _01x10 + e31 * _00x12 ,		
			e22 * _00x11 - e00 * _12x21 - e22 * _01x10 + e21 * _02x10 + e20 * _01x12 - e20 * _02x11) * (1.0f / determinant);
	}
	Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Matrix determinant equal 0");
	return *this;
}

float Mat4::Determinant() const noexcept
{
	float det_22_23_32_33 = e22 * e33 - e23 * e32;
	float det_21_22_31_32 = e21 * e32 - e22 * e31;
	float det_21_23_31_33 = e21 * e33 - e23 * e31;
	float det_20_23_30_33 = e20 * e33 - e23 * e30;
	float det_20_22_30_32 = e20 * e32 - e22 * e30;
	float det_20_21_30_31 = e20 * e31 - e21 * e30;

	return e00 * (e11 * det_22_23_32_33 - e12 * det_21_23_31_33 + e13 * det_21_22_31_32) -
		e01 * (e10 * det_22_23_32_33 - e12 * det_20_23_30_33 + e13 * det_20_22_30_32) +
		e02 * (e10 * det_21_23_31_33 - e11 * det_20_23_30_33 + e13 * det_20_21_30_31) -
		e03 * (e10 * det_21_22_31_32 - e11 * det_20_22_30_32 + e12 * det_20_21_30_31);
}


//operator

Mat4 Mat4::operator+(float _scale) const noexcept
{
	return Mat4(e00 + _scale, e01 + _scale, e02 + _scale, e03 + _scale,
		e10 + _scale, e11 + _scale, e12 + _scale, e13 + _scale,
		e20 + _scale, e21 + _scale, e22 + _scale, e23 + _scale,
		e30 + _scale, e31 + _scale, e32 + _scale, e33 + _scale);
}

Mat4 Mat4::operator-(float _scale) const noexcept
{
	return Mat4(e00 - _scale, e01 - _scale, e02 - _scale, e03 - _scale,
		e10 - _scale, e11 - _scale, e12 - _scale, e13 - _scale,
		e20 - _scale, e21 - _scale, e22 - _scale, e23 - _scale,
		e30 - _scale, e31 - _scale, e32 - _scale, e33 - _scale);
}

Mat4 Mat4::operator*(float _scale) const noexcept
{
	return Mat4(e00 * _scale, e01 * _scale, e02 * _scale, e03 * _scale,
		e10 * _scale, e11 * _scale, e12 * _scale, e13 * _scale,
		e20 * _scale, e21 * _scale, e22 * _scale, e23 * _scale,
		e30 * _scale, e31 * _scale, e32 * _scale, e33 * _scale);
}

Mat4 Mat4::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Mat4(e00 / _scale, e01 / _scale, e02 / _scale, e03 / _scale,
		e10 / _scale, e11 / _scale, e12 / _scale, e13 / _scale,
		e20 / _scale, e21 / _scale, e22 / _scale, e23 / _scale,
		e30 / _scale, e31 / _scale, e32 / _scale, e33 / _scale);
}

Mat4& Mat4::operator+=(float _scale) noexcept
{
	e00 += _scale;
	e01 += _scale;
	e02 += _scale;
	e03 += _scale;
	e10 += _scale;
	e11 += _scale;
	e12 += _scale;
	e13 += _scale;
	e20 += _scale;
	e21 += _scale;
	e22 += _scale;
	e23 += _scale;
	e30 += _scale;
	e31 += _scale;
	e32 += _scale;
	e33 += _scale;

	return *this;
}

Mat4& Mat4::operator-=(float _scale) noexcept
{
	e00 -= _scale;
	e01 -= _scale;
	e02 -= _scale;
	e03 -= _scale;
	e10 -= _scale;
	e11 -= _scale;
	e12 -= _scale;
	e13 -= _scale;
	e20 -= _scale;
	e21 -= _scale;
	e22 -= _scale;
	e23 -= _scale;
	e30 -= _scale;
	e31 -= _scale;
	e32 -= _scale;
	e33 -= _scale;

	return *this;
}

Mat4& Mat4::operator*=(float _scale) noexcept
{
	e00 *= _scale;
	e01 *= _scale;
	e02 *= _scale;
	e03 *= _scale;
	e10 *= _scale;
	e11 *= _scale;
	e12 *= _scale;
	e13 *= _scale;
	e20 *= _scale;
	e21 *= _scale;
	e22 *= _scale;
	e23 *= _scale;
	e30 *= _scale;
	e31 *= _scale;
	e32 *= _scale;
	e33 *= _scale;

	return *this;
}

Mat4& Mat4::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/=", "Division by 0");

	e00 /= _scale;
	e01 /= _scale;
	e02 /= _scale;
	e03 /= _scale;
	e10 /= _scale;
	e11 /= _scale;
	e12 /= _scale;
	e13 /= _scale;
	e20 /= _scale;
	e21 /= _scale;
	e22 /= _scale;
	e23 /= _scale;
	e30 /= _scale;
	e31 /= _scale;
	e32 /= _scale;
	e33 /= _scale;

	return *this;
}

Vec4 Mat4::operator*(const Vec4& _rhs) const noexcept
{
	return Vec4(e00 * _rhs.X + e01 * _rhs.Y + e02 * _rhs.Z + e03 * _rhs.W,
		e10 * _rhs.X + e11 * _rhs.Y + e12 * _rhs.Z + e13 * _rhs.W,
		e20 * _rhs.X + e21 * _rhs.Y + e22 * _rhs.Z + e23 * _rhs.W,
		e30 * _rhs.X + e31 * _rhs.Y + e32 * _rhs.Z + e33 * _rhs.W);
}

Mat4 Mat4::operator+(const Mat4& _rhs) const noexcept
{
	return Mat4(e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02, e03 + _rhs.e03,
		e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12, e13 + _rhs.e13,
		e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22, e23 + _rhs.e23, 
		e30 + _rhs.e30, e31 + _rhs.e31, e32 + _rhs.e32, e33 + _rhs.e33);
}

Mat4 Mat4::operator-(const Mat4& _rhs) const noexcept
{
	return Mat4(e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02, e03 - _rhs.e03,
		e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12, e13 - _rhs.e13,
		e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22, e23 - _rhs.e23,
		e30 - _rhs.e30, e31 - _rhs.e31, e32 - _rhs.e32, e33 - _rhs.e33);
}

Mat4 Mat4::operator*(const Mat4& _rhs) const noexcept
{
	return Mat4(
		e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20 + e03 * _rhs.e30,
		e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21 + e03 * _rhs.e31,
		e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22 + e03 * _rhs.e32,
		e00 * _rhs.e03 + e01 * _rhs.e13 + e02 * _rhs.e23 + e03 * _rhs.e33,

		e10 * _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20 + e13 * _rhs.e30,
		e10 * _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21 + e13 * _rhs.e31,
		e10 * _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22 + e13 * _rhs.e32,
		e10 * _rhs.e03 + e11 * _rhs.e13 + e12 * _rhs.e23 + e13 * _rhs.e33,

		e20 * _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20 + e23 * _rhs.e30,
		e20 * _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21 + e23 * _rhs.e31,
		e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22 + e23 * _rhs.e32,
		e20 * _rhs.e03 + e21 * _rhs.e13 + e22 * _rhs.e23 + e23 * _rhs.e33,

		e30 * _rhs.e00 + e31 * _rhs.e10 + e32 * _rhs.e20 + e33 * _rhs.e30,
		e30 * _rhs.e01 + e31 * _rhs.e11 + e32 * _rhs.e21 + e33 * _rhs.e31,
		e30 * _rhs.e02 + e31 * _rhs.e12 + e32 * _rhs.e22 + e33 * _rhs.e32,
		e30 * _rhs.e03 + e31 * _rhs.e13 + e32 * _rhs.e23 + e33 * _rhs.e33
	);
}

Mat4& Mat4::operator+=(const Mat4& _rhs) noexcept
{
	e00 += _rhs.e00;
	e01 += _rhs.e01;
	e02 += _rhs.e02;
	e03 += _rhs.e03;
	e10 += _rhs.e10;
	e11 += _rhs.e11;
	e12 += _rhs.e12;
	e13 += _rhs.e13;
	e20 += _rhs.e20;
	e21 += _rhs.e21;
	e22 += _rhs.e22;
	e23 += _rhs.e23;
	e30 += _rhs.e30;
	e31 += _rhs.e31;
	e32 += _rhs.e32;
	e33 += _rhs.e33;

	return *this;
}

Mat4& Mat4::operator-=(const Mat4& _rhs) noexcept
{
	e00 -= _rhs.e00;
	e01 -= _rhs.e01;
	e02 -= _rhs.e02;
	e03 -= _rhs.e03;
	e10 -= _rhs.e10;
	e11 -= _rhs.e11;
	e12 -= _rhs.e12;
	e13 -= _rhs.e13;
	e20 -= _rhs.e20;
	e21 -= _rhs.e21;
	e22 -= _rhs.e22;
	e23 -= _rhs.e23;
	e30 -= _rhs.e30;
	e31 -= _rhs.e31;
	e32 -= _rhs.e32;
	e33 -= _rhs.e33;

	return *this;
}

Mat4& Mat4::operator*=(const Mat4& _rhs) noexcept
{
	Mat4 tmp = *this;
	e00 = tmp.e00 * _rhs.e00 + tmp.e01 * _rhs.e10 + tmp.e02 * _rhs.e20 + tmp.e03 * _rhs.e30;
	e01 = tmp.e00 * _rhs.e01 + tmp.e01 * _rhs.e11 + tmp.e02 * _rhs.e21 + tmp.e03 * _rhs.e31;
	e02 = tmp.e00 * _rhs.e02 + tmp.e01 * _rhs.e12 + tmp.e02 * _rhs.e22 + tmp.e03 * _rhs.e32;
	e03 = tmp.e00 * _rhs.e03 + tmp.e01 * _rhs.e13 + tmp.e02 * _rhs.e23 + tmp.e03 * _rhs.e33;

	e10 = tmp.e10 * _rhs.e00 + tmp.e11 * _rhs.e10 + tmp.e12 * _rhs.e20 + tmp.e13 * _rhs.e30;
	e11 = tmp.e10 * _rhs.e01 + tmp.e11 * _rhs.e11 + tmp.e12 * _rhs.e21 + tmp.e13 * _rhs.e31;
	e12 = tmp.e10 * _rhs.e02 + tmp.e11 * _rhs.e12 + tmp.e12 * _rhs.e22 + tmp.e13 * _rhs.e32;
	e13 = tmp.e10 * _rhs.e03 + tmp.e11 * _rhs.e13 + tmp.e12 * _rhs.e23 + tmp.e13 * _rhs.e33;

	e20 = tmp.e20 * _rhs.e00 + tmp.e21 * _rhs.e10 + tmp.e22 * _rhs.e20 + tmp.e23 * _rhs.e30;
	e21 = tmp.e20 * _rhs.e01 + tmp.e21 * _rhs.e11 + tmp.e22 * _rhs.e21 + tmp.e23 * _rhs.e31;
	e22 = tmp.e20 * _rhs.e02 + tmp.e21 * _rhs.e12 + tmp.e22 * _rhs.e22 + tmp.e23 * _rhs.e32;
	e23 = tmp.e20 * _rhs.e03 + tmp.e21 * _rhs.e13 + tmp.e22 * _rhs.e23 + tmp.e23 * _rhs.e33;

	e30 = tmp.e30 * _rhs.e00 + tmp.e31 * _rhs.e10 + tmp.e32 * _rhs.e20 + tmp.e33 * _rhs.e30;
	e31 = tmp.e30 * _rhs.e01 + tmp.e31 * _rhs.e11 + tmp.e32 * _rhs.e21 + tmp.e33 * _rhs.e31;
	e32 = tmp.e30 * _rhs.e02 + tmp.e31 * _rhs.e12 + tmp.e32 * _rhs.e22 + tmp.e33 * _rhs.e32;
	e33 = tmp.e30 * _rhs.e03 + tmp.e31 * _rhs.e13 + tmp.e32 * _rhs.e23 + tmp.e33 * _rhs.e33;

	return *this;
}