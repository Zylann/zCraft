/*
interpolation.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/interpolation.hpp"

namespace engine
{
    /*
        Linear intepolations
    */

    float biLinearInterpolation(
		const float x0y0, const float x1y0,
		const float x0y1, const float x1y1,
		const float x, const float y)
	{
		const float tx = smoothCurve(x);
		const float ty = smoothCurve(y);

		const float u = linearInterpolation(x0y0,x1y0, tx);
		const float v = linearInterpolation(x0y1,x1y1, tx);

		return linearInterpolation(u,v,ty);
    }

    float triLinearInterpolation(
        const float v000, const float v100, const float v010, const float v110,
		const float v001, const float v101, const float v011, const float v111,
		const float x, const float y, const float z)
    {
		/*double tx = easeCurve(x);
		double ty = easeCurve(y);
		double tz = easeCurve(z);*/
		const float tx = x;
		const float ty = y;
		const float tz = z;

		return(
			v000 * (1 - tx) * (1 - ty) * (1 - tz) +
			v100 * tx * (1 - ty) * (1 - tz) +
			v010 * (1 - tx) * ty * (1 - tz) +
			v110 * tx * ty * (1 - tz) +
			v001 * (1 - tx) * (1 - ty) * tz +
			v101 * tx * (1 - ty) * tz +
			v011 * (1 - tx) * ty * tz +
			v111 * tx * ty * tz
		);
    }

    /*
        Cubic intepolations
    */

	static float a = 0, b = 0, c = 0, d = 0;

	float cubicInterpolation(float x0, float x1, float x2, float x3, float t)
	{
		a = x3 - x2 - x0 + x1;
		b = x0 - x1 - a;
		c = x2 - x0;
		d = x1;

		return a * t*t*t + b * t*t + c * t + d;
	}

	float biCubicInterpolation(float x0y[4], float x1y[4], float x2y[4], float x3y[4], float x)
	{
		a = cubicInterpolation(x0y[0], x0y[1], x0y[2], x0y[3], x);
		b = cubicInterpolation(x1y[0], x1y[1], x1y[2], x1y[3], x);
		c = cubicInterpolation(x2y[0], x2y[1], x2y[2], x2y[3], x);
		d = cubicInterpolation(x3y[0], x3y[1], x3y[2], x3y[3], x);

		return cubicInterpolation(a,b,c,d, x);
	}

} // namespace engine

