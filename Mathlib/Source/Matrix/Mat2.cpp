#include <Vector/Vec2.hpp>
#include <Misc/Math.hpp>
#include <Misc/Callback.hpp>
#include <Misc/Trigonometry.hpp>

#include <Matrix/Mat2.hpp>

using namespace Mathlib;

//Constants

const Mat2 Mat2::Zero = Mat2(0.f, 0.f, 
							0.f, 0.f);

const Mat2 Mat2::Identity = Mat2(1.f, 0.f, 
								0.f, 1.f);


//Constructors

Mat2::Mat2() noexcept :
	m00 { 0.f }, m01{ 0.f }, m10{ 0.f }, m11{ 0.f }
{
}

Mat2::Mat2(float _m00, float _m01, float _m10, float _m11) noexcept :
	m00{ _m00 }, m01{ _m01 }, m10{ _m10 }, m11{ _m11 }
{
}

Mat2::Mat2(float _scale) noexcept :
	m00{ _scale }, m01{ _scale }, m10{ _scale }, m11{ _scale }
{
}

Mat2::Mat2(Vec2 _row0, Vec2 _row1) noexcept:
	m00 { _row0.X }, m01{ _row0.Y }, m10{ _row1.X }, m11{ _row1.Y }
{
}

//Accessors

const float* Mat2::Data() const noexcept
{
	return &m00;
}

//Equality

bool Mat2::IsZero() const noexcept
{
	return *this == Mat2::Zero;
}

bool Mat2::Equals(const Mat2& _other, float _epsilon) const noexcept
{
	return Math::Equals(m00, _other.m00, _epsilon) &&
		Math::Equals(m01, _other.m01, _epsilon) &&
		Math::Equals(m10, _other.m10, _epsilon) &&
		Math::Equals(m11, _other.m11, _epsilon);
}

bool Mat2::operator==(const Mat2& _rhs) const noexcept
{
	return m00 == _rhs.m00 &&
		m01 == _rhs.m01 &&
		m10 == _rhs.m10 &&
		m11 == _rhs.m11;
}

bool Mat2::operator!=(const Mat2& _rhs) const noexcept
{
	return !(*this == _rhs);
}