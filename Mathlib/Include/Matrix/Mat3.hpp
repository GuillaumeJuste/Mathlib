#pragma once

#ifndef MATHLIB_MAT3
#define MATHLIB_MAT3

#include "Misc/Includes.hpp"

/**
*	\file Mat3.hpp
*
*	\brief Mat3 type implementation.
*/

namespace Mathlib
{
	struct Vec3;

	struct MATHLIBRARY_API Mat3
	{
		/// Matrix components.
		Vec3 X, Y, Z;

		//Constants
		/**
		*	\brief zero matrix
		*	{0, 0
		*	0, 0}
		*/
		static const Mat3 Zero;

		/**
		*	\brief identity matrix
		*	{1, 0
		*	0, 1}
		*/
		static const Mat3 Identity;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Mat3() noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _m00 matrix first row first column value.
		* 	\param[in] _m01 matrix first row second column value.
		*	\param[in] _m02 matrix first row third column value.
		*	\param[in] _m10 matrix second row first column value.
		* 	\param[in] _m11 matrix second row second column value.
		* 	\param[in] _m12 matrix second row third column value.
		*	\param[in] _m20 matrix third row first column value.
		*	\param[in] _m21 matrix third row second column value.
		*	\param[in] _m22 matrix third row third column value.
		*/
		Mat3(float _m00, float _m01, float _m02, 
			float _m10, float _m11, float _m12, 
			float _m20, float _m21, float _m22) noexcept;

		/**
		*	\brief Value constructor
		*	Set all components of the matrix to the value
		*
		*	\param[in] _value to initialise matix from.
		*/
		Mat3(float _value) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _row0 to initialise matix first row from.
		*	\param[in] _row1 to initialise matix second row from.
		*	\param[in] _row2 to initialise matix third row from.
		*/
		Mat3(Vec3 _row0, Vec3 _row1, Vec3 _row2) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Mat3(const Mat3& _mat) noexcept = default;

		/**
		*	\brief Default move constructor
		*/
		Mat3(Mat3&& _mat) noexcept = default;

		//Static methods

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _angle angle in radian to create matrix from.
		*
		*/
		static Mat3 RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept;

		/**
		*	\brief Create scale matrix from specified scale.
		*
		*	\param[in] _scale scale to create matrix from.
		*
		*/
		static Mat3 ScaleMatrix(float _scale) noexcept;

		//Accessors

		/**
		*	\brief return this matrix as a float*.
		*/
		const float* Data() const noexcept;

		/**
		*	\brief Access matrix data at index.
		*/
		const float operator[](unsigned int _index) const;

		//Equality

		/**
		*	\brief Check if Mat3 is equal to default Zero Mat3
		**/
		bool IsZero() const noexcept;

		/**
		*	\brief Check if Mat3 is equal to default Identity Mat3
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
		bool Equals(const Mat3& _other, float _epsilon = Math::Epsilon) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Mat3& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this matrix with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Mat3& _rhs) const noexcept;

		//methods
		/**
		*	\brief Transpose Matrix.
		*
		*	\return This matrix transposed.
		**/
		Mat3 Transpose() noexcept;

		/**
		*	\brief Transpose Matrix.
		*
		*	\return New transposed Matrix.
		**/
		Mat3 GetTranspose()const noexcept;

		/**
		*	\brief Compute inverse matrix.
		*
		*	\return This matrix inverted.
		**/
		Mat3 Inverse() noexcept;

		/**
		*	\brief Compute inverse matrix.
		*
		*	\return new matrix inverted.
		**/
		Mat3 GetInverse() const noexcept;

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
		Mat3& operator=(Mat3&&) = default;

		/**
		*	\brief \e Default copy assignement.
		*
		*	\return self matrix assigned.
		*/
		Mat3& operator=(const Mat3&) = default;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat3 operator+(float _scale) const noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat3 operator-(float _scale) const noexcept;

		/**
		*	\brief Scale each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new matrix scaled.
		*/
		Mat3 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's matrix components.
		*
		*	\param[in] _scale	Scale value to apply to all components.
		*
		*	\return new divided matrix.
		*/
		Mat3 operator/(float _scale) const;

		/**
		*	\brief Add scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat3& operator+=(float _scale) noexcept;

		/**
		*	\brief Substract scale to each matrix components.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat3& operator-=(float _scale) noexcept;

		/**
		*	\brief Scale each matrix components by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat3& operator*=(float _scale) noexcept;

		/**
		*	\brief Divide each matrix components axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all components.
		*
		*	\return self matrix result.
		*/
		Mat3& operator/=(float _scale);

		/**
		*	\brief Multiply Mat3 and Vec3.
		*
		*	\param[in] _vec	vector to add to the matrix.
		*
		*	\return new vector.
		*/
		Vec3 operator*(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Add two Mat3.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator+(const Mat3 & _rhs) const noexcept;

		/**
		*	\brief Substract two Mat3.
		*
		*	\param[in] _mat	matrix to substract to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator-(const Mat3 & _rhs) const noexcept;

		/**
		*	\brief Multiply two Mat3.
		*
		*	\param[in] _mat	matrix to multiply to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator*(const Mat3& _rhs) const noexcept;

		/**
		*	\brief Add two Mat3.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator+=(const Mat3& _rhs) noexcept;

		/**
		*	\brief Substract two Mat3.
		*
		*	\param[in] _mat	matrix to substract to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator-=(const Mat3& _rhs) noexcept;

		/**
		*	\brief Multiply two Mat3.
		*
		*	\param[in] _mat	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator*=(const Mat3& _rhs) noexcept;
	};
}

#endif