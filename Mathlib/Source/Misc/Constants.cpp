#include <Misc/Constants.hpp>
#include <limits>


namespace Mathlib
{
	namespace Math
	{
		const float Pi = 3.1415926535897932384f;
		const float DegToRad = Pi / 180.0f;
		const float RadToDeg = 180.0f / Pi;
		const float Epsilon = std::numeric_limits<float>::epsilon();
	}
}