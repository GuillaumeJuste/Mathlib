#include <stdexcept>
#include <string>

#include <Vec2.hpp>
#include <Vec3.hpp>
#include <Vec4.hpp>
#include <Math.hpp>
#include <Callback.hpp>
#include <Trigonometry.hpp>

using namespace Mathlib;

#define CLASS_NAME "Vec4"

//Constants

const Vec4 Vec4::Zero = Vec4();

const Vec4 Vec4::One = Vec4(1.f, 1.f, 1.f, 0.f);

const Vec4 Vec4::Right = Vec4(1.f, 0.f, 0.f, 0.f);

const Vec4 Vec4::Left = Vec4(-1.f, 0.f, 0.f, 0.f);

const Vec4 Vec4::Up = Vec4(0.f, 1.f, 0.f, 0.f);

const Vec4 Vec4::Down = Vec4(0.f, -1.f, 0.f, 0.f);

const Vec4 Vec4::Forward = Vec4(0.f, 0.f, 1.f, 0.f);

const Vec4 Vec4::Backward = Vec4(0.f, 0.f, -1.f, 0.f);

//Constructors

Vec4::Vec4(float _x, float _y, float _z, float _w) noexcept :
	X{ _x }, Y{ _y }, Z{ _z }, W{_w}
{
}

Vec4::Vec4(float _xyzw) noexcept :
	X{ _xyzw }, Y{ _xyzw }, Z{ _xyzw }, W{ _xyzw}
{
}

Vec4::Vec4(Vec2 _vec2, float _z, float _w) noexcept :
	X{ _vec2.X }, Y{ _vec2.Y }, Z{ _z }, W{ _w}
{
}

Vec4::Vec4(Vec3 _vec3, float _w) noexcept :
	X{ _vec3.X }, Y{ _vec3.Y }, Z{ _vec3.Z }, W{ _w }
{
}

//Static Methods
float Vec4::Distance(const Vec4& _start, const Vec4& _end) noexcept
{
	return (_end - _start).Length();
}

float Vec4::SqrDistance(const Vec4& _start, const Vec4& _end) noexcept
{
	return (_end - _start).SquaredLength();
}

Vec4 Vec4::Lerp(const Vec4& _start, const Vec4& _end, float _alpha) noexcept
{
	float alpha = Math::Clamp(_alpha, 0.f, 1.f);

	Vec4 temp = _end - _start;
	return _start + (_end - _start) * alpha;
}


//Equality
bool Vec4::IsZero() const noexcept
{
	return *this == Vec4::Zero;
}

bool Vec4::Equals(const Vec4& _other, float _epsilon) const noexcept
{
	bool compare_X = Math::Equals(X, _other.X, _epsilon);
	bool compare_Y = Math::Equals(Y, _other.Y, _epsilon);
	bool compare_Z = Math::Equals(Z, _other.Z, _epsilon);
	bool compare_W = Math::Equals(W, _other.W, _epsilon);

	return compare_X && compare_Y && compare_Z && compare_W;
}

bool Vec4::operator==(const Vec4& _rhs) const noexcept
{
	return (X == _rhs.X && Y == _rhs.Y && Z == _rhs.Z && W == _rhs.W);
}

bool Vec4::operator!=(const Vec4& _rhs) const noexcept
{
	return !(X == _rhs.X && Y == _rhs.Y && Z == _rhs.Z && W == _rhs.W);
}

//Accessors
const float* Vec4::Data() const noexcept
{
	return &X;
}

//Methods
float Vec4::Length() const noexcept
{
	return Math::Sqrt(SquaredLength());
}

float Vec4::SquaredLength() const noexcept
{
	return X * X + Y * Y + Z * Z + W * W;
}

Vec4& Vec4::Normalize() noexcept
{
	float length = Length();

	if (length != 0.f)
	{
		X /= length;
		Y /= length;
		Z /= length;
		W /= length;
	}
	else
	{
		Callback::CallErrorCallback(CLASS_NAME, "Normalize", "Division by O due to vector length being equal to 0");
	}

	return *this;
}

Vec4 Vec4::GetNormalized() const noexcept
{
	Vec4 tmp = *this;
	tmp.Normalize();

	return tmp;
}

bool  Vec4::IsNormalized() const noexcept
{
	return Math::Equals(Length(), 1.f, 0.001f);
}

//Operator
Vec4 Vec4::operator-() const noexcept
{
	return Vec4(-X, -Y, -Z, -W);
}

Vec4 Vec4::operator*(float _scale) const noexcept
{
	return Vec4(X * _scale, Y * _scale, Z * _scale, W * _scale);
}

Vec4 Vec4::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");
	return Vec4(X / _scale, Y / _scale, Z / _scale, W / _scale);
}

Vec4 Vec4::operator+(const Vec4& _rhs) const noexcept
{
	return Vec4(X + _rhs.X, Y + _rhs.Y, Z + _rhs.Z, W + _rhs.W);
}

Vec4 Vec4::operator-(const Vec4& _rhs) const noexcept
{
	return Vec4(X - _rhs.X, Y - _rhs.Y, Z - _rhs.Z, W - _rhs.W);
}

Vec4 Vec4::operator*(const Vec4& _rhs) const noexcept
{
	return Vec4(X * _rhs.X, Y * _rhs.Y, Z * _rhs.Z, W * _rhs.W);
}

Vec4 Vec4::operator/(const Vec4& _rhs) const
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f || _rhs.Z == 0.f || _rhs.W == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Vec4(X / _rhs.X, Y / _rhs.Y, Z / _rhs.Z, W / _rhs.W);
}

Vec4& Vec4::operator+=(const Vec4& _rhs) noexcept
{
	X += _rhs.X;
	Y += _rhs.Y;
	Z += _rhs.Z;
	W += _rhs.W;
	return *this;
}

Vec4& Vec4::operator-=(const Vec4& _rhs) noexcept
{
	X -= _rhs.X;
	Y -= _rhs.Y;
	Z -= _rhs.Z;
	W -= _rhs.W;
	return *this;
}

Vec4& Vec4::operator*=(const Vec4& _rhs) noexcept
{
	X *= _rhs.X;
	Y *= _rhs.Y;
	Z *= _rhs.Z;
	W *= _rhs.W;
	return *this;
}

Vec4& Vec4::operator/=(const Vec4& _rhs)
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f || _rhs.Z == 0.f || _rhs.W == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _rhs.X;
	Y /= _rhs.Y;
	Z /= _rhs.Z;
	W /= _rhs.W;
	return *this;
}

Vec4& Vec4::operator*=(float _scale) noexcept
{
	X *= _scale;
	Y *= _scale;
	Z *= _scale;
	W *= _scale;
	return *this;
}

Vec4& Vec4::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _scale;
	Y /= _scale;
	Z /= _scale;
	W /= _scale;
	return *this;
}

//Debug
std::string Vec4::ToString()const noexcept
{
	std::string str = "(" + std::to_string(X) + " ; " + std::to_string(Y) + " ; " + std::to_string(Z) + std::to_string(W) + ")";
	return str;
}