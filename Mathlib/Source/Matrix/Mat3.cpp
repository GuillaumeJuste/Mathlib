#include <Space/Vec2.hpp>
#include <Space/Vec3.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat2.hpp>
#include <Matrix/Mat3.hpp>
#include <Matrix/Mat4.hpp>

using namespace Mathlib;

#define CLASS_NAME "Mat3"

//Constants

const Mat3 Mat3::Zero = Mat3(0.f, 0.f, 0.f,
							0.f, 0.f, 0.f, 
							0.f, 0.f, 0.f);

const Mat3 Mat3::Identity = Mat3(1.f, 0.f, 0.f,
								0.f, 1.f, 0.f, 
								0.f, 0.f, 1.f);


//Constructors

Mat3::Mat3(float _e00, float _e01, float _e02,
	float _e10, float _e11, float _e12,
	float _e20, float _e21, float _e22) noexcept :
	e00{ _e00 }, e01{ _e01 }, e02{ _e02 },
	e10{ _e10 }, e11{ _e11 }, e12{ _e12 },
	e20{ _e20 }, e21{ _e21 }, e22{ _e22 }
{
}

Mat3::Mat3(float _value) noexcept :
	e00{ _value }, e01{ _value }, e02{ _value },
	e10{ _value }, e11{ _value }, e12{ _value },
	e20{ _value }, e21{ _value }, e22{ _value }
{
}

Mat3::Mat3(const Vec3& _row0, const Vec3& _row1, const Vec3& _row2) noexcept :
	e00{ _row0.X }, e01{ _row0.Y }, e02{ _row0.Z },
	e10{ _row1.X }, e11{ _row1.Y }, e12{ _row1.Z },
	e20{ _row2.X }, e21{ _row2.Y }, e22{ _row2.Z }
{
}

Mat3::Mat3(const Mat2& _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e02{ 0.f },
	e10{ _mat.e10 }, e11{ _mat.e11 }, e12{ 0.f },
	e20{ 0.f}, e21{ 0.f }, e22{ 1.f }
{
}

Mat3::Mat3(const Mat4& _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e02{ _mat.e02 },
	e10{ _mat.e10 }, e11{ _mat.e11 }, e12{ _mat.e12 },
	e20{ _mat.e20 }, e21{ _mat.e21 }, e22{ _mat.e22 }
{
}


//static methods

Mat3 Mat3::RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept
{
	float _x_angle_rad = _x_angle * Math::DegToRad;
	float _y_angle_rad = _y_angle * Math::DegToRad;
	float _z_angle_rad = _z_angle * Math::DegToRad;

	float cos_x = Math::Cos(_x_angle_rad);
	float sin_x = Math::Sin(_x_angle_rad);

	float cos_y = Math::Cos(_y_angle_rad);
	float sin_y = Math::Sin(_y_angle_rad);

	float cos_z = Math::Cos(_z_angle_rad);
	float sin_z = Math::Sin(_z_angle_rad);

	return Mat3(cos_z * cos_y, cos_z * sin_y * sin_x - sin_z * cos_x, cos_z * sin_y * cos_x + sin_z * sin_x,
				sin_z * cos_y, sin_z * sin_y * sin_x + cos_z * cos_y, sin_z * sin_y * cos_x - cos_z * sin_x,
				-sin_y, cos_y * sin_x, cos_y * cos_x);
}

Mat3 Mat3::RotationMatrix(const Vec3& _rotation) noexcept
{
	return Mat3::RotationMatrix(_rotation.X, _rotation.Y, _rotation.Z);
}

Mat3 Mat3::RotationMatrix2D(float _rotation) noexcept
{
	float cos = Math::Cos(_rotation);
	float sin = Math::Sin(_rotation);

	return Mat3(cos, -sin, 0.f,
				sin, cos, 0.f,
				0.f, 0.f, 1.f);
}

Mat3 Mat3::ScaleMatrix(float _scale) noexcept
{
	return Mat3(_scale, 0.f, 0.f,
				0.f, _scale, 0.f,
				0.f, 0.f, 1.f);
}

Mat3 Mat3::ScaleMatrix(const Vec2& _scale) noexcept
{
	return Mat3(_scale.X, 0.f, 0.f,
		0.f, _scale.Y, 0.f,
		0.f, 0.f, 1.f);
}

Mat3 Mat3::TranslationMatrix(const Vec2& _vec) noexcept
{
	return Mat3(1.f, 0.f, _vec.X,
				0.f, 1.f, _vec.Y,
				0.f, 0.f, 1.f);
}

Mat3 Mat3::TransformMatrix2D(float _rotation, const Vec2& _position, const Vec2& _scale) noexcept
{
	float cos = Math::Cos(_rotation);
	float sin = Math::Sin(_rotation);

	return Mat3(cos * _scale.X, -sin * _scale.X, _position.X,
		sin * _scale.Y, cos * _scale.Y, _position.Y,
		0.f, 0.f, 1.f);
}

//Accessors

const float* Mat3::Data() const noexcept
{
	return &e00;
}

float& Mat3::operator[](unsigned int _index)
{
	if (_index > 8)
		Callback::CallErrorCallback(CLASS_NAME, "operator[]", "Index out of bound");

	return (&e00)[_index];
}

//Equality

bool Mat3::IsZero() const noexcept
{
	return *this == Mat3::Zero;
}

bool Mat3::IsIdentity() const noexcept
{
	return *this == Mat3::Identity;
}

bool Mat3::Equals(const Mat3& _other, float _epsilon) const noexcept
{
	return Math::Equals(e00, _other.e00, _epsilon) &&
		Math::Equals(e01, _other.e01, _epsilon) &&
		Math::Equals(e02, _other.e02, _epsilon) &&
		Math::Equals(e10, _other.e10, _epsilon) &&
		Math::Equals(e11, _other.e11, _epsilon) &&
		Math::Equals(e12, _other.e12, _epsilon) &&
		Math::Equals(e20, _other.e20, _epsilon) &&
		Math::Equals(e21, _other.e21, _epsilon) &&
		Math::Equals(e22, _other.e22, _epsilon);
}

bool Mat3::operator==(const Mat3& _rhs) const noexcept
{
	return e00 == _rhs.e00 &&
		e01 == _rhs.e01 &&
		e02 == _rhs.e02 &&
		e10 == _rhs.e10 &&
		e11 == _rhs.e11 &&
		e12 == _rhs.e12 &&
		e20 == _rhs.e20 &&
		e21 == _rhs.e21 &&
		e22 == _rhs.e22 ;

}

bool Mat3::operator!=(const Mat3& _rhs) const noexcept
{
	return !(*this == _rhs);
}

//methods

Mat3 Mat3::Transpose() noexcept
{
	*this = GetTranspose();
	return *this;
}

Mat3 Mat3::GetTranspose()const noexcept
{
	return Mat3(e00, e10, e20,
				e01, e11, e21,
				e02, e12, e22);
}

Mat3 Mat3::Inverse() noexcept
{
	*this = GetInverse();
	return *this;
}

Mat3 Mat3::GetInverse() const noexcept
{
	float determinant = Determinant();
	if (determinant != 0.f)
	{
		return  Mat3(
			e11 * e22 - e21 * e12, e02 * e21 - e01 * e22, e01 * e12 - e11 * e02,
			e12 * e20 - e10 * e22, e00 * e22 - e20 * e02, e02 * e10 - e00 * e12,
			e10 * e21 - e20 * e11, e01 * e20 - e00 * e21, e00 * e11 - e10 * e01
		) * (1.0f / determinant);
	}
	Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Matrix determinant equal 0");
	return *this;
}

float Mat3::Determinant() const noexcept
{
	return e00 * (e11 * e22 - e12 * e21) - e01 * (e10 * e22 - e12 * e20) + e02 * (e10 * e21 - e11 * e20);
}

//operator

Mat3 Mat3::operator+(float _scale) const noexcept
{
	return Mat3(e00 + _scale, e01 + _scale, e02 + _scale,
				e10 + _scale, e11 + _scale, e12 + _scale,
				e20 + _scale, e21 + _scale, e22 + _scale);
}

Mat3 Mat3::operator-(float _scale) const noexcept
{
	return Mat3(e00 - _scale, e01 - _scale, e02 - _scale,
		e10 - _scale, e11 - _scale, e12 - _scale,
		e20 - _scale, e21 - _scale, e22 - _scale);
}

Mat3 Mat3::operator*(float _scale) const noexcept
{
	return Mat3(e00 * _scale, e01 * _scale, e02 * _scale,
		e10 * _scale, e11 * _scale, e12 * _scale,
		e20 * _scale, e21 * _scale, e22 * _scale);
}

Mat3 Mat3::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Mat3(e00 / _scale, e01 / _scale, e02 / _scale,
		e10 / _scale, e11 / _scale, e12 / _scale,
		e20 / _scale, e21 / _scale, e22 / _scale);
}

Mat3& Mat3::operator+=(float _scale) noexcept
{
	e00 += _scale;
	e01 += _scale;
	e02 += _scale;
	e10 += _scale;
	e11 += _scale;
	e12 += _scale;
	e20 += _scale;
	e21 += _scale;
	e22 += _scale;
	return *this;
}

Mat3& Mat3::operator-=(float _scale) noexcept
{
	e00 -= _scale;
	e01 -= _scale;
	e02 -= _scale;
	e10 -= _scale;
	e11 -= _scale;
	e12 -= _scale;
	e20 -= _scale;
	e21 -= _scale;
	e22 -= _scale;
	return *this;
}

Mat3& Mat3::operator*=(float _scale) noexcept
{
	e00 *= _scale;
	e01 *= _scale;
	e02 *= _scale;
	e10 *= _scale;
	e11 *= _scale;
	e12 *= _scale;
	e20 *= _scale;
	e21 *= _scale;
	e22 *= _scale;
	return *this;
}

Mat3& Mat3::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/=", "Division by 0");

	e00 /= _scale;
	e01 /= _scale;
	e02 /= _scale;
	e10 /= _scale;
	e11 /= _scale;
	e12 /= _scale;
	e20 /= _scale;
	e21 /= _scale;
	e22 /= _scale;
	return *this;
}

Vec3 Mat3::operator*(const Vec3& _rhs) const noexcept
{
	return Vec3(e00 * _rhs.X + e01 * _rhs.Y + e02 * _rhs.Z,
		e10 * _rhs.X + e11 * _rhs.Y + e12 * _rhs.Z,
		e20 * _rhs.X + e21 * _rhs.Y + e22 * _rhs.Z);
}

Mat3 Mat3::operator+(const Mat3& _rhs) const noexcept
{
	return Mat3(e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02, 
		e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12,
		e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22);
}

Mat3 Mat3::operator-(const Mat3& _rhs) const noexcept
{
	return Mat3(e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02,
				e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12,
				e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22);
}

Mat3 Mat3::operator*(const Mat3& _rhs) const noexcept
{
	return Mat3(
		e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20,
		e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21,
		e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22,

		e10* _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20,
		e10* _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21,
		e10* _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22,

		e20* _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20,
		e20* _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21,
		e20* _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22
	);
}

Mat3& Mat3::operator+=(const Mat3& _rhs) noexcept
{
	e00 += _rhs.e00;
	e01 += _rhs.e01;
	e02 += _rhs.e02;
	e10 += _rhs.e10;
	e11 += _rhs.e11;
	e12 += _rhs.e12;
	e20 += _rhs.e20;
	e21 += _rhs.e21;
	e22 += _rhs.e22;
	return *this;
}

Mat3& Mat3::operator-=(const Mat3& _rhs) noexcept
{
	e00 -= _rhs.e00;
	e01 -= _rhs.e01;
	e02 -= _rhs.e02;
	e10 -= _rhs.e10;
	e11 -= _rhs.e11;
	e12 -= _rhs.e12;
	e20 -= _rhs.e20;
	e21 -= _rhs.e21;
	e22 -= _rhs.e22;
	return *this;
}

Mat3& Mat3::operator*=(const Mat3& _rhs) noexcept
{
	Mat3 tmp = *this;
	e00 = tmp.e00* _rhs.e00 + tmp.e01 * _rhs.e10 + tmp.e02 * _rhs.e20;
	e01 = tmp.e00* _rhs.e01 + tmp.e01 * _rhs.e11 + tmp.e02 * _rhs.e21;
	e02 = tmp.e00* _rhs.e02 + tmp.e01 * _rhs.e12 + tmp.e02 * _rhs.e22;

	e10 = tmp.e10* _rhs.e00 + tmp.e11 * _rhs.e10 + tmp.e12 * _rhs.e20;
	e11 = tmp.e10* _rhs.e01 + tmp.e11 * _rhs.e11 + tmp.e12 * _rhs.e21;
	e12 = tmp.e10* _rhs.e02 + tmp.e11 * _rhs.e12 + tmp.e12 * _rhs.e22;

	e20 = tmp.e20* _rhs.e00 + tmp.e21 * _rhs.e10 + tmp.e22 * _rhs.e20;
	e21 = tmp.e20* _rhs.e01 + tmp.e21 * _rhs.e11 + tmp.e22 * _rhs.e21;
	e22 = tmp.e20* _rhs.e02 + tmp.e21 * _rhs.e12 + tmp.e22 * _rhs.e22;
	return *this;
}