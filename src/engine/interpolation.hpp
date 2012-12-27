/*
interpolation.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef INTERPOLATION_HPP_INCLUDED
#define INTERPOLATION_HPP_INCLUDED

#include <cmath>

namespace engine
{
    // x in [0,1]
    inline double smoothCurve(double x)
    {
        return 6*pow(x,5)-15*pow(x,4)+10*pow(x,3);
    }

    /*
        Linear interpolations
    */

    inline float linearInterpolation(float x0, float x1, float t)
    {
        return x0 + (x1 - x0) * t;
    }

    float biLinearInterpolation(
        float x0y0, float x1y0,
        float x0y1, float x1y1,
        float x, float y);

    float triLinearInterpolation(
        float v000, float v100, float v010, float v110,
        float v001, float v101, float v011, float v111,
        float x, float y, float z);

    /*
        Cubic interpolations
    */

    float cubicInterpolation(float x0, float x1, float x2, float x3, float t);
    float biCubicInterpolation(float x0y[4], float x1y[4], float x2y[4], float x3y[4], float x);

} // namespace engine


#endif // INTERPOLATION_HPP_INCLUDED
