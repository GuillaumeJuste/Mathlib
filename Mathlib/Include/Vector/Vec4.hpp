#pragma once	

#ifndef MATHLIB_VEC4
#define MATHLIB_VEC4

#include "Misc/Includes.hpp"

/**
*	\file Vector4.hpp
*
*	\brief Vec4 type implementation.
*/

namespace Mathlib
{
	struct Vec2;
	struct Vec3;

	struct MATHLIBRARY_API Vec4
	{
		/// Vector's X component
		float X = 0.f;
		/// Vector's Y component
		float Y = 0.f;
		/// Vector's Z component
		float Z = 0.f;
		/// Vector's W component
		float W = 0.f;

		//Constants
		/// Zero vector constant {0, 0, 0, 0}.
		static const Vec4 Zero;

		/// One vector constant {1, 1, 1, 0}.
		static const Vec4 One;

		/// Right vector constant {1, 0, 0, 0}.
		static const Vec4 Right;

		/// Left vector constant {-1, 0, 0, 0}.
		static const Vec4 Left;

		/// Up vector constant {0, 1, 0, 0}.
		static const Vec4 Up;

		/// Down vector constant {0, -1, 0, 0}.
		static const Vec4 Down;

		/// Down vector constant {0, 0, 1, 0}.
		static const Vec4 Forward;

		/// Down vector constant {0, 0, -1, 0}.
		static const Vec4 Backward;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Vec4() = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _xyz Value applied on all vector axis.
		*/
		Vec4(float _xyzw) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _x X axis value.
		* 	\param[in] _y Y axis value.
		*	\param[in] _z Z axis value.
		*	\param[in] _w W axis value.
		*/
		Vec4(float _x, float _y, float _z, float _w) noexcept;

		/**
		*	\brief Constructor from a Vec2
		*
		*	\param[in] _vec2 Vec2 to copy axis values from.
		*	\param[in] _z Z axis value.
		*	\param[in] _w W axis value.
		*/
		Vec4(Vec2 _vec2, float _z = 0.f, float _w = 0.f) noexcept;

		/**
		*	\brief Constructor from a Vec3
		*
		*	\param[in] _vec3 Vec3 to copy axis values from.
		*	\param[in] _w W axis value.
		*/
		Vec4(Vec3 _vec3, float _w = 0.f) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Vec4(const Vec4& _vec4) = default;

		/**
		*	\brief Default move constructor
		*/
		Vec4(Vec4&& _vec4) = default;

		//Static Methods

		/**
		*	\brief Compute distance between two Vec4
		*
		* 	\param[in] _start left hand side operand to compute distance with.
		* 	\param[in] _end right hand side operand to compute distance with.
		*
		* 	\return distance between _start and _end
		*/
		static float Distance(const Vec4& _start, const Vec4& _end) noexcept;

		/**
		*	\brief Compute squared distance between two Vec4
		*
		* 	\param[in] _start left hand side operand to compute squared distance with.
		* 	\param[in] _end right hand side operand to compute squared distance with.
		*
		* 	\return squared distance between _start and _end
		*/
		static float SqrDistance(const Vec4& _start, const Vec4& _end) noexcept;

		/**
		*	\brief Compute lerped vector between two Vec3
		*
		* 	\param[in] _start left hand side operand to compute lerped vector with.
		* 	\param[in] _end right hand side operand to compute lerped vector with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped vector between _start and _end
		*/
		static Vec4 Lerp(const Vec4& _start, const Vec4& _end, float _alpha) noexcept;

		//Equality

		/**
		*	\brief Check if Vec4 is equal to default Zero vector
		**/
		bool IsZero() const noexcept;

		/**
		*	\brief Compare this vector with with _other
		*
		*	\param[in] _other other vector to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Vec4& _other, float _epsilon = 0.f) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Vec4& _rhs) const noexcept;

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
		Vec4& Normalize() noexcept;

		/**
		*	\brief Return this vector normalized vector.
		*/
		Vec4 GetNormalized() const noexcept;

		/**
		*	\brief Check if the vector is normalized.
		*/
		bool  IsNormalized() const noexcept;

		//Operator

		/**
		*	\brief \e Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Vec4& operator=(Vec4&&) = default;

		/**
		*	\brief \e Default copy assignement.
		*
		*	\return self vector assigned.
		*/
		Vec4& operator=(const Vec4&) = default;

		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		Vec4 operator-() const noexcept;

		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return new vector sum of both vectors.
		*/
		Vec4 operator+(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return new vector result of the substraction of both vectors.
		*/
		Vec4 operator-(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return new vector result of the multiplication of both vectors.
		*/
		Vec4 operator*(const Vec4& _rhs) const noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide this vector with.
		*
		*	\return new vector result of the operation.
		*/
		Vec4 operator/(const Vec4& _rhs) const;

		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return self vector result.
		*/
		Vec4& operator+=(const Vec4& _rhs) noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return self vector result.
		*/
		Vec4& operator-=(const Vec4& _rhs) noexcept;

		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec4& operator*=(const Vec4& _rhs) noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide.
		*
		*	\return self vector result.
		*/
		Vec4& operator/=(const Vec4& _rhs);

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new vector scaled.
		*/
		Vec4 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new divided vector.
		*/
		Vec4 operator/(float _scale) const;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec4& operator*=(float _scale) noexcept;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec4& operator/=(float _scale);

		//Debug

				/**
				*	\brief return vector values as string.
				*/
		std::string ToString()const noexcept;
	};
}

#endif