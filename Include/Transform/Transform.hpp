#pragma once

#ifndef MATHLIB_TRANSFORM
#define MATHLIB_TRANSFORM

#include "Misc/DllExport.hpp"
#include "Misc//Constants.hpp"
#include "Misc/Common.hpp"

#include <Space/Quaternion.hpp>
#include <Space/Vec3.hpp>

/**
*	\file Transform.hpp
*
*	\brief Transform type implementation.
*/

namespace Mathlib
{
	struct Mat4;

	/**
	*	\brief transform struct.
	*/
	struct MATHLIBRARY_API Transform
	{
		///  Transform rotation quaternion
		Quat rotation;
		
		///  Transform position vector 3
		Vec3 position;
		
		/// Transform position vector 3
		Vec3 scale;

		//Constructor

		/**
		*	\brief Default constructor
		*/
		Transform() noexcept = default;

		/**
		*	\brief Value constructor
		*
		*	\param[in] _rotation transform  rotation.
		*	\param[in] _position transform position.
		*	\param[in] _scale transform scale.
		*/
		Transform(const Quat& _rotation, const Vec3& _position, const Vec3& _scale) noexcept;
		
		/**
		*	\brief Value constructor
		*
		*	\param[in] _rotation transform euler rotation.
		*	\param[in] _position transform position.
		*	\param[in] _scale transform scale.
		*/
		Transform(const Vec3& _rotation, const Vec3& _position, const Vec3& _scale) noexcept;
		
		/**
		*	\brief Value constructor
		*
		*	\param[in] _rotation transform rotation.
		*/
		Transform(const Quat& _rotation) noexcept;
		
		/**
		*	\brief Value constructor
		*
		*	\param[in] _position transform position.
		*/
		Transform(const Vec3& _position) noexcept;

		/**
		*	\brief Default copy constructor
		*/
		Transform(const Transform& _transform) noexcept = default;

		/**
		*	\brief Default move constructor
		*/
		Transform(Transform&& _transform) noexcept = default;

		//Lerp

		/**
		*	\brief Compute lerped vector between two Transform
		*
		* 	\param[in] _start left hand side operand to compute lerped quaternion with.
		* 	\param[in] _end right hand side operand to compute lerped quaternion with.
		*	\param[in] _alpha Alpha of the lerp.
		*
		* 	\return lerped quaternion between _start and _end
		*/
		static Transform Lerp(const Transform& _start, const Transform& _end, float _alpha);

		//Equality
		/**
		*	\brief Compare this Transform with with _other
		*
		*	\param[in] _other other Transform to do the comparison with.
		* 	\param[in] _epsilon threshold to accept equality.
		*
		*	\return if this and _other are equal.
		*/
		bool Equals(const Transform& _other, float _epsilon = 0.f) const noexcept;

		/**
		*	\brief Operator to compare this Transform with with _rhs
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are equal.
		*/
		bool operator==(const Transform& _rhs) const noexcept;

		/**
		*	\brief Operator to compare this Transform with with _rhs.
		*
		*	\param[in] _rhs right hand side operand to do the comparison with.
		*
		*	\return if this and _rhs are different.
		*/
		bool operator!=(const Transform& _rhs) const noexcept;

		//ToMatrix

		/**
		*	\brief Create matrix from transform components.
		*
		*	\return transform matrix.
		*/
		Mat4 ToMatrixWithScale();

		/**
		*	\brief Create matrix from transform components and invert it.
		*
		*	\return transform matrix inverted.
		*/
		Mat4 ToInverseMatrixWithScale();

		/**
		*	\brief Create matrix from transform components ignoring scale.
		*
		*	\return transform matrix.
		*/
		Mat4 ToMatrixNoScale();

		/**
		*	\brief Create matrix from transform components ignoring scale and invert it.
		*
		*	\return transform matrix inverted.
		*/
		Mat4 ToInverseMatrixNoScale();

		//GetWorldTransfrom
		/**
		*	\brief compute child object world transform based on parent transform.
		*
		*	\param[in] _parent parent object transfrom.
		*	\param[in] _child child object transfrom.
		*
		*	\return return new world transform of the child object.
		*/
		static Transform GetWorldTransfrom(const Transform& _parent, const Transform& _child);
	};
}

#endif