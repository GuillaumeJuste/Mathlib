#include <Math.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define CLASS_NAME "Math"

namespace Mathlib
{
	errorCallbackFunction Math::errorCallback = NULL;
	const double Math::Pi = 3.1415926535897932384;
	const double Math::DegToRad = Pi / 180.0;
	const double Math::RadToDeg = 180.0 / Pi;
	const float Math::Epsilon = std::numeric_limits<float>::epsilon();
	
	int Math::Abs(int _value) noexcept
	{
		return _value < 0 ? -_value : _value;
	}
	float Math::Abs(float _value) noexcept
	{
		return _value < 0.f ? -_value : _value;
	}
	
	int Math::Sign(int _value) noexcept
	{
		return _value < 0 ? -1 : 1;

	}
	int Math::Sign(float _value) noexcept
	{
		return _value < 0.f ? -1 : 1;
	}
	
	int Math::Min(int _left, int _right) noexcept
	{
		return std::min(_left, _right);
	}
	float Math::Min(float _left, float _right) noexcept
	{
		return std::min(_left, _right);
	}
	
	int Math::Max(int _left, int _right) noexcept
	{
		return std::max(_left, _right);
	}
	float Math::Max(float _left, float _right)noexcept
	{
		return std::max(_left, _right);
	}
	
	int Math::Clamp(int _value, int _min, int _max) noexcept
	{
		return Max(Min(_value, _max), _min);
	}
	float Math::Clamp(float _value, float _min, float _max) noexcept
	{
		return Max(Min(_value, _max), _min);
	}
	
	int Math::Pow(int _value, int _exp) noexcept
	{
		return int(std::pow(_value, _exp));
	}
	float Math::Pow(float _value, float _exp) noexcept
	{
		return std::powf(_value, _exp);
	}
	
	float Math::Sqrt(int _value) noexcept
	{
		if(_value < 0)
			Math::CallErrorCallback(CLASS_NAME, "Sqrt", "Square root of negative number");
		return int(std::sqrt(_value));
	}
	float Math::Sqrt(float _value) noexcept
	{
		if (_value < 0.f)
			Math::CallErrorCallback(CLASS_NAME, "Sqrt", "Square root of negative number");
		return std::sqrt(_value);
	}
	
	float Math::Cos(float _value) noexcept
	{
		return std::cosf(_value);
	}
	
	float Math::ACos(float _value) noexcept
	{
		return std::acosf(_value);
	}
	
	float Math::Sin(float _value) noexcept
	{
		return std::sinf(_value);
	}
	
	float Math::ASin(float _value) noexcept
	{
		return std::asinf(_value);
	}
	
	float Math::Tan(float _value) noexcept
	{
		return std::tanf(_value);
	}
	
	float Math::ATan(float _value) noexcept
	{
		return std::atanf(_value);
	}
	
	bool Math::Equals(float _lhs, float _rhs, float _epsilon) noexcept
	{
		return std::abs(_lhs - _rhs) <= _epsilon;
	}

	bool Math::Equals0(float _value, float _epsilon) noexcept
	{
		return std::abs(0 - _value) <= _epsilon;
	}
	
	float Math::Lerp(float _start, float _end, float _alpha) noexcept
	{
		return (1.0f - _alpha) * _start + _alpha * _end;
	}
	
	void Math::InitializeRandom() noexcept
	{
		std::srand(std::time(nullptr));
	}

	int Math::Random() noexcept
	{
		return rand();
	}
	
	int Math::Random(int _min, int _max) noexcept
	{
		return rand() % (_max - _min) + _min;
	}

	void Math::SetErrorCallback(errorCallbackFunction _errorCallback)
	{
		errorCallback = _errorCallback;
	}

	void Math::CallErrorCallback(const char* _class, const char* _function, const char* _errorMessage)
	{
		if (errorCallback != NULL)
			errorCallback(_class, _function, _errorMessage);
	}
}