#pragma once

#ifndef MATHLIB_CONSTANTS
#define MATHLIB_CONSTANTS

#include "DllExport.hpp"

/**
*	\file Constants.hpp
*
*	\brief Implementation of math constants.
*/

namespace Mathlib
{
	namespace Math
	{
		/// PI constant.
		extern MATHLIBRARY_API const float Pi;

		/// Conversion constant to convert degree to radian.
		extern MATHLIBRARY_API const float DegToRad;

		/// Conversion constant to convert radian to degree.
		extern MATHLIBRARY_API const float RadToDeg;

		///machine epsilon value
		extern MATHLIBRARY_API const float FloatEpsilon;
	}
}

#endif