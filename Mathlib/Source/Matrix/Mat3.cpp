#include <Vector/Vec3.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat3.hpp>

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

Mat3::Mat3() noexcept :
	X{ 0.f }, Y{ 0.f }
{
}

Mat3::Mat3(float _m00, float _m01, float _m02,
	float _m10, float _m11, float _m12,
	float _m20, float _m21, float _m22) noexcept :
	X{ _m00, _m01, _m02 }, Y{ _m10, _m11, _m12 }, Z{ _m20, _m21, _m22 }
{
}

Mat3::Mat3(float _value) noexcept :
	X{ _value }, Y{ _value }, Z{ _value }
{
}

Mat3::Mat3(Vec3 _row0, Vec3 _row1, Vec3 _row2) noexcept :
	X{ _row0 }, Y{ _row1 }, Z{ _row2 }
{
}

//static methods

Mat3 Mat3::RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept
{
	float cos_x = Math::Cos(_x_angle);
	float sin_x = Math::Sin(_x_angle);

	float cos_y = Math::Cos(_y_angle);
	float sin_y = Math::Sin(_y_angle);

	float cos_z = Math::Cos(_z_angle);
	float sin_z = Math::Sin(_z_angle);

	Mat3 rotation_x = Mat3(1.f, 0.f, 0.f,
							0.f, cos_x, -sin_x,
							0.f, sin_x, cos_x);

	Mat3 rotation_y = Mat3(cos_y, 0.f, sin_y,
						0.f, 1.f, 0.f,
						-sin_y, 0, cos_y);

	Mat3 rotation_z = Mat3(cos_z, -sin_z, 0.f,
						sin_z, cos_z, 0.f,
						0.f, 0.f, 1.f);

	return rotation_z * rotation_y * rotation_x;
}

Mat3 Mat3::ScaleMatrix(float _scale) noexcept
{
	return Mat3(_scale, 0.f, 0.f,
				0.f, _scale, 0.f,
				0.f, 0.f, _scale);
}

//Accessors

const float* Mat3::Data() const noexcept
{
	return &X.X;
}

float& Mat3::operator[](unsigned int _index)
{
	if (_index > 8)
		Callback::CallErrorCallback(CLASS_NAME, "operator[]", "Index out of bound");

	return (&X.X)[_index];
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
	return Math::Equals(X.X, _other.X.X, _epsilon) &&
		Math::Equals(X.Y, _other.X.Y, _epsilon) &&
		Math::Equals(Y.X, _other.Y.X, _epsilon) &&
		Math::Equals(Y.Y, _other.Y.Y, _epsilon);
}

bool Mat3::operator==(const Mat3& _rhs) const noexcept
{
	return X == _rhs.X && Y == Y && Z == Z;
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
	return Mat3(X.X, Y.X, Z.X,
				X.Y, Y.Y, Z.Y,
				X.Z, Y.Z, Z.Z);
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
			Y.Y * Z.Z - Z.Y * Y.Z, X.Z * Z.Y - X.Y * Z.Z, X.Y * Y.Z - Y.Y * X.Z,
			Y.Z * Z.X - Y.X * Z.Z, X.X * Z.Z - Z.X * X.Z, X.Z * Y.X - X.X * Y.Z,
			Y.X * Z.Y - Z.X * Y.Y, X.Y * Z.X - X.X * Z.Y, X.X * Y.Y - Y.X * X.Y
		) * (1.0f / determinant);
	}
	Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Matrix determinant equal 0");
	return *this;
}

float Mat3::Determinant() const noexcept
{
	return X.X * (Y.Y * Z.Z - Y.Z * Z.Y) - X.Y * (Y.X * Z.Z - Y.Z * Z.X) + X.X * (Y.X * Z.Y - Y.Y * Z.X);
}

//operator

Mat3 Mat3::operator+(float _scale) const noexcept
{
	return Mat3(X + _scale, Y + _scale, Z + _scale);
}

Mat3 Mat3::operator-(float _scale) const noexcept
{
	return Mat3(X - _scale, Y - _scale, Z - _scale);

}

Mat3 Mat3::operator*(float _scale) const noexcept
{
	return Mat3(X * _scale, Y * _scale, Z * _scale);

}

Mat3 Mat3::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Mat3(X / _scale, Y / _scale, Z / _scale);

}

Mat3& Mat3::operator+=(float _scale) noexcept
{
	X += _scale;
	Y += _scale;
	Z += _scale;
	return *this;
}

Mat3& Mat3::operator-=(float _scale) noexcept
{
	X -= _scale;
	Y -= _scale;
	Z -= _scale;
	return *this;
}

Mat3& Mat3::operator*=(float _scale) noexcept
{
	X *= _scale;
	Y *= _scale;
	Z *= _scale;
	return *this;
}

Mat3& Mat3::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/=", "Division by 0");

	X /= _scale;
	Y /= _scale;
	Z /= _scale;
	return *this;
}

Vec3 Mat3::operator*(const Vec3& _rhs) const noexcept
{
	return Vec3(X.X * _rhs.X + X.Y * _rhs.Y + X.Z * _rhs.Z,
				Y.X * _rhs.X + Y.Y * _rhs.Y + Y.Z * _rhs.Z,
				Z.X * _rhs.X + Z.Y * _rhs.Y + Z.Z * _rhs.Z);
}

Mat3 Mat3::operator+(const Mat3& _rhs) const noexcept
{
	return Mat3(X + _rhs.X, Y + _rhs.Y, Z + _rhs.Z);
}

Mat3 Mat3::operator-(const Mat3& _rhs) const noexcept
{
	return Mat3(X - _rhs.X, Y - _rhs.Y, Z - _rhs.Z);
}

Mat3 Mat3::operator*(const Mat3& _rhs) const noexcept
{
	return Mat3(
		X.X * _rhs.X.X + X.Y * _rhs.Y.X + X.Z * _rhs.Z.X,
		X.X * _rhs.X.Y + X.Y * _rhs.Y.Y + X.Z * _rhs.Z.Y,
		X.X * _rhs.X.Z + X.Y * _rhs.Y.Z + X.Z * _rhs.Z.Z,

		Y.X* _rhs.X.X + Y.Y * _rhs.Y.X + Y.Z * _rhs.Z.X,
		Y.X* _rhs.X.Y + Y.Y * _rhs.Y.Y + Y.Z * _rhs.Z.Y,
		Y.X* _rhs.X.Z + Y.Y * _rhs.Y.Z + Y.Z * _rhs.Z.Z,

		Z.X* _rhs.X.X + Z.Y * _rhs.Y.X + Z.Z * _rhs.Z.X,
		Z.X* _rhs.X.Y + Z.Y * _rhs.Y.Y + Z.Z * _rhs.Z.Y,
		Z.X* _rhs.X.Z + Z.Y * _rhs.Y.Z + Z.Z * _rhs.Z.Z
	);
}

Mat3& Mat3::operator+=(const Mat3& _rhs) noexcept
{
	X += _rhs.X;
	Y += _rhs.Y;
	Z += _rhs.Z;
	return *this;
}

Mat3& Mat3::operator-=(const Mat3& _rhs) noexcept
{
	X -= _rhs.X;
	Y -= _rhs.Y;
	Z -= _rhs.Z;
	return *this;
}

Mat3& Mat3::operator*=(const Mat3& _rhs) noexcept
{
	Mat3 tmp = *this;
	X.X = X.X* _rhs.X.X + X.Y * _rhs.Y.X + X.Z * _rhs.Z.X;
	X.Y = X.X* _rhs.X.Y + X.Y * _rhs.Y.Y + X.Z * _rhs.Z.Y;
	X.Z = X.X* _rhs.X.Z + X.Y * _rhs.Y.Z + X.Z * _rhs.Z.Z;

	Y.X = Y.X * _rhs.X.X + Y.Y * _rhs.Y.X + Y.Z * _rhs.Z.X;
	Y.Y = Y.X * _rhs.X.Y + Y.Y * _rhs.Y.Y + Y.Z * _rhs.Z.Y;
	Y.Z = Y.X* _rhs.X.Z + Y.Y * _rhs.Y.Z + Y.Z * _rhs.Z.Z;

	Z.X = Z.X * _rhs.X.X + Z.Y * _rhs.Y.X + Z.Z * _rhs.Z.X;
	Z.Y = Z.X * _rhs.X.Y + Z.Y * _rhs.Y.Y + Z.Z * _rhs.Z.Y;
	Z.Z = Z.X* _rhs.X.Z + Z.Y * _rhs.Y.Z + Z.Z * _rhs.Z.Z;
	return *this;
}