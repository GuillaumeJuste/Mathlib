#pragma once

#ifndef MATHLIB_TRIGONOMETRY
#define MATHLIB_TRIGONOMETRY

#include <Misc/DllExport.hpp>
#include<Misc/Constants.hpp>

/**
*	\file Trigonometry.hpp
*
*	\brief implementation of trigonometry functions.
*/

namespace Mathlib
{
	namespace Math
	{
		/**
		*	\brief Compute the cosine of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		MATHLIBRARY_API float Cos(float _value) noexcept;

		/**
		*	\brief Compute the arc cosine of the value.
		*
		* 	\param[in] _value value to compute arc cosine from.
		*/
		MATHLIBRARY_API float ACos(float _value) noexcept;

		/**
		*	\brief Compute the sine  of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		MATHLIBRARY_API float Sin(float _value) noexcept;

		/**
		*	\brief Compute the arc sine of the value.
		*
		* 	\param[in] _value value to compute arc sine from.
		*/
		MATHLIBRARY_API float ASin(float _value) noexcept;

		/**
		*	\brief Compute the tangent of the value.
		*
		* 	\param[in] _value value representing angle in radians.
		*/
		MATHLIBRARY_API float Tan(float _value) noexcept;

		/**
		*	\brief Compute the arc tangent of the value.
		*
		* 	\param[in] _value value to compute arc tangent from.
		*/
		MATHLIBRARY_API float ATan(float _value) noexcept;

		/**
		*	\brief Computes the arc tangent of y/x 
		*	using the signs of arguments to determine the correct quadrant.
		*
		* 	\param[in] _x value to compute arc cosine from.
		* 	\param[in] _y value to compute arc cosine from.
		*/
		MATHLIBRARY_API float ATan2(float _x, float _y) noexcept;
	}
}

#endif