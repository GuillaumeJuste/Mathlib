#include <cmath>

#include <Misc/Trigonometry.hpp>

namespace Mathlib
{
	namespace Math
	{
		float Cos(float _value) noexcept
		{
			return std::cosf(_value);
		}

		float ACos(float _value) noexcept
		{
			return std::acosf(_value);
		}

		float Sin(float _value) noexcept
		{
			return std::sinf(_value);
		}

		float ASin(float _value) noexcept
		{
			return std::asinf(_value);
		}

		float Tan(float _value) noexcept
		{
			return std::tanf(_value);
		}

		float ATan(float _value) noexcept
		{
			return std::atanf(_value);
		}
	}
}