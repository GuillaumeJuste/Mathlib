#include <Space/Quaternion.hpp>
#include <Space/Vec3.hpp>
#include <Matrix/Mat4.hpp>

#include <Misc/Math.hpp>
#include <Misc/Constants.hpp>
#include <Misc/Trigonometry.hpp>
#include <Misc/Callback.hpp>

using namespace Mathlib;

#define CLASS_NAME "Quat"

//Constants

const Quat Quat::Zero = Quat();
const Quat Quat::Identity = Quat(1.f, 0.f, 0.f, 0.f);

//Constructors

Quat::Quat(float _w, float _x, float _y, float _z) noexcept :
	W{ _w }, X{ _x }, Y{ _y }, Z{ _z }
{
}

Quat::Quat(float _angle, Vec3 _axis) noexcept 
{
	float half_angle_rad = _angle * Math::DegToRad / 2.f;
	W = Math::Cos(half_angle_rad / 2.f);
	
	float angle_sin = Math::Sin(half_angle_rad);

	X = _axis.X * angle_sin;
	Y = _axis.Y * angle_sin;
	Z = _axis.Z * angle_sin;

	Normalize();
}

//Length & Normalization

float Quat::Length() const noexcept
{
	return Math::Sqrt(SquaredLength());
}

float Quat::SquaredLength() const noexcept
{
	return X * X + Y * Y + Z * Z + W * W;
}

Quat& Quat::Normalize() noexcept
{
	float length = Length();

	W /= length;
	X /= length;
	Y /= length;
	Z /= length;

	return *this;
}

Quat Quat::GetNormalized() const noexcept
{
	float length = Length();

	return Quat( W / length,
		X / length,
		Y / length,
		Z / length
	);
}

bool  Quat::IsNormalized() const noexcept
{
	return Math::Equals(Length(), 1.f);
}

//Euler

Quat Quat::FromEuler(const Vec3& _angles) noexcept
{
	float cos_half_X = Math::Cos(_angles.X * 0.5f);
	float sin_half_X = Math::Sin(_angles.X * 0.5f);
	float cos_half_Y = Math::Cos(_angles.Y * 0.5f);
	float sin_half_Y = Math::Sin(_angles.Y * 0.5f);
	float cos_half_Z = Math::Cos(_angles.Z * 0.5f);
	float sin_half_Z = Math::Sin(_angles.Z * 0.5f);

	Quat result = Quat();
	result.W = cos_half_Z * cos_half_Y * cos_half_X + sin_half_Z * sin_half_Y * sin_half_X;
	result.X = sin_half_Z * cos_half_Y * cos_half_X - cos_half_Z * sin_half_Y * sin_half_X;
	result.Y = cos_half_Z * sin_half_Y * cos_half_X + cos_half_Z * cos_half_Y * sin_half_X;
	result.Z = cos_half_Z * cos_half_Y * sin_half_X - cos_half_Z * sin_half_Y * cos_half_X;

	return result;
}

Vec3 Quat::Euler() const noexcept
{
	Vec3 result = Vec3();

	float sinX = 2.f * (W * X + Y * Z);
	float cosX = 1.f - 2.f * (X * X + Y * Y);

	result.X = Math::ATan2(sinX, cosX);

	float sinY = 2.f * (W * Y - Z * X);
	if (Math::Abs(sinY) >= 1)
		result.Y = Math::Copysign(Math::Pi / 2.f, sinY);
	else
		result.Y = Math::ASin(sinY);

	float sinZ = 2 * (W * Z + X * Y);
	float cosZ = 1 - 2 * (Y * Y + Z * Z);
	result.Z = Math::ATan2(sinZ, cosZ);

	return result;
}

//Invert

Quat& Quat::Inverse() noexcept
{
	float squared_length = SquaredLength();

	if (squared_length == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "Inverse", "Division by O due to vector length being equal to 0");

	if (Math::Equals(1.f, squared_length))
	{
		X = -X;
		Y = -Y;
		Z = -Z;
	}
	else
	{
		W *= squared_length;
		X *= -squared_length;
		Y *= -squared_length;
		Z *= -squared_length;
	}

	return *this;
}

Quat Quat::GetInverse() const noexcept
{
	float squared_length = SquaredLength();

	Quat conjugate = Quat(W, -X, -Y, -Z);

	if(squared_length == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "GetInverse", "Division by O due to vector length being equal to 0");

	if (Math::Equals(1.f, squared_length))
		return conjugate;
	else
		return conjugate / squared_length;
}

//Conjugate

Quat Quat::GetConjugate() const noexcept
{
	return Quat(W, -X, -Y, -Z);
}

//Angle/Axis

float Quat::GetAngle() const noexcept
{
	return Math::ACos(W) * 2.f;
}

Vec3 Quat::GetAxis() const noexcept
{
	return Vec3(X, Y, Z) / Math::Sqrt(1.f - (W * W));
}

// Rotate

Quat Quat::Rotate(Quat _quat) const noexcept
{
	if (!IsNormalized() || !_quat.IsNormalized())
		Callback::CallErrorCallback(CLASS_NAME, "Rotate", "Quat should be normalized");

	float result_W = W * _quat.W - X * _quat.X - Y * _quat.Y - Z * _quat.Z;
	float result_X = W * _quat.X + X * _quat.W + Y * _quat.Z - Z * _quat.Y ;
	float result_Y = W * _quat.Y - X * _quat.Z + Y * _quat.W + Z * _quat.X;
	float result_Z = W * _quat.Z + X * _quat.Y - Y * _quat.X + Z * _quat.W;

	return Quat(result_W, result_X, result_Y, result_Z);
}

Vec3 Quat::Rotate(Vec3 _vec) const noexcept
{
	if (!IsNormalized())
		Callback::CallErrorCallback(CLASS_NAME, "Rotate", "Quat should be normalized");

	Vec3 const QuatVector = Vec3(X, Y, Z);
	Vec3 const uv(Vec3::CrossProduct(QuatVector, _vec));
	Vec3 const uuv(Vec3::CrossProduct(QuatVector, uv));

	return _vec + ((uv * W) + uuv) * 2.f;
}

Vec3 Quat::GetRightVector() const noexcept
{
	return  Rotate(Vec3::Right);
}

Vec3 Quat::GetUpVector() const noexcept
{
	return  Rotate(Vec3::Up);
}

Vec3 Quat::GetForwardVector() const noexcept
{
	return  Rotate(Vec3::Forward);
}

//Dot

float Quat::DotProduct(const Quat& _lhs, const Quat& _rhs) noexcept
{
	return _lhs.W * _rhs.W + _lhs.X * _rhs.X + _lhs.Y * _rhs.Y + _lhs.Z * _rhs.Z;
}

//Lerp / Slerp

Quat Quat::Lerp(const Quat& _start, const Quat& _end, float _alpha)
{
	float alpha = Math::Clamp(_alpha, 0.f, 1.f);

	Quat temp = _end - _start;
	return _start + (_end - _start) * alpha;
}

Quat Quat::SLerp(const Quat& _start, const Quat& _end, float _alpha) noexcept
{
	float dot = DotProduct(_start, _end);

	Quat end = _end;

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

	Quat lhs = _start * (Math::Sin((1.f - _alpha) * angle) / angle_sin);
	Quat rhs = _end * (Math::Sin(_alpha * angle) / angle_sin);

	return lhs + rhs;
}

//Equality

bool Quat::IsZero() const noexcept
{
	return *this == Quat::Zero;
}

bool Quat::IsIdentity() const noexcept
{
	return *this == Quat::Identity;
}

bool Quat::Equals(const Quat& _other, float _epsilon) const noexcept
{
	bool compare_W = Math::Equals(W, _other.W, _epsilon);
	bool compare_X = Math::Equals(X, _other.X, _epsilon);
	bool compare_Y = Math::Equals(Y, _other.Y, _epsilon);
	bool compare_Z = Math::Equals(Z, _other.Z, _epsilon);

	return compare_W && compare_Y && compare_Z && compare_X;
}

bool Quat::operator==(const Quat& _rhs) const noexcept
{
	return (W == _rhs.W &&
		X == _rhs.X && 
		Y == _rhs.Y &&
		Z == _rhs.Z);
}

bool Quat::operator!=(const Quat& _rhs) const noexcept
{
	return !(W == _rhs.W &&
		X == _rhs.X &&
		Y == _rhs.Y && 
		Z == _rhs.Z);
}

//Accessors
const float* Quat::Data() const noexcept
{
	return &W;
}

//Operator
Quat Quat::operator-() const noexcept
{
	return Quat(-W, -X, -Y, -Z);
}

Quat Quat::operator+(const Quat& _rhs) const noexcept
{
	return Quat(W + _rhs.W,
		X + _rhs.X,
		Y + _rhs.Y,
		Z + _rhs.Z);
}

Quat Quat::operator-(const Quat& _rhs) const noexcept
{
	return Quat(W - _rhs.W,
		X - _rhs.X,
		Y - _rhs.Y,
		Z - _rhs.Z);
}

Quat Quat::operator*(const Quat& _rhs) const noexcept
{
	return Rotate(_rhs);
}

Quat Quat::operator/(const Quat& _rhs) const noexcept
{
	return GetInverse().Rotate(_rhs);
}

Quat Quat::operator+=(const Quat& _rhs) noexcept
{
	W += _rhs.W;
	X += _rhs.X;
	Y += _rhs.Y;
	Z += _rhs.Z;

	return *this;
}

Quat Quat::operator-=(const Quat& _rhs) noexcept
{
	W -= _rhs.W;
	X -= _rhs.X;
	Y -= _rhs.Y;
	Z -= _rhs.Z;

	return *this;
}

Quat Quat::operator*=(const Quat& _rhs) noexcept
{
	Quat rotate_result = Rotate(_rhs);

	W = rotate_result.W;
	X = rotate_result.X;
	Y = rotate_result.Y;
	Z = rotate_result.Z;

	return *this;
}

Quat Quat::operator/=(const Quat& _rhs) noexcept
{
	Quat rotate_result = GetInverse().Rotate(_rhs);

	W = rotate_result.W;
	X = rotate_result.X;
	Y = rotate_result.Y;
	Z = rotate_result.Z;

	return *this;
}

Vec3 Quat::operator*(const Vec3& _rhs) const noexcept
{
	return Rotate(_rhs);
}

Vec3 Quat::operator/(const Vec3& _rhs) const noexcept
{
	return GetInverse().Rotate(_rhs);
}

Quat Quat::operator*(float _scale) const noexcept
{
	return Quat(W * _scale, X * _scale, Y * _scale, Z * _scale);
}

Quat Quat::operator/(float _scale) const
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");
	return Quat(W / _scale, X / _scale, Y / _scale, Z / _scale);
}

Quat& Quat::operator*=(float _scale) noexcept
{
	W *= _scale;
	X *= _scale;
	Y *= _scale;
	Z *= _scale;
	return *this;
}

Quat& Quat::operator/=(float _scale)
{
	if (_scale == 0.f)
		Callback::CallErrorCallback(CLASS_NAME, "operator/", "Division by 0");

	W /= _scale;
	X /= _scale;
	Y /= _scale;
	Z /= _scale;
	return *this;
}