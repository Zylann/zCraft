

#ifndef AABB_HPP_INCLUDED
#define AABB_HPP_INCLUDED

#include <string>
#include <iostream>

#include "engine/Vector3.hpp"

namespace engine
{
	/*
		Axis Aligned Bounding Box
	*/

	class AABB
	{
	public :

		Vector3f min;
		Vector3f max;

		AABB() {}

		AABB(Vector3f p_min, Vector3f p_max) : min(p_min), max(p_max) {}

		inline void set(const AABB & other)
		{
			min = other.min;
			max = other.max;
		}

		bool intersects(const AABB & other) const;

		bool contains(const Vector3f & point) const;

		void offset(const Vector3f off);

		void expand(f32 xyz);

		void expand(f32 x, f32 y, f32 z);

		void expandFromVector(const Vector3f vec);

		std::string toString() const;

	};

	std::ostream & operator<<(std::ostream & os, const AABB & aabb)
	{
		return os << aabb.toString();
	}

} // namespace engine

#endif // AABB_HPP_INCLUDED


