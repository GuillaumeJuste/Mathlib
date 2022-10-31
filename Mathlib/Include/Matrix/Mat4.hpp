#pragma once

#ifndef MATHLIB_MAT4
#define MATHLIB_MAT4

#include "Misc/DllExport.hpp"
#include "Misc//Constants.hpp"
#include "Misc/Common.hpp"

/**
*	\file Mat4.hpp
*
*	\brief Mat4 type implementation.
*/

namespace Mathlib
{
	struct Vec3;
	struct Vec4;
	struct Mat2;
	struct Mat3;
	struct Quat;

	/**
	*	\brief Matrix 4X4 struct.
	*/
	struct MATHLIBRARY_API Mat4
	{
	private:
		/**
		*	\brief left handed world to view matrix.
		*
		*	\param[in] _eye camera position.
		*	\param[in] _center camera look at target.
		*	\param[in] _up camera up vector.
		*/
		static Mat4 ViewMatrixLH(const Vec3& _eye, const Vec3& _center, const Vec3& _up);

		/**
		*	\brief Right handed world to view matrix.
		*
		*	\param[in] _eye camera position.
		*	\param[in] _center camera look at target.
		*	\param[in] _up camera up vector.
		*/
		static Mat4 ViewMatrixRH(const Vec3& _eye, const Vec3& _center, const Vec3& _up);

		/**
		*	\brief Create left handed perspective projection matrix.
		*	For a better distribution of the floating points values
		*	the near and far clip planes correspond to z normalized device coordinates of +1 and 0 respectively.	
		*		
		* 
		*	\param[in] _fovy Y axis field of view in radian.
		*	\param[in] _aspect aspect ratio of the render window.
		*	\param[in] _near near depth clipping plane.
		*	\param[in] _far far depth clipping plane.
		*
		*/
		static Mat4 PerspectiveMatrixLH(float _fovy, float _aspect, float _near, float _far);

		/**
		*	\brief Create right handed perspective projection matrix.
		*	For a better distribution of the floating points values
		*	the near and far clip planes correspond to z normalized device coordinates of +1 and 0 respectively.
		* 
		*	\param[in] _fovy Y axis field of view in radian.
		*	\param[in] _aspect aspect ratio of the render window.
		*	\param[in] _near near depth clipping plane.
		*	\param[in] _far far depth clipping plane.
		*
		*/
		static Mat4 PerspectiveMatrixRH(float _fovy, float _aspect, float _near, float _far);

	public:

		// Matrix components.
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
		Mat4(const Vec4& _row0, const Vec4& _row1, const Vec4& _row2, const Vec4& _row3) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat4(const Mat2& _mat) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _mat matrix to create matrix from.
		*/
		Mat4(const Mat3& _mat) noexcept;

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
		*	\param[in] _x_angle angle of the rotation around X axuis in radian.
		*	\param[in] _y_angle angle of the rotation around Y axuis in radian.
		*	\param[in] _z_angle angle of the rotation around Z axuis in radian.
		*
		*/
		static Mat4 RotationMatrix(float _x_angle, float _y_angle, float _z_angle) noexcept;

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _rotation vec3 containing rotation value around X, Y and Z axis.
		*
		*/
		static Mat4 RotationMatrix(const Vec3& _rotation) noexcept;

		/**
		*	\brief Create rotation matrix from specified angle.
		*
		*	\param[in] _rotation quaternion.
		*
		*/
		static Mat4 RotationMatrix(const Quat& _rotation) noexcept;

		/**
		*	\brief Create scale matrix from specified scale.
		*
		*	\param[in] _scale scale to create matrix from.
		*
		*/
		static Mat4 ScaleMatrix(float _scale) noexcept;

		/**
		*	\brief Create scale matrix from specified scale vector.
		*
		*	\param[in] _scale vector containg scale value for each axis.
		*
		*/
		static Mat4 ScaleMatrix(const Vec3& _scale) noexcept;

		/**
		*	\brief Create translation matrix from specified vector.
		*
		*	\param[in] _vec vector to create matrix from.
		*
		*/
		static Mat4 TranslationMatrix(const Vec3& _vec) noexcept;

		/**
		*	\brief world to view matrix.
		*
		*	\param[in] _coordinate_system coordinate system to use to compute the view matrix.
		*	\param[in] _eye camera position.
		*	\param[in] _center camera look at target.
		*	\param[in] _up camera up vector.
		*/
		static Mat4 ViewMatrix(COORDINATE_SYSTEM _coordinate_system, const Vec3& _eye, const Vec3& _center, const Vec3& _up);

		/**
		*	\brief Create perspective projection matrix.
		*
		*	\param[in] _coordinate_system coordinate system to use to compute the projection matrix.
		*	\param[in] _fovy Y axis field of view in radian.
		*	\param[in] _aspect aspect ratio of the render window.
		*	\param[in] _near near depth clipping plane.
		*	\param[in] _far far depth clipping plane.
		*
		*/
		static Mat4 PerspectiveMatrix(COORDINATE_SYSTEM _coordinate_system, float _fovy, float _aspect, float _near, float _far);
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
		bool Equals(const Mat4& _other, float _epsilon = Math::FloatEpsilon) const noexcept;

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
		*	\param[in] _rhs	vector to add to the matrix.
		*
		*	\return new vector.
		*/
		Vec4 operator*(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Add two Mat4.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator+(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Substract two Mat4.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator-(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Multiply two Mat4.
		*
		*	\param[in] _rhs	matrix to multiply to the matrix.
		*
		*	\return new matrix.
		*/
		Mat4 operator*(const Mat4& _rhs) const noexcept;

		/**
		*	\brief Add two Mat4.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator+=(const Mat4& _rhs) noexcept;

		/**
		*	\brief Substract two Mat4.
		*
		*	\param[in] _rhs	matrix to substract to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator-=(const Mat4& _rhs) noexcept;

		/**
		*	\brief Multiply two Mat4.
		*
		*	\param[in] _rhs	matrix to add to the matrix.
		*
		*	\return self matrix result.
		*/
		Mat4& operator*=(const Mat4& _rhs) noexcept;
	};
}

#endif