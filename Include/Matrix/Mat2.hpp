#pragma once

#ifndef MATHLIB_MAT2
#define MATHLIB_MAT2

#include "Misc/DllExport.hpp"

/**
*	\file Mat2.hpp
*
*	\brief Mat2 type implementation.
*/

namespace Mathlib
{
	struct Vec2;
	struct Mat3;
	struct Mat4;

	/**
	*	\brief Matrix 2X2 struct.
	*/
	struct MATHLIBRARY_API Mat2
	{
		// Matrix components.
		float e00{ 0.f }; float e01{ 0.f }; 
		float e10{ 0.f }; float e11{ 0.f };

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
		Mat2() noexcept = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _e00 matrix first row first column value.
		* 	\param[in] _e01 matrix first row second column value.
		*	\param[in] _e10 matrix second row first column value.
		*	\param[in] _e11 matrix second row second column value.
		*/
		Mat2(float _e00, float _e01, float _e10, float _e11) noexcept;

		/**
		*	\brief Value constructor
		*	Set all components of the matrix to the value
		*
		*	\param[in] _value to initialise matix from.
		*/
		Mat2(float _value) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _row0 to initialise matix first row from.
		*	\param[in] _row1 to initialise matix second row from.
		*/
		Mat2(const Vec2& _row0, const Vec2& _row1) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat2(const Mat3& _mat) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat2(const Mat4& _mat) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Mat2(const Mat2& _mat2) noexcept = default;

		/**
		*	\brief Default move constructor
		*/
		Mat2(Mat2&& _mat2) noexcept  = default;

		//Static methods

		/**
		*	\brief Create rotation matrix from specified angle.
		* 
		*	\param[in] _angle angle in radian to create matrix from.
		*
		*/
		static Mat2 RotationMatrix(float _angle) noexcept;

		/**
		*	\brief Create scale matrix from specified scale.
		*
		*	\param[in] _scale scale to create matrix from.
		*
		*/
		static Mat2 ScaleMatrix(float _scale) noexcept;

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
		*	\brief Check if Mat2 is equal to default Zero Mat2
		**/
		bool IsZero() const noexcept;

		/**
		*	\brief Check if Mat2 is equal to default Identity Mat2
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
		bool Equals(const Mat2& _other, float _epsilon = Math::FloatEpsilon) const noexcept;

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

		//methods
		/**
		*	\brief Transpose Matrix.
		* 
		*	\return This matrix transposed.
		**/
		Mat2 Transpose() noexcept;

		/**
		*	\brief Transpose Matrix.
		*
		*	\return New transposed Matrix.
		**/
		Mat2 GetTranspose()const noexcept;

		/**
		*	\brief Compute inverse matrix.
		*
		*	\return This matrix inverted.
		**/
		Mat2 Inverse() noexcept;
		
		/**
		*	\brief Compute inverse matrix.
		*
		*	\return new matrix inverted.
		**/
		Mat2 GetInverse() const noexcept;

		/**
		*	\brief Compute matrix determinant.
		**/
		float Determinant() const noexcept;

		//Operators

		/**
		*	\brief Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Mat2& operator=(Mat2&&) = default;

		/**
		*	\brief Default copy assignement.
		*
		*	\return self matrix assigned.
		*/
		Mat2& operator=(const Mat2&) = default;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat2 operator+(float _scale) const noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat2 operator-(float _scale) const noexcept;

		/**
		*	\brief Scale each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat2 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new divided matrix.
		*/
		Mat2 operator/(float _scale) const;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat2& operator+=(float _scale) noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat2& operator-=(float _scale) noexcept;

		/**
		*	\brief Scale each matrix components by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat2& operator*=(float _scale) noexcept;

		/**
		*	\brief Divide each matrix components axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat2& operator/=(float _scale);

		/**
		*	\brief Multiply Mat2 and Vec2.
		*
		*	\param[in] _rhs	vector to add to the matrix.
		*
		*	\return new vector.
		*/
		Vec2 operator*(const Vec2& _rhs) const noexcept;

		/**
		*	\brief Add two Mat2.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return new matrix.
		*/
		Mat2 operator+(const Mat2& _rhs) const noexcept;

		/**
		*	\brief Substract two Mat2.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return new matrix.
		*/
		Mat2 operator-(const Mat2& _rhs) const noexcept;

		/**
		*	\brief Multiply two Mat2.
		*
		*	\param[in] _rhs	matrix to multiply to the matrix.
		*
		*	\return new matrix.
		*/
		Mat2 operator*(const Mat2& _rhs) const noexcept;

		/**
		*	\brief Add two Mat2.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat2& operator+=(const Mat2& _rhs) noexcept;

		/**
		*	\brief Substract two Mat2.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat2& operator-=(const Mat2& _rhs) noexcept;

		/**
		*	\brief Multiply two Mat2.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat2& operator*=(const Mat2& _rhs) noexcept;
	};
}

#endif