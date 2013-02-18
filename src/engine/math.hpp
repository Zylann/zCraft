/*
math.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_MATH_HPP_INCLUDED
#define ENGINE_MATH_HPP_INCLUDED

#include <cmath>
#include "engine/types.hpp"

namespace zn
{
namespace math
{
	const f32 ROUNDING_ERROR_F32 = 0.000001f;
	const f64 ROUNDING_ERROR_F64 = 0.00000001;

	/// Constant for PI.
	const f32 PI = 3.14159265359f;

#ifdef PI64 // make sure we don't collide with a define
	#undef PI64
#endif
	/// Constant for 64bit PI.
	const f64 PI64 = 3.1415926535897932384626433832795028841971693993751;

	/// 32bit Constant for converting from degrees to radians
	const f32 DEG2RAD = PI / 180.0f;

	/// 32bit constant for converting from radians to degrees
	const f32 RAD2DEG = 180.0f / PI;

	/// 64bit constant for converting from degrees to radians
	const f64 DEG2RAD64 = PI64 / 180.0;

	/// 64bit constant for converting from radians to degrees
	const f64 RAD2DEG64 = 180.0 / PI64;

	/// Utility function to convert a radian value to degrees
	inline f32 radToDeg(f32 radians)
	{
		return RAD2DEG * radians;
	}

	/// Utility function to convert a degrees value to radians
	inline f32 degToRad(f32 degrees)
	{
		return DEG2RAD * degrees;
	}

	/// Utility function to convert a 64bit radian value to degrees
	inline f64 radToDeg(f64 radians)
	{
		return RAD2DEG64 * radians;
	}

	/// Utility function to convert a 64bit degrees value to radians
	inline f64 degToRad(f64 degrees)
	{
		return DEG2RAD64 * degrees;
	}

	/// returns if a equals b, taking possible rounding errors into account
	inline bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_F64)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	/// returns if a equals b, taking possible rounding errors into account
	inline bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_F32)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	template<class T>
	inline const T & min(const T & a, const T & b)
	{
		return a < b ? a : b;
	}

	template<class T>
	inline const T & max(const T & a, const T & b)
	{
		return a < b ? b : a;
	}

	template<class T>
	inline const T & clamp(const T & x, const T & min, const T & max)
	{
		if(x > max)
			return max;
		else if(x < min)
			return min;
		return x;
	}

	// TODO math: random functions
	// TODO math: put interpolations here (lerp)
	// TODO math: fast rsqrt for vector normalization

} // namespace math
} // namespace zn


#endif // MATH_HPP_INCLUDED
