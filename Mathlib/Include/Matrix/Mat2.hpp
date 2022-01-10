#pragma once

#ifndef MATHLIB_MAT2
#define MATHLIB_MAT2

#include "Misc/Includes.hpp"

/**
*	\file Mat2.hpp
*
*	\brief Mat2 type implementation.
*/

namespace Mathlib
{
	struct Vec2;

	struct MATHLIBRARY_API Mat2
	{
		/// Matrix components.
		float m00, m01, m10, m11;

		//Constants
		/**
		*	\brief zero matrix
		*	{0, 0
		*	0, 0}
		*/
		static const Mat2 Zero;

		/**
		*	\brief identity matrix
		*	{1, 0
		*	0, 1}
		*/
		static const Mat2 Identity;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Mat2() noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _m00 matrix first row first column value.
		* 	\param[in] _m01 matrix first row second column value.
		*	\param[in] _m10 matrix second row first column value.
		*	\param[in] _m11 matrix second row second column value.
		*/
		Mat2(float _m00, float _m01, float _m10, float _m11) noexcept;

		/**
		*	\brief Value constructor
		*	Set all components of the matrix to the value
		*
		*	\param[in] _scale to initialise matix from.
		*/
		Mat2(float _scale) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _row0 to initialise matix row 0 from.
		*	\param[in] _row1 to initialise matix row 1 from.
		*/
		Mat2(Vec2 _row0, Vec2 _row1) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Mat2(const Mat2& _mat2) noexcept = default;

		/**
		*	\brief Default move constructor
		*/
		Mat2(Mat2&& _mat2) noexcept  = default;

		//Accessors

		/**
		*	\brief return this matrix as a float*.
		*/
		const float* Data() const noexcept;

		//Equality

		/**
		*	\brief Check if Mat2 is equal to default Zero Mat2
		**/
		bool IsZero() const noexcept;

		/**
		*	\brief Compare this matrix with with _other
		*
		*	\param[in] _other other matrix to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Mat2& _other, float _epsilon = 0.f) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Mat2& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Mat2& _rhs) const noexcept;

		//Operators

			/**
		*	\brief \e Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Mat2& operator=(Mat2&&) = default;

		/**
		*	\brief \e Default copy assignement.
		*
		*	\return self vector assigned.
		*/
		Mat2& operator=(const Mat2&) = default;
	};
}

#endif