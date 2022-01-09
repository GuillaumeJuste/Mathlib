#include <stdexcept>
#include <string>

#include <Mathlib.hpp>

using namespace Mathlib;

#define CLASS_NAME "Vec2"

//Constants

const Vec2 Vec2::Zero = Vec2();

const Vec2 Vec2::One = Vec2(1.f, 1.f);

const Vec2 Vec2::Right = Vec2(1.f, 0.f);

const Vec2 Vec2::Left = Vec2(-1.f, 0.f);

const Vec2 Vec2::Up = Vec2(0.f, 1.f);

const Vec2 Vec2::Down = Vec2(0.f, -1.f);

//Constructors

Vec2::Vec2(float _x, float _y) noexcept :
	X{ _x }, Y{ _y }
{
}

Vec2::Vec2(float _xy) noexcept :
	X{ _xy }, Y{ _xy }
{
}

Vec2::Vec2(Vec3 _vec3) noexcept :
	X{ _vec3.X }, Y{ _vec3.Y }
{
}

Vec2::Vec2(Vec4 _vec4) noexcept :
	X{ _vec4.X }, Y{ _vec4.Y }
{
}

//Static Methods
float Vec2::DotProduct(const Vec2& _lhs, const Vec2& _rhs) noexcept
{
	return _lhs.X * _rhs.X + _lhs.Y * _rhs.Y;
}

float Vec2::CrossProduct(const Vec2& _lhs, const Vec2& _rhs) noexcept
{
	return _lhs.X * _rhs.Y - _lhs.Y * _rhs.X;
}

float Vec2::Angle(const Vec2& _start, const Vec2& _end)
{
	float angle = Math::ACos(Vec2::DotProduct(_start, _end) / (_start.Length() * _end.Length()));

	return angle * Math::Sign(CrossProduct(_start, _end));
}

float Vec2::Distance(const Vec2& _start, const Vec2& _end) noexcept
{
	return (_end - _start).Length();
}

float Vec2::SqrDistance(const Vec2& _start, const Vec2& _end) noexcept
{
	return (_end - _start).SquaredLength();
}

Vec2 Vec2::Lerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept
{
	float alpha = Math::Clamp(_alpha, 0.f, 1.f);
	return _start + (_end - _start) * alpha;
}

Vec2 Vec2::SLerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept
{
	float dot = DotProduct(_start, _end);

	Vec2 end = _end;

	// Ensure shortest path between _start and _end.
	if (dot < 0.0f)
	{
		end = -end;
		dot = -dot;
	}

	// Current angle.
	float angle = Math::ACos(dot);

	float angle_sin = Math::Sin(angle);

	if (angle_sin == 0.f)
	{
		Callback::CallErrorCallback(CLASS_NAME, "SLerp", "Division by 0 due to angle sine being equal to 0");
	}

	Vec2 lhs = _start * (Math::Sin((1.f - _alpha) * angle) / angle_sin);
	Vec2 rhs = _end * (Math::Sin(_alpha * angle) / angle_sin);

	return lhs + rhs;
}

//Equality

bool Vec2::IsZero() const noexcept
{
	return *this == Vec2::Zero;
}

bool Vec2::Equals(const Vec2& _other, float _epsilon) const noexcept
{
	bool compare_X = Math::Equals(X, _other.X, _epsilon);
	bool compare_Y = Math::Equals(Y, _other.Y, _epsilon);

	return compare_X && compare_Y;
}

bool Vec2::operator==(const Vec2& _rhs) const noexcept
{
	return (X == _rhs.X && Y == _rhs.Y);
}

bool Vec2::operator!=(const Vec2& _rhs) const noexcept
{
	return !(X == _rhs.X && Y == _rhs.Y);
}

//Accessors
const float* Vec2::Data() const noexcept
{
	return &X;
}

//Methods
float Vec2::Length() const noexcept
{
	return Math::Sqrt(SquaredLength());
}

float Vec2::SquaredLength() const noexcept
{
	return X * X + Y * Y;
}

Vec2& Vec2::Normalize() noexcept
{
	float length = Length();

	if (length != 0.f)
	{
		X /= length;
		Y /= length;
	}
	else
	{
		Callback::CallErrorCallback(CLASS_NAME, "Normalize", "Division by O due to vector length being equal to 0");
	}

	return *this;
}

Vec2 Vec2::GetNormalized() const noexcept
{
	Vec2 tmp = *this;
	tmp.Normalize();

	return tmp;
}

bool  Vec2::IsNormalized() const noexcept
{
	return Math::Equals(Length(), 1.f, 0.001f);
}

Vec2 Vec2::ProjectOn(const Vec2& _other) const noexcept
{
	float otherLength = _other.SquaredLength();

	if (otherLength == 0)
		Callback::CallErrorCallback(CLASS_NAME, "ProjectOn", "Division by 0 due to _other SquaredLength being 0");

	return _other * (Vec2::DotProduct(*this, _other) / _other.SquaredLength());
}

//Operator
Vec2 Vec2::operator-() const noexcept
{
	return Vec2(-X, -Y);
}

Vec2 Vec2::operator*(float _scale) const noexcept
{
	return Vec2(X * _scale, Y * _scale);
}

Vec2 Vec2::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");
	return Vec2(X / _scale, Y / _scale);
}

Vec2 Vec2::operator+(const Vec2& _rhs) const noexcept
{
	return Vec2(X + _rhs.X, Y + _rhs.Y);
}

Vec2 Vec2::operator-(const Vec2& _rhs) const noexcept
{
	return Vec2(X - _rhs.X, Y - _rhs.Y);
}

Vec2 Vec2::operator*(const Vec2& _rhs) const noexcept
{
	return Vec2(X * _rhs.X, Y * _rhs.Y);
}

Vec2 Vec2::operator/(const Vec2& _rhs) const
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Vec2(X / _rhs.X, Y / _rhs.Y);
}

Vec2& Vec2::operator+=(const Vec2& _rhs) noexcept
{
	X += _rhs.X;
	Y += _rhs.Y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& _rhs) noexcept
{
	X -= _rhs.X;
	Y -= _rhs.Y;
	return *this;
}

Vec2& Vec2::operator*=(const Vec2& _rhs) noexcept
{
	X *= _rhs.X;
	Y *= _rhs.Y;
	return *this;
}

Vec2& Vec2::operator/=(const Vec2& _rhs)
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f )
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _rhs.X;
	Y /= _rhs.Y;
	return *this;
}

Vec2& Vec2::operator*=(float _scale) noexcept
{
	X *= _scale;
	Y *= _scale;
	return *this;
}

Vec2& Vec2::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _scale;
	Y /= _scale;
	return *this;
}

//Debug
std::string Vec2::ToString()const noexcept
{
	std::string str = "(" + std::to_string(X) + " ; " + std::to_string(Y) + ")";
	return str;
}