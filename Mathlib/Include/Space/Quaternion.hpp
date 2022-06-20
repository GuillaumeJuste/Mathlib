#pragma once	

#ifndef MATHLIB_QUATERNION
#define MATHLIB_QUATERNION

#include "Misc/DllExport.hpp"
#include "Misc/Constants.hpp"
#include <string>

/**
*	\file Quaternion.hpp
*
*	\brief Quaternion type implementation.
*/

namespace Mathlib
{
	struct Vec3;
	struct Mat4;

	/**
	*	\brief quaternion struct.
	*/
	struct MATHLIBRARY_API Quat
	{
		/// Quaternion's rotation component
		float W = 0.f;
		/// Quaternion's X axis component
		float X = 0.f;
		/// Quaternion's Y axis component
		float Y = 0.f;
		/// Quaternion's Z axis component
		float Z = 0.f;
		//Constants

		/// Quaternion zero constant {0, 0, 0, 0}.
		static const Quat Zero;

		/// Quaternion Identity constant {1, 0, 0, 0}.
		static const Quat Identity;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Quat() = default;


		/**
		*	\brief Value constructor
		*
		*	\param[in] _w W value.
		*	\param[in] _x X value.
		* 	\param[in] _y Y value.
		*	\param[in] _z Z value.
		*/
		Quat(float _w, float _x, float _y, float _z) noexcept;

		/**
		*	\brief Value constructor
		*
		* 	\param[in] _angle quaternion rotation in degree.
		*	\param[in] _axis Z value.
		*/
		Quat(float _angle, const Vec3& _axis) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Quat(const Quat& _quat) = default;

		/**
		*	\brief Default move constructor
		*/
		Quat(Quat&& _quat) = default;

		//Length & Normalization

		/**
		*	\brief return the length of this quaternion.
		*/
		float Length() const noexcept;

		/**
		*	\brief Return the squared length of this quaternion.
		*/
		float SquaredLength() const noexcept;

		/**
		*	\brief Normalize this quaternion and return it.
		*/
		Quat& Normalize() noexcept;

		/**
		*	\brief Return this quaternion normalized vector.
		*/
		Quat GetNormalized() const noexcept;

		/**
		*	\brief Check if the quaternion is normalized.
		*/
		bool  IsNormalized() const noexcept;

		//Euler

		/**
		*	\brief Create quaternion from euler rotations
		*
		*	\param[in] _angles	vector containing euler rotation around all 3 axis in degrees.
		*
		*	\return new quaternions created from euler angles;
		*/
		static Quat FromEuler(const Vec3& _angles) noexcept;

		/**
		*	\brief Convert a Quaternion into floating-point Euler angles (in degrees).
		*/
		Vec3 Euler() const noexcept;

		//Invert

		/**
		*	\brief Invert this quaternion and return it.
		*/
		Quat& Inverse() noexcept;

		/**
		*	\brief Invert this quaternion and return it as a new quaternion.
		*/
		Quat GetInverse() const noexcept;

		//Conjugate

		/**
		*	\brief return the conjugate of this quaternion as a new quaternion.
		*/
		Quat GetConjugate() const noexcept;

		//Angle/Axis

		/**
		*	\brief return the quaternions angle.
		*/
		float GetAngle() const noexcept;

		/**
		*	\brief return the quaternions axis.
		*/
		Vec3 GetAxis() const noexcept;

		// Rotate

		/**
		*	\brief Rotate input quaternion by this quaternion;
		*
		*	\param[in] _quat quaternion to rotate.
		*
		*	\return new quaternion result of the input quaternion rotated by this quaternion.
		*/
		Quat Rotate(const Quat& _quat) const noexcept;

		/**
		*	\brief Rotate input vector by this quaternion;
		*
		*	\param[in] _vec vector to rotate.
		*
		*	\return new Quaternion result of the input vector rotated by this quaternion.
		*/
		Vec3 Rotate(const Vec3& _vec) const noexcept;

		/**
		*	\brief Get the Right vector (X axis) rotated by this quaternion.
		*/
		Vec3 GetRightVector() const noexcept;

		/**
		*	\brief Get the Up vector (Y axis) rotated by this quaternion.
		*/
		Vec3 GetUpVector() const noexcept;
		
		/**
		*	\brief Get the Forward vector (Z axis) rotated by this quaternion.
		*/
		Vec3 GetForwardVector() const noexcept;

		//Dot

		/**
		*	\brief Compute dot product between two Quat
		*
		* 	\param[in] _lhs left hand side operand to compute dot product with.
		* 	\param[in] _rhs right hand side operand to compute dot product with.
		*
		*	\return dot product between _lhs and _rhs
		*/
		static float DotProduct(const Quat& _lhs, const Quat& _rhs) noexcept;

		//Lerp / Slerp

		/**
		*	\brief Compute lerped vector between two Quat
		*
		* 	\param[in] _start left hand side operand to compute lerped quaternion with.
		* 	\param[in] _end right hand side operand to compute lerped quaternion with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped quaternion between _start and _end
		*/
		static Quat Lerp(const Quat& _start, const Quat& _end, float _alpha);

		/**
		*	\brief Compute spherical lerped vector between two quaternion
		*
		* 	\param[in] _start left hand side operand to compute spherical lerped quaternion with.
		* 	\param[in] _end right hand side operand to compute spherical lerped quaternion with.
		*	\param[in] _alpha Alpha of the lerp value is between 0 and 1.
		*
		* 	\return spherical lerped quaternion between _start and _end
		*/
		static Quat SLerp(const Quat& _start, const Quat& _end, float _alpha) noexcept;

		//Equality

		/**
		*	\brief Check if Quaternion is equal to default Zero vector
		*/
		bool IsZero() const noexcept;

		/**
		*	\brief Check if Quaternion is equal to default Identity vector
		*/
		bool IsIdentity() const noexcept;

		/**
		*	\brief Compare this Quaternion with with _other
		*
		*	\param[in] _other other quaternion to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Quat& _other, float _epsilon = Math::FloatEpsilon) const noexcept;

		/**
		*	\brief Operator to compare this Quaternion with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Quat& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this Quaternion with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Quat& _rhs) const noexcept;

		//Accessors

		/**
		*	\brief return this Quaternion as a float*.
		*/
		const float* Data() const noexcept;

		//Operator

		/**
		*	\brief Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Quat& operator=(Quat&&) = default;

		/**
		*	\brief Default copy assignement.
		*
		*	\return self vector assigned.
		*/
		Quat& operator=(const Quat&) = default;

		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed quaternion.
		*/
		Quat operator-() const noexcept;

		/**
		*	\brief Add term by term quaternions values.
		*
		*	\param[in] _rhs	quaternion to add.
		*
		*	\return new quaternions sum of both quaternions.
		*/
		Quat operator+(const Quat& _rhs) const noexcept;

		/**
		*	\brief Substract term by term quaternions values.
		*
		*	\param[in] _rhs	quaternion to substract.
		*
		*	\return new quaternions result of the substraction of both quaternions.
		*/
		Quat operator-(const Quat& _rhs) const noexcept;

		/**
		*	\brief Rotate _rhs by this quaternion;
		*
		*	\param[in] _rhs quaternion to rotate.
		*
		*	\return new quaternion result of the rotation.
		*/
		Quat operator*(const Quat& _rhs) const noexcept;

		/**
		*	\brief Rotate _rhs by the inverse of this quaternion;
		*
		*	\param[in] _rhs quaternion to rotate.
		*
		*	\return new quaternion result of the rotation.
		*/
		Quat operator/(const Quat& _rhs) const noexcept;

		/**
		*	\brief Add term by term quaternions values.
		*
		*	\param[in] _rhs	quaternion to add.
		*
		*	\return self quaternions sum of both quaternions.
		*/
		Quat operator+=(const Quat& _rhs) noexcept;

		/**
		*	\brief Substract term by term quaternions values.
		*
		*	\param[in] _rhs	quaternion to substract.
		*
		*	\return self quaternions result of the substraction of both quaternions.
		*/
		Quat operator-=(const Quat& _rhs) noexcept;

		/**
		*	\brief Rotate _rhs by this quaternion;
		*
		*	\param[in] _rhs quaternion to rotate.
		*
		*	\return self quaternion result of the rotation.
		*/
		Quat operator*=(const Quat& _rhs) noexcept;

		/**
		*	\brief Rotate _rhs by the inverse of this quaternion;
		*
		*	\param[in] _rhs quaternion to rotate.
		*
		*	\return self quaternion result of the rotation.
		*/
		Quat operator/=(const Quat& _rhs) noexcept;

		/**
		*	\brief Rotate _rhs by this quaternion;
		*
		*	\param[in] _rhs vec3 to rotate.
		*
		*	\return new quaternion result of the rotation.
		*/
		Vec3 operator*(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Rotate _rhs by the inverse of this quaternion;
		*
		*	\param[in] _rhs vec3 to rotate.
		*
		*	\return new quaternion result of the rotation.
		*/
		Vec3 operator/(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Scale each quaternion's components by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new Quat scaled.
		*/
		Quat operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each quaternion's components by scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new Quat vector.
		*/
		Quat operator/(float _scale) const;

		/**
		*	\brief Scale each quaternion's components by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self Quat result.
		*/
		Quat& operator*=(float _scale) noexcept;

		/**
		*	\brief Scale each quaternion's components by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self Quat result.
		*/
		Quat& operator/=(float _scale);
	};
}

#endif