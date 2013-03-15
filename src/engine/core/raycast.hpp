/*
raycast.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_RAYCAST_HPP_INCLUDED
#define ENGINE_RAYCAST_HPP_INCLUDED

#include <functional>
#include "Vector3.hpp"

namespace zn
{
	/*
		This is a voxel traversal algorithm implementation.
	*/

	struct Ray
	{
		Vector3f pos; // origin of the ray
		Vector3f dir; // orientation of the ray (should be normalized)

		Ray() {}
		Ray(const Vector3f & pos0, const Vector3f & dir0) : pos(pos0), dir(dir0) {}
	};

	struct RayHit
	{
		Vector3i pos; // Position of the voxel that stopped the ray
		Vector3i prevPos; // Previously crossed voxel position (to find which face we have hit)
	};

	struct RayCaster
	{
		typedef std::function<bool (const Vector3i&)> HitPredicate;

		// Config (can be modified directly)
		HitPredicate hitFunc;
		f32 maxDistance;

		// Result
		bool isHit = false; // True if hit corresponds to a ray collision
		RayHit hit; // Result of ray casting. Contains last ray state if not.

		// Constructs the raycaster by specifying a hit predicate and a maximal cast distance
		RayCaster(
			HitPredicate hitFunc0,
			f32 maxDistance0)
		: hitFunc(hitFunc0), maxDistance(maxDistance0) {}

		// Casts a ray, returns true if a collision occurred.
		// Options of the raycaster are used.
		// Important : you must normalize the ray direction,
		// otherwise the crossed distance will not be accurate.
		bool cast(const Ray & ray);

	};

} // namespace zn


#endif // ENGINE_RAYCAST_HPP_INCLUDED

