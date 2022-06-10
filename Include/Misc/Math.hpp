#pragma once

#ifndef MATHLIB_MATH
#define MATHLIB_MATH

#include <Misc/Includes.hpp>
#include<Misc/Constants.hpp>

namespace Mathlib
{
	namespace Math
	{
		/**
		*	\brief Compute absolute value.
		*
		* 	\param[in] _value value to compute absolute value with.
		*
		*	\return _value's absolute value.
		*/
		MATHLIBRARY_API int Abs(int _value) noexcept;

		/**
		*	\brief Compute absolute value.
		*
		* 	\param[in] _value value to compute absolute value with.
		*
		*	\return _value's absolute value.
		*/
		MATHLIBRARY_API float Abs(float _value) noexcept;

		/**
		*	\brief get _value sign.
		*
		* 	\param[in] _value value to get the sign from.
		*
		*	\return _value's sign, 1 if positive, -1 if negative.
		*/
		MATHLIBRARY_API int Sign(int _value) noexcept;

		/**
		*	\brief get _value sign.
		*
		* 	\param[in] _value value to get the sign from.
		*
		*	\return _value's sign, 1 if positive, -1 if negative.
		*/
		MATHLIBRARY_API int Sign(float _value) noexcept;

		/**
		*	\brief get minimum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return lower value between _left and _right.
		*/
		MATHLIBRARY_API int Min(int _left, int _right) noexcept;

		/**
		*	\brief get minimum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return lower value between _left and _right.
		*/
		MATHLIBRARY_API float Min(float _left, float _right) noexcept;

		/**
		*	\brief get maximum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return higher value between _left and _right.
		*/
		MATHLIBRARY_API int Max(int _left, int _right) noexcept;

		/**
		*	\brief get maximum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return higher value between _left and _right.
		*/
		MATHLIBRARY_API float Max(float _left, float _right) noexcept;

		/**
		*	\brief Clamp _value between min and max value.
		*
		* 	\param[in] _value value to clamp.
		* 	\param[in] _min minimum value for the clamping.
		* 	\param[in] _max maximum value for the clamping.
		*
		*	\return _value clamped betwenn _min and _max.
		*/
		MATHLIBRARY_API int Clamp(int _value, int _min, int _max) noexcept;

		/**
		*	\brief Clamp _value between min and max value.
		*
		* 	\param[in] _value value to clamp.
		* 	\param[in] _min minimum value for the clamping.
		* 	\param[in] _max maximum value for the clamping.
		*
		*	\return _value clamped betwenn _min and _max.
		*/
		MATHLIBRARY_API float Clamp(float _value, float _min, float _max) noexcept;

		/**
		*	\brief Compute the power of the value with exponent.
		*
		* 	\param[in] _value value to compute power from.
		* 	\param[in] _exp exponent value.
		*
		*	\return base raised to the power exponent.
		*/
		MATHLIBRARY_API int Pow(int _value, int _exp) noexcept;

		/**
		*	\brief Compute the power of the value with exponent.
		*
		* 	\param[in] _value value to compute power from.
		* 	\param[in] _exp exponent value.
		*
		*	\return base raised to the power exponent.
		*/
		MATHLIBRARY_API float Pow(float _value, float _exp) noexcept;

		/**
		*	\brief Compute the square root of the value.
		*
		* 	\param[in] _value value to compute square root from.
		*
		*	\return square root of the value.
		*/
		MATHLIBRARY_API float Sqrt(int _value) noexcept;

		/**
		*	\brief Compute the square root of the value.
		*
		* 	\param[in] _value value to compute square root from.
		*
		*	\return square root of the value.
		*/
		MATHLIBRARY_API float Sqrt(float _value) noexcept;

		/**
		*	\brief Compare two values.
		*
		* 	\param[in] _start left hand side operand to compare.
		* 	\param[in] _end right hand side operand to compare.
		* 	\param[in] _epsilon threshold to accept equality.
		*/
		MATHLIBRARY_API bool Equals(float _lhs, float _rhs, float _epsilon = Math::FloatEpsilon) noexcept;

		/**
		*	\brief Check if value is equal to 0.
		*
		* 	\param[in] _value right hand side operand to compare.
		* 	\param[in] _epsilon threshold to accept equality.
		*/
		MATHLIBRARY_API bool Equals0(float _value, float _epsilon = Math::FloatEpsilon) noexcept;

		/**
		*	\brief Compute lerped vector between two float
		*
		* 	\param[in] _start left hand side operand to compute lerped vector with.
		* 	\param[in] _end right hand side operand to compute lerped vector with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped vector between _start and _end
		*/
		MATHLIBRARY_API float Lerp(float _start, float _end, float _alpha) noexcept;

		/**
		*	\brief Initalize Random functions seed.
		*/
		MATHLIBRARY_API void InitializeRandom() noexcept;
		
		/**
		*	\brief Return a random int between 0 and RAND_MAX
		*	Call InitializeRandom() before to initialize random seeding.
		*/
		MATHLIBRARY_API int Random() noexcept;

		/**
		*	\brief Return a random int between min and max value
		*	Call InitializeRandom() before to initialize random seeding.
		*
		* 	\param[in] _min random min value.
		* 	\param[in] _max random max value.
		*/
		MATHLIBRARY_API int Random(int _min, int _max) noexcept;

		/**
		*	\brief compute angle value as radians
		*
		*	\param[in] _angle angle to compute radians value from.
		*/
		MATHLIBRARY_API float Radians(float _angle) noexcept;

		/**
		*	\brief compute angle value as degree
		* 
		*	\param[in] _angle angle to compute degree value from.
		*/
		MATHLIBRARY_API float Degree(float _angle) noexcept;

		/**
		*	\brief Composes a floating point value with the 
		*	magnitude of _value and the _sign of sgn.
		*
		*	\param[in] _value value to apply the signe to.
		*	\param[in] _sign sign to aplly on the value.
		*/
		MATHLIBRARY_API float Copysign(float _value, float _sign) noexcept;
	}
}

#endif