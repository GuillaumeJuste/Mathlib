#include <stdexcept>
#include <string>

#include <Mathlib.hpp>

using namespace Mathlib;

#define CLASS_NAME "Vec3"

//Constants

const Vec3 Vec3::Zero = Vec3();

const Vec3 Vec3::One = Vec3(1.f, 1.f, 1.f);

const Vec3 Vec3::Right = Vec3(1.f, 0.f, 0.f);

const Vec3 Vec3::Left = Vec3(-1.f, 0.f, 0.f);

const Vec3 Vec3::Up = Vec3(0.f, 1.f, 0.f);

const Vec3 Vec3::Down = Vec3(0.f, -1.f, 0.f);

const Vec3 Vec3::Forward = Vec3(0.f, 0.f, 1.f);

const Vec3 Vec3::Backward = Vec3(0.f, 0.f, -1.f);

//Constructors

Vec3::Vec3(float _x, float _y, float _z) noexcept :
	X{ _x }, Y{ _y }, Z{ _z }
{
}

Vec3::Vec3(float _xyz) noexcept :
	X{ _xyz }, Y{ _xyz }, Z{ _xyz }
{
}

Vec3::Vec3(Vec2 _vec2, float _z) noexcept :
	X{ _vec2.X }, Y{ _vec2.Y }, Z{ _z }
{
}

Vec3::Vec3(Vec4 _vec4) noexcept :
	X{ _vec4.X }, Y{ _vec4.Y }, Z{ _vec4.Z }
{
}

//Static Methods
float Vec3::DotProduct(const Vec3& _lhs, const Vec3& _rhs) noexcept
{
	return _lhs.X * _rhs.X + _lhs.Y * _rhs.Y + _lhs.Z * _rhs.Z;
}

Vec3 Vec3::CrossProduct(const Vec3& _lhs, const Vec3& _rhs) noexcept
{
	return Vec3(_lhs.Y * _rhs.Z - _lhs.Z * _rhs.Y,
				_lhs.Z * _rhs.X - _lhs.X * _rhs.Z,
				_lhs.X * _rhs.Y - _lhs.Y * _rhs.X);
}

float Vec3::Angle(const Vec3& _start, const Vec3& _end, const Vec3& _normal)
{
	float angle = Math::ACos(Vec3::DotProduct(_start, _end) / (_start.Length() * _end.Length()));

	Vec3 cross = Vec3::CrossProduct(_start, _end);

	if (Vec3::DotProduct(cross, _normal) < 0.0f)
		angle = -angle;

	return angle;
}

float Vec3::Distance(const Vec3& _start, const Vec3& _end) noexcept
{
	return (_end - _start).Length();
}

float Vec3::SqrDistance(const Vec3& _start, const Vec3& _end) noexcept
{
	return (_end - _start).SquaredLength();
}

Vec3 Vec3::Lerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
{
	float alpha = Math::Clamp(_alpha, 0.f, 1.f);

	Vec3 temp = _end - _start;
	return _start + (_end - _start) * alpha;
}

Vec3 Vec3::SLerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept
{
	float dot = DotProduct(_start, _end);

	Vec3 end = _end;

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

	Vec3 lhs = _start * (Math::Sin((1.f - _alpha) * angle) / angle_sin);
	Vec3 rhs = _end * (Math::Sin(_alpha * angle) / angle_sin);

	return lhs + rhs;
}

//Equality

bool Vec3::IsZero() const noexcept
{
	return *this == Vec3::Zero;
}

bool Vec3::Equals(const Vec3& _other, float _epsilon) const noexcept
{
	bool compare_X = Math::Equals(X, _other.X, _epsilon);
	bool compare_Y = Math::Equals(Y, _other.Y, _epsilon);
	bool compare_Z = Math::Equals(Z, _other.Z, _epsilon);

	return compare_X && compare_Y && compare_Z;
}

bool Vec3::operator==(const Vec3& _rhs) const noexcept
{
	return (X == _rhs.X && Y == _rhs.Y && Z == _rhs.Z);
}

bool Vec3::operator!=(const Vec3& _rhs) const noexcept
{
	return !(X == _rhs.X && Y == _rhs.Y && Z == _rhs.Z);
}

//Accessors
const float* Vec3::Data() const noexcept
{
	return &X;
}

//Methods
float Vec3::Length() const noexcept
{
	return Math::Sqrt(SquaredLength());
}

float Vec3::SquaredLength() const noexcept
{
	return X * X + Y * Y + Z * Z;
}

Vec3& Vec3::Normalize() noexcept
{
	float length = Length();

	if(length != 0.f)
	{ 
		X /= length;
		Y /= length;
		Z /= length;
	}
	else
	{
		Callback::CallErrorCallback(CLASS_NAME, "Normalize", "Division by O due to vector length being equal to 0");
	}
	
	return *this;
}

Vec3 Vec3::GetNormalized() const noexcept
{
	Vec3 tmp = *this;
	tmp.Normalize();

	return tmp;
}

bool  Vec3::IsNormalized() const noexcept
{
	return Math::Equals(Length(), 1.f, 0.001f);
}

Vec3 Vec3::ProjectOn(const Vec3& _other) const noexcept
{
	float otherLength = _other.SquaredLength();

	if (otherLength == 0)
		Callback::CallErrorCallback(CLASS_NAME, "ProjectOn", "Division by 0 due to _other SquaredLength being 0");

	return _other * (Vec3::DotProduct(*this, _other) / _other.SquaredLength());
}

//Operator
Vec3 Vec3::operator-() const noexcept
{
	return Vec3(-X, -Y, -Z);
}

Vec3 Vec3::operator*(float _scale) const noexcept
{
	return Vec3(X * _scale, Y * _scale, Z * _scale);
}

Vec3 Vec3::operator/(float _scale) const 
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");
	return Vec3(X / _scale, Y / _scale, Z / _scale);
}

Vec3 Vec3::operator+(const Vec3& _rhs) const noexcept
{
	return Vec3(X + _rhs.X, Y + _rhs.Y, Z + _rhs.Z);
}

Vec3 Vec3::operator-(const Vec3& _rhs) const noexcept
{
	return Vec3(X - _rhs.X, Y - _rhs.Y, Z - _rhs.Z);
}

Vec3 Vec3::operator*(const Vec3& _rhs) const noexcept
{
	return Vec3(X * _rhs.X, Y * _rhs.Y, Z * _rhs.Z);
}

Vec3 Vec3::operator/(const Vec3& _rhs) const 
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f || _rhs.Z == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	return Vec3(X / _rhs.X, Y / _rhs.Y, Z / _rhs.Z);
}

Vec3& Vec3::operator+=(const Vec3& _rhs) noexcept
{
	X += _rhs.X;
	Y += _rhs.Y;
	Z += _rhs.Z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& _rhs) noexcept
{
	X -= _rhs.X;
	Y -= _rhs.Y;
	Z -= _rhs.Z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& _rhs) noexcept
{
	X *= _rhs.X;
	Y *= _rhs.Y;
	Z *= _rhs.Z;
	return *this;
}

Vec3& Vec3::operator/=(const Vec3& _rhs) 
{
	if (_rhs.X == 0.f || _rhs.Y == 0.f || _rhs.Z == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _rhs.X;
	Y /= _rhs.Y;
	Z /= _rhs.Z;
	return *this;
}

Vec3& Vec3::operator*=(float _scale) noexcept
{
	X *= _scale;
	Y *= _scale;
	Z *= _scale;
	return *this;
}

Vec3& Vec3::operator/=(float _scale) 
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	X /= _scale;
	Y /= _scale;
	Z /= _scale;
	return *this;
}

//Debug
std::string Vec3::ToString()const noexcept
{
	std::string str = "(" + std::to_string(X) + " ; " + std::to_string(Y) + " ; " + std::to_string(Z) + ")";
	return str;
}