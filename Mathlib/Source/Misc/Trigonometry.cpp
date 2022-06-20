#include <cmath>

#include <Misc/Trigonometry.hpp>

namespace Mathlib
{
	namespace Math
	{
		float Cos(float _value) noexcept
		{
			return cosf(_value);
		}

		float ACos(float _value) noexcept
		{
			return acosf(_value);
		}

		float Sin(float _value) noexcept
		{
			return sinf(_value);
		}

		float ASin(float _value) noexcept
		{
			return asinf(_value);
		}

		float Tan(float _value) noexcept
		{
			return tanf(_value);
		}

		float ATan(float _value) noexcept
		{
			return atanf(_value);
		}

		float ATan2(float _x, float _y) noexcept
		{
			return atan2(_x, _y);
		}
	}
}