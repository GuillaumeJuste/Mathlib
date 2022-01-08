#pragma once

#ifndef MATHLIB_VEC2
#define MATHLIB_VEC2

#include "Includes.hpp"

/**
*	\file Vector2.hpp
*
*	\brief Vec2 type implementation.
*/

namespace Mathlib
{
	struct Vec3;
	struct Vec4;

	struct MATHLIBRARY_API Vec2
	{
		/// Vector's X component
		float X = 0.f;
		/// Vector's Y component
		float Y = 0.f;

		//Constants

		/// Zero vector constant {0, 0}.
		static const Vec2 Zero;

		/// One vector constant {1, 1}.
		static const Vec2 One;

		/// Right vector constant {1, 0}.
		static const Vec2 Right;

		/// Left vector constant {-1, 0}.
		static const Vec2 Left;

		/// Up vector constant {0, 1}.
		static const Vec2 Up;

		/// Down vector constant {0, -1}.
		static const Vec2 Down;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Vec2() = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _xy Value applied on all vector axis.
		*/
		Vec2(float _xy) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _x X axis value.
		* 	\param[in] _y Y axis value.
		*/
		Vec2(float _x, float _y) noexcept;

		/**
		*	\brief Constructor from a Vec3
		*
		*	\param[in] _vec3 Vec3 to copy axis values from.
		*/
		Vec2(Vec3 _vec3) noexcept;

		/**
		*	\brief Constructor from a Vec4
		*
		*	\param[in] _vec4 Vec4 to copy axis values from.
		*/
		Vec2(Vec4 _vec4) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Vec2(const Vec2& _vec2) = default;

		/**
		*	\brief Default move constructor
		*/
		Vec2(Vec2&& _vec2) = default;

		//Static Methods

		/**
		*	\brief Compute dot product between two Vec2
		*
		* 	\param[in] _lhs left hand side operand to compute dot product with.
		* 	\param[in] _rhs right hand side operand to compute dot product with.
		*
		*	\return dot product between _lhs and _rhs
		*/
		static float DotProduct(const Vec2& _lhs, const Vec2& _rhs) noexcept;

		/**
		*	\brief Compute cross product between two Vec2
		*
		* 	\param[in] _lhs left hand side operand to compute cross product with.
		* 	\param[in] _rhs right hand side operand to compute cross product with.
		*
		* 	\return cross product between _lhs and _rhs
		*/
		static float CrossProduct(const Vec2& _lhs, const Vec2& _rhs) noexcept;

		/**
		*	\brief Compute angle between two vectors
		*
		* 	\param[in] _start left hand side operand to compute angle with.
		* 	\param[in] _end right hand side operand to compute angle with.
		*
		* 	\return Angle between _start and _end
		*/
		static float Angle(const Vec2& _start, const Vec2& _end);

		/**
		*	\brief Compute distance between two Vec2
		*
		* 	\param[in] _start left hand side operand to compute distance with.
		* 	\param[in] _end right hand side operand to compute distance with.
		*
		* 	\return distance between _start and _end
		*/
		static float Distance(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief Compute squared distance between two Vec2
		*
		* 	\param[in] _start left hand side operand to compute squared distance with.
		* 	\param[in] _end right hand side operand to compute squared distance with.
		*
		* 	\return squared distance between _start and _end
		*/
		static float SqrDistance(const Vec2& _start, const Vec2& _end) noexcept;

		/**
		*	\brief Compute lerped vector between two Vec2
		*
		* 	\param[in] _start left hand side operand to compute lerped vector with.
		* 	\param[in] _end right hand side operand to compute lerped vector with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped vector between _start and _end
		*/
		static Vec2 Lerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

		/**
		*	\brief Compute spherical lerped vector between two Vec2
		*
		* 	\param[in] _start left hand side operand to compute spherical lerped vector with.
		* 	\param[in] _end right hand side operand to compute spherical lerped vector with.
		*	\param[in] _alpha Alpha of the lerp value is between 0 and 1.
		*
		* 	\return spherical lerped vector between _start and _end
		*/
		static Vec2 SLerp(const Vec2& _start, const Vec2& _end, float _alpha) noexcept;

		//Equality

		/**
		*	\brief Check if Vec2 is equal to default Zero vector
		*/
		bool IsZero() const noexcept;

		/**
		*	\brief Compare this vector with with _other
		*
		*	\param[in] _other other vector to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Vec2& _other, float _epsilon = 0.f) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Vec2& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Vec2& _rhs) const noexcept;

		//Accessors

		/**
		*	\brief return this vector as a float*.
		*/
		const float* Data() const noexcept;

		//Methods

		/**
		*	\brief return the length of this vector.
		*/
		float Length() const noexcept;

		/**
		*	\brief Return the squared length of this vector.
		*/
		float SquaredLength() const noexcept;

		/**
		*	\brief Normalize this vector and return it.
		*/
		Vec2& Normalize() noexcept;

		/**
		*	\brief Return this vector normalized vector.
		*/
		Vec2 GetNormalized() const noexcept;

		/**
		*	\brief Check if the vector is normalized.
		*/
		bool  IsNormalized() const noexcept;

		/**
		*	\brief Project this vector on _other
		*
		*	\param _other	Vector on which to project this vector.
		*
		*	\return projection of this vector on the other vector
		*/
		Vec2 ProjectOn(const Vec2& _other) const noexcept;

		//Operator

		/**
		*	\brief Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Vec2& operator=(Vec2&&) = default;

		/**
		*	\brief Default copy assignement.
		*
		*	\return self vector assigned.
		*/
		Vec2& operator=(const Vec2&) = default;

		/**
		*	\brief Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		Vec2 operator-() const noexcept;

		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return new vector sum of both vectors.
		*/
		Vec2 operator+(const Vec2& _rhs) const noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return new vector result of the substraction of both vectors.
		*/
		Vec2 operator-(const Vec2& _rhs) const noexcept;

		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return new vector result of the multiplication of both vectors.
		*/
		Vec2 operator*(const Vec2& _rhs) const noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide this vector with.
		*
		*	\return new vector result of the operation.
		*/
		Vec2 operator/(const Vec2& _rhs) const;

		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return self vector result.
		*/
		Vec2& operator+=(const Vec2& _rhs) noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return self vector result.
		*/
		Vec2& operator-=(const Vec2& _rhs) noexcept;

		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec2& operator*=(const Vec2& _rhs) noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide.
		*
		*	\return self vector result.
		*/
		Vec2& operator/=(const Vec2& _rhs);

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new vector scaled.
		*/
		Vec2 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new divided vector.
		*/
		Vec2 operator/(float _scale) const;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec2& operator*=(float _scale) noexcept;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec2& operator/=(float _scale);

		//Debug

		/**
		*	\brief return vector values as string.
		*/
		std::string ToString()const noexcept;
	};
}

#endif