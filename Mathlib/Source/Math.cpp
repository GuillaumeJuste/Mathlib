#include <Math.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <Callback.hpp>

#define CLASS_NAME "Math"

namespace Mathlib
{
	namespace Math
	{
		int Abs(int _value) noexcept
		{
			return _value < 0 ? -_value : _value;
		}
		float Abs(float _value) noexcept
		{
			return _value < 0.f ? -_value : _value;
		}

		int Sign(int _value) noexcept
		{
			return _value < 0 ? -1 : 1;

		}
		int Sign(float _value) noexcept
		{
			return _value < 0.f ? -1 : 1;
		}

		int Min(int _left, int _right) noexcept
		{
			return std::min(_left, _right);
		}
		float Min(float _left, float _right) noexcept
		{
			return std::min(_left, _right);
		}

		int Max(int _left, int _right) noexcept
		{
			return std::max(_left, _right);
		}
		float Max(float _left, float _right)noexcept
		{
			return std::max(_left, _right);
		}

		int Clamp(int _value, int _min, int _max) noexcept
		{
			return Max(Min(_value, _max), _min);
		}
		float Clamp(float _value, float _min, float _max) noexcept
		{
			return Max(Min(_value, _max), _min);
		}

		int Pow(int _value, int _exp) noexcept
		{
			return int(std::pow(_value, _exp));
		}
		float Pow(float _value, float _exp) noexcept
		{
			return std::powf(_value, _exp);
		}

		float Sqrt(int _value) noexcept
		{
			if (_value < 0)
				Callback::CallErrorCallback(CLASS_NAME, "Sqrt", "Square root of negative number");
			return float(std::sqrt(_value));
		}
		float Sqrt(float _value) noexcept
		{
			if (_value < 0.f)
				Callback::CallErrorCallback(CLASS_NAME, "Sqrt", "Square root of negative number");
			return std::sqrt(_value);
		}

		bool Equals(float _lhs, float _rhs, float _epsilon) noexcept
		{
			return std::abs(_lhs - _rhs) <= _epsilon;
		}

		bool Equals0(float _value, float _epsilon) noexcept
		{
			return std::abs(0 - _value) <= _epsilon;
		}

		float Lerp(float _start, float _end, float _alpha) noexcept
		{
			return (1.0f - _alpha) * _start + _alpha * _end;
		}

		void InitializeRandom() noexcept
		{
			std::srand(unsigned int(std::time(nullptr)));
		}

		int Random() noexcept
		{
			return rand();
		}

		int Random(int _min, int _max) noexcept
		{
			return rand() % (_max - _min) + _min;
		}
	}
}