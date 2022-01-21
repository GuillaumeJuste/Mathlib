#pragma once

#ifndef MATHLIB_MAT4
#define MATHLIB_MAT4

#include "Misc/Includes.hpp"

/**
*	\file Mat4.hpp
*
*	\brief Mat4 type implementation.
*/

namespace Mathlib
{
	struct Vec4;

	struct MATHLIBRARY_API Mat4
	{
		/// Matrix components.
		float e00{ 0.f }; float e01{ 0.f }; float e02{ 0.f }; float e03{ 0.f };
		float e10{ 0.f }; float e11{ 0.f }; float e12{ 0.f }; float e13{ 0.f };
		float e20{ 0.f }; float e21{ 0.f }; float e22{ 0.f }; float e23{ 0.f };
		float e30{ 0.f }; float e31{ 0.f }; float e32{ 0.f }; float e33{ 0.f };

		//Constants
		/**
		*	\brief zero matrix
		*	{0, 0, 0, 0,
		*	0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0}
		*/
		static const Mat4 Zero;

		/**
		*	\brief identity matrix
		*	{1, 0, 0, 0,
		*	0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1}
		*/
		static const Mat4 Identity;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Mat4() noexcept = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _e00 matrix first row first column value.
		* 	\param[in] _e01 matrix first row second column value.
		*	\param[in] _e02 matrix first row third column value.
		*	\param[in] _e03 matrix first row fourth column value.
		*	\param[in] _e10 matrix second row first column value.
		* 	\param[in] _e11 matrix second row second column value.
		* 	\param[in] _e12 matrix second row third column value.
		* 	\param[in] _e13 matrix second row fourth column value.
		*	\param[in] _e20 matrix third row first column value.
		*	\param[in] _e21 matrix third row second column value.
		*	\param[in] _e22 matrix third row third column value.
		*	\param[in] _e23 matrix third row fourth column value.
		* 	\param[in] _e30 matrix fourth row first column value.
		*	\param[in] _e31 matrix fourth row second column value.
		*	\param[in] _e32 matrix fourth row third column value.
		*	\param[in] _e33 matrix fourth row fourth column value.
		*/
		Mat4(float _e00, float _e01, float _e02, float _e03,
			float _e10, float _e11, float _e12, float _e13,
			float _e20, float _e21, float _e22, float _e23, 
			float _e30, float _e31, float _e32, float _e33) noexcept;

		/**
		*	\brief Value constructor
		*	Set all components of the matrix to the value
		*
		*	\param[in] _value to initialise matix from.
		*/
		Mat4(float _value) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _row0 to initialise matix first row from.
		*	\param[in] _row1 to initialise matix second row from.
		*	\param[in] _row2 to initialise matix third row from.
		*	\param[in] _row3 to initialise matix fourth row from.
		*/
		Mat4(Vec4 _row0, Vec4 _row1, Vec4 _row2, Vec4 _row3) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Mat4(const Mat4& _mat) noexcept = default;

		/**
		*	\brief Default move constructor
		*/
		Mat4(Mat4&& _mat) noexcept = default;

		//Static methods

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _angle angle in radian to create matrix from.
		*
		*/
		static Mat4 RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept;

		/**
		*	\brief Create scale matrix from specified scale.
		*
		*	\param[in] _scale scale to create matrix from.
		*
		*/
		static Mat4 ScaleMatrix(float _scale) noexcept;

		//Accessors

		/**
		*	\brief return this matrix as a float*.
		*/
		const float* Data() const noexcept;

		/**
		*	\brief Access matrix data at index.
		*/
		float& operator[](unsigned int _index);

		//Equality

		/**
		*	\brief Check if Mat4 is equal to default Zero Mat4
		**/
		bool IsZero() const noexcept;

		/**
		*	\brief Check if Mat4 is equal to default Identity Mat4
		**/
		bool IsIdentity() const noexcept;

		/**
		*	\brief Compare this matrix with with _other
		*
		*	\param[in] _other other matrix to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Mat4& _other, float _epsilon = Math::Epsilon) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Mat4& _rhs) const noexcept;

		//methods
		/**
		*	\brief Transpose Matrix.
		*
		*	\return This matrix transposed.
		**/
		Mat4 Transpose() noexcept;

		/**
		*	\brief Transpose Matrix.
		*
		*	\return New transposed Matrix.
		**/
		Mat4 GetTranspose()const noexcept;

		/**
		*	\brief Compute inverse matrix.
		*
		*	\return This matrix inverted.
		**/
		Mat4 Inverse() noexcept;

		/**
		*	\brief Compute inverse matrix.
		*
		*	\return new matrix inverted.
		**/
		Mat4 GetInverse() const noexcept;

		/**
		*	\brief Compute matrix determinant.
		**/
		float Determinant() const noexcept;

		//Operators

		/**
		*	\brief \e Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Mat4& operator=(Mat4&&) = default;

		/**
		*	\brief \e Default copy assignement.
		*
		*	\return self matrix assigned.
		*/
		Mat4& operator=(const Mat4&) = default;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat4 operator+(float _scale) const noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat4 operator-(float _scale) const noexcept;

		/**
		*	\brief Scale each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat4 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new divided matrix.
		*/
		Mat4 operator/(float _scale) const;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat4& operator+=(float _scale) noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat4& operator-=(float _scale) noexcept;

		/**
		*	\brief Scale each matrix components by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat4& operator*=(float _scale) noexcept;

		/**
		*	\brief Divide each matrix components axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat4& operator/=(float _scale);

		/**
		*	\brief Multiply Mat4 and Vec4.
		*
		*	\param[in] _vec	vector to add to the matrix.
		*
		*	\return new vector.
		*/
		Vec4 operator*(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Add two Mat4.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator+(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Substract two Mat4.
		*
		*	\param[in] _mat	matrix to substract to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator-(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Multiply two Mat4.
		*
		*	\param[in] _mat	matrix to multiply to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator*(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Add two Mat4.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator+=(const Mat4& _rhs) noexcept;

		/**
		*	\brief Substract two Mat4.
		*
		*	\param[in] _mat	matrix to substract to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator-=(const Mat4& _rhs) noexcept;

		/**
		*	\brief Multiply two Mat4.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator*=(const Mat4& _rhs) noexcept;
	};
}

#endif