#include <Vector/Vec2.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat2.hpp>

using namespace Mathlib;

#define CLASS_NAME "Mat2"

//Constants

const Mat2 Mat2::Zero = Mat2(0.f, 0.f, 
							0.f, 0.f);

const Mat2 Mat2::Identity = Mat2(1.f, 0.f, 
								0.f, 1.f);


//Constructors

Mat2::Mat2() noexcept :
	X { 0.f }, Y{ 0.f }
{
}

Mat2::Mat2(float _m00, float _m01, float _m10, float _m11) noexcept :
	X{ _m00, _m01 }, Y { _m10, _m11 }
{
}

Mat2::Mat2(float _value) noexcept :
	X{ _value }, Y{ _value }
{
}

Mat2::Mat2(Vec2 _row0, Vec2 _row1) noexcept:
	X{ _row0 }, Y{ _row1 }
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
	return &X.X;
}

const float Mat2::operator[](unsigned int _index) const
{
	if(_index > 3)
		Callback::CallErrorCallback(CLASS_NAME, "operator[]", "Index out of bound");

	return (&X.X)[_index];
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
	return Math::Equals(X.X, _other.X.X, _epsilon) &&
		Math::Equals(X.Y, _other.X.Y, _epsilon) &&
		Math::Equals(Y.X, _other.Y.X, _epsilon) &&
		Math::Equals(Y.Y, _other.Y.Y, _epsilon);
}

bool Mat2::operator==(const Mat2& _rhs) const noexcept
{
	return X.X == _rhs.X.X &&
		X.Y == _rhs.X.Y &&
		Y.X == _rhs.Y.X &&
		Y.Y == _rhs.Y.Y;
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
	return Mat2(X.X, Y.X, X.Y, Y.Y);
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
		return Mat2(Y.Y, -X.Y, -Y.X, X.X) / determinant;

	Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Matrix determinant equal 0");
	return *this;
}

float Mat2::Determinant() const noexcept
{
	return X.X * Y.Y - X.Y * Y.X;
}

//operator

Mat2 Mat2::operator+(float _scale) const noexcept
{
	return Mat2(X.X + _scale, X.Y + _scale,
		Y.X + _scale, Y.Y + _scale);
}

Mat2 Mat2::operator-(float _scale) const noexcept
{
	return Mat2(X.X - _scale, X.Y - _scale,
		Y.X - _scale, Y.Y - _scale);
}

Mat2 Mat2::operator*(float _scale) const noexcept
{
	return Mat2(X.X * _scale, X.Y * _scale,
		Y.X * _scale, Y.Y * _scale);
}

Mat2 Mat2::operator/(float _scale) const
{
	if (_scale == 0.f )
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Mat2(X.X / _scale, X.Y / _scale,
		Y.X / _scale, Y.Y / _scale);
}

Mat2& Mat2::operator+=(float _scale) noexcept
{
	X.X += _scale;
	X.Y += _scale;
	Y.X += _scale;
	Y.Y += _scale;
	return *this;
}

Mat2& Mat2::operator-=(float _scale) noexcept
{
	X.X -= _scale;
	X.Y -= _scale;
	Y.X -= _scale;
	Y.Y -= _scale;
	return *this;
}

Mat2& Mat2::operator*=(float _scale) noexcept
{
	X.X *= _scale;
	X.Y *= _scale;
	Y.X *= _scale;
	Y.Y *= _scale;
	return *this;
}

Mat2& Mat2::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/=", "Division by 0");

	X.X /= _scale;
	X.Y /= _scale;
	Y.X /= _scale;
	Y.Y /= _scale;
	return *this;
}

Vec2 Mat2::operator*(const Vec2& _vec) const noexcept
{
	return Vec2(X.X * _vec.X + X.Y * _vec.Y,
		Y.X * _vec.X + Y.Y * _vec.Y);
}

Mat2 Mat2::operator+(const Mat2& _mat) const noexcept
{
	return Mat2(X.X + _mat.X.X, X.Y + _mat.X.Y,
		Y.X + _mat.Y.X, Y.Y + _mat.Y.Y);
}

Mat2 Mat2::operator-(const Mat2& _mat) const noexcept
{
	return Mat2(X.X - _mat.X.X, X.Y - _mat.X.Y,
		Y.X - _mat.Y.X, Y.Y - _mat.Y.Y);
}

Mat2 Mat2::operator*(const Mat2& _mat) const noexcept
{
	return Mat2(X.X * _mat.X.X + X.Y * _mat.Y.X, X.X * _mat.X.Y + X.Y * _mat.Y.Y,
		Y.X * _mat.X.X + Y.Y * _mat.Y.X, Y.X * _mat.X.Y + Y.Y * _mat.Y.Y);
}

Mat2& Mat2::operator+=(const Mat2& _mat) noexcept
{
	X.X += _mat.X.X;
	X.Y += _mat.X.Y;
	Y.X += _mat.Y.X;
	Y.Y += _mat.Y.Y;
	return *this;
}

Mat2& Mat2::operator-=(const Mat2& _mat) noexcept
{
	X.X -= _mat.X.X;
	X.Y -= _mat.X.Y;
	Y.X -= _mat.Y.X;
	Y.Y -= _mat.Y.Y;
	return *this;
}

Mat2& Mat2::operator*=(const Mat2& _mat) noexcept
{
	Mat2 tmp = *this;
	X.X = tmp.X.X * _mat.X.X + tmp.X.Y * _mat.Y.X;
	X.Y = tmp.X.X * _mat.X.Y + tmp.X.Y * _mat.Y.Y;
	Y.X = tmp.Y.X * _mat.X.X + tmp.Y.Y * _mat.Y.X;
	Y.Y = tmp.Y.X * _mat.X.Y + tmp.Y.Y * _mat.Y.Y;
	return *this;
}