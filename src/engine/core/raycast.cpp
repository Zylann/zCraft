/*
raycast.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <cmath>
#include "raycast.hpp"

namespace zn
{
	const float g_infinite = 9999999;

	bool RayCaster::cast(const Ray & ray)
	{
		// Equation : p + v*t
		// p : ray start position (ray.pos)
		// v : ray orientation vector (ray.dir)
		// t : parametric variable = a distance if v is normalized

		// This raycasting technique is described here :
		// http://www.cse.yorku.ca/~amana/research/grid.pdf

		// Note : the grid is assumed to have 1-unit square cells.

		/* Initialisation */

		isHit = false;

		// Voxel position
		hit.pos.x = floor(ray.pos.x);
		hit.pos.y = floor(ray.pos.y);
		hit.pos.z = floor(ray.pos.z);
		hit.prevPos = hit.pos;

		// Voxel step
		const s32 xi_step = ray.dir.x > 0 ? 1 : ray.dir.x < 0 ? -1 : 0;
		const s32 yi_step = ray.dir.y > 0 ? 1 : ray.dir.y < 0 ? -1 : 0;
		const s32 zi_step = ray.dir.z > 0 ? 1 : ray.dir.z < 0 ? -1 : 0;

		// Parametric voxel step
		const f32 tdelta_x = xi_step != 0 ? 1.f / fabs(ray.dir.x) : g_infinite;
		const f32 tdelta_y = yi_step != 0 ? 1.f / fabs(ray.dir.y) : g_infinite;
		const f32 tdelta_z = zi_step != 0 ? 1.f / fabs(ray.dir.z) : g_infinite;

		// Parametric grid-cross
		f32 tcross_x; // At which value of T we will cross a vertical line?
		f32 tcross_y; // At which value of T we will cross a horizontal line?
		f32 tcross_z; // At which value of T we will cross a depth line?

		// X initialization
		if(xi_step != 0)
		{
			if(xi_step == 1)
				tcross_x = (ceil(ray.pos.x) - ray.pos.x) * tdelta_x;
			else
				tcross_x = (ray.pos.x - floor(ray.pos.x)) * tdelta_x;
		}
		else
			tcross_x = g_infinite; // Will never cross on X

		// Y initialization
		if(yi_step != 0)
		{
			if(yi_step == 1)
				tcross_y = (ceil(ray.pos.y) - ray.pos.y) * tdelta_y;
			else
				tcross_y = (ray.pos.y - floor(ray.pos.y)) * tdelta_y;
		}
		else
			tcross_y = g_infinite; // Will never cross on X

		// Z initialization
		if(zi_step != 0)
		{
			if(zi_step == 1)
				tcross_z = (ceil(ray.pos.z) - ray.pos.z) * tdelta_z;
			else
				tcross_z = (ray.pos.z - floor(ray.pos.z)) * tdelta_z;
		}
		else
			tcross_z = g_infinite; // Will never cross on X

		/* Iteration */

		do
		{
			hit.prevPos = hit.pos;
			if(tcross_x < tcross_y)
			{
				if(tcross_x < tcross_z)
				{
					// X collision
					//hit.prevPos.x = hit.pos.x;
					hit.pos.x += xi_step;
					if(tcross_x > maxDistance)
						return false;
					tcross_x += tdelta_x;
				}
				else
				{
					// Z collision (duplicate code)
					//hit.prevPos.z = hit.pos.z;
					hit.pos.z += zi_step;
					if(tcross_z > maxDistance)
						return isHit;
					tcross_z += tdelta_z;
				}
			}
			else
			{
				if(tcross_y < tcross_z)
				{
					// Y collision
					//hit.prevPos.y = hit.pos.y;
					hit.pos.y += yi_step;
					if(tcross_y > maxDistance)
						return isHit;
					tcross_y += tdelta_y;
				}
				else
				{
					// Z collision (duplicate code)
					//hit.prevPos.z = hit.pos.z;
					hit.pos.z += zi_step;
					if(tcross_z > maxDistance)
						return isHit;
					tcross_z += tdelta_z;
				}
			}

		} while(!hitFunc(hit.pos));

		isHit = true;
		return isHit;
	}


} // namespace zn

