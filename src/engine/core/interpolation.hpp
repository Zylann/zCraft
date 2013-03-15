/*
interpolation.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef INTERPOLATION_HPP_INCLUDED
#define INTERPOLATION_HPP_INCLUDED

#include <cmath>

namespace zn
{
    // x in [0,1]
    inline float smoothCurve(float x)
    {
        return 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x;
    }

    /*
        Linear interpolations
    */

    inline float linearInterpolation(float x0, float x1, float t)
    {
        return x0 + (x1 - x0) * t;
    }

    float biLinearInterpolation(
        const float x0y0, const float x1y0,
        const float x0y1, const float x1y1,
        const float x, const float y);

    float triLinearInterpolation(
		const float v000, const float v100, const float v010, const float v110,
		const float v001, const float v101, const float v011, const float v111,
		const float x, const float y, const float z);

    /*
        Cubic interpolations
    */

    float cubicInterpolation(float x0, float x1, float x2, float x3, float t);
    float biCubicInterpolation(float x0y[4], float x1y[4], float x2y[4], float x3y[4], float x);

} // namespace zn


#endif // INTERPOLATION_HPP_INCLUDED
