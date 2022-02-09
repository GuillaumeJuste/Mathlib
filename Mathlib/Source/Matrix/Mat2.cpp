#include <Space/Vec2.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat2.hpp>
#include <Matrix/Mat3.hpp>
#include <Matrix/Mat4.hpp>

using namespace Mathlib;

#define CLASS_NAME "Mat2"

//Constants

const Mat2 Mat2::Zero = Mat2(0.f, 0.f, 
							0.f, 0.f);

const Mat2 Mat2::Identity = Mat2(1.f, 0.f, 
								0.f, 1.f);


//Constructors

Mat2::Mat2(float _e00, float _e01, float _e10, float _e11) noexcept :
	e00{ _e00 }, e01{ _e01 }, e10{ _e10 }, e11{ _e11 }
{
}

Mat2::Mat2(float _value) noexcept :
	e00{ _value }, e01{ _value }, e10{ _value }, e11{ _value }
{
}

Mat2::Mat2(Vec2 _row0, Vec2 _row1) noexcept:
	e00{ _row0.X }, e01{ _row0.Y }, e10{ _row1.X }, e11{ _row1.Y }
{
}

Mat2::Mat2(Mat3 _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e10{ _mat.e10 }, e11{ _mat.e11 }
{
}

Mat2::Mat2(Mat4 _mat) noexcept :
	e00{ _mat.e00 }, e01{ _mat.e01 }, e10{ _mat.e10 }, e11{ _mat.e11 }
{
}

//static methods

Mat2 Mat2::RotationMatrix(float _angle) noexcept
{
	float cos = Math::Cos(_angle);
	float sin = Math::Sin(_angle);

	return Mat2(cos, -sin, 
				sin, cos);
}

Mat2 Mat2::ScaleMatrix(float _scale) noexcept
{
	return Mat2(_scale, 0.f,
		0.f, _scale);
}

//Accessors

const float* Mat2::Data() const noexcept
{
	return &e00;
}

float& Mat2::operator[](unsigned int _index) 
{
	if(_index > 3)
		Callback::CallErrorCallback(CLASS_NAME, "operator[]", "Index out of bound");

	return (&e00)[_index];
}

//Equality

bool Mat2::IsZero() const noexcept
{
	return *this == Mat2::Zero;
}

bool Mat2::IsIdentity() const noexcept
{
	return *this == Mat2::Identity;
}

bool Mat2::Equals(const Mat2& _other, float _epsilon) const noexcept
{
	return Math::Equals(e00, _other.e00, _epsilon) &&
		Math::Equals(e01, _other.e01, _epsilon) &&
		Math::Equals(e10, _other.e10, _epsilon) &&
		Math::Equals(e11, _other.e11, _epsilon);
}

bool Mat2::operator==(const Mat2& _rhs) const noexcept
{
	return e00 == _rhs.e00 &&
		e01 == _rhs.e01 &&
		e10 == _rhs.e10 &&
		e11 == _rhs.e11;
}

bool Mat2::operator!=(const Mat2& _rhs) const noexcept
{
	return !(*this == _rhs);
}

//methods

Mat2 Mat2::Transpose() noexcept
{
	*this = GetTranspose();
	return *this;
}

Mat2 Mat2::GetTranspose()const noexcept
{
	return Mat2(e00, e10, e01, e11);
}

Mat2 Mat2::Inverse() noexcept
{
	*this = GetInverse();
	return *this;
}

Mat2 Mat2::GetInverse() const noexcept
{
	float determinant = Determinant();
	if(determinant != 0.f)
		return Mat2(e11, -e01, -e10, e00) / determinant;

	Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Matrix determinant equal 0");
	return *this;
}

float Mat2::Determinant() const noexcept
{
	return e00 * e11 - e01 * e10;
}

//operator

Mat2 Mat2::operator+(float _scale) const noexcept
{
	return Mat2(e00 + _scale, e01 + _scale,
		e10 + _scale, e11 + _scale);
}

Mat2 Mat2::operator-(float _scale) const noexcept
{
	return Mat2(e00 - _scale, e01 - _scale,
		e10 - _scale, e11 - _scale);
}

Mat2 Mat2::operator*(float _scale) const noexcept
{
	return Mat2(e00 * _scale, e01 * _scale,
		e10 * _scale, e11 * _scale);
}

Mat2 Mat2::operator/(float _scale) const
{
	if (_scale == 0.f )
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Mat2(e00 / _scale, e01 / _scale,
		e10 / _scale, e11 / _scale);
}

Mat2& Mat2::operator+=(float _scale) noexcept
{
	e00 += _scale;
	e01 += _scale;
	e10 += _scale;
	e11 += _scale;
	return *this;
}

Mat2& Mat2::operator-=(float _scale) noexcept
{
	e00 -= _scale;
	e01 -= _scale;
	e10 -= _scale;
	e11 -= _scale;
	return *this;
}

Mat2& Mat2::operator*=(float _scale) noexcept
{
	e00 *= _scale;
	e01 *= _scale;
	e10 *= _scale;
	e11 *= _scale;
	return *this;
}

Mat2& Mat2::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/=", "Division by 0");

	e00 /= _scale;
	e01 /= _scale;
	e10 /= _scale;
	e11 /= _scale;
	return *this;
}

Vec2 Mat2::operator*(const Vec2& _vec) const noexcept
{
	return Vec2(e00 * _vec.X + e01 * _vec.Y,
		e10 * _vec.X + e11 * _vec.Y);
}

Mat2 Mat2::operator+(const Mat2& _mat) const noexcept
{
	return Mat2(e00 + _mat.e00, e01 + _mat.e01,
		e10 + _mat.e10, e11 + _mat.e11);
}

Mat2 Mat2::operator-(const Mat2& _mat) const noexcept
{
	return Mat2(e00 - _mat.e00, e01 - _mat.e01,
		e10 - _mat.e10, e11 - _mat.e11);
}

Mat2 Mat2::operator*(const Mat2& _mat) const noexcept
{
	return Mat2(e00 * _mat.e00 + e01 * _mat.e10, e00 * _mat.e01 + e01 * _mat.e11,
		e10 * _mat.e00 + e11 * _mat.e10, e10 * _mat.e01 + e11 * _mat.e11);
}

Mat2& Mat2::operator+=(const Mat2& _mat) noexcept
{
	e00 += _mat.e00;
	e01 += _mat.e01;
	e10 += _mat.e10;
	e11 += _mat.e11;
	return *this;
}

Mat2& Mat2::operator-=(const Mat2& _mat) noexcept
{
	e00 -= _mat.e00;
	e01 -= _mat.e01;
	e10 -= _mat.e10;
	e11 -= _mat.e11;
	return *this;
}

Mat2& Mat2::operator*=(const Mat2& _mat) noexcept
{
	Mat2 tmp = *this;
	e00 = tmp.e00 * _mat.e00 + tmp.e01 * _mat.e10;
	e01 = tmp.e00 * _mat.e01 + tmp.e01 * _mat.e11;
	e10 = tmp.e10 * _mat.e00 + tmp.e11 * _mat.e10;
	e11 = tmp.e10 * _mat.e01 + tmp.e11 * _mat.e11;
	return *this;
}