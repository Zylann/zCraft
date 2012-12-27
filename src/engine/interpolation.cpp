/*
interpolation.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "engine/interpolation.hpp"

namespace engine
{
    // temp vars
    static float a = 0, b = 0, c = 0, d = 0;

    /*
        Linear intepolations
    */

    float biLinearInterpolation(
        float x0y0, float x1y0,
        float x0y1, float x1y1,
        float x, float y)
    {
        float tx = smoothCurve(x);
        float ty = smoothCurve(y);

        float u = linearInterpolation(x0y0,x1y0,tx);
        float v = linearInterpolation(x0y1,x1y1,tx);

        return linearInterpolation(u,v,ty);
    }

    float triLinearInterpolation(
        float v000, float v100, float v010, float v110,
        float v001, float v101, float v011, float v111,
        float x, float y, float z)
    {
        /*double tx = easeCurve(x);
        double ty = easeCurve(y);
        double tz = easeCurve(z);*/
        float tx = x;
        float ty = y;
        float tz = z;

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

