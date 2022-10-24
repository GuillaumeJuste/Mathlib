#pragma once

#ifndef MATHLIB_MAT3
#define MATHLIB_MAT3

#include "Misc/DllExport.hpp"

/**
*	\file Mat3.hpp
*
*	\brief Mat3 type implementation.
*/

namespace Mathlib
{
	struct Vec2;
	struct Vec3;
	struct Mat2;
	struct Mat4;

	/**
	*	\brief Matrix 3X3 struct.
	*/
	struct MATHLIBRARY_API Mat3
	{
		// Matrix components.
		float e00{ 0.f }; float e01{ 0.f }; float e02{ 0.f };
		float e10{ 0.f }; float e11{ 0.f }; float e12{ 0.f };
		float e20{ 0.f }; float e21{ 0.f }; float e22{ 0.f };

		//Constants
		/**
		*	\brief zero matrix
		*	{0, 0, 0
		*	0, 0, 0,
			0, 0, 0}
		*/
		static const Mat3 Zero;

		/**
		*	\brief identity matrix
		*	{1, 0, 0,
		*	0, 1, 0,
			0, 0, 1}
		*/
		static const Mat3 Identity;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Mat3() noexcept = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _e00 matrix first row first column value.
		* 	\param[in] _e01 matrix first row second column value.
		*	\param[in] _e02 matrix first row third column value.
		*	\param[in] _e10 matrix second row first column value.
		* 	\param[in] _e11 matrix second row second column value.
		* 	\param[in] _e12 matrix second row third column value.
		*	\param[in] _e20 matrix third row first column value.
		*	\param[in] _e21 matrix third row second column value.
		*	\param[in] _e22 matrix third row third column value.
		*/
		Mat3(float _e00, float _e01, float _e02,
			float _e10, float _e11, float _e12,
			float _e20, float _e21, float _e22) noexcept;

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
		Mat3(const Vec3& _row0, const Vec3& _row1, const Vec3& _row2) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat3(const Mat2& _mat) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat3(const Mat4& _mat) noexcept;

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
		*	\param[in] _x_angle around X axis in degree to create matrix from.
		*	\param[in] _y_angle around Y axis in degree to create matrix from.
		*	\param[in] _z_angle around Z axis in degree to create matrix from.
		*
		*/
		static Mat3 RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept;

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _rotation vec3 containing rotation value around X, Y and Z axis.
		*
		*/
		static Mat3 RotationMatrix(const Vec3& _rotation) noexcept;

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _rotation angle in radian to create matrix from.
		*
		*/
		static Mat3 RotationMatrix2D(float _rotation) noexcept;

		/**
		*	\brief Create scale matrix from specified scale.
		*
		*	\param[in] _scale scale to create matrix from.
		*
		*/
		static Mat3 ScaleMatrix(float _scale) noexcept;

		/**
		*	\brief Create scale matrix from specified scale vector.
		*
		*	\param[in] _scale vector containg scale value for each axis.
		*
		*/
		static Mat3 ScaleMatrix(const Vec2& _scale) noexcept;

		/**
		*	\brief Create translation matrix from specified vector.
		*
		*	\param[in] _vec vector to create matrix from.
		*
		*/
		static Mat3 TranslationMatrix(const Vec2& _vec) noexcept;

		/**
		*	\brief Create 2D transform matrix.
		*
		*	\param[in] _rotation transform's rotations.
		*	\param[in] _position transform's position.
		*	\param[in] _scale transform's scale.
		*
		*/
		static Mat3 TransformMatrix2D(float _rotation, const Vec2& _position, const Vec2& _scale) noexcept;

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
		bool Equals(const Mat3& _other, float _epsilon = Math::FloatEpsilon) const noexcept;

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
		*	\brief Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Mat3& operator=(Mat3&&) = default;

		/**
		*	\brief Default copy assignement.
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
		*	\param[in] _rhs	vector to add to the matrix.
		*
		*	\return new vector.
		*/
		Vec3 operator*(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Add two Mat3.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator+(const Mat3& _rhs) const noexcept;

		/**
		*	\brief Substract two Mat3.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator-(const Mat3& _rhs) const noexcept;

		/**
		*	\brief Multiply two Mat3.
		*
		*	\param[in] _rhs	matrix to multiply to the matrix.
		*
		*	\return new matrix.
		*/
		Mat3 operator*(const Mat3& _rhs) const noexcept;

		/**
		*	\brief Add two Mat3.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator+=(const Mat3& _rhs) noexcept;

		/**
		*	\brief Substract two Mat3.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator-=(const Mat3& _rhs) noexcept;

		/**
		*	\brief Multiply two Mat3.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat3& operator*=(const Mat3& _rhs) noexcept;
	};
}

#endif