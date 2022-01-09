#pragma once

#ifndef MATHLIB_MATH
#define MATHLIB_MATH

#include "Includes.hpp"


typedef void (* errorCallbackFunction)(const char*, const char*, const char*);

namespace Mathlib
{
	class MATHLIBRARY_API Math
	{
	
	public:
		/// PI constant.
		static const double Pi;

		/// Conversion constant to convert degree to radian.
		static const double DegToRad;

		/// Conversion constant to convert radian to degree.
		static const double RadToDeg;

		///machine epsilon value
		static const float Epsilon;

		/**
		*	\brief Compute absolute value.
		*
		* 	\param[in] _value value to compute absolute value with.
		*
		*	\return _value's absolute value.
		*/
		static int Abs(int _value) noexcept;

		/**
		*	\brief Compute absolute value.
		*
		* 	\param[in] _value value to compute absolute value with.
		*
		*	\return _value's absolute value.
		*/
		static float Abs(float _value) noexcept;

		/**
		*	\brief get _value sign.
		*
		* 	\param[in] _value value to get the sign from.
		*
		*	\return _value's sign, 1 if positive, -1 if negative.
		*/
		static int Sign(int _value) noexcept;

		/**
		*	\brief get _value sign.
		*
		* 	\param[in] _value value to get the sign from.
		*
		*	\return _value's sign, 1 if positive, -1 if negative.
		*/
		static int Sign(float _value) noexcept;

		/**
		*	\brief get minimum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return lower value between _left and _right.
		*/
		static int Min(int _left, int _right) noexcept;

		/**
		*	\brief get minimum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return lower value between _left and _right.
		*/
		static float Min(float _left, float _right) noexcept;

		/**
		*	\brief get maximum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return higher value between _left and _right.
		*/
		static int Max(int _left, int _right) noexcept;

		/**
		*	\brief get maximum value between two values.
		*
		* 	\param[in] _left value to compare with _right.
		* 	\param[in] _right value to compare with _left.
		*
		*	\return higher value between _left and _right.
		*/
		static float Max(float _left, float _right) noexcept;

		/**
		*	\brief Clamp _value between min and max value.
		*
		* 	\param[in] _value value to clamp.
		* 	\param[in] _min minimum value for the clamping.
		* 	\param[in] _max maximum value for the clamping.
		*
		*	\return _value clamped betwenn _min and _max.
		*/
		static int Clamp(int _value, int _min, int _max) noexcept;

		/**
		*	\brief Clamp _value between min and max value.
		*
		* 	\param[in] _value value to clamp.
		* 	\param[in] _min minimum value for the clamping.
		* 	\param[in] _max maximum value for the clamping.
		*
		*	\return _value clamped betwenn _min and _max.
		*/
		static float Clamp(float _value, float _min, float _max) noexcept;

		/**
		*	\brief Compute the power of the value with exponent.
		*
		* 	\param[in] _value value to compute power from.
		* 	\param[in] _exp exponent value.
		*
		*	\return base raised to the power exponent.
		*/
		static int Pow(int _value, int _exp) noexcept;

		/**
		*	\brief Compute the power of the value with exponent.
		*
		* 	\param[in] _value value to compute power from.
		* 	\param[in] _exp exponent value.
		*
		*	\return base raised to the power exponent.
		*/
		static float Pow(float _value, float _exp) noexcept;

		/**
		*	\brief Compute the square root of the value.
		*
		* 	\param[in] _value value to compute square root from.
		*
		*	\return square root of the value.
		*/
		static float Sqrt(int _value) noexcept;

		/**
		*	\brief Compute the square root of the value.
		*
		* 	\param[in] _value value to compute square root from.
		*
		*	\return square root of the value.
		*/
		static float Sqrt(float _value) noexcept;

		/**
		*	\brief Compute the cosine of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		static float Cos(float _value) noexcept;

		/**
		*	\brief Compute the arc cosine of the value.
		*
		* 	\param[in] _value value to compute arc cosine from.
		*/
		static float ACos(float _value) noexcept;

		/**
		*	\brief Compute the sine  of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		static float Sin(float _value) noexcept;

		/**
		*	\brief Compute the arc sine of the value.
		*
		* 	\param[in] _value value to compute arc cosine from.
		*/
		static float ASin(float _value) noexcept;

		/**
		*	\brief Compute the tangent of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		static float Tan(float _value) noexcept;

		/**
		*	\brief Compute the arc tangent of the value.
		*
		* 	\param[in] _value value to compute arc cosine from.
		*/
		static float ATan(float _value) noexcept;

		/**
		*	\brief Compare two values.
		*
		* 	\param[in] _start left hand side operand to compare.
		* 	\param[in] _end right hand side operand to compare.
		* 	\param[in] _epsilon threshold to accept equality.
		*/
		static bool Equals(float _lhs, float _rhs, float _epsilon = Epsilon) noexcept;

		/**
		*	\brief Check if value is equal to 0.
		*
		* 	\param[in] _value right hand side operand to compare.
		* 	\param[in] _epsilon threshold to accept equality.
		*/
		static bool Equals0(float _value, float _epsilon = Epsilon) noexcept;

		/**
		*	\brief Compute lerped vector between two float
		*
		* 	\param[in] _start left hand side operand to compute lerped vector with.
		* 	\param[in] _end right hand side operand to compute lerped vector with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped vector between _start and _end
		*/
		static float Lerp(float _start, float _end, float _alpha) noexcept;

		/**
		*	\brief Initalize Random functions seed.
		*/
		static void InitializeRandom() noexcept;
		
		/**
		*	\brief Return a random int between 0 and RAND_MAX
		*	Call InitializeRandom() before to initialize random seeding.
		*/
		static int Random() noexcept;

		/**
		*	\brief Return a random int between min and max value
		*	Call InitializeRandom() before to initialize random seeding.
		*
		* 	\param[in] _min random min value.
		* 	\param[in] _max random max value.
		*/
		static int Random(int _min, int _max) noexcept;
	};
}

#endif