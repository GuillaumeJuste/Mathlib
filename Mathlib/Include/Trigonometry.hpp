#pragma once

#ifndef MATHLIB_TRIGONOMETRY
#define MATHLIB_TRIGONOMETRY

#include <Includes.hpp>
#include<Constants.hpp>

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
		* 	\param[in] _value value to compute arc cosine from.
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
		* 	\param[in] _value value to compute arc cosine from.
		*/
		MATHLIBRARY_API float ATan(float _value) noexcept;
	}
}

#endif