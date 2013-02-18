/*
AABB.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream>
#include "engine/AABB.hpp"

namespace zn
{
	bool AABB::intersects(const AABB & other) const
	{
		return !(other.min.x > max.x || other.max.x < min.x ||
				 other.min.y > max.y || other.max.y < min.y ||
				 other.min.z > max.z || other.max.z < min.z);
	}

	bool AABB::contains(const Vector3f & point) const
	{
		return point.x > min.x && point.x < max.x &&
			   point.y > min.y && point.y < max.y &&
			   point.z > min.z && point.z < max.z;
	}

	void AABB::offset(const Vector3f off)
	{
		min += off;
		max += off;
	}

	void AABB::expand(f32 xyz)
	{
		min.x -= xyz;
		min.y -= xyz;
		min.z -= xyz;
		max.x += xyz;
		max.y += xyz;
		max.z += xyz;
	}

	void AABB::expand(f32 x, f32 y, f32 z)
	{
		min.x -= x;
		min.y -= y;
		min.z -= z;
		max.x += x;
		max.y += y;
		max.z += z;
	}

	void AABB::expandFromVector(const Vector3f vec)
	{
		vec.x < 0 ? min.x += vec.x : max.x += vec.x;
		vec.y < 0 ? min.y += vec.y : max.y += vec.y;
		vec.z < 0 ? min.z += vec.z : max.z += vec.z;
	}

	std::string AABB::toString() const
	{
		std::stringstream ss;
		ss << "(" << min << ", " << max << ")";
		return ss.str();
	}

} // namespace zn



