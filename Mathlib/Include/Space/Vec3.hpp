#pragma once	

#ifndef MATHLIB_VEC3
#define MATHLIB_VEC3

#include "Misc/Includes.hpp"
#include "Misc/Constants.hpp"
#include <string>

/**
*	\file Vec3.hpp
*
*	\brief Vec3 type implementation.
*/

namespace Mathlib
{
	struct Vec2;
	struct Vec4;

	struct MATHLIBRARY_API Vec3
	{
		/// Vector's X component
		float X = 0.f;
		/// Vector's Y component
		float Y = 0.f;
		/// Vector's Z component
		float Z = 0.f;

		//Constants

		/// Zero vector constant {0, 0, 0}.
		static const Vec3 Zero;

		/// One vector constant {1, 1, 1}.
		static const Vec3 One;

		/// Right vector constant {1, 0, 0}.
		static const Vec3 Right;

		/// Left vector constant {-1, 0, 0}.
		static const Vec3 Left;

		/// Up vector constant {0, 1, 0}.
		static const Vec3 Up;

		/// Down vector constant {0, -1, 0}.
		static const Vec3 Down;

		/// Down vector constant {0, 0, 1}.
		static const Vec3 Forward;

		/// Down vector constant {0, 0, -1}.
		static const Vec3 Backward;

		//Constructors

		/**
		*	\brief Default constructor
		*/
		Vec3() = default;

		/**
		*	\brief Value constructor
		*	
		*	\param[in] _xyz Value applied on all vector axis.
		*/
		Vec3(float _xyz) noexcept;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _x X axis value.
		* 	\param[in] _y Y axis value.
		*	\param[in] _z Z axis value.
		*/
		Vec3(float _x, float _y, float _z) noexcept;

		/**
		*	\brief Constructor from a Vec2
		*
		*	\param[in] _vec2 Vec2 to copy axis values from.
		*	\param[in] _z Z axis value.
		*/
		Vec3(const Vec2& _vec2, float _z = 0.f) noexcept;

		/**
		*	\brief Constructor from a Vec4
		*
		*	\param[in] _vec4 Vec4 to copy axis values from.
		*/
		Vec3(const Vec4& _vec4) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Vec3(const Vec3& _vec3) = default;

		/**
		*	\brief Default move constructor
		*/
		Vec3(Vec3&& _vec3) = default;

		//Static Methods

		/**
		*	\brief Compute dot product between two Vec3
		* 
		* 	\param[in] _lhs left hand side operand to compute dot product with.
		* 	\param[in] _rhs right hand side operand to compute dot product with.
		* 
		*	\return dot product between _lhs and _rhs
		*/
		static float DotProduct(const Vec3& _lhs, const Vec3& _rhs) noexcept;

		/**
		*	\brief Compute cross product between two Vec3
		*
		* 	\param[in] _lhs left hand side operand to compute cross product with.
		* 	\param[in] _rhs right hand side operand to compute cross product with.
		* 
		* 	\return cross product between _lhs and _rhs
		*/
		static Vec3 CrossProduct(const Vec3& _lhs, const Vec3& _rhs) noexcept;

		/**
		*	\brief Compute angle between two vectors
		*
		* 	\param[in] _start left hand side operand to compute angle with.
		* 	\param[in] _end right hand side operand to compute angle with.
		* 	\param[in] _normal normal of the plan defined by _start and _end used to determine the angle's sign.
		*
		* 	\return Angle between _start and _end
		*/
		static float Angle(const Vec3& _start, const Vec3& _end, const Vec3& _normal = Vec3::Up);
		
		/**
		*	\brief Compute distance between two Vec3
		*
		* 	\param[in] _start left hand side operand to compute distance with.
		* 	\param[in] _end right hand side operand to compute distance with.
		*
		* 	\return distance between _start and _end
		*/
		static float Distance(const Vec3& _start, const Vec3& _end) noexcept;
		
		/**
		*	\brief Compute squared distance between two Vec3
		*
		* 	\param[in] _start left hand side operand to compute squared distance with.
		* 	\param[in] _end right hand side operand to compute squared distance with.
		*
		* 	\return squared distance between _start and _end
		*/
		static float SqrDistance(const Vec3& _start, const Vec3& _end) noexcept;
		
		/**
		*	\brief Compute lerped vector between two Vec3
		*
		* 	\param[in] _start left hand side operand to compute lerped vector with.
		* 	\param[in] _end right hand side operand to compute lerped vector with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped vector between _start and _end
		*/
		static Vec3 Lerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept;
		
		/**
		*	\brief Compute spherical lerped vector between two Vec3
		*
		* 	\param[in] _start left hand side operand to compute spherical lerped vector with.
		* 	\param[in] _end right hand side operand to compute spherical lerped vector with.
		*	\param[in] _alpha Alpha of the lerp value is between 0 and 1.
		*
		* 	\return spherical lerped vector between _start and _end
		*/
		static Vec3 SLerp(const Vec3& _start, const Vec3& _end, float _alpha) noexcept;

		//Equality

		/**
		*	\brief Check if Vec3 is equal to default Zero vector
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
		bool Equals(const Vec3& _other, float _epsilon = Math::FloatEpsilon) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this vector with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Vec3& _rhs) const noexcept;

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
		Vec3& Normalize() noexcept;

		/**
		*	\brief Return this vector normalized vector.
		*/
		Vec3 GetNormalized() const noexcept;

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
		Vec3 ProjectOn(const Vec3& _other) const noexcept;

		//Operator

		/**
		*	\brief Default move assignement.
		*
		*	\return self vector assigned.
		*/
		Vec3& operator=(Vec3&&) = default;

		/**
		*	\brief Default copy assignement.
		*
		*	\return self vector assigned.
		*/
		Vec3& operator=(const Vec3&) = default;

		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		Vec3 operator-() const noexcept;
		
		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return new vector sum of both vectors.
		*/
		Vec3 operator+(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return new vector result of the substraction of both vectors.
		*/
		Vec3 operator-(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return new vector result of the multiplication of both vectors.
		*/
		Vec3 operator*(const Vec3& _rhs) const noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide this vector with.
		*
		*	\return new vector result of the operation.
		*/
		Vec3 operator/(const Vec3& _rhs) const ;

		/**
		*	\brief Add term by term vector values.
		*
		*	\param[in] _rhs	vector to add.
		*
		*	\return self vector result.
		*/
		Vec3& operator+=(const Vec3& _rhs) noexcept;

		/**
		*	\brief Substract term by term vector values.
		*
		*	\param[in] _rhs	vector to substract.
		*
		*	\return self vector result.
		*/
		Vec3& operator-=(const Vec3& _rhs) noexcept;
		
		/**
		*	\brief Multiply term by term vector values.
		*
		*	\param[in] _rhs	vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec3& operator*=(const Vec3& _rhs) noexcept;

		/**
		*	\brief Divide term by term vector values.
		*
		*	\param[in] _rhs	vector to divide.
		*
		*	\return self vector result.
		*/
		Vec3& operator/=(const Vec3& _rhs) ;

		/**
		*	\brief Add scale to each vector's axis.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new vector scaled.
		*/
		Vec3 operator+(float _scale) const noexcept;

		/**
		*	\brief Substract scale to each vector's axis.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new vector scaled.
		*/
		Vec3 operator-(float _scale) const noexcept;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new vector scaled.
		*/
		Vec3 operator*(float _scale) const noexcept;

		/**
		*	\brief Divide each vector's axis by _scale.
		*
		*	\param[in] _scale	Scale value to apply to all axis.
		*
		*	\return new divided vector.
		*/
		Vec3 operator/(float _scale) const;

		/**
		*	\brief Add scale to each vector's axis.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec3& operator+=(float _scale) noexcept;

		/**
		*	\brief Substract scale to each vector's axis.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec3& operator-=(float _scale) noexcept;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec3& operator*=(float _scale) noexcept;

		/**
		*	\brief Scale each vector's axis by _scale.
		*
		*	\param[in] _scale Scale value to apply to all axis.
		*
		*	\return self vector result.
		*/
		Vec3& operator/=(float _scale) ;

		//Debug

		/**
		*	\brief return vector values as string.
		*/
		std::string ToString()const noexcept;
	};
}

#endif